#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <iomanip>

using namespace std;

int main()
{
    // яйчейка: A 1 2 3
    int store[4][8][2][1] = { 0 };
    string storeName[4][8][2][1];

    int Azona = 0;
    int Bzona = 0;
    int Czona = 0;
    int Dzona = 0;
 
    while (true) 
    {
        string comand;
        cin >> comand;

        bool check = true;

        if (comand != "ADD" || comand != "REMOVE" || comand != "INFO") 
        {
            check = false;
        }
    
        if (check == false)
        {    
            cout << "Команда неверная.";
        }

        if (comand == "ADD" || comand == "REMOVE") 
        {
            string product;
            int qual;
            cin >> product >> qual;

            string cell;
            cin >> cell;

            char z = cell[0];
            int zona = static_cast<int>(z) + 64; // парсинг имени зоны (А, Б, В, Г)

            char s = cell[1];
            int rack = static_cast<int>(s) - 49;

            char s1 = cell[2];
            int section = static_cast<int>(s1) - 49;

            char p = cell[3];
            int shelf = static_cast<int>(p) - 49;

   
            if (qual > 10) 
            {
                cout << "Больше 10 единиц товара" << endl;
            }

            else if (zona > 3 || rack > 7 || section > 1 || shelf > 0) 
            {
                cout << "Нет такого адреса" << endl;
            }

            else if (comand == "ADD") 
            {

                if (store[zona][rack][section][shelf] == 0) 
                {
                    store[zona][rack][section][shelf] = qual;
                    storeName[zona][rack][section][shelf] = product;

                    if (zona == 0) 
                    {
                        Azona += qual;
                    }

                    if (zona == 1) 
                    {   
                        Bzona += qual;
                    }

                    if (zona == 2) 
                    {
                        Czona += qual;
                    }

                    if (zona == 3) 
                    {
                        Dzona += qual;
                    }

                }
                else
                {
                    cout << "Полка занята." << endl;
                }

            }
            
            else if (comand == "REMOVE") 
            {

                if (storeName[zona][rack][section][shelf] == product && store[zona][rack][section][shelf] >= qual) 
                {
                    store[zona][rack][section][shelf] -= qual;

                    if (zona == 0) 
                    {
                        Azona -= qual;
                    }

                    if (zona == 1) 
                    {
                        Bzona -= qual;
                    }

                    if (zona == 2) 
                    {
                        Czona -= qual;
                    }

                    if (zona == 3) 
                    {
                        Dzona -= qual;
                    }

                }   

                else 
                {
                    cout << "На полке другой товар или товара не достаточно." << endl;
                }

            }
        }
        else if (comand == "INFO") 
        {

            double zagruz = (Azona + Bzona + Czona + Dzona) * 100.0 / 640;

            double zagruzA = Azona * 100.0 / 160;
            double zagruzB = Bzona * 100.0 / 160;
            double zagruzC = Czona * 100.0 / 160;
            double zagruzD = Dzona * 100.0 / 160;

            cout << "Склад загружен на " << zagruz << "%" << endl;
            cout << "Зона А загружена на " << zagruzA << "%" << endl;
            cout << "Зона Б загружена на " << zagruzB << "%" << endl;
            cout << "Зона В загружена на " << zagruzC << "%" << endl;
            cout << "Зона Г загружена на " << zagruzD << "%" << endl;
            cout << endl << "Содержимое склада:" << endl;

            for (int i1 = 0; i1 < 4; i1++) 
            {
                for (int i2 = 0; i2 < 8; i2++) 
                {
                    for (int i3 = 0; i3 < 2; i3++) 
                    {
                        for (int i4 = 0; i4 < 1; i4++) 
                        {

                            char zon = static_cast<char>(i1 /*- 64*/);

                            if (store[i1][i2][i3][i4] != 0) 
                            {

                                cout << zon << i2 + 1 << i3 + 1 << i4 + 1 << " ";
                                cout << storeName[i1][i2][i3][i4] << " " << store[i1][i2][i3][i4] << endl;
                            }
                        }
                    }
                }
            }

            cout << endl << "Пустые ячейки:" << endl;

            //vector<int> Zones {, , , };
            for (int i1 = 0; i1 < 4; i1++) 
            {
                for (int i2 = 0; i2 < 8; i2++) 
                {
                    for (int i3 = 0; i3 < 2; i3++) 
                    {
                        for (int i4 = 0; i4 < 1; i4++) 
                        {

                            char zon = static_cast<char>(i1 - 64);

                            //char zone = static_cast<char>(Zones[i1]);

                            if (store[i1][i2][i3][i4] == 0) 
                            {
                                cout << zon << i2 + 1 << i3 + 1 << i4 + 1 << " ";
                            }
                        }
                    }
                }
            }
        }
    }
}