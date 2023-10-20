#include "CompilerParser.h"


/**
 * Constructor for the CompilerParser
 * @param tokens A linked list of tokens to be parsed
 */
CompilerParser::CompilerParser(std::list<Token*> tokens) : tokens(tokens), currentToken(tokens.begin()) {

}

/**
 * Generates a parse tree for a single program
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileProgram() {
    // We're expecting a class as the first construct in a valid Jack program
    if (!have("keyword", "class")) {
        throw ParseException(); // The program should start with a class definition
    }

    return compileClass(); // Delegate to compileClass to handle class construction
}

/**
 * Generates a parse tree for a single class
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileClass() {
    // Structure for class: 'class' className '{' classVarDec* subroutineDec* '}'
    mustBe("keyword", "class");
    ParseTree* classNode = new ParseTree("class");

    classNode->addChild(mustBe("identifier")); // className
    classNode->addChild(mustBe("symbol", "{"));

    while (have("keyword", "static") || have("keyword", "field")) {
        classNode->addChild(compileClassVarDec()); // classVarDec
    }

    // Here you would also handle subroutineDec, which are methods, functions, and constructors
    // while (have("keyword", "function") || have("keyword", "method") || have("keyword", "constructor")) {
    //     classNode->addChild(compileSubroutine());
    // }

    classNode->addChild(mustBe("symbol", "}"));

    return classNode;
}


/**
 * Generates a parse tree for a static variable declaration or field declaration
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileClassVarDec() {
    // Structure for class variable declaration: ('static' | 'field') type varName (',' varName)* ';'
    ParseTree* varDecNode = new ParseTree("classVarDec");

    varDecNode->addChild(mustBe("keyword")); // 'static' | 'field'
    varDecNode->addChild(mustBe("keyword")); // type: 'int', 'char', 'boolean' or className
    varDecNode->addChild(mustBe("identifier")); // varName

    while (have("symbol", ",")) {
        varDecNode->addChild(mustBe("symbol", ","));
        varDecNode->addChild(mustBe("identifier")); // varName
    }

    varDecNode->addChild(mustBe("symbol", ";"));

    return varDecNode;
}


/**
 * Generates a parse tree for a method, function, or constructor
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileSubroutine() {
    // Structure: ('constructor' | 'function' | 'method') ('void' | type) subroutineName '(' parameterList ')' subroutineBody
    ParseTree* subroutineNode = new ParseTree("subroutine");

    subroutineNode->addChild(mustBe("keyword")); // 'constructor' | 'function' | 'method'
    if (have("keyword", "void")) {
        subroutineNode->addChild(mustBe("keyword", "void")); // 'void'
    } else {
        subroutineNode->addChild(mustBe("keyword")); // type: 'int', 'char', 'boolean' or className
    }

    subroutineNode->addChild(mustBe("identifier")); // subroutineName
    subroutineNode->addChild(mustBe("symbol", "("));
    subroutineNode->addChild(compileParameterList()); // parameterList
    subroutineNode->addChild(mustBe("symbol", ")"));
    subroutineNode->addChild(compileSubroutineBody()); // subroutineBody

    return subroutineNode;
}


/**
 * Generates a parse tree for a subroutine's parameters
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileParameterList() {
    // Structure: ((type varName) (',' type varName)*)?
    ParseTree* paramListNode = new ParseTree("parameterList");

    if (!have("symbol", ")")) { // if not an empty list
        paramListNode->addChild(mustBe("keyword")); // type
        paramListNode->addChild(mustBe("identifier")); // varName

        while (have("symbol", ",")) {
            paramListNode->addChild(mustBe("symbol", ","));
            paramListNode->addChild(mustBe("keyword")); // type
            paramListNode->addChild(mustBe("identifier")); // varName
        }
    }

    return paramListNode;
}


/**
 * Generates a parse tree for a subroutine's body
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileSubroutineBody() {
    // Structure: '{' varDec* statements '}'
    ParseTree* bodyNode = new ParseTree("subroutineBody");

    bodyNode->addChild(mustBe("symbol", "{"));

    while (have("keyword", "var")) {
        bodyNode->addChild(compileVarDec()); // varDec
    }

    bodyNode->addChild(compileStatements()); // statements - this method should parse a series of statements

    bodyNode->addChild(mustBe("symbol", "}"));

    return bodyNode;
}


/**
 * Generates a parse tree for a subroutine variable declaration
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileVarDec() {
    // Structure: 'var' type varName (',' varName)* ';'
    ParseTree* varDecNode = new ParseTree("varDec");

    varDecNode->addChild(mustBe("keyword", "var")); // 'var'
    varDecNode->addChild(mustBe("keyword")); // type: 'int', 'char', 'boolean' or className
    varDecNode->addChild(mustBe("identifier")); // varName

    while (have("symbol", ",")) {
        varDecNode->addChild(mustBe("symbol", ","));
        varDecNode->addChild(mustBe("identifier")); // varName
    }

    varDecNode->addChild(mustBe("symbol", ";"));

    return varDecNode;
}


/**
 * Generates a parse tree for a series of statements
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileStatements() {
    // Structure: statement*
    ParseTree* statementsNode = new ParseTree("statements");

    // The following loop handles a series of statements. It checks for the first token of each possible statement and calls the respective method.
    while (true) {
        if (have("keyword", "let")) {
            statementsNode->addChild(compileLet());
        } else if (have("keyword", "if")) {
            statementsNode->addChild(compileIf());
        } else if (have("keyword", "while")) {
            statementsNode->addChild(compileWhile());
        } else if (have("keyword", "do")) {
            statementsNode->addChild(compileDo());
        } else if (have("keyword", "return")) {
            statementsNode->addChild(compileReturn());
        } else {
            break; // No recognizable statement start, exit the loop
        }
    }

    return statementsNode;
}


/**
 * Generates a parse tree for a let statement
 * @return a ParseTree
 */
