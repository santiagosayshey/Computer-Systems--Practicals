#include <string>
#include <sstream>
#include <stdexcept>
#include <regex>
#include <cstdint>

#include "VMTranslator.h"

using namespace std;

static stringstream streamASM;

void writeToScreen(string asmCode){
    if(asmCode.find("(") == string::npos)
    {
        streamASM << "\t";
    }
    streamASM << asmCode << endl;
}

string nameReg(string segment, int offset){
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
    string seg = nameReg(segment, offset);

    if (segment == "constant")
    {
        writeToScreen("@"+index+" // Push " + segment + " " + index);
        writeToScreen("D=A");
        writeToScreen("@SP");
        writeToScreen("A=M");
        writeToScreen("M=D");
        writeToScreen("@SP");
        writeToScreen("M=M+1");
    }
    else if (seg == "Error")
    {
        throw runtime_error("VM Push(): invalid Segment");
    }
    else if (segment == "static")
    {
        writeToScreen("@" + seg +" // Push " + segment + " " + index);
        writeToScreen("D=A");
        writeToScreen("@" + index);
        writeToScreen("A=D+A");
        writeToScreen("D=M");
        writeToScreen("@SP");
        writeToScreen("A=M");
        writeToScreen("M=D");
        writeToScreen("@SP");
        writeToScreen("M=M+1");
    }
    else if (segment == "pointer" || segment == "temp")
    {
        writeToScreen("@" + seg +" // Push " + segment + " " + index);
        writeToScreen("D=M");
        writeToScreen("@SP");
        writeToScreen("A=M");
        writeToScreen("M=D");
        writeToScreen("@SP");
        writeToScreen("M=M+1");
    }
    else
    {
        writeToScreen("@" + seg +" // Push " + segment + " " + index);
        writeToScreen("D=M");
        writeToScreen("@" + index);
        writeToScreen("A=D+A");
        writeToScreen("D=M");
        writeToScreen("@SP");
        writeToScreen("A=M");
        writeToScreen("M=D");
        writeToScreen("@SP");
        writeToScreen("M=M+1");
    }

    return streamASM.str() + "\n";
}

/** Generate Hack Assembly code for a VM pop operation assessed in Practical Assignment 6 */
string VMTranslator::vm_pop(string segment, int offset){
    
    streamASM.str(string());
    string index = to_string(offset);
    string seg = nameReg(segment, offset);
    
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
        writeToScreen("@" + seg + " // Pop " + segment + index);
        writeToScreen("D=A");
        writeToScreen("@" + index);
        writeToScreen("D=D+A");
        writeToScreen("@R13");
        writeToScreen("M=D");
        writeToScreen("@SP");
        writeToScreen("AM=M-1");
        writeToScreen("D=M");
        writeToScreen("@R13");
        writeToScreen("A=M");
        writeToScreen("M=D");
    }
    else if (segment == "pointer" || segment == "temp")
    {
        writeToScreen("@SP");
        writeToScreen("AM=M-1");
        writeToScreen("D=M");
        writeToScreen("@" + seg);
        writeToScreen("M=D");
    }
    else
    {
        writeToScreen("@" + seg + " // Pop " + segment + index);
        writeToScreen("D=M");
        writeToScreen("@" + index);
        writeToScreen("D=D+A");
        writeToScreen("@R13");
        writeToScreen("M=D");
        writeToScreen("@SP");
        writeToScreen("AM=M-1");
        writeToScreen("D=M");
        writeToScreen("@R13");
        writeToScreen("A=M");
        writeToScreen("M=D");
    }

    return streamASM.str() + "\n";
}

/** Generate Hack Assembly code for a VM add operation assessed in Practical Assignment 6 */
string VMTranslator::vm_add(){
    streamASM.str(string());
    writeToScreen("@SP");
    writeToScreen("AM=M-1");
    writeToScreen("D=M");
    writeToScreen("A=A-1");
    writeToScreen("M=M+D");
    return streamASM.str() + "\n";
}

/** Generate Hack Assembly code for a VM sub operation assessed in Practical Assignment 6 */
string VMTranslator::vm_sub(){
    streamASM.str(string());
    writeToScreen("@SP");
    writeToScreen("AM=M-1");
    writeToScreen("D=M");
    writeToScreen("A=A-1");
    writeToScreen("M=M-D");
    return streamASM.str() + "\n";
}

/** Generate Hack Assembly code for a VM neg operation assessed in Practical Assignment 6 */
string VMTranslator::vm_neg(){
    streamASM.str(string());
    writeToScreen("@SP");
    writeToScreen("A=M");
    writeToScreen("A=A-1");
    writeToScreen("M=-M");
    return streamASM.str() + "\n";
}

