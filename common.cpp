#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>

using namespace std;

string generateRandomString(int length) {
    string str = "";
    for (int i = 0; i < length; i++) {
        char c = 'A' + rand() % 26; // char c = '0' + rand() % 2;
        str += c;
    }
    return str;
}

int lcs(const string& X, const string& Y) {
    int m = X.length();
    int n = Y.length();
    int dp[m + 1][n + 1];

    for (int i = 0; i <= m; i++)
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                dp[i][j] = 0;
            else if (X[i - 1] == Y[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }

    return dp[m][n];
}

int main() {
    srand(time(0));
    ofstream fout("lcs_time.txt");
    int n = 1000;

    for (int len = 100; len <= 1000; len += 100) {
        double totalDuration = 0;

        for (int it = 0; it < n; ++it) {
            string A = generateRandomString(len);
            string B = generateRandomString(len);

            clock_t start = clock();
            lcs(A, B);
            clock_t stop = clock();

            double duration = (double)(stop - start) * 1e6 / CLOCKS_PER_SEC; 
            totalDuration += duration;
        }

        float avgDuration = totalDuration / n;
        fout << len << "," << avgDuration << endl;
    }

    fout.close();
    return 0;
}
