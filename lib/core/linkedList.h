#include "../header.h"

#pragma once
template <class T>
struct Node
{
    T data;
    Node *link;
};

template <class T>
class LinkedList
{
    private:
        Node<T> *head;
    public:
        LinkedList()
        {
            head = NULL;
        }

        void createAtStart(T value)
        {
            Node<T> *newNode = new Node<T>; 
            newNode->data = value;

            if(head == NULL)
            {
                head = newNode;
                newNode->link = NULL;
            }
            else
            {
                newNode->link = head;
                head = newNode;
                newNode->data = value;
            }
        }

        T deleteAtStart()
        {
            T n;
            if(head == NULL)
            {
                return n;
            }
            else
            {
                Node<T> *temp = new Node<T>;
                temp = head;
                head = temp->link;
                n = temp->data;
                delete temp;
                return n;
            }
        }
};
