#ifndef __EVALUATOR_H__
#define __EVALUATOR_H__

#include "expr.hpp"

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