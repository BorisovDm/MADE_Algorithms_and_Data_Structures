/*
 * Задача 8. Хеш-таблица (10 баллов)
 *
 * Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы с открытой адресацией.
 * Хранимые строки непустые и состоят из строчных латинских букв.
 * Хеш-функция строки должна быть реализована с помощью вычисления значения многочлена методом Горнера.
 * Начальный размер таблицы должен быть равным 8-ми.
 * Перехеширование выполняйте при добавлении элементов в случае, когда коэффициент заполнения таблицы достигает 3/4.
 * Структура данных должна поддерживать операции добавления строки в множество,
 * удаления строки из множества и проверки принадлежности данной строки множеству.
 *
 * 8_2. Для разрешения коллизий используйте двойное хеширование.
 *
 * Формат входных данных
 * Каждая строка входных данных задает одну операцию над множеством.
 * Запись операции состоит из типа операции и следующей за ним через пробел строки, над которой проводится операция.
 * Тип операции  – один из трех символов:
 *     +  означает добавление данной строки в множество;
 *     -  означает удаление  строки из множества;
 *     ?  означает проверку принадлежности данной строки множеству.
 * При добавлении элемента в множество НЕ ГАРАНТИРУЕТСЯ, что он отсутствует в этом множестве.
 * При удалении элемента из множества НЕ ГАРАНТИРУЕТСЯ, что он присутствует в этом множестве.
 *
 * Формат выходных данных
 * Программа должна вывести для каждой операции одну из двух строк OK или FAIL.
 * Для операции '?': OK, если элемент присутствует во множестве. FAIL иначе.
 * Для операции '+': FAIL, если добавляемый элемент уже присутствует во множестве и потому не может быть добавлен. OK иначе.
 * Для операции '-': OK, если элемент присутствовал во множестве и успешно удален. FAIL иначе.
 */


#include <iostream>
#include <string>
#include <vector>

#define HASH_TABLE_SIZE 8
#define HASH_BASE_1 3343
#define HASH_BASE_2 2861
#define HASH_MODULE 4294967296 // 2^32


struct Hasher {
    unsigned int operator()(const std::string& str, unsigned int base) const {
        unsigned int hashValue = 0;
        for (const auto& x : str) {
            hashValue = (hashValue * base + x) % HASH_MODULE;
        }
        return hashValue;
    }
};

class HashTable {
public:
    explicit HashTable(int initial_size, const Hasher& _hasher);
    ~HashTable();

    HashTable(const HashTable&) = delete;
    HashTable(HashTable&&) = delete;
    HashTable& operator=(const HashTable&) = delete;
    HashTable& operator=(HashTable&&) = delete;

    bool Has(const std::string& key) const;
    bool Add(const std::string& key);
    bool Remove(const std::string& key);

private:
    std::vector<std::string> table;
    std::vector<bool> isDeleted;

    Hasher hasher;
    void Rehash();
    unsigned int filledNodesNumber = 0;
    unsigned int getHashCode(const std::string&) const;
    unsigned int getHashStep(const std::string&) const;
};

HashTable::HashTable(int initial_size, const Hasher& _hasher) :
    table(initial_size, ""), isDeleted(initial_size, false), hasher(_hasher) {}

HashTable::~HashTable() {}

unsigned int HashTable::getHashCode(const std::string& key) const {
    return hasher(key, HASH_BASE_1);
}

unsigned int HashTable::getHashStep(const std::string& key) const {
    return (2 * hasher(key, HASH_BASE_2) + 1);
}

bool HashTable::Remove(const std::string& key) {
    unsigned int hashCode = getHashCode(key);
    unsigned int hashStep = getHashStep(key);
    unsigned int index = hashCode % table.size();

    while (table[index] != "" or isDeleted[index]) {
        if (table[index] == key) {
            table[index] = "";
            isDeleted[index] = true;
            return true;
        }
        index = (index + hashStep) % table.size();
    }
    return false;
}

bool HashTable::Has(const std::string& key) const {
    unsigned int hashCode = getHashCode(key);
    unsigned int hashStep = getHashStep(key);
    unsigned int index = hashCode % table.size();

    while (table[index] != "" or isDeleted[index]) {
        if (table[index] == key) {
            return true;
        }
        index = (index + hashStep) % table.size();
    }
    return false;
}

bool HashTable::Add(const std::string& key) {
    unsigned int hashCode = getHashCode(key);
    unsigned int hashStep = getHashStep(key);
    unsigned int index = hashCode % table.size();
    int freeIndexToInsert = -1;

    while (table[index] != "" or isDeleted[index]) {
        if (table[index] == key) {
            return false;
        }

        if (isDeleted[index] && freeIndexToInsert < 0) {
            freeIndexToInsert = index;
        }

        index = (index + hashStep) % table.size();
    }

    if (freeIndexToInsert >= 0) {
        table[freeIndexToInsert] = key;
        isDeleted[freeIndexToInsert] = false;
    } else {
        table[index] = key;
        filledNodesNumber++;
    }

    if (4 * filledNodesNumber >= 3 * table.size()) {
        Rehash();
    }
    return true;
}

void HashTable::Rehash() {
    std::vector<std::string> oldTable = table;
    table = std::vector<std::string>(oldTable.size() * 2, "");
    isDeleted = std::vector<bool>(oldTable.size() * 2, false);
    filledNodesNumber = 0;

    for (const auto& key : oldTable) {
        if (key != "") {
            Add(key);
        }
    }
}


int main() {
    Hasher hasher;
    HashTable table(HASH_TABLE_SIZE, hasher);
    char command = ' ';
    std::string value;

    while (std::cin >> command >> value) {
        switch (command) {
            case '?':
                std::cout << (table.Has(value) ? "OK" : "FAIL") << std::endl;
                break;
            case '+':
                std::cout << (table.Add(value) ? "OK" : "FAIL") << std::endl;
                break;
            case '-':
                std::cout << (table.Remove(value) ? "OK" : "FAIL") << std::endl;
                break;
        }
    }

    return 0;
}
