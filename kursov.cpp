#include <iostream>
#include <string>
#include <conio.h>   
#include <windows.h> 
#include <ctime>     
#include <fstream> 

using namespace std;

const int WIDTH = 40;
const int HEIGHT = 20;
bool field[HEIGHT][WIDTH];


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

void UpdateField() {
    bool nextField[HEIGHT][WIDTH];
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
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            field[i][j] = nextField[i][j];
        }
    }
}

// 3. РОБОТА З КОНСОЛЛЮ
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


void LoadFieldFromFile() {
    system("cls");
    cout << "=== SELECT MAP FILE ===\n";
    cout << "1. Gosper Glider Gun (map1.txt)\n";
    cout << "2. Spaceships (map2.txt)\n";
    cout << "3. Pulsars (map3.txt)\n";
    cout << "Enter choice (1-3): ";
    
    int choice;
    if (!(cin >> choice)) { 
        cin.clear();
        cin.ignore(1000, '\n');
        return;
    }

    string fileName;

    
    switch (choice) {
        case 1:
            fileName = "map1.txt";
            break;
        case 2:
            fileName = "map2.txt";
            break;
        case 3:
            fileName = "map3.txt";
            break;
        default:
            fileName = "map1.txt"; 
            break;
    }

    ifstream m(fileName);

    if (!m.is_open()) {
        cout << "\n[ERROR] File " << fileName << " not found!\n";
        _getch();
        return;
    }

    
    for (int i = 0; i < HEIGHT; i++)
        for (int j = 0; j < WIDTH; j++) field[i][j] = false;

    char symbol;
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            
            m >> symbol ;
                field[i][j] = (symbol == 'X' || symbol == 'x'); 
            
        }
    }

    m.close(); 
    cout << "\n[OK] Map loaded! Press any key...";
    _getch();
}


void ShowFieldStatus() {
     system("cls");
    GoToXY(0, 0); 
    SetColor(8);
    cout << "--- Current Field Status ---" << endl;
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (field[i][j]) {
                SetColor(10); cout << "■"; 
            } else {
                SetColor(8); cout << "."; 
            }
        }
        cout << endl;
    }
    SetColor(7);
}


int ShowMenu() {
    const int cntItems = 7;
    string menuItems[cntItems] = { 
        "Start Simulation", 
        "Step by Step", 
        "Generate Random Field", 
        "Load from File", 
        "Clear Field",
        "Rules", 
        "Exit" 
    };

    int selectedItem = 0;
    while (true) {
        system("cls");
        GoToXY(0, 0);
        SetColor(10);
        cout << "==========================\n";
        cout << "    GAME OF LIFE (V.1)    \n";
        cout << "==========================\n";
        for (int i = 0; i < cntItems; i++) {
            if (i == selectedItem) {
                SetColor(11);
                cout << "  >> " << menuItems[i] << " <<  " << endl;
            } else {
                SetColor(7);
                cout << "     " << menuItems[i] << "       " << endl;
            }
            //прорисовало одно синим, остальное серым еще до моей проходки
        }
        
        int key = _getch();
        if (key == 224) {
            key = _getch();
            if (key == 72) selectedItem = (selectedItem > 0) ? selectedItem - 1 : cntItems - 1;
            if (key == 80) selectedItem = (selectedItem < cntItems - 1) ? selectedItem + 1 : 0;
        } else if (key == 13) return selectedItem;
    }
}


int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001); 
    srand(time(0)); 
    HideCursor();
    bool isRunning = true;

    while (isRunning) {
        int choice = ShowMenu();
        switch (choice) {
            case 0: // Simulation
                system("cls");
                cout << "--- SIMULATION ACTIVE ---\n";
                cout << "Press ENTER to make a step, ESC to exit to menu\n";
                ShowFieldStatus();
                while (true) {
                    if (_kbhit()) {
                        int key = _getch();
                        if (key == 13) { 
                            UpdateField(); 
                            ShowFieldStatus(); 
                        } 
                        else if (key == 27) break; 
                    }
                }
                break;

            case 1: // Step by Step
                UpdateField();
                ShowFieldStatus();
                cout << "\nGeneration passed. Press any key...";
                _getch();
                break;

            case 2: 
                for (int i = 0; i < HEIGHT; i++) {
                    for (int j = 0; j < WIDTH; j++) {
                        field[i][j] = (rand() % 5 == 0); 
                    }
                }
                ShowFieldStatus();
                SetColor(14);
                cout << "\n[OK] Generated! Press any key...";
                _getch(); 
                break;

            case 3: 
                LoadFieldFromFile();
                break;

            case 4: // Clear
                for (int i = 0; i < HEIGHT; i++)
                    for (int j = 0; j < WIDTH; j++) field[i][j] = false;
                ShowFieldStatus();
                cout << "\n[OK] Cleared! Press any key...";
                _getch();
                break;

            case 5: // Rules
        
    system("cls");
    SetColor(11); 
    cout << "====================================================\n";
    cout << "               ПРАВИЛА ГРИ \"ЖИТТЯ\"                  \n";
    cout << "====================================================\n";
    SetColor(7); 
    cout << " Всесвіт гри - це сітка з клітин, які можуть бути \n";
    cout << " 'живими' (квадрат) або 'мертвими' (крапка).\n\n";
    
    SetColor(14);
    cout << " 1. ВИЖИВАННЯ: \n";
    cout << "    Якщо у живої клітини є 2 або 3 живих сусіди, \n";
    cout << "    вона продовжує жити в наступному поколінні.\n\n";
    
    cout << " 2. СМЕРТЬ: \n";
    cout << "    - Від 'самотності': якщо сусідів менше 2.\n";
    cout << "    - Від 'перенаселення': якщо сусідів більше 3.\n\n";
    
    cout << " 3. НАРОДЖЕННЯ: \n";
    cout << "    Якщо у мертвої клітини рівно 3 живих сусіди, \n";
    cout << "    вона стає живою.\n";
    
    SetColor(8); 
    cout << "----------------------------------------------------\n";
    cout << " Натисніть будь-яку клавішу, щоб повернутися в меню...";
    _getch();
    break;

            case 6: // Exit
                isRunning = false; 
                break;
        }
    }
    return 0;
}