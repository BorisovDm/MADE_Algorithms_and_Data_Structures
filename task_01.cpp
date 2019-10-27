/*
 * Задача № 1 (5 баллов)
 * Во всех задачах из следующего списка следует написать структуру данных, обрабатывающую команды push* и pop*.
 *
 * Формат входных данных.
 * В первой строке количество команд n. n ≤ 1000000.
 * Каждая команда задаётся как 2 целых числа: a b.
 * a = 1 - push front
 * a = 2 - pop front
 * a = 3 - push back
 * a = 4 - pop back
 * Для очереди используются команды 2 и 3. Для дека используются все четыре команды.
 * Если дана команда pop*, то число b - ожидаемое значение.
 * Если команда pop вызвана для пустой структуры данных, то ожидается “-1”.
 *
 * Формат выходных данных.
 * Требуется напечатать YES - если все ожидаемые значения совпали.
 * Иначе, если хотя бы одно ожидание не оправдалось, то напечатать NO.
 *
 * 1_3. Реализовать очередь с помощью двух стеков. Использовать стек, реализованный с помощью динамического буфера.
 */


#include <cassert>
#include <iostream>


class Stack {
public:
    Stack();
    ~Stack();

    bool IsEmpty();
    int Pop();
    void Push(int data);
    int Top();

private:
    int capacity;
    int* values = new int[capacity];
    int size;
};

Stack::Stack() : size(0), capacity(10) {}

Stack::~Stack() {
    delete[] values;
}

void Stack::Push(int data) {
    if (size == capacity) {
        capacity = capacity * 1.5 + 1;
        int *tmp_values = new int[capacity];
        for (int i = 0; i < size; i++) {
            tmp_values[i] = values[i];
        }

        delete[] values;
        values = tmp_values;
    }
    values[size++] = data;
}

int Stack::Pop() {
    assert(size > 0);

    int return_value = values[--size];

    int reduced_capacity = capacity / 1.5;
    if (size < reduced_capacity) {  // save 1 place for potential data additions
        capacity = reduced_capacity;
        int *tmp_values = new int[capacity];
        for (int i = 0; i < size; i++) {
            tmp_values[i] = values[i];
        }

        delete[] values;
        values = tmp_values;
    }

    return return_value;
}

bool Stack::IsEmpty() {
    return size == 0;
}

int Stack::Top() {
    assert(size > 0);
    return values[size - 1];
}

class Queue {
public:
    void Enqueue(int data);
    int Dequeue();
    bool IsEmpty();

private:
    Stack in_stack;
    Stack out_stack;
};

void Queue::Enqueue(int data) {
    in_stack.Push(data);
}

int Queue::Dequeue() {
    if (out_stack.IsEmpty()) {
        while (!in_stack.IsEmpty()) {
            out_stack.Push(in_stack.Pop());
        }
    }

    assert(!out_stack.IsEmpty());
    return out_stack.Pop();
}

bool Queue::IsEmpty() {
    return in_stack.IsEmpty() && out_stack.IsEmpty();
}


int main() {
    int n_commands, command_code, command_value;
    bool is_correct = true;
    Queue q;

    std::cin >> n_commands;
    for (int i = 0; i < n_commands; i++) {
        std::cin >> command_code >> command_value;
        assert(command_code == 2 || command_code == 3);

        if (command_code == 2) {  // pop front
            int returned_value = q.IsEmpty() ? -1 : q.Dequeue();
            if (command_value != returned_value) {
                is_correct = false;
                break;
            }
        } else {  // push back
            q.Enqueue(command_value);
        }
    }

    std::cout << (is_correct ? "YES" : "NO");
    return 0;
}
