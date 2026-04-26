#include <iostream>
#include <vector>
#include <string>
#include <conio.h>   
#include <windows.h> 
#include <ctime>   

using namespace std;

// Розміри поля
const int WIDTH = 40;
const int HEIGHT = 20;

// ОСсновне поле двумерная сетка
bool field[HEIGHT][WIDTH];

//new
// 1. ФУНКЦИЯ ПОДСЧЕТА СОСЕДЕЙ
int CountNeighbors(int y, int x) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue; // Пропускаем 

            int ny = y + i;
            int nx = x + j;

            // Проверяем, что не вышли за границы массива
            if (ny >= 0 && ny < HEIGHT && nx >= 0 && nx < WIDTH) {
                if (field[ny][nx]) {
                    count++;
                }
            }
        }
    }
    return count;
}


void UpdateField() {
    // Создаем временную сетку, заполненную мертвыми клетками (false)
    bool nextField[HEIGHT][WIDTH]={false};

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            int neighbors = CountNeighbors(i, j); // Используем функцию из Шага 1

            if (field[i][j]) {
                // Живая клетка остается жить, если у нее 2 или 3 соседа
                nextField[i][j] = (neighbors == 2 || neighbors == 3);
            } else {
                //  В пустой клетке рождается жизнь, если соседей ровно 3
                nextField[i][j] = (neighbors == 3);
            }
        }
    }
    // заменяем старое поле новым
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            field[i][j] = nextField[i][j];
        }
    }
}

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

//, що зараз на полі
void ShowFieldStatus() {
    system ("cls");
    GoToXY(0, 12); // Малюємо під меню
    SetColor(8);
    
    cout << "--- Current Field Status ---" << endl;
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (field[i][j]) {
                SetColor(10); cout << "■"; // Жива клітина
            } else {
                SetColor(8);
                 cout << (char)46; // Порожнє місце
            }
        }
        cout << endl;
    }
     SetColor(7);
}

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
       
        system ("cls");
       GoToXY(0, 0);
        SetColor(10);
        cout << "==========================\n";
        cout << "    GAME OF LIFE (V.1)    \n";
        cout << "==========================\n";
        for (int i = 0; i < menuItems.size(); i++) {
            if (i == selectedItem) {
                SetColor(11);
                cout << "  >> " << menuItems[i] << " <<  " << endl;
            } else {
                SetColor(7);
                cout << "     " << menuItems[i] << "       " << endl;
            }
        }
        

       

        int key = _getch();
        if (key == 224) {
            key = _getch();
            if (key == 72) selectedItem = (selectedItem > 0) ? selectedItem - 1 : menuItems.size() - 1;
            if (key == 80) selectedItem = (selectedItem < menuItems.size() - 1) ? selectedItem + 1 : 0;
        } else if (key == 13) return selectedItem;
    }
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001); // Устанавливает кодировку UTF-8 (чтобы точка была точкой)
    srand(time(0)); // Ініціалізація рандому
    HideCursor();
    bool isRunning = true;

    while (isRunning) {
        
        int choice = ShowMenu();


        switch (choice) {
            case 0: 
               // Start Simulation (Режим с ENTER)
                cout << "--- SIMULATION ACTIVE ---\n";
                cout << "Press ENTER to make a step, ESC to exit to menu\n";
                while (true) {
                    if (_kbhit()) {

                        int key = _getch();
                        if (key == 13) { // Клавиша ENTER
                            UpdateField();    // Считаем
                            ShowFieldStatus(); // Рисуем
                        } 
                        else if (key == 27) break; // ESC — выходим из цикла симуляции
                    }
                }
                break;
                    case 1: // Step by Step (Один шаг)
                UpdateField();
                ShowFieldStatus();
                cout << "\nGeneration passed. Press any key...";
                _getch();
                break;
            case 2:
         // Заполнение поля случайными клетками
    
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            field[i][j] = (rand() % 5 == 0); 
        }
    }


    //system("cls");

    
    ShowFieldStatus();

    
    SetColor(14); // Желтый
    cout << "\n[OK] Field generated! Press any key to return to menu...";
    _getch(); 
    break; 
            case 3:
    // Проходимо по кожному рядку і кожному стовпчику нашого масиву
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            
    }
    cout << "Поле заповнено випадковими клітинами!";
    _getch();
    break;
            case 4: /* ShowRules(); */ break;
            case 5: isRunning = false; break;
        }
        system("cls");
    }
    return 0;
}