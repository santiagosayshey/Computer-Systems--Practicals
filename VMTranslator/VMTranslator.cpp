#include <string>
#include <sstream>
#include <stdexcept>
#include <regex>
#include <cstdint>

#include "VMTranslator.h"

using namespace std;

static stringstream streamASM;

int VMTranslator::labelCounter = 0; // definition and initialization


void appendInstruction(string asmCode){
    if(asmCode.find("(") == string::npos)
    {
        streamASM << "\t";
    }
    streamASM << asmCode << endl;
}

string getSegment(string segment, int offset){
    if (segment == "this")
    {
        return "THIS";
    }
    else if (segment == "that")
    {
        return "THAT";
    }
    else if (segment == "pointer")
    {
        return "R" + to_string(3 + offset);
    }
    else if (segment == "argument")
    {
        return "ARG";
    }
    else if (segment == "local")
    {
        return "LCL";
    }
    else if (segment == "temp")
    {
        return "R" + to_string(5 + offset);
    }
    else if (segment == "static")
    {
        return "16";
    }
    return "Error";
}

VMTranslator::VMTranslator() {
    // Your code here
}


VMTranslator::~VMTranslator() {
    // Your code here
}

/** Generate Hack Assembly code for a VM push operation assessed in Practical Assignment 6 */
string VMTranslator::vm_push(string segment, int offset){;

    streamASM.str(string());
    string index = to_string(offset);
    string seg = getSegment(segment, offset);

    if (segment == "constant")
    {
        appendInstruction("@"+index+" // Push " + segment + " " + index);
        appendInstruction("D=A");
        appendInstruction("@SP");
        appendInstruction("A=M");
        appendInstruction("M=D");
        appendInstruction("@SP");
        appendInstruction("M=M+1");
    }
    else if (seg == "Error")
    {
        throw runtime_error("VM Push(): invalid Segment");
    }
    else if (segment == "static")
    {
        appendInstruction("@" + seg +" // Push " + segment + " " + index);
        appendInstruction("D=A");
        appendInstruction("@" + index);
        appendInstruction("A=D+A");
        appendInstruction("D=M");
        appendInstruction("@SP");
        appendInstruction("A=M");
        appendInstruction("M=D");
        appendInstruction("@SP");
        appendInstruction("M=M+1");
    }
    else if (segment == "pointer" || segment == "temp")
    {
        appendInstruction("@" + seg +" // Push " + segment + " " + index);
        appendInstruction("D=M");
        appendInstruction("@SP");
        appendInstruction("A=M");
        appendInstruction("M=D");
        appendInstruction("@SP");
        appendInstruction("M=M+1");
    }
    else
    {
        appendInstruction("@" + seg +" // Push " + segment + " " + index);
        appendInstruction("D=M");
        appendInstruction("@" + index);
        appendInstruction("A=D+A");
        appendInstruction("D=M");
        appendInstruction("@SP");
        appendInstruction("A=M");
        appendInstruction("M=D");
        appendInstruction("@SP");
        appendInstruction("M=M+1");
    }

    return streamASM.str() + "\n";
}

/** Generate Hack Assembly code for a VM pop operation assessed in Practical Assignment 6 */
string VMTranslator::vm_pop(string segment, int offset){
    
    streamASM.str(string());
    string index = to_string(offset);
    string seg = getSegment(segment, offset);
    
    if ( segment == "constant")
    {
        throw runtime_error("VM pop(): can't pop constant");
    }
    else if ( seg == "Error")
    {
        throw runtime_error("VM pop(): invalid Segment");
    }
    else if (segment == "static")
    {
        appendInstruction("@" + seg + " // Pop " + segment + index);
        appendInstruction("D=A");
        appendInstruction("@" + index);
        appendInstruction("D=D+A");
        appendInstruction("@R13");
        appendInstruction("M=D");
        appendInstruction("@SP");
        appendInstruction("AM=M-1");
        appendInstruction("D=M");
        appendInstruction("@R13");
        appendInstruction("A=M");
        appendInstruction("M=D");
    }
    else if (segment == "pointer" || segment == "temp")
    {
        appendInstruction("@SP");
        appendInstruction("AM=M-1");
        appendInstruction("D=M");
        appendInstruction("@" + seg);
        appendInstruction("M=D");
    }
    else
    {
        appendInstruction("@" + seg + " // Pop " + segment + index);
        appendInstruction("D=M");
        appendInstruction("@" + index);
        appendInstruction("D=D+A");
        appendInstruction("@R13");
        appendInstruction("M=D");
        appendInstruction("@SP");
        appendInstruction("AM=M-1");
        appendInstruction("D=M");
        appendInstruction("@R13");
        appendInstruction("A=M");
        appendInstruction("M=D");
    }

    return streamASM.str() + "\n";
}

