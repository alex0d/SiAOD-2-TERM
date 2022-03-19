#include <iostream>
#include <string.h>
#include <Windows.h> 

using namespace std;

void splitSentence(char* str);
void lastLetterToBegin(char* word);
bool isLetterInWord(char c, char* word, int before);
void removeDuplicateLetter(char* word);

int main()
{
    SetConsoleOutputCP(1251); // Задаём кодировку вывода консоли
    SetConsoleCP(1251); // Задаём кодировку ввода консоли
    cout << "Работа #3 Строки. Денисов А.В. ИКБО-03-21. Вариант 7\n\n";
    char sentence[1024];
    cout << "Введите предложение: ";
    gets_s(sentence);
    splitSentence(sentence);
    return 0;
}

void splitSentence(char* str) {
    char word[32];
    int i = 0;  // Для прохода по предложения
    int j; // Для слова 
    while (str[i] != '\0') {
        while (str[i] == ' ' || str[i] == ',' || str[i] == '.' || str[i] == '?') {
            i++;
        }
        if (str[i] == '\0') {
            return;
        }
        j = 0; // Начинаем записывать слово
        while (str[i] != '\0' && str[i] != ' ' && str[i] != ',' && str[i] != '.' && str[i] != '?') {
            word[j] = str[i];
            i++;
            j++;
        }
        word[j] = '\0';
        lastLetterToBegin(word);
        removeDuplicateLetter(word);
        puts(word);
        if (str[i] == '\0') {
            return;
        }
        i++;
    }
}

void lastLetterToBegin(char* word) {
    char last = word[strlen(word) - 1];
    for (int i = strlen(word) - 2; i >= 0; i--) {
        word[i + 1] = word[i];
    }
    word[0] = last;
}

bool isLetterInWord(char c, char* word, int before) {
    for (int i = 0; i < before; i++) {
        if (word[i] == c) {
            return true;
        }
    }
    return false;
}

void removeDuplicateLetter(char* word) {
    int new_index = 0;
    for (int cur_index = 0; cur_index < strlen(word); cur_index++) {
        if (!isLetterInWord(word[cur_index], word, new_index)) {
            word[new_index] = word[cur_index];
            new_index++;
        }
    }
    word[new_index] = '\0';
}