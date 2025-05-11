#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>

using namespace std;

int main() {
    // Инициализация склада (4 зоны, 8 стеллажей, 2 секции, 1 полка)
    int store[4][8][2][1] = { 0 };
    string storeName[4][8][2][1];

    // Переменные для хранения загрузки зон
    int zoneCapacity[4] = { 0, 0, 0, 0 };
    const int MAX_CELL_CAPACITY = 10;
    const int TOTAL_CAPACITY = 640; // Общая вместимость

    while (true) 
    {
        string command;
        cin >> command;

        // Проверка команды
        bool validCommand = (command == "ADD" || command == "REMOVE" || command == "INFO");

        if (!validCommand) {
            cout << "Неверная команда. Доступные команды: ADD, REMOVE, INFO" << endl;
            continue;
        }

        if (command == "ADD" || command == "REMOVE") 
        {
            string product;
            int quantity;
            string cell;

            // Чтение параметров команды
            cin >> product >> quantity >> cell;

            // Проверка длины адреса
            if (cell.length() < 4) {
                cout << "Неверный формат адреса" << endl;
                continue;
            }

            // Парсинг зоны
            char zoneChar = cell[0];
            map<char, int> zoneMap = {{'A', 0}, {'B', 1}, {'C', 2}, {'D', 3}};
            
            if (zoneMap.find(zoneChar) == zoneMap.end()) {
                cout << "Неверная зона хранения" << endl;
                continue;
            }
            int zone = zoneMap[zoneChar];

            // Парсинг стеллажа (две цифры)
            if (cell.length() < 3 || !isdigit(cell[1]) || !isdigit(cell[2])) {
                cout << "Неверный номер стеллажа" << endl;
                continue;
            }
            int rack = stoi(cell.substr(1, 2)) - 1; // индексация с 0
            if (rack < 0 || rack >= 8) {
                cout << "Нет такого стеллажа" << endl;
                continue;
            }

            // Парсинг секции
            int section = cell[3] - '0' - 1;
            if (section < 0 || section >= 2) {
                cout << "Нет такой секции" << endl;
                continue;
            }

            // Парсинг полки (всегда 1)
            int shelf = 0;
            if (cell.length() > 4 && cell[4] != '1') {
                cout << "Нет такой полки" << endl;
                continue;
            }

            // Проверка количества товара
            if (quantity > MAX_CELL_CAPACITY) {
                cout << "Количество не может превышать " << MAX_CELL_CAPACITY << " единиц" << endl;
                continue;
            }

            // Обработка команды ADD
            if (command == "ADD")
            {
                if (store[zone][rack][section][shelf] == 0) {
                    store[zone][rack][section][shelf] = quantity;
                    storeName[zone][rack][section][shelf] = product;
                    zoneCapacity[zone] += quantity;
                    cout << "Товар добавлен" << endl;
                }
                else {
                    cout << "Ячейка занята" << endl;
                }
            }
            // Обработка команды REMOVE
            else if (command == "REMOVE")
            {
                if (storeName[zone][rack][section][shelf] == product && 
                    store[zone][rack][section][shelf] >= quantity)
                {
                    store[zone][rack][section][shelf] -= quantity;
                    zoneCapacity[zone] -= quantity;
                    
                    // Если ячейка опустела
                    if (store[zone][rack][section][shelf] == 0) {
                        storeName[zone][rack][section][shelf] = "";
                    }
                    cout << "Товар удален" << endl;
                }
                else {
                    cout << "Невозможно удалить товар" << endl;
                }
            }
        }
        // Обработка команды INFO
        else if (command == "INFO")
        {
            // Вычисление загрузки
            int totalUsed = 0;
            for(int i = 0; i < 4; i++) {
                totalUsed += zoneCapacity[i];
            }
            
            double totalLoad = (totalUsed * 100.0) / TOTAL_CAPACITY;
            
            cout << fixed << setprecision(2);
            cout << "Склад загружен на " << totalLoad << "%" << endl;
            
            // Загрузка по зонам
            const char* zoneNames[] = {"А", "Б", "В", "Г"};
            for(int i = 0; i < 4; i++) {
                double zoneLoad = (zoneCapacity[i] * 100.0) / 160;
                cout << "Зона " << zoneNames[i] << " загружена на " << zoneLoad << "%" << endl;
            }
            
            cout << endl << "Содержимое склада:" << endl;
            for(int z = 0; z < 4; z++) {
                for(int r = 0; r < 8; r++) {
                    for(int s = 0; s < 2; s++) {
                        for(int p = 0; p < 1; p++) {
                            if(store[z][r][s][p] > 0) {
                                cout << zoneNames[z] << (r+1) << (s+1) << (p+1) << " ";
                                cout << storeName[z][r][s][p] << " " << store[z][r][s][p] << endl;
                            }
                        }
                    }
                }
            }
            
            cout << endl << "Пустые ячейки:" << endl;
            for(int z = 0; z < 4; z++) {
                for(int r = 0; r < 8; r++) {
                    for(int s = 0; s < 2; s++) {
                        for(int p = 0; p < 1; p++) {
                            if(store[z][r][s][p] == 0) {
                                cout << zoneNames[z] << (r+1) << (s+1) << (p+1) << " ";
                            }
                        }
                    }
                }
            }
            cout << endl;
        }
    }
}