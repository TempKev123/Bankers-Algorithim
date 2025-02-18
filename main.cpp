#include <bits/stdc++.h>
using namespace std;
#include <iostream>
#include <string>
#include "split.cpp"
#include <random>
int randomNo()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 9); // Generates num

    int randomNumber = dist(gen);

    return randomNumber;
}

void printVector(const vector<int> &v)
{
    for (int num : v)
    {
        cout << num << " ";
    }
    cout << endl;
}

void printMatrix(const vector<vector<int>> &matrix)
{
    for (const auto &row : matrix)
    {
        for (int num : row)
        {
            cout << num << " "; // Print each element in the row
        }
        cout << endl; // After each row, move to the next line
    }
}

int main()
{
    string s;
    int no;
    vector<int> avail;
    vector<vector<int>> max, allo;
    bool texttruth = false;
    std::cout << "============================================\n";
    std::cout << "         WELCOME TO MOCK BANKER'S           \n";
    std::cout << "         ALGORITHM SIMULATION               \n";
    std::cout << "============================================\n";
    std::cout << "This program simulates the Banker's Algorithm\n";
    std::cout << "for deadlock avoidance in a banking system.\n";
    std::cout << "--------------------------------------------\n";
    string x;
    cout << "name the file please: ";
    cin >> x;

    ifstream f(x + ".txt");
    if (!f.is_open())
    {
        cerr << "\nno file found! Default to Random!\n";
    }
    else
    {
        texttruth = true;
    }

    if (texttruth)
    {
        getline(f, s);
        avail = convertStrtoArr(s);
        getline(f, s);
        no = stoi(s);
        string line;
        int row = 0;
        while (getline(f, line))
        {
            if (row % 2 == 0)
            {
                max.push_back({convertStrtoArr(line)});
            }
            else
            {
                allo.push_back({convertStrtoArr(line)});
            }
            row++;
        }

        f.close();
        cout << (x + " file loaded successfully!\n");
    }
    else
    {
        no = 3;
        avail = {randomNo(), randomNo(), randomNo()};
        for (int i = 0; i < 3; i++)
        {
            max.push_back({randomNo(), randomNo(), randomNo()});
            allo.push_back({randomNo(), randomNo(), randomNo()});
        }
    }
    cout << "# of Processes: " + to_string(no) << endl;
    cout << "Available:";
    printVector(avail);
    cout << "Maximum:\n";
    printMatrix(max);
    cout << "Allocated:\n";
    printMatrix(allo);
    int len = max[0].size();
    int temp;
    vector<vector<int>> need(no, {0, 0, 0});
    for (int i = 0; i < no; i++)
    {
        for (int j = 0; j < len; j++)
        {
            temp = max[i][j] - allo[i][j]; // Element-wisesubtraction
            if (temp < 0)
            {
                temp = 0;
            }
            need[i][j] = temp;
            // cout << "\ni: " << i << ", j: " << j << endl; // Correct way to print indices
        }
    }
    cout << "Needed:\n";
    printMatrix(need);

    // BANKERS/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    vector<int> total(no,0),available = avail;
    vector<bool> finish(no, false);
    string compOrder="";
    int comp = 0;
    // len=length of max[0]

    for (int i = 0; i < no; i++){
        for (int jj = 0; jj < len; jj++)
                {
                    total[jj] += need[i][jj];
                }
    }

    cout << "changes in available space: \n";
    while (comp < no)
    {
        for (int i = 0; i < no; i++)
        {
            if (finish[i])
            {
                break;
            }
            temp = 0;
            for (int j = 0; j < len; j++)//check if resources available
            {
                if (need[i][j] < available[j])
                {
                    temp++;
                }
                if (need[i][j]>(total[j]-need[i][j]+avail[j])){
                    cout << "ERROR: unable to allocate";
                    return 1;
                }
            }
            if (temp >= len)
            {
                for (int jj = 0; jj < len; jj++)
                {
                    available[jj] += need[i][jj];
                }
                printVector(available);
                finish[i] = true;
                comp++;
                compOrder += "P" + to_string(i)+" ";
            }
        }
    }
cout << "completion order: ";
cout << compOrder;
    return 0;
}