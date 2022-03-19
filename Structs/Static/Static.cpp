﻿#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>
#include "Employee.h"

using namespace std;

// Максимальный размер таблицы (массив сотрудников).
const int N = 100;

// Справочник по должностям
position positions[5] = { {1, "Cleaner"},
                          {2, "Programmer"},
                          {3, "Project manager"},
                          {4, "The useless one"},
                          {5, "CEO"} };

// Создаёт нового сотрудника, сохраняя его данные в переданную запись.
void createWorker(worker& note);

// Добавляет сотрудника в таблицу, изменяет её размер. Возвращает true при успехе, иначе false.
bool addWorkerToTable(worker* table, const worker& note, int& n);

// Вставляет сотрудника так, чтобы запись разместилась после последней записи с такой же должностью.
// Возвращает true при успехе, иначе false.
bool insertWorkerByPosition(worker* table, const worker& note, int& n);

// Возвращает код должности по её названию. Возвращает 0, если переданной должности не существует.
unsigned short getPositionCodeByTitle(string title);

// Возвращает индекс последнего работника с переданной занимаемой должностью.
int findLastNoteWithRequiredPosition(int pos, const worker* table, int n);

// Заменяет у всех сотрудников код заданной должности на новый код.
// Возвращает true при успехе, иначе false.
bool changePositions(worker* table, int n, string old_pos_title, string new_pos_title);

// Удаляет из таблицы всех сотрудников с заданной должностью. Уменьшает размер таблицы.
// Возвращает true при успехе, иначе false.
bool fireWorkersByPosition(worker* table, int& n, string pos_title);

// Выводит таблицу сотрудников в консоль.
void showTable(const worker* table, int n);

int main()
{
    SetConsoleOutputCP(1251); // Задаём кодировку вывода консоли.
    SetConsoleCP(1251); // Задаём кодировку ввода консоли.
    
    int n = 0; // Текущее количество записей о сотрудниках.
    worker table[N]; // Таблица: записи о сотрудниках.
    
    int input_n;
    cout << "Введите количество записей о сотрудниках: ";
    cin >> input_n;
    if (input_n > N) {
        cout << "Количество записей не может быть больше 100.";
        return 1;
    }

    worker new_note;
    for (int i = 0; i < input_n; i++) {
        cout << "\nЗаполнение данных сотрудника #" << i << "...\n";
        createWorker(new_note);
        addWorkerToTable(table, new_note, n);
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
            showTable(table, n);
            break;
        
        case (2): // Вставить в таблицу сведения о новом сотруднике.
            cout << "Введите данные о новом сотруднике..." << endl;
            createWorker(new_note);
            if (insertWorkerByPosition(table, new_note, n)) {
                cout << "Запись о новом сотруднике вставлена в таблицу." << endl;
            } else {
                cout << "Невозможно вставить запись в таблицу." << endl;
            }
            break;

        case(3): // Перевести всех сотрудников с заданной должности на другую.
            cout << "Введите старую должность: ";
            cin.seekg(cin.eof());
            getline(cin, old_pos_title);

            cout << "Введите новую должность: ";
            cin.seekg(cin.eof());
            getline(cin, new_pos_title);

            if (changePositions(table, n, old_pos_title, new_pos_title)) {
                cout << "Сотрудники переведены на новую должность." << endl;
            } else {
                cout << "Произошла ошибка. Должности не изменены." << endl;
            }
            break;

        case (4): // Удалить всех сотрудников с заданной должностью.
            cout << "Введите должность, всех сотрудников с которой надо уволить: ";
            cin.seekg(cin.eof());
            getline(cin, old_pos_title);

            if (fireWorkersByPosition(table, n, old_pos_title)) {
                cout << "Все сотрудники с этой должностью были уволены." << endl;
            } else {
                cout << "Произошла ошибка: должность не найдена." << endl;
            }
            break;

        default:
            return 0;
        }
    }
}

void createWorker(worker& note) {
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

bool addWorkerToTable(worker* table, const worker& note, int& n) {
    if (n + 1 > N) {
        return false;
    }
    table[n] = note;
    n++;
    return true;
}

bool insertWorkerByPosition(worker* table, const worker& note, int& n) {
    if (n + 1 > N) {
        return false;
    }
    int pos = findLastNoteWithRequiredPosition(note.position_code, table, n);
    if (pos == -1) {
        return addWorkerToTable(table, note, n);
    }
    for (int i = pos + 1; i < n; i++) {
        table[i + 1] = table[i];
    }
    table[pos + 1] = note;
    n++;
    return true;
}

unsigned short getPositionCodeByTitle(string title) {
    for (position pos : positions) {
        if (pos.title == title) {
            return pos.code;
        }
    }
    return 0;
}

int findLastNoteWithRequiredPosition(int pos, const worker* table, int n) {
    for (int i = n - 1; i >= 0; i--) {
        if (table[i].position_code == pos) {
            return i;
        }
    }
    return -1;
}

bool changePositions(worker* table, int n, string old_pos_title, string new_pos_title) {
    unsigned short old_pos = getPositionCodeByTitle(old_pos_title);
    unsigned short new_pos = getPositionCodeByTitle(new_pos_title);
    if (old_pos == 0 || new_pos == 0) {
        return false;
    }
    for (int i = 0; i < n; i++) {
        if (table[i].position_code == old_pos) {
            table[i].position_code = new_pos;
        }
    }
    return true;
}

bool fireWorkersByPosition(worker* table, int& n, string pos_title) {
    unsigned short pos = getPositionCodeByTitle(pos_title);
    if (pos == 0) {
        return false;
    }
    int new_n = 0;
    for (int i = 0; i < n; i++) {
        if (table[i].position_code != pos) {
            table[new_n] = table[i];
            new_n++;
        }
    }
    n = new_n;
    return true;
}

void showTable(const worker* table, int n) {
    for (int i = 0; i < n; i++) {
        cout << "       " << setw(3) << setfill('0') << right << table[i].personal_code << "       |";
        cout << setw(floor((22.0 - table[i].name.size()) / 2)) << setfill(' ') << "";
        cout << setw(22 - floor((22.0 - table[i].name.size()) / 2)) << left << table[i].name << "|";
        cout << "            " << setw(2) << setfill('0') << right << table[i].position_code << "            |";
        cout << "        " << setw(2) << setfill('0') << table[i].employment.day << ".";
        cout << setw(2) << setfill('0') << table[i].employment.month << "." << table[i].employment.year << "        ";
        cout << endl;
    }
}