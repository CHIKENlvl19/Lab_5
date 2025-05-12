#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <iomanip>
#include <cstring> // для memcmp

using namespace std;

// проверка, начинается ли строка с заданного UTF-8 символа
bool startsWithUTF8(const string& str, const char* utf8Bytes, size_t len) {
    if (str.length() < len) return false;
    return memcmp(str.c_str(), utf8Bytes, len) == 0;
}

int main() {
    // настройки склада
    const int ZONES = 5;
    const int RACKS = 8;
    const int SECTIONS = 2;
    const int SHELVES = 1;
    const int MAX_CELL_CAPACITY = 10;
    const int TOTAL_CAPACITY = ZONES * RACKS * SECTIONS * SHELVES * MAX_CELL_CAPACITY;

    // склад и названия товаров
    int store[ZONES][RACKS][SECTIONS][SHELVES] = {0};
    string storeName[ZONES][RACKS][SECTIONS][SHELVES];

    // загрузка зон
    int zoneCapacity[ZONES] = {0};

    // UTF-8 последовательности для зон
    struct Zone {
        const char* utf8; // указатель на UTF-8 байты
        size_t length;    // длина UTF-8 символа (2 байта для кириллицы)
        int index;
    };

    vector<Zone> zones = {
        { "\xD0\x90", 2, 0 }, // А
        { "\xD0\x91", 2, 1 }, // Б
        { "\xD0\x92", 2, 2 }, // В
        { "\xD0\x93", 2, 3 }, // Г
        { "\xD0\x94", 2, 4 }  // Д
    };

    while (true) {
        string command;
        cin >> command;

        if (command == "ADD" || command == "REMOVE") {
            string product;
            int quantity;
            string cell;

            cin >> product >> quantity >> cell;

            // парсинг зоны
            int zone = -1;
            size_t zoneLength = 0;
            for (const auto& z : zones) {
                if (startsWithUTF8(cell, z.utf8, z.length)) { // используйте z.utf8 вместо z
                    zone = z.index;
                    zoneLength = z.length;
                    break;
                }
            }

            if (zone == -1) {
                cout << "Неверная зона хранения" << endl;
                continue;
            }

            // парсинг стеллажа (одна цифра)
            if (cell.length() < zoneLength + 1 || !isdigit(cell[zoneLength])) { // используйте z.length вместо z
                cout << "Неверный номер стеллажа" << endl;
                continue;
            }
            int rack = cell[zoneLength] - '0' - 1; // используйте z.length вместо z
            if (rack < 0 || rack >= RACKS) {
                cout << "Нет такого стеллажа" << endl;
                continue;
            }

            // парсинг секции
            if (cell.length() < zoneLength + 2 || !isdigit(cell[zoneLength + 1])) { // используйте z.length вместо z
                cout << "Неверный номер секции" << endl;
                continue;
            }
            int section = cell[zoneLength + 1] - '0' - 1; // используйте z.length вместо z
            if (section < 0 || section >= SECTIONS) {
                cout << "Нет такой секции" << endl;
                continue;
            }

            // парсинг полки (всегда 1)
            if (cell.length() < zoneLength + 3 || cell[zoneLength + 2] != '1') {
                cout << "Нет такой полки" << endl;
                continue;
            }
            int shelf = 0;

            // обработка команд ADD и REMOVE
            if (command == "ADD") {
                if (store[zone][rack][section][shelf] == 0) {
                    store[zone][rack][section][shelf] = quantity;
                    storeName[zone][rack][section][shelf] = product;
                    zoneCapacity[zone] += quantity;
                    cout << "Товар добавлен" << endl;
                } else {
                    cout << "Ячейка занята" << endl;
                }
            } else if (command == "REMOVE") {
                if (storeName[zone][rack][section][shelf] == product && store[zone][rack][section][shelf] >= quantity) {
                    store[zone][rack][section][shelf] -= quantity;
                    zoneCapacity[zone] -= quantity;
                    if (store[zone][rack][section][shelf] == 0) {
                        storeName[zone][rack][section][shelf] = "";
                    }
                    cout << "Товар удален" << endl;
                } else {
                    cout << "Невозможно удалить товар" << endl;
                }
            }
        } else if (command == "INFO") {
            // вычисление загрузки
            int totalUsed = 0;
            for (int i = 0; i < ZONES; i++) {
                totalUsed += zoneCapacity[i];
            }
            double totalLoad = (totalUsed * 100.0) / TOTAL_CAPACITY;

            cout << fixed << setprecision(2);
            cout << "Склад загружен на " << totalLoad << "%" << endl;

            // загрузка по зонам
            const char* zoneNames[] = {"А", "Б", "В", "Г", "Д"};
            for (int i = 0; i < ZONES; i++) {
                double zoneLoad = (zoneCapacity[i] * 100.0) / (RACKS * SECTIONS * SHELVES * MAX_CELL_CAPACITY);
                cout << "Зона " << zoneNames[i] << " загружена на " << zoneLoad << "%" << endl;
            }

            cout << endl << "Содержимое склада:" << endl;
            for (int z = 0; z < ZONES; z++) {
                for (int r = 0; r < RACKS; r++) {
                    for (int s = 0; s < SECTIONS; s++) {
                        for (int p = 0; p < SHELVES; p++) {
                            if (store[z][r][s][p] > 0) {
                                cout << zoneNames[z] << (r + 1) << (s + 1) << (p + 1) << " ";
                                cout << storeName[z][r][s][p] << " " << store[z][r][s][p] << endl;
                            }
                        }
                    }
                }
            }

            cout << endl << "Пустые ячейки:" << endl;
            for (int z = 0; z < ZONES; z++) {
                for (int r = 0; r < RACKS; r++) {
                    for (int s = 0; s < SECTIONS; s++) {
                        for (int p = 0; p < SHELVES; p++) {
                            if (store[z][r][s][p] == 0) {
                                cout << zoneNames[z] << (r + 1) << (s + 1) << (p + 1) << " ";
                            }
                        }
                    }
                }
            }
            cout << endl;
        }
    }
}