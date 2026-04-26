#include <iostream>
#include <cstring>
#include <iomanip>

using namespace std;

// === КЛАС 1: ДАТА (Date) ===
class Date {
private:
    int day, month, year;

public:
    // 1. Конструктор за замовчуванням
    Date() : day(1), month(1), year(2026) {}

    // 2. Конструктор з параметрами
    Date(int d, int m, int y) : day(d), month(m), year(y) {}

    // 3. Конструктор копіювання
    Date(const Date& other) : day(other.day), month(other.month), year(other.year) {}

    // Оператор присвоєння
    Date& operator=(const Date& other) {
        if (this == &other) return *this;
        day = other.day;
        month = other.month;
        year = other.year;
        return *this;
    }

    // Деструктор
    ~Date() {}

    // Модифікатори-ланцюжки (як на фото)
    Date& setDay(int d) { day = d; return *this; }
    Date& setMonth(int m) { month = m; return *this; }
    Date& setYear(int y) { year = y; return *this; }

    void printFull() const {
        cout << "Дата: " << setfill('0') << setw(2) << day << "."
             << setw(2) << month << "." << year << endl;
    }

    void printShort() const {
        cout << "Дата (скор): " << day << "/" << month << "/" << (year % 100) << endl;
    }
};

// === КЛАС 2: ПІДКЛЮЧЕННЯ (Connection) ===
class Connection {
private:
    char* networkName; 
    int discount;      
    static int total;  

public:
    // 1. Конструктор за замовчуванням
    Connection() {
        networkName = new char[1];
        networkName[0] = '\0';
        discount = 0;
        total++;
    }

    // 2. Конструктор з параметрами
    Connection(const char* name, int disc) {
        networkName = new char[strlen(name) + 1];
        strcpy(networkName, name);
        discount = disc;
        total++;
    }

    // 3. Конструктор копіювання (Глибоке копіювання)
    Connection(const Connection& other) {
        networkName = new char[strlen(other.networkName) + 1];
        strcpy(networkName, other.networkName);
        discount = other.discount;
        total++;
    }

    // Оператор присвоєння (Deep Assignment)
    Connection& operator=(const Connection& other) {
        if (this == &other) return *this;
        delete[] networkName;
        networkName = new char[strlen(other.networkName) + 1];
        strcpy(networkName, other.networkName);
        discount = other.discount;
        return *this;
    }

    // Деструктор
    ~Connection() {
        delete[] networkName;
    }

    Connection& setName(const char* n) {
        delete[] networkName;
        networkName = new char[strlen(n) + 1];
        strcpy(networkName, n);
        return *this;
    }

    Connection& setDiscount(int d) {
        discount = d;
        return *this;
    }

    void printFull() const {
        cout << "Мережа: " << networkName 
             << " | Пільга: " << (discount ? "Є" : "Немає") 
             << " | Об'єктів: " << total << endl;
    }

    void printShort() const {
        cout << "[Connection]: " << networkName << " (D:" << discount << ")" << endl;
    }
};

int Connection::total = 0;

// === ТЕСТУВАННЯ ===
int main() {
    cout << "--- Робота з класом Date ---" << endl;
    Date d1; // Default
    Date d2(25, 12, 2025); // Parameterized
    Date d3(d2); // Copy
    
    d1.setDay(10).setMonth(3); // Chaining
    d1.printFull();
    d3.printShort();

    cout << "\n--- Робота з класом Connection ---" << endl;
    Connection c1; 
    Connection c2("Cyber_Net", 1);
    Connection c3(c2); // Перевірка копіювання динамічної пам'яті
    
    c1.setName("WiFi_Free").setDiscount(0);
    
    c1.printFull();
    c2.printFull();
    c3.printShort();

    return 0;
}