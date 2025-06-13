#include <iostream>
#include <ctime>
#include <climits>
#include <cstdlib>
#include <fstream>

using namespace std;

const int MAX_N = 20;
int dist[MAX_N][MAX_N];
int dp[1 << MAX_N][MAX_N];
int n;
int VISITED_ALL;

int tsp(int mask, int pos) {
    if (mask == VISITED_ALL)
        return dist[pos][0];

    if (dp[mask][pos] != -1)
        return dp[mask][pos];

    int ans = INT_MAX;
    for (int city = 0; city < n; city++) {
        if ((mask & (1 << city)) == 0) {
            int newAns = dist[pos][city] + tsp(mask | (1 << city), city);
            ans = min(ans, newAns);
        }
    }

    return dp[mask][pos] = ans;
}

int main() {
    srand(time(0));
    const int iterations = 100;

    ofstream fout("tsp_time_data.txt");
    
    fout << "n,avg_time_sec\n";

    for (n = 2; n <= MAX_N; n++) {
        VISITED_ALL = (1 << n) - 1;
        double totalDuration = 0.0;

        for (int i = 0; i < iterations; i++) {
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    dist[i][j] = (i == j) ? 0 : rand() % 100 + 1;

            for (int i = 0; i < (1 << n); i++)
                for (int j = 0; j < n; j++)
                    dp[i][j] = -1;

            clock_t start = clock();
            tsp(1, 0);
            clock_t end = clock();

            double duration = (float)(end - start) / CLOCKS_PER_SEC;
            totalDuration += duration;
        }

        double avgDuration = totalDuration / iterations;
        fout << n << "," << avgDuration << endl;
    }

    fout.close();

    return 0;
}
