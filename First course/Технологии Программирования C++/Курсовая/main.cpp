#include <iostream> // Для вывода на экран и работы с вводом
#include <vector> // Для использования контейнера vector
#include <string> // Для использования строки string
#include <fstream> // Для работы с файлами (чтение/запись)
#include <locale> // Для установки локали
#include <unordered_set> // Для использования контейнера unordered_set
#include <limits> // Для работы с пределами числовых типов, очистки ввода

using namespace std;

// Структура для хранения информации о пицце
struct Pizza {
    string name; // Название пиццы
    double price; // Цена пиццы
};

// Структура для хранения информации о напитках
struct Drink {
    string name; // Название напитка
    double price; // Цена напитка
};

// Структура для хранения информации о снэках
struct Snack {
    string name; // Название снэка
    double price; // Цена снэка
};

// Структура для хранения информации о филиале
struct Branch {
    string address; // Адрес филиала
};

// Структура для хранения информации о клиенте
struct Client {
    string name; // Имя клиента
    string favoriteItem; // Любимая позиция клиента
    double totalSpent; // Общая сумма заказов клиента
    string branch; // Филиал, который клиент выбирает чаще всего
};

// Класс для работы с заказами
class Order {
public:
    vector<Pizza> pizzas; // Вектор для хранения пицц в заказе
    vector<Drink> drinks; // Вектор для хранения напитков в заказе
    vector<Snack> snacks; // Вектор для хранения снэков в заказе
    double total; // Общая сумма заказа
    string branch; // Филиал, в который делается заказ
    string promoCode; // Промокод, если применен

    // Конструктор по умолчанию, инициализирующий общую сумму заказа нулем
    Order() : total(0) {}

    // Метод для добавления пиццы в заказ
    void addPizza(const Pizza& pizza) {
        pizzas.push_back(pizza);
        total += pizza.price;
    }

    // Метод для добавления напитка в заказ
    void addDrink(const Drink& drink) {
        drinks.push_back(drink);
        total += drink.price;
    }

    // Метод для добавления снэка в заказ
    void addSnack(const Snack& snack) {
        snacks.push_back(snack);
        total += snack.price;
    }

    // Метод для применения промокода к заказу
    void applyPromoCode(const string& code) {
        promoCode = code;
        total *= 0.8; // Применение скидки 20%
    }

    // Метод для печати чека заказа в файл
    void printReceipt() const {
        ofstream receipt("Receipt.txt"); // Открытие файла для записи
        receipt << "Чек заказа\n";
        receipt << "Филиал: " << branch << "\n";
        for (const auto& pizza : pizzas) {
            receipt << "Пицца: " << pizza.name << " - " << pizza.price << " руб.\n";
        }
        for (const auto& drink : drinks) {
            receipt << "Напиток: " << drink.name << " - " << drink.price << " руб.\n";
        }
        for (const auto& snack : snacks) {
            receipt << "Снэк: " << snack.name << " - " << snack.price << " руб.\n";
        }
        if (!promoCode.empty()) {
            receipt << "Промокод: " << promoCode << " - Скидка 20%\n";
        }
        receipt << "Итого: " << total << " руб.\n";
        receipt << "-------------------------\n";
        receipt.close(); // Закрытие файла
    }
};

// Класс для работы с пиццерией
class Pizzeria {
public:
    vector<Pizza> pizzas; // Вектор для хранения ассортимента пицц
    vector<Drink> drinks; // Вектор для хранения ассортимента напитков
    vector<Snack> snacks; // Вектор для хранения ассортимента снэков
    vector<Branch> branches; // Вектор для хранения адресов филиалов
    vector<Client> topClients; // Вектор для хранения информации о топ клиентах
    vector<string> discounts; // Вектор для хранения информации о скидках
    unordered_set<string> promoCodes; // Множество для хранения промокодов

