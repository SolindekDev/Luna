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
#include <cstring>
#include <string>

#include <lexer.h>
#include <io.h>
#include <parser_.h>
#include <error.h>
#include <l_utils.h>

#define FAILED_CODE  1
#define SUCCESS_CODE 0

void help() {
    std::cout << "Usage: luna [--version] [--help] [<name of file to compile>.lu]\n";
    exit(FAILED_CODE);
}

void version() {
    std::cout << "luna (x86_64) v0.0.1\n"
              << "Copyright (C) 2022, SolindekDev | GNU General Public License\n\n"
              << "This program is free software: you can redistribute it and/or modify\n"
              << "it under the terms of the GNU General Public License as published by\n"
              << "the Free Software Foundation, either version 3 of the License, or\n"
              << "(at your option) any later version."
              << std::endl;
    exit(FAILED_CODE);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout <<  "luna shell (x86_64) v0.0.1\n"
                  << "Copyright (C) 2022, SolindekDev | GNU General Public License\n\n"
                  << "This program is free software: you can redistribute it and/or modify\n"
                  << "it under the terms of the GNU General Public License as published by\n"
                  << "the Free Software Foundation, either version 3 of the License, or\n"
                  << "(at your option) any later version."
                  <<  std::endl;
        while (1) {
            std::cout << ">> ";
            std::string shinput;
            std::getline(std::cin, shinput);

            Lexer* lexer = new Lexer("shell", shinput);
            std::vector<Tokens::Token> tokens = lexer->init();

            if (lexer->is_error_message == true)
                exit(0);

            ParserAST* parser = new ParserAST();
            parser->init(tokens);

            if (parser->error == true) 
                exit(0);
        }

    } else {
        if (strcmp(argv[1], "help") == 0 || strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "h") == 0 ||
            strcmp(argv[1], "--h") == 0 || strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "-help") == 0) {
            help();
        } else if (strcmp(argv[1], "version") == 0 || strcmp(argv[1], "--version") == 0 || strcmp(argv[1], "v") == 0 ||
                   strcmp(argv[1], "--v") == 0 || strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "-version") == 0) {
            version();
        } else {
            if (IO::file_exists(argv[1]) == 0) {
                IO::Value value = IO::read_file(argv[1]);

                Lexer* lexer = new Lexer((std::string)argv[1], value.value);
                std::vector<Tokens::Token> tokens = lexer->init();

                if (lexer->is_error_message == true)
                    exit(0);

                ParserAST* parser = new ParserAST();
                parser->init(tokens);
                
                if (parser->error == true) 
                    exit(0);
            } else {
                Error::quick_err(FILE_ERROR, (std::string)argv[1] + " file does not exist", "nofilename", 0, 0);
            }
        }
    }

    return 0;
}
