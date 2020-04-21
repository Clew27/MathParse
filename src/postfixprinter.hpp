#ifndef __POSTFIXPRINTER_H__
#define __POSTFIXPRINTER_H__

#include <iostream>
#include "expr.hpp"
#include "lex.hpp"

namespace visitor {
    class PostfixPrinter : public expr::ExprVisitorInterface<void> { 
    public:
        void operator()(expr::Binary& expr) {
            boost::apply_visitor(*this, expr.left);
            std::cout << " ";
            boost::apply_visitor(*this, expr.right);

            switch(expr.op.type) {
                case lex::token_t::MULT:
                    std::cout << " * ";
                    break;
                case lex::token_t::DIV:
                    std::cout << " / ";
                    break;
                case lex::token_t::PLUS:
                    std::cout << " + ";
                    break;
                case lex::token_t::MINUS:
                    std::cout << " - ";
                    break;
            }
        }

        void operator()(expr::Literal& expr) {
            std::cout << expr.val;
        }
    };
}

#endif /* __POSTFIXPRINTER_H__ */