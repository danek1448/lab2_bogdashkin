#include <iostream> // ввод-вывод
#include <fstream> // работа с файлом
#include <string> // работа со строками
#include <limits> // пределы числовых типов
#include <cctype> // для проверок на буквы и пробелы в строках

using namespace std;
// определение трубы
struct Truba {
    string name;
    float dlina_km;
    int diameter_mm;
    bool remont;
};

// определение компрессорной станцт
struct Compressor {
    string name;
    int kol_cehov;
    int vrabote;
    float klass_stancii;
};

// проверка строки на наличие цифр
bool Proverka_stroki(const string& s) {
    for (char c : s) {
        if (!isalpha(c) && !isspace(c)) {
            return false;
        }
    }
    return !s.empty();
}

// ввод строки с проверкой
string Vvod_stroki(const string& prompt) {
    string input;
    while (true) {
        cout << prompt;
        getline(cin, input);

        if (Proverka_stroki(input)) {
            return input;
        }
        else {
            cout << "Ошибка! Введите только буквы: ";
        }
    }
}

// проверка булевого значения на ввод только 0 или 1
bool Proverka_bl() {
    int znachenie;
    while (true) {
        cin >> znachenie;
        if (cin.fail() || (znachenie != 0 && znachenie != 1)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка. Введите 0 или 1: ";
        }
        else {
            // проверка на наличие лишнего после числа
            char next_char = cin.peek();
            if (next_char != '\n' && next_char != EOF) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Ошибка! Введите только число (0 или 1): ";
                continue;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return znachenie == 1;
        }
    }
}

// проверка флота от 0 до максимума через limits
float Proverka_fl(float min_znach = 0.0f, float max_znach = numeric_limits<float>::max()) {
    float znachenie;
    while (true) {
        cin >> znachenie;
        if (cin.fail() || znachenie < min_znach || znachenie > max_znach) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка. Введите число от " << min_znach << " до " << max_znach << ": ";
        }
        else {
            // проверка на наличие лишнего после числа
            char next_char = cin.peek();
            if (next_char != '\n' && next_char != EOF) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Ошибка! Введите только число: ";
                continue;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return znachenie;
        }
    }
}

// проверка инта от 0 до максимума через limits
int Proverka_in(int min_znach = 0, int max_znach = numeric_limits<int>::max()) {
    int znachenie;
    while (true) {
        cin >> znachenie;
        if (cin.fail() || znachenie < min_znach || znachenie > max_znach) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка. Введите число от " << min_znach << " до " << max_znach << ": ";
        }
        else {
            // проверка на наличие лишнего после числа
            char next_char = cin.peek();
            if (next_char != '\n' && next_char != EOF) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Ошибка! Введите только число: ";
                continue;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return znachenie;
        }
    }
}

// ввод данных о трубе
void Vvodtrubi(Truba& pipe) {

    pipe.name = Vvod_stroki("Введите название трубы (только буквы): ");

    cout << "Введите длину трубы(км): ";
    pipe.dlina_km = Proverka_fl(0.1f);

    cout << "Введите диаметр трубы(мм): ";
    pipe.diameter_mm = Proverka_in(1);

    cout << "Введите статус трубы (0 - работает, 1 - в ремонте): ";
    pipe.remont = Proverka_bl();

}

// ввод данных о кс
void Vvodcomp(Compressor& cm) {

    cm.name = Vvod_stroki("Введите название КС (только буквы): ");

    cout << "Введите общее количество цехов: ";
    cm.kol_cehov = Proverka_in(1);

    cout << "Введите количество работающих цехов: ";
    cm.vrabote = Proverka_in(0, cm.kol_cehov);

    cout << "Введите класс станции (0.0-5.0): ";
    cm.klass_stancii = Proverka_fl(0.0f, 5.0f);

}

// показ данных трубы
void Pokaz_trubi(const Truba& pipe) {
    if (pipe.name.empty()) {
        cout << "Труба не добавлена" << endl;
        return;
    }

    cout << "Труба " << endl;
    cout << "Название: " << pipe.name << endl;
    cout << "Длина: " << pipe.dlina_km << " км" << endl;
    cout << "Диаметр: " << pipe.diameter_mm << " мм" << endl;
    cout << "Статус: " << (pipe.remont ? "В ремонте" : "Работает") << endl;
    cout << endl;
}

// показ данных кс
void Pokaz_comp(const Compressor& cm) {
    if (cm.name.empty()) {
        cout << "Компрессорная станция не добавлена" << endl;
        return;
    }

    cout << "Компрессорная станция " << endl;
    cout << "Название: " << cm.name << endl;
    cout << "Всего цехов: " << cm.kol_cehov << endl;
    cout << "Работающих цехов: " << cm.vrabote << endl;
    cout << "Класс станции: " << cm.klass_stancii << endl;
    cout << endl;
}

// вывод всех введенных объектов
void Vse_objects(const Truba& pipe, const Compressor& cm) {
    Pokaz_trubi(pipe);
    Pokaz_comp(cm);
}

