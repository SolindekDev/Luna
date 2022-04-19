#ifndef LEXER_H
#define LEXER_H

#include <tokens.h>
#include <io.h>

#define NEWLINE__ (std::string)"NEWLINE_0x10"
#define NO_CHAR__ (char)0x4e4f5f43484152
#define EOF__     (std::string)"EOF__0x656f66"

// Lexer Class Definition
class Lexer {
public:
    std::string value; // Value of the file
    std::string filename; // Filename of the file

    int curr_row; // Current row number
    int curr_col; // Current column number
    int index; // Index of the for loop

    char curr_char; // Current character that lexer is currently at

    bool space; // Is space 
    bool string_opened; // Is string opened
    bool comment_opened_inline; // Is comment opened
    bool comment_opened_multi; // Is comment opened
    bool mulcomment_opened; // Is multi-line comment opened
    bool is_error_message; // Is any error

    // Initialize function of class Lexer.
    Lexer(std::string filename, std::string value);

    // Start lexer work
    std::vector<Tokens::Token> init();

    // Get last token from the array token.
    Tokens::Token get_last_token(std::vector<Tokens::Token> &tokens);

    // When lexer is at newline. 
    void newline(std::vector<Tokens::Token> &tokens);

    // Creating inline comments
    void comment_inline(std::vector<Tokens::Token> &tokens); 

    // Creating multi-line comments
    void comment_multiline(std::vector<Tokens::Token> &tokens);

    // Creating string tokens
    void string_creator(std::vector<Tokens::Token> &tokens);

    // Appending to string a characters.
    void string_append(std::vector<Tokens::Token> &tokens);

    // Checking characters for a token.
    Tokens::Types one_char(char next_char);

    // Create eof token
    void eof(std::vector<Tokens::Token> &tokens);

    // Get next character of value.
    char get_next_char();

    // Add and create a token with char value
    void add_and_create_token_char(char curr_char, std::string filename, Tokens::Types type, int curr_row, int curr_col, std::vector<Tokens::Token> &tokens);

    // Create a identifier token
    void identifier_creator(std::vector<Tokens::Token> &tokens, Tokens::Token last_token);

    // Create a number token
    void number_creator(std::vector<Tokens::Token> &tokens, Tokens::Token last_token);

    // Create a float token
    void float_creator(std::vector<Tokens::Token> &tokens, Tokens::Token last_token);

    // Unsupported character function
    void unsupported_char();
};

#endif //LEXER_H
