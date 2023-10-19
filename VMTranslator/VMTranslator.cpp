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

/** Generate Hack Assembly code for a VM function operation */
string VMTranslator::vm_function(string function_name, int n_vars){
    string code = "(" + function_name + ")\n"; // Create the function label
    // Initialize the local variables to 0 and push them to the stack
    for(int i = 0; i < n_vars; i++) {
        code += "@0\n" // Load constant 0
                "D=A\n" // Store it in D
                "@SP\n" // Point to the current stack pointer
                "A=M\n" // Go to the top of the stack
                "M=D\n" // Push 0 to the stack
                "@SP\n" // Increment stack pointer
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
    code += "@LCL\nD=M\n@R13\nM=D\n"; // We'll use R13 as EndFrame
    // RET = *(EndFrame-5)
    code += "@5\nA=D-A\nD=M\n@R14\nM=D\n"; // We'll use R14 as RET
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
