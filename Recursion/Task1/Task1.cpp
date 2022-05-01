#include <iostream>

int recursion_max(int* array, int size, int i = 0) {
    if (i == size - 1) {
        return array[i];
    }
    int t = recursion_max(array, size, i + 1);
    return array[i] > t ? array[i] : t;
}

int main() {
    int n;
    std::cout << "Введите размер массива: ";
    std::cin >> n;

    std::cout << "Введите элементы массива: ";
    int* array = new int[n];
    for (int i = 0; i < n; i++) {
        std::cin >> array[i];
    }

    std::cout << "Максимальное число: " << recursion_max(array, n);

    delete[] array;
    return 0;
}