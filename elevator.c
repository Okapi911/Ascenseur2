#include <stdio.h>
#include <stdlib.h>
#include "person.h"
#include "elevator.h"

Elevator *create_elevator(int capacity, int currentFloor, PersonList *persons){
    Elevator *res=malloc(sizeof(Elevator*));
    res -> capacity = capacity;
    res -> currentFloor = currentFloor;
    res -> targetFloor = currentFloor;
    res -> persons = persons;
    return res; 
}

Building *create_building(int nbFloor, Elevator *elevator, PersonList **waitingLists){
    Building *res = malloc(sizeof(Building*));
    res -> nbFloor = nbFloor;
    res -> elevator = elevator;
    res -> waitingLists = waitingLists;
    return res;
}

PersonList* exitElevator(Elevator *e){
    PersonList *res=malloc(sizeof(PersonList*));
    if (e->persons != NULL){
        if(e->persons->next!=NULL){
            if(e->persons->next->next != NULL){
                if (e->persons->next->next->person->dest == e->currentFloor){
                    res = insert(e->persons->next->next->person, res);
                    e->persons->next->next = suppr(e->persons->next->next);
                }
            }
            if (e->persons->next->person->dest == e->currentFloor){
                res = insert(e->persons->next->person, res);
                e->persons->next = suppr(e->persons->next);
            }
        }
        if (e->persons->person->dest==e->currentFloor){
            res = insert(e->persons->person, res);
            e->persons = suppr(e->persons);
        }
    }
    
    return res;
}

PersonList*enterElevator(Elevator *e, PersonList *list){
    while ((list != NULL) & (taille(e->persons)<e->capacity)){
        e->persons = insert(list->person,e->persons);
        list = list->next;
    }
    return list;
}

void stepElevator(Building *b){
    if(b->elevator->currentFloor==b->elevator->targetFloor){
        if(b->elevator->persons != NULL){
            exitElevator(b->elevator); 
        }
        if(b->waitingLists(b->elevator->currentFloor) != NULL){
            b->waitingLists(b->elevator->currentFloor) = enterElevator(b->elevator,b->waitingLists(b->elevator->currentFloor));
        }    
    }
    else {
        if(b->elevator->currentFloor< b->elevator->targetFloor){
            b->elevator->currentFloor =(b->elevator->currentFloor+1)%(b->nbFloor);
        }
        else {
            b->elevator->currentFloor =(b->elevator->currentFloor-1)%(b->nbFloor);
        }
    }
}