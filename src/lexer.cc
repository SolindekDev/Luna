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

#include <lexer.h>
#include <l_utils.h>
#include <error.h>
#include <utils.h>
#include <tokens.h>
#include <io.h>

std::string identifier_constant = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_?@";
std::string number_constant = "0123456789";

Tokens::Token Lexer::get_last_token(std::vector<Tokens::Token> &tokens) {
    if (tokens.size() == 0)
        return Tokens::create_token("NULL", "none.sbasic",Tokens::Types::None, 0, 0);
    else
        return tokens[tokens.size() - 1];
} 

void Lexer::newline(std::vector<Tokens::Token> &tokens) {
    int newline_col = this->curr_col;
    this->space = true;
    this->comment_opened_inline = false;
    this->curr_row++;
    this->curr_col = 0;
    // tokens.push_back(Tokens::create_token(NEWLINE__, this->filename, Tokens::Types::Newline, this->curr_row, this->curr_col));
}

void Lexer::comment_inline(std::vector<Tokens::Token> &tokens) {
    if (this->string_opened == true)
        tokens[tokens.size() - 1].value += this->curr_char;
    else
        this->comment_opened_inline = true;
}

void Lexer::comment_multiline(std::vector<Tokens::Token> &tokens) {
    if (this->string_opened == true)
        tokens[tokens.size() - 1].value += this->curr_char;
    else {
        if (this->comment_opened_multi == false) {
            this->comment_opened_multi = true;
        } else {
            this->comment_opened_multi = false;
        }
    }
}

void Lexer::string_creator(std::vector<Tokens::Token> &tokens) {
    if (this->string_opened == true) 
        this->string_opened = false;
    else {
        tokens.push_back(Tokens::create_token("", this->filename, Tokens::Types::String, this->curr_row, this->curr_col));
        this->string_opened = true;
    }
}

void Lexer::string_append(std::vector<Tokens::Token> &tokens) {
    tokens[tokens.size() - 1].value += this->curr_char;
}

Tokens::Types Lexer::one_char(char next_char) {
    switch (this->curr_char) {
        case '\n':
            return Tokens::Types::Newline; // \n
        case '(':
            return Tokens::Types::Lpar; // (
        case ')':
            return Tokens::Types::Rpar; // )
        case '+':
            if (next_char != NO_CHAR__ && next_char == '=') // +=
                return Tokens::Types::AddAssignment;
            if (next_char != NO_CHAR__ && next_char == '+') // ++
                return Tokens::Types::Increment;
            return Tokens::Types::Plus; // +
        case '-':
            if (next_char != NO_CHAR__ && next_char == '=') // -=
                return Tokens::Types::SubtractAssignment;
            if (next_char != NO_CHAR__ && next_char == '-') // --
                return Tokens::Types::Increment;
            return Tokens::Types::Minus; // -
        case '%':
            return Tokens::Types::Modulus; // %
        case '>':
            if (next_char != NO_CHAR__ && next_char == '=') // >=
                return Tokens::Types::BiggerThanOrEquals;
            return Tokens::Types::BiggerThan; // >
        case '<':
            if (next_char != NO_CHAR__ && next_char == '=') // >=
                return Tokens::Types::LessThanOrEquals;
            if (next_char != NO_CHAR__ && next_char == '>')
                return Tokens::Types::StringJoin;
            return Tokens::Types::LessThan; // <
        case '*':
            if (next_char != NO_CHAR__ && next_char == '=') // *=
                return Tokens::Types::MultiplyAssignment;
            return Tokens::Types::Multiply; // *
        case '/':
            if (next_char != NO_CHAR__ && next_char == '=') // /=
                return Tokens::Types::DivideAssignment;
            return Tokens::Types::Divide; // /
        case '=':
            if (next_char != NO_CHAR__ && next_char == '=') // ==
                return Tokens::Types::Equals;
            return Tokens::Types::Assignment; // =
        case '!':
            if (next_char != NO_CHAR__ && next_char == '=') // !=
                return Tokens::Types::NotEquals;
            return Tokens::Types::Bang; // =
        case '|':
            return Tokens::Types::Or; // |
        case '&':
            return Tokens::Types::And; // &
        case '[':
            return Tokens::Types::RightBracketRectangle; // [
        case ']':
            return Tokens::Types::LeftBracketRectangle; // [
        default:
            return Tokens::Types::None;
    }
}

void Lexer::eof(std::vector<Tokens::Token> &tokens) {
    tokens.push_back(Tokens::create_token(EOF__, this->filename, Tokens::Types::Eof, this->curr_row, this->curr_col));
}

char Lexer::get_next_char() {
    if (this->value.length() == this->index)
        return NO_CHAR__;
    else
        return this->value[this->index+1];
}

void Lexer::add_and_create_token_char(char curr_char, std::string filename, Tokens::Types type, int curr_row, int curr_col, std::vector<Tokens::Token> &tokens) {
    std::string value;
    value.assign(1, curr_char);
    tokens.push_back(Tokens::create_token(value, filename, type, curr_row, curr_col));
}

