#include <iostream>
#include <fstream>
#include <cstdlib>
#include <chrono>
#include <cstring>
#include <ctime>
#include <algorithm>
#include <limits>
#include <cmath>

const int MAX_SIZE = 100000;
const int MAX_STR_LEN = 256;

void swap_int(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

int getMaxAbs(const int arr[], int n) {
    if (n <= 0) return 0;
    int mx = std::abs(arr[0]);
    for (int i = 1; i < n; i++) {
        if (std::abs(arr[i]) > mx) {
            mx = std::abs(arr[i]);
        }
    }
    return mx;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap_int(arr[i], arr[j]);
        }
    }
    swap_int(arr[i + 1], arr[high]);
    return (i + 1);
}

void merge(int arr[], int left, int mid, int right) {
    if (left > mid || mid > right) return;
    int n1 = mid - left + 1;
    int n2 = right - mid;
    if (n1 <= 0 || n2 <= 0) return;

    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    delete[] L;
    delete[] R;
}

void selectionSort(int arr[], int n) {
    if (n <= 1) return;
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            swap_int(arr[i], arr[minIndex]);
        }
    }
}

void bubbleSort(int arr[], int n) {
    if (n <= 1) return;
    for (int i = 0; i < n - 1; ++i) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap_int(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

void insertionSort(int arr[], int n) {
    if (n <= 1) return;
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void recursionMergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        recursionMergeSort(arr, left, mid);
        recursionMergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void iterativeMergeSort(int arr[], int n) {
    if (n <= 1) return;
    for (int curr_size = 1; curr_size <= n - 1; curr_size *= 2) {
        for (int left_start = 0; left_start < n - 1; left_start += 2 * curr_size) {
            int mid = std::min(left_start + curr_size - 1, n - 1);
            int right_end = std::min(left_start + 2 * curr_size - 1, n - 1);
            if (mid < right_end) merge(arr, left_start, mid, right_end);
        }
    }
}

void shellSort(int arr[], int n) {
    if (n <= 1) return;
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; ++i) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

void radixSortLSD(int arr[], int n) {
    if (n <= 0) return;
    int m = getMaxAbs(arr, n);
    int* output = new int[n];
    for (int exp = 1; m / exp > 0; exp *= 10) {
        int count[10] = {0};
        for (int i = 0; i < n; i++) count[(std::abs(arr[i]) / exp) % 10]++;
        for (int i = 1; i < 10; i++) count[i] += count[i - 1];
        for (int i = n - 1; i >= 0; i--) {
            int idx = (std::abs(arr[i]) / exp) % 10;
            output[count[idx] - 1] = arr[i];
            count[idx]--;
        }
        for (int i = 0; i < n; i++) arr[i] = output[i];
    }

    int* out = new int[n];
    int count2[2] = {0, 0}; // 0 = negative, 1 = non-negative
    for (int i = 0; i < n; i++) count2[arr[i] < 0 ? 0 : 1]++;
    count2[1] += count2[0];
    for (int i = n - 1; i >= 0; i--) {
        int d = (arr[i] < 0) ? 0 : 1;
        out[count2[d] - 1] = arr[i];
        count2[d]--;
    }
    int neg_count = 0;
    for (int i = 0; i < n && out[i] < 0; ++i) neg_count++;
    for (int i = 0; i < neg_count / 2; i++) {
        int tmp = out[i];
        out[i] = out[neg_count - 1 - i];
        out[neg_count - 1 - i] = tmp;
    }
    for (int i = 0; i < n; i++) arr[i] = out[i];

    delete[] output;
    delete[] out;
}

void heapify(int arr[], int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < n && arr[l] > arr[largest]) largest = l;
    if (r < n && arr[r] > arr[largest]) largest = r;
    if (largest != i) {
        swap_int(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    if (n <= 1) return;
    for (int i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        swap_int(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

void swap_str(char a[], char b[]) {
    char temp[MAX_STR_LEN];
    std::strcpy(temp, a);
    std::strcpy(a, b);
    std::strcpy(b, temp);
}

int partition_str(char arr[][MAX_STR_LEN], int low, int high) {
    char pivot[MAX_STR_LEN];
    std::strcpy(pivot, arr[high]);
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (std::strcmp(arr[j], pivot) < 0) {
            i++;
            swap_str(arr[i], arr[j]);
        }
    }
    swap_str(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort_str(char arr[][MAX_STR_LEN], int low, int high) {
    if (low < high) {
        int pi = partition_str(arr, low, high);
        quickSort_str(arr, low, pi - 1);
        quickSort_str(arr, pi + 1, high);
    }
}

void performSort(int choice, bool is_string, int n, int int_arr[], char str_arr[][MAX_STR_LEN]) {
    if (n <= 1) {
        std::cout << "Массив слишком мал для сортировки (n <= 1).\n";
        return;
    }

    auto start = std::chrono::high_resolution_clock::now();

    switch (choice) {
    case 1:
        if (is_string) { std::cout << "Не поддерживает строки!\n"; return; }
        std::cout << "Выбран Selection Sort\n";
        selectionSort(int_arr, n);
        break;
    case 2:
        if (is_string) { std::cout << "Не поддерживает строки!\n"; return; }
        std::cout << "Выбран Bubble Sort\n";
        bubbleSort(int_arr, n);
        break;
    case 3:
        if (is_string) { std::cout << "Не поддерживает строки!\n"; return; }
        std::cout << "Выбран Insertion Sort\n";
        insertionSort(int_arr, n);
        break;
    case 4:
        if (is_string) { std::cout << "Не поддерживает строки!\n"; return; }
        std::cout << "Выбран Quick Sort\n";
        quickSort(int_arr, 0, n - 1);
        break;
    case 5:
        if (is_string) { std::cout << "Не поддерживает строки!\n"; return; }
        std::cout << "Выбран Recursive Merge Sort\n";
        recursionMergeSort(int_arr, 0, n - 1);
        break;
    case 6:
        if (is_string) { std::cout << "Не поддерживает строки!\n"; return; }
        std::cout << "Выбран Iterative Merge Sort\n";
        iterativeMergeSort(int_arr, n);
        break;
    case 7:
        if (is_string) { std::cout << "Не поддерживает строки!\n"; return; }
        std::cout << "Выбран Shell Sort\n";
        shellSort(int_arr, n);
        break;
    case 8:
        if (is_string) { std::cout << "Не поддерживает строки!\n"; return; }
        std::cout << "Выбран Radix Sort LSD\n";
        radixSortLSD(int_arr, n);
        break;
    case 9:
        if (!is_string) { std::cout << "Lexicographic sort только для строк!\n"; return; }
        std::cout << "Выбран Lexicographic Sort\n";
        quickSort_str(str_arr, 0, n - 1);
        break;
    case 10:
        if (is_string) { std::cout << "Не поддерживает строки!\n"; return; }
        std::cout << "Выбран Heap Sort\n";
        heapSort(int_arr, n);
        break;
    default:
        std::cout << "Неверный выбор алгоритма!\n";
        return;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;
    std::cout << "Время выполнения: " << elapsed.count() << " мс\n";
}

void loadData(int choice, bool& is_string, int& n, int int_arr[], char str_arr[][MAX_STR_LEN]) {
    n = 0;
    switch (choice) {
    case 1: {
        int size;
        std::cout << "Введите размер случайного массива: ";
        std::cin >> size;
        if (!std::cin || size <= 0) { std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); std::cout << "Неверный размер.\n"; n = 0; break; }
        if (size > MAX_SIZE) {
            std::cout << "Слишком большой размер! Будет использовано MAX_SIZE.\n";
            size = MAX_SIZE;
        }
        char type[10];
        std::cout << "Введите тип (int, string): ";
        std::cin >> type;
        if (std::strcmp(type, "int") == 0) {
            is_string = false;
            n = size;
            for (int i = 0; i < n; i++) int_arr[i] = rand() % 20001 - 10000;
        } else if (std::strcmp(type, "string") == 0) {
            is_string = true;
            n = size;
            for (int i = 0; i < n; i++) {
                int len = rand() % 10 + 1;
                if (len >= MAX_STR_LEN) len = MAX_STR_LEN - 1;
                for (int k = 0; k < len; k++) str_arr[i][k] = 'a' + rand() % 26;
                str_arr[i][len] = '\0';
            }
        } else {
            std::cout << "Неверный тип! Используется int.\n";
            is_string = false;
            n = size;
            for (int i = 0; i < n; i++) int_arr[i] = rand() % 20001 - 10000;
        }
        break;
    }
    case 2: {
        std::cout << "Выберите предзаписанный массив (1-3): ";
        int arrChoice;
        std::cin >> arrChoice;
        is_string = false;
        if (arrChoice == 1) {
            int temp[] = {64, 25, 12, 22, 3, 0};
            n = 6;
            for (int i = 0; i < n; i++) int_arr[i] = temp[i];
        } else if (arrChoice == 2) {
            int temp[] = {68, 21, 8, 22, 0, -1, -31, -12};
            n = 8;
            for (int i = 0; i < n; i++) int_arr[i] = temp[i];
        } else if (arrChoice == 3) {
            int temp[] = {1, -4, 0, 4, 4, -2, -2};
            n = 7;
            for (int i = 0; i < n; i++) int_arr[i] = temp[i];
        } else {
            std::cout << "Неверный выбор массива! Используется массив 1.\n";
            int temp[] = {64, 25, 12, 22, 3, 0};
            n = 6;
            for (int i = 0; i < n; i++) int_arr[i] = temp[i];
        }
        break;
    }
    case 3: {
        char filename[256];
        std::cout << "Введите имя файла: ";
        std::cin >> filename;
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cout << "Ошибка открытия файла!\n";
            n = 0;
            break;
        }
        is_string = false;
        n = 0;
        int num;
        while (file >> num && n < MAX_SIZE) {
            int_arr[n++] = num;
        }
        file.close();
        break;
    }
    case 4: {
        char type[10];
        std::cout << "Введите тип (int, string): ";
        std::cin >> type;
        int size;
        std::cout << "Введите размер массива: ";
        std::cin >> size;
        if (!std::cin || size <= 0) { std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); std::cout << "Неверный размер.\n"; n = 0; break; }
        if (size > MAX_SIZE) {
            std::cout << "Слишком большой размер! Будет использовано MAX_SIZE.\n";
            size = MAX_SIZE;
        }
        n = size;
        if (std::strcmp(type, "int") == 0) {
            is_string = false;
            for (int i = 0; i < n; i++) {
                std::cout << "Введите элемент " << i + 1 << ": ";
                std::cin >> int_arr[i];
            }
        } else if (std::strcmp(type, "string") == 0) {
            is_string = true;
            for (int i = 0; i < n; i++) {
                std::cout << "Введите элемент " << i + 1 << ": ";
                std::cin >> str_arr[i];
            }
        } else {
            std::cout << "Неверный тип!\n";
            n = 0;
        }
        break;
    }
    case 5: {
        char filename[256] = "lexicographic.txt";
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cout << "Ошибка открытия файла: " << filename << "\n";
            n = 0;
            break;
        }
        is_string = true;
        n = 0;
        char temp[MAX_STR_LEN];
        while (file >> temp && n < MAX_SIZE) {
            std::strncpy(str_arr[n], temp, MAX_STR_LEN - 1);
            str_arr[n][MAX_STR_LEN - 1] = '\0';
            n++;
        }
        file.close();
        break;
    }
    default:
        std::cout << "Неверный выбор источника данных! Используется случайный массив.\n";
        is_string = false;
        n = 10;
        for (int i = 0; i < n; i++) int_arr[i] = rand() % 20001 - 10000;
        break;
    }
}

void display(bool is_string, int n, const int int_arr[], const char str_arr[][MAX_STR_LEN]) {
    for (int i = 0; i < n; i++) {
        if (!is_string) std::cout << int_arr[i] << " ";
        else std::cout << str_arr[i] << " ";
    }
    std::cout << std::endl;
}

void showMenu() {
    std::cout << "\n=== МЕНЮ ВЫБОРА СОРТИРОВКИ ===\n";
    std::cout << "1. Selection Sort\n2. Bubble Sort\n3. Insertion Sort\n4. Quick Sort\n";
    std::cout << "5. Recursive Merge Sort\n6. Iterative Merge Sort\n7. Shell Sort\n";
    std::cout << "8. Radix Sort LSD\n9. Lexicographic Sort\n10. Heap Sort\n0. Выход\n";
    std::cout << "Выберите алгоритм сортировки: ";
}

void showDataSourceMenu() {
    std::cout << "\n=== ВЫБОР ИСТОЧНИКА ДАННЫХ ===\n";
    std::cout << "1. Случайный массив\n2. Предзаписанный массив\n3. Данные из файла (числа)\n4. Ввести свой массив\n5. Данные из файла (строки)\n";
    std::cout << "Выберите источник данных: ";
}

int main() {
    srand(static_cast<unsigned>(time(0)));

    // Динамическое выделение больших массивов в куче (не на стеке)
    int* int_arr = nullptr;
    char (*str_arr)[MAX_STR_LEN] = nullptr;
    try {
        int_arr = new int[MAX_SIZE];
        str_arr = new char[MAX_SIZE][MAX_STR_LEN];
    } catch (const std::bad_alloc&) {
        std::cerr << "Не удалось выделить память для массивов (bad_alloc).\n";
        return 1;
    }

    bool is_string = false;
    int n = 0;
    int algorithmChoice = 0;
    int dataChoice = 0;

    while (true) {
        showMenu();
        if (!(std::cin >> algorithmChoice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Неверный ввод. Повторите.\n";
            continue;
        }

        if (algorithmChoice == 0) break;

        showDataSourceMenu();
        if (!(std::cin >> dataChoice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Неверный ввод. Повторите.\n";
            continue;
        }

        loadData(dataChoice, is_string, n, int_arr, str_arr);

        if (n == 0) {
            std::cout << "Ошибка получения данных или n == 0. Попробуйте снова.\n";
            continue;
        }

        std::cout << "\nИсходный массив: ";
        display(is_string, n, int_arr, str_arr);

        performSort(algorithmChoice, is_string, n, int_arr, str_arr);

        std::cout << "Отсортированный массив: ";
        display(is_string, n, int_arr, str_arr);

        std::cout << "\nНажмите Enter для продолжения...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
    }

    delete[] int_arr;
    delete[] str_arr;

    std::cout << "Программа завершена.\n";
    return 0;
}
