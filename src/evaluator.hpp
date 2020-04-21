#ifndef __EVALUATOR_H__
#define __EVALUATOR_H__

#include <math.h>
#include "expr.hpp"
#include "exception.hpp"

namespace visitor {
    class Evaluator : public expr::ExprVisitorInterface<float> { 
    public:
        float operator()(expr::Binary& expr) {
            float left  = boost::apply_visitor(*this, expr.left);
            float right = boost::apply_visitor(*this, expr.right);

            switch(expr.op.type) {
                case lex::token_t::MULT:
                    return left * right;
                case lex::token_t::DIV:
                    if (right == 0)
                        raise_exception(exception_t::RUNTIME, 
                            "Division by zero is not allowed.");
                    return left / right;
                case lex::token_t::PLUS:
                    return left + right;
                case lex::token_t::MINUS:
                    return left - right;
                case lex::token_t::POWER:
                    return pow(left, right);
            }
        }

        float operator()(expr::Literal& expr) {
            return expr.val;
        }
    };
}

#endif /* __EVALUATOR_H__ */