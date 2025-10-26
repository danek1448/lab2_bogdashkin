#ifndef TRUBA_H
#define TRUBA_H
#include <string>

using namespace std;

class Truba {
private:
    string name;        // �������� �����
    double dlina_km;    // ����� ����� � ����������
    int diameter_mm;    // ������� ����� � �����������
    bool remont;        // ������ ������� 

public:
    // ������������
    Truba();  
    Truba(string n, double l, int d, bool r); 

    string getName() const;     // �������� �������� �����
    double getDlina() const;    // �������� ����� �����
    int getDiameter() const;    // �������� ������� �����
    bool isRemont() const;      // �������� ������ �������

    void setRemont(bool r);                // ���������� ������ �������
    void setName(const string& newName);   // ���������� ����� �������� �����

    void print() const;  // ������� ���� � ����� 
    void read();         // ������ ������ � �����
};

#endif