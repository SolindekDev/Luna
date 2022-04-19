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

#include <tokens.h>

Tokens::Token Tokens::create_token(std::string value, std::string filename, Tokens::Types type, int row, int col) {
    Tokens::Token     token;
    Tokens::Position  pos;

    pos.col           = col;
    pos.row           = row;

    token.value       = value;
    token.filename    = filename;
    token.type        = type;
    token.position    = pos;

    return token;
}

void Tokens::print_token(Tokens::Token token) {
    std::cout << "Type: "
              << Tokens::type_token_raw(token.type)
              // << token.type
              << " | Value: "
              << token.value
              << " | Row: "
              << token.position.row
              << " | Col: "
              << token.position.col
              << std::endl;
}

std::string Tokens::type_token_raw(Tokens::Types type_) {
    switch (type_) {
        case Tokens::Types::String:
            return (std::string)"String";
            break;
        case Tokens::Types::Int:
            return (std::string)"Int";
            break;
        case Tokens::Types::Float:
            return (std::string)"Float";
            break;
        case Tokens::Types::Identifier:
            return (std::string)"Identifier";
            break;
        case Tokens::Types::None:
            return (std::string)"None";
            break;
        case Tokens::Types::Newline:
            return (std::string)"Newline";
            break;
        case Tokens::Types::Eof:
            return (std::string)"EOF";
            break;
        case Tokens::Types::Lpar:
            return (std::string)"Lpar";
            break;
        case Tokens::Types::Rpar:
            return (std::string)"Rpar";
            break;
        case Tokens::Types::Plus:
            return (std::string)"Plus";
            break;
        case Tokens::Types::Minus:
            return (std::string)"Minus";
            break;
        case Tokens::Types::Divide:
            return (std::string)"Divide";
            break;
        case Tokens::Types::Multiply:
            return (std::string)"Multiply";
            break;
        case Tokens::Types::Assignment:
            return (std::string)"Assignment";
            break;
        case Tokens::Types::AddAssignment:
            return (std::string)"AddAssignment";
            break;
        case Tokens::Types::SubtractAssignment:
            return (std::string)"SubtractAssignment";
            break;
        case Tokens::Types::MultiplyAssignment:
            return (std::string)"MultiplyAssignment";
            break;
        case Tokens::Types::DivideAssignment:
            return (std::string)"DivideAssignment";
            break;
        case Tokens::Types::Increment:
            return (std::string)"Increment";
            break;
        case Tokens::Types::Decrement:
            return (std::string)"Decrement";
            break;
        case Tokens::Types::Modulus:
            return (std::string)"Modulus";
            break;
        case Tokens::Types::BiggerThan:
            return (std::string)"BiggerThan";
            break;
        case Tokens::Types::LessThan:
            return (std::string)"LessThan";
            break;
        case Tokens::Types::Equals:
            return (std::string)"Equals";
            break;
        case Tokens::Types::NotEquals:
            return (std::string)"NotEquals";
            break;
        case Tokens::Types::BiggerThanOrEquals:
            return (std::string)"BiggerThanOrEquals";
            break;
        case Tokens::Types::LessThanOrEquals:
            return (std::string)"LessThanOrEquals";
            break;
        case Tokens::Types::Or:
            return (std::string)"Or";
            break;
        case Tokens::Types::And:
            return (std::string)"And";
            break;
        case Tokens::Types::Bang:
            return (std::string)"Bang";
            break;
        case Tokens::Types::LeftBracketRectangle:
            return (std::string)"LeftBracketRectangle";
            break;
        case Tokens::Types::RightBracketRectangle:
            return (std::string)"RightBracketRectangle";
            break;
    }

    return "Unknown Type";
}