// 'let' varName ('[' expression ']')? '=' expression ';'
ParseTree* CompilerParser::compileLet() {
    ParseTree* letNode = new ParseTree("letStatement");

    letNode->addChild(mustBe("keyword", "let"));
    letNode->addChild(mustBe("identifier")); // varName

    if (have("symbol", "[")) {
        letNode->addChild(mustBe("symbol", "["));
        letNode->addChild(compileExpression()); // expression
        letNode->addChild(mustBe("symbol", "]"));
    }

    letNode->addChild(mustBe("symbol", "="));
    letNode->addChild(compileExpression()); // expression
    letNode->addChild(mustBe("symbol", ";"));

    return letNode;
}

/**
 * Generates a parse tree for an if statement
 * @return a ParseTree
 */
// 'if' '(' expression ')' '{' statements '}' ('else' '{' statements '}')?
ParseTree* CompilerParser::compileIf() {
    ParseTree* ifNode = new ParseTree("ifStatement");

    ifNode->addChild(mustBe("keyword", "if"));
    ifNode->addChild(mustBe("symbol", "("));
    ifNode->addChild(compileExpression()); // expression
    ifNode->addChild(mustBe("symbol", ")"));
    ifNode->addChild(mustBe("symbol", "{"));
    ifNode->addChild(compileStatements()); // statements
    ifNode->addChild(mustBe("symbol", "}"));

    if (have("keyword", "else")) {
        ifNode->addChild(mustBe("keyword", "else"));
        ifNode->addChild(mustBe("symbol", "{"));
        ifNode->addChild(compileStatements()); // statements
        ifNode->addChild(mustBe("symbol", "}"));
    }

    return ifNode;
}

/**
 * Generates a parse tree for a while statement
 * @return a ParseTree
 */
// 'while' '(' expression ')' '{' statements '}'
ParseTree* CompilerParser::compileWhile() {
    ParseTree* whileNode = new ParseTree("whileStatement");

    whileNode->addChild(mustBe("keyword", "while"));
    whileNode->addChild(mustBe("symbol", "("));
    whileNode->addChild(compileExpression()); // expression
    whileNode->addChild(mustBe("symbol", ")"));
    whileNode->addChild(mustBe("symbol", "{"));
    whileNode->addChild(compileStatements()); // statements
    whileNode->addChild(mustBe("symbol", "}"));

    return whileNode;
}

/**
 * Generates a parse tree for a do statement
 * @return a ParseTree
 */
// 'do' subroutineCall ';'
ParseTree* CompilerParser::compileDo() {
    ParseTree* doNode = new ParseTree("doStatement");

    doNode->addChild(mustBe("keyword", "do"));
    doNode->addChild(compileExpression()); // Assuming subroutineCall is part of compileExpression
    doNode->addChild(mustBe("symbol", ";"));

    return doNode;
}


/**
 * Generates a parse tree for a return statement
 * @return a ParseTree
 */
// 'return' expression? ';'
ParseTree* CompilerParser::compileReturn() {
    ParseTree* returnNode = new ParseTree("returnStatement");

    returnNode->addChild(mustBe("keyword", "return"));

    if (!have("symbol", ";")) { // Check if there's an expression
        returnNode->addChild(compileExpression()); // expression
    }

    returnNode->addChild(mustBe("symbol", ";"));

    return returnNode;
}

/**
 * Generates a parse tree for an expression
 * @return a ParseTree
 */
