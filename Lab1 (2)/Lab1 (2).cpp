#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <string>
#include <windows.h >

void input_1(std::string array_name_file, std::string array_mark) {
    int n;
    std::cout << "Введіть кількість елементів масиву '" << array_mark << "':\n";
    std::cin >> n;

    std::ofstream outFile(array_name_file); // Відкриваємо файл для запису
    if (!outFile) { // Перевіряємо, чи файл відкрився успішно
        std::cerr << "Помилка відкриття файлу для запису!\n";
        return;
    }

    std::cout << "Введіть " << n << " чисел для масиву " << array_mark << ":\n";
    for (int i = 0; i < n; ++i) {
        std::cout << "Елемент [" << i << "]: ";
        double val;
        std::cin >> val;
        outFile << val << " ";
    }
    outFile.close();
    std::cout << "Дані успішно записані.\n\n";

}

void task_2(std::string fileName) { // Функція для читання масиву з файлу та пошуку макс. парного до першого непарного
    std::ifstream inFile(fileName);
    if (!inFile) {
        std::cerr << "Файл не знайдено!\n";
        return;
    }

    // Рахуємо кількість чисел
    int count = 0;
    int temp;
    while (inFile >> temp) count++;

    if (count == 0) {
        std::cout << "Файл порожній.\n";
        return;
    }

    // Повертаємося на початок для зчитування
    inFile.clear();
    inFile.seekg(0);

    // Створюємо динамічний масив
    int* dynArr = new int[count];
    for (int i = 0; i < count; ++i) {
        inFile >> dynArr[i];
    }
    inFile.close();

    // Логіка пошуку: макс. парне до першого непарного
    int max_even = 0;
    bool found = false;

    for (int i = 0; i < count; ++i) {
        if (dynArr[i] % 2 != 0) { // Якщо непарне — стоп
            break;
        }
        if (dynArr[i] % 2 == 0) { // Якщо парне — шукаємо макс.
            if (!found || dynArr[i] > max_even) {
                max_even = dynArr[i];
                found = true;
            }
        }
    }

    // Запис результату у файл
    std::ofstream resultFile("result_data.txt");
    if (found) {
        std::string res = "Максимальний парний до першого непарного: " + std::to_string(max_even);
        std::cout << res << std::endl;
        resultFile << res;
    }
    else {
        std::string res = "Парних елементів до першого непарного не знайдено.";
        std::cout << res << std::endl;
        resultFile << res;
    }
    resultFile.close();

    std::cout << "Результати також записані у 'result_data.txt'.\n";

    delete[] dynArr; // Звільняємо пам'ять
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    
    input_1("Array_text", "A");
	task_2("Array_text");

    
    return 0;
}