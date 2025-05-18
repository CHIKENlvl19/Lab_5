#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

void CLASS(int day, string cl, int &curMonth, const vector<int>& daysInMonth, map<int, vector<string>>& classes) {
    if (day > daysInMonth[curMonth - 1]) {
        cout << "Error. In this month " << daysInMonth[curMonth - 1] << " days.";
        return;
    }

    classes[day].push_back(cl);
}

void NEXT(int &curMonth, const vector<int>& daysInMonth, map<int, vector<string>>& classes) {
    int currentDays = daysInMonth[curMonth - 1];
    curMonth++;
    int nextDays = daysInMonth[curMonth - 1];

    if (currentDays > nextDays) {
        int lastLastDay = nextDays - 1;

        for (int day = currentDays; day > lastLastDay; day--) {
            if (classes.find(day) != classes.end()) {
                classes[lastLastDay].insert(classes[lastLastDay].end(), classes[day].begin(), classes[day].end());
                classes.erase(day);
            }
        }
    }
}

void VIEW(int day, int &curMonth, const vector<int>& daysInMonth, map<int, vector<string>>& classes) {
    if (day > daysInMonth[curMonth - 1]) {
        cout << "Error. In this month " << daysInMonth[curMonth - 1] << " days.";
        return;
    }

    if (!classes[day].empty()) {
        cout << "In " << day << " day " << classes[day].size() << " classes in university: ";
        for (const auto& cls : classes[day]) {
            cout << cls << ", ";
        }
        cout << endl;
    } else {
        cout << "In day " << day << " we are free!" << endl;
    }
}

int main() {
    map<int, vector<string>> classes;
    int curMonth = 1;
    vector<int> daysInMonth{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    int qual;
    cin >> qual;

    for (int i = 0; i < qual; i++) {
        string command;
        cin >> command;

        if (command == "CLASS") {
            int day;
            string cl;

            cin >> day >> cl;
            
            CLASS(day, cl, curMonth, daysInMonth, classes);
        } 
        else if (command == "NEXT") 
        {
            NEXT(curMonth, daysInMonth, classes);
        } 
        else if (command == "VIEW") 
        {
            int day;
            cin >> day;

            VIEW(day, curMonth, daysInMonth, classes);
        }
    }
}