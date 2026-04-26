#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Введіть розмір матриці: ";
    cin >> n;

    int A[100][100];
cout << "Введіть елементи матриці: "<<endl;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> A[i][j];

   cout << "Стара матриця: " <<endl;   
for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cout << A[i][j]<< " ";
        }
            cout << endl;
        }
        

    int left = 0, right = n - 1;

    while (left < right) {
        int lastSwap = 0;

        for (int i = left; i < right; i++) {
            if (A[i][i] > A[i+1][i+1]) {
                swap(A[i][i], A[i+1][i+1]);
                lastSwap = i;
            }
        }
        right = lastSwap;

        lastSwap = left;
        for (int i = right; i > left; i--) {
            if (A[i][i] < A[i-1][i-1]) {
                swap(A[i][i], A[i-1][i-1]);
                lastSwap = i;
            }
        }
        left = lastSwap;
    }
cout<<"Відсортована матриця: "<< endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << A[i][j] << " ";
        cout << endl;
    }

    return 0;
}
