#include <stdio.h>
#include <stdlib.h>
#include "person.h"

Person* createPerson(int src, int dest){
    Person* res=malloc(sizeof(Person*));
    res -> src = src;
    res -> dest = dest;
    return res;
}

PersonList* insert(Person *p, PersonList *list){
    PersonList* res= malloc(sizeof(PersonList*));
    res -> person = p;
    res -> next = list;
    return res;
}

PersonList* suppr(PersonList *list){
    if (list != NULL){
        PersonList* res = list -> next;
        free(list);
        return res;
    }
    else {
        return NULL;
    }
}

int taille(PersonList *list){
    if (list == NULL){
        return 0;
    }
    else {
        return taille(list->next)+1;
    }
}