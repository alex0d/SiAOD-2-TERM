#include <iostream>

using namespace std;

void fillArray(int arr[], int n);

void printArray(int arr[], int n);

// Ищет элемент, цифровой корень которого равен 7.
// Возвращает индекс первого такого числа. -1, если не найдено.
int findElem(int arr[], int n);

// Вставляет новый элемент перед элементом, цифровой корень которого равен 7.
// Возвращает указатель на новый массив.
int* insertElem(int elem, int arr[], int* n);

// Удаляет из массивы все элементы, цифровой корень которых равен 7.
// Возвращает указатель на новый массив (может быть возвращен нулевой указатель).
int* deleteElems(int arr[], int* n);

// Возвращает цифровой корень числа.
int digitalRoot(int x);

int main()
{
    setlocale(LC_ALL, "Russian");
    cout << "Работа #1 Одномерный массив. Денисов А.В. ИКБО-03-21. Вариант 7\n\n";
    int n;
    cout << "Введите размер массива: ";
    cin >> n;
    if (n < 1 || n > 100000) {
        cout << "Введено неверное значение размера массива." << endl;
        return 1;
    }

    int* arr = (int*)malloc(n * sizeof(int));
    if (arr == NULL) {
        cout << "Ошибка распределения памяти.";
        return 1;
    }

    cout << "Поддерживаемые команды:\n" <<
        "0 - Выход\n1 - Заполнить массив\n2 - Отобразить массив\n" <<
        "3 - Найти индекс элемента массива, цифровой корень которого равен 7\n" <<
        "4 - Вставить новый элемент перед элементом, цифровой корень которого равен 7\n" <<
        "5 - Удалить элементы массива цифровой корень которых равен 7" << endl;
    int cmd = 1;
    int index;
    int new_element;
    while (cmd != 0) {
        cout << "\nВведите команду: ";
        cin >> cmd;
        switch (cmd) {
        case 1:
            cout << "Введите значения массива: ";
            fillArray(arr, n);
            break;

        case 2:
            cout << "Массив: " << endl;
            printArray(arr, n);
            break;

        case 3:
            index = findElem(arr, n);
            if (index != -1) {
                cout << "Индекс элемента, цифровой корень которого равен 7: " << index << endl;
            }
            else {
                cout << "Элемент, цифровой корень которого равен 7, не найден." << endl;
            }
            break;

        case 4:
            cout << "Введите новый элемент массива: ";
            cin >> new_element;
            arr = insertElem(new_element, arr, &n);
            cout << "Элемент вставлен." << endl;
            break;

        case 5:
            arr = deleteElems(arr, &n);
            cout << "Элементы удалены." << endl;
            break;

        default:
            break;
        }
    }
    free(arr);
}

void fillArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int findElem(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        if (digitalRoot(arr[i]) == 7) {
            return i;
        }
    }
    return -1;
}

int* insertElem(int elem, int arr[], int* n) {
    int dr7_index = findElem(arr, *n);
    if (dr7_index == -1) {
        return arr;
    }
    (*n)++;

    arr = (int*)realloc(arr, (*n) * sizeof(int));
    if (arr == NULL) {
        cout << "Произошла ошибка распределения памяти.";
        exit(1);
    }

    for (int i = *n - 1; i > dr7_index; i--) {
        arr[i] = arr[i - 1];
    }
    arr[dr7_index] = elem;
    return arr;
}

int* deleteElems(int arr[], int* n) {
    int i = 0;
    while (true) {
        if (digitalRoot(arr[i]) == 7) {
            for (int j = i; j < *n - 1; j++) {
                arr[j] = arr[j + 1];
            }
            (*n)--;
        }
        else {
            i++;
        }

        if (*n == 0) {
            cout << "Удалены все элементы массива.";
            exit(0);
        }

        if (i >= *n - 1) {
            break;
        }
    }
    arr = (int*)realloc(arr, (*n) * sizeof(int));
    if (arr == NULL) {
        cout << "Произошла ошибка распределения памяти.";
        exit(1);
    }
}

int digitalRoot(int x) {
    if (x == 0) {
        return 0;
    }
    int root = x % 9;
    if (root == 0) {
        return 9;
    }
    return root;
}