#include <iostream>
#include <cstring>
#include <iomanip>

using namespace std;

// === ТВОЙ КОД ИЗ ПРОШЛОЙ ЛАБЫ (ОДИН В ОДИН) ===

class Date {
private:
    int day, month, year;
public:
    Date(int d = 1, int m = 1, int y = 2026) {
        day = d; month = m; year = y;
    }
    Date(const Date& a) {
        day = a.day; month = a.month; year = a.year;
    }
    ~Date() {}

    Date& setDay(int d) { day = d; return *this; }
    Date& setMonth(int m) { month = m; return *this; }
    Date& setYear(int y) { year = y; return *this; }

    int getDay() { return day; }
    int getMonth() { return month; }
    int getYear() { return year; }

    void printFull() const {
        cout << setfill('0') << setw(2) << day << "." << setw(2) << month << "." << year;
    }
    void printShort() const {
        cout << day << "/" << month << "/" << (year % 100);
    }
};

class Connection {
protected: // Изменил private на protected, чтобы наследники видели поля
    char* networkName;
    int discount;
    static int total;

public:
    Connection() {
        networkName = new char[8];
        strcpy(networkName, "Noname");
        discount = 0;
        total++;
        cout << "Student()" << endl; // Оставил твои метки для отслеживания
    }

    Connection(const char* n, int d) {
        networkName = new char[strlen(n) + 1];
        strcpy(networkName, n);
        discount = d;
        total++;
        cout << "Student(par)" << endl;
    }

    Connection(const Connection& a) {
        networkName = new char[strlen(a.networkName) + 1];
        strcpy(networkName, a.networkName);
        discount = a.discount;
        total++;
        cout << "Student(Student&)" << endl;
    }

    virtual ~Connection() { // Добавил virtual для безопасности деструкторов
        cout << "~Student()" << endl;
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
        cout << "Мережа: " << networkName << " | Пільга: " << (discount ? "Так" : "Ні");
    }

    static int getTotal() { return total; }
};

int Connection::total = 0;

// === ДОПИСЫВАЕМ НОВУЮ ЛАБОРАТОРНУЮ (ВАРИАНТ 25) ===

// 1. Наследник "За контрактом"
class Contract : public Connection {
private:
    int accountNumber;
    Date openDate;
    int qualification;
    double balance;

public:
    // Конструктор с параметрами (тот самый "разговор" через двоеточие)
    Contract(const char* n, int d, int acc, Date date, int qual, double bal) 
        : Connection(n, d), accountNumber(acc), openDate(date), qualification(qual), balance(bal) {
        cout << "Headman(par)" << endl;
    }

    // Конструктор копирования
    Contract(const Contract& a) 
        : Connection(a), accountNumber(a.accountNumber), openDate(a.openDate), 
          qualification(a.qualification), balance(a.balance) {
        cout << "Headman(Headman&)" << endl;
    }

    ~Contract() {
        cout << "~Headman()" << endl;
    }

    void printFull() const {
        Connection::printFull(); // Используем прототип базового класса
        cout << " | Рахунок: " << accountNumber << " | Баланс: " << balance << " грн" << endl;
        cout << "   Дата відкриття: "; openDate.printFull();
        cout << " | Кваліфікація: " << qualification << endl;
    }
};

// 2. Наследник "За карткою"
class Card : public Connection {
private:
    Date endDate;
    double balance;

public:
    Card(const char* n, int d, Date date, double bal) 
        : Connection(n, d), endDate(date), balance(bal) {
        cout << "Headman(par) [Card]" << endl;
    }

    ~Card() {
        cout << "~Headman() [Card]" << endl;
    }

    void printFull() const {
        Connection::printFull();
        cout << " | Тип: Картка | Баланс: " << balance << " грн | Дійсна до: ";
        endDate.printShort();
        cout << endl;
    }
};

// === ТЕСТОВАЯ ЧАСТЬ (MAIN) ===

int main() {Date d1(15, 10, 2023);
    Date d2(31, 12, 2025);

    cout << "--- Створення об'єктів ---" << endl;
    
    Contract c1("Kyivstar", 1, 123456, d1, 5, 250.0);
    c1.printFull();
    
    cout << endl;

    Card p1("Lifecell", 0, d2, 50.0);
    p1.printFull();

    cout << endl << "--- Тест копіювання ---" << endl;
    Contract c2(c1); // Тут сработает конструктор копии
    c2.printFull();

    cout << endl << "--- Кінець програми ---" << endl;
    return 0;
}