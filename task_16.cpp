/*
 * Задача 16. Поиск подстроки (5 баллов)
 * Вариант 2. С помощью z-функции.
 *
 * Формат входного файла
 * Шаблон, символ перевода строки, строка.
 *
 * Формат выходного файла
 * Позиции вхождения шаблона в строке.
 */


#include <iostream>
#include <vector>


std::vector<int> substring_search(const std::string& pattern, const std::string& text) {
    const int PATTERN_LENGTH = pattern.size();
    const int TEXT_LENGTH = text.size();

    std::vector<int> z_values(PATTERN_LENGTH, 0);
    z_values[0] = PATTERN_LENGTH;
    int l = 0;
    int r = 0;

    // итерация по паттерну
    for (int i = 1; i < PATTERN_LENGTH; i++) {
        if (i >= r || z_values[i - l] + i == r) {
            z_values[i] = i >= r ? 0 : z_values[i - l];

            bool is_changed = false;
            while (i + z_values[i] < PATTERN_LENGTH && pattern[i + z_values[i]] == pattern[z_values[i]]) {
                z_values[i]++;
                is_changed = true;
            }

            if (is_changed) {
                l = i;
                r = i + z_values[i];
            }
        } else if (z_values[i - l] + i > r) {
            z_values[i] = r - i;
        } else {
            z_values[i] = z_values[i - l];
        }
    }

    l = 0;
    r = 0;
    std::vector<int> output;

    // итерация по тексту
    for (int i = 0; i < TEXT_LENGTH; i++) {
        if (i >= r || z_values[i - l] + i == r) {
            int matching_length = i >= r ? 0 : z_values[i - l];

            bool is_changed = false;
            while (matching_length < PATTERN_LENGTH
                    && i + matching_length < TEXT_LENGTH
                    && text[i + matching_length] == pattern[matching_length]) {
                matching_length++;
                is_changed = true;
            }

            if (is_changed) {
                l = i;
                r = i + matching_length;
            }

            if (matching_length == PATTERN_LENGTH) {
                output.push_back(i);
            }
        }
    }

    return output;
}


int main() {
    std::string pattern, text;
    std::cin >> pattern >> text;

    std::vector<int> answer = substring_search(pattern, text);
    for (const auto& x : answer) {
        std::cout << x << " ";
    }

    return 0;
}
