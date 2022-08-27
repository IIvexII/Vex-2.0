#include "linkedList.h"

template <class T>
class Stack
{
    private:
        int top;
        LinkedList<T> list;

    public:
        Stack()
        {
            top = -1;
        }

        bool empty()
        {
            if(top==-1)
                return true;
            else 
                return false;
        }

        void push(T value)
        {
            top++;
            list.createAtStart(value);
        }

        T pop()
        {
            top--;
            return list.deleteAtStart();
        }
};