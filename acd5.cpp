#include <iostream>
#include <iomanip>
using namespace std;

// Вузол однозв’язного списку
struct Node {
    int hour;
    int minute;
    Node* next;
    Node(int h, int m, Node* n = nullptr) : hour(h), minute(m), next(n) {}
};

// Коректне введення числа
int safeInputInt() {
    int x;
    while (true) {
        cin >> x;
        if (!cin.fail()) return x;
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Помилка! Введіть число: ";
    }
}

// Нормалізація часу
void normalizeTime(int& h, int& m) {
    if (m >= 60) { h += m / 60; m %= 60; }
    if (m < 0) m = 0;
    if (h < 0) h = 0;
}

// 1) Додати елемент у порядку зростання
void addSorted(Node*& head, int h, int m) {
    normalizeTime(h, m);
    Node* newNode = new Node(h, m);
    long long newTime = h * 60 + m;

    if (!head || newTime < head->hour * 60 + head->minute) {
        newNode->next = head;
        head = newNode;
        return;
    }

    Node* cur = head;
    while (cur->next && cur->next->hour * 60 + cur->next->minute <= newTime)
        cur = cur->next;

    newNode->next = cur->next;
    cur->next = newNode;
}

// 2) Видалення голови списку
void deleteHead(Node*& head) {
    if (!head) return;
    Node* temp = head;
    head = head->next;
    delete temp;
}

// 3) Вивести елементи > заданого часу
void printGreater(Node* head, int h, int m) {
    normalizeTime(h, m);
    long long t = h * 60 + m;
    bool found = false;

    while (head) {
        long long cur = head->hour * 60 + head->minute;
        if (cur > t) {
            cout << setw(2) << setfill('0') << head->hour << ":"
                 << setw(2) << head->minute << "\n";
            found = true;
        }
        head = head->next;
    }

    if (!found) cout << "Немає елементів більших за заданий час.\n";
}

// 4) Вивести весь список у форматі "hh:mm"
void printList(Node* head) {
    if (!head) {
        cout << "Список порожній.\n";
        return;
    }
    while (head) {
        cout << setw(2) << setfill('0') << head->hour << ":"
             << setw(2) << head->minute << "\n";
        head = head->next;
    }
}

// 5) Видалити весь список
void deleteAll(Node*& head) {
    while (head) deleteHead(head);
}

// Головна функція з меню
int main() {
    Node* head = nullptr;
    int choice;

    do {
        cout << "\n===== МЕНЮ =====\n";
        cout << "1. Додати елемент (за зростанням)\n";
        cout << "2. Видалити елемент з голови списку\n";
        cout << "3. Вивести елементи > заданого часу\n";
        cout << "4. Вивести весь список (hh:mm)\n";
        cout << "5. Видалити весь список\n";
        cout << "6. Вихiд\n";
        cout << "Ваш вибір: ";

        choice = safeInputInt();

        switch (choice) {
            case 1: {
                cout << "Введіть годину: "; 
                int h = safeInputInt();
                cout << "Введіть хвилини: ";
                int m = safeInputInt();
                addSorted(head, h, m);
                cout << "Елемент додано.\n";
                break;
            }
            case 2:
                deleteHead(head);
                cout << "Голову видалено.\n";
                break;
            case 3: {
                cout << "Введіть пороговий час (години хвилини): ";
                int h = safeInputInt();
                int m = safeInputInt();
                printGreater(head, h, m);
                break;
            }
            case 4:
                printList(head);
                break;
            case 5:
                deleteAll(head);
                cout << "Список повністю видалено.\n";
                break;
            case 6:
                cout << "Вихiд...\n";
                break;
            default:
                cout << "Невірний вибір!\n";
        }

    } while (choice != 6);

    deleteAll(head);
    return 0;
}
