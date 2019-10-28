/*
 * Задача № 2 (5 баллов)
 * Решение всех задач данного раздела предполагает использование кучи.
 *
 * 2_2. Быстрое сложение.
 * Для сложения чисел используется старый компьютер.
 * Время, затрачиваемое на нахождение суммы двух чисел равно их сумме.
 * Таким образом для нахождения суммы чисел 1,2,3 может потребоваться разное время, в зависимости от порядка вычислений.
 *
 * ((1+2)+3) -> 1+2 + 3+3 = 9
 * ((1+3)+2) -> 1+3 + 4+2 = 10
 * ((2+3)+1) -> 2+3 + 5+1 = 11
 *
 * Требуется написать программу, которая определяет минимальное время,
 * достаточное для вычисления суммы заданного набора чисел.
 *
 * Формат входных данных.
 * Вначале вводится n - количество чисел.
 * Затем вводится n строк - значения чисел (значение каждого числа не превосходит 10^9,
 * сумма всех чисел не превосходит 2*10^9).
 *
 * Формат выходных данных.
 * Натуральное число - минимальное время.
 */


#include <cassert>
#include <iostream>
#include <vector>

void Swap(int& a, int& b) {
    int tmp = a;
    a = b;
    b = tmp;
}

class Heap {  // use min Heap
public:
    Heap();
    explicit Heap(const std::vector<int>& init_values);
    int ExtractTop();
    int GetTop();
    int GetSize();
    void Push(int data);

private:
    void Heapify();
    void SiftUp(int idx);
    void SiftDown(int idx);
    std::vector<int> values;
};

Heap::Heap() {}

Heap::Heap(const std::vector<int>& init_values) {
    values.assign(init_values.begin(), init_values.end());
    Heapify();
}

void Heap::Push(int data) {
    values.push_back(data);
    SiftUp(GetSize() - 1);
}

int Heap::GetSize() {
    return values.size();
}

int Heap::GetTop() {
    assert(GetSize() > 0);
    return values[0];
}

int Heap::ExtractTop() {
    int return_value = values[0];
    values[0] = values.back();
    values.pop_back();
    SiftDown(0);

    return return_value;
}

void Heap::Heapify() {
    // last element have index GetSize() - 1
    // it's parent index is (GetSize() - 1 - 1) / 2 => GetSize() / 2 - 1
    for (int i = GetSize() / 2 - 1; i >= 0; i--) {
        SiftDown(i);
    }
}

void Heap::SiftUp(int idx) {
    while (idx > 0) {  // while not root
        int parent_idx = (idx - 1) / 2;
        if (values[idx] < values[parent_idx]) {
            Swap(values[parent_idx], values[idx]);
            idx = parent_idx;
        } else {
            return;
        }
    }
}

void Heap::SiftDown(int idx) {
    int left_child_idx, right_child_idx;
    bool is_left_child_exist, is_right_child_exist;

    while (true) {
        left_child_idx = 2 * idx + 1;
        right_child_idx = 2 * idx + 2;
        is_left_child_exist = left_child_idx < GetSize();
        is_right_child_exist = right_child_idx < GetSize();

        if (!is_left_child_exist) {
            return;
        }

        if (values[left_child_idx] < values[idx]) {
            if ( (!is_right_child_exist) || (values[left_child_idx] <= values[right_child_idx]) ) {
                Swap(values[left_child_idx], values[idx]);
                idx = left_child_idx;
                continue;
            }
        }

        if ( (is_right_child_exist) && (values[right_child_idx] < values[idx]) ) {
            Swap(values[right_child_idx], values[idx]);
            idx = right_child_idx;
            continue;
        }

        return;
    }
}


int main() {
    int n_numbers;
    std::cin >> n_numbers;

    std::vector<int> data(n_numbers);
    for (int& x : data) {
        std::cin >> x;
    }
    Heap min_heap(data);

    int total_time = 0;
    while (min_heap.GetSize() > 1) {
        int new_value = min_heap.ExtractTop() + min_heap.ExtractTop();
        total_time += new_value;
        min_heap.Push(new_value);
    }

    std::cout << total_time;

    return 0;
}
