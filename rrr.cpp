#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream file("m.txt"); // відкриваємо файл

    if (!file.is_open()) {
        std::cout << "Не вдалося відкрити файл!" << std::endl;
        return 1;
    }

    std::string line;

    // читаємо файл пострічково
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }

    file.close(); // закриваємо файл

    return 0;
}

