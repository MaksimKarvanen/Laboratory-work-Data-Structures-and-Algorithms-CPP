#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <type_traits>
#include <cstdlib>
#include <memory>
#include <chrono>

class ArrayBase {
public:
    virtual ~ArrayBase() {}
    virtual void display() const = 0;
    virtual void selectAlgorithm(int choice) = 0;
    virtual size_t getSize() const = 0;
};

template <typename T>
class Array : public ArrayBase {
    std::vector<T> arr;
public:
    Array(std::vector<T> a) : arr(std::move(a)) {}
    void display() const override {
        for (const auto& i : arr) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }
    void selectAlgorithm(int choice) override;
    size_t getSize() const override { return arr.size(); }
    std::vector<T>& get() { return arr; }
};

template <typename T>
void swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

int getMaxAbs(const std::vector<int>& arr) {
    int n = arr.size();
    int mx = std::abs(arr[0]);
    for (int i = 1; i < n; i++) {
        if (std::abs(arr[i]) > mx) {
            mx = std::abs(arr[i]);
        }
    }
    return mx;
}

template <typename T>
int partition(std::vector<T>& arr, int low, int high) {
    T pivot = arr[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

template <typename T>
void merge(std::vector<T>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    std::vector<T> L(n1);
    std::vector<T> R(n2);
    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }
    int i = 0;
    int j = 0;
    int k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

template <typename T>
void selectionSort(std::vector<T>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            swap(arr[i], arr[minIndex]);
        }
    }
}

template <typename T>
void bubbleSort(std::vector<T>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
}

template <typename T>
void insertionSort(std::vector<T>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        T key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

template <typename T>
void quickSort(std::vector<T>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

template <typename T>
void recursionMergeSort(std::vector<T>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        recursionMergeSort(arr, left, mid);
        recursionMergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

template <typename T>
void iterativeMergeSort(std::vector<T>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i *= 2) {
        for (int j = 0; j < n - 1; j += 2 * i) {
            merge(arr, j, j + i - 1, std::min(j + 2 * i - 1, n - 1));
        }
    }
}

template <typename T>
void shellSort(std::vector<T>& arr) {
    int n = arr.size();
    for (int gap = n / 2; gap > 0; gap = gap / 2) {
        for (int i = gap; i < n; ++i) {
            T temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}


void radixSortLSD(std::vector<int>& arr) {
    int n = arr.size();
    int m = getMaxAbs(arr);
    for (int exp = 1; m / exp > 0; exp *= 10) {
        std::vector<int> output(n);
        int i;
        std::vector<int> count(10, 0);
        for (i = 0; i < n; i++) {
            count[(std::abs(arr[i]) / exp) % 10]++;
        }
        for (i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }
        for (i = n - 1; i >= 0; i--) {
            output[count[(std::abs(arr[i]) / exp) % 10] - 1] = arr[i];
            count[(std::abs(arr[i]) / exp) % 10]--;
        }
        for (i = 0; i < n; i++) {
            arr[i] = output[i];
        }
    }
    // Sign pass
    {
        std::vector<int> output(n);
        int i;
        std::vector<int> count(10, 0);
        for (i = 0; i < n; i++) {
            int digit = (arr[i] < 0 ? 0 : 1);
            count[digit]++;
        }
        int neg_count = count[0];
        for (i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }
        for (i = n - 1; i >= 0; i--) {
            int digit = (arr[i] < 0 ? 0 : 1);
            output[count[digit] - 1] = arr[i];
            count[digit]--;
        }
        for (i = 0; i < n; i++) {
            arr[i] = output[i];
        }
        // Reverse the negatives
        for (i = 0; i < neg_count / 2; i++) {
            int temp = arr[i];
            arr[i] = arr[neg_count - 1 - i];
            arr[neg_count - 1 - i] = temp;
        }
    }
}

template <bool IsInt>
struct RadixHelper {
    template <typename U>
    void operator()(std::vector<U>&) {
        std::cout << "Radix Sort LSD не поддерживается для этого типа!" << std::endl;
    }
};

template <>
struct RadixHelper<true> {
    void operator()(std::vector<int>& arr) {
        radixSortLSD(arr);
    }
};

template <typename T>
void Array<T>::selectAlgorithm(int choice) {
    std::vector<T>& arr = get();
    int n = arr.size();
    switch (choice) {
    case 1: {
        std::cout << "Выбран Selection Sort" << std::endl;
        auto start = std::chrono::high_resolution_clock::now();
        selectionSort(arr);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end - start;
        std::cout << "Время выполнения: " << elapsed.count() << " мс" << std::endl;
        break;
    }
    case 2: {
        std::cout << "Выбран Bubble Sort" << std::endl;
        auto start = std::chrono::high_resolution_clock::now();
        bubbleSort(arr);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end - start;
        std::cout << "Время выполнения: " << elapsed.count() << " мс" << std::endl;
        break;
    }
    case 3: {
        std::cout << "Выбран Insertion Sort" << std::endl;
        auto start = std::chrono::high_resolution_clock::now();
        insertionSort(arr);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end - start;
        std::cout << "Время выполнения: " << elapsed.count() << " мс" << std::endl;
        break;
    }
    case 4: {
        std::cout << "Выбран Quick Sort" << std::endl;
        auto start = std::chrono::high_resolution_clock::now();
        quickSort(arr, 0, n - 1);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end - start;
        std::cout << "Время выполнения: " << elapsed.count() << " мс" << std::endl;
        break;
    }
    case 5: {
        std::cout << "Выбран Recursive Merge Sort" << std::endl;
        auto start = std::chrono::high_resolution_clock::now();
        recursionMergeSort(arr, 0, n - 1);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end - start;
        std::cout << "Время выполнения: " << elapsed.count() << " мс" << std::endl;
        break;
    }
    case 6: {
        std::cout << "Выбран Iterative Merge Sort" << std::endl;
        auto start = std::chrono::high_resolution_clock::now();
        iterativeMergeSort(arr);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end - start;
        std::cout << "Время выполнения: " << elapsed.count() << " мс" << std::endl;
        break;
    }
    case 7: {
        std::cout << "Выбран Shell Sort" << std::endl;
        auto start = std::chrono::high_resolution_clock::now();
        shellSort(arr);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end - start;
        std::cout << "Время выполнения: " << elapsed.count() << " мс" << std::endl;
        break;
    }
    case 8: {
        std::cout << "Выбран Radix Sort LSD" << std::endl;
        auto start = std::chrono::high_resolution_clock::now();
        RadixHelper<std::is_same<T, int>::value>()(arr);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end - start;
        std::cout << "Время выполнения: " << elapsed.count() << " мс" << std::endl;
        break;
    }
    case 9: {
        std::cout << "Выбран Lexicographic Sort" << std::endl;
        if (!std::is_same<T, std::string>::value) {
            std::cout << "Lexicographic sort is only for strings!" << std::endl;
            return;
        }
        auto start = std::chrono::high_resolution_clock::now();
        quickSort(arr, 0, n - 1);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end - start;
        std::cout << "Время выполнения: " << elapsed.count() << " мс" << std::endl;
        break;
    }
    default:
        std::cout << "Неверный выбор алгоритма!" << std::endl;
        return;
    }
}

std::vector<double> readArrayFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Ошибка открытия файла!" << std::endl;
        return {};
    }

    std::vector<double> temp;
    double num;
    while (file >> num) {
        temp.push_back(num);
    }

    file.close();
    return temp;
}

std::vector<std::string> readStringsFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Ошибка открытия файла!" << std::endl;
        return {};
    }

    std::vector<std::string> temp;
    std::string str;
    while (file >> str) {
        temp.push_back(str);
    }

    file.close();
    return temp;
}