// статус ремонта трубы
void Izmenit_status(Truba& pipe) {
    if (pipe.name.empty()) {
        cout << "Труба не добавлена!" << endl;
        return;
    }

    cout << "Текущий статус: " << (pipe.remont ? "В ремонте" : "Работает") << endl;
    cout << "Введите новый статус (0 - работает, 1 - в ремонте): ";
    pipe.remont = Proverka_bl();
    cout << "Статус трубы изменен на: " << (pipe.remont ? "В ремонте" : "Работает") << endl;
}

// запуск цехов с проверкой количества
void Zapustit_cehi(Compressor& cm) {
    if (cm.name.empty()) {
        cout << "Компрессорная станция не добавлена!" << endl;
        return;
    }

    int dostupno = cm.kol_cehov - cm.vrabote;
    if (dostupno == 0) {
        cout << "Все цехи уже работают!" << endl;
        return;
    }

    cout << "Доступно для запуска: " << dostupno << " цехов" << endl;
    cout << "Сколько цехов запустить? ";

    int zapuskaem = Proverka_in(1, dostupno);
    cm.vrabote += zapuskaem;

    cout << "Запущено " << zapuskaem << " цехов. Теперь работает: " << cm.vrabote << " цехов" << endl;
}

// остановка цехов с проверкой на количество
void Ostanovit_cehi(Compressor& cm) {
    if (cm.name.empty()) {
        cout << "Компрессорная станция не добавлена!" << endl;
        return;
    }

    if (cm.vrabote == 0) {
        cout << "Нет работающих цехов!" << endl;
        return;
    }

    cout << "Работает цехов: " << cm.vrabote << endl;
    cout << "Сколько цехов остановить? ";

    int ostanavlivaem = Proverka_in(1, cm.vrabote);
    cm.vrabote -= ostanavlivaem;

    cout << "Остановлено " << ostanavlivaem << " цехов. Теперь работает: " << cm.vrabote << " цехов" << endl;
}

// сохранение в файл
void Sohranit_v_file(const Truba& pipe, const Compressor& cm) {
    ofstream file("labor1.txt");

    if (!file.is_open()) {
        cout << "Ошибка открытия файла для записи!" << endl;
        return;
    }

    file << "ТРУБА" << endl;
    file << pipe.name << endl;
    file << pipe.dlina_km << endl;
    file << pipe.diameter_mm << endl;
    file << pipe.remont << endl;

    file << "КС" << endl;
    file << cm.name << endl;
    file << cm.kol_cehov << endl;
    file << cm.vrabote << endl;
    file << cm.klass_stancii << endl;

    file.close();
    cout << "Данные успешно сохранены в файл!" << endl;
}

// чтение из файла
void Zagruzit_iz_file(Truba& pipe, Compressor& cm) {
    ifstream file("labor1.txt");

    if (!file.is_open()) {
        cout << "Файл данных не найден!" << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        if (line == "ТРУБА") {
            getline(file, pipe.name);
            file >> pipe.dlina_km >> pipe.diameter_mm >> pipe.remont;
            file.ignore();
        }
        else if (line == "КС") {
            getline(file, cm.name);
            file >> cm.kol_cehov >> cm.vrabote >> cm.klass_stancii;
            file.ignore();
        }
    }

    file.close();
    cout << "Данные успешно загружены из файла!" << endl;
}

// меню консоли
void menu() {
    Truba pipe = { "", 0.0f, 0, false };
    Compressor cm = { "", 0, 0, 0.0f };

    while (true) {
        cout << "Меню" << endl;
        cout << "1. Добавить трубу" << endl;
        cout << "2. Добавить КС" << endl;
        cout << "3. Просмотр всех объектов" << endl;
        cout << "4. Редактировать трубу" << endl;
        cout << "5. Редактировать КС" << endl;
        cout << "6. Сохранить данные" << endl;
        cout << "7. Загрузить данные" << endl;
        cout << "8. Выход" << endl;
        cout << "Выберите действие: ";

        int vibor = Proverka_in(1, 8);
        cout << endl;

        switch (vibor) {
        case 1:
            Vvodtrubi(pipe);
            cout << "Труба успешно добавлена!" << endl;
            break;

        case 2:
            Vvodcomp(cm);
            cout << "Компрессорная станция успешно добавлена!" << endl;
            break;

        case 3:
            Vse_objects(pipe, cm);
            break;

        case 4:
            Izmenit_status(pipe);
            break;

        case 5:
        {
            if (cm.name.empty()) {
                cout << "Сначала добавьте компрессорную станцию!" << endl;
                break;
            }

            cout << "1. Запустить цехи" << endl;
            cout << "2. Остановить цехи" << endl;
            cout << "Выберите действие: ";

            int podvibor = Proverka_in(1, 2);
            if (podvibor == 1) {
                Zapustit_cehi(cm);
            }
            else {
                Ostanovit_cehi(cm);
            }
            break;
        }

        case 6:
            Sohranit_v_file(pipe, cm);
            break;

        case 7:
            Zagruzit_iz_file(pipe, cm);
            break;

        case 8:
            cout << "Выход из программы!" << endl;
            return;
        }
    }
}

// пуск
int main() {
    setlocale(LC_ALL, "RU");
    menu();
    return 0;
}