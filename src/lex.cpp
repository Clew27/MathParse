#include "lex.hpp"
#include "exception.hpp"
#include <iostream>

bool is_digit(char n) {
    return n >= '0' && n <= '9';
}

namespace lex {
    std::unordered_map<token_t, std::string> token_name_map = {
        {token_t::PLUS,    "TOK_PLUS"},
        {token_t::MINUS,   "TOK_MINUS"},
        {token_t::MULT,    "TOK_MULT"},
        {token_t::DIV,     "TOK_DIV"},
        {token_t::LPAREN,  "TOK_LPAREN"},
        {token_t::RPAREN,  "TOK_RPAREN"},
        {token_t::INTEGER, "TOK_INTEGER"}
    };

    char Lexer::advance() {
        index++;
        if (index == input.length()) return '\0';
        return input[index];
    }

    char Lexer::peek() {
        if (index + 1 == input.length()) return '\0';
        return input[index + 1];
    }

    std::vector<Token> Lexer::scan(std::string input_) {
        /// Reset tracking
        input = input_;
        cur_pos = {1, 0};
        index = -1;

        /// Lex!!!
        std::vector<Token> tokens;
        char next_char;
        while ((next_char = advance()) != '\0') {
            cur_pos.offset++;
            switch (next_char) {
                case ' ':
                case '\t': {
                    break;
                }
                case '\n': {
                    cur_pos.line_no++;
                    cur_pos.offset = 1;
                    break;
                }
                case '(': {
                    tokens.push_back({token_t::LPAREN, cur_pos, "("});
                    break;
                }
                case ')': {
                    tokens.push_back({token_t::RPAREN, cur_pos, ")"});
                    break;
                }
                case '+': {
                    tokens.push_back({token_t::PLUS, cur_pos, "+"});
                    break;
                }
                case '-': {
                    tokens.push_back({token_t::MINUS, cur_pos, "-"});
                    break;
                }
                case '*': {
                    tokens.push_back({token_t::MULT, cur_pos, "*"});
                    break;
                }
                case '/': {
                    tokens.push_back({token_t::DIV, cur_pos, "/"});
                    break;
                }
                case '^': {
                    tokens.push_back({token_t::POWER, cur_pos, "^"});
                    break;
                }
                case '0': {
                    /// Zero is a special case
                    /// There can only be one zero followed by no digits
                    if (is_digit(peek())) {
                        raise_exception(exception_t::LEX, 
                            "A number cannot begin with a 0.");
                    }
                    tokens.push_back({token_t::INTEGER, cur_pos, "0"});
                }
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9': {
                    location start_pos = cur_pos;
                    int start_idx = index;

                    /// Advance until there are no more digits
                    /// (stops at last digit)
                    while (is_digit(peek())) advance();

                    tokens.push_back({token_t::INTEGER, start_pos, 
                        input.substr(start_idx, index - start_idx + 1)});               
                    break;
                }
                default: {
                    std::string msg = "Invalid character ";
                    msg += next_char;
                    msg += '.';
                    raise_exception(exception_t::LEX, msg);
                }
            }
        }
        return tokens;
    }
}