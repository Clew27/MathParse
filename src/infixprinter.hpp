#ifndef __INFIXPRINTER_H__
#define __INFIXPRINTER_H__

#include <iostream>
#include "expr.hpp"
#include "lex.hpp"

namespace visitor {
    class InfixPrinter : public expr::ExprVisitorInterface<void> { 
    public:
        void operator()(expr::Binary& expr) {
            std::cout << "(";
            boost::apply_visitor(*this, expr.left);

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

            boost::apply_visitor(*this, expr.right);
            std::cout << ")";
        }

        void operator()(expr::Literal& expr) {
            std::cout << expr.val;
        }
    };
}

#endif /* __INFIXPRINTER_H__ */