/** Generate Hack Assembly code for a VM eq operation assessed in Practical Assignment 6 */
string VMTranslator::vm_eq(){
    streamASM.str(string());
    writeToScreen("@SP");
    writeToScreen("AM=M-1");
    writeToScreen("D=M");
    writeToScreen("@SP");
    writeToScreen("AM=M-1");
    writeToScreen("D=M-D");
    writeToScreen("@ifEQTrue");
    writeToScreen("D;JEQ");
    writeToScreen("D=0");
    writeToScreen("@ifEQFalse");
    writeToScreen("0;JMP");
    writeToScreen("(ifEQTrue)");
    writeToScreen("D=-1");
    writeToScreen("(ifEQFalse)");
    writeToScreen("@SP");
    writeToScreen("A=M");
    writeToScreen("M=D");
    writeToScreen("@SP");
    writeToScreen("M=M+1");
    return streamASM.str() + "\n";
}

/** Generate Hack Assembly code for a VM gt operation assessed in Practical Assignment 6 */
string VMTranslator::vm_gt(){
    streamASM.str(string());
    writeToScreen("@SP");
    writeToScreen("AM=M-1");
    writeToScreen("D=M");
    writeToScreen("@SP");
    writeToScreen("AM=M-1");
    writeToScreen("D=M-D");
    writeToScreen("@ifGTTrue");
    writeToScreen("D;JGT");
    writeToScreen("D=0");
    writeToScreen("@ifGTFalse");
    writeToScreen("0;JMP");
    writeToScreen("(ifGTTrue)");
    writeToScreen("D=-1");
    writeToScreen("(ifGTFalse)");
    writeToScreen("@SP");
    writeToScreen("A=M");
    writeToScreen("M=D");
    writeToScreen("@SP");
    writeToScreen("M=M+1");
    return streamASM.str() + "\n";
}

/** Generate Hack Assembly code for a VM lt operation assessed in Practical Assignment 6 */
string VMTranslator::vm_lt(){
    streamASM.str(string());
    writeToScreen("@SP");
    writeToScreen("AM=M-1");
    writeToScreen("D=M");
    writeToScreen("@SP");
    writeToScreen("AM=M-1");
    writeToScreen("D=M-D");
    writeToScreen("@ifLTTrue");
    writeToScreen("D;JLT");
    writeToScreen("D=0");
    writeToScreen("@ifLTFalse");
    writeToScreen("0;JMP");
    writeToScreen("(ifLTTrue)");
    writeToScreen("D=-1");
    writeToScreen("(ifLTFalse)");
    writeToScreen("@SP");
    writeToScreen("A=M");
    writeToScreen("M=D");
    writeToScreen("@SP");
    writeToScreen("M=M+1");
    return streamASM.str() + "\n";
}

/** Generate Hack Assembly code for a VM and operation assessed in Practical Assignment 6 */
string VMTranslator::vm_and(){
    streamASM.str(string());
    writeToScreen("@SP");
    writeToScreen("AM=M-1");
    writeToScreen("D=M");
    writeToScreen("A=A-1");
    writeToScreen("M=D&M");
    return streamASM.str() + "\n";
}

/** Generate Hack Assembly code for a VM or operation assessed in Practical Assignment 6 */
string VMTranslator::vm_or(){
    streamASM.str(string());
    writeToScreen("@SP");
    writeToScreen("AM=M-1");
    writeToScreen("D=M");
    writeToScreen("A=A-1");
    writeToScreen("M=D|M");
    return streamASM.str() + "\n";
}

/** Generate Hack Assembly code for a VM not operation assessed in Practical Assignment 6 */
string VMTranslator::vm_not(){
    streamASM.str(string());
    writeToScreen("@SP");
    writeToScreen("A=M");
    writeToScreen("A=A-1");
    writeToScreen("M=!M");
    return streamASM.str() + "\n";
}

/** Generate Hack Assembly code for a VM label operation assessed in Practical Assignment 7 */
string VMTranslator::vm_label(string label){
    return "";
}

/** Generate Hack Assembly code for a VM goto operation assessed in Practical Assignment 7 */
string VMTranslator::vm_goto(string label){
    return "";
}

/** Generate Hack Assembly code for a VM if-goto operation assessed in Practical Assignment 7 */
string VMTranslator::vm_if(string label){
    return "";
}

/** Generate Hack Assembly code for a VM function operation assessed in Practical Assignment 7 */
string VMTranslator::vm_function(string function_name, int n_vars){
    return "";
}

/** Generate Hack Assembly code for a VM call operation assessed in Practical Assignment 7 */
string VMTranslator::vm_call(string function_name, int n_args){
    return "";
}

/** Generate Hack Assembly code for a VM return operation assessed in Practical Assignment 7 */
string VMTranslator::vm_return(){
    return "";
}

// string VMTranslator::vm_end(){
//     streamASM.str(string());
//     writeToScreen("(END)");
//     writeToScreen("@END");
//     writeToScreen("0;JMP");
//     return streamASM.str() + "\n";
// }