#ifndef LASER_H_INCLUDED
#define LASER_H_INCLUDED
#include <iostream>
#include<stdlib.h>
#include<SFML/Graphics.hpp>

//this is basic queue linked list stuff, DS class YAY
using namespace std;
struct node {
   sf::Vector2f data;
   struct node *next;
};
class Laser{
public:
    struct node* front = NULL;
    struct node* rear = NULL;
    struct node* temp;
    void Insert(sf::Vector2f x) {

        if (rear == NULL) {
            rear = (struct node *)malloc(sizeof(struct node));
            rear->next = NULL;
            rear->data = x;
            front = rear;
        }     else {
            temp=(struct node *)malloc(sizeof(struct node));
            rear->next = temp;
            temp->data = x;
            temp->next = NULL;
            rear = temp;
            }
    }
    void Delete() {

        if (front == NULL) {
                return;
        }
        else
            if (temp->next != NULL) {
                temp = temp->next;
                free(front);
                front = temp;
            } else {
                free(front);
            front = NULL;
            rear = NULL;
            }
        }
    void DeleteAll()
    {
        while(rear!=NULL)
        {
            temp = front;
            if (front == NULL) {
                    return;
            }
            else
            {
                if (temp->next != NULL) {
                    temp = temp->next;
                    free(front);
                    front = temp;
                } else {
                    free(front);
                    front = NULL;
                    rear = NULL;
                    }
            }
        }
    }
};
#endif // LASER_H_INCLUDED
