#include <iostream>
#include <chrono>

// Сортировка выбором.
void selection_sort(int arr[], int n) {
    int min_index;

    for (int i = 0; i < n - 1; i++) {
        min_index = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }
        if (min_index != i) {
            std::swap(arr[min_index], arr[i]);
        }
    }
}


// Построение двоичной кучи поддерева с корнем i.
void heapify(int arr[], int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest]) {
        largest = l;
    }

    if (r < n && arr[r] > arr[largest]) {
        largest = r;
    }

    if (largest != i)
    {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

// Пирамидальная сортировка.
void heap_sort(int arr[], int n)
{
    // Строим двоичную кучу (снизу вверх).
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    for (int i = n - 1; i >= 0; i--)
    {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}


// Слияние подмассивов [left, mid] и [mid + 1, right]
void merge(int arr[], int left, int mid, int right)
{
    int left_arr_size = mid - left + 1;
    int right_arr_size = right - mid;

    int* left_arr = new int[left_arr_size];
    int* right_arr = new int[right_arr_size];

    memcpy(left_arr, arr + left, left_arr_size * sizeof(int));
    memcpy(right_arr, arr + mid + 1, right_arr_size * sizeof(int));

    int left_arr_index = 0;
    int right_arr_index = 0;
    int merged_arr_index = left;

    // Слияние подмассивов обратно в массив [left, right]
    while (left_arr_index < left_arr_size && right_arr_index < right_arr_size) {
        if (left_arr[left_arr_index] <= right_arr[right_arr_index]) {
            arr[merged_arr_index] = left_arr[left_arr_index];
            left_arr_index++;
        }
        else {
            arr[merged_arr_index] = right_arr[right_arr_index];
            right_arr_index++;
        }
        merged_arr_index++;
    }

    // Копирование оставшихся в подмассиве left_arr элементов
    // обратно в [left, right]
    while (left_arr_index < left_arr_size) {
        arr[merged_arr_index] = left_arr[left_arr_index];
        left_arr_index++;
        merged_arr_index++;
    }

    // Копирование оставшихся в подмассиве right_arr элементов
    // обратно в [left, right]
    while (right_arr_index < right_arr_size) {
        arr[merged_arr_index] = right_arr[right_arr_index];
        right_arr_index++;
        merged_arr_index++;
    }

    delete[] left_arr;
    delete[] right_arr;
}

void merge_sort(int arr[], int begin, int end)
{
    if (begin >= end) {
        return;
    }

    int mid = begin + (end - begin) / 2;
    merge_sort(arr, begin, mid);
    merge_sort(arr, mid + 1, end);
    merge(arr, begin, mid, end);
}

void fill_random(int* arr, int n) {
    std::srand(time(nullptr));
    for (int i = 0; i < n; i++) {
        arr[i] = std::rand() % 100;
    }
}

void fill_decreasing(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = n - i;
    }
}

void fill_increasing(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = 1 + i;
    }
}

void print_arr(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    int* arr;
    int n, cmd;
    std::cout << "Введите размер массива: ";
    std::cin >> n;
    arr = new int[n];

    std::cout << "1 - Заполнение псевдослучайными числами;\n"
                 "2 - Заполнение в строго убывающем порядке;\n"
                 "3 - Заполнение в строго возрастающем порядке.\n"
                 "Выберите пункт меню: ";
    std::cin >> cmd;
    switch (cmd) {
        case 1:
            fill_random(arr, n);
            break;
        case 2:
            fill_decreasing(arr, n);
            break;
        case 3:
            fill_increasing(arr, n);
            break;
        default:
            delete[] arr;
            exit(0);
    }
    print_arr(arr, n);

    std::cout << std::endl;
    std::cout << "1 - Сортировка выбором;\n"
                 "2 - Пирамидальная сортировка;\n"
                 "3 - Сортировка слиянием.\n"
                 "Выберите пункт меню: ";
    std::cin >> cmd;
    auto start = std::chrono::high_resolution_clock::now();
    switch (cmd) {
        case 1:
            selection_sort(arr, n);
            break;
        case 2:
            heap_sort(arr, n);
            break;
        case 3:
            merge_sort(arr, 0, n - 1);
            break;
        default:
            delete[] arr;
            exit(0);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float, std::milli> duration = end - start;
    print_arr(arr, n);
    std::cout << "Время сортировки: " << duration.count() << " ms";

    delete[] arr;
    return 0;
}