#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

#define MAX 100

int array_check(int *array, int N, bool(*func)(int)) {
    int count = 0;
    for (int i = 0; i < N; i++) {
        if (func(array[i])) count++;
    }
    return count;
}

bool isSquare(int a) {
    if (a < 0) return false;
    for (int i = 0; i*i <= a; i++) {
        if (i*i == a) return true;
    }
    return false;
}

bool doesContainFive(int a) {
    a = abs(a);
    while (a > 0) {
        if (a % 10 == 5) return true;
        a /= 10;
    }
    return false;
}

void genArray(int *array, int N) {
    for (int i = 0; i < N; i++) {
        array[i] = -100 + rand() % 201;
    }
}

int main() {
    srand(time(0));
    int N;
    cout << "Введіть розмірність масиву: ";
    cin >> N;

    int array[MAX];
    char ask;
    cout << "Згенерувати масив випадковим чином? (y/n): ";
    do {
        ask = getchar();
    } while (toupper(ask) != 'Y' && toupper(ask) != 'N');

    if (toupper(ask) == 'N') {
        cout << "Введіть елементи масиву: ";
        for (int i = 0; i < N; i++) cin >> array[i];
    } else {
        genArray(array, N);
    }

    cout << "Масив: ";
    for (int i = 0; i < N; i++) {
        cout << array[i] << " ";
    }
    cout << endl;

    int squares = array_check(array, N, isSquare);
    cout << "Кількість елементів, що є квадратом числа: " << squares << endl;

    int fives = array_check(array, N, doesContainFive);
    cout << "Кількість елементів, що містять цифру 5: " << fives << endl;

    return 0;
}