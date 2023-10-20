#ifndef COMPILERPARSER_H
#define COMPILERPARSER_H

#include <list>
#include <exception>
#include <string>

#include "ParseTree.h"
#include "Token.h"

class CompilerParser {
    private:
        std::list<Token*> tokens; // List of tokens to parse
        std::list<Token*>::iterator currentToken; // Current position in the token list

    public:
        CompilerParser(std::list<Token*> tokens);

        ParseTree* compileProgram();
        ParseTree* compileClass();
        ParseTree* compileClassVarDec();
        ParseTree* compileSubroutine();
        ParseTree* compileParameterList();
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

        bool isOp(Token* token);            // checks if the token is an operator
        bool isUnaryOp(Token* token);       // checks if the token is a unary operator
        bool isStartOfTerm(Token* token);   // checks if the token is the start of a term

        void next();
        Token* current();
        bool have(std::string expectedType, std::string expectedValue);
        Token* mustBe(std::string expectedType, std::string expectedValue);
};

class ParseException : public std::exception {
    public:
        const char* what() const noexcept override; // Removed extra semicolon
};

#endif /*COMPILERPARSER_H*/
