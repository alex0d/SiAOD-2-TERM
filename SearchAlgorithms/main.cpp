#include <iostream>
#include <string>
#include <iomanip>
#include <chrono>

struct Specialization {
    int code;
    std::string name;
};

const std::string universities[] = {"MIREA", "Polytech", "MSU", "BMSTU", "HSE", "MEPhI"};

// Заполнение таблицы случайными записями с уникальными ключами.
void create_random_entries(Specialization* table, int n) {
    int nums_size = n;
    int* nums = new int[nums_size];
    for (int i = 0; i < n; i++) {
        nums[i] = i + 1;
    }
    int index;
    for (int i = 0; i < n; i++) {
        index = rand() % nums_size;
        table[i].code = nums[index];
        table[i].name = universities[rand() % 6];
        nums[index] = nums[nums_size - 1];
        nums_size--;
    }

    delete[] nums;
}

// Заполнение таблицы записями, отсортированными по ключам.
// Стараемся сделать не слишком равномерное распределение.
void create_ascending_entries(Specialization* table, int n) {
    table[0].code = 1;
    table[0].name = universities[rand() % 6];

    for (int i = 1; i < n; i++) {
        int x = -1;
        while (x < table[i - 1].code) {
            x = rand() % 100 * i;
        }
        table[i].code = x;
        table[i].name = universities[rand() % 6];
    }
}

// Линейный поиск (bruteforce)
int linear_search(Specialization* table, int n, int key) {
    for (int i = 0; i < n; i++) {
        if (table[i].code == key) {
            return i;
        }
    }
    return -1;
}

// Поиск с барьером
int linear_search_with_barrier(Specialization* table, int n, int key) {
    if (table[n - 1].code == key) {
        return n - 1;
    }

    table[n - 1].code = key;
    int i = 0;
    while (table[i].code != key) {
        i++;
    }
    if (i != n + 1){
        return i;
    }
    return -1;
}

// Интерполяционный поиск
int interpolation_search(Specialization* table, int n, int key) {
    int mid;
    int left = 0;
    int right = n - 1;

    while (table[left].code < key && table[right].code > key) {
        if (table[right].code == table[left].code) {
            break;
        }
        mid = left + (((long long)key - table[left].code) * (right - left)) / (table[right].code - table[left].code);

        if (table[mid].code < key) {
            left = mid + 1;
        }
        else if (table[mid].code > key) {
            right = mid - 1;
        }
        else {
            return mid;
        }
    }

    if (table[left].code == key) {
        return left;
    }
    if (table[right].code == key) {
        return right;
    }

    return -1;
}

void print_table(Specialization* table, int n) {
    std::cout << std::setw(6) << "Code";
    std::cout << std::setw(15) << "University" << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << std::setw(6) << table[i].code;
        std::cout << std::setw(15) << table[i].name << std::endl;
    }
}

int main() {
    srand(time(nullptr));

    int n = 10; // Количество записей
    int key = 213; // Поиск ключа
    Specialization* table = new Specialization[n];
    create_ascending_entries(table, n);
    print_table(table, n);

    auto start = std::chrono::high_resolution_clock::now();
    interpolation_search(table, n, key);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<float, std::milli> duration = end - start;
    std::cout << "Время поиска: " << duration.count() << " ms";

    delete[] table;
    return 0;
}
