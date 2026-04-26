#include <iostream>
#include <cstring>
#include <iomanip>

using namespace std;


class Date {
private:
    int day, month, year;

public:
    
    Date(int d = 1, int m = 1, int y = 2026) : day(d), month(m), year(y) {}

    
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


class Connection {
private:
    char* networkName; 
    int discount;      
    static int total;  

public:
    
    Connection() {
        networkName = new char[1];
        networkName[0] = '\0';
        discount = 0;
        total++;
    }

    
    Connection(const char* name, int disc) {
        networkName = new char[strlen(name) + 1];
        strcpy(networkName, name);
        discount = disc;
        total++;
    }

    
    Connection(const Connection& other) {
        networkName = new char[strlen(other.networkName) + 1];
        strcpy(networkName, other.networkName);
        discount = other.discount;
        total++;
    }

    
    Connection& operator=(const Connection& other) {
        if (this == &other) return *this;
        delete[] networkName; 
        networkName = new char[strlen(other.networkName) + 1];
        strcpy(networkName, other.networkName);
        discount = other.discount;
        return *this;
    }


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


int main() {
    cout << "--- Тест класу Date ---" << endl;
    Date d1(17, 3, 2026); 
    d1.printFull();
    d1.printShort();

    cout << "\n--- Тест класу Connection ---" << endl;
    
    Connection c1;                            
    Connection c2("Kyivstar", 1);          
    Connection c3(c2);                        
    
    c1.setName("Lifecell").setDiscount(0);   
    
    c1.printFull();
    c2.printFull();
    c3.printShort();

    return 0;
}