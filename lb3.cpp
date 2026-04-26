#include <iostream>
#include <cstring>
#include <iomanip>
#include <string>

using namespace std;

// ===  ===
class Date {
private:
    int day, month, year;
public:
    Date(int d = 1, int m = 1, int y = 2026) : day(d), month(m), year(y) {}
    Date& setDay(int d) { day = d; return *this; }
    Date& setMonth(int m) { month = m; return *this; }
    Date& setYear(int y) { year = y; return *this; }

    void printFull() const {
        cout << setfill('0') << setw(2) << day << "." << setw(2) << month << "." << year;
    }
    void printShort() const {
        cout << day << "/" << month << "/" << (year % 100);
    }
};

class Connection {
protected:
    char* networkName;
    int discount;
    static int total;
public:
    Connection() {
        networkName = new char[1]; networkName[0] = '\0';
        discount = 0; total++;
    }
    Connection(const char* name, int disc) {
        networkName = new char[strlen(name) + 1];
        strcpy(networkName, name);
        discount = disc; total++;
    }
    Connection(const Connection& other) {
        networkName = new char[strlen(other.networkName) + 1];
        strcpy(networkName, other.networkName);
        discount = other.discount; total++;
    }
    Connection& operator=(const Connection& other) {
        if (this == &other) return *this;
        delete[] networkName;
        networkName = new char[strlen(other.networkName) + 1];
        strcpy(networkName, other.networkName);
        discount = other.discount;
        return *this;
    }
    ~Connection() { delete[] networkName; }
    Connection& setName(const char* n) {
        delete[] networkName;
        networkName = new char[strlen(n) + 1];
        strcpy(networkName, n);
        return *this;
    }
    Connection& setDiscount(int d) { discount = d; return *this; }

    void printFull() const {
        cout << "Мережа: " << networkName << " | Пільга: " << (discount ? "Є" : "Немає") << " | Об'єктів: " << total;
    }
    void printShort() const {
        cout << "Мережа: " << networkName << " (D:" << discount << ")";
    }
};
int Connection::total = 0;

// === ===

//Подключение по контракту
class ContractConnection : public Connection {
private:
    string clientName;
    string accountNumber;
    Date openDate;      // Агрегация Date
    string qualification;
    double balance;

public:
    // Конструктор: передает данные в Connection и заполняет свои
    ContractConnection(const char* netName, int disc, string name, string acc, Date date, string qual, double bal)
        : Connection(netName, disc), clientName(name), accountNumber(acc), openDate(date), qualification(qual), balance(bal) {
        cout << "[+] Створено Контракт для " << clientName << endl;
    }

    void print() {
        cout << "--- КОНТРАКТНЕ ПІДКЛЮЧЕННЯ ---" << endl;
        Connection::printFull(); // Вызов метода базового класса
        cout << "\nКлієнт: " << clientName << " | Рахунок: " << accountNumber << endl;
        cout << "Дата відкриття: "; openDate.printFull();
        cout << " | Кваліфікація: " << qualification << " | Баланс: " << balance << " грн." << endl;
    }
};

// 2. Подключение по карточке
class CardConnection : public Connection {
private:
    string clientName;
    Date expiryDate; // Срок действия (объект Date)
    double balance;

public:
    CardConnection(const char* netName, int disc, string name, Date exp, double bal)
        : Connection(netName, disc), clientName(name), expiryDate(exp), balance(bal) {
        cout << "[+] Створено Картку для " << clientName << endl;
    }

    void print() {
        cout << "--- ПІДКЛЮЧЕННЯ ЗА КАРТКОЮ ---" << endl;
        Connection::printShort(); // Вызов метода базового класса
        cout << "\nКлієнт: " << clientName << " | Дійсна до: "; 
        expiryDate.printShort();
        cout << " | Баланс: " << balance << " грн." << endl;
    }
};

int main() {
    setlocale(LC_ALL, "ukr");

    cout << "=== ТЕСТ ІЄРАРХІЇ (БАЗОВИЙ КЛАС CONNECTION) ===" << endl << endl;

    // Создаем дату
    Date d1(15, 4, 2024);
    
    // Создаем Контракт (наследуется от Connection)
    ContractConnection conSub("Kyivstar", 1, "Олексій", "ACC-101", d1, "VIP", 500.0);
    conSub.print();

    cout << "\n------------------------------------------\n" << endl;

    // Создаем Карточку (наследуется от Connection)
    Date d2(31, 12, 2026);
    CardConnection cardSub("Vodafone", 0, "Марія", d2, 50.0);
    cardSub.print();

    return 0;
}