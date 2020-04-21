#include "parse.hpp"
#include <string>
#include "exception.hpp"

#include <iostream>

namespace parse {
    lex::Token* Parser::advance() {
        index++;
        if (index == tokens.size()) return nullptr;
        return &tokens[index];
    }

    lex::Token* Parser::peek() {
        if (index + 1 == tokens.size()) return nullptr;
        return &tokens[index + 1];
    }

    lex::Token* Parser::consume(lex::token_t type) {
        return consume({type});
    }

    lex::Token* Parser::consume(std::initializer_list<lex::token_t> types) {
        lex::Token* next = peek();

        if (next == nullptr) return nullptr;

        bool is_valid_type = false;
        if (next != nullptr) {
            for (const auto& type : types) {
                if (next->type == type) {
                    is_valid_type = true;
                    break;
                }
            }
        }

        // Don't consume if types are not found
        if (!is_valid_type) return nullptr;

        /// Return token if otherwise
        return advance();
    }

    inline expr::expr_t Parser::parse_expr() {
        return parse_addition();
    }

    expr::expr_t Parser::parse_addition() {
        expr::expr_t addition = parse_multiplication();

        lex::Token* next = consume({lex::token_t::PLUS, lex::token_t::MINUS});
        while (next != nullptr) {
            expr::expr_t rhs = parse_multiplication();
            addition = expr::Binary(addition, *next, rhs);
            next = consume({lex::token_t::PLUS, lex::token_t::MINUS});
        }
        return addition;
    }
    
    expr::expr_t Parser::parse_multiplication() {
        expr::expr_t multiplication = parse_power();

        lex::Token* next = consume({lex::token_t::MULT, lex::token_t::DIV});
        while (next != nullptr) {
            expr::expr_t rhs = parse_power();
            multiplication = expr::Binary(multiplication, *next, rhs);
            next = consume({lex::token_t::MULT, lex::token_t::DIV});
        }
        return multiplication;
    }

    expr::expr_t Parser::parse_power() {
        expr::expr_t power = parse_primary();
        lex::Token* next = consume(lex::token_t::POWER);
        while (next != nullptr){
            expr::expr_t rhs = parse_power();
            power = expr::Binary(power, *next, rhs);
            next = consume(lex::token_t::POWER);
        }
        return power;
    }

    expr::expr_t Parser::parse_primary() {
        if (peek() == nullptr)
            raise_exception(exception_t::PARSE, "Expecting '(' or integer.");
        
        lex::Token* next_tok = advance();
        switch (next_tok->type) {
            case lex::token_t::LPAREN: {
                expr::expr_t expr = parse_expr();
                consume(lex::token_t::RPAREN);
                return expr;
            }
            case lex::token_t::INTEGER: {
                return expr::Literal(std::stoi(next_tok->lexeme));
            }
            default: {
                raise_exception(exception_t::PARSE, 
                    "Invalid token " + next_tok->lexeme);
            }
        }
    }

    expr::expr_t Parser::parse(std::vector<lex::Token> tokens_) {
        tokens = tokens_;
        index = -1;
        expr::expr_t parsed = parse_expr();

        if (index + 1 != tokens.size())
            raise_exception(exception_t::PARSE, "Invalid statement.");

        return parsed;
    }
}