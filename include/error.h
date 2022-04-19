#ifndef ERROR_H
#define ERROR_H

#include <iostream>

#define INVALID_SYNTAX_ERROR    (std::string)"InvalidSyntax"
#define SHELL_ERROR             (std::string)"ShellError"
#define FILE_ERROR              (std::string)"FileError"
#define INVALID_CHARACTER       (std::string)"InvalidCharacter" 
#define ARITHMETIC_ERROR        (std::string)"ArithmeticError"     
#define UNSUPPORTED_TOKEN       (std::string)"UnsupportedTokenError"     

namespace Error {
    typedef struct Error_Type {
        std::string  title;
        std::string  message;
        std::string  filename;
        int row;
        int col;
    } Error_Type;

    // Quick error creator
    void quick_err(std::string title, std::string message, std::string filename, int row, int col);

    // Create error
    Error::Error_Type create_error(std::string title, std::string message, std::string filename, int row, int col);

    // Print out error
    void print_error(Error::Error_Type err);
};

#endif //ERROR_H