void showMenu() {
    std::cout << "\n=== МЕНЮ ВЫБОРА СОРТИРОВКИ ===" << std::endl;
    std::cout << "1. Selection Sort" << std::endl;
    std::cout << "2. Bubble Sort" << std::endl;
    std::cout << "3. Insertion Sort" << std::endl;
    std::cout << "4. Quick Sort" << std::endl;
    std::cout << "5. Recursive Merge Sort" << std::endl;
    std::cout << "6. Iterative Merge Sort" << std::endl;
    std::cout << "7. Shell Sort" << std::endl;
    std::cout << "8. Radix Sort LSD" << std::endl;
    std::cout << "9. Lexicographic Sort" << std::endl;
    std::cout << "0. Выход" << std::endl;
    std::cout << "Выберите алгоритм сортировки: ";
}

void showDataSourceMenu() {
    std::cout << "\n=== ВЫБОР ИСТОЧНИКА ДАННЫХ ===" << std::endl;
    std::cout << "1. Случайный массив" << std::endl;
    std::cout << "2. Предзаписанный массив" << std::endl;
    std::cout << "3. Данные из файла (погода)" << std::endl;
    std::cout << "4. Ввести свой массив" << std::endl;
    std::cout << "5. Данные из файла (строки)" << std::endl;
    std::cout << "Выберите источник данных: ";
}

