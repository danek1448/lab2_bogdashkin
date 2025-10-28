﻿#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <string>
#include "truba.h"
#include <limits>
#include "cs.h"
#include "instruments.h"
#include "logirovanie.h"
#include <windows.h>

using namespace std;

// глобальные контейнеры для хранения объектов
unordered_map<int, Truba> truby;
unordered_map<int, Kompressornaya_stantsiya> kompressornye_stantsii;
int sleduyushiy_id_truba = 1;
int sleduyushiy_id_ks = 1;

// прототипы функций
void Pokazat_menu();
void Dobavit_trubu();
void Dobavit_KS();
void Pokazat_vse_obekty();
void Redaktirovat_trubu();
void Redaktirovat_KS();
void Sohranit_dannye();
void Zagruzit_dannye();
void Poisk_trub();
void Poisk_KS();
void Paketnoe_redaktirovanie_trub();

void Pokazat_menu() {
    cout << "\nМеню" << endl;
    cout << "1. Добавить трубу" << endl;
    cout << "2. Добавить компрессорную станцию" << endl;
    cout << "3. Просмотр всех объектов" << endl;
    cout << "4. Редактировать трубу" << endl;
    cout << "5. Редактировать компрессорную станцию" << endl;
    cout << "6. Поиск труб" << endl;
    cout << "7. Поиск компрессорных станций" << endl;
    cout << "8. Пакетное редактирование труб" << endl;
    cout << "9. Сохранить данные" << endl;
    cout << "10. Загрузить данные" << endl;
    cout << "0. Выход" << endl;
    cout << "Выберите действие: ";
}

void Dobavit_trubu() {
    Truba novaya_truba;

    cin.ignore((numeric_limits<streamsize>::max)(), '\n');
    novaya_truba.read();
    truby[sleduyushiy_id_truba++] = novaya_truba;
    logirovanie::log("Добавлена труба с ID: " + to_string(sleduyushiy_id_truba - 1));
    cout << "Труба успешно добавлена с ID: " << sleduyushiy_id_truba - 1 << endl;
}

void Dobavit_KS() {
    Kompressornaya_stantsiya novaya_ks;

    cin.ignore((numeric_limits<streamsize>::max)(), '\n');
    novaya_ks.read();
    kompressornye_stantsii[sleduyushiy_id_ks++] = novaya_ks;
    logirovanie::log("Добавлена КС с ID: " + to_string(sleduyushiy_id_ks - 1));
    cout << "Компрессорная станция успешно добавлена с ID: " << sleduyushiy_id_ks - 1 << endl;
}

void Pokazat_vse_obekty() {
    cout << "\nТРУБЫ" << endl;
    if (truby.empty()) {
        cout << "Трубы отсутствуют" << endl;
    }
    else {
        for (const auto& pair : truby) {
            cout << "ID: " << pair.first << endl;
            pair.second.print();
        }
    }

    cout << "\nКОМПРЕССОРНЫЕ СТАНЦИИ" << endl;
    if (kompressornye_stantsii.empty()) {
        cout << "Компрессорные станции отсутствуют" << endl;
    }
    else {
        for (const auto& pair : kompressornye_stantsii) {
            cout << "ID: " << pair.first << endl;
            pair.second.print();
        }
    }
    logirovanie::log("Просмотр всех объектов");
}

void Redaktirovat_trubu() {
    if (truby.empty()) {
        cout << "Нет доступных труб для редактирования" << endl;
        return;
    }

    cout << "Доступные трубы (ID): ";
    for (const auto& pair : truby) {
        cout << pair.first << " ";
    }
    cout << "\nВведите ID трубы для редактирования: ";

    int id;
    cin >> id;
    if (truby.find(id) == truby.end()) {
        cout << "Труба с указанным ID не найдена!" << endl;
        return;
    }

    cout << "Текущий статус: " << (truby[id].isRemont() ? "В ремонте" : "Работает") << endl;
    cout << "Введите новый статус (1 - в ремонте, 0 - работает): ";
    int status;
    cin >> status;
    bool noviy_status = (status == 1);

    truby[id].setRemont(noviy_status);
    logirovanie::log("Изменен статус трубы ID: " + to_string(id) + " на: " + (noviy_status ? "в ремонте" : "работает"));
    cout << "Статус трубы успешно изменен!" << endl;
}

