#include <bits/stdc++.h>
using namespace std;

int main() {
    deque<char> q;
    q.push_back('a');
    q.push_back('b');
    q.push_back('c');
    q.push_back('d');
    q.push_back('e');
    q.push_back('f');
    q.push_back('g');
    
    cout << q.size() << '\n';
    cout << q[0] << '\n';
    cout << q[3] << '\n';
    cout << q[6] << '\n';
}