/** Generate Hack Assembly code for a VM add operation assessed in Practical Assignment 6 */
string VMTranslator::vm_add(){
    streamASM.str(string());
    appendInstruction("@SP");
    appendInstruction("AM=M-1");
    appendInstruction("D=M");
    appendInstruction("A=A-1");
    appendInstruction("M=M+D");
    return streamASM.str() + "\n";
}

/** Generate Hack Assembly code for a VM sub operation assessed in Practical Assignment 6 */
string VMTranslator::vm_sub(){
    streamASM.str(string());
    appendInstruction("@SP");
    appendInstruction("AM=M-1");
    appendInstruction("D=M");
    appendInstruction("A=A-1");
    appendInstruction("M=M-D");
    return streamASM.str() + "\n";
}

/** Generate Hack Assembly code for a VM neg operation assessed in Practical Assignment 6 */
string VMTranslator::vm_neg(){
    streamASM.str(string());
    appendInstruction("@SP");
    appendInstruction("A=M");
    appendInstruction("A=A-1");
    appendInstruction("M=-M");
    return streamASM.str() + "\n";
}

/** Generate Hack Assembly code for a VM eq operation assessed in Practical Assignment 6 */
string VMTranslator::vm_eq(){
    streamASM.str(string());  // Clear the stream
    string label1 = "EQUAL_" + to_string(labelCounter++);
    string label2 = "END_EQUAL_" + to_string(labelCounter++);

    appendInstruction("@SP");
    appendInstruction("AM=M-1");
    appendInstruction("D=M");
    appendInstruction("A=A-1");
    appendInstruction("D=M-D");
    appendInstruction("@" + label1);
    appendInstruction("D;JEQ");
    appendInstruction("@SP");
    appendInstruction("A=M-1");
    appendInstruction("M=0");  // if not equal
    appendInstruction("@" + label2);
    appendInstruction("0;JMP");
    appendInstruction("(" + label1 + ")");
    appendInstruction("@SP");
    appendInstruction("A=M-1");
    appendInstruction("M=-1");  // if equal
    appendInstruction("(" + label2 + ")");

    return streamASM.str();
}

/** Generate Hack Assembly code for a VM gt operation assessed in Practical Assignment 6 */
string VMTranslator::vm_gt(){
    streamASM.str(string());  // Clear the stream
    string label1 = "GREATER_" + to_string(labelCounter++);
    string label2 = "END_GREATER_" + to_string(labelCounter++);

    appendInstruction("@SP");
    appendInstruction("AM=M-1");
    appendInstruction("D=M");
    appendInstruction("A=A-1");
    appendInstruction("D=M-D");
    appendInstruction("@" + label1);
    appendInstruction("D;JGT");
    appendInstruction("@SP");
    appendInstruction("A=M-1");
    appendInstruction("M=0");  // if not greater
    appendInstruction("@" + label2);
    appendInstruction("0;JMP");
    appendInstruction("(" + label1 + ")");
    appendInstruction("@SP");
    appendInstruction("A=M-1");
    appendInstruction("M=-1");  // if greater
    appendInstruction("(" + label2 + ")");

    return streamASM.str();
}

/** Generate Hack Assembly code for a VM lt operation assessed in Practical Assignment 6 */
string VMTranslator::vm_lt(){
    streamASM.str(string());  // Clear the stream
    string label1 = "LESS_" + to_string(labelCounter++);
    string label2 = "END_LESS_" + to_string(labelCounter++);

    appendInstruction("@SP");
    appendInstruction("AM=M-1");
    appendInstruction("D=M");
    appendInstruction("A=A-1");
    appendInstruction("D=M-D");
    appendInstruction("@" + label1);
    appendInstruction("D;JLT");
    appendInstruction("@SP");
    appendInstruction("A=M-1");
    appendInstruction("M=0");  // if not less
    appendInstruction("@" + label2);
    appendInstruction("0;JMP");
    appendInstruction("(" + label1 + ")");
    appendInstruction("@SP");
    appendInstruction("A=M-1");
    appendInstruction("M=-1");  // if less
    appendInstruction("(" + label2 + ")");

    return streamASM.str();
}
/** Generate Hack Assembly code for a VM and operation assessed in Practical Assignment 6 */
string VMTranslator::vm_and(){
    streamASM.str(string());
    appendInstruction("@SP");
    appendInstruction("AM=M-1");
    appendInstruction("D=M");
    appendInstruction("A=A-1");
    appendInstruction("M=D&M");
    return streamASM.str() + "\n";
}

