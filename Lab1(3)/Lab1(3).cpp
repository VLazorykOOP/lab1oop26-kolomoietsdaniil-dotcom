#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <string>
#include <windows.h>

void randomi() {
    int n;
    std::cout << "Введіть розмір масиву для генерації: ";
    std::cin >> n;

    // Використання генератора випадкових чисел
    std::random_device rd; 
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-100, 100); // числа від 1 до 100

	double* arr = new double[n];  // Динамічно виділяємо пам'ять для масиву
    for (int i = 0; i < n; ++i) { 
        arr[i] = dis(gen); // Генеруємо випадкове число і зберігаємо його в масиві
	}
    

	std::ofstream outBin("binary_array.bin", std::ios::binary); // Відкриваємо бінарний файл для запису
    if (!outBin) {
        std::cerr << "Помилка відкриття бінарного файлу!\n";
        delete[] arr;
        return;
    }

	outBin.write(reinterpret_cast<const char*>(&n), sizeof(n)); // Записуємо розмір масиву
	outBin.write(reinterpret_cast<const char*>(arr), n * sizeof(double)); // Записуємо масив у бінарному форматі
    outBin.close();

    std::cout << "Згенеровано " << n << " чисел і записано у 'binary_array.bin'.\n\n";
    delete[] arr;
}


void task_3() {
    std::ifstream inBin("binary_array.bin", std::ios::binary); // Відкриваємо бінарний файл для читання
    if (!inBin) {
        std::cerr << "Бінарний файл не знайдено!\n";
        return;
    }
        
int n;
inBin.read(reinterpret_cast<char*>(&n), sizeof(n)); // Читаємо розмір
double* A = new double[n]; // Динамічно виділяємо пам'ять для масиву
inBin.read(reinterpret_cast<char*>(A), n * sizeof(double)); // Читаємо масив
inBin.close(); // Закриваємо файл   

std::vector<double> B; // Вектор для зберігання результатів
for (int i = 0; i < n; ++i) {
    double D = 9.0 * A[i] * A[i] - 20.0; // 9.0 * A[i] + 1.0; // Обчислюємо D
    if (D >= 0 && A[i] < 0) {
        B.push_back(A[i]); // Додаємо A[i] до вектора B, якщо D >= 0 і A[i] < 0
    }
}
    std::ofstream resFile("result.txt"); // Відкриваємо файл для запису результатів
    std::cout << "Масив B (елементи, що задовольняють умову):\n";
    for (size_t i = 0; i < B.size(); ++i) {
        std::cout << B[i] << "\t"; // Виводимо елементи масиву B на екран
        resFile << B[i] << " ";
        if ((i + 1) % 5 == 0) std::cout << "\n"; // Додаємо новий рядок після кожних 5 елементів для кращого форматування
    }
    std::cout << "\nРезультати записані у 'result.txt'\n\n";

    resFile.close();
    delete[] A;
}


int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    randomi();
	task_3();
    return 0;
}