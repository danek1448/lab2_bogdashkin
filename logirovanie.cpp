#include "logirovanie.h"
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std; 

void logirovanie::log(const string& message) {
    string logFileName = "log.txt";
    // ��������� ���� ��� ���������� �������
    ofstream logFile(logFileName, ios::app);

    // �������� ��������� ������ ����� 
    if (!logFile.is_open()) {
        ofstream createLogFile(logFileName);
        createLogFile.close();
        logFile.open(logFileName, ios::app);
    }

    if (logFile.is_open()) {
        time_t now = time(0);
        char dt[26]; // ����� ��� �������� ������ � ����� � ��������
        ctime_s(dt, sizeof dt, &now); // �������� ������ �������
        logFile << dt << " - " << message << endl;
        logFile.close();
    }
    else {
        cerr << "Unable to open log file!" << endl;
    }
}