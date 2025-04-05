#include <iostream>
#include <ctime>
#include <fstream>

using namespace std;

void merge(int *array, int low, int mid, int high) {
    int n1 = mid - low + 1;
    int n2 = high - mid;
    int L[n1];
    int R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = array[low + i];
    for (int i = 0; i < n2; i++)
        R[i] = array[mid + 1 + i];

    int i = 0, j = 0, k = low;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            array[k] = L[i];
            i++;
        } else {
            array[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        array[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        array[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int low, int high) {
    if (low < high) {
        int mid = low + (high - low) / 2;
        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);
        merge(arr, low, mid, high);
    }
}

int main() {   
    srand(time(0));
    ofstream avgTimeFile("avgTimeMsort.txt"), sortFile("Msort.txt");

    for (int n = 10000; n <= 100000; n += 5000) {
        int *array = new int[n];
        for (int i = 0; i < n; i++) {
            array[i] = rand() % n;
        }

        double totalDuration = 0.0;
        int num = 10000;
        for (int k = 0; k < num; k++) {
            int *temp = new int[n];
            copy(array, array + n, temp);

            clock_t start = clock();
            mergeSort(temp, 0, n - 1);
            clock_t end = clock();

            double duration = double(end - start) * 1e6 / CLOCKS_PER_SEC;
            totalDuration += duration;

            sortFile << "Size -> " << n << endl
                     << " * Sorting complete" << endl
                     << " * Time: " << duration << " microseconds " << endl;
            
            delete[] temp;
        }

        avgTimeFile << n << " -> " << (totalDuration / num) << endl;
        delete[] array;
    }

    return 0;
}
