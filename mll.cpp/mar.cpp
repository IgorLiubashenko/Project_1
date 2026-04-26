
#include <iostream>
#include <string>
using namespace std;

int main() {
    string s;
    cout << "Введіть фразу: ";
    getline(cin, s);

    int count = 0;


    for (size_t i = 0; i < s.length(); i++) {
        if (isdigit(s[i])) { 
            count++;
        }
    }

    cout << "Кількість цифр у фразі: " << count << endl;

    return 0;
}