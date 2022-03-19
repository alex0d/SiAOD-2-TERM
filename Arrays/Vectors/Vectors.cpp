#include <iostream>
#include <vector>

using namespace std;

void fillVector(vector<int> &v);

void printVector(vector<int> &v);

// Ищет элемент, цифровой корень которого равен 7.
// Возвращает индекс первого такого числа. -1, если не найдено.
int findElem(vector<int> &v);

// Вставляет новый элемент перед элементом, цифровой корень которого равен 7.
// Возвращает 0 при успехе, иначе -1.
int insertElem(int elem, vector<int> &v);

// Удаляет из массива все элементы, цифровой корень которых равен 7.
void deleteElems(vector<int> &v);

// Возвращает цифровой корень числа.
int digitalRoot(int x);

int main()
{
    setlocale(LC_ALL, "Russian");
    cout << "Работа #1 Одномерный массив. Денисов А.В. ИКБО-03-21. Вариант 7\n\n";
    int n;
    cout << "Введите размер массива: ";
    cin >> n;
    if (n < 1) {
        cout << "Введено неверное значение размера массива." << endl;
        return 1;
    }
    vector<int> v(n);
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
            fillVector(v);
            break;

        case 2:
            cout << "Массив: " << endl;
            printVector(v);
            break;

        case 3:
            index = findElem(v);
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
            if (insertElem(new_element, v) != -1) {
                cout << "Элемент вставлен успешно." << endl;
            }
            else {
                cout << "Произошла ошибка. Элемент не был вставлен." << endl;
            }
            break;

        case 5:
            deleteElems(v);
            cout << "Элементы удалены." << endl;
            break;

        default:
            break;
        }
    }
}

void fillVector(vector<int> &v) {
    for (int i = 0; i < v.size(); i++) {
        cin >> v.at(i);
    }
}

void printVector(vector<int> &v) {
    for (int i = 0; i < v.size(); i++) {
        cout << v.at(i) << " ";
    }
    cout << endl;
}

int findElem(vector<int> &v) {
    for (int i = 0; i < v.size(); i++) {
        if (digitalRoot(v.at(i)) == 7) {
            return i;
        }
    }
    return -1;
}

int insertElem(int elem, vector<int> &v) {
    int dr7_index = findElem(v);
    if (dr7_index == -1) {
        return -1;
    }
    v.insert(v.begin() + dr7_index, elem);
    return 0;
}

void deleteElems(vector<int> &v) {
    vector<int>::iterator Iter = v.begin();
    while (Iter != v.end()) {
        if (digitalRoot(*Iter) == 7) {
            Iter = v.erase(Iter);
        }
        else {
            Iter++;
        }

        if (v.empty()) {
            cout << "Удалены все элементы массива.";
            exit(0);
        }
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