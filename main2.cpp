#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <sstream>
#include <algorithm>

using namespace std;

class MedicalSystem {
private:
    int load;
    double coef, hosp, resources, seasonal;

public:
    MedicalSystem(int l, double c, double h, double r, double s) 
        : load(l), coef(c), hosp(h), resources(r), seasonal(s) {}

    void showResults() {
        double forecastValue = calculateLoad();
        string forecastSign = forecastValue >= 0 ? "+" : "";
        cout << fixed << setprecision(0);
        cout << "Прогноз нагрузки: " << forecastSign << forecastValue << "%" << endl;
        cout << "Пик нагрузки: через " << getPeakDays() << " дней" << endl;
        cout << "Критический ресурс: " << getCriticalResource() << endl;
        cout << "Рекомендации: " << getRecommendations() << endl;
    }

private:
    double calculateLoad() {
        double base = load * coef;
        double current = base * seasonal;
        double change = current * (1 + hosp * 2);
        return ((change - load) / load) * 100;
    }

    int getPeakDays() {
        if (coef > 1.5) return 7;
        if (coef > 1.2) return 10;
        if (coef > 0.9) return 14;
        return 21;
    }

    string getCriticalResource() {
        if (resources < 0.5) return "койки";
        if (resources < 0.7) return "персонал";
        if (resources < 0.9) return "оборудование";
        return "лекарства";
    }

    string getRecommendations() {
        double forecast = calculateLoad();
        if (forecast > 15) return "увеличить коечный фонд на 20%";
        if (forecast > 5) return "увеличить количество персонала";
        if (forecast < -5) return "перераспределить медсестер";
        return "поддерживать текущий уровень ресурсов";
    }
};

// Функция для замены запятых на точки
void replaceCommaWithDot(string& str) {
    replace(str.begin(), str.end(), ',', '.');
}

double getInputWithDefault(string msg, double min, double max, double defaultValue) {
    while (true) {
        // Для доли госпитализации показываем два знака после запятой
        if (min == 0.01) {
            cout << msg << " (от " << fixed << setprecision(2) << min 
                 << " до " << setprecision(1) << max 
                 << ", по умолчанию " << setprecision(1) << defaultValue << "): ";
        } else {
            cout << msg << " (от " << fixed << setprecision(1) << min 
                 << " до " << setprecision(1) << max 
                 << ", по умолчанию " << setprecision(1) << defaultValue << "): ";
        }
        
        string input;
        getline(cin, input);
        
        if (input.empty()) {
            cout << "Используется значение по умолчанию: " 
                 << fixed << setprecision(1) << defaultValue << endl;
            return defaultValue;
        }
        
        try {
            // Заменяем запятые на точки для корректного парсинга
            replaceCommaWithDot(input);
            
            // Используем stringstream для преобразования строки в double
            stringstream ss(input);
            double value;
            ss >> value;
            
            // Проверяем, что преобразование прошло успешно
            if (ss.fail() || !ss.eof()) {
                throw invalid_argument("Не число");
            }
            
            if (value >= min && value <= max) {
                return value;
            } else {
                if (min == 0.01) {
                    cout << "Ошибка! Число должно быть от " 
                         << fixed << setprecision(2) << min 
                         << " до " << setprecision(1) << max << "!" << endl;
                } else {
                    cout << "Ошибка! Число должно быть от " 
                         << fixed << setprecision(1) << min 
                         << " до " << setprecision(1) << max << "!" << endl;
                }
            }
        } catch (...) {
            cout << "Ошибка! Введите именно число (можно с запятой или точкой)!" << endl;
        }
    }
}

int getIntInputWithDefault(string msg, int min, int max, int defaultValue) {
    while (true) {
        cout << msg << " (от " << min << " до " << max 
             << ", по умолчанию " << defaultValue << "): ";
        
        string input;
        getline(cin, input);
        
        if (input.empty()) {
            cout << "Используется значение по умолчанию: " << defaultValue << endl;
            return defaultValue;
        }
        
        try {
            // Используем stringstream для преобразования строки в int
            stringstream ss(input);
            int value;
            ss >> value;
            
            // Проверяем, что преобразование прошло успешно
            if (ss.fail() || !ss.eof()) {
                throw invalid_argument("Не число");
            }
            
            if (value >= min && value <= max) {
                return value;
            } else {
                cout << "Ошибка! Число должно быть от " << min << " до " << max << "!" << endl;
            }
        } catch (...) {
            cout << "Ошибка! Введите именно целое число!" << endl;
        }
    }
}

