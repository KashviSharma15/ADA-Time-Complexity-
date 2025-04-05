#include <iostream>
#include <algorithm>
using namespace std;

struct Activity {
    int index, start, end;
};

bool compare(Activity a, Activity b) {
    return a.end < b.end;
}

void maxActivities(int N, int S[], int F[]) {
    Activity activities[N];
    int ans[N], count = 0;

    for (int i = 0; i < N; i++) {
        activities[i].index = i + 1;
        activities[i].start = S[i];
        activities[i].end = F[i];
    }

    sort(activities, activities + N, compare);

    ans[count++] = activities[0].index;
    int endTime = activities[0].end;

    for (int i = 1; i < N; i++) {
        if (activities[i].start > endTime) {
            ans[count++] = activities[i].index;
            endTime = activities[i].end;
        }
    }
    cout << "Maximum number of activities: " << count << endl;
    cout << "Selected activities: ";
    sort(ans, ans + count);
    for (int i = 0; i < count; i++) {
        cout << ans[i] << " ";
    }
}

int main() {
    int N = 6;
    int S[] = {1, 3, 0, 5, 8, 5};
    int F[] = {2, 4, 6, 7, 9, 9};

    maxActivities(N, S, F);

    return 0;
}
