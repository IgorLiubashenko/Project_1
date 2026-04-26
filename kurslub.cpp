#include <iostream>
#include <vector>
#include <string>
#include <conio.h>   
#include <windows.h> 
#include <ctime>     

using namespace std;

// Размеры поля
const int WIDTH = 40;
const int HEIGHT = 20;

// ОСНОВНОЕ ПОЛЕ
vector<vector<bool>> field(HEIGHT, vector<bool>(WIDTH, false));

// --- ТВОИ ФУНКЦИИ КРАСОТЫ ---

void SetColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void GoToXY(int x, int y) {
    COORD c = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void HideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

// --- МОЯ ЧАСТЬ: ЛОГИКА ЭВОЛЮЦИИ ---

// Считаем соседей для клетки
int CountNeighbors(int y, int x) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;
            int ny = y + i;
            int nx = x + j;
            if (ny >= 0 && ny < HEIGHT && nx >= 0 && nx < WIDTH) {
                if (field[ny][nx]) count++;
            }
        }
    }
    return count;
}

// Создаем новое поколение (используем временную матрицу)
void UpdateField() {
    vector<vector<bool>> nextField(HEIGHT, vector<bool>(WIDTH, false));
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            int neighbors = CountNeighbors(i, j);
            if (field[i][j]) {
                nextField[i][j] = (neighbors == 2 || neighbors == 3);
            } else {
                nextField[i][j] = (neighbors == 3);
            }
        }
    }
    field = nextField; // Подмена матриц
}

// Функция для отрисовки статуса поля
void ShowFieldStatus() {
    GoToXY(0, 12); 
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (field[i][j]) {
                SetColor(10); cout << (char)219; // Живая (Зеленая)
            } else {
                SetColor(8); cout << "."; // Мертвая (Серая точка)
            }
        }
        cout << endl;
    }
    SetColor(7); // Сброс цвета
}

// --- ТВОЕ МЕНЮ ---

int ShowMenu() {
    vector<string> menuItems = { 
        "Start Simulation", 
        "Step by Step", 
        "Generate Random Field", 
        "Clear Field",
        "Rules", 
        "Exit" 
    };

    int selectedItem = 0;
    while (true) {
        GoToXY(0, 0);
        SetColor(10);
        cout << "==========================\n";
        cout << "    GAME OF LIFE (V.1)    \n";
        cout << "==========================\n\n";

        for (int i = 0; i < menuItems.size(); i++) {
            if (i == selectedItem) {
                SetColor(11);
                cout << "  >> " << menuItems[i] << " <<  " << endl;
            } else {
                SetColor(7);
                cout << "     " << menuItems[i] << "       " << endl;
            }
        }
        
        ShowFieldStatus();

        int key = _getch();
        if (key == 224) {
            key = _getch();
            if (key == 72) selectedItem = (selectedItem > 0) ? selectedItem - 1 : menuItems.size() - 1;
            if (key == 80) selectedItem = (selectedItem < menuItems.size() - 1) ? selectedItem + 1 : 0;
        } else if (key == 13) return selectedItem;
    }
}

// --- ГЛАВНЫЙ ЦИКЛ ---

int main() {
    srand(time(0)); 
    HideCursor();
    bool isRunning = true;

    while (isRunning) {
        int choice = ShowMenu();
        system("cls");

        switch (choice) {
            case 0: // Симуляция по нажатию ENTER
                GoToXY(0, 10);
                SetColor(14);
                cout << "Press ENTER for next step, ESC to return to menu...";
                while (true) {
                    if (_kbhit()) {
                        int key = _getch();
                        if (key == 13) { // ENTER
                            UpdateField();
                            ShowFieldStatus();
                        } else if (key == 27) { // ESC
                            break;
                        }
                    }
                }
                break;

            case 1: // Один шаг
                UpdateField();
                ShowFieldStatus();
                SetColor(14);
                cout << "\nOne generation passed. Press any key...";
                _getch();
                break;

            case 2: // Рандом 20%
                for(int i=0; i<HEIGHT; i++)
                    for(int j=0; j<WIDTH; j++)
                        field[i][j] = (rand() % 5 == 0); 
                break;

            case 3: // Очистка
                field.assign(HEIGHT, vector<bool>(WIDTH, false));
                break;

            case 4: // Правила
                SetColor(11);
                cout << "Rules:\n1. 2-3 neighbors: Life continues\n2. 3 neighbors: Life is born\n3. Others: Death\n\nPress any key...";
                _getch();
                break;

            case 5: // Выход
                isRunning = false; 
                break;
        }
        system("cls");
    }
    return 0;
}