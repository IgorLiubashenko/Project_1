#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    srand(time(0));

    long long size;
    cout << "Введіть розмір масиву: ";
    cin >> size;

    
    long long* asc = new long long[size];
    long long* randArr = new long long[size];
    long long* desc = new long long[size];

    for (long long i = 0; i < size; ++i) {
        asc[i] = i + 1;             
        randArr[i] = rand() % 1001; 
        desc[i] = size - i;        
    }

    
    long long comparisons = 0, swaps = 0;
    long long* stack = new long long[2 * size];
    long long top = -1;

    stack[++top] = 0;
    stack[++top] = size - 1;

    while (top >= 0) {
        long long right = stack[top--];
        long long left = stack[top--];

        long long i = left, j = right;
        long long pivot = asc[(left + right) / 2];

        while (i <= j) {
            while (asc[i] < pivot) { comparisons++; i++; }
            comparisons++;
            while (asc[j] > pivot) { comparisons++; j--; }
            comparisons++;

            if (i <= j) {
                if (i != j) {       
                    swap(asc[i], asc[j]);
                    swaps++;
                }
                i++;
                j--;
            }
        }

        if (left < j) { stack[++top] = left; stack[++top] = j; }
        if (i < right) { stack[++top] = i; stack[++top] = right; }
    }

    cout << "\nМасив по зростанню після швидкого сортування:\n";
    cout << "Порівнянь = " << comparisons << ", Обмінів = " << swaps << endl;

    
    comparisons = 0; swaps = 0;
    top = -1;
    stack[++top] = 0;
    stack[++top] = size - 1;

    while (top >= 0) {
        long long right = stack[top--];
        long long left = stack[top--];

        long long i = left, j = right;
        long long pivot = randArr[(left + right) / 2];

        while (i <= j) {
            while (randArr[i] < pivot) { comparisons++; i++; }
            comparisons++;
            while (randArr[j] > pivot) { comparisons++; j--; }
            comparisons++;

            if (i <= j) {
                if (i != j) {        
                    swap(randArr[i], randArr[j]);
                    swaps++;
                }
                i++;
                j--;
            }
        }

        if (left < j) { stack[++top] = left; stack[++top] = j; }
        if (i < right) { stack[++top] = i; stack[++top] = right; }
    }

    cout << "\nВипадковий масив після швидкого сортування:\n";
    cout << "Порівнянь = " << comparisons << ", Обмінів = " << swaps << endl;

    
    comparisons = 0; swaps = 0;
    top = -1;
    stack[++top] = 0;
    stack[++top] = size - 1;

    while (top >= 0) {
        long long right = stack[top--];
        long long left = stack[top--];

        long long i = left, j = right;
        long long pivot = desc[(left + right) / 2];

        while (i <= j) {
            while (desc[i] < pivot) { comparisons++; i++; }
            comparisons++;
            while (desc[j] > pivot) { comparisons++; j--; }
            comparisons++;

            if (i <= j) {
                if (i != j) {        
                    swap(desc[i], desc[j]);
                    swaps++;
                }
                i++;
                j--;
            }
        }

        if (left < j) { stack[++top] = left; stack[++top] = j; }
        if (i < right) { stack[++top] = i; stack[++top] = right; }
    }

    cout << "\nМасив по спаданню після швидкого сортування (по зростанню):\n";
    cout << "Порівнянь = " << comparisons << ", Обмінів = " << swaps << endl;


    delete[] asc;
    delete[] randArr;
    delete[] desc;
    delete[] stack;

    return 0;
}