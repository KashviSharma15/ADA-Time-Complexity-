# include <iostream>
# include <ctime>
#include <fstream>
using namespace std;

int linearSearch(int * array, int size, int key) {

    for (int i = 0; i < size; i++) {
        if (array[i] == key) {
            return i+1; 
        }
    }
    return -1;
}

int main() {
    srand(time(0));
    ofstream avgTimeFile("avgTime.txt"), keyFile("key.txt");

    for (int n = 10000; n <= 100000; n += 5000){
        int * array = new int[n];
        for ( int i = 0 ; i < n ; i ++){
            array[i] = rand()%n;
        }

        double totalDuration = 0.0;
        int num = n;
        for (int k = 0; k < num; k++) {
        int key = rand()%(2*n) + 2000;
    
        clock_t start = clock();
        int result = linearSearch(array, n, key);
        clock_t end = clock();
    
    double duration = double(end - start) * 1e6 / CLOCKS_PER_SEC;
    totalDuration += duration;

    keyFile << "Size -> " << n << " Key: " << key << endl << " * Result: " << (result != -1 ? "Found" : "Not Found")
                    << endl << " * Time: " << duration << " microseconds " << endl;
    }
    avgTimeFile << n << " -> " << (totalDuration / num) << endl;
        
        delete[] array;
    }

    return 0;
}