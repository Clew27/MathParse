#include "exception.hpp"

void raise_exception(exception_t type, std::string msg) {
    std::stringstream ss;
    ss << "(";
    switch (type) {
        case exception_t::LEX:
            ss << "Lexing" << " Exception) " << msg;
            throw LexException(ss.str());
        case exception_t::PARSE:
            ss << "Runtime" << " Exception) " << msg; 
            ss << "Parse" << " Exception) " << msg; 
            throw ParseException(ss.str());
        case exception_t::RUNTIME:
            throw RuntimeException(ss.str());
    }
}