#include <iostream>
#include <string>
#include <vector>

using namespace std;

int Out(vector<int>& V, int qual) {
    vector<vector<int>> windows;
    
    for (int i = 0; i < qual; i++) 
    {
        vector<int> time = { 0 };
        windows.push_back(time);
    }

    for (int i = 0; i < V.size(); i++) 
    {   //ищем индекс максимального
        int maxV = 0;
        int maxIndex = 0;
        
        for (int j = 0; j < V.size(); j++) 
        {
            if (V[j] > maxV) 
            {
                maxV = V[j];
                maxIndex = j;
            }
        }
  
        int minO = 1000;
        int minIndex;
        
        for (int j = 0; j < windows.size(); j++) 
        { //ищем индекс минимального
            if (windows[j][0] < minO) 
            {
                minO = windows[j][0];
                minIndex = j;
            }
        }
  
        windows[minIndex][0] += V[maxIndex];
        windows[minIndex].push_back(maxIndex + 1);
        V[maxIndex] = 0;
    }

    for (int i = 0; i < windows.size(); i++) 
    {
        cout << "Окно " << i + 1 << " (" << windows[i][0] << " минут): ";
        
        for (int j = 1; j < windows[i].size(); j++) 
        {
            if (windows[i][j] < 10) 
            {
                cout << "T00" << windows[i][j] << " ";
            }
            else 
            {
                cout << "T0" << windows[i][j] << " ";
            }
        }
        
        cout << endl;
    }
    
    return 0;
}

int main() {
    //setlocale(LC_ALL, "Russian");
    cout << "Введите кол-во окон" << endl;
    int qual;
    cin >> qual;
    
    int t = 1;
    vector<int> V;
    
    while (true) 
    {
        string enq;
        cin >> enq;
        
        if (enq == "DISTRIBUTE") 
        {
            Out(V, qual);
            break;
        }
        
        if (enq != "ENQUEUE") 
        {
            cout << "Некорректные данные" << endl;
        }
        else {
            int minut = 0;
            cin >> minut;
            
            if (minut == 0) 
            {
                cout << "Некорректные данные" << endl;
            }
            else
            {
                V.push_back(minut);
                if (t < 10) 
                {
                    cout << "T00" << t << endl;
                }
                else {
                    cout << "T0" << t << endl;
                }
            t++;
            } 
        }
    }
}