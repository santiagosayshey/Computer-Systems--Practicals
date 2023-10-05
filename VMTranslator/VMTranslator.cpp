#include <string>
#include "VMTranslator.h"

using namespace std;

// Declare static members
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
string VMTranslator::vm_push(string segment, int offset)
{
    string assemblyCode = "";
    string indexStr = to_string(offset);
    string registerStr = registerName(segment, offset);

    if(segment == "constant")
    {
        assemblyCode += "@" + indexStr + "\n";
        assemblyCode += "D=A\n";
        assemblyCode += "@SP\n";
        assemblyCode += "A=M\n";
        assemblyCode += "M=D\n";
        assemblyCode += "@SP\n";
        assemblyCode += "M=M+1\n";
    } 
    else if(segment == "static" || segment == "temp" || segment == "pointer")
    {
        assemblyCode += "@" + registerStr + "\n";
        assemblyCode += "D=A\n";
        assemblyCode += "@" + indexStr + "\n";
        assemblyCode += "A=D+A\n";
        assemblyCode += "D=M\n";
        assemblyCode += "@SP\n";
        assemblyCode += "A=M\n";
        assemblyCode += "M=D\n";
        assemblyCode += "@SP\n";
        assemblyCode += "M=M+1\n";
    } 
    else if(segment == "argument" || segment == "local" || segment == "this" || segment == "that")
    {
        assemblyCode += "@" + registerStr + "\n";
        assemblyCode += "D=M\n";
        assemblyCode += "@" + indexStr + "\n";
        assemblyCode += "A=D+A\n";
        assemblyCode += "D=M\n";
        assemblyCode += "@SP\n";
        assemblyCode += "A=M\n";
        assemblyCode += "M=D\n";
        assemblyCode += "@SP\n";
        assemblyCode += "M=M+1\n";
    }
    else 
    {
        return assemblyCode;
    }

    return assemblyCode;
}


/** Generate Hack Assembly code for a VM pop operation */
string VMTranslator::vm_pop(string segment, int offset)
{
    string assemblyCode = "";
    string indexStr = to_string(offset);
    string registerStr = registerName(segment, offset);

    if(segment == "constant")
    {
        return assemblyCode;
    } 
    else if(segment == "static")
    {
        assemblyCode += "@" + registerStr + "\n";
        assemblyCode += "D=A\n";
        assemblyCode += "@" + indexStr + "\n";
        assemblyCode += "D=D+A\n";
        assemblyCode += "@R13\n";
        assemblyCode += "M=D\n";
        assemblyCode += "@SP\n";
        assemblyCode += "AM=M-1\n";
        assemblyCode += "D=M\n";
        assemblyCode += "@R13\n";
        assemblyCode += "A=M\n";
        assemblyCode += "M=D\n";
    } 
    else if(segment == "argument" || segment == "local" || segment == "this" || segment == "that" || segment == "temp" || segment == "pointer")
    {
        assemblyCode += "@" + registerStr + "\n";
        assemblyCode += "D=M\n";
        assemblyCode += "@" + indexStr + "\n";
        assemblyCode += "D=D+A\n";
        assemblyCode += "@R13\n";
        assemblyCode += "M=D\n";
        assemblyCode += "@SP\n";
        assemblyCode += "AM=M-1\n";
        assemblyCode += "D=M\n";
        assemblyCode += "@R13\n";
        assemblyCode += "A=M\n";
        assemblyCode += "M=D\n";
    }
    else 
    {
        return assemblyCode;
    }

    return assemblyCode;
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
    return "(" + label + ")\n";
}

/** Generate Hack Assembly code for a VM goto operation */
string VMTranslator::vm_goto(string label){
    return "@" + label + "\n0;JMP\n";
}

/** Generate Hack Assembly code for a VM if-goto operation */
string VMTranslator::vm_if(string label){
    return 
    "@SP\n"        // Point to the current stack pointer.
    "AM=M-1\n"     // Decrement the stack pointer and go to the topmost value.
    "D=M\n"        // Pop the topmost value to D.
    "@" + label + "\n"
    "D;JNE\n";     // Jump if D (the popped value) is not 0.
}

/** Generate Hack Assembly code for a VM function operation */
string VMTranslator::vm_function(string function_name, int n_vars){
    string code = "(" + function_name + ")\n";  // Create the function label

    // Initialize the local variables to 0 and push them to the stack
    for(int i = 0; i < n_vars; i++) {
        code += "@0\n"          // Load constant 0
                "D=A\n"          // Store it in D
                "@SP\n"          // Point to the current stack pointer
                "A=M\n"          // Go to the top of the stack
                "M=D\n"          // Push 0 to the stack
                "@SP\n"          // Increment stack pointer
                "M=M+1\n";
    }

    return code;
}

/** Generate Hack Assembly code for a VM call operation */
string VMTranslator::vm_call(string function_name, int n_args){
    // Unique label for returning after the function is done
    string returnLabel = "RETURN_" + function_name + "_" + to_string(labelCounter++);
    string code = "";

    // Push the return address
    code += "@" + returnLabel + "\nD=A\n@SP\nA=M\nM=D\n@SP\nM=M+1\n";

    // Save LCL, ARG, THIS, and THAT
    string segments[] = {"LCL", "ARG", "THIS", "THAT"};
    for (string segment : segments) {
        code += "@" + segment + "\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n";
    }

    // ARG = SP - n_args - 5
    code += "@SP\nD=M\n@" + to_string(n_args + 5) + "\nD=D-A\n@ARG\nM=D\n";

    // LCL = SP
    code += "@SP\nD=M\n@LCL\nM=D\n";

    // Goto function
    code += "@" + function_name + "\n0;JMP\n";

    // Declare the return label
    code += "(" + returnLabel + ")\n";

    return code;
}

/** Generate Hack Assembly code for a VM return operation */
string VMTranslator::vm_return(){
    string code = "";

    // EndFrame = LCL (temporary variable)
    code += "@LCL\nD=M\n@R13\nM=D\n";  // We'll use R13 as EndFrame

    // RET = *(EndFrame-5)
    code += "@5\nA=D-A\nD=M\n@R14\nM=D\n";  // We'll use R14 as RET

    // *ARG = pop()
    code += "@SP\nAM=M-1\nD=M\n@ARG\nA=M\nM=D\n";

    // SP = ARG+1
    code += "@ARG\nD=M+1\n@SP\nM=D\n";

    // Restore THAT, THIS, ARG, LCL
    string segments[] = {"THAT", "THIS", "ARG", "LCL"};
    for (int i = 1; i <= 4; i++) {
        code += "@R13\nD=M\n@" + to_string(i) + "\nA=D-A\nD=M\n@" + segments[i-1] + "\nM=D\n";
    }

    // Goto RET
    code += "@R14\nA=M\n0;JMP\n";

    return code;
}

string VMTranslator::registerName(string segment, int index)
{
    if (segment == "static")
        return "16";
    if (segment == "local")
        return "LCL";
    if (segment == "argument")
        return "ARG";
    if (segment == "this")
        return "THIS";
    if (segment == "that")
        return "THAT";
    if (segment == "pointer")
        return "R" + to_string(3 + index);
    if (segment == "temp")
        return "R" + to_string(5 + index);

    string moduleName = "";
    return moduleName + "." + to_string(index); // else it is static
}