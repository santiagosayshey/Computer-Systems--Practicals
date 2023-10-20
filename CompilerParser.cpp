#include "CompilerParser.h"
#include <stdexcept>
#include <set>

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
    ParseTree* program = new ParseTree("program", "");

    // Loop through all tokens and process all classes
    while (!this->tokens.empty() && have("keyword", "class")) {
        program->addChild(compileClass());

        // Ensure there are tokens left after parsing a class
        if (this->currentToken == this->tokens.end()) {
            break;
        }
    }

    // Check if the program is empty (i.e., contains no classes) and handle it as an error
    if (program->getChildren().empty()) {
        // Error handling: Your language might expect at least one class per program
        throw ParseException();
    }
    
    return program;
}


/**
 * Generates a parse tree for a single class
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileClass() {
    // Ensure the current token is 'class'
    if (!have("keyword", "class")) {
        throw ParseException();
    }

    ParseTree* classTree = new ParseTree("class", "");
    
    // Add 'class' keyword to the tree
    classTree->addChild(new ParseTree("keyword", mustBe("keyword", "class")->getValue()));

    // Add class name to the tree
    classTree->addChild(new ParseTree("identifier", mustBe("identifier", "")->getValue()));

    // Add '{' symbol to the tree
    classTree->addChild(new ParseTree("symbol", mustBe("symbol", "{")->getValue()));

    // Process class variable declarations
    while (have("keyword", "static") || have("keyword", "field")) {
        classTree->addChild(compileClassVarDec());
    }

    // Process subroutine declarations
    while (have("keyword", "constructor") || have("keyword", "function") || have("keyword", "method")) {
        classTree->addChild(compileSubroutine());
    }

    // Add '}' symbol to the tree
    classTree->addChild(new ParseTree("symbol", mustBe("symbol", "}")->getValue()));

    return classTree;
}


/**
 * Generates a parse tree for a static variable declaration or field declaration
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileClassVarDec() {
    // Ensure the current token is 'static' or 'field'
    if (!have("keyword", "static") && !have("keyword", "field")) {
        throw ParseException();
    }

    ParseTree* varDecTree = new ParseTree("classVarDec", "");

    // Add 'static' or 'field' keyword to the tree
    varDecTree->addChild(new ParseTree("keyword", mustBe("keyword", current()->getValue())->getValue()));

    // Add type (which could be a primitive type keyword or an identifier for custom types)
    if (have("keyword", current()->getValue())) { // assuming primitive type keywords are also categorized under "keyword"
        varDecTree->addChild(new ParseTree("keyword", mustBe("keyword", current()->getValue())->getValue()));
    } else {
        varDecTree->addChild(new ParseTree("identifier", mustBe("identifier", "")->getValue()));
    }

    // Add variable name identifier
    varDecTree->addChild(new ParseTree("identifier", mustBe("identifier", "")->getValue()));

    // Check for and add any additional var names in this declaration
    while (have("symbol", ",")) {
        varDecTree->addChild(new ParseTree("symbol", mustBe("symbol", ",")->getValue()));
        varDecTree->addChild(new ParseTree("identifier", mustBe("identifier", "")->getValue()));
    }

    // Expect and add semicolon symbol
    varDecTree->addChild(new ParseTree("symbol", mustBe("symbol", ";")->getValue()));

    return varDecTree;
}

/**
 * Generates a parse tree for a method, function, or constructor
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileSubroutine() {
    // Ensure the current token is 'constructor', 'function', or 'method'
    if (!have("keyword", "constructor") && !have("keyword", "function") && !have("keyword", "method")) {
        throw ParseException();
    }

    ParseTree* subroutineTree = new ParseTree("subroutineDec", "");

    // Add 'constructor', 'function', or 'method' keyword to the tree
    subroutineTree->addChild(new ParseTree("keyword", mustBe("keyword", current()->getValue())->getValue()));

    // Add 'void' or return type (which could be a primitive type keyword or an identifier for custom types)
    if (have("keyword", "void")) {
        subroutineTree->addChild(new ParseTree("keyword", mustBe("keyword", "void")->getValue()));
    } else if (have("keyword", current()->getValue())) { // assuming primitive type keywords are also categorized under "keyword"
        subroutineTree->addChild(new ParseTree("keyword", mustBe("keyword", current()->getValue())->getValue()));
    } else {
        subroutineTree->addChild(new ParseTree("identifier", mustBe("identifier", "")->getValue()));
    }

    // Add subroutine name identifier
    subroutineTree->addChild(new ParseTree("identifier", mustBe("identifier", "")->getValue()));

    // Expect and add '(' symbol
    subroutineTree->addChild(new ParseTree("symbol", mustBe("symbol", "(")->getValue()));

    // Add parameter list
    subroutineTree->addChild(compileParameterList());

    // Expect and add ')' symbol
    subroutineTree->addChild(new ParseTree("symbol", mustBe("symbol", ")")->getValue()));

    // Add subroutine body
    subroutineTree->addChild(compileSubroutineBody());

    return subroutineTree;
}


/**
 * Generates a parse tree for a subroutine's parameters
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileParameterList() {
    ParseTree* parameterListTree = new ParseTree("parameterList", "");

    // If the first token is not ")", then we have parameters to parse.
    while (!have("symbol", ")")) {
        // Add type (which could be a primitive type keyword or an identifier for custom types)
        if (have("keyword", current()->getValue())) { // assuming primitive type keywords are also categorized under "keyword"
            parameterListTree->addChild(new ParseTree("keyword", mustBe("keyword", current()->getValue())->getValue()));
        } else {
            parameterListTree->addChild(new ParseTree("identifier", mustBe("identifier", "")->getValue()));
        }

        // Add variable name identifier
        parameterListTree->addChild(new ParseTree("identifier", mustBe("identifier", "")->getValue()));

        // If the next token is a comma, it means there are more parameters.
        if (have("symbol", ",")) {
            parameterListTree->addChild(new ParseTree("symbol", mustBe("symbol", ",")->getValue()));
        } else if (!have("symbol", ")")) {
            // If the token is not a comma or ")", the parameter list is malformed.
            throw ParseException();
        }
    }

    return parameterListTree;
}

ParseTree* CompilerParser::compileSubroutineCall() {
    ParseTree* callTree = new ParseTree("subroutineCall", "");

    // Add subroutine name identifier
    callTree->addChild(new ParseTree("identifier", mustBe("identifier", current()->getValue())->getValue()));

    // Handle subroutine calls with class or object name (for methods)
    if (have("symbol", ".")) {
        callTree->addChild(new ParseTree("symbol", mustBe("symbol", ".")->getValue()));
        callTree->addChild(new ParseTree("identifier", mustBe("identifier", current()->getValue())->getValue()));
    }

    // Expect '(' symbol for the start of the arguments list
    callTree->addChild(new ParseTree("symbol", mustBe("symbol", "(")->getValue()));

    // Add arguments list (which is a series of expressions)
    callTree->addChild(compileExpressionList());

    // Expect ')' symbol for the end of the arguments list
    callTree->addChild(new ParseTree("symbol", mustBe("symbol", ")")->getValue()));

    return callTree;
}

/**
 * Generates a parse tree for a subroutine's body
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileSubroutineBody() {
    ParseTree* bodyTree = new ParseTree("subroutineBody", "");

    // The subroutine body should start with a "{" symbol.
    if (!have("symbol", "{")) {
        throw ParseException();
    }
    bodyTree->addChild(new ParseTree("symbol", mustBe("symbol", "{")->getValue()));

    // Variable declarations are optional and there can be more than one.
    while (have("keyword", "var")) {
        bodyTree->addChild(compileVarDec());
    }

    // Statements are also optional but can be in a sequence.
    bodyTree->addChild(compileStatements());

    // The subroutine body should end with a "}" symbol.
    if (!have("symbol", "}")) {
        throw ParseException();
    }
    bodyTree->addChild(new ParseTree("symbol", mustBe("symbol", "}")->getValue()));

    return bodyTree;
}


/**
 * Generates a parse tree for a subroutine variable declaration
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileVarDec() {
    ParseTree* varDecTree = new ParseTree("varDec", "");

    // Variable declarations should start with the 'var' keyword.
    varDecTree->addChild(new ParseTree("keyword", mustBe("keyword", "var")->getValue()));

    // Next, we expect a type.
    if (have("keyword", current()->getValue())) { // for primitive types
        varDecTree->addChild(new ParseTree("keyword", mustBe("keyword", current()->getValue())->getValue()));
    } else { // custom types
        varDecTree->addChild(new ParseTree("identifier", mustBe("identifier", "")->getValue()));
    }

    // Then we expect at least one variable name.
    do {
        varDecTree->addChild(new ParseTree("identifier", mustBe("identifier", "")->getValue()));

        // If there's a comma, we expect more variables.
        if (have("symbol", ",")) {
            varDecTree->addChild(new ParseTree("symbol", mustBe("symbol", ",")->getValue()));
        }
    } while (have("symbol", ","));

    // Finally, we expect a semicolon at the end of the declaration.
    varDecTree->addChild(new ParseTree("symbol", mustBe("symbol", ";")->getValue()));

    return varDecTree;
}

/**
 * Generates a parse tree for a series of statements
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileStatements() {
    ParseTree* statementsTree = new ParseTree("statements", "");

    // Statements can be a series of let, if, while, do, and return statements.
    // We loop until we don't recognize a statement start.
    while (true) {
        if (have("keyword", "let")) {
            statementsTree->addChild(compileLet());
        } else if (have("keyword", "if")) {
            statementsTree->addChild(compileIf());
        } else if (have("keyword", "while")) {
            statementsTree->addChild(compileWhile());
        } else if (have("keyword", "do")) {
            statementsTree->addChild(compileDo());
        } else if (have("keyword", "return")) {
            statementsTree->addChild(compileReturn());
        } else {
            break;
        }
    }

    return statementsTree;
}

/**
 * Generates a parse tree for a let statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileLet() {
    ParseTree* letTree = new ParseTree("letStatement", "");

    // A let statement should start with the 'let' keyword.
    letTree->addChild(new ParseTree("keyword", mustBe("keyword", "let")->getValue()));

    // Next, we expect an identifier for the variable name.
    letTree->addChild(new ParseTree("identifier", mustBe("identifier", "")->getValue()));

    // If there's a '[', this is an array entry assignment.
    if (have("symbol", "[")) {
        letTree->addChild(new ParseTree("symbol", mustBe("symbol", "[")->getValue()));
        letTree->addChild(compileExpression()); // The array index.
        letTree->addChild(new ParseTree("symbol", mustBe("symbol", "]")->getValue()));
    }

    // We expect the '=' symbol followed by an expression.
    letTree->addChild(new ParseTree("symbol", mustBe("symbol", "=")->getValue()));
    letTree->addChild(compileExpression());

    // Finally, the statement should end with a semicolon.
    letTree->addChild(new ParseTree("symbol", mustBe("symbol", ";")->getValue()));

    return letTree;
}

/**
 * Generates a parse tree for an if statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileIf() {
    ParseTree* ifTree = new ParseTree("ifStatement", "");

    // An if statement should start with the 'if' keyword.
    ifTree->addChild(new ParseTree("keyword", mustBe("keyword", "if")->getValue()));

    // Next, we expect a '(' followed by an expression and then a ')'.
    ifTree->addChild(new ParseTree("symbol", mustBe("symbol", "(")->getValue()));
    ifTree->addChild(compileExpression());
    ifTree->addChild(new ParseTree("symbol", mustBe("symbol", ")")->getValue()));

    // Then, we expect a '{', followed by statements, and then a '}'.
    ifTree->addChild(new ParseTree("symbol", mustBe("symbol", "{")->getValue()));
    ifTree->addChild(compileStatements());
    ifTree->addChild(new ParseTree("symbol", mustBe("symbol", "}")->getValue()));

    // If there's an 'else', we expect another '{', followed by statements, and then a '}'.
    if (have("keyword", "else")) {
        ifTree->addChild(new ParseTree("keyword", mustBe("keyword", "else")->getValue()));
        ifTree->addChild(new ParseTree("symbol", mustBe("symbol", "{")->getValue()));
        ifTree->addChild(compileStatements());
        ifTree->addChild(new ParseTree("symbol", mustBe("symbol", "}")->getValue()));
    }

    return ifTree;
}

/**
 * Generates a parse tree for a while statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileWhile() {
    ParseTree* whileTree = new ParseTree("whileStatement", "");

    // A while statement should start with the 'while' keyword.
    whileTree->addChild(new ParseTree("keyword", mustBe("keyword", "while")->getValue()));

    // Next, we expect a '(' followed by an expression and then a ')'.
    whileTree->addChild(new ParseTree("symbol", mustBe("symbol", "(")->getValue()));
    whileTree->addChild(compileExpression());
    whileTree->addChild(new ParseTree("symbol", mustBe("symbol", ")")->getValue()));

    // Then, we expect a '{', followed by statements, and then a '}'.
    whileTree->addChild(new ParseTree("symbol", mustBe("symbol", "{")->getValue()));
    whileTree->addChild(compileStatements());
    whileTree->addChild(new ParseTree("symbol", mustBe("symbol", "}")->getValue()));

    return whileTree;
}

/**
 * Generates a parse tree for a do statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileDo() {
    ParseTree* doTree = new ParseTree("doStatement", "");

    // A do statement should start with the 'do' keyword.
    doTree->addChild(new ParseTree("keyword", mustBe("keyword", "do")->getValue()));

    // This can be followed by a subroutine call which can have various forms.
    doTree->addChild(compileSubroutineCall()); // Assuming you have a method to compile subroutine calls.

    // The statement ends with a semicolon.
    doTree->addChild(new ParseTree("symbol", mustBe("symbol", ";")->getValue()));

    return doTree;
}

/**
 * Generates a parse tree for a return statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileReturn() {
    ParseTree* returnTree = new ParseTree("returnStatement", "");

    // A return statement should start with the 'return' keyword.
    returnTree->addChild(new ParseTree("keyword", mustBe("keyword", "return")->getValue()));

    // It can be followed by an expression, which is optional, before the ending semicolon.
    if (!have("symbol", ";")) {
        returnTree->addChild(compileExpression());
    }

    // The statement ends with a semicolon.
    returnTree->addChild(new ParseTree("symbol", mustBe("symbol", ";")->getValue()));

    return returnTree;
}

/**
 * Generates a parse tree for an expression
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileExpression() {
    ParseTree* expressionTree = new ParseTree("expression", "");

    // Add the first term.
    expressionTree->addChild(compileTerm());

    // As long as the next token is an operator, we add it and the term that follows.
    while (isOperator(current()->getValue())) { // Need to implement isOperator, see below.
        expressionTree->addChild(new ParseTree("operator", current()->getValue()));
        next(); // Move to the next token.
        expressionTree->addChild(compileTerm());
    }

    return expressionTree;
}

bool CompilerParser::isOperator(const std::string& value) {
    // Here, define all the operator strings that are valid in your language.
    const std::set<std::string> operators = {"+", "-", "*", "/", "&", "|", "<", ">", "=", "&lt;", "&gt;", "&amp;"};
    return operators.find(value) != operators.end();
}

/**
 * Generates a parse tree for an expression term
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileTerm() {
    ParseTree* termTree = new ParseTree("term", "");

    Token* currentToken = current(); // Get the current token.
    std::string type = currentToken->getType();
    std::string value = currentToken->getValue();

    if (type == "integerConstant" || type == "stringConstant" || type == "keywordConstant") {
        // For constants, we create a child with the token's type and value.
        termTree->addChild(new ParseTree(type, value));
        next(); // Move to the next token.
    } 
    else if (type == "identifier") {
        // This could be a variable name, an array entry, or a subroutine call.
        // We need to distinguish these cases.
        termTree->addChild(new ParseTree("identifier", value));
        next(); // Move to the next token.

        if (have("symbol", "[")) {
            // It's an array entry.
            termTree->addChild(new ParseTree("symbol", "["));
            next(); // Move past the '['.
            termTree->addChild(compileExpression()); // Compile the expression inside the brackets.
            termTree->addChild(new ParseTree("symbol", "]"));
            next(); // Move past the ']'.
        } 
        else if (have("symbol", "(") || have("symbol", ".")) {
            // It's a subroutine call, handle it accordingly.
            // We're assuming here that 'compileSubroutineCall' is a method you have that properly parses a subroutine call.
            termTree->addChild(compileSubroutineCall());
        }
        // If it's just a plain identifier (variable name), we've already handled it above by adding it to the tree.
    } 
    else if (have("symbol", "(")) {
        // It's an expression in parentheses.
        termTree->addChild(new ParseTree("symbol", "("));
        next(); // Move past the '('.
        termTree->addChild(compileExpression());
        termTree->addChild(new ParseTree("symbol", ")"));
        next(); // Move past the ')'.
    } 
    else if (type == "symbol" && (value == "-" || value == "~")) { // Replace with your language's unary operators
        // It's a unary operation.
        termTree->addChild(new ParseTree("unaryOperator", value));
        next(); // Move to the next token.
        termTree->addChild(compileTerm());
    } 
    else {
        // It's not a valid term.
        throw ParseException();
    }

    return termTree;
}


/**
 * Generates a parse tree for an expression list
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileExpressionList() {
    ParseTree* expressionListTree = new ParseTree("expressionList", "");

    // Check if there's an expression first, as an expression list can be empty.
    if (!have("symbol", ")")) {
        expressionListTree->addChild(compileExpression());

        // As long as there's a comma, we expect another expression.
        while (have("symbol", ",")) {
            expressionListTree->addChild(new ParseTree("symbol", mustBe("symbol", ",")->getValue()));
            expressionListTree->addChild(compileExpression());
        }
    }

    return expressionListTree;
}


/**
 * Advance to the next token
 */
