#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Company {
    string name;
    string owner;
    string phone;
    string address;
    string activity;
};

class Directory {
private:
    vector<Company> companies;
    string filename;

    void loadFromFile() {
        ifstream file(filename);
        if (file.is_open()) {
            Company company;
            while (getline(file, company.name) &&
                   getline(file, company.owner) &&
                   getline(file, company.phone) &&
                   getline(file, company.address) &&
                   getline(file, company.activity)) {
                companies.push_back(company);
            }
            file.close();
        }
    }

    void saveToFile() {
        ofstream file(filename);
        if (file.is_open()) {
            for (const auto &company : companies) {
                file << company.name << endl
                     << company.owner << endl
                     << company.phone << endl
                     << company.address << endl
                     << company.activity << endl;
            }
            file.close();
        }
    }

public:
    Directory(const string &file) : filename(file) {
        loadFromFile();
    }

    ~Directory() {
        saveToFile();
    }

    void addCompany() {
        Company company;
        cout << "Введіть назву фірми: ";
        getline(cin, company.name);
        cout << "Введіть власника: ";
        getline(cin, company.owner);
        cout << "Введіть телефон: ";
        getline(cin, company.phone);
        cout << "Введіть адресу: ";
        getline(cin, company.address);
        cout << "Введіть рід діяльності: ";
        getline(cin, company.activity);
        companies.push_back(company);
        saveToFile();
    }

    void searchByField(const string &field, const string &value) {
        bool found = false;
        for (const auto &company : companies) {
            if ((field == "name" && company.name == value) ||
                (field == "owner" && company.owner == value) ||
                (field == "phone" && company.phone == value) ||
                (field == "activity" && company.activity == value)) {
                cout << "Назва: " << company.name << "\n"
                     << "Власник: " << company.owner << "\n"
                     << "Телефон: " << company.phone << "\n"
                     << "Адреса: " << company.address << "\n"
                     << "Рід діяльності: " << company.activity << "\n\n";
                found = true;
            }
        }
        if (!found) {
            cout << "Запис не знайдено." << endl;
        }
    }

    void displayAll() {
        for (const auto &company : companies) {
            cout << "Назва: " << company.name << "\n"
                 << "Власник: " << company.owner << "\n"
                 << "Телефон: " << company.phone << "\n"
                 << "Адреса: " << company.address << "\n"
                 << "Рід діяльності: " << company.activity << "\n\n";
        }
    }
};

int main() {
    Directory directory("directory.txt");
    int choice;

    do {
        cout << "Меню:\n"
             << "1. Додати запис\n"
             << "2. Пошук за назвою\n"
             << "3. Пошук за власником\n"
             << "4. Пошук за телефоном\n"
             << "5. Пошук за родом діяльності\n"
             << "6. Показати всі записи\n"
             << "0. Вихід\n"
             << "Ваш вибір: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                directory.addCompany();
                break;
            case 2: {
                string name;
                cout << "Введіть назву: ";
                getline(cin, name);
                directory.searchByField("name", name);
                break;
            }
            case 3: {
                string owner;
                cout << "Введіть власника: ";
                getline(cin, owner);
                directory.searchByField("owner", owner);
                break;
            }
            case 4: {
                string phone;
                cout << "Введіть телефон: ";
                getline(cin, phone);
                directory.searchByField("phone", phone);
                break;
            }
            case 5: {
                string activity;
                cout << "Введіть рід діяльності: ";
                getline(cin, activity);
                directory.searchByField("activity", activity);
                break;
            }
            case 6:
                directory.displayAll();
                break;
            case 0:
                cout << "До побачення!" << endl;
                break;
            default:
                cout << "Невірний вибір. Спробуйте ще раз." << endl;
        }
    } while (choice != 0);

    return 0;
}
