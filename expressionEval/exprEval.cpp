#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <unordered_map>
#include <set>

struct Token {
    std::string type; // type of the token
    std::string value; // boolean expressions such as AND, OR, etc.
};

struct ASTNode {
    std::string value; // operator or variable name
    ASTNode* left; // left child
    ASTNode* right; // right child

    ASTNode(std::string val) : value(val), left(nullptr), right(nullptr) {}
};

// function to tokenize the input
std::vector<Token> tokenize(const std::string& input) {
    std::vector<Token> tokens; // stores the tokens taken from the input
    std::string current; // hold the current token thats being built

    for (char c : input) {
        if (std::isspace(c)) {
            continue;
        } else if (std::isalpha(c)) {
            current += c;
        } else {
            if (!current.empty()) {
                tokens.push_back({ "VARIABLE", current });
                current.clear();
            }
            if (c == '(' || c == ')') {
                tokens.push_back({ "PAREN", std::string(1, c) });
            }
        }
    }
    if (!current.empty()) {
        tokens.push_back({ "VARIABLE", current });
    }
    return tokens;
}

// function to parse tokens into an AST
ASTNode* parseExpression(std::vector<Token>& tokens, size_t& idx) {
    if (tokens[idx].type == "VARIABLE" || tokens[idx].type == "CONSTANT") {
        return new ASTNode(tokens[idx++].value);
    }
    if (tokens[idx].value == "NOT") {
        ASTNode* node = new ASTNode("NOT");
        idx++;
        node->left = parseExpression(tokens, idx);
        return node;
    }
    if (tokens[idx].value == "(") {
        idx++;
        ASTNode* node = parseExpression(tokens, idx);
        idx++;
        return node;
    }
    return nullptr;
}

// function to evaluate the AST
bool evaluateAST(ASTNode* node, const std::unordered_map<std::string, bool>& variableValues) {
    if (node->value == "TRUE") return true;
    if (node->value == "FALSE") return false;
    if (node->value == "NOT") return !evaluateAST(node->left, variableValues);
    if (node->value == "AND") return evaluateAST(node->left, variableValues) && evaluateAST(node->right, variableValues);
    if (node->value == "OR") return evaluateAST(node->left, variableValues) || evaluateAST(node->right, variableValues);
    return variableValues.at(node->value);
}

int main() 
{
    std::string expression;
    std::cout << "Enter a Boolean expression: ";
    std::getline(std::cin, expression);

    //tokenize the input
    std::vector<Token> tokens = tokenize(expression);

    // get the input variable names
    std::set<std::string> variables;
    for (const auto& token : tokens) {
        if (token.type == "VARIABLE") {
            variables.insert(token.value);
        }
    }

    // get truth values for ea. variable from the user
    std::unordered_map<std::string, bool> variableValues;
    for (const auto& var : variables) {
        std::string value;
        std::cout << "Enter value for " << var << " (true/false or 1/0): ";
        std::cin >> value;
        if (value == "true" || value == "1") {
            variableValues[var] = true;
        } else if (value == "false" || value == "0") {
            variableValues[var] = false;
        } else {
            std::cerr << "Error: Defaulting " << var << " to false." << std::endl;
            variableValues[var] = false;
        }
    }
    // parse the token into an AST
    size_t idx = 0;
    ASTNode* ast = parseExpression(tokens, idx);

    // evaluate the AST
    bool result = evaluateAST(ast, variableValues);

    // output the result back to the client
    std::cout << "The result of the expression is: " << (result ? "TRUE" : "FALSE") << std::endl;

    return 0;
}