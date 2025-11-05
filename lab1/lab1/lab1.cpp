#include <iostream>
#include <ctime>
#include <cstdlib>

const int MAX_STR_LEN = 256;
const int MAX_SIZE = 5000;

void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

void swap_double(double& a, double& b) {
    double temp = a;
    a = b;
    b = temp;
}

void selectionSort(int arr[], int n) {
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

void bubbleSort(int arr[], int n) {
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

int partition(int arr[], int low, int high) {
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

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int partition_double(double arr[], int low, int high) {
    double pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap_double(arr[i], arr[j]);
        }
    }
    swap_double(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort_double(double arr[], int low, int high) {
    if (low < high) {
        int pi = partition_double(arr, low, high);
        quickSort_double(arr, low, pi - 1);
        quickSort_double(arr, pi + 1, high);
    }
}

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int L[MAX_SIZE];
    int R[MAX_SIZE];
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

void recursionMergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        recursionMergeSort(arr, left, mid);
        recursionMergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void iterativeMergeSort(int arr[], int n) {
    for (int i = 1; i < n; i *= 2) {
        for (int j = 0; j < n - 1; j += 2 * i) {
            merge(arr, j, j + i - 1, std::min(j + 2 * i - 1, n - 1));
        }
    }
}

void heapify(int arr[], int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < n && arr[l] > arr[largest]) {
        largest = l;
    }
    if (r < n && arr[r] > arr[largest]) {
        largest = r;
    }
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

int getMaxAbs(int arr[], int n) {
    int max = abs(arr[0]);
    for (int i = 1; i < n; i++) {
        if (abs(arr[i]) > max) {
            max = abs(arr[i]);
        }
    }
    return max;
}

void radixSortLSD(int arr[], int n) {
    int m = getMaxAbs(arr, n);
    for (int exp = 1; m / exp > 0; exp *= 10) {
        int output[MAX_SIZE];
        int i;
        int count[10] = {0};
        for (i = 0; i < n; i++) {
            count[(abs(arr[i]) / exp) % 10]++;
        }
        for (i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }
        for (i = n - 1; i >= 0; i--) {
            output[count[(abs(arr[i]) / exp) % 10] - 1] = arr[i];
            count[(abs(arr[i]) / exp) % 10]--;
        }
        for (i = 0; i < n; i++) {
            arr[i] = output[i];
        }
    }
    // Sign pass
    {
        int output[MAX_SIZE];
        int i;
        int count[2] = {0};
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

void shellSort(int arr[], int n) {
    for (int gap = n / 2; gap > 0; gap = gap / 2) {
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

void swap_str(char a[], char b[])
{
    for (int i = 0 ; i < 256 ; i++)
    {
        char temp = a[i];
        a[i] = b[i];
        b[i] = temp;
    }
}

int partition_str(char arr[][MAX_STR_LEN], int low, int high)
{
    char pivot[MAX_STR_LEN];
    strcpy(pivot, arr[high]);
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (strcmp(arr[j], pivot) <= 0) {
            i++;
            swap_str(arr[i], arr[j]);
        }
    }
    swap_str(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort_str(char arr[][MAX_STR_LEN], int low, int high) {
    if (low < high) {
        int pi = partition_str(arr, low, high);
        quickSort_str(arr, low, pi - 1);
        quickSort_str(arr, pi + 1, high);
    }
}

int strcmp_str(const char* a, const char* b)
{
    while (*a && (*a == *b))
    {
        a++;
        b++;
    }
    return *(const unsigned char*)a - *(const unsigned char*)b;
}

void bubbleSort_str(char arr[][256], int n)
{
    for (int i = 0; i < n; i++)
    {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++)
        {
            if (strcmp_str(arr[j], arr[j + 1]) > 0)
            {
                swap_str(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped)
        {
            break;
        }
    }
}

void selectionSort_str(char arr[][256], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int min_index = i;
        for (int j = i + 1; j < n; j++)
        {
            if (strcmp_str(arr[min_index], arr[j]) > 0)
            {
                min_index = j;
            }
        }
        if (min_index != i)
        {
            swap_str(arr[i], arr[min_index]);
        }
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

void printDoubleArray(double arr[], int n) {
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

void printStringArray(char arr[][MAX_STR_LEN], int n) {
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << ", ";
    }
    std::cout << std::endl;
}

void generateRandomArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000 - 500; // числа от -500 до 499
    }
}

int readWeatherData(const char* filename, double data[]) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        std::cout << "Ошибка открытия файла " << filename << std::endl;
        return 0;
    }

    int count = 0;
    while (fscanf(file, "%lf", &data[count]) == 1 && count < MAX_SIZE) {
        count++;
    }

    fclose(file);
    return count;
}

int readLexicographicData(const char* filename, char data[][MAX_STR_LEN]) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        std::cout << "Ошибка открытия файла " << filename << std::endl;
        return 0;
    }

    int count = 0;
    char buffer[MAX_STR_LEN];
    while (fgets(buffer, MAX_STR_LEN, file) && count < MAX_SIZE) {
        // Удаляем символ новой строки
        int len = 0;
        while (buffer[len] != '\0' && buffer[len] != '\n' && buffer[len] != '\r') {
            len++;
        }
        buffer[len] = '\0';

        // Копируем в массив
        for (int i = 0; i <= len; i++) {
            data[count][i] = buffer[i];
        }
        count++;
    }

    fclose(file);
    return count;
}

void copyArray(int source[], int dest[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = source[i];
    }
}

typedef void (*SortFunctionInt)(int[], int);
typedef void (*SortFunctionDouble)(double[], int, int);
typedef void (*SortFunctionString)(char[][MAX_STR_LEN], int);

void testAlgorthm(SortFunctionInt sortFunc, const char* algorithmName)
{
    std::cout << "\n---- Тестирование сортировки: " << algorithmName << std::endl;

    const int testSize = 100;
    int* originalArray = new int[testSize];
    int* testArray = new int[testSize];

    generateRandomArray(originalArray, testSize);

    std::cout << "Исходный массив:";
    printArray(originalArray, testSize);

    copyArray(originalArray, testArray, testSize);

    sortFunc(testArray, testSize);

    std::cout << "Отсортированный массив:";
    printArray(testArray, testSize);

    delete[] originalArray;
    delete[] testArray;
}

void testAlgorythmDouble(SortFunctionDouble sortFunc, const char* algorithmName, const char* filename)
{
    std::cout << "\n---- Тестирование сортировки: " << algorithmName << " для вещественных чисел (погода)" << std::endl;

    double* weatherData = new double[MAX_SIZE];
    int count = readWeatherData(filename, weatherData);

    if (count > 0)
    {
        std::cout << "Исходный массив: ";
        printDoubleArray(weatherData, count);

        sortFunc(weatherData, 0, count - 1);

        std::cout << "Отсортированный массив: ";
        printDoubleArray(weatherData, count);
    }
    delete[] weatherData;
}

void testAlgorythmString(SortFunctionString sortFunc, const char* algorithmName, const char* filename)
{
    std::cout << "\n---- Тестирование сортировки: " << algorithmName << " для строк (имена)" << std::endl;

    char (*names)[MAX_STR_LEN] = new char[MAX_SIZE][MAX_STR_LEN];
    int count = readLexicographicData(filename, names);

    if (count > 0)
    {
        std::cout << "Исходный массив: ";
        printStringArray(names, count);

        sortFunc(names, count);

        std::cout << "Отсортированный массив: ";
        printStringArray(names, count);
    }
    delete[] names;
}

void quickSortWrapper(int arr[], int n) {
    quickSort(arr, 0, n - 1);
}

void recursionMergeSortWrapper(int arr[], int n) {
    recursionMergeSort(arr, 0, n - 1);
}

void quickSortStrWrapper(char arr[][MAX_STR_LEN], int n)
{
    quickSort_str(arr, 0, n - 1);
}

int main()
{
    srand(time(0));

    testAlgorthm(selectionSort, "SelectionSort");
    testAlgorthm(bubbleSort, "BubbleSort");
    testAlgorthm(insertionSort, "SelectionSort");
    testAlgorthm(heapSort, "HeapSort");
    testAlgorthm(shellSort, "ShellSort");
    testAlgorthm(radixSortLSD, "Radix Sort");
    testAlgorthm(iterativeMergeSort, "Iterative Merge Sort");
    testAlgorthm(recursionMergeSortWrapper, "Recursive Merge Sort");
    testAlgorthm(quickSortWrapper, "Quick Sort");

    testAlgorythmDouble(quickSort_double, "Quick Sort", "weather_data.txt");

    testAlgorythmString(bubbleSort_str, "Bubble Sort", "lexicographic.txt");
    testAlgorythmString(selectionSort_str, "Selection Sort", "lexicographic.txt");
    testAlgorythmString(quickSortStrWrapper, "Quick Sort", "lexicographic.txt");

    return 0;
}
