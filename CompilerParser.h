#ifndef COMPILERPARSER_H
#define COMPILERPARSER_H

#include <list>
#include <exception>

#include "ParseTree.h"
#include "Token.h"

class CompilerParser {
    private:
        std::list<Token*>::iterator currentToken;
        std::list<Token*> tokens;
    public:
        CompilerParser(std::list<Token*> tokens);

        ParseTree* compileProgram();
        ParseTree* compileClass();
        ParseTree* compileClassVarDec();
        ParseTree* compileSubroutine();
        ParseTree* compileParameterList();
        ParseTree* compileSubroutineCall();
        ParseTree* compileSubroutineBody();
        ParseTree* compileVarDec();

        ParseTree* compileStatements();
        ParseTree* compileLet();
        ParseTree* compileIf();
        ParseTree* compileWhile();
        ParseTree* compileDo();
        ParseTree* compileReturn();

        ParseTree* compileExpression();

        ParseTree* compileTerm();
        ParseTree* compileExpressionList();
        
        void next();
        Token* current();
        bool have(std::string expectedType, std::string expectedValue);
        Token* mustBe(std::string expectedType, std::string expectedValue);
        bool isOperator(const std::string& value);
};

class ParseException : public std::exception {
private:
    std::string message;
public:
    explicit ParseException(const std::string& msg = "An Exception occurred while parsing!") : message(msg) {}
    
    virtual const char* what() const noexcept override {
        return message.c_str();
    }
};

#endif /*COMPILERPARSER_H*/