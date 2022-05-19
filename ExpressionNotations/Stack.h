#pragma once

class Stack {
private:
    int* array;
    int size;

    // Changes the stack size to new_size.
    void resize(int new_size);

public:
    // Constructor.
    Stack();

    // Destructor.
    ~Stack();

    // Pushes an item onto the top of this stack.
    void push(int item);

    // Removes the value at the top of this stack and returns that value.
    int pop();
};
