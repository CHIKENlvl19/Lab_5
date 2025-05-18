#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

void CLASS(int day, string cl, int &curMonth, const vector<int>& daysInMonth, map<int, vector<string>>& classes) {
    if (day > daysInMonth[curMonth - 1]) 
    {
        cout << "Error. In this month " << daysInMonth[curMonth - 1] << " days.";
        return;
    }  
 
    classes[day].push_back(cl);
    for (size_t i = 0; i < classes[day].size(); i++) 
    {
        for (size_t j = 1; j < classes[day].size(); j++) 
        {
            auto iter = cbegin(classes[day]);
            if (classes[day][i] == classes[day][j]) 
            {
                classes[day].erase(iter + j);
            }
        }
    }
}

void NEXT(int &curMonth, const vector<int>& daysInMonth, map<int, vector<string>>& classes) {
    if (daysInMonth[curMonth - 1] >= daysInMonth[curMonth]) 
    {
        int lastDay = daysInMonth[curMonth - 1];
        int lastLastDay = daysInMonth[curMonth] - 1;
  
        for (lastDay; lastDay > lastLastDay + 1; lastDay--) 
        {
            vector<string> ld = classes[lastDay];
            
            classes[lastLastDay].insert(begin(classes[lastLastDay]), ld.begin(), ld.end());
            classes[lastDay].clear();
        }
    }
    
    curMonth++;
}

void VIEW(int day, int &curMonth, const vector<int>& daysInMonth, map<int, vector<string>>& classes) {
    if (day > daysInMonth[curMonth - 1]) 
    {
        cout << "Error. In this month " << daysInMonth[curMonth - 1] << " days.";
        return;
    }

    if (!classes[day].empty()) 
    {
        cout << "In " << day << " day " << classes[day].size() << " classes in university: ";
        
        for (string className : classes[day]) 
        {
            cout << className << ", ";
        }
        
        cout << endl;
    }
    else
    {
        cout << "In " << day << " day We are free!" << endl;
    }
}

int main() {

    map<int, vector<string>> classes;
    int curMonth = 1;
    vector<int> daysInMonth{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    int qual;
    cin >> qual;

    for (int i = 0; i < qual; i++) 
    {
        string command;
        cin >> command;
        
        if (command == "CLASS") 
        {
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