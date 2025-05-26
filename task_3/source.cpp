#include "header.h"

int CREATE_PLANE(vector<vector<string>>& V)
{
    string plane;
    getline(cin, plane);

    vector<string> onePlane;
    string word = "";
    int k = 0;
    for (char letter : plane) {
        if (letter == ' ') {
            if (word.size() != 0) {
                onePlane.push_back(word);
                k++;
            }
            word = "";
        }
        else {
            word.push_back(letter);
        }
    }
    if (k < 2) {
        cout << "Мало городов.";
    }
    if (word.size() != 0) {
        onePlane.push_back(word);
    }

    for (int i = 0; i < V.size(); i++) {
        if (V[i][0] == onePlane[0]) {
            cout << "Такой уже есть" << endl;
            return 0;
        }
    }

    for (int i = 0; i < onePlane.size() - 1; i++) {
        for (int j = i + 1; j < onePlane.size(); j++) {
            if (onePlane[i] == onePlane[j]) {
                cout << "Города повторяются";
                return 0;
            }
        }
    }
        
    V.push_back(onePlane);
    
    cout << endl;

    return 0;
}

int PLANES_FOR_TOWN(vector<vector<string>> V, string town)
{
    bool townNet = true;
    for (int i = 0; i < V.size(); i++) {
        for (int j = 1; j < V[i].size(); j++) {
            if (V[i][j] == town) {
                cout << V[i][0] << " ";
                townNet = false;
            }
        }
    }
    if (townNet) {
        cout << "Такого города нет";
    }
    cout << endl;
    cout << endl;

    return 0;
}

int TOWNS_FOR_PLANE(vector<vector<string>> V)
{
    string plane;
    cin >> plane;

    bool planeNet = true;
    for (int i = 0; i < V.size(); i++) {
        if (V[i][0] == plane) {
            for (int j = 1; j < V[i].size(); j++) {
                cout << V[i][j] << ": ";
                for (int k = 0; k < V.size(); k++) {
                    for (int c = 1; c < V[k].size(); c++) {
                        if (V[k][c] == V[i][j] && V[k][0] != plane) {
                            cout << V[k][0] << " ";
                        }
                    }
                }
                cout << endl;
            }
            planeNet = false;
        }
    }
    if (planeNet) {
        cout << "Такого самолета нет";
        cout << endl;
    }
    cout << endl;

    return 0;
}

int PLANES(vector<vector<string>> V)
{
    for (int i = 0; i < V.size(); i++) {
        cout << V[i][0] << ": ";
        for (int j = 1; j < V[i].size(); j++) {
            cout << V[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    return 0;
}
