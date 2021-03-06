#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <Windows.h>
#include "Employee_vector.h"

using namespace std;

// Справочник по должностям
Position positions[5] = { {1, "Cleaner"},
                          {2, "Programmer"},
                          {3, "Project manager"},
                          {4, "The useless one"},
                          {5, "CEO"} };

// Возвращает код должности по её названию. Возвращает 0, если переданной должности не существует.
unsigned short getPositionCodeByTitle(string title);

// Создаёт нового сотрудника, сохраняя его данные в переданную запись.
void createWorker(Worker& note);

// Вставляет сотрудника так, чтобы запись разместилась после последней записи с такой же должностью.
void insertWorkerByPosition(vector<Worker>& table);

// Возвращает индекс последнего работника с переданной занимаемой должностью.
int findLastNoteWithRequiredPosition(int pos, const vector<Worker>& table);

// Заменяет у всех сотрудников код заданной должности на новый код.
// Возвращает true при успехе, иначе false.
bool changePositions(vector<Worker>& table, string old_pos_title, string new_pos_title);

// Удаляет из таблицы всех сотрудников с заданной должностью. Уменьшает размер таблицы.
// Возвращает true при успехе, иначе false.
bool fireWorkersByPosition(vector<Worker>& table, string pos_title);

// Выводит таблицу сотрудников в консоль.
void showTable(const vector<Worker>& table);

int main()
{
    SetConsoleOutputCP(1251); // Задаём кодировку вывода консоли.
    SetConsoleCP(1251); // Задаём кодировку ввода консоли.

    int n; // Текущее количество записей о сотрудниках.
    cout << "Введите количество записей о сотрудниках: ";
    cin >> n;
    vector<Worker> table(n); // Таблица: записи о сотрудниках.

    for (int i = 0; i < n; i++) {
        cout << "\nЗаполнение данных сотрудника #" << i << "...\n";
        createWorker(table.at(i));
    }
    cout << "Таблица заполнена." << endl;

    cout << "\n0 - Выход;\n" <<
        "1 - Показать таблицу с сотрудниками;\n" <<
        "2 - Вставить в таблицу сведения о новом сотруднике;\n" <<
        "3 - Перевести всех сотрудников с заданной должности на другую;\n" <<
        "4 - Удалить всех сотрудников с заданной должностью.\n";
    string old_pos_title, new_pos_title;
    int cmd;
    while (true) {
        cout << "\nВведите команду: ";
        cin >> cmd;
        switch (cmd)
        {
        case (1): // Показать таблицу с сотрудниками.
            cout << " Табельный номер |     Фамилия И.О.     | Код занимаемой должности | Дата поступления на работу \n";
            showTable(table);
            break;

        case (2): // Вставить в таблицу сведения о новом сотруднике.
            cout << "Введите данные о новом сотруднике..." << endl;
            insertWorkerByPosition(table);
            cout << "Запись о новом сотруднике вставлена в таблицу." << endl;
            break;

        case(3): // Перевести всех сотрудников с заданной должности на другую.
            cout << "Введите старую должность: ";
            cin.seekg(cin.eof());
            getline(cin, old_pos_title);

            cout << "Введите новую должность: ";
            cin.seekg(cin.eof());
            getline(cin, new_pos_title);

            if (changePositions(table, old_pos_title, new_pos_title)) {
                cout << "Сотрудники переведены на новую должность." << endl;
            }
            else {
                cout << "Произошла ошибка. Должности не изменены." << endl;
            }
            break;

        case (4): // Удалить всех сотрудников с заданной должностью.
            cout << "Введите должность, всех сотрудников с которой надо уволить: ";
            cin.seekg(cin.eof());
            getline(cin, old_pos_title);

            if (fireWorkersByPosition(table, old_pos_title)) {
                cout << "Все сотрудники с этой должностью были уволены." << endl;
            }
            else {
                cout << "Произошла ошибка: должность не найдена." << endl;
            }
            break;

        default:
            return 0;
        }
    }
}

unsigned short getPositionCodeByTitle(string title) {
    for (Position pos : positions) {
        if (pos.title == title) {
            return pos.code;
        }
    }
    return 0;
}

void createWorker(Worker& note) {
    cout << "Табельный номер: ";
    cin >> note.personal_code;
    cout << "Фамилия И. О.: ";
    cin.seekg(cin.eof());
    getline(cin, note.name);
    cout << "Код занимаемой должности: ";
    cin >> note.position_code;
    cout << "Дата поступления на работу (дд мм гггг): ";
    cin >> skipws >> note.employment.day >> note.employment.month >> note.employment.year;
}

void insertWorkerByPosition(vector<Worker>& table) {
    int n = table.size();
    table.resize(++n);

    Worker new_note;
    createWorker(new_note);

    int last = findLastNoteWithRequiredPosition(new_note.position_code, table);
    if (last == -1) {
        last = n - 2;
    }

    for (int i = last + 1; i < n - 1; i++) {
        table.at(i + 1) = table.at(i);
    }
    table.at(last + 1) = new_note;
}

int findLastNoteWithRequiredPosition(int pos, const vector<Worker>& table) {
    for (int i = table.size() - 1; i >= 0; i--) {
        if (table.at(i).position_code == pos) {
            return i;
        }
    }
    return -1;
}

bool changePositions(vector<Worker>& table, string old_pos_title, string new_pos_title) {
    unsigned short old_pos = getPositionCodeByTitle(old_pos_title);
    unsigned short new_pos = getPositionCodeByTitle(new_pos_title);
    if (old_pos == 0 || new_pos == 0) {
        return false;
    }
    for (int i = 0; i < table.size(); i++) {
        if (table.at(i).position_code == old_pos) {
            table.at(i).position_code = new_pos;
        }
    }
    return true;
}

bool fireWorkersByPosition(vector<Worker>& table, string pos_title) {
    unsigned short pos = getPositionCodeByTitle(pos_title);
    if (pos == 0) {
        return false;
    }

    int new_n = 0;
    for (int i = 0; i < table.size(); i++) {
        if (table.at(i).position_code != pos) {
            table.at(new_n) = table.at(i);
            new_n++;
        }
    }
    table.resize(new_n);
    return true;
}

void showTable(const vector<Worker>& table) {
    for (int i = 0; i < table.size(); i++) {
        cout << "       " << setw(3) << setfill('0') << right << table.at(i).personal_code << "       |";
        cout << setw(floor((22.0 - table.at(i).name.size()) / 2)) << setfill(' ') << "";
        cout << setw(22 - floor((22.0 - table.at(i).name.size()) / 2)) << left << table.at(i).name << "|";
        cout << "            " << setw(2) << setfill('0') << right << table.at(i).position_code << "            |";
        cout << "        " << setw(2) << setfill('0') << table.at(i).employment.day << ".";
        cout << setw(2) << setfill('0') << table.at(i).employment.month << "." << table.at(i).employment.year << "        ";
        cout << endl;
    }
}