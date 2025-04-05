#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Item {
    double weight, profit;
};

bool compare(Item a, Item b) {
    return (a.profit / a.weight) > (b.profit / b.weight);
}

double fractionalKnapsack(Item* items, int N, double capacity) {
    sort(items, items + N, compare);
    double totalprofit = 0.0;

    for (int i = 0; i < N; i++) {
        if (capacity >= items[i].weight) {
            totalprofit += items[i].profit;
            capacity -= items[i].weight;
        } else {
            totalprofit += items[i].profit * (capacity / items[i].weight);
            break;
        }
    }
    return totalprofit;
}

int main() {
    srand(time(0));
    ofstream resultsFile("AnalysisKnapsack.txt");
    double capacity = 10000;

    for (int N = 10000; N <= 100000; N += 10000) {
        Item* items = new Item[N];
        double total_duration = 0;

        for (int i = 1; i <= 1000; i++) {
            for (int i = 0; i < N; i++) {
                items[i].weight = (rand() % 100) + 1;
                items[i].profit = (rand() % 100) + 1;
            }

            clock_t start = clock();
            double maxprofit = fractionalKnapsack(items, N, capacity);
            clock_t end = clock();
            total_duration += (double)(end - start) * 1e6 / CLOCKS_PER_SEC;

            cout << "n" << i << " Items: " << N << " -> Max Profit: " << maxprofit << endl;
        }

        resultsFile << "Items = " << N << ", Average Time = " << total_duration / 1000.0 << " microseconds.\n";

        delete[] items;
    }

    resultsFile.close();
    return 0;
}

