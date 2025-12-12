#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class MedicalSystem {
private:
    int load;
    double coef, hosp, resources, seasonal;

public:
    MedicalSystem(int l, double c, double h, double r, double s) 
        : load(l), coef(c), hosp(h), resources(r), seasonal(s) {}

    void showResults() {
        cout << fixed << setprecision(2);
        cout << "Прогноз нагрузки: " << calculateLoad() << "%" << endl;
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

double getInput(string msg, double min, double max) {
    double value;
    while (true) {
        cout << msg;
        if (cin >> value) {
            if (value >= min && value <= max) {
                return value;
            }
        } else {
            cin.clear();
            cin.ignore(1000, '\n');
        }
        cout << "Ошибка! Введите число от " << min << " до " << max << endl;
    }
}

void showMenu() {
    while (true) {
        cout << "\n=== ГЛАВНОЕ МЕНЮ ===" << endl;
        cout << "1. Выполнить расчет" << endl;
        cout << "2. Тестирование" << endl;
        cout << "3. Выход" << endl;
        
        int choice;
        cout << "Выберите пункт (1-3): ";
        cin >> choice;
        
        if (choice == 1) {
            // Ввод и проверка нагрузки
            int load;
            while (true) {
                cout << "Текущая нагрузка (% от 1 до 200): ";
                cin >> load;
                if (load >= 1 && load <= 200) {
                    break;
                }
                cout << "Введите число в предоставленном диапазоне!" << endl;
                cin.clear();
                cin.ignore(1000, '\n');
            }
            
            // Ввод и проверка коэффициента
            double coef;
            while (true) {
                cout << "Коэффициент заболеваемости (от 0.1 до 3.0): ";
                cin >> coef;
                if (coef >= 0.1 && coef <= 3.0) {
                    break;
                }
                cout << "Введите число в предоставленном диапазоне!" << endl;
                cin.clear();
                cin.ignore(1000, '\n');
            }
            
            // Ввод и проверка доли госпитализации
            double hosp;
            while (true) {
                cout << "Доля госпитализации (от 0.01 до 0.5): ";
                cin >> hosp;
                if (hosp >= 0.01 && hosp <= 0.5) {
                    break;
                }
                cout << "Введите число в предоставленном диапазоне!" << endl;
                cin.clear();
                cin.ignore(1000, '\n');
            }
            
            // Ввод и проверка доступности ресурсов
            double res;
            while (true) {
                cout << "Доступность ресурсов (от 0.1 до 1.0): ";
                cin >> res;
                if (res >= 0.1 && res <= 1.0) {
                    break;
                }
                cout << "Введите число в предоставленном диапазоне!" <<endl;
                cin.clear();
                cin.ignore(1000, '\n');
            }
            
            // Ввод и проверка сезонного фактора
            double season;
            while (true) {
                cout << "Сезонный фактор (от 0.5 до 2.0): ";
                cin >> season;
                if (season >= 0.5 && season <= 2.0) {
                    break;
                }
                cout << "Введите число в предоставленном диапазоне!" << endl;
                cin.clear();
                cin.ignore(1000, '\n');
            }
            
            MedicalSystem ms(load, coef, hosp, res, season);
            cout << "\n=== РЕЗУЛЬТАТЫ ===" << endl;
            ms.showResults();
        }
        else if (choice == 2) {
            // Тестирование с различными данными
            MedicalSystem test1(100, 1.2, 0.1, 0.8, 1.1);
            MedicalSystem test2(150, 1.8, 0.2, 0.6, 1.3);
            MedicalSystem test3(80, 0.8, 0.05, 0.9, 0.7);
            MedicalSystem test4(50, 2.8, 0.4, 0.3, 1.8);
            
            cout << "Тест 1 (нормальные условия):" << endl;
            test1.showResults();
            cout << "\nТест 2 (высокая нагрузка):" << endl;
            test2.showResults();
            cout << "\nТест 3 (низкая нагрузка):" << endl;
            test3.showResults();
            cout << "\nТест 4 (критические условия):" << endl;
            test4.showResults();
        }
        else if (choice == 3) {
            cout << "Выход из программы..." << endl;
            cout << "Нажмите Enter для закрытия...";
            cin.ignore();
            cin.get();
            return;
        }
        else {
            cout << "Неверный выбор! Введите число от 1 до 3." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }
}

int main() {
    showMenu();
    return 0;
}