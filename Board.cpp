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

// ============================================
// MOVEMENT AND GAME LOGIC MODULE
// ============================================

// Reads keyboard input and controls movement
void input() {
    if(_kbhit()) {
        switch(_getch()) {
            case 'a': if(dx!=1){dx=-1;dy=0;} break;
            case 'd': if(dx!=-1){dx=1;dy=0;} break;
            case 'w': if(dy!=1){dx=0;dy=-1;} break;
            case 's': if(dy!=-1){dx=0;dy=1;} break;
            case 'x': gameOver=true; break;
        }
    }
}

// Handles movement, collision, and food eating
void logic() {
    pair<int,int> head = snake.front();
    head.first += dx;
    head.second += dy;

    if(head.first<0 || head.first>=width ||
       head.second<0 || head.second>=height)
        gameOver = true;

    for(size_t i=0;i<snake.size();i++)
        if(head==snake[i]) gameOver=true;

    snake.insert(snake.begin(), head);

    if(head.first==fruitX && head.second==fruitY) {
        score += 10;
        fruitX = rand()%width;
        fruitY = rand()%height;
    } else {
        snake.pop_back();
    }
}

// ============================================
// MAIN FUNCTION
// ============================================

int main() {
    setup();

    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO ci;
    ci.dwSize = 100;
    ci.bVisible = FALSE;
    SetConsoleCursorInfo(h, &ci);

    while(!gameOver) {
        draw();      // Board module
        input();     // Movement module
        logic();     // Food + game logic module
        Sleep(120);
    }

    color(12);
    cout << "\\nGAME OVER! Final Score: " << score << endl;
    color(7);

    return 0;
}

