#include <iostream> // ��� ������ �� ����� � ������ � ������
#include <vector> // ��� ������������� ���������� vector
#include <string> // ��� ������������� ������ string
#include <fstream> // ��� ������ � ������� (������/������)
#include <locale> // ��� ��������� ������
#include <unordered_set> // ��� ������������� ���������� unordered_set
#include <limits> // ��� ������ � ��������� �������� �����, ������� �����

using namespace std;

// ��������� ��� �������� ���������� � �����
struct Pizza {
    string name; // �������� �����
    double price; // ���� �����
};

// ��������� ��� �������� ���������� � ��������
struct Drink {
    string name; // �������� �������
    double price; // ���� �������
};

// ��������� ��� �������� ���������� � ������
struct Snack {
    string name; // �������� �����
    double price; // ���� �����
};

// ��������� ��� �������� ���������� � �������
struct Branch {
    string address; // ����� �������
};

// ��������� ��� �������� ���������� � �������
struct Client {
    string name; // ��� �������
    string favoriteItem; // ������� ������� �������
    double totalSpent; // ����� ����� ������� �������
    string branch; // ������, ������� ������ �������� ���� �����
};

// ����� ��� ������ � ��������
class Order {
public:
    vector<Pizza> pizzas; // ������ ��� �������� ���� � ������
    vector<Drink> drinks; // ������ ��� �������� �������� � ������
    vector<Snack> snacks; // ������ ��� �������� ������ � ������
    double total; // ����� ����� ������
    string branch; // ������, � ������� �������� �����
    string promoCode; // ��������, ���� ��������

    // ����������� �� ���������, ���������������� ����� ����� ������ �����
    Order() : total(0) {}

    // ����� ��� ���������� ����� � �����
    void addPizza(const Pizza& pizza) {
        pizzas.push_back(pizza);
        total += pizza.price;
    }

    // ����� ��� ���������� ������� � �����
    void addDrink(const Drink& drink) {
        drinks.push_back(drink);
        total += drink.price;
    }

    // ����� ��� ���������� ����� � �����
    void addSnack(const Snack& snack) {
        snacks.push_back(snack);
        total += snack.price;
    }

    // ����� ��� ���������� ��������� � ������
    void applyPromoCode(const string& code) {
        promoCode = code;
        total *= 0.8; // ���������� ������ 20%
    }

    // ����� ��� ������ ���� ������ � ����
    void printReceipt() const {
        ofstream receipt("Receipt.txt"); // �������� ����� ��� ������
        receipt << "��� ������\n";
        receipt << "������: " << branch << "\n";
        for (const auto& pizza : pizzas) {
            receipt << "�����: " << pizza.name << " - " << pizza.price << " ���.\n";
        }
        for (const auto& drink : drinks) {
            receipt << "�������: " << drink.name << " - " << drink.price << " ���.\n";
        }
        for (const auto& snack : snacks) {
            receipt << "����: " << snack.name << " - " << snack.price << " ���.\n";
        }
        if (!promoCode.empty()) {
            receipt << "��������: " << promoCode << " - ������ 20%\n";
        }
        receipt << "�����: " << total << " ���.\n";
        receipt << "-------------------------\n";
        receipt.close(); // �������� �����
    }
};

// ����� ��� ������ � ���������
class Pizzeria {
public:
    vector<Pizza> pizzas; // ������ ��� �������� ������������ ����
    vector<Drink> drinks; // ������ ��� �������� ������������ ��������
    vector<Snack> snacks; // ������ ��� �������� ������������ ������
    vector<Branch> branches; // ������ ��� �������� ������� ��������
    vector<Client> topClients; // ������ ��� �������� ���������� � ��� ��������
    vector<string> discounts; // ������ ��� �������� ���������� � �������
    unordered_set<string> promoCodes; // ��������� ��� �������� ����������

    // ����������� ������, ���������������� ������
    Pizzeria() {
        // ������������� ������������� ����, �������� � ������
        pizzas = { {"���������", 500.0}, {"���������", 600.0}, {"���������", 700.0}, {"������ ����", 800.0}, {"������", 900.0} };
        drinks = { {"����-����", 100.0}, {"�����", 90.0}, {"����", 50.0}, {"��� ������������", 120.0}, {"��� ��������", 110.0} };
        snacks = { {"��������� ����", 150.0}, {"��������", 200.0}, {"��������� �������", 180.0}, {"��������� ���", 170.0}, {"������� ������", 160.0}, {"���������", 100.0} };

        // ������������� ������� ��������
        branches = { {"������� ��������, ��� 28"}, {"���������� ׸���� �����, ��� 51"}, {"�������� �����������, ��� 2"}, {"��������� ��������, ��� 50"}, {"�������� �����, ��� 44"} };

        // ������������� ��� ��������
        topClients = {
            {"�������� ���", "���������", 4500.0, "������� ��������, ��� 28"},
            {"��������� �����", "������", 5500.0, "���������� ׸���� �����, ��� 51"},
            {"������� �����", "������ ����", 6200.0, "�������� �����������, ��� 2"},
            {"���������� ��������", "���������", 7000.0, "��������� ��������, ��� 50"},
            {"��������� �����", "���������", 4800.0, "�������� �����, ��� 44"},
            {"�������� �������  ", "���������", 5200.0, "������� ��������, ��� 28"},
            {"������ ���������  ", "������", 5300.0, "���������� ׸���� �����, ��� 51"},
            {"�������� ������", "������ ����", 6100.0, "�������� �����������, ��� 2"},

        };

        // ������������� ������
        discounts = { "��� ������� �����, �������� � ������� �������� ���������� ���������!", "���������� ���� ��� ������ �� 1000 ���.", "������� ����� � ������ ������ 20%!" };

        // �������� ���������� �� �����
        loadPromoCodes();
    }

    // ����� ��� ����������� ����
    void showMenu() const {
        cout << "----- ���� -----\n";
        cout << "�����:\n";
        for (const auto& pizza : pizzas) {
            cout << pizza.name << " - " << pizza.price << " ���.\n";
        }
        cout << "----------------\n";
        cout << "�������:\n";
        for (const auto& drink : drinks) {
            cout << drink.name << " - " << drink.price << " ���.\n";
        }
        cout << "�����:\n";
        cout << "----------------\n";
        for (const auto& snack : snacks) {
            cout << snack.name << " - " << snack.price << " ���.\n";
        }
        cout << "----------------\n";
    }

    // ����� ��� ����������� ������
    void showDiscounts() const {
        cout << "----- ������ -----\n";
        for (const auto& discount : discounts) {
            cout << discount << endl;
        }
        cout << "---------------------\n";
    }

    // ����� ��� ����������� ��������
    void showBranches() const {
        cout << "----- ������� -----\n";
        for (const auto& branch : branches) {
            cout << branch.address << endl;
        }
        cout << "---------------------\n";
    }

    // ����� ��� ����������� ��� ��������
    void showTopClients() const {
        cout << "----- ��� ������� -----\n";
        for (const auto& client : topClients) {
            cout << client.name << " - ������� �������: " << client.favoriteItem
                 << " - ����� ����� �������: " << client.totalSpent << " ���."
                 << " - ������: " << client.branch << "\n";
        }
        cout << "-----------------------\n";
    }

    // ����� ��� �������� ������
    void createOrder() {
        Order order; // �������� ������ ������
        chooseBranch(order); // ����� ������� ��� ������
        char choice;
        do {
            cout << "�������� ��������� ��� ���������� � �����:\n";
            cout << "1. �����\n2. �������\n3. �����\n";
            int category;
            cin >> category;
            // �������� ������������ �����
            while(cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "�������� �����! ����������, �������� �����:\n";
                cin >> category;
            }
            switch (category) {
                case 1:
                    addPizzaToOrder(order); // ���������� ����� � �����
                    break;
                case 2:
                    addDrinkToOrder(order); // ���������� ������� � �����
                    break;
                case 3:
                    addSnackToOrder(order); // ���������� ����� � �����
                    break;
                default:
                    cout << "�������� �����!\n";
            }
            cout << "������ �������� ��� ���-������? (y/n): ";
            cin >> choice;
        } while (choice == 'y'); // ���������� �����, ���� ������������ �� ������� 'n'

        applyPromoCode(order); // ���������� ���������

        order.printReceipt(); // ������ ���� ������
        cout << "����� ��������. ��������� 'Receipt.txt' ��� �������.\n";
    }

private:
    // ����� ��� �������� ���������� �� �����
    void loadPromoCodes() {
        ifstream promoFile("Promocodes.txt"); // �������� ����� ��� ������
        if (promoFile.is_open()) {
            string code;
            while (getline(promoFile, code)) {
                promoCodes.insert(code); // ���������� ��������� � ���������
            }
            promoFile.close(); // �������� �����
        } else {
            cout << "�� ������� ������� ���� 'Promocodes.txt'.\n";
        }
    }

