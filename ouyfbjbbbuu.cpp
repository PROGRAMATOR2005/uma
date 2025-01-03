#include <iostream>
#include <limits>
#include <functional>
using namespace std;

// Универсальная функция для ввода данных с проверкой
template <typename T>
T correctInput(const string& prompt, const string& errorPrompt, function<bool(T)> validate = [](T) { return true; }) {
    T value;
    while (true) {
        cout << prompt;
        if (cin >> value && validate(value)) {
            return value; // Если ввод корректный и проходит проверку, возвращаем значение
        } else {
            cout << errorPrompt << endl;
            cin.clear();  // Очистка флага ошибки
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Очистка ввода
        }
    }
}

// Функция для проверки принадлежности точки области
void checkPoint(int k, int b, int a) {
    int x = correctInput<int>(
        "Введите координату x точки (x != 0): ",
        "Ошибка: x не может быть равным 0.",
        [](int val) { return val != 0; } // Проверка: x != 0
    );
    int y = correctInput<int>(
        "Введите координату y точки: ",
        "Ошибка ввода! Пожалуйста, введите число."
    );
    // Вычисление значений функций
    double y1 = static_cast<double>(a) / x; // y = a / x
    double y2 = static_cast<double>(k) * x + b; // y = kx + b
    // Проверка принадлежности точки области
    if (y >= min(y1, y2) && y <= max(y1, y2)) {
        cout << "Точка (" << x << ", " << y << ") принадлежит заданной области." << endl;
    } else {
        cout << "Точка (" << x << ", " << y << ") не принадлежит заданной области." << endl;
    }
}

// Функция для изменения коэффициентов
void modifyCoefficients(int& k, int& b, int& a) {
    k = correctInput<int>(
        "Введите новый коэффициент k для уравнения y = kx + b: ",
        "Ошибка: коэффициент k не может быть равен 0.",
        [](int val) { return val != 0; }
    );
    b = correctInput<int>(
        "Введите новый коэффициент b для уравнения y = kx + b: ",
        "Ошибка ввода! Пожалуйста, введите число."
    );
    a = correctInput<int>(
        "Введите новый коэффициент a для уравнения y = a / x: ",
        "Ошибка ввода! Пожалуйста, введите число."
    );
    cout << "Коэффициенты успешно обновлены: k = " << k << ", b = " << b << ", a = " << a << endl;
}

// Меню программы
void displayMenu() {
    cout << "=== Главное меню ===" << endl;
    cout << "1. Проверить точку" << endl;
    cout << "2. Изменить коэффициенты a, b, k" << endl;
    cout << "3. Выйти из программы" << endl;
    cout << "=====================" << endl;
}

int main() {
    int k = 1, b = 0, a = 1; // Значения по умолчанию
    bool running = true;

    while (running) {
        displayMenu();
        int choice = correctInput<int>(
            "Выберите пункт меню: ",
            "Ошибка: введите 1, 2 или 3.",
            [](int val) { return val >= 1 && val <= 3; }
        );

        switch (choice) {
            case 1: {
                cout << "Проверка точки..." << endl;
                checkPoint(k, b, a);
                break;
            }
            case 2: {
                cout << "Изменение коэффициентов..." << endl;
                modifyCoefficients(k, b, a);
                break;
            }
            case 3: {
                cout << "Выход из программы. Спасибо за использование!" << endl;
                running = false;
                break;
            }
        }
    }
    return 0;
}