void Lexer::identifier_creator(std::vector<Tokens::Token> &tokens, Tokens::Token last_token) {
    if (last_token.type == Tokens::Types::None) {
        Lexer::add_and_create_token_char(this->curr_char, this->filename, Tokens::Types::Identifier, this->curr_row, this->curr_row, tokens);
        this->space = false;
    } else {
        if (this->space == false) { 
            if (last_token.type == Tokens::Types::Identifier) {
                tokens[tokens.size() - 1].value += this->curr_char;
                this->space = false;
            } else {
                Lexer::add_and_create_token_char(this->curr_char, this->filename, Tokens::Types::Identifier, this->curr_row, this->curr_row, tokens);
                this->space = false;
            }
        } else {
            Lexer::add_and_create_token_char(this->curr_char, this->filename, Tokens::Types::Identifier, this->curr_row, this->curr_row, tokens);
            this->space = false;
        }
    }
}

void Lexer::number_creator(std::vector<Tokens::Token> &tokens, Tokens::Token last_token) {
    if (last_token.type == Tokens::Types::None) {
        Lexer::add_and_create_token_char(this->curr_char, this->filename, Tokens::Types::Int, this->curr_row, this->curr_row, tokens);
        this->space = false;
    } else {
        if (this->space == false) { 
            if (last_token.type == Tokens::Types::Int) {
                tokens[tokens.size() - 1].value += this->curr_char;
                this->space = false;
            } else if (last_token.type == Tokens::Types::Float) {
                tokens[tokens.size() - 1].value += this->curr_char;
                this->space = false;
            } else if (last_token.type == Tokens::Types::Identifier && this->space == false) {
                tokens[tokens.size() - 1].value += this->curr_char;
                tokens[tokens.size() - 1].type = Tokens::Types::Identifier;
                this->space = false;
            } else {
                Lexer::add_and_create_token_char(this->curr_char, this->filename, Tokens::Types::Int, this->curr_row, this->curr_row, tokens);
                this->space = false;
            }
        } else {
            Lexer::add_and_create_token_char(this->curr_char, this->filename, Tokens::Types::Int, this->curr_row, this->curr_row, tokens);
            this->space = false;
        }
    }
}

void Lexer::float_creator(std::vector<Tokens::Token> &tokens, Tokens::Token last_token) {
    if (last_token.type == Tokens::Types::None) {
        tokens.push_back(Tokens::create_token("0.", this->filename, Tokens::Types::Float, this->curr_row, this->curr_col));
        this->space = false;
    } else {
        if (last_token.type == Tokens::Types::Int) {
            tokens[tokens.size() - 1].value += this->curr_char;
            tokens[tokens.size() - 1].type = Tokens::Types::Float;
            this->space = false;
        } else if (last_token.type == Tokens::Types::Float) {
            if (last_token.value.find('.') != std::string::npos) {
                Error::quick_err(INVALID_SYNTAX_ERROR, "This float already contains a \".\"", this->filename, this->curr_row, this->curr_col);
                this->is_error_message = true;
            } else {
                tokens[tokens.size() - 1].value += this->curr_char;
                tokens[tokens.size() - 1].type = Tokens::Types::Float;
            }
        } else {
            tokens.push_back(Tokens::create_token("0.", this->filename, Tokens::Types::Float, this->curr_row, this->curr_col));
            this->space = false;  
        }
    }
}

void Lexer::unsupported_char() { // 🍝 code
    char buffer[100] = {0};
    int number_base = 10;
    std::string message = "Founded unsupported character: ";
    std::string str_code = "";
    str_code.assign(1, this->curr_char);
    int input = utf8_to_unicode(str_code);
    message += this->curr_char;
    message.append(" | ");
    message.append(itoa(input, buffer, number_base));
    Error::quick_err(INVALID_CHARACTER, message, this->filename, this->curr_row, this->curr_col);
    std::cout << std::endl << (int)this->curr_char << std::endl;
    this->is_error_message = true;
}

Lexer::Lexer(std::string filename, std::string value) {
    this->filename = filename;
    this->value = value;
}

std::vector<Tokens::Token> Lexer::init() {
    std::vector<Tokens::Token> tokens;
    Tokens::Token last_token;
    char next_char;

    this->curr_row = 0;

    for (int i = 0; i < value.length(); i++) {
        this->index = i;
        this->curr_char = value[i];
        last_token = this->get_last_token(tokens);
        next_char = this->get_next_char();
        
        if (this->curr_char == '\0')
            this->eof(tokens);
        else if (this->curr_char == '\n') 
            this->newline(tokens);
        else if (this->curr_char == '\r' || (int)this->curr_char == -1)
            continue;
        else if (this->curr_char == ';')
            this->comment_inline(tokens);
        else if (this->comment_opened_inline == true)
            continue;
        else if (this->curr_char == '"')
            this->string_creator(tokens);
        else if (this->string_opened == true)
            this->string_append(tokens);
        else if (this->curr_char == ' ')
            this->space = true;
        else if (this->one_char(next_char) != Tokens::Types::None)
            this->add_and_create_token_char(this->curr_char, this->filename, this->one_char(next_char), this->curr_row, this->curr_col, tokens);
        else if (identifier_constant.find(this->curr_char) != std::string::npos)
            this->identifier_creator(tokens, last_token);
        else if (number_constant.find(this->curr_char) != std::string::npos)
            this->number_creator(tokens, last_token);
        else if (this->curr_char == '.')
            this->float_creator(tokens, last_token);
        else
            this->unsupported_char();

        this->curr_col++;
    }

    this->eof(tokens);

    // LUtils::show_tokens(tokens);

    if (this->is_error_message == true)
        exit(1);

    return tokens;
}