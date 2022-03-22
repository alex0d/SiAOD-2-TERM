#ifndef __EMPLOYEE_H
#define __EMPLOYEE_H

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

struct Table {
    Table(int n) : size(n) {};
    int size;
    const static int max_size = 100;
    Worker data[max_size];
};

#endif

