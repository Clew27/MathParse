#ifndef __EXPR_H__
#define __EXPR_H__

#include <boost/variant.hpp>
#include "lex.hpp"

namespace expr {
    class Binary;
    class Literal;

    using expr_t = boost::variant<
        boost::recursive_wrapper<Binary>,
        boost::recursive_wrapper<Literal>
    >;

    template <class R>
    class ExprVisitorInterface : public boost::static_visitor<R> {
    public:
        virtual R operator()(Binary& expr) = 0;
        virtual R operator()(Literal& expr) = 0;
    };

    class Binary{
    public:
        expr_t left;
        lex::Token op;
        expr_t right;

        Binary(expr_t left_, lex::Token op_, expr_t right_)
            : left(left_)
            , op(op_)
            , right(right_)
        {}

        template <class R>
        R apply_visitor(ExprVisitorInterface<R>& visitor) {
            return visitor(*this);
        }
    };

    class Literal{
    public:
        int val;

        Literal(int val_)
            : val(val_)
        {}

        template <class R>
        R apply_visitor(ExprVisitorInterface<R>& visitor) {
            return visitor(*this);
        }
    };
}

#endif /* __EXPR_H__ */
