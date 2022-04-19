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

#include <io.h>

#include <iostream>
#include <fstream>
#include <string>

int IO::file_exists(std::string filename) {
    std::ifstream file(filename);

    if(!file.is_open())
        return -1;

    return 0;
}

IO::Value IO::read_file(std::string filename) {
    IO::Value value;
    std::ifstream file(filename);
    std::string str_value;
    char ac;
    int length = 0;

    if (file.is_open()) {
        while (file) {
            ac = file.get();
            str_value.append(1, ac);
            length++;
        }
    }

    value.value = str_value;
    value.length = length;

    return value;
}