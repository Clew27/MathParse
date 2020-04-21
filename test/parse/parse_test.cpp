#include <iostream>
#include <string>
#include <vector>

#include <boost/variant.hpp>

#include "../../src/exception.hpp"
#include "../../src/lex.hpp"
#include "../../src/parse.hpp"
#include "../../src/infixprinter.hpp"
#include "../../src/postfixprinter.hpp"
#include "../../src/evaluator.hpp"

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
    parse::Parser parser;
    visitor::InfixPrinter inprinter;
    visitor::PostfixPrinter postprinter;
    visitor::Evaluator evaluator;

    // std::string valid = "1 + 5 / 4 + 7 * (5 - 2) / 4";
    std::string valid = "1 / (9 * 9 / 3 / 3 / 3)"; 
    std::cout << valid << std::endl;
    auto tokens = lexer.scan(valid);
    print_tokens(tokens);
    auto ast = parser.parse(tokens); 
    
    boost::apply_visitor(inprinter, ast);
    std::cout << std::endl;

    boost::apply_visitor(postprinter, ast);
    std::cout << std::endl;

    std::cout << boost::apply_visitor(evaluator, ast) << std::endl;

    return EXIT_SUCCESS;
}