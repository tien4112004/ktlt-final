/**
 * @author phanttien
 * @create date 2023-06-03 11:37:40
 * @modify date 2023-06-03 11:37:40
 * @desc KURO_01
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n = 0; cin >> n;
    int m = 0; cin >> m;
    bool read[n + 1];
    int tmp = 0;
    stack<int> deck;
    while (cin >> tmp) {
        deck.push(tmp);
    }
    for (int i = 1; i <= n; i++) {
        read[i] = false;
    }
    queue<int> order;
    while (!deck.empty()) {
        int u = deck.top();
        if (!read[u]) {
            order.push(u);    
        }
        read[u] = true;
        deck.pop();
    }
    for (int i = 1; i <= n; i++) {
        if (!read[i]) {
            order.push(i);
        }
    }
    while (!order.empty()) {
        cout << order.front() << ' ';
        order.pop();
    }
    return 0;
}