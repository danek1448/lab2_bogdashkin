#include "cs.h"
#include "instruments.h"
#include <iostream>
#include <string>

using namespace std;

// ��������������
Kompressornaya_stantsiya::Kompressornaya_stantsiya() : name(""), kol_cehov(0), vrabote(0), klass_stancii(0.0) {}

Kompressornaya_stantsiya::Kompressornaya_stantsiya(string n, int cehi, int rabotayushchie, double klass)
    : name(n), kol_cehov(cehi), vrabote(rabotayushchie), klass_stancii(klass) {
}

// �������� ������ � ��
string Kompressornaya_stantsiya::getName() const { return name; }
int Kompressornaya_stantsiya::getKolCehov() const { return kol_cehov; }
int Kompressornaya_stantsiya::getVrabote() const { return vrabote; }
double Kompressornaya_stantsiya::getKlass() const { return klass_stancii; }

// ������ �������� ����������������� �����
double Kompressornaya_stantsiya::getProcentNeispolzovannyh() const {
    return (kol_cehov - vrabote) * 100.0 / kol_cehov;
}

// ������ ������ ����
void Kompressornaya_stantsiya::zapustit_ceh() {
    if (vrabote < kol_cehov) {
        vrabote++;  
        cout << "��� �������!" << endl;
    }
    else {
        cout << "��� ���� ��� ��������!" << endl;
    }
}

// ��������� ������ ����
void Kompressornaya_stantsiya::ostanovit_ceh() {
    if (vrabote > 0) {
        vrabote--; 
        cout << "��� ����������!" << endl;
    }
    else {
        cout << "��� ���� ��� �����������!" << endl;
    }
}

// ��������� ������ �������� �������
void Kompressornaya_stantsiya::setName(const string& newName) { name = newName; }

// ����� ���������� � ������� 
void Kompressornaya_stantsiya::print() const {
    if (name.empty()) {
        cout << "������������� ������� �� ���������" << endl;
        return;
    }

    cout << "������������� ������� " << endl;
    cout << "��������: " << name << endl;
    cout << "����� �����: " << kol_cehov << endl;
    cout << "���������� �����: " << vrabote << endl;
    cout << "����� �������: " << klass_stancii << endl;
    cout << endl;
}

// ���� ������ � ������� 
void Kompressornaya_stantsiya::read() {
    name = Vvod_stroki("������� �������� �� (������ �����): ");

    cout << "������� ����� ���������� �����: ";
    kol_cehov = Proverka_in(1);

    cout << "������� ���������� ���������� �����: ";
    vrabote = Proverka_in(0, kol_cehov);

    cout << "������� ����� ������� (0.0-5.0): ";
    klass_stancii = Proverka_fl(0.0f, 5.0f);
}