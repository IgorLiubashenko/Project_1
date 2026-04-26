#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// Структура "Підключення"
struct Connection {
    string networkName;
    bool hasDiscount;
    Connection* next;
};


// 1. Додавання в кінець
void addToEnd(Connection*& head) {
    Connection* newNode = new Connection;

    cout << "Введіть назву мережі: ";
    cin >> newNode->networkName;

    cout << "Наявність пільги (1 - так, 0 - ні): ";
    cin >> newNode->hasDiscount;

    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
    } else {
        Connection* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    cout << "Елемент додано.\n";
}

// 2. Виведення списку
void printList(Connection* head) {
    if (head == NULL) {
        cout << "Список порожній.\n";
        return;
    }

    int i = 1;
    Connection* temp = head;

    while (temp != NULL) {
        cout << i << ". Мережа: " << temp->networkName;
        cout << " | Пільга: ";
        if (temp->hasDiscount)
            cout << "Так";
        else
            cout << "Ні";
        cout << endl;

        temp = temp->next;
        i++;
    }
}

// 3. Підрахунок заданої мережі
void countNetwork(Connection* head, string target) {
    int count = 0;
    Connection* temp = head;

    while (temp != NULL) {
        if (temp->networkName == target) 
            count++;
        temp = temp->next;
    }

    cout << "Кількість елементів з назвою '" 
         << target << "' = " << count << endl;
}

// 4. Додавання після k-го
void addAfterK(Connection* head, int k) {
    if (head == NULL) {
        cout << "Список порожній.\n";
        return;
    }

    Connection* temp = head;

    for (int i = 1; i < k && temp != NULL; i++) {
        temp = temp->next;
    }

    if (temp == NULL) {
        cout << "Елемент номер " << k << " не знайдено.\n";
        return;
    }

    Connection* newNode = new Connection;

    cout << "Назва нової мережі: ";
    cin >> newNode->networkName;

    cout << "Пільга (1/0): ";
    cin >> newNode->hasDiscount;

    newNode->next = temp->next;
    temp->next = newNode;

    cout << "Елемент додано.\n";
}

// 5. Поміняти k-й і j-й елементи
void swapElements(Connection* head, int k, int j) {
    if (head == NULL || k == j) {
        cout << "Обмін неможливий.\n";
        return;
    }

    Connection* nodeK = NULL;
    Connection* nodeJ = NULL;
    Connection* temp = head;

    int index = 1;

    while (temp != NULL) {
        if (index == k)
            nodeK = temp;
        if (index == j)
            nodeJ = temp;

        temp = temp->next;
        index++;
    }

    if (nodeK == NULL || nodeJ == NULL) {
        cout << "Один із елементів не знайдено.\n";
        return;
    }

    
    string tempName = nodeK->networkName;
    bool tempDiscount = nodeK->hasDiscount;

    nodeK->networkName = nodeJ->networkName;
    nodeK->hasDiscount = nodeJ->hasDiscount;

    nodeJ->networkName = tempName;
    nodeJ->hasDiscount = tempDiscount;

    cout << "Елементи поміняно місцями.\n";
}

// 6. Видалити елемент перед k-м
void deleteBeforeK(Connection*& head, int k) {
    if (head == NULL || k <= 1) {
        cout << "Видалення неможливе.\n";
        return;
    }

    if (k == 2) {
        Connection* toDelete = head;
        head = head->next;
        delete toDelete;
        cout << "Перший елемент видалено.\n";
        return;
    }

    Connection* temp = head;

    for (int i = 1; i < k - 2 && temp->next != NULL; i++) {
        temp = temp->next;
    }

    if (temp->next == NULL || temp->next->next == NULL) {
        cout << "Елемент для видалення не знайдено.\n";
        return;
    }

    Connection* toDelete = temp->next;
    temp->next = toDelete->next;
    delete toDelete;

    cout << "Елемент видалено.\n";
}

// 7. Запис у файл
void saveToFile(Connection* head) {
    ofstream fout("connections.txt");

    if (!fout) {
        cout << "Помилка відкриття файлу.\n";
        return;
    }

    Connection* temp = head;
    while (temp != NULL) {
        fout << "Мережа: " << temp->networkName;
        fout << " | Пільга: ";
        if (temp->hasDiscount)
            fout << "Так";
        else
            fout << "Ні";
        fout << endl;

        temp = temp->next;
    }

    fout.close();
    cout << "Дані збережено у connections.txt\n";
}

// Головна функція
int main() {
    Connection* list = NULL;
    int choice, k, j;
    string name;

    do {
        cout << "\n--- МЕНЮ ---\n";
        cout << "1. Додати в кінець\n";
        cout << "2. Вивести список\n";
        cout << "3. Порахувати за назвою\n";
        cout << "4. Додати після k-го\n";
        cout << "5. Поміняти k та j\n";
        cout << "6. Видалити перед k-м\n";
        cout << "7. Зберегти у файл\n";
        cout << "0. Вихід\n";
        cout << "Ваш вибір: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addToEnd(list);
                break;

            case 2:
                printList(list);
                break;

            case 3:
                cout << "Введіть назву мережі: ";
                cin >> name;
                countNetwork(list, name);
                break;

            case 4:
                cout << "Введіть k: ";
                cin >> k;
                addAfterK(list, k);
                break;

            case 5:
                cout << "Введіть k та j: ";
                cin >> k >> j;
                swapElements(list, k, j);
                break;

            case 6:
                cout << "Введіть k: ";
                cin >> k;
                deleteBeforeK(list, k);
                break;

            case 7:
                saveToFile(list);
                break;
        }

    } while (choice != 0);

    return 0;
}
