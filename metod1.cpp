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
    for (long long i = 0; i < size - 1; i++) {
        long long minIndex = i;
        for (long long j = i + 1; j < size; j++) {
            comparisons++;
            if (asc[j] < asc[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            swap(asc[i], asc[minIndex]);
            swaps++;
        }
    }
    cout << "\nМасив по зростанню після сортування вибором:\n";
    cout << "Порівнянь = " << comparisons << ", Обмінів = " << swaps << endl;

    
    comparisons = 0; swaps = 0;
    for (long long i = 0; i < size - 1; i++) {
        long long minIndex = i;
        for (long long j = i + 1; j < size; j++) {
            comparisons++;
            if (randArr[j] < randArr[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            swap(randArr[i], randArr[minIndex]);
            swaps++;
        }
    }
    cout << "\nВипадковий масив після сортування вибором:\n";
    cout << "Порівнянь = " << comparisons << ", Обмінів = " << swaps << endl;

    
    comparisons = 0; swaps = 0;
    for (long long i = 0; i < size - 1; i++) {
        long long minIndex = i;
        for (long long j = i + 1; j < size; j++) {
            comparisons++;
            if (desc[j] < desc[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            swap(desc[i], desc[minIndex]);
            swaps++;
        }
    }
    cout << "\nМасив по спаданню після сортування вибором (по зростанню):\n";
    cout << "Порівнянь = " << comparisons << ", Обмінів = " << swaps << endl;

    
    delete[] asc;
    delete[] randArr;
    delete[] desc;

    return 0;
}