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

#include <error.h>

#include <iostream>

void Error::quick_err(std::string title, std::string message, std::string filename, int row, int col) {
    Error::print_error(Error::create_error(title, message, filename, row, col));
}

Error::Error_Type Error::create_error(std::string title, std::string message, std::string filename, int row, int col) {
    Error:Error_Type error;

    error.title    = title;
    error.message  = message;
    error.filename = filename;
    error.row      = row;
    error.col      = col;

    return error;
}

void Error::print_error(Error::Error_Type err) {
    if (err.filename == "shell") {
        std::cout << "\e[0;31m" << err.title
                  << ": "
                  << "\e[0;37m" << err.message
                  << std::endl;
    } else {
        std::cout << "\e[0;33m" << err.filename 
                  << ":" 
                  << err.row 
                  << ":" 
                  << err.col 
                  << " " 
                  << "\e[0;31m" << err.title
                  << ": "
                  << "\e[0;37m" << err.message
                  << std::endl;
    }

}