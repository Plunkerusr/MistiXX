#pragma once

#include <algo/String.hpp>
#include <drivers/Uart.hpp>

namespace kernel {

namespace Logger {
    void putc(char c);
    void print(const char* str);
    void print(const String& str);
    void printn(int64_t numb, uint32_t s);
    void printd(int64_t numb);

    class Log {
    public:
        Log() = default;

        friend const Log& operator<<(const Log& log, const String& value);
        friend const Log& operator<<(const Log& log, int value);
        friend const Log& operator<<(const Log& log, uint32_t value);
    };
}
}