#include "instruments.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <cctype>

using namespace std;

bool Proverka_stroki(const string& s) {
    if (s.empty()) return false;

    for (char c : s) {
        // ��������� ��� �����, �������, ������, ���������
        bool is_letter = (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ||
            (c >= '�' && c <= '�') || (c == '�' || c == '�'); 
        bool is_space = isspace(c);
        bool is_allowed_punctuation = (c == '-' || c == '\'' || c == ' ' || c == '.');

        if (!is_letter && !is_space && !is_allowed_punctuation) {
            return false;
        }
    }
    return true;    
}

string Vvod_stroki(const string& prompt) {
    string input;
    while (true) {
        cout << prompt;
        getline(cin, input);

        if (!input.empty()) {
            return input;
        }
        else {
            cout << "������! �������� �� ����� ���� ������: ";
        }
    }
}

float Proverka_fl(float min_znach, float max_znach) {
    float znachenie;
    while (true) {
        cin >> znachenie;
        if (cin.fail() || znachenie < min_znach || znachenie > max_znach) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "������. ������� ����� �� " << min_znach << " �� " << max_znach << ": ";
        }
        else {
            char next_char = cin.peek();
            if (next_char != '\n' && next_char != EOF) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "������! ������� ������ �����: ";
                continue;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return znachenie;
        }
    }
}

int Proverka_in(int min_znach, int max_znach) {
    int znachenie;
    while (true) {
        cin >> znachenie;
        if (cin.fail() || znachenie < min_znach || znachenie > max_znach) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "������. ������� ����� �� " << min_znach << " �� " << max_znach << ": ";
        }
        else {
            char next_char = cin.peek();
            if (next_char != '\n' && next_char != EOF) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "������! ������� ������ �����: ";
                continue;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return znachenie;
        }
    }
}

bool Proverka_bl() {
    int znachenie;
    while (true) {
        cin >> znachenie;
        if (cin.fail() || (znachenie != 0 && znachenie != 1)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "������. ������� 0 ��� 1: ";
        }
        else {
            char next_char = cin.peek();
            if (next_char != '\n' && next_char != EOF) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "������! ������� ������ ����� (0 ��� 1): ";
                continue;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return znachenie == 1;
        }
    }
}

void Sohranit_dannye(const string& filename, const vector<Truba>& truby, const vector<Kompressornaya_stantsiya>& kompressornye_stantsii) {
    ofstream outfile(filename);
    if (!outfile.is_open()) {
        cout << "������ �������� �����!" << endl;
        return;
    }

    if (outfile.is_open()) {
        outfile << "�����:" << endl;
        for (const auto& truba : truby) {
            outfile << truba.getName() << "," << truba.getDlina() << "," << truba.getDiameter() << "," << (truba.isRemont() ? "1" : "0") << endl;
        }

        outfile << "��������������������:" << endl;
        for (const auto& ks : kompressornye_stantsii) {
            outfile << ks.getName() << "," << ks.getKolCehov() << "," << ks.getVrabote() << "," << ks.getKlass() << endl;
        }
        outfile.close();
        cout << "������ ��������� � ���� " << filename << endl;
    }
}

void Zagruzit_dannye(const string& filename, vector<Truba>& truby, vector<Kompressornaya_stantsiya>& kompressornye_stantsii) {
    ifstream infile(filename);
    if (!infile.is_open()) {
        cout << "���� �� ����������!" << endl;
        return;
    }

    if (infile.is_open()) {
        string line;
        string type;
        while (getline(infile, line)) {
            if (line.find("�����:") != string::npos) {
                type = "�����";
                continue;
            }
            else if (line.find("��������������������:") != string::npos) {
                type = "��������������������";
                continue;
            }

            if (type == "�����") {
                string name, dlinaStr, diameterStr, remontStr;
                int commaIndex = static_cast<int>(line.find(','));
                name = line.substr(0, commaIndex);
                line = line.substr(commaIndex + 1);
                commaIndex = static_cast<int>(line.find(','));
                dlinaStr = line.substr(0, commaIndex);
                line = line.substr(commaIndex + 1);
                commaIndex = static_cast<int>(line.find(','));
                diameterStr = line.substr(0, commaIndex);
                remontStr = line.substr(commaIndex + 1);

                truby.push_back(Truba(name, stod(dlinaStr), stoi(diameterStr), remontStr == "1"));
            }
            else if (type == "��������������������") {
                string name, kolCehovStr, vraboteStr, klassStr;
                int commaIndex = static_cast<int>(line.find(','));
                name = line.substr(0, commaIndex);
                line = line.substr(commaIndex + 1);
                commaIndex = static_cast<int>(line.find(','));
                kolCehovStr = line.substr(0, commaIndex);
                line = line.substr(commaIndex + 1);
                commaIndex = static_cast<int>(line.find(','));
                vraboteStr = line.substr(0, commaIndex);
                klassStr = line.substr(commaIndex + 1);

                kompressornye_stantsii.push_back(Kompressornaya_stantsiya(name, stoi(kolCehovStr), stoi(vraboteStr), stod(klassStr)));
            }
        }
        infile.close();
        cout << "������ ��������� �� ����� " << filename << endl;
    }
}