void Redaktirovat_KS() {
    if (kompressornye_stantsii.empty()) {
        cout << "Нет доступных компрессорных станций для редактирования" << endl;
        return;
    }

    cout << "Доступные КС (ID): ";
    for (const auto& pair : kompressornye_stantsii) {
        cout << pair.first << " ";
    }
    cout << "\nВведите ID КС для редактирования: ";

    int id;
    cin >> id;
    if (kompressornye_stantsii.find(id) == kompressornye_stantsii.end()) {
        cout << "КС с указанным ID не найдена!" << endl;
        return;
    }

    cout << "1. Запустить цех" << endl;
    cout << "2. Остановить цех" << endl;
    cout << "Выберите действие: ";

    int vibor;
    cin >> vibor;
    if (vibor == 1) {
        kompressornye_stantsii[id].zapustit_ceh();
        logirovanie::log("Запущен цех на КС ID: " + to_string(id));
    }
    else if (vibor == 2) {
        kompressornye_stantsii[id].ostanovit_ceh();
        logirovanie::log("Остановлен цех на КС ID: " + to_string(id));
    }
    else {
        cout << "Неверный выбор!" << endl;
    }
}

void Poisk_trub() {
    if (truby.empty()) {
        cout << "Нет доступных труб для поиска" << endl;
        return;
    }

    cout << "Критерии поиска труб:" << endl;
    cout << "1. По названию" << endl;
    cout << "2. По статусу ремонта" << endl;
    cout << "Выберите критерий: ";

    int kriteriy;
    cin >> kriteriy;
    vector<int> naydennye_id;

    if (kriteriy == 1) {
        cout << "Введите название для поиска: ";
        cin.ignore();
        string iskomoe_nazvanie;
        getline(cin, iskomoe_nazvanie);

        for (const auto& pair : truby) {
            if (pair.second.getName().find(iskomoe_nazvanie) != string::npos) {
                naydennye_id.push_back(pair.first);
            }
        }
    }
    else if (kriteriy == 2) {
        cout << "Введите статус ремонта (1 - в ремонте, 0 - работает): ";
        int status;
        cin >> status;
        bool iskomy_status = (status == 1);

        for (const auto& pair : truby) {
            if (pair.second.isRemont() == iskomy_status) {
                naydennye_id.push_back(pair.first);
            }
        }
    }
    else {
        cout << "Неверный критерий!" << endl;
        return;
    }

    if (naydennye_id.empty()) {
        cout << "Трубы по заданному критерию не найдены" << endl;
        return;
    }

    cout << "\nНайденные трубы:" << endl;
    for (int id : naydennye_id) {
        cout << "ID: " << id << endl;
        truby[id].print();
    }
    logirovanie::log("Выполнен поиск труб. Найдено: " + to_string(naydennye_id.size()) + " объектов");
}

void Poisk_KS() {
    if (kompressornye_stantsii.empty()) {
        cout << "Нет доступных компрессорных станций для поиска" << endl;
        return;
    }

    cout << "Критерии поиска компрессорных станций:" << endl;
    cout << "1. По названию" << endl;
    cout << "2. По проценту незадействованных цехов" << endl;
    cout << "Выберите критерий: ";

    int kriteriy;
    cin >> kriteriy;
    vector<int> naydennye_id;

    if (kriteriy == 1) {
        cout << "Введите название для поиска: ";
        cin.ignore();
        string iskomoe_nazvanie;
        getline(cin, iskomoe_nazvanie);

        for (const auto& pair : kompressornye_stantsii) {
            if (pair.second.getName().find(iskomoe_nazvanie) != string::npos) {
                naydennye_id.push_back(pair.first);
            }
        }
    }
    else if (kriteriy == 2) {
        cout << "Введите минимальный процент незадействованных цехов: ";
        double min_procent;
        cin >> min_procent;

        for (const auto& pair : kompressornye_stantsii) {
            if (pair.second.getProcentNeispolzovannyh() >= min_procent) {
                naydennye_id.push_back(pair.first);
            }
        }
    }
    else {
        cout << "Неверный критерий!" << endl;
        return;
    }

    if (naydennye_id.empty()) {
        cout << "Компрессорные станции по заданному критерию не найдены" << endl;
        return;
    }

    cout << "\nНайденные компрессорные станции:" << endl;
    for (int id : naydennye_id) {
        cout << "ID: " << id << endl;
        kompressornye_stantsii[id].print();
        cout << "Процент незадействованных цехов: " << kompressornye_stantsii[id].getProcentNeispolzovannyh() << "%" << endl;
    }
    logirovanie::log("Выполнен поиск КС. Найдено: " + to_string(naydennye_id.size()) + " объектов");
}

