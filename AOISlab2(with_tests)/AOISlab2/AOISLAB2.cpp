#include <iostream>
#include <algorithm>
#include<math.h>
#include <string>
#include <vector>
#include <cmath>
#include "..\Tests_LAB2\pch.h"

using namespace std;

//!(((!a)+(!b))*(!((!c)*(!b))))
//!(((!x1)+(!x2))*(!((!x3)*(!x2))))



bool check(string function)
{
    if (function.find('a') == -1 || function.find('b') == -1 || function.find('c') == -1 || function.find('(') == -1 || function.find(')') == -1)
        return false;
    else
        return true;
}
vector <vector<int>> function(string value)
{

    vector<string>actions;
    int pos1, pos2;
    vector<int> max;
    bool flag = true;
    while (value.find(')') != -1)
    {
        for (int i = 0; i < value.size(); ++i)
        {
            if (value[i] == '(') {
                pos1 = i;
            }

            if (value[i] == ')')
            {
                actions.push_back(value.substr(pos1, i - pos1 + 1));

                for (int j = 0; j < actions.size(); ++j)
                {
                    pos2 = value.find(actions[j]);
                    if (pos2 != -1)
                    {
                        value.erase(pos2, actions[j].size());

                        value.insert(pos2, to_string(j + 1));
                        i = -1;
                    }
                }
            }
        }
    }

    actions.push_back(value);
    string buff;
    for (int i = 0; i < actions.size(); ++i)
    {
        if (actions[i].find('!') != -1)
        {
            if (actions[i].size() > 4)
            {
                buff = actions[i].substr(actions[i].find('!'), 2);
                actions.emplace(actions.cbegin() + i, buff);
                i++;
            }
        }
    }

    for (int i = 0; i < actions.size(); ++i) {
        if (actions[i].find('(') != -1 || actions[i].find(')') != -1)
        {
            max.push_back(i);
        }
    }

    vector <string> line = { "a","b","c" };
    vector<vector <int>> table = {
        //a b c
         {0,0,0},
         {0,0,1},
         {0,1,0},
         {0,1,1},
         {1,0,0},
         {1,0,1},
         {1,1,0},
         {1,1,1}
    };


    for (int i = 0; i < actions.size(); ++i) {
        int valuetable; vector<int> positionOfActions;
        if (actions[i].size() <= 4) {
            if (actions[i].find('!') != -1) {
                if (actions[i].find('*') == -1) {
                    if (actions[i].find('+') == -1) {
                        string buffer = actions[i];
                        for (int j = 0; j < max.size(); ++j) {
                            if (buffer.find(to_string(j + 1)) != -1)
                            {
                                valuetable = 3 + max[j];

                            }
                        }
                        if (buffer.find('a') != -1)
                            valuetable = 0;
                        if (buffer.find('b') != -1)
                            valuetable = 1;
                        if (buffer.find('c') != -1)
                            valuetable = 2;
                        line.push_back(actions[i]);
                        for (int line = 0; line < table.size(); ++line) {
                            if (table[line][valuetable] == 0)
                                table[line].push_back(table[line][valuetable] + 1);
                            else
                                table[line].push_back(table[line][valuetable] - 1);
                        }
                    }


                }
            }
        }
        else
        {

            for (int j = 0; j < actions[i].size(); ++j) {



                if (actions[i].find("!a") != -1) {
                    positionOfActions.push_back(2 + i);
                    actions[i].erase(actions[i].find("!a"), 2);
                    j = 0;
                }
                if (actions[i].find("!b") != -1) {
                    positionOfActions.push_back(2 + i);
                    actions[i].erase(actions[i].find("!b"), 2);
                    j = 0;
                }
                if (actions[i].find("!c") != -1) {
                    positionOfActions.push_back(2 + i);
                    actions[i].erase(actions[i].find("!c"), 2);
                    j = 0;
                }

            }


            for (int j = 0; j < actions[i].size(); ++j) {



                if (actions[i].find("a") != -1)
                {
                    positionOfActions.push_back(0);
                    actions[i].erase(actions[i].find("a"), 1);
                    j = 0;
                }
                if (actions[i].find("b") != -1)
                {
                    positionOfActions.push_back(1);
                    actions[i].erase(actions[i].find("b"), 1);
                    j = 0;
                }
                if (actions[i].find("c") != -1)
                {
                    positionOfActions.push_back(2);
                    actions[i].erase(actions[i].find("c"), 1);
                    j = 0;
                }



                for (int p = 0; p < max.size(); ++p) {
                    if (actions[i].find(to_string(p + 1)) != -1) {
                        positionOfActions.push_back(3 + max[p]);

                    }
                }
            }

            if (actions[i].find('!') != -1)
            {
                for (int j = 0; j < table.size(); ++j) {
                    for (int h = 0; h < positionOfActions.size(); ++h) {
                        if (table[j][positionOfActions[h]] == 0)
                            table[j].push_back(table[j][valuetable] + 1);
                        else
                            table[j].push_back(table[j][valuetable] - 1);
                    }
                }

            }

            if (actions[i].find('+') != -1)
            {
                for (int j = 0; j < table.size(); ++j) {
                    int iter, summa = 0;
                    for (int k = 0; k < positionOfActions.size(); ++k) {
                        iter = positionOfActions[k];
                        summa = summa + table[j][iter];
                    }
                    if (summa >= 1)
                        table[j].push_back(1);
                    else
                        table[j].push_back(0);
                }
            }

            if (actions[i].find('*') != -1)
            {
                for (int j = 0; j < table.size(); ++j) {
                    int iter, mult = 1;
                    for (int k = 0; k < positionOfActions.size(); ++k) {
                        iter = positionOfActions[k];
                        mult = mult * table[j][iter];
                    }

                    table[j].push_back(mult);


                }
            }
            positionOfActions.clear();


        }


    }

    for (int i = 0; i < table.size(); i++)
    {
        for (int j = 0; j < table[i].size(); j++)
        {
            cout << (table[i][j]) << " ";
            if (j == table[i].size()-1)
            {
                cout << "\n";
            }
        }
    }
    cout << "------------------------------------------------------------------------------------------" << endl;
    return table;
}

