#ifndef __INFIXPRINTER_H__
#define __INFIXPRINTER_H__

#include <iostream>
#include "expr.hpp"

namespace visitor {
    class InfixPrinter : public expr::ExprVisitorInterface<void> { 
    public:
        void operator()(expr::Binary& expr) {
            std::cout << "(";
            boost::apply_visitor(*this, expr.left);

            switch(expr.op) {
                case expr::operation_t::MULT:
                    std::cout << " * ";
                    break;
                case expr::operation_t::DIV:
                    std::cout << " / ";
                    break;
                case expr::operation_t::ADD:
                    std::cout << " + ";
                    break;
                case expr::operation_t::SUB:
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