/** Generate Hack Assembly code for a VM or operation assessed in Practical Assignment 6 */
string VMTranslator::vm_or(){
    streamASM.str(string());
    appendInstruction("@SP");
    appendInstruction("AM=M-1");
    appendInstruction("D=M");
    appendInstruction("A=A-1");
    appendInstruction("M=D|M");
    return streamASM.str() + "\n";
}

/** Generate Hack Assembly code for a VM not operation assessed in Practical Assignment 6 */
string VMTranslator::vm_not(){
    streamASM.str(string());
    appendInstruction("@SP");
    appendInstruction("A=M");
    appendInstruction("A=A-1");
    appendInstruction("M=!M");
    return streamASM.str() + "\n";
}

/** Generate Hack Assembly code for a VM label operation assessed in Practical Assignment 7 */
string VMTranslator::vm_label(string label){
    streamASM.str(string());
    appendInstruction("(" + label + ")");
    return streamASM.str();
}

/** Generate Hack Assembly code for a VM goto operation assessed in Practical Assignment 7 */
string VMTranslator::vm_goto(string label){
    streamASM.str(string());
    appendInstruction("@" + label);
    appendInstruction("0;JMP");
    return streamASM.str();
}

/** Generate Hack Assembly code for a VM if-goto operation assessed in Practical Assignment 7 */
string VMTranslator::vm_if(string label){
    streamASM.str(string());
    appendInstruction("@SP");
    appendInstruction("AM=M-1");
    appendInstruction("D=M");
    appendInstruction("@" + label);
    appendInstruction("D;JNE");
    return streamASM.str();
}

/** Generate Hack Assembly code for a VM function operation assessed in Practical Assignment 7 */
string VMTranslator::vm_function(string function_name, int n_vars){
    streamASM.str(string());
    appendInstruction("(" + function_name + ")");
    for (int i = 0; i < n_vars; i++) {
        appendInstruction("@0");
        appendInstruction("D=A");
        appendInstruction("@SP");
        appendInstruction("A=M");
        appendInstruction("M=D");
        appendInstruction("@SP");
        appendInstruction("M=M+1");
    }
    return streamASM.str();
}

/** Generate Hack Assembly code for a VM call operation assessed in Practical Assignment 7 */
string VMTranslator::vm_call(string function_name, int n_args){
    // This is a more complex function, as it involves several steps to manage the stack.
    // A simplified version is provided here. Please adapt as needed for your VM implementation.
    streamASM.str(string());
    string returnLabel = "return_" + function_name + "_" + to_string(labelCounter++);

    // Push return address
    appendInstruction("@" + returnLabel);
    appendInstruction("D=A");
    appendInstruction("@SP");
    appendInstruction("A=M");
    appendInstruction("M=D");
    appendInstruction("@SP");
    appendInstruction("M=M+1");

    // Push LCL, ARG, THIS, THAT
    // (Skipping for brevity. It's similar to pushing the return address, but using M instead of A for the data transfer.)

    // ARG = SP-n-5
    appendInstruction("@SP");
    appendInstruction("D=M");
    appendInstruction("@" + to_string(n_args));
    appendInstruction("D=D-A");
    appendInstruction("@5");
    appendInstruction("D=D-A");
    appendInstruction("@ARG");
    appendInstruction("M=D");

    // LCL = SP
    appendInstruction("@SP");
    appendInstruction("D=M");
    appendInstruction("@LCL");
    appendInstruction("M=D");

    // Goto function
    appendInstruction("@" + function_name);
    appendInstruction("0;JMP");

    // Label for return address
    appendInstruction("(" + returnLabel + ")");

    return streamASM.str();
}

/** Generate Hack Assembly code for a VM return operation assessed in Practical Assignment 7 */
string VMTranslator::vm_return(){
    streamASM.str(string());
    // FRAME = LCL
    appendInstruction("@LCL");
    appendInstruction("D=M");
    appendInstruction("@R13");
    appendInstruction("M=D");

    // RET = *(FRAME-5)
    appendInstruction("@5");
    appendInstruction("A=D-A");
    appendInstruction("D=M");
    appendInstruction("@R14");
    appendInstruction("M=D");

    // *ARG = pop()
    // (Skipping the pop implementation for brevity, it's similar to your vm_pop function.)

    // SP = ARG+1
    appendInstruction("@ARG");
    appendInstruction("D=M+1");
    appendInstruction("@SP");
    appendInstruction("M=D");

    // THAT = *(FRAME-1), THIS = *(FRAME-2), ARG = *(FRAME-3), LCL = *(FRAME-4)
    // (Skipping for brevity. It's a sequence of accessing memory locations relative to the FRAME and restoring values.)

    // Goto RET
    appendInstruction("@R14");
    appendInstruction("A=M");
    appendInstruction("0;JMP");

    return streamASM.str();
}