#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

struct Item {
    int profit;
    int weight;

    Item(int p = 0, int w = 0) : profit(p), weight(w) {}
};

int knapsack01(int W, Item arr[], int N, vector<int>& itemsChosen) {
    int** dp = new int*[N + 1];
    for (int i = 0; i <= N; ++i) {
        dp[i] = new int[W + 1]();
    }

    for (int i = 1; i <= N; ++i) {
        for (int w = 0; w <= W; ++w) {
            if (arr[i - 1].weight <= w) {
                dp[i][w] = max(arr[i - 1].profit + dp[i - 1][w - arr[i - 1].weight], dp[i - 1][w]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    int w = W;
    for (int i = N; i > 0 && w > 0; i--) {
        if (dp[i][w] != dp[i - 1][w]) {
            itemsChosen.push_back(i - 1); 
            w -= arr[i - 1].weight;  
        }
    }

    int result = dp[N][W];

    for (int i = 0; i <= N; ++i) {
        delete[] dp[i];
    }
    delete[] dp;

    return result;
}

int main() {
    const int N = 10;              
    const int W = 100;              
    Item* arr = new Item[N];       
    vector<int> itemsChosen;  
    cout << "Enter profit and weight for 10 items:\n";
    for (int i = 0; i < N; i++) {
        int profit, weight;
        cout << "Item " << i + 1 << " - Profit and Weight: ";
        cin >> profit >> weight;
        arr[i] = Item(profit, weight);
    }

    int maxProfit = knapsack01(W, arr, N, itemsChosen);
    cout << "Maximum profit: " << maxProfit << endl;
    cout << "Items chosen (bitmask): ";
    vector<int> chosenBitmask(N, 0);
    for (int index : itemsChosen) {
    chosenBitmask[index] = 1;
}
for (int bit : chosenBitmask) {
    cout << bit;
}
cout << endl;

    delete[] arr;   
    return 0;
}
