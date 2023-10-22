#include "CompilerParser.h"


/**
 * Constructor for the CompilerParser
 * @param tokens A linked list of tokens to be parsed
 */
CompilerParser::CompilerParser(std::list<Token*> tokens) {
    this->tokens = tokens;
    this->currentToken = this->tokens.begin();
}

/**
 * Generates a parse tree for a single program
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileProgram() {
    if (have("keyword", "class")) {
        return compileClass();
    }
    throw ParseException();  // If the program doesn't start with a class keyword, throw a ParseException.
}


/**
 * Generates a parse tree for a single class
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileClass() {
    // Create a new ParseTree for the class structure
    ParseTree* classNode = new ParseTree("class", "");

    // Expect the 'class' keyword token and add it to the class node
    classNode->addChild(mustBe("keyword", "class"));

    // Expect an identifier token (class name) and add it to the class node
    classNode->addChild(mustBe("identifier", ""));

    // Expect the '{' symbol token and add it to the class node
    classNode->addChild(mustBe("symbol", "{"));

    // Process class variable declarations and subroutines until we hit the '}' symbol
    while (!have("symbol", "}")) {
        if (have("keyword", "static") || have("keyword", "field")) {
            // If we encounter a class variable declaration, compile it and add to the class node
            classNode->addChild(compileClassVarDec());
        } else if (have("keyword", "constructor") || have("keyword", "function") || have("keyword", "method")) {
            // If we encounter a subroutine declaration, compile it and add to the class node
            classNode->addChild(compileSubroutine());
        } else {
            // Error handling for unexpected tokens
            throw ParseException();
        }
    }

    // Finally, expect the '}' symbol token and add it to the class node
    classNode->addChild(mustBe("symbol", "}"));

    return classNode;
}

/**
 * Generates a parse tree for a static variable declaration or field declaration
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileClassVarDec() {
    ParseTree* varDecNode = new ParseTree("classVarDec", "");

    varDecNode->addChild(mustBe("keyword", ""));  // expects "static" or "field"
    varDecNode->addChild(mustBe("keyword", ""));  // expects type ("int", "char", "boolean", or className)
    varDecNode->addChild(mustBe("identifier", ""));  // variable name

    while (have("symbol", ",")) {
        varDecNode->addChild(mustBe("symbol", ","));
        varDecNode->addChild(mustBe("identifier", ""));
    }

    varDecNode->addChild(mustBe("symbol", ";"));

    return varDecNode;
}

/**
 * Generates a parse tree for a method, function, or constructor
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileSubroutine() {
    ParseTree* subroutineNode = new ParseTree("subroutine", "");

    subroutineNode->addChild(mustBe("keyword", ""));  // expects "constructor", "function", or "method"
    subroutineNode->addChild(mustBe("keyword", ""));  // expects "void" or type
    subroutineNode->addChild(mustBe("identifier", ""));  // subroutine name

    subroutineNode->addChild(mustBe("symbol", "("));
    subroutineNode->addChild(compileParameterList());
    subroutineNode->addChild(mustBe("symbol", ")"));

    subroutineNode->addChild(compileSubroutineBody());

    return subroutineNode;
}

/**
 * Generates a parse tree for a subroutine's parameters
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileParameterList() {
    ParseTree* paramListNode = new ParseTree("parameterList", "");

    while (!have("symbol", ")")) {
        paramListNode->addChild(mustBe("keyword", ""));  // expects type
        paramListNode->addChild(mustBe("identifier", ""));  // variable name

        if (have("symbol", ",")) {
            paramListNode->addChild(mustBe("symbol", ","));
        }
    }

    return paramListNode;
}

/**
 * Generates a parse tree for a subroutine's body
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileSubroutineBody() {
    ParseTree* bodyNode = new ParseTree("subroutineBody", "");

    bodyNode->addChild(mustBe("symbol", "{"));

    while (have("keyword", "var")) {
        bodyNode->addChild(compileVarDec());
    }

    bodyNode->addChild(compileStatements());
    bodyNode->addChild(mustBe("symbol", "}"));

    return bodyNode;
}

/**
 * Generates a parse tree for a subroutine variable declaration
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileVarDec() {
    ParseTree* varNode = new ParseTree("varDec", "");

    varNode->addChild(mustBe("keyword", "var"));
    varNode->addChild(mustBe("keyword", ""));  // expects type
    varNode->addChild(mustBe("identifier", ""));  // variable name

    while (have("symbol", ",")) {
        varNode->addChild(mustBe("symbol", ","));
        varNode->addChild(mustBe("identifier", ""));
    }

    varNode->addChild(mustBe("symbol", ";"));

    return varNode;
}

/**
 * Generates a parse tree for a series of statements
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileStatements() {
    ParseTree* statementsNode = new ParseTree("statements", "");

    while (!have("symbol", "}")) { 
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
            throw ParseException();
        }
    }
    return statementsNode;
}

/**
 * Generates a parse tree for a let statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileLet() {
    ParseTree* letNode = new ParseTree("letStatement", "");

    letNode->addChild(mustBe("keyword", "let"));
    letNode->addChild(mustBe("identifier", ""));
    letNode->addChild(mustBe("symbol", "="));
    letNode->addChild(compileExpression());
    letNode->addChild(mustBe("symbol", ";"));

    return letNode;
}

/**
 * Generates a parse tree for an if statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileIf() {
    ParseTree* ifNode = new ParseTree("ifStatement", "");

    ifNode->addChild(mustBe("keyword", "if"));
    ifNode->addChild(mustBe("symbol", "("));
    ifNode->addChild(compileExpression());
    ifNode->addChild(mustBe("symbol", ")"));
    ifNode->addChild(mustBe("symbol", "{"));
    ifNode->addChild(compileStatements());
    ifNode->addChild(mustBe("symbol", "}"));

    if (have("keyword", "else")) {
        ifNode->addChild(mustBe("keyword", "else"));
        ifNode->addChild(mustBe("symbol", "{"));
        ifNode->addChild(compileStatements());
        ifNode->addChild(mustBe("symbol", "}"));
    }

    return ifNode;
}


/**
 * Generates a parse tree for a while statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileWhile() {
    ParseTree* whileNode = new ParseTree("whileStatement", "");


    whileNode->addChild(mustBe("keyword", "while"));
    whileNode->addChild(mustBe("symbol", "("));
    whileNode->addChild(compileExpression());
    whileNode->addChild(mustBe("symbol", ")"));
    whileNode->addChild(mustBe("symbol", "{"));
    whileNode->addChild(compileStatements());
    whileNode->addChild(mustBe("symbol", "}"));

    return whileNode;
}

/**
 * Generates a parse tree for a do statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileDo() {
    ParseTree* doNode = new ParseTree("doStatement", "");

    // Expect the 'do' keyword token and add it to the do node
    doNode->addChild(mustBe("keyword", "do"));

    // Here, a subroutine call is expected; depending on your implementation, 
    // you might have a `compileSubroutineCall` method or something similar.
    // doNode->addChild(compileSubroutineCall());

    // Expect the ';' symbol token and add it to the do node
    doNode->addChild(mustBe("symbol", ";"));

    return doNode;
}

/**
 * Generates a parse tree for a return statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileReturn() {
    ParseTree* returnNode = new ParseTree("returnStatement", "");

    // Expect the 'return' keyword token and add it to the return node
    returnNode->addChild(mustBe("keyword", "return"));

    // If there's an expression before the ';', compile it
    if (!have("symbol", ";")) {
        returnNode->addChild(compileExpression());
    }

    // Expect the ';' symbol token and add it to the return node
    returnNode->addChild(mustBe("symbol", ";"));

    return returnNode;
}

/**
 * Generates a parse tree for an expression
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileExpression() {
    // Create a new ParseTree node for the expression
    ParseTree* expressionNode = new ParseTree("expression", "");

    // Compile the first term of the expression
    expressionNode->addChild(compileTerm());

    // As long as the current token is an operator (e.g., +, -, etc.), keep processing terms
    while (isOperator(current())) {
        // Use the mustBe function to ensure the current token is an operator and add it to the expression node
        expressionNode->addChild(mustBe("symbol", current()->getValue()));

        // Compile the next term of the expression
        expressionNode->addChild(compileTerm());
    }

    return expressionNode;
}

bool CompilerParser::isOperator(Token* token) {
    if (token == nullptr) {
        return false;
    }
    std::string value = token->getValue();
    return (value == "+" || value == "-" || value == "*" || value == "/" || value == "&" || value == "|" || value == "<" || value == ">" || value == "=");
}

/**
 * Generates a parse tree for an expression term
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileTerm() {
    ParseTree* termNode = new ParseTree("term", "");

    if (have("integerConstant", "")) {
        termNode->addChild(mustBe("integerConstant", ""));
    } else if (have("symbol", "(")) {
        termNode->addChild(mustBe("symbol", "("));
        termNode->addChild(compileExpression());
        termNode->addChild(mustBe("symbol", ")"));
    } else if (have("identifier", "")) {
        termNode->addChild(mustBe("identifier", ""));
        if (have("symbol", "-") || isOperator(current())) {
            termNode->addChild(mustBe("symbol", current()->getValue()));
            termNode->addChild(compileTerm());
        }
    } else {
        throw ParseException();
    }

    return termNode;
}

/**
 * Generates a parse tree for an expression list
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileExpressionList() {
    ParseTree* expressionListNode = new ParseTree("expressionList", "");

    if (!have("symbol", ")")) {
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
    if (currentToken != tokens.end()) {
        ++currentToken;
    }
}

/**
 * Return the current token
 * @return the Token
 */
Token* CompilerParser::current() {
    if (currentToken != tokens.end()) {
        return *currentToken;
    }
    return nullptr;
}

/**
 * Check if the current token matches the expected type and value.
 * @return true if a match, false otherwise
 */
bool CompilerParser::have(std::string expectedType, std::string expectedValue = ""){
    if (currentToken != tokens.end()) {
        if (expectedValue == "") {
            return ((*currentToken)->getType() == expectedType);
        }
        return ((*currentToken)->getType() == expectedType && (*currentToken)->getValue() == expectedValue);
    }
    return false;
}


/**
 * Check if the current token matches the expected type and value.
 * If so, advance to the next token, returning the current token, otherwise throw a ParseException.
 * @return the current token before advancing
 */
Token* CompilerParser::mustBe(std::string expectedType, std::string expectedValue = ""){
    if (have(expectedType, expectedValue)) {
        Token* current = *currentToken;
        next();
        return current;
    }
    throw ParseException();
}


/**
 * Definition of a ParseException
 * You can use this ParseException with `throw ParseException();`
 */
const char* ParseException::what() {
    return "An Exception occurred while parsing!";
}