void Paketnoe_redaktirovanie_trub() {
    if (truby.empty()) {
        cout << "Нет доступных труб для пакетного редактирования" << endl;
        return;
    }

    vector<int> vozmozhnye_id;
    cout << "Выберите трубы для пакетного редактирования:" << endl;
    cout << "1. Все трубы" << endl;
    cout << "2. Только трубы в ремонте" << endl;
    cout << "3. Только работающие трубы" << endl;
    cout << "Выберите опцию: ";

    int opciya;
    cin >> opciya;

    for (const auto& pair : truby) {
        if (opciya == 1 ||
            (opciya == 2 && pair.second.isRemont()) ||
            (opciya == 3 && !pair.second.isRemont())) {
            vozmozhnye_id.push_back(pair.first);
        }
    }

    if (vozmozhnye_id.empty()) {
        cout << "Нет труб, соответствующих выбранному критерию" << endl;
        return;
    }

    vector<int> vybrannye_id;
    cout << "\nДоступные трубы для редактирования:" << endl;
    for (int id : vozmozhnye_id) {
        cout << "ID: " << id << " - " << truby[id].getName()
            << " (" << (truby[id].isRemont() ? "в ремонте" : "работает") << ")" << endl;
    }

    cout << "Введите ID труб для редактирования (по одному, -1 для завершения): " << endl;
    while (true) {
        int id;
        cin >> id;
        if (id == -1) break;

        if (find(vozmozhnye_id.begin(), vozmozhnye_id.end(), id) != vozmozhnye_id.end()) {
            vybrannye_id.push_back(id);
            cout << "Труба " << id << " добавлена в список редактирования" << endl;
        }
        else {
            cout << "Труба с ID " << id << " не найдена в доступном списке!" << endl;
        }
    }

    if (vybrannye_id.empty()) {
        cout << "Не выбрано ни одной трубы для редактирования" << endl;
        return;
    }

    cout << "\nДействия:" << endl;
    cout << "1. Изменить статус ремонта" << endl;
    cout << "2. Удалить выбранные трубы" << endl;
    cout << "Выберите действие: ";

    int deystvie;
    cin >> deystvie;

    if (deystvie == 1) {
        cout << "Введите новый статус (1 - в ремонте, 0 - работает): ";
        int status;
        cin >> status;
        bool noviy_status = (status == 1);

        for (int id : vybrannye_id) {
            truby[id].setRemont(noviy_status);
        }
        logirovanie::log("Пакетное изменение статуса " + to_string(vybrannye_id.size()) + " труб на: " + (noviy_status ? "в ремонте" : "работает"));
        cout << "Статус " << vybrannye_id.size() << " труб успешно изменен!" << endl;
    }
    else if (deystvie == 2) {
        for (int id : vybrannye_id) {
            truby.erase(id);
        }
        logirovanie::log("Пакетное удаление " + to_string(vybrannye_id.size()) + " труб");
        cout << "Удалено " << vybrannye_id.size() << " труб!" << endl;
    }
    else {
        cout << "Неверное действие!" << endl;
    }
}

void Sohranit_dannye() {
    cout << "Введите имя файла для сохранения: ";
    cin.ignore();
    string imya_faila;
    getline(cin, imya_faila);

    vector<Truba> vektor_trub;
    for (const auto& pair : truby) {
        vektor_trub.push_back(pair.second);
    }

    vector<Kompressornaya_stantsiya> vektor_ks;
    for (const auto& pair : kompressornye_stantsii) {
        vektor_ks.push_back(pair.second);
    }

    Sohranit_dannye(imya_faila, vektor_trub, vektor_ks);
    logirovanie::log("Сохранение данных в файл: " + imya_faila);
}

void Zagruzit_dannye() {
    cout << "Введите имя файла для загрузки: ";
    cin.ignore();
    string imya_faila;
    getline(cin, imya_faila);

    vector<Truba> vektor_trub;
    vector<Kompressornaya_stantsiya> vektor_ks;

    Zagruzit_dannye(imya_faila, vektor_trub, vektor_ks);

    truby.clear();
    kompressornye_stantsii.clear();

    sleduyushiy_id_truba = 1;
    sleduyushiy_id_ks = 1;

    for (const auto& truba : vektor_trub) {
        truby[sleduyushiy_id_truba++] = truba;
    }

    for (const auto& ks : vektor_ks) {
        kompressornye_stantsii[sleduyushiy_id_ks++] = ks;
    }

    logirovanie::log("Загрузка данных из файла: " + imya_faila);
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");
    logirovanie::log("Программа запущена");

    while (true) {
        Pokazat_menu();
        int vibor;
        cin >> vibor;

        switch (vibor) {
        case 1: Dobavit_trubu(); break;
        case 2: Dobavit_KS(); break;
        case 3: Pokazat_vse_obekty(); break;
        case 4: Redaktirovat_trubu(); break;
        case 5: Redaktirovat_KS(); break;
        case 6: Poisk_trub(); break;
        case 7: Poisk_KS(); break;
        case 8: Paketnoe_redaktirovanie_trub(); break;
        case 9: Sohranit_dannye(); break;
        case 10: Zagruzit_dannye(); break;
        case 0:
            logirovanie::log("Выход из программы");
            cout << "Выход из программы!" << endl;
            return 0;
        default:
            cout << "Неверный выбор!" << endl;
            break;
        }
    }
}