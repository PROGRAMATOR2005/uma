#include <iostream>
#include <limits>
#include <string>
#include <cmath> // Для округления при необходимости

using namespace std;

// Функция для безопасного ввода числа с проверкой диапазона
double correctInput(const string& prompt, const string& errorPrompt, double minValue, double maxValue) {
    double value;
    while (true) {
        cout << prompt << " (дробные числа вводите через точку): ";
        cin >> value;

        if (cin.fail()) {
            cout << "Ошибка ввода! Пожалуйста, введите число." << endl;
            cin.clear(); // Сбрасываем флаг ошибки
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очищаем буфер ввода
        } else if (value < minValue || value > maxValue) {
            cout << errorPrompt << " Диапазон: [" << minValue << ", " << maxValue << "]." << endl;
        } else {
            return value;
        }
    }
}

// Проверка принадлежности точки области
void checkPoint(double k, double b, double a) {
    double x = correctInput("Введите координату x точки (x != 0): ",
                            "Ошибка: x не должен быть равен 0 и должен быть в допустимом диапазоне!",
                            -100000.0, 100000.0);
    while (x == 0) {
        cout << "Ошибка: x не может быть равен 0. Повторите ввод." << endl;
        x = correctInput("Введите координату x точки (x != 0): ",
                         "Ошибка: x должен быть в диапазоне [-100000, 100000]!", -100000.0, 100000.0);
    }

    double y = correctInput("Введите координату y точки: ",
                            "Ошибка: y должен быть в диапазоне [-100000, 100000]!", -100000.0, 100000.0);

    double y1 = a / x; // y = a / x
    double y2 = k * x + b; // y = kx + b

    if (y >= min(y1, y2) && y <= max(y1, y2)) {
        cout << "Точка (" << x << ", " << y << ") принадлежит заданной области." << endl;
    } else {
        cout << "Точка (" << x << ", " << y << ") не принадлежит заданной области." << endl;
    }
}

// Изменение коэффициентов
void modifyCoefficients(double& k, double& b, double& a) {
    k = correctInput("Введите новый коэффициент k для уравнения y = kx + b: ",
                     "Ошибка: k не должен быть равен 0 и должен быть в диапазоне [-100000, 100000]!",
                     -100000.0, 100000.0);
    while (k == 0) {
        cout << "Ошибка: k не может быть равен 0. Повторите ввод." << endl;
        k = correctInput("Введите новый коэффициент k для уравнения y = kx + b: ",
                         "Ошибка: k должен быть в диапазоне [-100000, 100000]!", -100000.0, 100000.0);
    }

    b = correctInput("Введите новый коэффициент b для уравнения y = kx + b: ",
                     "Ошибка: b должен быть в диапазоне [-100000, 100000]!", -100000.0, 100000.0);

    a = correctInput("Введите новый коэффициент a для уравнения y = a / x: ",
                     "Ошибка: a должен быть в диапазоне [-100000, 100000]!", -100000.0, 100000.0);

    cout << "Коэффициенты успешно обновлены: k = " << k << ", b = " << b << ", a = " << a << endl;
}

// Главное меню
void displayMenu() {
    cout << "=== Главное меню ===" << endl;
    cout << "1. Проверить точку" << endl;
    cout << "2. Изменить коэффициенты a, b, k" << endl;
    cout << "3. Выйти из программы" << endl;
    cout << "=====================" << endl;
}

int main() {
    double k = 1.0, b = 0.0, a = 1.0; // Значения по умолчанию
    bool running = true;

    while (running) {
        displayMenu();
        int choice = static_cast<int>(correctInput("Выберите пункт меню (1-3): ",
                                                   "Ошибка: введите корректное число в диапазоне [1, 3]!", 1, 3));

        switch (choice) {
            case 1:
                cout << "Проверка точки..." << endl;
                checkPoint(k, b, a);
                break;
            case 2:
                cout << "Изменение коэффициентов..." << endl;
                modifyCoefficients(k, b, a);
                break;
            case 3:
                cout << "Выход из программы." << endl;
                running = false;
                break;
            default:
                cout << "Ошибка: введите 1, 2 или 3." << endl;
        }
    }

    return 0;
}