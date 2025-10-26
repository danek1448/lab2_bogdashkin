#ifndef INSTRUMENTS_H
#define INSTRUMENTS_H

#include <string>
#include <vector>
#include "truba.h"
#include "cs.h"

using namespace std;

// ������� �������� �����
bool Proverka_stroki(const string& s);  // �������� ������ �� ���������� �������
string Vvod_stroki(const string& prompt);  // ���� ������ � ����������
float Proverka_fl(float min_znach = 0.0f, float max_znach = 3.402823466e+38f);  // ���� �������� �����
int Proverka_in(int min_znach = 0, int max_znach = 2147483647);  // ���� ������ �����
bool Proverka_bl();  //  ���� �������� �������� 

void Sohranit_dannye(const string& filename, const vector<Truba>& truby, const vector<Kompressornaya_stantsiya>& kompressornye_stantsii);  // ���������� ������ � ����
void Zagruzit_dannye(const string& filename, vector<Truba>& truby, vector<Kompressornaya_stantsiya>& kompressornye_stantsii);  // �������� ������ �� �����

#endif