#ifndef __LEX_H__
#define __LEX_H__

#include <string>
#include <vector>

/**
 * Token Definitions 
 * PLUS           +
 * MINUS          -
 * MULT           *
 * DIV            /
 * LPAREN         (
 * RPAREN         )
 * INTEGER        0|([1-9][0-9]*)
 */

namespace lex {
    enum token_t {
        PLUS, MINUS, MULT, DIV, LPAREN, RPAREN, INTEGER
    };

    struct location {
        size_t line_no;
        size_t offset;
    };

    struct Token {
        token_t type;
        location pos;
        std::string lexeme;
    };

    class Lexer {
    private:
        location cur_pos = {1, 0}; /// Current position in the file
        size_t index;              /// Current position of the lexer head
        std::string input;         /// Input file

        char advance();
        char peek();

    public:
        std::vector<Token> scan(std::string input_);
    };
}

#endif /* __LEX_H__ */
