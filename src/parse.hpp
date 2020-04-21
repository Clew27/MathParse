#ifndef __PARSE_H__
#define __PARSE_H__

#include <vector>
#include <initializer_list>
#include "lex.hpp"
#include "expr.hpp"

/** Grammar
 * expr           -> addition
 * addition       -> multiplication (('+' | '-') multiplication)*
 * multiplication -> primary (('*' | '/') primary)*
 * primary        -> INTEGER
 *                 | '(' expr ')'
 */

namespace parse {
    class Parser {
    private:
        size_t index;
        std::vector<lex::Token> tokens;

        lex::Token* advance();
        lex::Token* peek();
        lex::Token* consume(lex::token_t type);
        lex::Token* consume(std::initializer_list<lex::token_t> types);

        inline expr::expr_t parse_expr();
        expr::expr_t parse_addition();
        expr::expr_t parse_multiplication();
        expr::expr_t parse_primary();

    public:
        expr::expr_t parse(std::vector<lex::Token> tokens_);
    };
}

#endif /* __PARSE_H__ */