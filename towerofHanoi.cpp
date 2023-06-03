/**
 * @author phanttien
 * @create date 2023-06-03 12:23:24
 * @modify date 2023-06-03 12:23:24
 * @desc tower of Hanoi
 */
#include<iostream>
using namespace std;
void move(int disc, int n, char src, char temp, char dest) {
    if (n == 1) {
        // move disc from src to dest
        cout << disc << ' ' << src << ' ' << dest << endl;   
    }
    else {
        move(disc - 1, n - 1, src, dest, temp);
        move(disc, 1, src, temp, dest);
        move(disc - 1, n - 1, temp, src, dest);
    }
}
int main() {
    cin.tie(nullptr) -> sync_with_stdio(false);
    int n; cin >> n;
    move(n, n, 'A', 'B', 'C');

    return 0;
}