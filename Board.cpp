#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <ctime>
using namespace std;

// ============================================
// GLOBAL VARIABLES
// ============================================
const int width = 30;
const int height = 15;

int x, y, fruitX, fruitY, score;
int dx, dy;
bool gameOver;

vector<pair<int,int>> snake;

// ============================================
// BOARD AND DISPLAY MODULE
// ============================================

// Changes console text color
void color(int c) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

// Moves cursor to a fixed position
void gotoXY(int X, int Y) {
    COORD coord;
    coord.X = X;
    coord.Y = Y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Draws the complete game board
void draw() {
    gotoXY(0,0);

    color(14);
    cout << "========== SNAKE GAME ==========" << endl;
    cout << "Score: " << score << endl;

    color(10);
    for(int i=0;i<width+2;i++) cout << char(219);
    cout << endl;

    for(int i=0;i<height;i++) {
        color(10);
        cout << char(219);

        for(int j=0;j<width;j++) {
            if(i==fruitY && j==fruitX) {
                color(12);
                cout << "*";
            }
            else {
                bool printed=false;
                for(size_t k=0;k<snake.size();k++) {
                    if(snake[k].first==j && snake[k].second==i) {
                        color(k==0 ? 11 : 2);
                        cout << "O";
                        printed=true;
                        break;
                    }
                }
                if(!printed) {
                    color(7);
                    cout << " ";
                }
            }
        }

        color(10);
        cout << char(219) << endl;
    }

    color(10);
    for(int i=0;i<width+2;i++) cout << char(219);
    cout << endl;

    color(13);
    cout << "Controls: W A S D | X = Exit" << endl;
}
