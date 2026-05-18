#include <iostream>
#include <cstring>
#include <iomanip>

using namespace std;

class Date {
    int day, month, year;
public:
    Date(int d = 1, int m = 1, int y = 2026) : day(d), month(m), year(y) {}
    Date(const Date& v) : day(v.day), month(v.month), year(v.year) {}
    void printFull() const {
        cout << setfill('0') << setw(2) << day << "." << setw(2) << month << "." << year;
    }
};


class Connection {
protected: 
    char* networkName;
    int discount;
public:

    Connection() : discount(0) {
        networkName = new char[5];
        strcpy(networkName, "none");
    }
    
    Connection(const char* name, int disc) : discount(disc) {
        networkName = new char[strlen(name) + 1];
        strcpy(networkName, name);
    }
    
    Connection(const Connection& v) : discount(v.discount) {
        networkName = new char[strlen(v.networkName) + 1];
        strcpy(networkName, v.networkName);
    }
Connection& operator=(const Connection& v) {
    if (this == &v) return *this;

    delete[] networkName; 

    networkName = new char[strlen(v.networkName) + 1];
    strcpy(networkName, v.networkName);
    discount = v.discount;

    return *this;
}
    
    virtual ~Connection() { delete[] networkName; }

    virtual void printFull() const {
        cout << "Network: " << networkName << " | Discount: " << discount << "%";
    }
};


class ContractConnection : public Connection {
private:
    int accountNumber;   
    Date openDate;        
    char* qualification;
    double balance;       
public:
    ContractConnection() : Connection(), accountNumber(0), openDate(), balance(0.0) {
        qualification = new char[5];
        strcpy(qualification, "none");
    }
    ContractConnection(const char* name, int disc, int accNum, Date oDate, const char* qual, double bal) 
        : Connection(name, disc), accountNumber(accNum), openDate(oDate), balance(bal) {
        qualification = new char[strlen(qual) + 1];
        strcpy(qualification, qual);
    }
    ContractConnection(const ContractConnection& v) 
        : Connection(v), accountNumber(v.accountNumber), openDate(v.openDate), balance(v.balance) {
        qualification = new char[strlen(v.qualification) + 1];
        strcpy(qualification, v.qualification);
    }
   ContractConnection& operator=(const ContractConnection& v) {
    if (this == &v) return *this;

    Connection::operator=(v); 

    delete[] qualification;

    accountNumber = v.accountNumber;
    openDate = v.openDate;
    balance = v.balance;

    qualification = new char[strlen(v.qualification) + 1];
    strcpy(qualification, v.qualification);

    return *this;
}
    ~ContractConnection() { delete[] qualification; 
    
    }

    void printFull() const override {
        Connection::printFull(); 
        cout << " | Acc: " << accountNumber << " | Bal: " << balance << " | Qual: " << qualification;
        cout << " | Date: "; openDate.printFull(); cout << endl;
    }
};


class Clients {
private:
    char* networkTitle;              
    ContractConnection* connections; 
    int size;                        
public:

    Clients() : size(0), networkTitle(nullptr), connections(nullptr) {}

    Clients(const char* title, int n) : size(n), networkTitle(nullptr), connections(nullptr) {
        networkTitle = new char[strlen(title) + 1];
        strcpy(networkTitle, title);
        connections = new ContractConnection[size]; 
    }

    
    Clients(const Clients& x) : size(x.size), networkTitle(nullptr), connections(nullptr) {
        if (x.networkTitle) {
            networkTitle = new char[strlen(x.networkTitle) + 1];
            strcpy(networkTitle, x.networkTitle);
        }
        if (size > 0) {
            connections = new ContractConnection[size];
            for (int i = 0; i < size; i++) connections[i] = x.connections[i];
        }
    }

    

    
    ContractConnection& operator[](int i) { return connections[i]; }

    ~Clients() {
        if (networkTitle) delete[] networkTitle;
        if (connections) delete[] connections;
    }

    void showAll() const {
        cout << "\n--- Conection: " << (networkTitle ? networkTitle : "Empty") << " ---" << endl;
        for (int i = 0; i < size; i++) {
            cout << "[" << i << "] ";
            connections[i].printFull();
        }
    }
};

int main() {
    
    Clients myOffice("KPI-Net", 2);

    
    myOffice[0] = ContractConnection("Kyivstar", 10, 777, Date(1, 1, 2025), "Gold", 500.0);
    myOffice[1] = ContractConnection("Lifecell", 5, 888, Date(5, 5, 2025), "Base", 200.0);

    
    myOffice.showAll();


    Clients secondOffice = myOffice;
    cout << "\n--- КОПІЯ";
    secondOffice.showAll();

    return 0;
}