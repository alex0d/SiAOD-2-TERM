#include <iostream>

struct Node {
    int data;
    Node* next;
};

void addNode(Node* &head, int data) {
    if (!head) {
        // Исходная очередь была пустая.
        head = new Node{data, nullptr};
        return;
    }

    if (!head->next) {
        head->next = new Node{data, nullptr};
        return;
    }
    addNode(head->next, data);
}

void removeNode(Node* &head) {
    if (!head) {
        // В качестве параметра был передан nullptr.
        return;
    }

    if (!head->next) {
        delete head;
        head = nullptr;
        return;
    }
    Node* tmp = head->next;
    delete head;
    head = tmp;
}

void printQueue(const Node* head) {
    if (!head) {
        return;
    }
    std::cout << head->data << " ";
    printQueue(head->next);
};

void deleteQueue(Node* &head) {
    if (!head) {
        return;
    }
    deleteQueue(head->next);
    delete head;
    head = nullptr;
}

int main() {
    setlocale(LC_ALL, "Russian");

    Node* head = nullptr;
    int n, new_data;
    std::cout << "Введите размер очереди: ";
    std::cin >> n;

    std::cout << "Введите числа, записываемые в очередь: ";
    for (int i = 0; i < n; i++) {
        std::cin >> new_data;
        addNode(head, new_data);
    }

    int cmd = 1;
    std::cout << "1 - Добавить элемент в очередь;\n" <<
                 "2 - Удалить элемент из очереди;\n" <<
                 "3 - Печать текущий очереди;\n" <<
                 "4 - Очистить всю очередь\n";
    while (cmd) {
        std::cout << "Введите команду: ";
        std::cin >> cmd;
        switch (cmd) {
            case 1:
                std::cout << "Введите число: ";
                std::cin >> new_data;
                addNode(head, new_data);
                std::cout << "Элемент добавлен." << std::endl;
                break;

            case 2:
                removeNode(head);
                std::cout << "Первый элемент удалён." << std::endl;
                break;

            case 3:
                printQueue(head);
                std::cout << std::endl;
                break;

            case 4:
                deleteQueue(head);
                std::cout << "Очередь очищена." << std::endl;
                break;

            default:
                std::cout << "Нет такой команды." << std::endl;
                break;
        }
    }
    deleteQueue(head);
    return 0;
}