// Assuming an expression is a combination of terms and operators
ParseTree* CompilerParser::compileExpression() {
    // expression: term (op term)*
    ParseTree* expressionNode = new ParseTree("expression");

    // Here, we'll need a way to check if the current token is the start of a term
    if (isStartOfTerm()) { // You need to define isStartOfTerm() to check the token against possible starts of terms (integerConstant, stringConstant, keyword, identifier, symbol '(' or unaryOp)
        expressionNode->addChild(compileTerm());
    } else {
        // Handle unexpected token/start of term
        handleError("Expected start of term, found unexpected token.");
    }

    // Check for operation symbols, assuming isOp() checks if the current token is an operator
    while (isOp()) { // You need to define isOp() to check if the token is an operator
        expressionNode->addChild(mustBe("symbol")); // Assuming all operators are symbols, adds the operator
        expressionNode->addChild(compileTerm());
    }

    return expressionNode;
}`

/**
 * Generates a parse tree for an expression term
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileTerm() {
    // term: integerConstant | stringConstant | keywordConstant | varName | varName '[' expression ']' | subroutineCall | '(' expression ')' | unaryOp term
    ParseTree* termNode = new ParseTree("term");

    if (have("integerConstant")) {
        termNode->addChild(mustBe("integerConstant"));
    } else if (have("stringConstant")) {
        termNode->addChild(mustBe("stringConstant"));
    } else if (have("keyword")) { // true, false, null, this
        termNode->addChild(mustBe("keyword"));
    } else if (have("identifier")) {
        termNode->addChild(mustBe("identifier")); // varName or subroutineCall
        // Further checks can be performed here to distinguish between a varName, a varName with an array index, and a subroutineCall
    } else if (have("symbol", "(")) {
        termNode->addChild(mustBe("symbol", "("));
        termNode->addChild(compileExpression());
        termNode->addChild(mustBe("symbol", ")"));
    } else if (isUnaryOp()) { // You need to define isUnaryOp() to check if the token is a unary operator
        termNode->addChild(mustBe("symbol")); // unaryOp
        termNode->addChild(compileTerm());
    } else {
        // Handle unexpected token
        handleError("Expected term, found unexpected token.");
    }

    return termNode;
}


/**
 * Generates a parse tree for an expression list
 * @return a ParseTree
 */
// (expression (',' expression)* )?
ParseTree* CompilerParser::compileExpressionList() {
    ParseTree* expressionListNode = new ParseTree("expressionList");

    if (!have("symbol", ")")) { // Check if not empty list
        expressionListNode->addChild(compileExpression());

        while (have("symbol", ",")) {
            expressionListNode->addChild(mustBe("symbol", ","));
            expressionListNode->addChild(compileExpression());
        }
    }

    return expressionListNode;
}


/**
 * Advance to the next token
 */
void CompilerParser::next() {
    if (currentToken != tokens.end())
        ++currentToken;
}
/**
 * Return the current token
 * @return the Token
 */
Token* CompilerParser::current() {
    if (currentToken != tokens.end())
        return *currentToken; // Return current token if it's valid
    else
        return NULL; // Or null if we've reached the end
}

/**
 * Check if the current token matches the expected type and value.
 * @return true if a match, false otherwise
 */
bool CompilerParser::have(std::string expectedType, std::string expectedValue) {
    if (currentToken != tokens.end()) {
        Token* t = *currentToken;
        // Assuming 'type' and 'value' are members of Token, adjust as necessary
        // If expectedValue is empty, check type only
        return (t->type == expectedType && (expectedValue.empty() || t->value == expectedValue));
    }
    return false; // If we've reached the end or the condition is not met
}

/**
 * Check if the current token matches the expected type and value.
 * If so, advance to the next token, returning the current token, otherwise throw a ParseException.
 * @return the current token before advancing
 */
Token* CompilerParser::mustBe(std::string expectedType, std::string expectedValue) {
    if (have(expectedType, expectedValue)) {
        Token* t = *currentToken;
        next(); // Advance to the next token for subsequent operations
        return t; // Return the token that was validated and matched
    } else {
        // If the token doesn't match, we throw a parse exception. This signals that the 
        // source code doesn't match the expected syntax.
        throw ParseException();
    }
}

bool CompilerParser::isOp(Token* token) {
    if (!token) return false; // null pointer guard

    // Assuming Token has a method getType() that returns a string representation of the token type,
    // and a method getValue() that returns the token's actual value.
    return token->getType() == "symbol" && (
           token->getValue() == "+" ||
           token->getValue() == "-" ||
           token->getValue() == "*" ||
           token->getValue() == "/" ||
           // add other operators as per your language's specifications
           token->getValue() == "&" ||
           token->getValue() == "|" ||
           token->getValue() == "<" ||
           token->getValue() == ">" ||
           token->getValue() == "=");
}

bool CompilerParser::isUnaryOp(Token* token) {
    if (!token) return false; // null pointer guard

    return token->getType() == "symbol" && (
           token->getValue() == "-" ||
           token->getValue() == "~");
    // add other unary operators as per your language's specifications
}

bool CompilerParser::isStartOfTerm(Token* token) {
    if (!token) return false; // null pointer guard

    // this is highly dependent on your language's grammar
    // but generally, numbers, identifiers, certain symbols like '(', etc., can start a term
    return token->getType() == "integerConstant" ||
           token->getType() == "stringConstant" ||
           token->getType() == "identifier" ||
           (token->getType() == "symbol" && (
               token->getValue() == "(" ||
               token->getValue() == "~" ||
               token->getValue() == "-"));
    // add other valid start symbols as per your language's specifications
}


/**
 * Definition of a ParseException
 * You can use this ParseException with `throw ParseException();`
 */
const char* ParseException::what() const noexcept {
    return "Parse exception: Unexpected token encountered.";
}
