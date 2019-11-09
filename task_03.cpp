/*
 * Задача № 3 (5 баллов)
 *
 * 3_3. Количество инверсий.
 * Дана последовательность целых чисел из диапазона (-10^9 .. 10^9).
 * Длина последовательности не больше 10^6. Числа записаны по одному в строке. Количество чисел не указано.
 *
 * Пусть количество элементов n, и числа записаны в массиве a = a[i]: i из [0..n-1].
 * Требуется напечатать количество таких пар индексов (i,j) из [0..n-1], что (i < j и a[i] > a[j]).
 *
 * Указание: количество инверсий может быть больше 4*10^9 - используйте int64_t.
 */


#include <iostream>
#include <vector>


std::pair<int*, int64_t> MergeAndCountInv(int* left, int* right, int left_size, int right_size) {
    int result_size = left_size + right_size;
    int *result = new int[result_size];
    int64_t n_inversions = 0;

    int i = 0;
    for (i = 0; i < result_size && left_size > 0 && right_size > 0; i++) {
        if (*left <= *right) {
            result[i] = *left++;
            left_size--;
        } else {
            result[i] = *right++;
            right_size--;
            n_inversions += left_size;
        }
    }

    if (left_size == 0 && right_size > 0) {
        std::copy(right, right + right_size, result + i);
    }

    if (right_size == 0 && left_size > 0) {
        std::copy(left, left + left_size, result + i);
    }

    return std::make_pair(result, n_inversions);
}


int main() {
    std::vector<int> data_vector;

    int input;
    while (std::cin >> input) {
        data_vector.push_back(input);
    }

    int n = data_vector.size();
    int* data = data_vector.data();

    int64_t n_inversions = 0;

    for (int merge_step = 1; merge_step < n; merge_step *= 2) {
        for (int i = 0; i < n; i += 2 * merge_step) {
            int left_start_idx = i;
            int left_end_idx = i + merge_step;

            if (left_end_idx >= n) {
                break;
            }

            int right_start_idx = i + merge_step;
            int right_end_idx = std::min(i + 2 * merge_step, n);

            auto [sorted_arr, n_inversions_tmp] = MergeAndCountInv(data + left_start_idx,
                    data + right_start_idx,
                    left_end_idx - left_start_idx,
                    right_end_idx - right_start_idx);
            n_inversions += n_inversions_tmp;

            std::copy(sorted_arr, sorted_arr + right_end_idx - left_start_idx, data + left_start_idx);
            delete[] sorted_arr;
        }
    }

    std::cout << n_inversions << std::endl;

    return 0;
}
