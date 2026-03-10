#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <string>
#include <windows.h >

// Функція для введення масиву з клавіатури та запису його у файл
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

// Функція для читання масиву з файлу
std::vector<double> readArrayFromFile(std::string fileName) {
	std::ifstream inFile(fileName); // Відкриваємо файл для читання
	std::vector<double> tempArray; // Тимчасовий вектор для зберігання чисел з файлу
	double val; // Змінна для зчитування чисел з файлу

    if (!inFile) {
        std::cerr << "Помилка: не вдалося відкрити файл " << fileName << std::endl;
		return tempArray; // Повертаємо порожній вектор у випадку помилки
    }

    while (inFile >> val) {
        tempArray.push_back(val);
    }

    inFile.close();
    return tempArray;
}

int main() {
    // Налаштування української мови в консолі
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    //1 варіант (Створення 2 масивів в текстовому файлі та подальше зчитування та використання у завданні 1) (f_1)
	//2 варіант (Створення 2 масивів в бінарному файлі та подальше зчитування та використання у завданні 1) (f_2)
	//3 варіант (Створення масиву в текстовому файлі та динамічне виділення та зчитування, використання у завданні 2)
	//4 варіант (Створення масиву в бінарному файлі та зчитування, використання у завданні 2)
	//5 варіант (Створення масиву в бінарному файлі та зчитування, використання у завданні 3)
        return 0; 
}

    