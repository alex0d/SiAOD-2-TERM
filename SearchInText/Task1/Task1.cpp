#include <iostream>
#include <string>
#include <vector>

std::vector<int> prefix_function (std::string s) {
    int n =  s.length();
    std::vector<int> pi(n);
    for (int i=1; i<n; ++i) {
        int j = pi[i-1];
        while ((j > 0) && (s[i] != s[j])) {
            j = pi[j - 1];
        }

        if (s[i] == s[j]) {
            ++j;
        }
        pi[i] = j;
    }
    return pi;
}

std::vector<int> KMP(const std::string& s, int begin, const std::string& pattern)
{
    std::vector<int> pf = prefix_function(pattern);

    std::vector<int> occurrences;
    for (int k = 0, i = begin; i < s.length(); ++i)
    {
        while ((k > 0) && (pattern[k] != s[i])) {
            k = pf[k - 1];
        }

        if (pattern[k] == s[i]) {
            k++;
            if (k == pattern.length()) {
                occurrences.push_back(i - pattern.length() + 1);
                k = 0;
            }
        }
    }
    return occurrences;
}

int search_min_substring(std::string s) {
    int n = s.length();
    for (int start = 0; start < n - 1; start++) {
        for (int sub_len = 1; sub_len <= n; sub_len++) {
            std::vector<int> occurrences = KMP(s, start, s.substr(start, sub_len));
            if (occurrences.size() != (n - start) / sub_len) {
                continue;
            }
            bool is_suitable_sub = true;
            for (int i = 0; i < occurrences.size(); i++) {
                if (occurrences[i] != start + i * sub_len) {
                    is_suitable_sub = false;
                    continue;
                }
            }
            if (is_suitable_sub) {
                return sub_len;
            }
        }
    }
    return n;
}

int main() {
    std::string s;
    std::cout << "Введите строку: ";
    std::cin >> s;
    std::cout << "Минимальная длина S: " << search_min_substring(s) << std::endl;
    return 0;
}
