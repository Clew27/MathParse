#ifndef __EVALUATOR_H__
#define __EVALUATOR_H__

#include "expr.hpp"
#include "exception.hpp"

namespace visitor {
    class Evaluator : public expr::ExprVisitorInterface<int> { 
    public:
        int operator()(expr::Binary& expr) {
            int left  = boost::apply_visitor(*this, expr.left);
            int right = boost::apply_visitor(*this, expr.right);

            switch(expr.op) {
                case expr::operation_t::MULT:
                    return left * right;
                case expr::operation_t::DIV:
                    if (right == 0) 
                        raise_exception(exception_t::RUNTIME, 
                            "Division by zero is not allowed.");
                    return left / right;
                case expr::operation_t::ADD:
                    return left + right;
                case expr::operation_t::SUB:
                    return left - right;
            }
        }

        int operator()(expr::Literal& expr) {
            return expr.val;
        }
    };
}

#endif /* __EVALUATOR_H__ */