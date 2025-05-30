#include <iostream>
#include <vector>
#include <pthread.h>
#include <cstdlib>
#include <chrono>
using namespace std;

const int MAX_DEPTH = 2;
const int SIZE = 100000; 

void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

struct ThreadArgs {
    vector<int>* arr;
    int left;
    int right;
    int depth;
};

void* parallelMergeSort(void* arg) {
    ThreadArgs* args = (ThreadArgs*)arg;
    int left = args->left;
    int right = args->right;
    int depth = args->depth;
    vector<int>* arr = args->arr;

    if (left >= right) return nullptr;

    int mid = left + (right - left) / 2;

    if (depth < MAX_DEPTH) {
        pthread_t tid1, tid2;
        ThreadArgs leftArgs = {arr, left, mid, depth + 1};
        ThreadArgs rightArgs = {arr, mid + 1, right, depth + 1};

        pthread_create(&tid1, nullptr, parallelMergeSort, &leftArgs);
        pthread_create(&tid2, nullptr, parallelMergeSort, &rightArgs);

        pthread_join(tid1, nullptr);
        pthread_join(tid2, nullptr);
} else {
    ThreadArgs leftArgs = {arr, left, mid, depth + 1};
    ThreadArgs rightArgs = {arr, mid + 1, right, depth + 1};

    parallelMergeSort(&leftArgs);
    parallelMergeSort(&rightArgs);
}
    merge(*arr, left, mid, right);
    return nullptr;
}

vector<int> generateRandomArray(int size) {
    vector<int> arr(size);
    for (int i = 0; i < size; ++i)
        arr[i] = rand() % 10000;
    return arr;
}

bool isSorted(const vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); ++i)
        if (arr[i - 1] > arr[i]) return false;
    return true;
}

int main() {
    auto start = chrono::high_resolution_clock::now();

    vector<int> arr = generateRandomArray(SIZE);

    ThreadArgs args = {&arr, 0, SIZE - 1, 0};
    parallelMergeSort(&args);

    if (!isSorted(arr)) {
        cout << "Error: Array is not sorted!" << endl;
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start;

    cout << "Array size: " << SIZE << endl;
    cout << "Total execution time (ms): " << duration.count() << endl;

    return 0;
}
