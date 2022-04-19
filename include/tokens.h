#ifndef TOKENS_H
#define TOKENS_H

#include <iostream>
#include <vector>

#define IDENTIFIER_CONSTANT (std::string)"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_?@"

namespace Tokens {

    enum Types {
        String, // "String"
        Int, // 100
        Float, // 100.1
        Identifier, // if
        None, // None
        Newline, // \n
        Lpar, // (
        Rpar, // )
        Plus, // +
        Minus, // -
        Divide, // /
		Assignment, // =
        Multiply, // *
		Eof, // \0
		Null, // Null
        AddAssignment, // +=
        SubtractAssignment, // -=
        MultiplyAssignment, // *=
        DivideAssignment, // /=
        Increment, // ++
        Decrement, // --
        Modulus, // %
        BiggerThan, // <
        LessThan, // >
        Equals, // ==
        NotEquals, // !=
        BiggerThanOrEquals, // <=
        LessThanOrEquals, // >=
        Or, // |
        And, // &
        Bang, // !
        RightBracketRectangle, // ]
        LeftBracketRectangle, // [
        StringJoin // <>
    };

    typedef struct Position {
        int row;
        int col;
    } Position;

    typedef struct Token {
        std::string value;
        std::string filename;
        Types       type;
        Position    position;
    } Token;

    // Creates a token structure
    Token create_token(std::string value, std::string filename, Tokens::Types type, int row, int col);

    // Prints out a token structure
    void  print_token(Tokens::Token token);

    // Get token type in string
    std::string type_token_raw(Tokens::Types type);
}

#endif //TOKENS_H
