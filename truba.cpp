#include "truba.h"
#include "instruments.h"
#include <iostream>
#include <string>

using namespace std;

// ������������
Truba::Truba() : name(""), dlina_km(0), diameter_mm(0), remont(false) {}

Truba::Truba(string n, double l, int d, bool r) : name(n), dlina_km(l), diameter_mm(d), remont(r) {}

// �������� ������ � �����
string Truba::getName() const { return name; }
double Truba::getDlina() const { return dlina_km; }
int Truba::getDiameter() const { return diameter_mm; }
bool Truba::isRemont() const { return remont; }
void Truba::setRemont(bool r) { remont = r; }
void Truba::setName(const string& newName) { name = newName; }

// ����� ��� � ����� 
void Truba::print() const {
    if (name.empty()) {
        cout << "����� �� ���������" << endl;
        return;
    }

    cout << "����� " << endl;
    cout << "��������: " << name << endl;
    cout << "�����: " << dlina_km << " ��" << endl;
    cout << "�������: " << diameter_mm << " ��" << endl;
    cout << "������: " << (remont ? "� �������" : "��������") << endl;
    cout << endl;
}

// ���� ������ � �����
void Truba::read() {
    name = Vvod_stroki("������� �������� �����: ");

    cout << "������� ����� �����(��): ";
    dlina_km = Proverka_fl(0.1f);

    cout << "������� ������� �����(��): ";
    diameter_mm = Proverka_in(1);

    cout << "������� ������ ����� (0 - ��������, 1 - � �������): ";
    remont = Proverka_bl();
}