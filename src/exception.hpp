#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

#include <iostream>
#include <string>
#include <exception>
#include <sstream>

enum exception_t {
    LEX, PARSE, RUNTIME
};

class Exception : public std::exception {
private:
    const char* msg;
public:
    Exception(const std::string msg_) {
        msg = msg_.c_str();
    }
    Exception(const char* msg_) : msg(msg_) {}

    const char* what() const throw() {
        return msg;
    }
};

/// Exception wrappers
class LexException : public Exception {
public:
    using Exception::Exception;
};

class ParseException : public Exception {
public:
    using Exception::Exception;
};

class RuntimeException : public Exception {
public:
    using Exception::Exception;
};

void raise_exception(exception_t type, std::string msg);

#endif /* __EXCEPTION_H__ */