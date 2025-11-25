#include <iostream>
#include <list>
#include <vector>
#include <cmath>
#include <functional>

using namespace std;

template<typename K, typename V>
class Node {
public:
    K key;
    V value;
    Node(K key, V value) : key(key), value(value) {}
};

const int capacity = 100;

// Простая хэш функция
template<typename K>
int simpleHashFunction(K key) {
    int hashValue = 0;
    string str = to_string(key);
    for (char ch : str) {
        hashValue += ch;
    }
    return hashValue % capacity;
}

// Специализация для string
template<>
int simpleHashFunction<string>(string key) {
    int hashValue = 0;
    for (char ch : key) {
        hashValue += ch;
    }
    return hashValue % capacity;
}

// Метод квадратичных остатков
template<typename K>
int quadraticResidueHashing(K key) {
    const int p = 101;
    int hash = 0;
    vector<int> coefficients = {2, 3, 5, 7, 11, 13, 17, 19};
    string str = to_string(key);

    for (size_t i = 0; i < str.length(); i++) {
        int coef = coefficients[i % coefficients.size()];
        int charValue = str[i];
        hash = (hash + coef * charValue * charValue) % p;
    }
    return hash % capacity;
}

// Специализация для string
template<>
int quadraticResidueHashing<string>(string key) {
    const int p = 101;
    int hash = 0;
    vector<int> coefficients = {2, 3, 5, 7, 11, 13, 17, 19};

    for (size_t i = 0; i < key.length(); i++) {
        int coef = coefficients[i % coefficients.size()];
        int charValue = key[i];
        hash = (hash + coef * charValue * charValue) % p;
    }
    return hash % capacity;
}

// Простая побитовая XOR
template<typename K>
int simpleFunctionXOR(K key) {
    int hash = 0;
    string str = to_string(key);
    for (char ch : str) {
        hash ^= static_cast<int>(ch);
    }
    return abs(hash) % capacity;
}

// Специализация для string
template<>
int simpleFunctionXOR<string>(string key) {
    int hash = 0;
    for (char ch : key) {
        hash ^= ch;
    }
    return abs(hash) % capacity;
}

template<typename K, typename V>
class HashTable {
private:
    list<Node<K, V>>* table;
    int capacity;
    int size;
    function<int(K)> hashFunction;

public:
    HashTable(int capacity, function<int(K)> hash) :
        capacity(capacity), size(0), hashFunction(hash) {
        table = new list<Node<K, V>>[capacity];
    }

    HashTable() : capacity(0), size(0), table(nullptr) {}

    ~HashTable() {
        delete[] table;
    }

    void insert(K key, V value) {
        int index = this->hashFunction(key) % capacity;
        Node<K, V> new_node(key, value);
        table[index].push_back(new_node);
        this->size++;
    }
    void erase(K key) {
        int index = this->hashFunction(key) % capacity;
        table[index].remove_if([&](Node<K, V>& el) { return el.key == key; });
        this->size--;
    }
    V get(K key)
    {
        int index = hashFunction(key) % capacity;
        for (auto& el : table[index]) {
            if (el.key == key) {
                return el.value;
            }
        }
        std::cout << "Ключ не найден.\n";
        return V();
    }
};

int main() {
    // Создаем хэш-таблицы с разными хэш-функциями
    HashTable<string, int> table1(capacity, simpleHashFunction<string>);
    HashTable<string, int> table2(capacity, quadraticResidueHashing<string>);
    HashTable<string, int> table3(capacity, simpleFunctionXOR<string>);

    // Тестируем первую хэш-таблицу (простая сумма)
    cout << "=== Тест простой хэш-функции (сумма) ===" << endl;
    table1.insert("apple", 10);
    table1.insert("banana", 20);
    table1.insert("orange", 30);

    cout << "apple: " << table1.get("apple") << endl;
    cout << "banana: " << table1.get("banana") << endl;
    cout << "orange: " << table1.get("orange") << endl;

    // Удаляем элемент
    table1.erase("banana");
    cout << "После удаления banana: " << table1.get("banana") << endl;

    // Тестируем вторую хэш-таблицу (квадратичные остатки)
    cout << "\n=== Тест квадратичных остатков ===" << endl;
    table2.insert("cat", 100);
    table2.insert("dog", 200);
    table2.insert("bird", 300);

    cout << "cat: " << table2.get("cat") << endl;
    cout << "dog: " << table2.get("dog") << endl;
    cout << "bird: " << table2.get("bird") << endl;

    // Тестируем третью хэш-таблицу (XOR)
    cout << "\n=== Тест XOR хэш-функции ===" << endl;
    table3.insert("hello", 1);
    table3.insert("world", 2);
    table3.insert("test", 3);

    cout << "hello: " << table3.get("hello") << endl;
    cout << "world: " << table3.get("world") << endl;
    cout << "test: " << table3.get("test") << endl;

    // Тест с коллизиями
    cout << "\n=== Тест коллизий ===" << endl;
    HashTable<string, string> table4(capacity, simpleHashFunction<string>);
    table4.insert("abc", "value1");
    table4.insert("acb", "value2");
    table4.insert("bac", "value3");

    cout << "abc: " << table4.get("abc") << endl;
    cout << "acb: " << table4.get("acb") << endl;
    cout << "bac: " << table4.get("bac") << endl;

    // Тест с целочисленными ключами
    cout << "\n=== Тест с целыми числами ===" << endl;
    HashTable<int, string> table5(capacity, simpleHashFunction<int>);

    for (int i = 0; i < 10; i++) {
        table5.insert(i, "Value_" + to_string(i));
    }

    for (int i = 0; i < 10; i++) {
        cout << "Ключ " << i << ": " << table5.get(i) << endl;
    }

    return 0;
}