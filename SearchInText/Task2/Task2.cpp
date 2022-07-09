#include <iostream>
#include <string>
#include <vector>
#include <regex>

void check_passwords(std::vector<std::string> passwords) {
    std::regex pass_pattern("[a-zA-Z\\d]+");
    for (int i = 0; i < passwords.size(); i++) {
        if (regex_match(passwords[i], pass_pattern)) {
            std::cout << "Пароль " << passwords[i] << " корректный" << std::endl;
        }
        else {
            std::cout << "Пароль " << passwords[i] << " некорректный" << std::endl;
        }
    }
}

int main() {
    int n;
    std::cout << "Введите количество паролей: ";
    std::cin >> n;

    std::vector<std::string> passwords(n);
    std::cout << "Введите список паролей: ";
    for (int i = 0; i < n; i++) {
        std::cin >> passwords[i];
    }
    check_passwords(passwords);

    return 0;
}
