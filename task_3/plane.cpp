#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "header.h"

using namespace std;

enum class Command
{
    CREATE_PLANE,
    PLANES_FOR_TOWN,
    TOWNS_FOR_PLANE,
    PLANES
};

int main() {
    map<string, int> commandMap = {
        {"CREATE_PLANE", 0},
        {"PLANES_FOR_TOWN", 1},
        {"TOWNS_FOR_PLANE", 2},
        {"PLANES", 3}
    };

    vector<vector<string>> V;

    while (true) {
        string commandValue;
        cin >> commandValue;

        Command command = static_cast<Command>(commandMap[commandValue]);

        if (command == Command::CREATE_PLANE) 
        {
            CREATE_PLANE(V);
        }
        else if (command == Command::PLANES_FOR_TOWN) 
        {
            string town;
            cin >> town;
            PLANES_FOR_TOWN(V, town);
        }
        else if (command == Command::TOWNS_FOR_PLANE) 
        {
            TOWNS_FOR_PLANE(V);
        }
        else if (command == Command::PLANES) 
        {
            PLANES(V);
        }
        else 
        {
            cout << "Такой команды нет" << endl;
        }
    }

    return 0;
}
