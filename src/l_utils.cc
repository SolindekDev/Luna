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
#include <tokens.h>
#include <io.h>

void LUtils::show_tokens(std::vector<Tokens::Token> &tokens) {
    for (int i = 0; i < tokens.size(); i++) 
        Tokens::print_token(
            tokens.at(i)
        );
}