std::unique_ptr<ArrayBase> selectDataSource(int choice) {
    switch (choice) {
    case 1: {
        int size;
        std::cout << "Введите размер случайного массива: ";
        std::cin >> size;
        std::string type;
        std::cout << "Введите тип (int, double, char, string): ";
        std::cin >> type;
        if (type == "int") {
            std::vector<int> arr(size);
            for (auto& i : arr) {
                i = rand() % (10000 - (-10000) + 1) + (-10000);
            }
            return std::make_unique<Array<int>>(arr);
        } else if (type == "double") {
            std::vector<double> arr(size);
            for (auto& d : arr) {
                d = (rand() / static_cast<double>(RAND_MAX)) * (10000.0 - (-10000.0)) + (-10000.0);
            }
            return std::make_unique<Array<double>>(arr);
        } else if (type == "char") {
            std::vector<char> arr(size);
            for (auto& c : arr) {
                c = 'a' + rand() % 26;
            }
            return std::make_unique<Array<char>>(arr);
        } else if (type == "string") {
            std::vector<std::string> arr(size);
            for (auto& s : arr) {
                int len = rand() % 10 + 1;
                for (int k = 0; k < len; k++) {
                    s += 'a' + rand() % 26;
                }
            }
            return std::make_unique<Array<std::string>>(arr);
        } else {
            std::cout << "Неверный тип! Используется int." << std::endl;
            std::vector<int> arr(size);
            for (auto& i : arr) {
                i = rand() % (10000 - (-10000) + 1) + (-10000);
            }
            return std::make_unique<Array<int>>(arr);
        }
    }
    case 2: {
        std::cout << "Выберите предзаписанный массив (1-3): ";
        int arrChoice;
        std::cin >> arrChoice;
        std::vector<int> arr1 = {64, 25, 12, 22, 3, 0};
        std::vector<int> arr2 = {68, 21, 8, 22, 0, -1, -31, -12};
        std::vector<double> arr3 = {1, -4, 0.23, 4.34, 4.3, -2.2, -2.24};
        switch (arrChoice) {
        case 1: return std::make_unique<Array<int>>(arr1);
        case 2: return std::make_unique<Array<int>>(arr2);
        case 3: return std::make_unique<Array<double>>(arr3);
        default:
            std::cout << "Неверный выбор массива! Используется массив 1." << std::endl;
            return std::make_unique<Array<int>>(arr1);
        }
    }
    case 3: {
        std::string filename;
        std::cout << "Введите имя файла: ";
        std::cin >> filename;
        return std::make_unique<Array<double>>(readArrayFromFile(filename));
    }
    case 4: {
        std::string type;
        std::cout << "Введите тип (int, double, char, string): ";
        std::cin >> type;
        int size;
        std::cout << "Введите размер массива: ";
        std::cin >> size;
        if (type == "int") {
            std::vector<int> arr(size);
            for (int i = 0; i < size; i++) {
                std::cout << "Введите элемент " << i + 1 << ": ";
                std::cin >> arr[i];
            }
            return std::make_unique<Array<int>>(arr);
        } else if (type == "double") {
            std::vector<double> arr(size);
            for (int i = 0; i < size; i++) {
                std::cout << "Введите элемент " << i + 1 << ": ";
                std::cin >> arr[i];
            }
            return std::make_unique<Array<double>>(arr);
        } else if (type == "char") {
            std::vector<char> arr(size);
            for (int i = 0; i < size; i++) {
                std::cout << "Введите элемент " << i + 1 << ": ";
                std::cin >> arr[i];
            }
            return std::make_unique<Array<char>>(arr);
        } else if (type == "string") {
            std::vector<std::string> arr(size);
            for (int i = 0; i < size; i++) {
                std::cout << "Введите элемент " << i + 1 << ": ";
                std::cin >> arr[i];
            }
            return std::make_unique<Array<std::string>>(arr);
        } else {
            std::cout << "Неверный тип!" << std::endl;
            return nullptr;
        }
    }
    case 5: {
        std::string filename = "lexicographic.txt";
        return std::make_unique<Array<std::string>>(readStringsFromFile(filename));
    }
    default:
        std::cout << "Неверный выбор источника данных! Используется случайный массив." << std::endl;
        std::vector<int> arr(10);
        for (auto& i : arr) {
            i = rand() % (10000 - (-10000) + 1) + (-10000);
        }
        return std::make_unique<Array<int>>(arr);
    }
}

int main() {
    srand(static_cast<unsigned>(time(0)));

    int algorithmChoice, dataChoice;

    while (true) {
        showMenu();
        std::cin >> algorithmChoice;

        if (algorithmChoice == 0) {
            break;
        }

        showDataSourceMenu();
        std::cin >> dataChoice;

        auto array_var = selectDataSource(dataChoice);

        if (!array_var || array_var->getSize() == 0) {
            std::cout << "Ошибка получения данных!" << std::endl;
            continue;
        }

        std::cout << "\nИсходный массив: ";
        array_var->display();

        array_var->selectAlgorithm(algorithmChoice);

        std::cout << "Отсортированный массив: ";
        array_var->display();

        std::cout << "\nНажмите Enter для продолжения...";
        std::cin.ignore();
        std::cin.get();
    }

    std::cout << "Программа завершена." << std::endl;

    return 0;
}