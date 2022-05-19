#include <cstring>
#include "Stack.h"

Stack::Stack() : array(nullptr), size(0) { };

Stack::~Stack() {
    delete array;
    array = nullptr;
    size = 0;
}

void Stack::resize(int new_size) {
    int* new_array = new int[new_size];
    if (new_size > size) {
        std::memcpy(new_array, array, sizeof(int) * size);
    }
    else {
        std::memcpy(new_array, array, sizeof(int) * new_size);
    }
    delete array;

    array = new_array;
    size = new_size;
}

void Stack::push(int item) {
    resize(size + 1);
    array[size - 1] = item;
}

int Stack::pop() {
    int top_value = array[size - 1];
    resize(size - 1);
    return top_value;
}