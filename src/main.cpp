#include <iostream>
#include "evaluator.hpp"
#include "infixprinter.hpp"
#include "postfixprinter.hpp"
#include "expr.hpp"

int main() {
    expr::Literal l1(1);
    expr::Literal l2(2);
    expr::Literal l3(3);
    expr::Binary  b1(l1, expr::operation_t::ADD, l2);
    expr::Binary  b2(b1, expr::operation_t::SUB, l3);

    /// Print Infix
    visitor::InfixPrinter in_print;
    boost::apply_visitor(in_print, b2);
    std::cout << std::endl; 

    /// Print Postfix
    visitor::PostfixPrinter post_print;
    boost::apply_visitor(post_print, b2);
    std::cout << std::endl;

    /// Print Evaluation
    visitor::Evaluator eval;
    int res = boost::apply_visitor(eval, b2);
    std::cout << "Result: " << res << std::endl;

    return EXIT_SUCCESS;
}