    // Конструктор класса, инициализирующий данные
    Pizzeria() {
        // Инициализации ассортиментов пицц, напитков и снеков
        pizzas = { {"Маргарита", 500.0}, {"Пепперони", 600.0}, {"Гавайская", 700.0}, {"Четыре сыра", 800.0}, {"Мясная", 900.0} };
        drinks = { {"Кока-Кола", 100.0}, {"Пепси", 90.0}, {"Вода", 50.0}, {"Сок апельсиновый", 120.0}, {"Сок яблочный", 110.0} };
        snacks = { {"Чесночный хлеб", 150.0}, {"Крылышки", 200.0}, {"Моцарелла палочки", 180.0}, {"Картофель фри", 170.0}, {"Луковые кольца", 160.0}, {"Мороженое", 100.0} };

        // Инициализация адресов филиалов
        branches = { {"Невский проспект, дом 28"}, {"Набережной Чёрной речки, дом 51"}, {"Проспект непокорённых, дом 2"}, {"Лиговский проспект, дом 50"}, {"Наличная улица, дом 44"} };

        // Инициализация топ клиентов
        topClients = {
            {"Дмитриев Лев", "Пепперони", 4500.0, "Невский проспект, дом 28"},
            {"Гаврилова Алина", "Мясная", 5500.0, "Набережной Чёрной речки, дом 51"},
            {"Поляков Марат", "Четыре сыра", 6200.0, "Проспект непокорённых, дом 2"},
            {"Герасимова Василиса", "Гавайская", 7000.0, "Лиговский проспект, дом 50"},
            {"Михайлова Алиса", "Маргарита", 4800.0, "Наличная улица, дом 44"},
            {"Прохоров Даниэль  ", "Пепперони", 5200.0, "Невский проспект, дом 28"},
            {"Беляев Владислав  ", "Мясная", 5300.0, "Набережной Чёрной речки, дом 51"},
            {"Чернышев Матвей", "Четыре сыра", 6100.0, "Проспект непокорённых, дом 2"},

        };

        // Инициализация скидок
        discounts = { "При покупке пиццы, крылышек и напитка получите бесплатное мороженое!", "Бесплатный снэк при заказе от 1000 руб.", "Приведи друга и получи скидку 20%!" };

        // Загрузка промокодов из файла
        loadPromoCodes();
    }

    // Метод для отображения меню
    void showMenu() const {
        cout << "----- Меню -----\n";
        cout << "Пиццы:\n";
        for (const auto& pizza : pizzas) {
            cout << pizza.name << " - " << pizza.price << " руб.\n";
        }
        cout << "----------------\n";
        cout << "Напитки:\n";
        for (const auto& drink : drinks) {
            cout << drink.name << " - " << drink.price << " руб.\n";
        }
        cout << "Снэки:\n";
        cout << "----------------\n";
        for (const auto& snack : snacks) {
            cout << snack.name << " - " << snack.price << " руб.\n";
        }
        cout << "----------------\n";
    }

    // Метод для отображения скидок
    void showDiscounts() const {
        cout << "----- Скидки -----\n";
        for (const auto& discount : discounts) {
            cout << discount << endl;
        }
        cout << "---------------------\n";
    }

    // Метод для отображения филиалов
    void showBranches() const {
        cout << "----- Филиалы -----\n";
        for (const auto& branch : branches) {
            cout << branch.address << endl;
        }
        cout << "---------------------\n";
    }

    // Метод для отображения топ клиентов
    void showTopClients() const {
        cout << "----- Топ Клиенты -----\n";
        for (const auto& client : topClients) {
            cout << client.name << " - Любимая позиция: " << client.favoriteItem
                 << " - Общая сумма заказов: " << client.totalSpent << " руб."
                 << " - Филиал: " << client.branch << "\n";
        }
        cout << "-----------------------\n";
    }

    // Метод для создания заказа
    void createOrder() {
        Order order; // Создание нового заказа
        chooseBranch(order); // Выбор филиала для заказа
        char choice;
        do {
            cout << "Выберите категорию для добавления в заказ:\n";
            cout << "1. Пиццы\n2. Напитки\n3. Снэки\n";
            int category;
            cin >> category;
            // Проверка корректности ввода
            while(cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Неверный выбор! Пожалуйста, выберите снова:\n";
                cin >> category;
            }
            switch (category) {
                case 1:
                    addPizzaToOrder(order); // Добавление пиццы в заказ
                    break;
                case 2:
                    addDrinkToOrder(order); // Добавление напитка в заказ
                    break;
                case 3:
                    addSnackToOrder(order); // Добавление снэка в заказ
                    break;
                default:
                    cout << "Неверный выбор!\n";
            }
            cout << "Хотите добавить еще что-нибудь? (y/n): ";
            cin >> choice;
        } while (choice == 'y'); // Повторение цикла, пока пользователь не выберет 'n'

        applyPromoCode(order); // Применение промокода

        order.printReceipt(); // Печать чека заказа
        cout << "Заказ оформлен. Проверьте 'Receipt.txt' для деталей.\n";
    }

private:
    // Метод для загрузки промокодов из файла
    void loadPromoCodes() {
        ifstream promoFile("Promocodes.txt"); // Открытие файла для чтения
        if (promoFile.is_open()) {
            string code;
            while (getline(promoFile, code)) {
                promoCodes.insert(code); // Добавление промокода в множество
            }
            promoFile.close(); // Закрытие файла
        } else {
            cout << "Не удалось открыть файл 'Promocodes.txt'.\n";
        }
    }

