#include <string>
#include "VMTranslator.h"

using namespace std;

// Declare static members
string VMTranslator::functionName = ""; // or provide a default function name if desired
int VMTranslator::labelCounter = 0;

/**
 * VMTranslator constructor
 */
VMTranslator::VMTranslator() {
    // Your code here
}

/**
 * VMTranslator destructor
 */
VMTranslator::~VMTranslator() {
    // Your code here
}

/** Generate Hack Assembly code for a VM push operation */
string VMTranslator::vm_push(string segment, int offset) {
    if (segment == "constant") {
        return "@" + std::to_string(offset) + "\nD=A\n@SP\nA=M\nM=D\n@SP\nM=M+1\n";
    }
    else if (segment == "local" || segment == "argument" || segment == "this" || segment == "that") {
        string baseAddress = (segment == "local") ? "LCL" :
                             (segment == "argument") ? "ARG" :
                             (segment == "this") ? "THIS" : "THAT";
        return "@" + baseAddress + "\nD=M\n@" + std::to_string(offset) + "\nA=D+A\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n";
    }
    else if (segment == "static") {
        return "@" + functionName + "." + std::to_string(offset) + "\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n";
    }
    else if (segment == "pointer") {
        return "@R" + std::to_string(3 + offset) + "\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n";
    }
    else if (segment == "temp") {
        return "@R" + std::to_string(5 + offset) + "\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n";
    }
    return "";
}

/** Generate Hack Assembly code for a VM pop operation */
string VMTranslator::vm_pop(string segment, int offset) {
    if (segment == "local" || segment == "argument" || segment == "this" || segment == "that") {
        string baseAddress = (segment == "local") ? "LCL" :
                             (segment == "argument") ? "ARG" :
                             (segment == "this") ? "THIS" : "THAT";
        return "@" + baseAddress + "\nD=M\n@" + std::to_string(offset) + "\nD=D+A\n@R13\nM=D\n@SP\nAM=M-1\nD=M\n@R13\nA=M\nM=D\n";
    }
    else if (segment == "static") {
        return "@SP\nAM=M-1\nD=M\n@" + functionName + "." + std::to_string(offset) + "\nM=D\n";
    }
    else if (segment == "pointer") {
        return "@SP\nAM=M-1\nD=M\n@R" + std::to_string(3 + offset) + "\nM=D\n";
    }
    else if (segment == "temp") {
        return "@SP\nAM=M-1\nD=M\n@R" + std::to_string(5 + offset) + "\nM=D\n";
    }
    return "";
}

/** Generate Hack Assembly code for a VM add operation */
string VMTranslator::vm_add(){
    return 
    "@SP\n"         // Get stack pointer address
    "AM=M-1\n"      // Decrement the stack pointer and go to y (the topmost value)
    "D=M\n"         // Store y in D
    "A=A-1\n"       // Go to x (the second topmost value)
    "M=D+M\n";      // Add x and y, then store result at x's location (top of stack now)
}

/** Generate Hack Assembly code for a VM sub operation */
string VMTranslator::vm_sub(){
    return "";
}

/** Generate Hack Assembly code for a VM neg operation */
string VMTranslator::vm_neg(){
    return "";
}

/** Generate Hack Assembly code for a VM eq operation */
string VMTranslator::vm_eq(){
    string label1 = "EQUAL_" + to_string(labelCounter);
    string label2 = "END_EQUAL_" + to_string(labelCounter);
    labelCounter++;

    return 
    "@SP\n"
    "AM=M-1\n"
    "D=M\n"
    "A=A-1\n"
    "D=M-D\n"       // D now has y - x
    "@" + label1 + "\n"
    "D;JEQ\n"      // If y - x is 0 (i.e., y=x), jump to label EQUAL
    "@SP\n"
    "A=M-1\n"
    "M=0\n"        // Push 0 (false)
    "@" + label2 + "\n"
    "0;JMP\n"
    "(" + label1 + ")\n"
    "@SP\n"
    "A=M-1\n"
    "M=-1\n"       // Push -1 (true)
    "(" + label2 + ")\n";
}


/** Generate Hack Assembly code for a VM gt operation */
string VMTranslator::vm_gt(){
    string label1 = "GREATER_" + to_string(labelCounter);
    string label2 = "END_GREATER_" + to_string(labelCounter);
    labelCounter++;

    return
    "@SP\n"
    "AM=M-1\n"
    "D=M\n"
    "A=A-1\n"
    "D=M-D\n"        // D now has y - x
    "@" + label1 + "\n"
    "D;JGT\n"        // If y - x is greater than 0 (i.e., y>x), jump to label GREATER
    "@SP\n"
    "A=M-1\n"
    "M=0\n"          // Push 0 (false)
    "@" + label2 + "\n"
    "0;JMP\n"
    "(" + label1 + ")\n"
    "@SP\n"
    "A=M-1\n"
    "M=-1\n"         // Push -1 (true)
    "(" + label2 + ")\n";
}

/** Generate Hack Assembly code for a VM lt operation */
string VMTranslator::vm_lt(){
    return "";
}

/** Generate Hack Assembly code for a VM and operation */
string VMTranslator::vm_and(){
    return "";
}

/** Generate Hack Assembly code for a VM or operation */
string VMTranslator::vm_or(){
    return "";
}

/** Generate Hack Assembly code for a VM not operation */
string VMTranslator::vm_not(){
    return "";
}

/** Generate Hack Assembly code for a VM label operation */
string VMTranslator::vm_label(string label){
    return "";
}

/** Generate Hack Assembly code for a VM goto operation */
string VMTranslator::vm_goto(string label){
    return "";
}

/** Generate Hack Assembly code for a VM if-goto operation */
string VMTranslator::vm_if(string label){
    return "";
}

/** Generate Hack Assembly code for a VM function operation */
string VMTranslator::vm_function(string function_name, int n_vars){
    return "";
}

/** Generate Hack Assembly code for a VM call operation */
string VMTranslator::vm_call(string function_name, int n_args){
    return "";
}

/** Generate Hack Assembly code for a VM return operation */
string VMTranslator::vm_return(){
    return "";
}