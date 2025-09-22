#include <iostream>

void display(int arr[], int n) {
    for (int i = 0; i < n; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
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

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int* L = new int[n1];
    int* R = new int[n2];
    for (int i = 0; i < n1; i++){
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++){
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
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
    delete[] L;
    delete[] R;
}

void selectionSort(int array[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (array[j] < array[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            swap(array[i], array[minIndex]);
        }
    }
}

void bubbleSort(int arr[], int n){
    for(int i = 0; i < n - 1; ++i){
        bool swapped = false;
        for(int j = 0; j < n - i - 1; ++j){
            if (arr[j] > arr[j + 1]){
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped){
            break;
        }
    }
}

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++){
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key){
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

void quickSort(int arr[], int low, int high){
    if (low < high){
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void recursionMergeSort(int arr[], int left, int right){
    if (left < right){
        int mid = left + (right - left) / 2;
        recursionMergeSort(arr, left, mid);
        recursionMergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void iterativeMergeSort(int arr[], int n) {
    for (int i = 1; i < n; i *= 2)
    {
        for (int j = 0; j < n - 1; j += 2 * i)
        {
            merge(arr, j, j + i - 1, std::min(j + 2 * i - 1, n - 1));
        }
    }
}

void shellSort(int arr[], int n)
{
    for (int gap = n / 2; gap > 0; gap = gap / 2)
    {
        for (int i = gap; i < n; ++i)
        {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
            {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

int main() {
    int arr1[] = {64, 25, 12, 22, 11};
    int arr2[] = {68, 21, 8, 22, 14, 1};
    int arr3[] = {12, 11, 13, 5, 6};
    int arr4[] = {78, 24, 18, 16, 10, 6, 83, 0};
    int arr5[] = {38, 27, 43, 3, 9, 82, 10};
    int arr6[] = {26, 25, 24, 7, 6, 5, 4, 3};
    int arr7[] = {18, 17, 16, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    int size3 = sizeof(arr3) / sizeof(arr3[0]);
    int size4 = sizeof(arr4) / sizeof(arr4[0]);
    int size5 = sizeof(arr5) / sizeof(arr5[0]);
    int size6 = sizeof(arr6) / sizeof(arr6[0]);
    int size7 = sizeof(arr7) / sizeof(arr7[0]);

    selectionSort(arr1, size1);
    bubbleSort(arr2, size2);
    insertionSort(arr3, size3);
    quickSort(arr4, 0, size4 - 1);
    recursionMergeSort(arr5, 0, size5 - 1);
    iterativeMergeSort(arr6, size6);
    shellSort(arr7, size7);

    std::cout << "Sorted array (selection sort): \n";
    display(arr1, size1);

    std::cout << "Sorted array (bubble sort): \n";
    display(arr2, size2);

    std::cout << "Sorted array (insertion sort): \n";
    display(arr3, size3);

    std::cout << "Sorted array (quick sort): \n";
    display(arr4, size4);

    std::cout << "Sorted array (recursion merge sort): \n";
    display(arr5, size5);

    std::cout << "Sorted array (iterative merge sort): \n";
    display(arr6, size6);

    std::cout << "Sorted array (shell sort): \n";
    display(arr7, size7);

    return 0;
}