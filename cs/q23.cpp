#include <bits/stdc++.h>
using namespace std;

bool meetingRooms(vector<vector<int>> intervals) {
    sort(intervals.begin(), intervals.end());

    for (int i = 1; i < intervals.size(); ++i) {
        if (intervals[i-1][1] >= intervals[i][0]) return false;
    }

    return true;
}

int meetingRoomsII(vector<vector<int>> intervals) {
    sort(intervals.begin(), intervals.end());

    priority_queue<int, vector<int>, greater<int>> endTimes;

    for (auto& interval : intervals) {
        if (!endTimes.empty() && interval[1] >= endTimes.top()) {
            endTimes.pop();
        } 
        endTimes.push(interval[1]);
    }

    return endTimes.size();
}

int main() {
    vector<vector<int>> test1 = {{0,30},{15,20},{5,10}};
    vector<vector<int>> test2 = {{7,10},{2,4}};

    cout << boolalpha << meetingRooms(test1) << '\n';
    cout << boolalpha << meetingRooms(test2) << '\n';

    cout << meetingRoomsII(test1) << '\n';
    cout << meetingRoomsII(test2) << '\n';
}
