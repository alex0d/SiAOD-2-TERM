#include <iostream>

int recursion_max(int* array, int size, int i = 0) {
    if (i == size - 1) {
        return array[i];
    }
    return std::max(array[i], recursion_max(array, size, i + 1));
}

int main() {
    int n;
    std::cout << "Введите размер массива: ";
    std::cin >> n;

    int* array = new int[n];
    for (int i = 0; i < n; i++) {
        std::cin >> array[i];
    }

    std::cout << "Максимальное число: " << recursion_max(array, n);

    delete[] array;
    return 0;
}