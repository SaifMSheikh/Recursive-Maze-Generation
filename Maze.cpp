#include <iostream>
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
using namespace std;

class Grid {
    public:
    // Grid Dimensions
    static const int height = 10;   // Default 40
    static const int width = 10;    // Default 120
    // Bool Determines Wall Status
    bool cell[height][width][4];
    bool visited[height][width];
    // Cell Stack
    stack<int> stack;
    // All Walls Initially Up
    Grid() {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                visited[y][x] = false;
                for (int i = 0; i < 4; i++) {
                    cell[y][x][i] = true;
                }
            }
        }
    }
    // Drop Specified Wall
    void Drop(int y, int x, int wall) {
        switch (wall) {
            case 0:
                cell[y][x][wall] = false;
                if (x < width - 1) {cell[y][x + 1][2] = false;}
                break;
            case 1:
                cell[y][x][wall] = false;
                if (y < height - 1) {cell[y + 1][x][3] = false;}
                break;
            case 2:
                cell[y][x][wall] = false;
                if (x > 0) {cell[y][x - 1][0] = false;}
                break;
            case 3:
                cell[y][x][wall] = false;
                 if (y > 0) {cell[y - 1][x][1] = false;}
                break;
        }
    }
    // Temporary Output Function
    void Display() {
        system("clear");
        // For Each Row
        for (int y = 0; y < height; y++) {
            // Top Walls
            for (int x = 0; x < width; x++) {
                cout << ' ';
                if (!cell[y][x][3]) {cout << "\u2588";} else {cout << ' ';}
                cout << ' ';
            }
            cout << endl;
            // Left Walls, Cells, Right Walls
            for (int x = 0; x < width; x++) {
                if (!cell[y][x][2]) {cout << "\u2588";} else {cout << ' ';}
                if (visited[y][x]) {cout << "\u2588";} else {cout << ' ';}
                if (!cell[y][x][0]) {cout << "\u2588";} else {cout << ' ';}
            }
            cout << endl;
            // Bottom Walls
            for (int x = 0; x < width; x++) {
                cout << ' ';
                if (!cell[y][x][1]) {cout << "\u2588";} else {cout << ' ';}
                cout << ' ';
            }
            cout << endl;
        }
    }
    // Recursive Backtracker
    void Check(int y, int x) {
        // usleep(100000);
        // Display();
        // Mark Current Cell As Visited
        if (!visited[y][x]) {visited[y][x] = true;}
        if (stack.empty()) {stack.push((y * 10) + x);}
        else if (y != stack.top() / 10 ||
                 x != stack.top() % 10)  
        {stack.push((y * 10) + x);}
        // Check Random Unvisited Neighbor
        int next, nextY = y, nextX = x;
        bool checked[4];
        for (int i = 0; i < 4; i++) {checked[i] = false;}
        do {
            nextY = y;
            nextX = x;
            // Randomly Choose Direction
            do {
                srand(clock());
                next = rand() % 4;
            } while (checked[next]);
            checked[next] = true;
            // Out Of Bounds Check
            switch (next) {
                case 0: // Right
                    if (x < width - 1) {nextX = x + 1;}
                    break;
                case 1: // Bottom
                    if (y < height - 1) {nextY = y + 1;}
                    break;
                case 2: // Left
                    if (x > 0) {nextX = x - 1;}
                    break;
                case 3: // Top
                    if (y > 0) {nextY = y - 1; }
                    break;
                default:
                    cout << "INVALID CELL ADDRESS";
                    return;
            }
            // If Selected Neighbor Hasn't Been Visited, Check It
            if (!visited[nextY][nextX]) {Drop(y, x, next); break;}
            else {
                // Return If All Neighbors Checked
                bool allNeighborsChecked = true;
                for (int i = 0; i < 4; i++) {if (!checked[i]) {allNeighborsChecked = false;}}
                if (allNeighborsChecked) {
                    // End Recursion If Stack Is Empty, Otherwise Backtrack
                    stack.pop();
                    if (stack.empty()) {return;}
                    else {
                        nextY = stack.top() / 10;
                        nextX = stack.top() % 10;
                        break;
                    }
                }
            }
        } while (true);
        // Check Next Cell
        Check(nextY, nextX);
    }
};