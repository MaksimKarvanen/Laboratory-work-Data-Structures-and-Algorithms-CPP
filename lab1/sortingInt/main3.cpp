#include <iostream>
#include <fstream>
#include <cstdlib>
#include <chrono>
#include <cstring>
#include <ctime>
#include <algorithm>
#include <limits>
#include <string>

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
        if (std::abs(arr[i]) > mx) mx = std::abs(arr[i]);
    }
    return mx;
}

int partition(double arr[], int low, int high) {
    double pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            double temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    double temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

void merge(int arr[], int left, int mid, int right) {
    if (left > mid || mid > right) return;
    int n1 = mid - left + 1;
    int n2 = right - mid;
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
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) minIndex = j;
        }
        if (minIndex != i) swap_int(arr[i], arr[minIndex]);
    }
}

void bubbleSort(int arr[], int n) {
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

void quickSort(double arr[], int low, int high) {
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
    for (int curr_size = 1; curr_size <= n - 1; curr_size *= 2) {
        for (int left_start = 0; left_start < n - 1; left_start += 2 * curr_size) {
            int mid = std::min(left_start + curr_size - 1, n - 1);
            int right_end = std::min(left_start + 2 * curr_size - 1, n - 1);
            if (mid < right_end) merge(arr, left_start, mid, right_end);
        }
    }
}

void shellSort(int arr[], int n) {
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
    int count2[2] = {0};
    for (int i = 0; i < n; i++) count2[arr[i] < 0 ? 0 : 1]++;
    count2[1] += count2[0];
    for (int i = n - 1; i >= 0; i--) {
        int d = (arr[i] < 0) ? 0 : 1;
        out[count2[d] - 1] = arr[i];
        count2[d]--;
    }
    int neg_count = 0;
    for (int i = 0; i < n && out[i] < 0; i++) neg_count++;
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

void performSort(int choice, bool is_string, int n, double* double_arr, int int_arr[], char str_arr[][MAX_STR_LEN]) {
    if (n <= 1) return;
    auto start = std::chrono::high_resolution_clock::now();
    switch (choice) {
        case 1: selectionSort(int_arr, n); break;
        case 2: bubbleSort(int_arr, n); break;
        case 3: insertionSort(int_arr, n); break;
        case 4: quickSort(double_arr, 0, n - 1); break;
        case 5: recursionMergeSort(int_arr, 0, n - 1); break;
        case 6: iterativeMergeSort(int_arr, n); break;
        case 7: shellSort(int_arr, n); break;
        case 8: radixSortLSD(int_arr, n); break;
        case 9: if (n > 0) quickSort_str(str_arr, 0, n - 1); break;
        case 10: heapSort(int_arr, n); break;
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;
    std::cout << "Время выполнения: " << elapsed.count() << " мс" << std::endl;
}

void display(bool is_string, int n, const double* double_arr, const int int_arr[], const char str_arr[][MAX_STR_LEN]) {
    for (int i = 0; i < n; i++) {
        if (is_string) {
            std::cout << str_arr[i] << " ";
        } else {
            if (double_arr) {
                std::cout << double_arr[i] << " ";
            } else {
                std::cout << int_arr[i] << " ";
            }
        }
    }
    std::cout << std::endl;
}

void showMenu() {
    std::cout << "\n=== МЕНЮ ВЫБОРА СОРТИРОВКИ ===\n";
    std::cout << "1. Selection Sort\n2. Bubble Sort\n3. Insertion Sort\n4. Quick Sort\n";
    std::cout << "5. Recursive Merge Sort\n6. Iterative Merge Sort\n7. Shell Sort\n";
    std::cout << "8. Radix Sort LSD\n9. Lexicographic Sort (строки)\n10. Heap Sort\n0. Выход\n";
    std::cout << "Выберите алгоритм сортировки: ";
}

int main() {
    srand(static_cast<unsigned>(time(0)));

    int* int_arr = new int[MAX_SIZE];
    char (*str_arr)[MAX_STR_LEN] = new char[MAX_SIZE][MAX_STR_LEN];
    double* double_arr = nullptr;

    bool is_string;
    int n;

    while (true) {
        showMenu();
        int algorithmChoice;
        std::cin >> algorithmChoice;
        if (algorithmChoice == 0) break;

        if (algorithmChoice == 9) {
            is_string = true;
            std::ifstream fin("lexicographic.txt");
            if (!fin.is_open()) {
                std::cout << "Cannot open lexicographic.txt" << std::endl;
                continue;
            }
            n = 0;
            std::string line;
            while (std::getline(fin, line) && n < MAX_SIZE) {
                std::strncpy(str_arr[n], line.c_str(), MAX_STR_LEN - 1);
                str_arr[n][MAX_STR_LEN - 1] = '\0';
                n++;
            }
            fin.close();
        } else if (algorithmChoice == 4) {
            is_string = false;
            std::ifstream fin("weather_data.txt");
            if (!fin.is_open()) {
                std::cout << "Cannot open weather_data.txt" << std::endl;
                continue;
            }
            double_arr = new double[MAX_SIZE];
            n = 0;
            double val;
            while (fin >> val && n < MAX_SIZE) {
                double_arr[n] = val;
                n++;
            }
            fin.close();
        } else {
            std::cout << "Введите размер массива: ";
            std::cin >> n;
            if (n <= 0) continue;
            if (n > MAX_SIZE) n = MAX_SIZE;
            is_string = false;
            for (int i = 0; i < n; i++)
                int_arr[i] = rand() % 20001 - 10000;
        }

        std::cout << "Исходный массив: ";
        display(is_string, n, double_arr, int_arr, str_arr);

        performSort(algorithmChoice, is_string, n, double_arr, int_arr, str_arr);

        std::cout << "Отсортированный массив: ";
        display(is_string, n, double_arr, int_arr, str_arr);

        if (algorithmChoice == 4) {
            delete[] double_arr;
            double_arr = nullptr;
        }

        std::cout << "\nНажмите Enter для продолжения...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
    }

    delete[] int_arr;
    delete[] str_arr;

    std::cout << "Программа завершена.\n";
    return 0;
}