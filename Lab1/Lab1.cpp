#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <string>
#define NOMINMAX
#include <windows.h>
#include <limits>


// 1 функція: введення масиву з клавіатури та запис у текстовий файл
void input_f(std::string array_name_file, std::string array_mark) { 
    int n;
	std::cout << "Введіть кількість елементів масиву '" << array_mark << "':\n"; // Виводимо запит з позначкою масиву (A, B, X тощо)
    std::cin >> n;

	std::ofstream outFile(array_name_file); // Відкриваємо файл для запису
    if (!outFile) {
        std::cerr << "Помилка відкриття файлу для запису!\n";
        return;
    }

    std::cout << "Введіть " << n << " чисел для масиву " << array_mark << ":\n"; //
    for (int i = 0; i < n; ++i) {
        std::cout << "Елемент [" << i << "]: "; 
		int val; // Змінна для зчитування введеного числа
        std::cin >> val;
		outFile << val << " "; // Записуємо число у файл з пробілом для розділення
    }
    outFile.close();
    std::cout << "Дані успішно записані у " << array_name_file << ".\n\n";
}

// 2 функція: генерація випадкових чисел та запис у бінарний  файл
void randomi(std::string fileName) { 
    int n;
    std::cout << "Введіть кількість елементів масиву ': ";
    std::cin >> n;

	std::random_device rd; // Отримуємо випадкове зерно для генератора
	std::mt19937 gen(rd()); // Ініціалізуємо генератор випадкових чисел
    std::uniform_real_distribution<> dis(-100, 100);

	int* arr = new int[n]; // Динамічно виділяємо масив для зберігання випадкових чисел
    for (int i = 0; i < n; ++i) {
		arr[i] = dis(gen); // Генеруємо випадкове число в діапазоні від -100 до 100 і зберігаємо його в масиві
    }

	std::ofstream outBin(fileName, std::ios::binary); // Відкриваємо бінарний файл для запису
    if (!outBin) {
        std::cerr << "Помилка відкриття бінарного файлу!\n";
        delete[] arr;
        return;
    }

	outBin.write(reinterpret_cast<const char*>(&n), sizeof(n)); // Спочатку записуємо розмір масиву (кількість елементів) у файл, щоб потім знати, скільки чисел зчитувати
	outBin.write(reinterpret_cast<const char*>(arr), n * sizeof(double)); // Записуємо всі елементи масиву у файл як бінарні дані (по n елементів, кожен розміром sizeof(double))
    outBin.close();

    std::cout << "Згенеровано " << n << " чисел і записано у '" << fileName << "'.\n\n";
    delete[] arr;
}

int solve_2(const int* arr, int size, bool& found) {
	int maxEven = std::numeric_limits<int>::min(); // Ініціалізуємо змінну для зберігання максимального парного числа мінімально можливим значенням
	found = false; // Ініціалізуємо прапорець, що вказує на те, чи знайдено хоча б одне парне число

    for (int i = 0; i < size; ++i) {
		if (arr[i] % 2 != 0) { // Якщо зустрічаємо перший непарний елемент
            std::cout << "-> Зустрівся перший непарний елемент (" << arr[i] << ") на індексі " << i << ". Пошук зупинено.\n";
            break; 
        }

		if (arr[i] > maxEven) { // Якщо поточний елемент більший за знайдений максимум, оновлюємо його
            maxEven = arr[i];
			found = true; // Встановлюємо прапорець, що ми знайшли принаймні одне парне число
        }
    }

    return maxEven; // Повертаємо знайдений результат
}


void space_f(std::string inputFile, std::string outputFile) { // Читаємо дані з текстового файлу та зберігаємо їх у динамічному масиві
    std::ifstream inFile(inputFile);
    if (!inFile) {
        std::cerr << "Файл " << inputFile << " не знайдено!\n";
        return;
    }

	int count = 0; // Лічильник для визначення кількості чисел у файлі
    int temp;
	while (inFile >> temp) count++; // Підраховуємо кількість чисел у файлі, щоб знати розмір динамічного масиву

    if (count == 0) {
        std::cout << "Файл порожній.\n";
        return;
    }

	inFile.clear(); // Очищаємо флаг EOF після підрахунку
	inFile.seekg(0); // Повертаємося на початок файлу для повторного зчитування даних у динамічний масив

	int* dynArr = new int[count]; // Динамічно виділяємо масив для зберігання чисел, розмір якого визначається кількістю чисел у файлі
    std::cout << "Зчитаний масив: ";
    for (int i = 0; i < count; ++i) {
        inFile >> dynArr[i];
		std::cout << dynArr[i] << " "; // Виводимо зчитані числа на екран для підтвердження правильності зчитування
    }
    std::cout << "\n\n";
    inFile.close();

	bool isValidResult = false; // Прапорець для визначення, чи знайдено хоча б одне парне число до першого непарного
	int result = solve_2(dynArr, count, isValidResult); // Викликаємо функцію для пошуку максимального парного числа до першого непарного, передаючи динамічний масив, його розмір та змінну для збереження результату

    std::ofstream outFile(outputFile);
    if (!outFile) {
        std::cerr << "Помилка створення файлу для результату!\n";
        delete[] dynArr;
        return;
    }

    if (isValidResult) {
        std::cout << "Максимальний парний елемент до першого непарного = " << result << "\n";
        outFile << result;
    }
    else {
        std::cout << "Відповідних елементів немає.\n";
        outFile << "Відповідних елементів немає";
    }

    outFile.close();

    delete[] dynArr;
}

