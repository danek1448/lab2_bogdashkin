#include "cs.h"
#include "instruments.h"
#include <iostream>
#include <string>

using namespace std;

// инициализируем
Kompressornaya_stantsiya::Kompressornaya_stantsiya() : name(""), kol_cehov(0), vrabote(0), klass_stancii(0.0) {}

Kompressornaya_stantsiya::Kompressornaya_stantsiya(string n, int cehi, int rabotayushchie, double klass)
    : name(n), kol_cehov(cehi), vrabote(rabotayushchie), klass_stancii(klass) {
}

// получаем данные о кс
string Kompressornaya_stantsiya::getName() const { return name; }
int Kompressornaya_stantsiya::getKolCehov() const { return kol_cehov; }
int Kompressornaya_stantsiya::getVrabote() const { return vrabote; }
double Kompressornaya_stantsiya::getKlass() const { return klass_stancii; }

// расчет процента незадействованных цехов
double Kompressornaya_stantsiya::getProcentNeispolzovannyh() const {
    return (kol_cehov - vrabote) * 100.0 / kol_cehov;
}

// запуск одного цеха
void Kompressornaya_stantsiya::zapustit_ceh() {
    if (vrabote < kol_cehov) {
        vrabote++;  
        cout << "Цех запущен!" << endl;
    }
    else {
        cout << "Все цехи уже работают!" << endl;
    }
}

// остановка одного цеха
void Kompressornaya_stantsiya::ostanovit_ceh() {
    if (vrabote > 0) {
        vrabote--; 
        cout << "Цех остановлен!" << endl;
    }
    else {
        cout << "Все цехи уже остановлены!" << endl;
    }
}

// установка нового названия станции
void Kompressornaya_stantsiya::setName(const string& newName) { name = newName; }

// вывод информации о станции 
void Kompressornaya_stantsiya::print() const {
    if (name.empty()) {
        cout << "Компрессорная станция не добавлена" << endl;
        return;
    }

    cout << "Компрессорная станция " << endl;
    cout << "Название: " << name << endl;
    cout << "Всего цехов: " << kol_cehov << endl;
    cout << "Работающих цехов: " << vrabote << endl;
    cout << "Класс станции: " << klass_stancii << endl;
    cout << endl;
}

// ввод данных о станции 
void Kompressornaya_stantsiya::read() {
    name = Vvod_stroki("Введите название КС: ");

    cout << "Введите общее количество цехов: ";
    kol_cehov = Proverka_in(1);

    cout << "Введите количество работающих цехов: ";
    vrabote = Proverka_in(0, kol_cehov);

    cout << "Введите класс станции (от 0 до 5): ";
    klass_stancii = Proverka_fl(0.0f, 5.0f);
}