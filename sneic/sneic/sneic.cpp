#include <iostream>
#include <chrono>
#include <thread>
#include <Windows.h>
#include<vector>
using namespace std::chrono_literals;
std::string arena[51];
#define ARENA_HEIGHT 31
#define ARENA_WIDTH 31

struct nod {
    int i;
    int j;
};
class snake {

public:
    std::vector<nod>corp;
    snake(int n) {
        for (int i = 0; i < n; i++) {
            corp.push_back(nod{ 10,20 + i });
        }
    }
};
nod mar;
snake s(5);
void initializeArena() {

    for (int i = 0; i < ARENA_HEIGHT; i++) {
        std::string a("                                                   ");
        arena[i] = a;
    }
}
void drawArena() {
    for (int i = 0; i < ARENA_HEIGHT; i++)
    {
        arena[i][0] = '|';
        arena[i][ARENA_WIDTH - 1] = '|';
    }
    for (int i = 0; i < ARENA_WIDTH; i++)
    {
        arena[0][i] = '_';
        arena[ARENA_HEIGHT-1][i] = '_';
    } arena[s.corp[0].i][s.corp[0].j] = 'K';
    for (int i = 1; i < s.corp.size(); i++)
    {
        arena[s.corp[i].i][s.corp[i].j] = '@';
    }
    arena[mar.i][mar.j] = 'M';

}
int direction = 0;//left
int oldDirection = 0;
int score = 0;
void generateMar() {
    mar.i = rand() % (ARENA_HEIGHT-2) + 1;
    mar.j = rand() % (ARENA_WIDTH - 2) + 1;
}
void move() {
    if (direction == 0 && oldDirection == 1 || direction == 1 && oldDirection == 0) {
        direction = oldDirection;
    }
    if (direction == 2 && oldDirection == 3 || direction == 3 && oldDirection == 2) {
        direction = oldDirection;
    }
    nod oldHead = s.corp[0];
    if (direction == 0) {

        s.corp[0].j--;
        for (int i = 1; i < s.corp.size(); i++) {
            nod x = s.corp[i];
            s.corp[i] = oldHead;
            oldHead = x;
        }

    }
    if (direction == 1) {

        s.corp[0].j++;
        for (int i = 1; i < s.corp.size(); i++) {
            nod x = s.corp[i];
            s.corp[i] = oldHead;
            oldHead = x;
        }
        arena[oldHead.i][oldHead.j] = ' ';
    }
    if (direction == 2) {

        s.corp[0].i--;
        for (int i = 1; i < s.corp.size(); i++) {
            nod x = s.corp[i];
            s.corp[i] = oldHead;
            oldHead = x;
        }

    }
    if (direction == 3) {

        s.corp[0].i++;
        for (int i = 1; i < s.corp.size(); i++) {
            nod x = s.corp[i];
            s.corp[i] = oldHead;
            oldHead = x;
        }

    }
    if (s.corp[0].i == mar.i && s.corp[0].j == mar.j) {
        s.corp.push_back(oldHead);
        score++;
        generateMar();
    }
    else {
        arena[oldHead.i][oldHead.j] = ' ';
    }

}
void printArena() {
    system("cls");
    std::cout << "SCORE:" << score << "\n\n";
    for (int i = 0; i < ARENA_HEIGHT; i++) {
        std::cout << arena[i] << "\n";
    }
};
bool checkLimits() {
    if (arena[s.corp[0].i][s.corp[0].j] == '|' || arena[s.corp[0].i][s.corp[0].j] == '_') {
        return false;
    }
    for (int  i = 1; i < s.corp.size(); i++)
    {
        if (s.corp[0].i == s.corp[i].i && s.corp[0].j == s.corp[i].j) {
            return false;
        }
    }
    return true;
}int counter = 0;
bool startGame() {
    score = 0;
    snake s2(5);
    s = s2;
    while (1) {
        std::this_thread::sleep_for(17ms);
        system("cls");
        std::cout << "PRESS 'S' TO START";
        if (GetAsyncKeyState(0x53) == -32767) {
            break;
        }
    }
    initializeArena();
    while (1) {
        std::this_thread::sleep_for(34ms);
        if (GetAsyncKeyState(VK_LEFT) == -32767) {
            oldDirection = direction;
            direction = 0;
        }
        if (GetAsyncKeyState(VK_RIGHT) == -32767) {
            oldDirection = direction;
            direction = 1;
        }
        if (GetAsyncKeyState(VK_UP) == -32767) {
            oldDirection = direction;
            direction = 2;
        }
        if (GetAsyncKeyState(VK_DOWN) == -32767) {
            oldDirection = direction;
            direction = 3;
        }
        if (counter == 11) {

            counter = 0;
        }
        move();
        if (!checkLimits())
            break;
        drawArena();
        printArena();
        counter++;
    }
    return true;
}void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

int main() { 
    ShowConsoleCursor(false);
    HWND console = GetConsoleWindow();

    CONSOLE_FONT_INFOEX cf;
    cf.cbSize = sizeof cf;
    cf.nFont = 0;
    cf.dwFontSize.X = 13;
    cf.dwFontSize.Y = 13;
    cf.FontFamily = FF_DONTCARE;
    cf.FontWeight = FW_NORMAL;
    wcscpy_s(cf.FaceName, L"Consolas");
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cf);
    RECT r;
    GetWindowRect(console, &r); //stores the console's current dimensions

    MoveWindow(console, 500, 200, 700, 600,TRUE);
   
    srand(time(NULL));
    generateMar();
   
  

    while (1) {
        startGame();
        bool sapasat = false;
        while (1)
        {
            if (sapasat)
                break;
            for (int i = 0; i < s.corp.size(); i++)
            {
                arena[s.corp[i].i][s.corp[i].j] = 'X';
            }
            while (1) {
                std::this_thread::sleep_for(150ms);
                printArena();
                std::cout << "                  AI PIERDUT APASA S CA SA INCEPI" << std::endl;
                if (GetAsyncKeyState(0x53) == -32767) {
                    direction = 0;
                    sapasat = true;
                    break;
                }
            }
        }
       
    }
    return 0;
}
