#include <iostream>
#include <string>
#include <vector>
#include "header.h"

using namespace std;

enum class Command
{
    CREATE_PLANE,
    PLANES_FOR_TOWN,
    TOWNS_FOR_PLANE,
    PLANES,
    INVALID // для обработки несуществующих команд
};

// функция для преобразования строки в команду
Command getCommandFromString(const string& commandValue) {
    if (commandValue == "CREATE_PLANE") return Command::CREATE_PLANE;
    if (commandValue == "PLANES_FOR_TOWN") return Command::PLANES_FOR_TOWN;
    if (commandValue == "TOWNS_FOR_PLANE") return Command::TOWNS_FOR_PLANE;
    if (commandValue == "PLANES") return Command::PLANES;
    return Command::INVALID; // если команда не распознана
}

int main() {
    vector<vector<string>> V;

    while (true) {
        string commandValue;
        cin >> commandValue;

        Command command = getCommandFromString(commandValue);

        switch (command) {
            case Command::CREATE_PLANE:
                CREATE_PLANE(V);
                break;
            case Command::PLANES_FOR_TOWN: {
                string town;
                cin >> town;
                PLANES_FOR_TOWN(V, town);
                break;
            }
            case Command::TOWNS_FOR_PLANE:
                TOWNS_FOR_PLANE(V);
                break;
            case Command::PLANES:
                PLANES(V);
                break;
            case Command::INVALID:

            default:
                cout << "Такой команды нет" << endl;
                break;
        }
    }
    
    return 0;
}
