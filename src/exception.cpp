#include "exception.hpp"

void raise_exception(exception_t type, std::string msg) {
    switch (type) {
        case exception_t::LEX:
            throw LexException(msg);
        case exception_t::PARSE:
            throw ParseException(msg);
        case exception_t::RUNTIME:
            throw RuntimeException(msg);
    }
}