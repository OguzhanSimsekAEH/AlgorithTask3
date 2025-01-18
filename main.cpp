#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <algorithm>


template <typename T>
int hoarePartitionFirst(std::vector<T>& arr, int low, int high) {
    T pivot = arr[low];
    int i = low - 1;
    int j = high + 1;

    while (true) {
        do { i++; } while (arr[i] < pivot);
        do { j--; } while (arr[j] > pivot);
        if (i >= j) return j;
        std::swap(arr[i], arr[j]);
    }
}


template <typename T>
int hoarePartitionMiddle(std::vector<T>& arr, int low, int high) {
    int mid = low + (high - low) / 2;
    T pivot = arr[mid];
    int i = low - 1;
    int j = high + 1;

    while (true) {
        do { i++; } while (arr[i] < pivot);
        do { j--; } while (arr[j] > pivot);
        if (i >= j) return j;
        std::swap(arr[i], arr[j]);
    }
}


template <typename T>
int hoarePartitionRandom(std::vector<T>& arr, int low, int high) {
    int randomIndex = low + rand() % (high - low + 1);
    std::swap(arr[low], arr[randomIndex]); 
    T pivot = arr[low];
    int i = low - 1;
    int j = high + 1;

    while (true) {
        do { i++; } while (arr[i] < pivot);
        do { j--; } while (arr[j] > pivot);
        if (i >= j) return j;
        std::swap(arr[i], arr[j]);
    }
}


template <typename T>
int hoarePartitionMedian(std::vector<T>& arr, int low, int high) {
    int mid = low + (high - low) / 2;
    int first = low;
    int last = high;

    std::vector<T> candidates = { arr[first], arr[mid], arr[last] };
    std::sort(candidates.begin(), candidates.end());
    T pivot = candidates[1];  

    if (pivot == arr[mid]) std::swap(arr[low], arr[mid]);
    else if (pivot == arr[last]) std::swap(arr[low], arr[last]);

    int i = low - 1;
    int j = high + 1;

    while (true) {
        do { i++; } while (arr[i] < pivot);
        do { j--; } while (arr[j] > pivot);
        if (i >= j) return j;
        std::swap(arr[i], arr[j]);
    }
}


template <typename T>
void quickSort(std::vector<T>& arr, int low, int high, int pivotType) {
    if (low < high) {
        int partitionIndex;
        if (pivotType == 1) {
            partitionIndex = hoarePartitionFirst(arr, low, high);
        }
        else if (pivotType == 2) {
            partitionIndex = hoarePartitionMiddle(arr, low, high);
        }
        else if (pivotType == 3) {
            partitionIndex = hoarePartitionRandom(arr, low, high);
        }
        else {
            partitionIndex = hoarePartitionMedian(arr, low, high);
        }
        quickSort(arr, low, partitionIndex, pivotType);
        quickSort(arr, partitionIndex + 1, high, pivotType);
    }
}


template <typename T>
long long measureExecutionTime(std::vector<T>& arr, int pivotType) {
    auto start = std::chrono::high_resolution_clock::now();
    quickSort(arr, 0, arr.size() - 1, pivotType);
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}


template <typename T>
void fillRandom(std::vector<T>& arr, int size) {
    arr.clear();
    for (int i = 0; i < size; ++i) {
        arr.push_back(rand() % 10000);
    }
}

template <typename T>
void fillSorted(std::vector<T>& arr, int size) {
    arr.clear();
    for (int i = 0; i < size; ++i) {
        arr.push_back(i);
    }
}

template <typename T>
void fillReverseSorted(std::vector<T>& arr, int size) {
    arr.clear();
    for (int i = size - 1; i >= 0; --i) {
        arr.push_back(i);
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0)));  
    std::vector<int> arr;
    int sizes[] = { 10000, 20000, 30000, 40000, 50000 };  
    int pivotTypes[] = { 1, 2, 3, 4 };  

    std::cout << "Pivot Strategy  | Array Size | Random Array Time (ms) | Sorted Array Time (ms) | Reverse Sorted Array Time (ms)\n";
    std::cout << "---------------------------------------------------------------------\n";

    
    for (int pivotType : pivotTypes) {
        std::string pivotStrategy;
        if (pivotType == 1) pivotStrategy = "First Element";
        else if (pivotType == 2) pivotStrategy = "Middle Element";
        else if (pivotType == 3) pivotStrategy = "Random Element";
        else pivotStrategy = "Median of First, Middle, and Last";

        for (int size : sizes) {
            
            fillRandom(arr, size);
            long long randomTime = measureExecutionTime(arr, pivotType);

            
            fillSorted(arr, size);
            long long sortedTime = measureExecutionTime(arr, pivotType);

            
            fillReverseSorted(arr, size);
            long long reverseSortedTime = measureExecutionTime(arr, pivotType);

            
            std::cout << pivotStrategy << " | " << size
                << " | " << randomTime << " ms"
                << " | " << sortedTime << " ms"
                << " | " << reverseSortedTime << " ms\n";
        }
    }

    return 0;
}
