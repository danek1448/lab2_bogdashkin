#include "truba.h"
#include "instruments.h"
#include <iostream>
#include <string>

using namespace std;

// конструкторы
Truba::Truba() : name(""), dlina_km(0), diameter_mm(0), remont(false) {}

Truba::Truba(string n, double l, int d, bool r) : name(n), dlina_km(l), diameter_mm(d), remont(r) {}

// получаем данные о трубе
string Truba::getName() const { return name; }
double Truba::getDlina() const { return dlina_km; }
int Truba::getDiameter() const { return diameter_mm; }
bool Truba::isRemont() const { return remont; }
void Truba::setRemont(bool r) { remont = r; }
void Truba::setName(const string& newName) { name = newName; }

// вывод инф о трубе 
void Truba::print() const {
    if (name.empty()) {
        cout << "Труба не добавлена" << endl;
        return;
    }

    cout << "Труба " << endl;
    cout << "Название: " << name << endl;
    cout << "Длина: " << dlina_km << " км" << endl;
    cout << "Диаметр: " << diameter_mm << " мм" << endl;
    cout << "Статус: " << (remont ? "В ремонте" : "Работает") << endl;
    cout << endl;
}

// ввод данных о трубе
void Truba::read() {
    name = Vvod_stroki("Введите название трубы: ");

    cout << "Введите длину трубы(км): ";
    dlina_km = Proverka_fl(0.1f);

    cout << "Введите диаметр трубы(мм): ";
    diameter_mm = Proverka_in(1);

    cout << "Введите статус трубы (0 - работает, 1 - в ремонте): ";
    remont = Proverka_bl();
}