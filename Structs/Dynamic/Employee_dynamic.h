#ifndef __EMPLOYEE_DYNAMIC_H
#define __EMPLOYEE_DYNAMIC_H

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
    Table(int n) : size(n) {
        data = new Worker[n];
    };
    int size;
    Worker* data;
};

#endif

