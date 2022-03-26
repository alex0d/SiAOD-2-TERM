#ifndef __EMPLOYEE_VECTOR_H
#define __EMPLOYEE_VECTOR_H

#include <string>

struct Date {
    unsigned short day;
    unsigned short month;
    unsigned short year;
};

struct Position {
    unsigned short code;
    std::string title;
};

struct Worker {
    unsigned short personal_code;
    std::string name;
    unsigned short position_code;
    Date employment;
};

#endif

