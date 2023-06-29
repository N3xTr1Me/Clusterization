#ifndef CLASTERIZATION_FILE_HANDLER_H
#define CLASTERIZATION_FILE_HANDLER_H


#include "../dataclasses/domain.h"


class FileHandler {

protected:
    unsigned int array_size_limit;  // максимальное количество считываемых точек
    char* point_filter;             // Регулярное выражение

public:
    FileHandler(unsigned int size_limit, char* filter);

    Domain read(char* path);
    void write(char* path, Domain& domain);

    ~FileHandler() = default;
};


#endif //CLASTERIZATION_FILE_HANDLER_H
