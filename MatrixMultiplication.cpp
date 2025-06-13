#include <iostream>
#include <climits>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

int m(int * p, int i, int j, int **temp) {
    if (i + 1 == j) {
        return 0;
    }

    if (temp[i][j] != -1) {
        return temp[i][j];
    }

    int res = INT_MAX;

    for (int k = i + 1; k < j; k++) {
        int current = m(p, i, k, temp) + m(p, k, j, temp) + p[i] * p[k] * p[j];
        res = min(current, res);
    }

    return temp[i][j] = res;
}

int main() {
    srand(time(0));
    ofstream fout("MatrixMultiplicationTime.txt");
    int n = 100; 

    for (int n = 100; n <= 1000; n += 100) {
        clock_t totalTime = 0;

        for (int j = 0; j < n; j++) {
            int *p = new int[n + 1];
            int **temp = new int *[n + 1];

            for (int i = 0; i < n + 1; i++) {
                temp[i] = new int[n + 1];
                for (int k = 0; k < n + 1; k++) {
                    temp[i][k] = -1;
                }
            }

            for (int i = 0; i < n + 1; i++) {
                p[i] = rand() % 100 + 1;
            }

            clock_t start = clock();
            m(p, 0, n, temp);
            clock_t end = clock();

            totalTime += (end - start);

            for (int i = 0; i < n + 1; i++) {
                delete[] temp[i];
            }
            delete[] temp;
            delete[] p;
        }

        float avgTime = (float)totalTime / CLOCKS_PER_SEC / n * 1000; 
        fout << n << "," << avgTime << endl;
    }

    fout.close();
    return 0;
}
