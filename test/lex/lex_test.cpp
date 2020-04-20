#include <iostream>
#include <string>
#include <vector>

#include "../../src/exception.hpp"
#include "../../src/lex.hpp"

void print_tokens(std::vector<lex::Token> tokens) {
    for (const auto& token : tokens) {
        switch(token.type) {
            case lex::token_t::PLUS:
                std::cout << "TOK_PLUS   ";
                break;
            case lex::token_t::MINUS:
                std::cout << "TOK_MINUS  ";
                break;
            case lex::token_t::MULT:
                std::cout << "TOK_MULT   ";
                break;
            case lex::token_t::DIV:
                std::cout << "TOK_DIV    ";
                break;
            case lex::token_t::LPAREN:
                std::cout << "TOK_LPAREN ";
                break;
            case lex::token_t::RPAREN:
                std::cout << "TOK_RPAREN ";
                break;
            case lex::token_t::INTEGER:
                std::cout << "TOK_INTEGER";
                break;
        }
        
        std::cout << " " << token.lexeme << " at (" \
            << token.pos.line_no << ", " << token.pos.offset \
            << ")" << std::endl;
    }
} 

int main() {
    lex::Lexer lexer;

    std::string valid1 = "(1 + 3) / 5";
    std::cout << valid1 << std::endl;
    auto tokens1 = lexer.scan(valid1);
    print_tokens(tokens1);

    std::string invalid1 = "(1 + 00) / 5";
    std::cout << invalid1 << std::endl;
    try {
        auto intokens1 = lexer.scan(invalid1);
    } catch (LexException& e) {
        std::cout << e.what() << std::endl;
    }

    std::string invalid2 = "(1 + 0) / hello_world";
    std::cout << invalid2 << std::endl;
    try {
        auto intokens2 = lexer.scan(invalid2);
    } catch (LexException& e) {
        std::cout << e.what() << std::endl;
    }
    return EXIT_SUCCESS;
}