    // ����� ��� ������ ������� ��� ������
    void chooseBranch(Order& order) const {
        cout << "�������� ������:\n";
        for (size_t i = 0; i < branches.size(); ++i) {
            cout << i + 1 << ". " << branches[i].address << "\n";
        }
        int choice;
        cin >> choice;
        // �������� ������������ �����
        while(cin.fail() || choice <= 0 || choice > branches.size()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "�������� �����! ����������, �������� �����:\n";
            cin >> choice;
        }
        order.branch = branches[choice - 1].address; // ��������� ���������� ������� � ������
    }

    // ����� ��� ���������� ����� � �����
    void addPizzaToOrder(Order& order) const {
        cout << "�������� �����:\n";
        for (size_t i = 0; i < pizzas.size(); ++i) {
            cout << i + 1 << ". " << pizzas[i].name << " - " << pizzas[i].price << " ���.\n";
        }
        int choice;
        cin >> choice;
        // �������� ������������ �����
        while(cin.fail() || choice <= 0 || choice > pizzas.size()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "�������� �����! ����������, �������� �����:\n";
            cin >> choice;
        }
        order.addPizza(pizzas[choice - 1]); // ���������� ��������� ����� � �����
    }

    // ����� ��� ���������� ������� � �����
    void addDrinkToOrder(Order& order) const {
        cout << "�������� �������:\n";
        for (size_t i = 0; i < drinks.size(); ++i) {
            cout << i + 1 << ". " << drinks[i].name << " - " << drinks[i].price << " ���.\n";
        }
        int choice;
        cin >> choice;
        // �������� ������������ �����
        while(cin.fail() || choice <= 0 || choice > drinks.size()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "�������� �����! ����������, �������� �����:\n";
            cin >> choice;
        }
        order.addDrink(drinks[choice - 1]); // ���������� ���������� ������� � �����
    }

    // ����� ��� ���������� ����� � �����
    void addSnackToOrder(Order& order) const {
        cout << "�������� ����:\n";
        for (size_t i = 0; i < snacks.size(); ++i) {
            cout << i + 1 << ". " << snacks[i].name << " - " << snacks[i].price << " ���.\n";
        }
        int choice;
        cin >> choice;
        // �������� ������������ �����
        while(cin.fail() || choice <= 0 || choice > snacks.size()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "�������� �����! ����������, �������� �����:\n";
            cin >> choice;
        }
        order.addSnack(snacks[choice - 1]); // ���������� ���������� ����� � �����
    }

    // ����� ��� ���������� ��������� � ������
    void applyPromoCode(Order& order) {
        cout << "������ ������ ��������? (y/n): ";
        char choice;
        cin >> choice;
        if (choice == 'y') {
            string promoCode;
            while (true) {
                cout << "������� �������� (��� 0 ��� ������): ";
                cin >> promoCode;
                if (promoCode == "0") {
                    cout << "�������� �� �������.\n";
                    break;
                }
                if (promoCodes.find(promoCode) != promoCodes.end()) {
                    order.applyPromoCode(promoCode); // ���������� ���������, ���� �� ������
                    cout << "�������� �������, ������ 20%.\n";
                    break;
                } else {
                    cout << "�������� ��������! ���������� �����.\n";
                }
            }
        }
    }
};

// �������� �������
int main() {
    setlocale(LC_ALL, "Russian"); // ��������� ������ ��� ��������� �������� �����
    Pizzeria pizzeria; // �������� ������� ������ Pizzeria
    int choice;

    // �������� ���� ����
    do {
        cout << "----- ���� �������� -----\n";
        cout << "1. �������� ����\n";
        cout << "2. �������� ������\n";
        cout << "3. ������� �����\n";
        cout << "4. �������� �������\n";
        cout << "5. �������� ��� ��������\n";
        cout << "6. �����\n";
        cout << "-------------------------\n";
        cout << "������� ��� �����: ";
        cin >> choice;

        // �������� ������������ �����
        while(cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "�������� �����! ���������� �����: ";
            cin >> choice;
        }

        // ��������� ������ ������������
        switch (choice) {
            case 1:
                pizzeria.showMenu(); // ����������� ����
                break;
            case 2:
                pizzeria.showDiscounts(); // ����������� ������
                break;
            case 3:
                pizzeria.createOrder(); // �������� ������
                break;
            case 4:
                pizzeria.showBranches(); // ����������� ��������
                break;
            case 5:
                pizzeria.showTopClients(); // ����������� ��� ��������
                break;
            case 6:
                cout << "�� ��������!\n"; // ����� �� ���������
                break;
            default:
                cout << "�������� �����! ���������� �����.\n";
        }
    } while (choice != 6); // ���������� �����, ���� ������������ �� ������� �����

    return 0;
}
