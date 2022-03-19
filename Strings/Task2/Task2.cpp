#include <iostream>
#include <string>
#include <Windows.h> 

using namespace std;

void splitSentence(string str);
void lastLetterToBegin(string& word);
void removeDuplicateLetter(string& word);

int main()
{
    SetConsoleOutputCP(1251); // Задаём кодировку вывода консоли
    SetConsoleCP(1251); // Задаём кодировку ввода консоли
    cout << "Работа #3 Строки. Денисов А.В. ИКБО-03-21. Вариант 7\n\n";
    string sentence;
    cout << "Введите предложение: ";
    getline(cin, sentence);
    splitSentence(sentence);
    return 0;
}

void splitSentence(string str) {
    string word = "";
    int i = 0;  // Для прохода по предложения
    while (str[i] != '\0') {
        while (str[i] == ' ' || str[i] == ',' || str[i] == '.' || str[i] == '?') {
            i++;
        }
        if (str[i] == '\0') {
            return;
        }
        word.erase(); // Начинаем записывать слово
        while (str[i] != '\0' && str[i] != ' ' && str[i] != ',' && str[i] != '.' && str[i] != '?') {
            word += str[i];
            i++;
        }
        lastLetterToBegin(word);
        removeDuplicateLetter(word);
        cout << word << endl;
        if (str[i] == '\0') {
            return;
        }
        i++;
    }
}

void lastLetterToBegin(string& word) {
    char last = word[word.length() - 1];
    for (int i = word.length() - 2; i >= 0; i--) {
        word[i + 1] = word[i];
    }
    word[0] = last;
}

void removeDuplicateLetter(string& word) {
    int new_index = 0;
    for (int cur_index = 0; cur_index < word.length(); cur_index++) {
        if (word.find(word[cur_index]) >= new_index) {
            word[new_index] = word[cur_index];
            new_index++;
        }
    }
    word.erase(new_index, word.length() - new_index);
}