#include <iostream>
using namespace std;

#pragma once

#define SIMPLE 1
#define PASSWORD 2

void input(char var[], size_t size, int mode)
{
    int index = 0;
    char ch = '\0';

     while (ch != '\r' && index < size-1)
    {
        ch = getch();
        if (ch != '\r' && ch != '\b')
        {
            var[index] = ch;
            if (mode == PASSWORD)
                cout << "*";
            else if (mode == SIMPLE)
                cout << ( (ch == '\t')? ' ' : ch );
            index++;
        }
        else if (ch == '\b' && index > 0)
        {
            cout << "\b_\b";
            index--;
        }
    }
    var[index] = 0;
    cout << endl;
}
