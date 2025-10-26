#ifndef CS_H
#define CS_H
#include <string>

using namespace std;

// класс кс
class Kompressornaya_stantsiya {
private:
    string name;           // название кс
    int kol_cehov;         // общее количество цехов  
    int vrabote;           // количество работающих цехов
    double klass_stancii;  // класс станции (от 0.0 до 5.0)

public:
    // конструкторы
    Kompressornaya_stantsiya();  
    Kompressornaya_stantsiya(string n, int cehi, int rabotayushchie, double klass);  

    string getName() const;                      // получить название 
    int getKolCehov() const;                     // получить общее количество цехов
    int getVrabote() const;                      // получить количество работающих цехов
    double getKlass() const;                     // получить класс 
    double getProcentNeispolzovannyh() const;    // рассчитать процент незадействованных цехов

    void zapustit_ceh();     // запустить цех
    void ostanovit_ceh();    // остановить цех
    void setName(const string& newName);  // установить новое название кс

 
    void print() const;  // вывести инфу о кс
    void read();         // ввести данные кс
};

#endif