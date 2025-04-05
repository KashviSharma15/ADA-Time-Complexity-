#include <iostream>
#include <algorithm>
#include <ctime>
#include <fstream>
using namespace std;

int n_arySearch(int* array, int start, int end, int key, int i) {
    if (start > end)
        return -1;

    int cut[i];
    cut[0] = start - 1;  
    for (int j = 1; j < i; j++) {
        cut[j] = start + (j * (end - start + 1)) / i; 
    }

    for (int j = 1; j < i; j++) {
        if (array[cut[j]] == key)
            return cut[j];
        else if (array[cut[j]] > key)
            return n_arySearch(array, cut[j - 1] + 1, cut[j] - 1, key, i);
    }

    return n_arySearch(array, cut[i - 1] + 1, end, key, i);
}

int main() {
    srand(time(0));
    ofstream avgTimeFile("avgTime_nary2.txt"), keyFile("key_nary2.txt");

    for (int n = 10000; n <= 50000; n += 5000){
        int* array = new int[n];

        for (int i = 0; i < n; i++) {
            array[i] = rand() % n;
        }
        sort(array, array + n);

        int num = 10000;
        int Part[11] = {2, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21};
        double avgTimes[11] = {0}; 

        for (int i = 0; i < 11; i++) { 
            double totalDuration = 0.0;

            for (int k = 0; k < num; k++) {
                int key = rand() % (2 * n) + 8000;

                clock_t start = clock();
                int result = n_arySearch(array, 0, n - 1, key, Part[i]);
                clock_t end = clock();

                double duration = double(end - start) * 1e6 / CLOCKS_PER_SEC; 
                totalDuration += duration;

                keyFile << "Size -> " << n << " Key: " << key << " | Part: " << Part[i] << endl
                        << " * Result: " << (result != -1 ? "Found" : "Not Found")
                        << endl
                        << " * Time: " << duration << " microseconds " << endl;
            }

            avgTimes[i] = totalDuration / num;             
        }

        avgTimeFile << "n = " << n << ", Average times (microseconds):\n";
        for (int i = 0; i < 11; i++) {
            avgTimeFile << "Part " << Part[i] << " -> " << avgTimes[i] << " µs\n";
        }
        avgTimeFile << endl; 

        delete[] array; 
    }
    return 0;
}
