/**
 * @author JD Ojeda
 * @brief Program to evaluate Boolean algebra expressions using Abstract Syntax Tree.
 */

#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <unordered_map>
#include <set>

/**
 * @struct Token
 * @brief Represents a token in the input Boolean expression.
 */
struct Token {
    std::string type; // type of the token
    std::string value; // boolean expressions such as AND, OR, etc.
};

/**
 * @struct ASTNode
 * @brief Represents a node in the Abstract Syntax Tree (AST).
 */
struct ASTNode {
    std::string value; // operator or variable name -> "AND", etc.
    ASTNode* left; // pointer for left child
    ASTNode* right; // pointer for right child

    ASTNode(std::string val) : value(val), left(nullptr), right(nullptr) {}
};

/**
 * @brief Tokenizes a Boolean expression into tokens.
 * @param input The input Boolean expression as a string.
 * @return A vector of Token objects.
 */
std::vector<Token> tokenize(const std::string& input) {
    std::vector<Token> tokens; // stores the tokens taken from the input
    std::string current; // hold the current token thats being built

    for (size_t i = 0; i < input.length(); i++) {
        char c = input[i];
        if (std::isspace(c)) { // skip spaces
            continue;
        } else if (std::isalpha(c)) { // build the variables/operators -> "AND", etc.
            current += c;
            if (current == "AND" || current == "OR" || current == "NOT") {
                tokens.push_back({ "OPERATOR", current });
                current.clear();
            }
        } else { // handle the parentheses and single char tokens
            if (!current.empty()) { // push var token before special characters
                tokens.push_back({ "VARIABLE", current });
                current.clear();
            }
            if (c == '(' || c == ')') {
                tokens.push_back({ "PAREN", std::string(1, c) });
            }
        }
    }
    if (!current.empty()) { // add the last token if any
        tokens.push_back({ "VARIABLE", current });
    }
    return tokens;
}

/**
 * @brief Parses tokens into an Abstract Syntax Tree (AST).
 * @param tokens The vector of tokens to parse.
 * @param idx The current index in the token vector.
 * @return A pointer to the root of the AST.
 */
ASTNode* parseExpression(std::vector<Token>& tokens, size_t& idx) {
    if (tokens[idx].type == "VARIABLE" || tokens[idx].type == "CONSTANT") {
        return new ASTNode(tokens[idx++].value); // created leaf node before moving to next token
    }
    if (tokens[idx].value == "NOT") {
        ASTNode* node = new ASTNode("NOT");
        idx++;
        node->left = parseExpression(tokens, idx); // parse the operand
        return node;
    }
    if (tokens[idx].value == "(") {
        idx++; // skip the '('
        ASTNode* node = parseExpression(tokens, idx); // parse the sub-expressions
        if (idx >= tokens.size() || tokens[idx].value != ")") {
            std::cerr << "Error: Unmatched parenthesis." << std::endl;
            exit(10);
        }
        idx++; // skip the ')'
        return node;
    }
    return nullptr;
}

/**
 * @brief Evaluates a Boolean expression represented by an AST.
 * @param node The root of the AST.
 * @param variableValues A map of variable names to their Boolean values.
 * @return The result of the evaluation (true/false).
 */
bool evaluateAST(ASTNode* node, const std::unordered_map<std::string, bool>& variableValues) {
    if (node->value == "TRUE") return true;
    if (node->value == "FALSE") return false;
    if (node->value == "NOT") return !evaluateAST(node->left, variableValues);
    if (node->value == "AND") return evaluateAST(node->left, variableValues) && evaluateAST(node->right, variableValues);
    if (node->value == "OR") return evaluateAST(node->left, variableValues) || evaluateAST(node->right, variableValues);
    return variableValues.at(node->value); // lookup var value
}

/**
 * @brief Deletes an AST and frees its memory.
 * @param node The root of the AST to delete.
 */
void deleteAST(ASTNode* node) {
    if (!node) return;
    deleteAST(node->left);
    deleteAST(node->right);
    delete node;
}


/**
 * @brief The main function of the program.
 *        Prompts the user for input, tokenizes the expression,
 *        parses it into an AST, evaluates it, and outputs the result.
 * @return int Exit status of the program.
 */
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
        while (true) {
            std::cout << "Enter value for " << var << " (true/false or 1/0): ";
            std::cin >> value;
            if (value == "true" || value == "1") {
                variableValues[var] = true;
                break;
            } else if (value == "false" || value == "0") {
                variableValues[var] = false;
                break;
            } else {
                std::cerr << "Invalid input. Please enter true/false or 1/0." << std::endl;
            }
        }
    }

    // parse the token into an AST
    size_t idx = 0;
    ASTNode* ast = parseExpression(tokens, idx);

    // evaluate the AST
    bool result = evaluateAST(ast, variableValues);

    // output the result back to the client
    std::cout << "The result of the expression is: " << (result ? "TRUE" : "FALSE") << std::endl;

    // free the dynamically allocated AST memory
    deleteAST(ast);

    return 0;
}
