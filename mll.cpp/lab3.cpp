#include <iostream>
using namespace std;

int main() {
    int y;

    cout<<"Введіть рік ";
    cin>>y;

    if (y > 0) {
        int c = (y - 1)/ 100 + 1;
        cout<<c;
       

        cout << "Це ";
        switch (c) {
            case 1:  cout << "I"; break;
            case 2:  cout << "II"; break;
            case 3:  cout << "III"; break;
            case 4:  cout << "IV"; break;
            case 5:  cout << "V"; break;
            case 6:  cout << "VI"; break;
            case 7:  cout << "VII"; break;
            case 8:  cout << "VIII"; break;
            case 9:  cout << "IX"; break;
            case 10: cout << "X"; break;
            case 11: cout << "XI"; break;
            case 12: cout << "XII"; break;
            case 13: cout << "XIII"; break;
            case 14: cout << "XIV"; break;
            case 15: cout << "XV"; break;
            case 16: cout << "XVI"; break;
            case 17: cout << "XVII"; break;
            case 18: cout << "XVIII"; break;
            case 19: cout << "XIX"; break;
            case 20: cout << "XX"; break;
            case 21: cout << "XXI"; break;
            default: cout << "століття (номер " << c << ")"; break;
            
        }

        cout << " століття" << endl;
    } 
    else {
        cout << "Рік має бути додатнім!" << endl;
    }

    return 0;
}

    
//1901 - 1 1900/100 19 +1 1899-1 1898/100 18 -  1 для кратних 100