void CompilerParser::next() {
    if (this->currentToken != this->tokens.end()) {
        ++this->currentToken;
    }
}

/**
 * Return the current token
 * @return the Token
 */
Token* CompilerParser::current() {
    if (this->currentToken != this->tokens.end()) {
        return *this->currentToken;
    } else {
        throw std::out_of_range("No more tokens");
    }
}

/**
 * Check if the current token matches the expected type and value.
 * @return true if a match, false otherwise
 */
bool CompilerParser::have(std::string expectedType, std::string expectedValue) {
    if (this->currentToken != this->tokens.end()) {
        Token* token = *this->currentToken;
        return (token->getType() == expectedType && token->getValue() == expectedValue);
    }
    return false;
}

/**
 * Check if the current token matches the expected type and value.
 * If so, advance to the next token, returning the current token, otherwise throw a ParseException.
 * @return the current token before advancing
 */
Token* CompilerParser::mustBe(std::string expectedType, std::string expectedValue) {
    if (!have(expectedType, expectedValue)) {
        throw ParseException();
    }
    Token* token = *this->currentToken;
    next();  // Advance to the next token before returning
    return token;
}

/**
 * Definition of a ParseException
 * You can use this ParseException with `throw ParseException();`
 */
const char* ParseException::what() {
    return "An Exception occurred while parsing!";
}
