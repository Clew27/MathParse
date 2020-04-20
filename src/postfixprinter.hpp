#ifndef __POSTFIXPRINTER_H__
#define __POSTFIXPRINTER_H__

#include <iostream>
#include "expr.hpp"

namespace visitor {
    class PostfixPrinter : public expr::ExprVisitorInterface<void> { 
    public:
        void operator()(expr::Binary& expr) {
            boost::apply_visitor(*this, expr.left);
            std::cout << " ";
            boost::apply_visitor(*this, expr.right);

            switch(expr.op) {
                case expr::operation_t::MULT:
                    std::cout << " *";
                    break;
                case expr::operation_t::DIV:
                    std::cout << " /";
                    break;
                case expr::operation_t::ADD:
                    std::cout << " +";
                    break;
                case expr::operation_t::SUB:
                    std::cout << " -";
                    break;
            }
        }

        void operator()(expr::Literal& expr) {
            std::cout << expr.val;
        }
    };
}

#endif /* __POSTFIXPRINTER_H__ */