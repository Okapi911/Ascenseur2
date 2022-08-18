#include <stdio.h>
#include <stdlib.h>
#include "person.h"
#include "elevator.h"

Elevator *create_elevator(int capacity, int currentFloor, PersonList *persons){
    Elevator *res=malloc(sizeof(Elevator));
    res -> capacity = capacity;
    res -> currentFloor = currentFloor;
    res -> targetFloor = currentFloor;
    res -> persons = persons;
    return res; 
}

Building *create_building(int nbFloor, Elevator *elevator, PersonList **waitingLists){
    Building *res = malloc(sizeof(Building));
    res -> nbFloor = nbFloor;
    res -> elevator = elevator;
    res -> waitingLists = waitingLists;
    return res;
}

PersonList* exitElevator(Elevator *e){
    PersonList *res=malloc(sizeof(PersonList));
    PersonList *remaining=malloc(sizeof(PersonList));
    PersonList *rest= e ->persons;
    while (rest != NULL){
        if(rest ->person->dest==e->targetFloor){
            insert(rest ->person, res);
        }
        else {
            insert(rest->person, remaining);
        }
        rest=rest->next;
    }
    e->persons=remaining;
    return res;
}

PersonList*enterElevator(Elevator *e, PersonList *list){
    while ((list != NULL) & (taille(list)<e->capacity)){
        e->persons=insert(list->person,e->persons);
        list=list->next;
    }
    return list;
}

void stepElevator(Building *b){
    if(b->elevator->currentFloor==b->elevator->targetFloor){
        PersonList* res=exitElevator(b->elevator);
        b->waitingLists[b->elevator->currentFloor]=enterElevator(b->elevator, b->waitingLists[b->elevator->currentFloor]);
    }
    else {
        if(b->elevator->currentFloor< b->elevator->targetFloor){
            b->elevator->currentFloor ++;
        }
        else {
            b->elevator->currentFloor --;
        }
    }
}