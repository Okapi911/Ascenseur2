#include <stdio.h>
#include <stdlib.h>
#include "person.h"

Person* createPerson(int src, int dest){
    Person* res=malloc(sizeof(Person));
    res -> src = src;
    res -> dest = dest;
    return res;
}

PersonList* insert(Person *p, PersonList *list){
    PersonList* res= malloc(sizeof(PersonList));
    res -> person = p;
    res -> next = list;
    return res;
}

int taille(PersonList *list){
    int a = 0;
    while (list != NULL){
        a++;
        list = list->next;
    }
    return a;
}