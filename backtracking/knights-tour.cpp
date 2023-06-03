#include<iostream>
#include<string>
#include<fstream>
#define MAX_SIZE 8
using namespace std;

void printBoard(ofstream &outDev, int board[][MAX_SIZE]) {
    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            outDev << board[i][j] << ' ';
        }
        outDev << '\n';
    }
}   

bool solveHorse(ofstream &outDev, int board[][MAX_SIZE], int x, int y, int Xindex[], int Yindex[], int count) {
    board[x][y] = count;
    for (int i = 0; i < 8; i++) {    
        if (count == MAX_SIZE*MAX_SIZE) {
            printBoard(outDev, board);
            exit(0);
        }
        if (x+Xindex[i] < MAX_SIZE && y+Yindex[i] < MAX_SIZE && x+Xindex[i] >= 0 && y+Yindex[i] >= 0 && board[x+Xindex[i]][y+Yindex[i]] == 0) { 
            solveHorse(outDev, board, x+Xindex[i], y+Yindex[i], Xindex, Yindex, count+1);
        }
    }
    board[x][y] = 0;
    return 0;
}

int main() {
    ifstream inDev;
    inDev.open("Board.txt", ios::in);
    ofstream outDev;
    outDev.open("stepHorse.txt", ios::out);
    int x; inDev >> x;
    int y; inDev >> y;
    int board[MAX_SIZE][MAX_SIZE] = {0};
    board[x][y] = 1;

    int Xindex[] = {2, 2, 1, -1, -2, -2, -1, 1};
    int Yindex[] = {1, -1, -2, -2, -1, 1, 2, 2};

    if (!solveHorse(outDev, board, x, y, Xindex, Yindex, 1)) {
        outDev << "Khong co nuoc di thoa man!";
    }
    inDev.close();
    outDev.close();
    return 0;
}