#ifndef CS_H
#define CS_H
#include <string>

using namespace std;

// ����� ��
class Kompressornaya_stantsiya {
private:
    string name;           // �������� ��
    int kol_cehov;         // ����� ���������� �����  
    int vrabote;           // ���������� ���������� �����
    double klass_stancii;  // ����� ������� (�� 0.0 �� 5.0)

public:
    // ������������
    Kompressornaya_stantsiya();  
    Kompressornaya_stantsiya(string n, int cehi, int rabotayushchie, double klass);  

    string getName() const;                      // �������� �������� 
    int getKolCehov() const;                     // �������� ����� ���������� �����
    int getVrabote() const;                      // �������� ���������� ���������� �����
    double getKlass() const;                     // �������� ����� 
    double getProcentNeispolzovannyh() const;    // ���������� ������� ����������������� �����

    void zapustit_ceh();     // ��������� ���
    void ostanovit_ceh();    // ���������� ���
    void setName(const string& newName);  // ���������� ����� �������� ��

 
    void print() const;  // ������� ���� � ��
    void read();         // ������ ������ ��
};

#endif