void solve_3(std::string inputFile) { 
	std::ifstream inFile(inputFile, std::ios::binary); // Відкриваємо бінарний файл для читання
    if (!inFile) {
        std::cerr << "Файл " << inputFile << " не знайдено!\n";
        return;
    }

    int n;
	inFile.read(reinterpret_cast<char*>(&n), sizeof(n)); // Зчитуємо розмір масиву (кількість елементів) з файлу, який ми раніше записали у функції randomi. Це дозволяє нам знати, скільки чисел потрібно зчитувати для заповнення масиву A.

    int* A = new int[n];
	inFile.read(reinterpret_cast<char*>(A), n * sizeof(int)); // Зчитуємо всі елементи масиву A з файлу як бінарні дані. Ми використовуємо reinterpret_cast для перетворення вказівника на char*, оскільки функція read працює з байтами, і ми вказуємо кількість байтів, яку потрібно зчитати (n * sizeof(int)).
    inFile.close();

    std::cout << "Зчитаний масив A:\n";
    for (int i = 0; i < n; i++) {
        std::cout << A[i] << " ";
    }
    std::cout << "\n\n";

	std::vector<int> B; // Вектор для зберігання елементів масиву A, для яких рівняння має дійсні та додатні корені

    for (int i = 0; i < n; ++i) { 
        // Рівняння: x^2 + 3A[i]x + 5 = 0
        // Рахуємо Дискримінант: D = b^2 - 4ac
        double D = (3.0 * A[i]) * (3.0 * A[i]) - 4.0 * 1.0 * 5.0;

        // За теоремою Вієта сума коренів дорівнює -b/a
        double sumRoots = -3.0 * A[i];

        // Якщо дискримінант >= 0 (дійсні корені) І сума коренів > 0 (додатні корені)
        if (D >= 0 && sumRoots > 0) {
            B.push_back(A[i]);
        }
    }

    // Виведення масиву B по 5 чисел у рядку (вимога із завдання)
    std::cout << "------------------------------------------\n";
    std::cout << "Сформований масив B (де корені дійсні і додатні):\n";

    if (B.empty()) {
        std::cout << "Таких елементів не знайдено.\n";
    }
    else {
        for (size_t i = 0; i < B.size(); ++i) {
            std::cout << B[i] << "\t"; // Табуляція для рівного відступу
            if ((i + 1) % 5 == 0) {    // Кожні 5 елементів робимо перехід на новий рядок
                std::cout << "\n";
            }
        }
        std::cout << "\n";
    }
    std::cout << "------------------------------------------\n";

    delete[] A; // Звільняємо пам'ять
}


