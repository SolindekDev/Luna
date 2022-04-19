#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <vector>

#include <tokens.h>

typedef struct AstNode AstNode;

typedef enum AstNodeType {
    NODE_NUMBER,
    NODE_OPERATOR,
    NODE_BINARY_EXPRESSIONS
} AstNodeType;

struct binaryNodeExpressions {
    std::vector<AstNode> left;
    std::vector<AstNode> right;
};

typedef struct AstNode {
    AstNodeType type;
    Tokens::Token token;
    struct binaryNodeExpressions binary_node;
} AstNode;

typedef struct AstBody {
    std::vector<AstNode> children_nodes;
} AstBody;

class ParserAST {
public:
    std::vector<Tokens::Token> tokens;
    int token_index;
    AstBody body;
    Tokens::Token curr_token;
    bool math;
    int math_number;
    bool error;
    int math_index;

    void init(std::vector<Tokens::Token> &tokens);

    void parse_math();

    void load_nodes_numbers_side(bool side);
    
    void load_nodes_operators_side(bool side);
};

#endif //PARSER_H
