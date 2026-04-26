// Розробити ігрову програму «П’ять в рядок» відповідно до класичних
// правил між людиною та комп’ютером з фіксованим полем, передбачити два режими складності.
// Інтерфейс реалізувати в алфавітно-цифровому режимі консольного вікна.
// Керування ігровим курсором за допомогою стрілочок клавіатури.

#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>
using namespace std;

void Color(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void GoToXY(int x, int y)
{
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void invisibleCursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

const int BOARD_SIZE = 9;
int board[BOARD_SIZE][BOARD_SIZE] = {0};
int cursorX = BOARD_SIZE / 2, cursorY = BOARD_SIZE / 2;

void DrawBoard(string mode, bool isHard)
{
    GoToXY(0, 0);
    Color(3);

    cout << "\n>>  GOMOKY (" << mode << ") <<                    \n\n";
    Color(7);
    // МАЛЮЄМО ВЕРХНЮ КРИШКУ РАМКИ
    cout << "      +";
    for (int i = 0; i < BOARD_SIZE; i++)
        cout << "---";
    cout << "+\n";
    for (int y = 0; y < BOARD_SIZE; y++)
    {
        cout << "      |"; // ЛІВА СТІНКА РАМКИ
        for (int x = 0; x < BOARD_SIZE; x++)
        {
            bool isVisible = true;

            if (isHard)
            {
                isVisible = false;
                if (board[y][x] == 1)
                {
                    isVisible = true;
                }
                else
                {
                    if (y > 0 && board[y - 1][x] == 1)
                        isVisible = true;
                    if (y < BOARD_SIZE - 1 && board[y + 1][x] == 1)
                        isVisible = true;
                    if (x > 0 && board[y][x - 1] == 1)
                        isVisible = true;
                    if (x < BOARD_SIZE - 1 && board[y][x + 1] == 1)
                        isVisible = true;
                    if (y > 0 && x > 0 && board[y - 1][x - 1] == 1)
                        isVisible = true;
                    if (y > 0 && x < BOARD_SIZE - 1 && board[y - 1][x + 1] == 1)
                        isVisible = true;
                    if (y < BOARD_SIZE - 1 && x > 0 && board[y + 1][x - 1] == 1)
                        isVisible = true;
                    if (y < BOARD_SIZE - 1 && x < BOARD_SIZE - 1 && board[y + 1][x + 1] == 1)
                        isVisible = true;
                }
            }
            if (x == cursorX && y == cursorY)
                Color(30);
            else
                Color(7);
            if (!isVisible)
            {
                cout << "   ";
            }
            else
            {
                switch (board[y][x])
                {
                case 0:
                    cout << " . ";
                    break;
                case 1:
                    cout << " X ";
                    break;
                case 2:
                    cout << " O ";
                    break;
                }
            }

            Color(7);
        }
        cout << "|";
        cout << endl;
    }
    cout << "      +";
    for (int i = 0; i < BOARD_SIZE; i++)
        cout << "---";
    cout << "+\n";
    Color(8);
    cout << "\n    [Arrows] Move   [Enter] Place X   [Esc] Exit to Menu\n";
    Color(7);
}

bool CheckWin(int player)
{
    for (int y = 0; y < BOARD_SIZE; y++)
    {
        for (int x = 0; x < BOARD_SIZE; x++)
        {
            if (board[y][x] == player)
            {
                if (x <= BOARD_SIZE - 5)
                {
                    if (board[y][x + 1] == player && board[y][x + 2] == player &&
                        board[y][x + 3] == player && board[y][x + 4] == player)
                        return true;
                }
                if (y <= BOARD_SIZE - 5)
                {
                    if (board[y + 1][x] == player && board[y + 2][x] == player &&
                        board[y + 3][x] == player && board[y + 4][x] == player)
                        return true;
                }
                if (x <= BOARD_SIZE - 5 && y <= BOARD_SIZE - 5)
                {
                    if (board[y + 1][x + 1] == player && board[y + 2][x + 2] == player &&
                        board[y + 3][x + 3] == player && board[y + 4][x + 4] == player)
                        return true;
                }
                if (x >= 4 && y <= BOARD_SIZE - 5)
                {
                    if (board[y + 1][x - 1] == player && board[y + 2][x - 2] == player &&
                        board[y + 3][x - 3] == player && board[y + 4][x - 4] == player)
                        return true;
                }
            }
        }
    }
    return false;
}

int PotentialMaxLine(int x, int y, int player)
{
    int maxLine = 1; // починаємо з 1, бо маємо як мінімум одну фішку - потенційну 
    int piecesInRow; 
    int potentialX;
    int potentialY;

    // Рахуємо по горизонталі 
    piecesInRow = 1;
    potentialX = x + 1;
    while (potentialX < BOARD_SIZE && board[y][potentialX] == player)
    {
        piecesInRow++;
        potentialX++;
    } 

    potentialX = x - 1; 
    while (potentialX >= 0 && board[y][potentialX] == player)
    {
        piecesInRow++;
        potentialX--;
    } 
    
    if (piecesInRow > maxLine)
        maxLine = piecesInRow;

    // Рахуємо по вертикалі 
    piecesInRow = 1;
    potentialY = y + 1;
    while (potentialY < BOARD_SIZE && board[potentialY][x] == player)
    {
        piecesInRow++;
        potentialY++;
    } 
    
    potentialY = y - 1;
    while (potentialY >= 0 && board[potentialY][x] == player)
    {
        piecesInRow++;
        potentialY--;
    } 
    
    if (piecesInRow > maxLine)
        maxLine = piecesInRow;

    // Головна діагональ 
    piecesInRow = 1;
    potentialX = x + 1;
    potentialY = y + 1;
    while (potentialX < BOARD_SIZE && potentialY < BOARD_SIZE && board[potentialY][potentialX] == player)
    {
        piecesInRow++;
        potentialX++;
        potentialY++;
    } 

    potentialX = x - 1;
    potentialY = y - 1;
    while (potentialX >= 0 && potentialY >= 0 && board[potentialY][potentialX] == player)
    {
        piecesInRow++;
        potentialX--;
        potentialY--;
    } 
    
    if (piecesInRow > maxLine)
        maxLine = piecesInRow;

    // Побічна діагональ 
    piecesInRow = 1;
    potentialX = x + 1;
    potentialY = y - 1;
    while (potentialX < BOARD_SIZE && potentialY >= 0 && board[potentialY][potentialX] == player)
    {
        piecesInRow++;
        potentialX++;
        potentialY--;
    } 
    potentialX = x - 1;
    potentialY = y + 1;
    while (potentialX >= 0 && potentialY < BOARD_SIZE && board[potentialY][potentialX] == player)
    {
        piecesInRow++;
        potentialX--;
        potentialY++;
    } 
    if (piecesInRow > maxLine)
        maxLine = piecesInRow;
    return maxLine; 
}

void ComputerMove()
{
    // ПРІОРИТЕТ 1: Ставимо 5-й нулик
    for (int y = 0; y < BOARD_SIZE; y++)
    {
        for (int x = 0; x < BOARD_SIZE; x++)
        {
            if (board[y][x] == 0)
            {
                if (PotentialMaxLine(x, y, 2) >= 5)
                {
                    board[y][x] = 2;
                    return;
                }
            }
        }
    }
    // ПРІОРИТЕТ 2: Блокуємо 5-й хрестик гравця
    for (int y = 0; y < BOARD_SIZE; y++)
    {
        for (int x = 0; x < BOARD_SIZE; x++)
        {
            if (board[y][x] == 0)
            {
                if (PotentialMaxLine(x, y, 1) >= 5)
                {
                    board[y][x] = 2;
                    return;
                }
            }
        }
    }
    // ПРІОРИТЕТ 3: Блокуємо 4-й хрестик гравця
    for (int y = 0; y < BOARD_SIZE; y++)
    {
        for (int x = 0; x < BOARD_SIZE; x++)
        {
            if (board[y][x] == 0)
            {
                if (PotentialMaxLine(x, y, 1) == 4)
                {
                    board[y] [x] = 2;
                    return;
                }
            }
        }
    }
    // ПРІОРИТЕТ 4: Атака 
    for (int target = 4; target >= 2; target--)
    {
        for (int y = 0; y < BOARD_SIZE; y++)
        {
            for (int x = 0; x < BOARD_SIZE; x++)
            {
                if (board[y][x] == 0)
                {
                    if (PotentialMaxLine(x, y, 2) == target)
                    {
                        board[y][x] = 2;
                        return;
                    }
                }
            }
        }
    }
    // ПРІОРИТЕТ 5: Раномний хід 
    int rx, ry;
    bool moved = false;
    while (!moved)
    {
        rx = rand() % BOARD_SIZE;
        ry = rand() % BOARD_SIZE;
        if (board[ry][rx] == 0)
        {
            board[ry][rx] = 2;
            moved = true;
        }
    }
}

int Menu()
{
    string options[4] = {
        "Standard Mode",
        "Hard Mode",
        "Rules",
        "Exit"};
    int choice = 0; 
    bool inMenu = true;
    while (inMenu)
    {
        GoToXY(0, 0);
        Color(1);
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        Color(14);
        cout << ">>>    G O M O K Y    <<<\n";
        Color(1);
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        for (int i = 0; i < 4; i++)
        {
            if (i == choice)
            {
                Color(3);
                cout << " > " << options[i] << " <  " << endl;
            }
            else
            {
                Color(7);
                cout << "   " << options[i] << "    " << endl;
            }
        }
        Color(7);
        int button = _getch();
        
        if (button == 224)  // 224 - натиснута стрілочка (якась)
        {                  
            button = _getch(); 
            switch (button)
            {
            case 72: // Стрілка вгору
                choice--;
                if (choice < 0)
                    choice = 3;
                break;
            case 80: // Стрілка вниз
                choice++;
                if (choice >= 4)
                    choice = 0;
                break;
            }
        }
        else if (button == 13) // 13 -  ENTER
        {                        
            return choice; 
        }
    }
    return 0;
}

void PlayStandard()
{
    system("cls"); 
    for (int y = 0; y < BOARD_SIZE; y++)
    {
        for (int x = 0; x < BOARD_SIZE; x++)
        {
            board[y][x] = 0;
        }
    }
    cursorX = BOARD_SIZE / 2;
    cursorY = BOARD_SIZE / 2;
    bool inGame = true;

    while (inGame)
    {
        DrawBoard("Standard Mode", false);
        int button = _getch();
        if (button == 224)
        { 
            button = _getch();
            switch (button)
            {
            case 72:
                if (cursorY > 0)
                    cursorY--;
                break; 
            case 80:
                if (cursorY < BOARD_SIZE - 1)
                    cursorY++;
                break;
            case 75:
                if (cursorX > 0)
                    cursorX--;
                break; 
            case 77:
                if (cursorX < BOARD_SIZE - 1)
                    cursorX++;
                break; 
            }
        }
        else if (button == 13) 
        {
            if (board[cursorY][cursorX] == 0)
            {                                      
                board[cursorY][cursorX] = 1;       
                DrawBoard("Standard Mode", false); // Оновлюємо екран, щоб гравець побачив свій хрестик
                if (CheckWin(1))
                {
                    Color(2);
                    cout << "\n   *** CONGRATULATIONS! YOU WIN!!! ***\n";
                    cout << "     Press any key to return to menu...";
                    Color(7);
                    _getch();
                    inGame = false; 
                    continue;       // Пропускаємо хід комп'ютера і йдемо на кінець циклу
                }
                ComputerMove();                   
                DrawBoard("Standard Mode", false);
                if (CheckWin(2))                  
                {
                    Color(4);
                    cout << "\n   *** GAME OVER!! COMPUTER WINS!! ***\n";
                    cout << "     Press any key to return to menu...";
                    Color(7);
                    _getch();
                    inGame = false;
                    continue;
                }
            }
        }
        else if (button == 27) // 27 - Esc
        {
            inGame = false;
        }
    }
}

void PlayHard()
{
    system("cls"); 
    for (int y = 0; y < BOARD_SIZE; y++)
    { 
        for (int x = 0; x < BOARD_SIZE; x++)
        {
            board[y][x] = 0;
        }
    }

    cursorX = BOARD_SIZE / 2;
    cursorY = BOARD_SIZE / 2;
    bool inGame = true;
    while (inGame)
    {
        DrawBoard("Hard Mode `Fog of War`", true);
        int button = _getch();
        if (button == 224)
        {
            button = _getch();
            switch (button)
            {
            case 72:
                if (cursorY > 0)
                    cursorY--;
                break;
            case 80:
                if (cursorY < BOARD_SIZE - 1)
                    cursorY++;
                break;
            case 75:
                if (cursorX > 0)
                    cursorX--;
                break;
            case 77:
                if (cursorX < BOARD_SIZE - 1)
                    cursorX++;
                break;
            }
        }
        else if (button == 13)
        { 
            if (board[cursorY][cursorX] == 0)
            {
                board[cursorY][cursorX] = 1;
                if (CheckWin(1))
                {
                    DrawBoard("Hard Mode `Fog of War`", true); 
                    Color(2);
                    cout << "\n   *** YOU CONQUERED THE FOG! YOU WIN!!! ***\n";
                    cout << "          Press any key to return to menu...";
                    _getch();
                    inGame = false;
                    continue;
                }
                ComputerMove();
                if (CheckWin(2))
                {
                    DrawBoard("Hard Mode `Fog of War`", true);
                    Color(4);
                    cout << "\n   *** THE FOG CONSUMED YOU... COMPUTER WINS! ***\n";
                    cout << "          Press any key to return to menu...";
                    _getch();
                    inGame = false;
                    continue;
                }
            }
        }
        else if (button == 27)
        { 
            inGame = false;
        }
    }
}

void Rules()
{
    system("cls");
    Color(3);
    cout << "\n   >> GAME RULES: Gomoku (5 in a Row) <<\n\n";

    Color(7);
    cout << "   * Opponents: The game is played between Player and Computer\n";
    cout << "     on a square playing field measuring 9x9 cells.\n\n";

    cout << "   * Gameplay: Players take turns placing one of their pieces\n";
    cout << "     (X or O) on any free cell of the board.\n";
    cout << "     The user always makes the first move.\n\n";

    cout << "   * Objective: The main goal is to be the first to build a\n";
    cout << "     continuous row of exactly five of your pieces.\n\n";

    cout << "   * Directions: The winning line can be located horizontally,\n";
    cout << "     vertically, or diagonally.\n\n";

    Color(12);
    cout << "   * HARD MODE (Fog of War):\n";
    Color(7);
    cout << "     The player sees only the part of the playing field that is\n";
    cout << "     directly around the placed pieces, forcing them to act under\n";
    cout << "     conditions of incomplete information.\n\n";

    Color(8);
    cout << "   [ Press any key to return to menu ]\n";
    Color(7);

    _getch();
}
int main()
{
    srand(time(0));
    invisibleCursor();

    bool stayOpen = true;
    while (stayOpen)
    {
        int choice = Menu();
        switch (choice)
        {
        case 0:
            PlayStandard();
            break;
        case 1:
            PlayHard();
            break;
        case 2:
        Rules();
            break;
        case 3:
            stayOpen = false;
            break;
        }
        system("cls"); 
    }
    return 0;
}