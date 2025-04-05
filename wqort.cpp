#include <iostream>
#include <ctime>
#include <fstream>
#include <algorithm>

using namespace std;

int partition(int *array, int low, int high) {
    int pivot = array[low];
    int i = low, j = high;

    while (i < j) {
        while (i <= high && array[i] <= pivot) 
            i++;
        while (j >= low && array[j] > pivot) 
            j--;
        if (i < j)
            swap(array[i], array[j]);
    }

    swap(array[low], array[j]);
    return j;
}

void quickSort(int *array, int low, int high) {
    if (low < high) {
        int j = partition(array, low, high);
        quickSort(array, low, j - 1);
        quickSort(array, j + 1, high);
    }
}

int main() {
    srand(time(0));
    ofstream avgTimeFile("avgTimeQsort(worst).txt"), sortFile("sort(worst).txt");

    for (int n = 10000; n <= 100000; n += 5000) {
        int *array = new int[n];
        for (int i = 0; i < n; i++) {
            array[i] = rand() % n;
        }
        // sort(array,array+n);
        sort(array, array + n, greater<int>());

        double totalDuration = 0.0;
        int num = 1000;
        for (int k = 0; k < num; k++) {
            int *temp = new int[n];
            copy(array, array + n, temp);

            clock_t start = clock();
            quickSort(temp, 0, n - 1);
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
