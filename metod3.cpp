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

    long long comparisons, moves;

    
    comparisons = 0; 
    moves = 0;

    long long maxVal = asc[0];
    for (long long i = 1; i < size; i++) {
        if (asc[i] > maxVal)
            maxVal = asc[i];
    }

    for (long long exp = 1; maxVal / exp > 0; exp *= 10) {
        long long count[10] = {0};

        for (long long i = 0; i < size; i++) {
            long long digit = (asc[i] / exp) % 10;
            count[digit]++;
        }

        for (int i = 1; i < 10; i++)
            count[i] += count[i - 1];

        long long* output = new long long[size];
        for (long long i = size - 1; i >= 0; i--) {
            long long digit = (asc[i] / exp) % 10;
            output[count[digit] - 1] = asc[i];
            count[digit]--;
            moves++;  
        }

        for (long long i = 0; i < size; i++) {
            asc[i] = output[i];
            moves++; 
        }
        delete[] output;
    }

    cout << "\nМасив по зростанню після сортування:\n";
    cout << "Порівнянь = " << comparisons << ", Переміщень = " << moves << endl;


    comparisons = 0;
    moves = 0;

    maxVal = randArr[0];
    for (long long i = 1; i < size; i++) {
        if (randArr[i] > maxVal)
            maxVal = randArr[i];
    }

    for (long long exp = 1; maxVal / exp > 0; exp *= 10) {
        long long count[10] = {0};
        for (long long i = 0; i < size; i++) {
            long long digit = (randArr[i] / exp) % 10;
            count[digit]++;
        }

        for (int i = 1; i < 10; i++)
            count[i] += count[i - 1];

        long long* output = new long long[size];
        for (long long i = size - 1; i >= 0; i--) {
            long long digit = (randArr[i] / exp) % 10;
            output[count[digit] - 1] = randArr[i];
            count[digit]--;
            moves++;
        }

        for (long long i = 0; i < size; i++) {
            randArr[i] = output[i];
            moves++;
        }
        delete[] output;
    }

    cout << "\nВипадковий масив після сортування:\n";
    cout << "Порівнянь = " << comparisons << ", Переміщень = " << moves << endl;

    
    comparisons = 0;
    moves = 0;

    maxVal = desc[0];
    for (long long i = 1; i < size; i++) {
        if (desc[i] > maxVal)
            maxVal = desc[i];
    }

    for (long long exp = 1; maxVal / exp > 0; exp *= 10) {
        long long count[10] = {0};
        for (long long i = 0; i < size; i++) {
            long long digit = (desc[i] / exp) % 10;
            count[digit]++;
        }

        for (int i = 1; i < 10; i++)
            count[i] += count[i - 1];

        long long* output = new long long[size];
        for (long long i = size - 1; i >= 0; i--) {
            long long digit = (desc[i] / exp) % 10;
            output[count[digit] - 1] = desc[i];
            count[digit]--;
            moves++;
        }

        for (long long i = 0; i < size; i++) {
            desc[i] = output[i];
            moves++;
        }
        delete[] output;
    }

    cout << "\nМасив по спаданню після сортування (відсортований по зростанню):\n";
    cout << "Порівнянь = " << comparisons << ", Переміщень = " << moves << endl;

    delete[] asc;
    delete[] randArr;
    delete[] desc;

    return 0;
}