string sknf(string value)
{
    return string();
}

int main()
{

    string function1;
    cout << "Enter your function: ";
    cin >> function1;

    if (check(function1) == false)
    {
        cout << "Error: invalid value!" << endl;
        return 0;
    }
    cout << endl;
    cout << " Function - " << function1 << endl;




    vector<vector <int>> table = function(function1);



    vector<string> sdnf;
    vector<string> sknf;
    string buff;
    int maxiteroftable = table[1].size() - 1;

    cout << "sdnf" << endl;

    for (int i = 0; i < table.size(); i++)
    {
        if (table[i][maxiteroftable] == 1)
        {
            buff = "";
            for (int count = 0; count < 3; count++)
            {
                buff += to_string(table[i][count]);

            }
            sdnf.push_back(buff);
        }


    }
    for (int i = 0; i < sdnf.size(); i++)
    {
        for (int j = 0; j < sdnf[i].size(); j++)
        {
            if (sdnf[i][j] == '0')
            {

                cout << "!";

            }
            cout << "x" << j + 1;
        }
        if (i != sdnf.size() - 1)
            cout << " V ";
    }
    cout << endl;
    cout << "------------------------------------------------------------------------------------------" << endl;
    cout << "sknf" << endl;

    for (int i = 0; i < table.size(); i++)
    {
        if (table[i][table[1].size() - 1] == 0)
        {
            buff = "";
            for (int count = 0; count < 3; count++)
            {
                buff += to_string(table[i][count]);

            }
            sknf.push_back(buff);
        }

    }

    for (int i = 0; i < sknf.size(); i++)
    {
        cout << "(";
        for (int j = 0; j < sknf[i].size(); j++)
        {
            if (sknf[i][j] == '1')
            {

                cout << "!";

            }

            cout << "x" << j + 1;
            if (j != sknf[i].size() - 1)
                cout << " V ";
        }
        cout << ")";
    }
    cout << endl;
    cout << "------------------------------------------------------------------------------------------" << endl;
    cout << "SDNF in binary:" << endl;

    for (int i = 0; i < sdnf.size(); i++)
    {
        cout << sdnf[i];
        if(i != sdnf.size()-1)
        {
            cout << "*";
        }
        
        
    }
    
    cout << endl;
    cout << "------------------------------------------------------------------------------------------" << endl;
    cout << "SKNF in binary:" << endl;

    for (int i = 0; i < sknf.size(); i++)
    {
        cout << sknf[i];
        if (i != sknf.size() - 1)
        {
            cout << "+";
        }


    }
    cout << endl;
    cout << "------------------------------------------------------------------------------------------" << endl;
    cout << "SKNF in decimal:";
    for (int i = 0; i < sknf.size(); i++)
    {  
        int answer = 0;
        int pow = 1;
        for (int j = sknf[i].size() - 1; j >= 0; j--)
        {
            if (sknf[i][j] == '1')
            {
                answer += pow;
            }
            pow *= 2;
        }
        cout << answer;
        if (i != sknf.size() - 1)
        {
            cout << ",";
        }

    }
    cout << endl;
    cout << "------------------------------------------------------------------------------------------" << endl;

    cout << "SDNF in decimal:";
    for (int i = 0; i < sdnf.size(); i++)
    {
        int answer = 0;
        int pow = 1;
        for (int j = sdnf[i].size() - 1; j >= 0; j--)
        {
            if (sdnf[i][j] == '1')
            {
                answer += pow;
            }
            pow *= 2;
        }
        cout << answer;
        if (i != sdnf.size() - 1)
        {
            cout << ",";
        }
    }
    cout << endl;
    cout << "------------------------------------------------------------------------------------------" << endl;
    int index = 0;
    for (int i = 0; i < table.size(); i++)
    {
        for (int j = 0; j < table[i].size(); j++)
        {
            if (table[i][j] == 1)
            {
                index++;
            }
        }
    }
    cout << "INDEX = " << index;
    cout << endl;
    cout << "------------------------------------------------------------------------------------------" << endl;

}

//!(((!a)+(!b))*(!((!c)*(!b))))