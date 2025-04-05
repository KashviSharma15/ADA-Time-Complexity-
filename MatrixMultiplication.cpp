#include <iostream>
#include <climits>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

int minMultiplication(int *arr, int i, int j, int **memo) {
    if (i + 1 == j) {
        return 0;
    }

    if (memo[i][j] != -1) {
        return memo[i][j];
    }

    int res = INT_MAX;

    for (int k = i + 1; k < j; k++) {
        int current = minMultiplication(arr, i, k, memo) + minMultiplication(arr, k, j, memo) + arr[i] * arr[k] * arr[j];
        res = min(current, res);
    }

    return memo[i][j] = res;
}

int main() {
    srand(time(0));
    ofstream fout("MatrixMultiplicationTime.txt");
    int n_tests = 100; 

    for (int n = 100; n <= 1000; n += 100) {
        clock_t totalTime = 0;

        for (int j = 0; j < n_tests; j++) {
            int *arr = new int[n + 1];
            int **memo = new int *[n + 1];

            for (int i = 0; i < n + 1; i++) {
                memo[i] = new int[n + 1];
                for (int k = 0; k < n + 1; k++) {
                    memo[i][k] = -1;
                }
            }

            for (int i = 0; i < n + 1; i++) {
                arr[i] = rand() % 100 + 1;
            }

            clock_t start = clock();
            minMultiplication(arr, 0, n, memo);
            clock_t end = clock();

            totalTime += (end - start);

            for (int i = 0; i < n + 1; i++) {
                delete[] memo[i];
            }
            delete[] memo;
            delete[] arr;
        }

        float avgTime = (float)totalTime / CLOCKS_PER_SEC / n_tests * 1000; 
        fout << n << "," << avgTime << endl;
    }

    fout.close();
    return 0;
}