    // Метод для выбора филиала для заказа
    void chooseBranch(Order& order) const {
        cout << "Выберите филиал:\n";
        for (size_t i = 0; i < branches.size(); ++i) {
            cout << i + 1 << ". " << branches[i].address << "\n";
        }
        int choice;
        cin >> choice;
        // Проверка корректности ввода
        while(cin.fail() || choice <= 0 || choice > branches.size()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Неверный выбор! Пожалуйста, выберите снова:\n";
            cin >> choice;
        }
        order.branch = branches[choice - 1].address; // Установка выбранного филиала в заказе
    }

    // Метод для добавления пиццы в заказ
    void addPizzaToOrder(Order& order) const {
        cout << "Выберите пиццу:\n";
        for (size_t i = 0; i < pizzas.size(); ++i) {
            cout << i + 1 << ". " << pizzas[i].name << " - " << pizzas[i].price << " руб.\n";
        }
        int choice;
        cin >> choice;
        // Проверка корректности ввода
        while(cin.fail() || choice <= 0 || choice > pizzas.size()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Неверный выбор! Пожалуйста, выберите снова:\n";
            cin >> choice;
        }
        order.addPizza(pizzas[choice - 1]); // Добавление выбранной пиццы в заказ
    }

    // Метод для добавления напитка в заказ
    void addDrinkToOrder(Order& order) const {
        cout << "Выберите напиток:\n";
        for (size_t i = 0; i < drinks.size(); ++i) {
            cout << i + 1 << ". " << drinks[i].name << " - " << drinks[i].price << " руб.\n";
        }
        int choice;
        cin >> choice;
        // Проверка корректности ввода
        while(cin.fail() || choice <= 0 || choice > drinks.size()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Неверный выбор! Пожалуйста, выберите снова:\n";
            cin >> choice;
        }
        order.addDrink(drinks[choice - 1]); // Добавление выбранного напитка в заказ
    }

    // Метод для добавления снэка в заказ
    void addSnackToOrder(Order& order) const {
        cout << "Выберите снэк:\n";
        for (size_t i = 0; i < snacks.size(); ++i) {
            cout << i + 1 << ". " << snacks[i].name << " - " << snacks[i].price << " руб.\n";
        }
        int choice;
        cin >> choice;
        // Проверка корректности ввода
        while(cin.fail() || choice <= 0 || choice > snacks.size()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Неверный выбор! Пожалуйста, выберите снова:\n";
            cin >> choice;
        }
        order.addSnack(snacks[choice - 1]); // Добавление выбранного снэка в заказ
    }

    // Метод для применения промокода к заказу
    void applyPromoCode(Order& order) {
        cout << "Хотите ввести промокод? (y/n): ";
        char choice;
        cin >> choice;
        if (choice == 'y') {
            string promoCode;
            while (true) {
                cout << "Введите промокод (или 0 для отмены): ";
                cin >> promoCode;
                if (promoCode == "0") {
                    cout << "Промокод не применён.\n";
                    break;
                }
                if (promoCodes.find(promoCode) != promoCodes.end()) {
                    order.applyPromoCode(promoCode); // Применение промокода, если он найден
                    cout << "Промокод применён, скидка 20%.\n";
                    break;
                } else {
                    cout << "Неверный промокод! Попробуйте снова.\n";
                }
            }
        }
    }
};

// Основная функция
int main() {
    setlocale(LC_ALL, "Russian"); // Установка локали для поддержки русского языка
    Pizzeria pizzeria; // Создание объекта класса Pizzeria
    int choice;

    // Основной цикл меню
    do {
        cout << "----- Меню Пиццерии -----\n";
        cout << "1. Показать Меню\n";
        cout << "2. Показать Скидки\n";
        cout << "3. Сделать Заказ\n";
        cout << "4. Показать Филиалы\n";
        cout << "5. Показать Топ Клиентов\n";
        cout << "6. Выход\n";
        cout << "-------------------------\n";
        cout << "Введите ваш выбор: ";
        cin >> choice;

        // Проверка корректности ввода
        while(cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Неверный выбор! Попробуйте снова: ";
            cin >> choice;
        }

        // Обработка выбора пользователя
        switch (choice) {
            case 1:
                pizzeria.showMenu(); // Отображение меню
                break;
            case 2:
                pizzeria.showDiscounts(); // Отображение скидок
                break;
            case 3:
                pizzeria.createOrder(); // Создание заказа
                break;
            case 4:
                pizzeria.showBranches(); // Отображение филиалов
                break;
            case 5:
                pizzeria.showTopClients(); // Отображение топ клиентов
                break;
            case 6:
                cout << "До свидания!\n"; // Выход из программы
                break;
            default:
                cout << "Неверный выбор! Попробуйте снова.\n";
        }
    } while (choice != 6); // Повторение цикла, пока пользователь не выберет выход

    return 0;
}