// 4 функція: читання масиву з ТЕКСТОВОГО файлу у vector
std::vector<double> read_file(std::string fileName) { // Читаємо дані з текстового файлу та зберігаємо їх у векторі
    std::ifstream inFile(fileName);
	std::vector<double> tempArray; // Вектор для зберігання чисел, зчитаних з файлу
    double val; 

    if (!inFile) {
        std::cerr << "Файл не знайдено: " << fileName << std::endl;
        return tempArray;
    }

    while (inFile >> val) {
		tempArray.push_back(val); // Додаємо зчитане число до вектора
    }

    inFile.close();
    return tempArray;
}
void solve_1(std::string fileA, std::string fileB, std::string fileC) { // Читаємо масиви A і B з текстових файлів та обчислюємо масив C, де c[i] = a[i] * b[i]
	std::vector<double> A = read_file(fileA); // Читаємо масив A з текстового файлу у вектор
	std::vector<double> B = read_file(fileB); // Читаємо масив B з текстового файлу у вектор

	if (A.empty() || B.empty()) { // Перевірка, чи обидва масиви були успішно зчитані і не є порожніми
        std::cerr << "Помилка: Один з файлів порожній або не був зчитаний.\n";
        return;
    }

	if (A.size() != B.size()) { // Перевірка, чи мають масиви однаковий розмір
        std::cerr << "Помилка: Масиви мають різні розміри (" << A.size() << " та " << B.size() << ")!\n";
        return;
    }

	std::vector<double> C(A.size()); // Створюємо вектор C того ж розміру, що і A і B, для зберігання результатів множення
    std::ofstream outFileC(fileC);

    if (!outFileC) {
        std::cerr << "Помилка створення файлу для результату!\n";
        return;
    }

    std::cout << "------------------------------------------\n";
    std::cout << "Результат (Масив C, де c[i] = a[i] * b[i]):\n";

    for (size_t i = 0; i < A.size(); ++i) {
        C[i] = A[i] * B[i];
        std::cout << C[i] << " ";
        outFileC << C[i] << " "; // Запис у файл
    }

    std::cout << "\n\nДані масиву C успішно збережено у файл " << fileC << "\n";
    std::cout << "------------------------------------------\n";

    outFileC.close();
}


int main() {
	SetConsoleCP(65001); // Встановлюємо кодову сторінку консолі на UTF-8 для коректного відображення українських символів
    SetConsoleOutputCP(65001);


	int choice; // Змінна для зберігання вибору користувача в головному меню
    do {
        std::cout << "\n================ ГОЛОВНЕ МЕНЮ ================\n";
        std::cout << "1. Завдання 1 (Множення масивів C = A * B)\n";
        std::cout << "2. Завдання 2 (Макс. парний до першого непарного)\n";
        std::cout << "3. Завдання 3 (Масив B за коренями рівняння)\n";
        std::cout << "0. Вихід з програми\n";
        std::cout << "==============================================\n";
        std::cout << "Ваш вибір: ";
		std::cin >> choice; // Зчитуємо вибір користувача

        std::cout << "\n"; // Порожній рядок для краси

		switch (choice) { // Виконуємо відповідну функцію залежно від вибору користувача
        case 1:
            std::cout << ">>> ВИКОНАННЯ ЗАВДАННЯ 1 <<<\n";
            std::cout << "--- ЕТАП 1: ВВЕДЕННЯ МАСИВУ 'А' ---\n";
            input_f("array_A.txt", "A"); // Введення масиву A та запис у arrayA.txt
            std::cout << "--- ЕТАП 2: ВВЕДЕННЯ МАСИВУ 'B' ---\n";
            input_f("array_B.txt", "B"); // Введення масиву B та запис у arrayB.txt
			std::cout << "--- ЕТАП 3: ОБЧИСЛЕННЯ МАСИВУ 'C' ---\n";
            solve_1("array_A.txt", "array_B.txt", "array_C.txt");
            break;
        case 2: {
            std::cout << ">>> ВИКОНАННЯ ЗАВДАННЯ 2 <<<\n";
			std::string inputFile = "array_data.txt"; // Файл для введення даних масиву (можна змінити на інший, якщо потрібно)
			std::string outputFile = "result_data.txt"; // Файл для збереження результату (максимального парного числа або повідомлення про відсутність відповідних елементів)

            std::cout << "--- ЕТАП 1: ВВЕДЕННЯ ДАНИХ ---\n";
			input_f(inputFile, "X"); // Введення даних для масиву X та запис у inputFile (array_data.txt)

            std::cout << "--- ЕТАП 2: ОБЧИСЛЕННЯ ЧЕРЕЗ ДИНАМІЧНИЙ МАСИВ ---\n";
			space_f(inputFile, outputFile); //  Читаємо дані з inputFile, обчислюємо результат і зберігаємо його у outputFile
            break;
        }
        case 3: { 
                std::cout << ">>> ВИКОНАННЯ ЗАВДАННЯ 3 <<<\n";
				std::string binaryFile = "array_A.bin"; // Файл для збереження згенерованого масиву у бінарному форматі

				std::cout << "=== ЕТАП 1: ГЕНЕРАЦІЯ МАСИВУ В БІНАРНИЙ ФАЙЛ ===\n"; 
                randomi(binaryFile);

                std::cout << "=== ЕТАП 2: РОЗРАХУНОК КОРЕНІВ ТА ПОБУДОВА МАСИВУ B ===\n";
                solve_3(binaryFile);
                break;
            }
        case 0:
            std::cout << "Роботу завершено.\n";
            break;
        default:
            std::cout << "Помилка: Невірний вибір. Введіть число від 0 до 3.\n";
        }
    } while (choice != 0);






        return 0; 
}

    