#ifndef IO_H
#define IO_H

#include <iostream>

namespace IO {
    typedef struct Value {
        int         length;
        std::string value;
    } Value;

    int file_exists(std::string filename);
    IO::Value read_file(std::string filename);
};


#endif //IO_H
