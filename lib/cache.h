#include "header.h"
#include "core/stack.h"
#include "weather.h"

#pragma once

class Cache
{
private:
    Stack<Weather> mainStack ,tmpStack;

public:
    void enter(Weather w)
    {
        mainStack.push(w);
    }
    void remove()
    {
        mainStack.pop();
    }
    Weather search(string value)
    {
        Weather tmp;
        bool isFound = false;

        while(!mainStack.empty())
        {
            tmp = mainStack.pop();
            tmpStack.push(tmp);
            if (tmp.city == value)
            {
                isFound = true;
                break;
            }
        }

        while(!tmpStack.empty())
        {
            mainStack.push(tmpStack.pop());
        }

        if (isFound)
            return tmp;
        else
        {
            Weather tmp;
            return tmp;
        }
    }

    void display()
    {
        Stack<Weather> tmp = mainStack;
        while (!tmp.empty())
        {
            cout << tmp.pop().city << endl;
        }
    }
};