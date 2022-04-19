// ------------------------------------------------------------------------------------
//
//   Luna Programming Language Compiler
//   Copyright (C) 2022 SolindekDev
//
//   This program is free software: you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//   (at your option) any later version.
//
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
//
//   You should have received a copy of the GNU General Public License
//   along with this program.  If not, see <https://www.gnu.org/licenses/>.
//
// ------------------------------------------------------------------------------------

#include <iostream>
#include <vector>

#include <parser_.h>
#include <tokens.h>
#include <l_utils.h>
#include <error.h>

void ParserAST::load_nodes_numbers_side(bool side) {
    // Create a representation of number
    AstNode num_node;
    num_node.type = NODE_NUMBER; // Set the type to NODE_NUMBER that will meens that the node is a number
    num_node.token = this->curr_token; // Set current token to the node
    if (side == true) // Right side
        this->body.children_nodes[this->body.children_nodes.size()-1].binary_node.right.push_back(num_node);
    else // Left side
        this->body.children_nodes[this->body.children_nodes.size()-1].binary_node.left.push_back(num_node);
}

void ParserAST::load_nodes_operators_side(bool side) {
    // Create a representation of opreator
    AstNode op_node;
    op_node.type = NODE_OPERATOR; // Set the type to NODE_OPERATOR that will meens that the node is a operator
    op_node.token = this->curr_token; // Set current token to the node
    if (side == true) // Right side
        this->body.children_nodes[this->body.children_nodes.size()-1].binary_node.right.push_back(op_node);
    else // Left side
        this->body.children_nodes[this->body.children_nodes.size()-1].binary_node.left.push_back(op_node);
}

void ParserAST::parse_math() {
    // Push to children nodes a new node that will be representation of this arithmetic operation.
    AstNode node;
    node.type = NODE_BINARY_EXPRESSIONS;
    this->body.children_nodes.push_back(node);

    // std::cout << this->body.children_nodes[this->body.children_nodes.size()-1].binary_node.left.size() << std::endl;
    // Set this->math boolean to true
    this->math = true;
    this->math_number = false;
    this->math_index = 0;
    // Create side variable
    bool side = false; // false - left | true - right

    while (
        this->curr_token.type == Tokens::Types::Int ||
        this->curr_token.type == Tokens::Types::Float ||
        this->curr_token.type == Tokens::Types::Plus ||
        this->curr_token.type == Tokens::Types::Minus ||
        this->curr_token.type == Tokens::Types::Divide ||
        this->curr_token.type == Tokens::Types::Multiply
    ) {

        // Condition that need to see is the this->curr_token is a type Int of Float
        if (this->curr_token.type == Tokens::Types::Int || this->curr_token.type == Tokens::Types::Float) {
            if (this->math_number == true) { // Just a little error
                Error::quick_err(ARITHMETIC_ERROR, "expected before number an operator", this->curr_token.filename, this->curr_token.position.row, this->curr_token.position.col);
                this->error = true;
            } else { 
                // Set the math_number value to true
                this->math_number = true;  
                // Increment the math_index value
                this->math_index++;
                // Call function that will append to node an another node that will representation of the number
                this->load_nodes_numbers_side(side);
            }
        } else {
            if (this->math_number == false && this->math_index == 0) {
                Error::quick_err(ARITHMETIC_ERROR, "expected before operator an number", this->curr_token.filename, this->curr_token.position.row, this->curr_token.position.col);
                this->error = true;
            } else {
                this->math_number = false;
                this->math_index++;
                this->load_nodes_operators_side(side);
            }
        }

        // Increment the token_index and set new current token
        this->token_index++;
        this->curr_token = this->tokens[this->token_index];
    }
    
    // std::cout << this->body.children_nodes[this->body.children_nodes.size()-1].binary_node.left.size() << std::endl;

    // Set this->math boolean to false
    this->math = false;
    this->math_number = false;
    this->math_index = 0;
}

void ParserAST::init(std::vector<Tokens::Token> &tokens) {
    this->tokens = tokens;

    for (this->token_index = 0; this->token_index < tokens.size(); this->token_index++) {
        this->curr_token = this->tokens[this->token_index];

        if ((this->math == false) && (this->curr_token.type == Tokens::Types::Int || this->curr_token.type == Tokens::Types::Float || this->curr_token.type == Tokens::Types::Plus || this->curr_token.type == Tokens::Types::Minus || this->curr_token.type == Tokens::Types::Divide || this->curr_token.type == Tokens::Types::Multiply))
            this->parse_math();
        else {
            Error::quick_err(UNSUPPORTED_TOKEN, "Parser not supports acutal token.", this->curr_token.filename, this->curr_token.position.row, this->curr_token.position.col);
            this->error = true;
        }
    }
}