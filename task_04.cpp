/*
 * Задача № 4 (5 баллов)
 *
 * Даны неотрицательные целые числа n,k и массив целых чисел из [0..10^9] размера n.
 * Требуется найти k-ю порядковую статистику. т.е. напечатать число,
 *     которое бы стояло на позиции с индексом k (0..n-1) в отсортированном массиве.
 * Напишите нерекурсивный алгоритм.
 * Требования к дополнительной памяти: O(n).
 * Требуемое среднее время работы: O(n).
 * Функцию Partition следует реализовывать методом прохода двумя итераторами в одном направлении.
 *
 * 4_1.
 * Реализуйте стратегию выбора опорного элемента “медиана трёх”.
 * Функцию Partition реализуйте методом прохода двумя итераторами от начала массива к концу.
 */


#include <iostream>
#include <cassert>


int* MedianOfThree(int* array, int size) {
    int* left_elem = array;
    int* med_elem = array + size / 2;
    int* right_elem = array + size - 1;

    if (*left_elem <= *med_elem && *left_elem <= *right_elem) {  // left_elem | med_elem ? right_elem
        return *med_elem < *right_elem ? med_elem : right_elem;
    } else if (*med_elem <= *left_elem && *med_elem <= *right_elem) {  // med_elem | left_elem ? right_elem
        return *left_elem < *right_elem ? left_elem : right_elem;
    } else if (*right_elem <= *left_elem && *right_elem <= *med_elem) {  // right_elem | left_elem ? med_elem
        return *left_elem < *med_elem ? left_elem : med_elem;
    }

    assert(false);
}

void Partition(int* array, int size, int*& pivot) {
    std::swap(*(array + size - 1), *pivot);
    int pivotValue = *(array + size - 1);

    int i = 0;
    for (int j = 0; j < size - 1; j++) {
        if (*(array + j) <= pivotValue) {
            std::swap(*(array + i), *(array + j));
            i++;
        }
    }

    std::swap(*(array + i), *(array + size - 1));
    pivot = array + i;
}

int KStatDC(int* array_original, int size, int k) {
    int *array = array_original;
    const int k_original = k;

    int *pivot;
    int pivotIdx;

    while (true) {
        pivot = MedianOfThree(array, size);
        Partition(array, size, pivot);
        pivotIdx = pivot - array;

        if (pivotIdx == k) {
            return *(array_original + k_original);
        } else if (k < pivotIdx) {
            size = pivotIdx;
        } else {
            array += pivotIdx + 1;
            size -= pivotIdx + 1;
            k -= pivotIdx + 1;
        }
    }
}

int main() {
    int n, k;
    std::cin >> n >> k;

    int *data = new int[n];
    for (int i = 0; i < n; i++) {
        std::cin >> data[i];
    }

    std::cout << KStatDC(data, n, k) << std::endl;

    delete[] data;
    return 0;
}