void showMenu() {
    const int DEFAULT_LOAD = 100;
    const double DEFAULT_COEF = 1.2;
    const double DEFAULT_HOSP = 0.1;
    const double DEFAULT_RESOURCES = 0.8;
    const double DEFAULT_SEASONAL = 1.1;
    
    while (true) {
        cout << "\n=== ГЛАВНОЕ МЕНЮ ===" << endl;
        cout << "1. Выполнить расчет" << endl;
        cout << "2. Тестирование" << endl;
        cout << "3. Выход" << endl;
        
        cout << "Выберите пункт (1-3): ";
        
        string input;
        getline(cin, input);
        
        if (input.empty()) {
            cout << "Ошибка! Введите число от 1 до 3!" << endl;
            continue;
        }
        
        try {
            // Используем stringstream для преобразования строки в int
            stringstream ss(input);
            int choice;
            ss >> choice;
            
            // Проверяем, что преобразование прошло успешно
            if (ss.fail() || !ss.eof()) {
                throw invalid_argument("Не число");
            }
            
            if (choice == 1) {
                cout << "\n=== ВВОД ДАННЫХ ===" << endl;
                cout << "Для использования значений по умолчанию просто нажмите Enter" << endl;
                
                int load = getIntInputWithDefault("Текущая нагрузка (% от мощности)", 10, 200, DEFAULT_LOAD);
                double coef = getInputWithDefault("Коэффициент заболеваемости (отношение к среднему)", 0.1, 5.0, DEFAULT_COEF);
                double hosp = getInputWithDefault("Доля госпитализации", 0.01, 0.5, DEFAULT_HOSP);
                double res = getInputWithDefault("Доступность ресурсов", 0.1, 1.0, DEFAULT_RESOURCES);
                double season = getInputWithDefault("Сезонный фактор", 0.5, 3.0, DEFAULT_SEASONAL);
                
                MedicalSystem ms(load, coef, hosp, res, season);
                cout << "\n=== РЕЗУЛЬТАТЫ ===" << endl;
                ms.showResults();
            }
            else if (choice == 2) {
                // Тестирование из оригинального кода
                MedicalSystem test1(100, 1.2, 0.1, 0.8, 1.1);
                MedicalSystem test2(150, 1.8, 0.2, 0.6, 1.3);
                MedicalSystem test3(80, 0.8, 0.05, 0.9, 0.7);
                MedicalSystem test4(50, 2.8, 0.4, 0.3, 1.8);
                
                cout << "\n=== ТЕСТИРОВАНИЕ ===" << endl;
                
                cout << "\nТест 1 (нормальные условия):" << endl;
                cout << "Ввод: [100, 1.2, 0.1, 0.8, 1.1]" << endl;
                test1.showResults();
                
                cout << "\nТест 2 (высокая нагрузка):" << endl;
                cout << "Ввод: [150, 1.8, 0.2, 0.6, 1.3]" << endl;
                test2.showResults();
                
                cout << "\nТест 3 (низкая нагрузка):" << endl;
                cout << "Ввод: [80, 0.8, 0.05, 0.9, 0.7]" << endl;
                test3.showResults();
                
                cout << "\nТест 4 (критические условия):" << endl;
                cout << "Ввод: [50, 2.8, 0.4, 0.3, 1.8]" << endl;
                test4.showResults();
            }
            else if (choice == 3) {
                cout << "Выход из программы..." << endl;
                cout << "Нажмите Enter для закрытия...";
                cin.get();
                return;
            }
            else {
                cout << "Неверный выбор! Введите число от 1 до 3." << endl;
            }
        } catch (...) {
            cout << "Ошибка! Введите именно число от 1 до 3!" << endl;
        }
    }
}

int main() {
    showMenu();
    return 0;
}