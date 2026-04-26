#include <iostream>
#include <windows.h>

using namespace std;


void drawStar(HANDLE hConsole, COORD Pos, WORD background) {
    
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    WORD oldAttr = csbi.wAttributes;

    
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | background);

    
    SetConsoleCursorPosition(hConsole, Pos);

    cout << "*"; 

    
    SetConsoleTextAttribute(hConsole, oldAttr);
}

int main() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    system("cls"); 

    
    COORD stars[10] = {
        {2,1}, {5,2}, {8,1}, {12,3}, {15,2},
        {18,1}, {3,4}, {7,3}, {10,4}, {14,3}
    };

    
    WORD backgrounds[10] = {
        BACKGROUND_BLUE, 
        BACKGROUND_GREEN, 
        BACKGROUND_RED,
        BACKGROUND_BLUE | BACKGROUND_INTENSITY,
        BACKGROUND_GREEN | BACKGROUND_INTENSITY,
        BACKGROUND_RED | BACKGROUND_INTENSITY,
        BACKGROUND_BLUE | BACKGROUND_RED,
        BACKGROUND_GREEN | BACKGROUND_RED,
        BACKGROUND_BLUE | BACKGROUND_GREEN,
        BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED
    };

   
    for (int i = 0; i < 10; i++) {
        drawStar(hConsole, stars[i], backgrounds[i]);
    }

    
    COORD pausePos = {0, 6}; 
    SetConsoleCursorPosition(hConsole, pausePos);

    system("pause"); 
    return 0;
}