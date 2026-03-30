/**
 * C++ 排序算法示例集合
 * 包含多种经典排序算法的实现与性能比较
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <iomanip>

using namespace std;

// ==================== 排序算法实现 ====================

/**
 * 冒泡排序 (Bubble Sort)
 * 时间复杂度: O(n²)
 * 空间复杂度: O(1)
 */
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;  // 优化：如果没有交换，说明已经有序
    }
}

/**
 * 选择排序 (Selection Sort)
 * 时间复杂度: O(n²)
 * 空间复杂度: O(1)
 */
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        swap(arr[i], arr[minIdx]);
    }
}

/**
 * 插入排序 (Insertion Sort)
 * 时间复杂度: O(n²)
 * 空间复杂度: O(1)
 */
void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

/**
 * 快速排序 (Quick Sort)
 * 时间复杂度: 平均 O(n log n), 最坏 O(n²)
 * 空间复杂度: O(log n)
 */
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void quickSort(vector<int>& arr) {
    quickSort(arr, 0, arr.size() - 1);
}

/**
 * 归并排序 (Merge Sort)
 * 时间复杂度: O(n log n)
 * 空间复杂度: O(n)
 */
void merge(vector<int>& arr, int left, int mid, int right) {
    vector<int> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];

    for (int i = 0; i < k; i++) {
        arr[left + i] = temp[i];
    }
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void mergeSort(vector<int>& arr) {
    mergeSort(arr, 0, arr.size() - 1);
}

/**
 * 堆排序 (Heap Sort)
 * 时间复杂度: O(n log n)
 * 空间复杂度: O(1)
 */
void heapify(vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<int>& arr) {
    int n = arr.size();

    // 构建最大堆
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // 逐个提取元素
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// ==================== 辅助函数 ====================

// 生成随机数组
vector<int> generateRandomArray(int size, int minVal = 1, int maxVal = 10000) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(minVal, maxVal);

    vector<int> arr(size);
    for (int i = 0; i < size; i++) {
        arr[i] = dis(gen);
    }
    return arr;
}

// 打印数组
void printArray(const vector<int>& arr, int maxElements = 20) {
    int n = min((int)arr.size(), maxElements);
    cout << "[";
    for (int i = 0; i < n; i++) {
        cout << arr[i];
        if (i < n - 1) cout << ", ";
    }
    if (arr.size() > maxElements) cout << ", ...";
    cout << "]" << endl;
}

// 测量排序时间(毫秒)
template<typename SortFunc>
double measureTime(vector<int> arr, SortFunc sortFunc) {
    auto start = chrono::high_resolution_clock::now();
    sortFunc(arr);
    auto end = chrono::high_resolution_clock::now();
    return chrono::duration<double, milli>(end - start).count();
}

// 验证数组是否有序
bool isSorted(const vector<int>& arr) {
    for (int i = 0; i < arr.size() - 1; i++) {
        if (arr[i] > arr[i + 1]) return false;
    }
    return true;
}

// ==================== 性能测试 ====================

void performanceTest(int arraySize) {
    cout << "\n========== 性能测试 (数组大小: " << arraySize << ") ==========\n";

    vector<int> original = generateRandomArray(arraySize);

    struct Algorithm {
        string name;
        function<void(vector<int>&)> sortFunc;
    };

    vector<Algorithm> algorithms = {
        {"冒泡排序", bubbleSort},
        {"选择排序", selectionSort},
        {"插入排序", insertionSort},
        {"快速排序", quickSort},
        {"归并排序", mergeSort},
        {"堆排序", heapSort},
        {"STL sort", [](vector<int>& arr) { sort(arr.begin(), arr.end()); }}
    };

    cout << left << setw(15) << "算法" << setw(15) << "时间(ms)" << "结果" << endl;
    cout << string(45, '-') << endl;

    for (auto& algo : algorithms) {
        double time = measureTime(original, algo.sortFunc);
        vector<int> testArr = original;
        algo.sortFunc(testArr);
        bool sorted = isSorted(testArr);

        cout << left << setw(15) << algo.name
             << setw(15) << fixed << setprecision(2) << time
             << (sorted ? "✓ 正确" : "✗ 错误") << endl;
    }
}

// ==================== 示例演示 ====================

void demonstrateSorting() {
    cout << "========== 排序算法演示 ==========\n\n";

    // 创建示例数组
    vector<int> arr = {64, 34, 25, 12, 22, 11, 90, 45, 33, 77};

    cout << "原始数组: ";
    printArray(arr);

    // 测试各种排序算法
    vector<pair<string, function<void(vector<int>&)>>> algorithms = {
        {"冒泡排序", bubbleSort},
        {"选择排序", selectionSort},
        {"插入排序", insertionSort},
        {"快速排序", quickSort},
        {"归并排序", mergeSort},
        {"堆排序", heapSort}
    };

    for (auto& algo : algorithms) {
        vector<int> temp = arr;
        algo.second(temp);
        cout << algo.first << ": ";
        printArray(temp);
    }

    // STL sort
    vector<int> stlArr = arr;
    sort(stlArr.begin(), stlArr.end());
    cout << "STL sort: ";
    printArray(stlArr);
}

// ==================== 主函数 ====================

int main() {
    cout << "╔════════════════════════════════════════╗\n";
    cout << "║     C++ 排序算法示例集合              ║\n";
    cout << "║     Sorting Algorithm Examples         ║\n";
    cout << "╚════════════════════════════════════════╝\n\n";

    // 演示排序算法
    demonstrateSorting();

    // 性能测试
    cout << "\n";
    performanceTest(1000);
    performanceTest(5000);
    performanceTest(10000);

    cout << "\n程序执行完成!\n";
    return 0;
}
