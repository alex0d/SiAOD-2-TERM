#ifndef __EMPLOYEE_H
#define __EMPLOYEE_H

#include <string>

struct date {
    unsigned short day;
    unsigned short month;
    unsigned short year;
};

struct position {
    unsigned short code;
    std::string title;
};

struct worker {
    unsigned short personal_code;
    std::string name;
    unsigned short position_code;
    date employment;
};

#endif

