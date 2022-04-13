#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next;
};

// Создаёт список, вставляя каждое введеное значение перед первым узлом.
void createList(Node* &head);

// Выводит список в консоль.
void printList(Node* head);

// Возвращает true, если в списке содержится два и более одинаковых элемента. Иначе false.
bool consistsEquals(Node* head);

// Удаляет из списка максимальное значение.
// Если содержится несколько одинаковых максимальных значений, удаляется первое вхождение.
bool deleteMax(Node* &head);

// Вставляет в список новое значение перед каждым узлом в четной позиции.
void insertBeforeEveryEven(Node* &head, int n);

int main()
{
    setlocale(LC_ALL, "Russian");

    Node* head = nullptr;
    int n;

    cout << "Введите числа (0 - конец ввода): ";
    createList(head);
    cout << "Создан список: ";
    printList(head);
    
    cout << "\n\n0 - Выход;\n1 - Печать списка;\n" <<
        "2 - Проверить, есть ли в списке одинаковые элементы;\n" <<
        "3 - Удалить из списка максимальное значение;\n" <<
        "4 - Вставить в список новое значение перед каждым узлом в четной позиции.\n";

    int cmd = 1;
    while (cmd) {
        cout << "\nВведите команду: ";
        cin >> cmd;
        switch (cmd) {
        case 1:
            cout << "Список: ";
            printList(head);
            cout << endl;
            break;

        case 2:
            if (consistsEquals(head)) {
                cout << "В списке есть одинаковые элементы." << endl;
            }
            else {
                cout << "В списке нет одинаковых элементов." << endl;
            }
            break;

        case 3:
            if (deleteMax(head)) {
                cout << "Максимальное значение удалено." << endl;
            }
            else {
                cout << "После удаления максимального значения список пуст." << endl;
                return 0;
            }
            break;

        case 4:
            cout << "Введите новое значение: ";
            cin >> n;
            insertBeforeEveryEven(head, n);
            cout << "Значение вставлено." << endl;
            break;
            
        default:
            break;
        }
    }
}

void createList(Node* &head) {
    int n;
    while (cin >> n && n != 0) {
        head = new Node{ n, head };
    }
}

void printList(Node* head) {
    Node* current = head;
    while (current) {
        cout << current->data << " ";
        current = current->next;
    }
}

bool consistsEquals(Node* head) {
    Node* current = head;
    Node* runner;
    while (current) {
        runner = current->next;
        while (runner) {
            if (runner->data == current->data) {
                return true;
            }
            runner = runner->next;
        }
        current = current->next;
    }
    return false;
}

bool deleteMax(Node* &head) {
    Node* max_node = head;
    Node* current = head;
    while (current) {
        if (current->data > max_node->data) {
            max_node = current;
        }
        current = current->next;
    }

    if (head == max_node) {
        head = head->next;
        delete max_node;
        if (head) {
            return true;
        }
        return false;
    }

    current = head;
    while (current) {
        if (current->next == max_node) {
            current->next = max_node->next;
            delete max_node;
            return true;
        }
        current = current->next;
    }
}

void insertBeforeEveryEven(Node* &head, int n) {
    head = new Node{ n, head };
    Node* current = head->next;
    int next_index = 1;
    while (current->next) {
        if (next_index % 2 == 0) {
            current->next = new Node{ n, current->next };
            current = current->next;
        }
        current = current->next;
        next_index++;
    }
}