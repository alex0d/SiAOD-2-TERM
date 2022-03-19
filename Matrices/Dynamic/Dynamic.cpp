#include <iostream>
#include <iomanip>
#include <time.h>

using namespace std;

void fillMatrixByUser(int** matrix, int n);
void fillMatrixByRandom(int** matrix, int n);
void printMatrix(int** matrix, int n);
void printMatrixClockwise(int** matrix, int n);

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(0));
    cout << "Работа #2 Двумерный массив. Денисов А.В. ИКБО-03-21. Вариант 7\n\n";
    int n;
    cout << "Введите порядок квадратной матрицы: ";
    cin >> n;
    if (n < 1 || n > 1000) {
        cout << "Введено неверное значение размера массива." << endl;
        return 1;
    }

    int** matrix = new int* [n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new int[n];
    }

    cout << "Поддерживаемые команды:\n" <<
        "0 - Выход\n1 - Заполнить матрицу с клавиатуры\n" <<
        "2 - Заполнить матрицу случайными числами\n"
        "3 - Вывести матрицу на экран построчно\n" <<
        "4 - Вывести элементы матрицы, обходя её по часовой стрелке, начиная первой строки\n";
    int cmd = 1;
    while (cmd != 0) {
        cout << "\nВведите команду: ";
        cin >> cmd;
        switch (cmd) {
        case 1:
            cout << "Вводите элементы матрицы по строкам" << endl;
            fillMatrixByUser(matrix, n);
            break;

        case 2:
            fillMatrixByRandom(matrix, n);
            cout << "Заполненная матрица:" << endl;
            printMatrix(matrix, n);
            break;

        case 3:
            cout << "Заполненная матрица:" << endl;
            printMatrix(matrix, n);
            break;

        case 4:
            cout << "Элементы матрицы по часовой стрелке:" << endl;
            printMatrixClockwise(matrix, n);
            break;

        default:
            break;
        }
    }
    for (int i = 0; i < n; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
    return 0;
}

void fillMatrixByUser(int** matrix, int n) {
    for (int y = 0; y < n; y++) {
        for (int x = 0; x < n; x++) {
            cin >> matrix[y][x];
        }
    }
}

void fillMatrixByRandom(int** matrix, int n) {
    for (int y = 0; y < n; y++) {
        for (int x = 0; x < n; x++) {
            matrix[y][x] = rand() % 100;
        }
    }
}

void printMatrix(int** matrix, int n) {
    for (int y = 0; y < n; y++) {
        for (int x = 0; x < n; x++) {
            cout << setw(3) << left << matrix[y][x] << " ";
        }
        cout << endl;
    }
}

void printMatrixClockwise(int** matrix, int n) {
    for (int i = 0; i < n / 2; i++) {
        for (int x = i; x < n - 1 - i; x++) {
            cout << matrix[i][x] << " ";  // Верхняя строка
        }
        for (int y = i; y < n - 1 - i; y++) {
            cout << matrix[y][n - 1 - i] << " ";  // Правый столбец
        }
        for (int x = n - 1 - i; x > i; x--) {
            cout << matrix[n - 1 - i][x] << " ";  // Нижняя строка
        }
        for (int y = n - 1 - i; y > i; y--) {
            cout << matrix[y][i] << " ";  // Левый столбец
        }
    }
    if (n % 2 != 0) {
        cout << matrix[n / 2][n / 2];  // Элемент в центре матрицы нечетного порядка
    }
}