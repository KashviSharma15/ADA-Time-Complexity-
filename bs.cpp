#include <iostream>
#include <algorithm>
# include <ctime>
#include <fstream>
using namespace std;

int binarySearch(int * array, int size, int key) {

    int low = 0;
    int high = size - 1;

    while (low <= high) {
        int mid = (low + high) / 2; 

        if (array[mid] == key) {
            return mid; 
        } 
        else if (array[mid] < key) {
            low = mid + 1;
        } 
        else {
            high = mid - 1;
        }

    }
    return -1;
}

int main() {
    srand(time(0));
    ofstream avgTimeFile("avgTimeBinary.txt"), keyFile("keyBinary.txt");

    for (int n = 10000; n <= 100000; n += 5000){
        int * array = new int[n];
        for ( int i = 0 ; i < n ; i ++){
            array[i] = rand()%n;
        }
        sort(array, array + n);

        double totalDuration = 0.0;
        int num = 1000000;
        for (int k = 0; k < num; k++) {
        int key = rand()%(n);
    
        clock_t start = clock();
        int result = binarySearch(array, n, key);
        clock_t end = clock();
    
    double duration = double(end - start) * 1e9 / CLOCKS_PER_SEC;
    totalDuration += duration;

    keyFile << "Size -> " << n << " Key: " << key << endl << " * Result: " << (result != -1 ? "Found" : "Not Found")
                    << endl << " * Time: " << duration << " nanoseconds " << endl;
    }
    avgTimeFile << n << " -> " << (totalDuration / num) << endl;
        
        delete[] array;
    }

    return 0;
}