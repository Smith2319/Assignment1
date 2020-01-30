#include <iostream>
#include <string.h>
#include <stdio.h>
#include "main.h"
#include <time.h>

using namespace std;

void newNode(item **head, char *buf){
    item *newitem = (item*)malloc(sizeof(item));
    newitem->name = (char*)malloc(30*sizeof(char));
    strcpy (newitem->name, strtok(buf, ","));
    newitem->minStr = atoi(strtok(NULL, ","));
    newitem->maxStr = atoi(strtok(NULL, ","));
    newitem->rarity = (char*)malloc(15*sizeof(char));
    strcpy(newitem->rarity, strtok(NULL, "\\"));
    newitem->next = (*head);
    newitem->prev = NULL;
    if ((*head) != NULL){
        (*head)->prev = newitem;
    }
    (*head) = newitem;
}


void fillBags(bags **bag, item **head){
    (*bag)->items = NULL;
    for(int i=0; i<25; i++){
        item *temp =  (item*)malloc(sizeof(item));

        temp->name = (char*)malloc(30*sizeof(char));
        strcpy (temp->name, (*head)->name);
        temp->minStr = (*head)->minStr;
        temp->maxStr = (*head)->maxStr;
        (*head)->str = rand() % ((*head)->maxStr - (*head)->minStr) +(*head)->minStr;
        temp->str = (*head)->str;
        temp->rarity = (char*)malloc(15*sizeof(char));
        strcpy (temp->rarity, (*head)->rarity);

        temp->next = (*bag)->items;
        temp->prev = NULL;
        if((*bag)->items != NULL){
            (*bag)->items->prev = temp;
        }
        (*bag)->items = temp;
        
        if((*head)->next == NULL){
            i=25;
        } else {
        (*head) = (*head)->next;
        }
        
    }

}

void randSearch(int b, int n, bags *(bag[30]), item **head){
    while((*head)->prev!=NULL){     //points head back to beginning
        (*head) = (*head)->prev;
        }
    for (int i=0; i<(rand()%n); i++){
        (*head) = (*head)->next;
    }
    printf("looking for %s...\n", (*head)->name);

    for(int i=0; i<b; i++){
        int j = 0;
        while((*bag)->items->prev!=NULL){     //points (*bag) back to beginning
        (*bag)->items = (*bag)->items->prev;
        }
        do{
            if((*bag)->items->prev){
            ((*bag)->items = (*bag)->items->next);
            }
            if (!strcmp((*bag)->items->name, (*head)->name) &&
            (*bag)->items->str == (*head)->str){
                printf("found in bag %i in slot %i\n\n", i+1, j+1);
                i=b;
            }
            if(!(*bag)->items->prev){
            ((*bag)->items = (*bag)->items->next);
            }
            j++;
        } while((*bag)->items->next!=NULL && i<b);
        *bag++;
    }
}

void insertionSort(item** head){    //ask about lower case letters          
    item *search = (item*)malloc(sizeof(item));     //linkedlist to store sorted items
    int comp=1;
    search->prev = NULL;            //sets a stopping point for navigating to beginning of linkedlist
    while((*head)->prev!=NULL){     //points head back to beginning
        (*head) = (*head)->prev;
        }

    while((*head)->next!=NULL){     //goes until head is empty
        search->next = (*head);     //sets next node to compare with
        
        while((*head)->next!=NULL ){
            comp = strcmp((*head)->next->name, search->next->name); //finds lowest name in head
            if (comp<=0){ 
                if(comp || !((*head)->next->str < search->next->str)){  //sorts weapon subgroup by highest damage
                    search->next=(*head)->next;
                }
            }
            (*head)=(*head)->next; 
        }

        if(search->next->next!=NULL){                       // takes lowest name in head out of linked list
            search->next->next->prev = search->next->prev;  //
        }                                                   //
        if(search->next->prev!=NULL){                       //
            search->next->prev->next = search->next->next;  //
        }

        while((*head)->prev!=NULL){                         //points head back to beginning
        (*head) = (*head)->prev;
        }
        search->next->prev = search;                        //adds lowest name in head to new list
        search=search->next;
    }
    
    search->next= (*head);
    (*head)->prev = search;
    while(search->prev!=NULL){
        search = search->prev;
    }
    search->next->prev = NULL;
    search = search->next;
    (*head) = search;
}


main(){

    srand(time(0));
    FILE *file;
    file = fopen("hw1input_items.txt", "r");
    char* buf =(char*) malloc(LINE* sizeof(char)); 
    item *head = NULL;
    int n=0;
    
    fgets(buf, LINE, file);
    while(fgets(buf, LINE, file)){
        newNode(&head, buf);
        n++;
    }

    int b = n/25;
    bags *bag[b];
    for(int i =0; i<(b); i++) {
        bag[i] = (bags*)malloc(sizeof(bags));
        fillBags(&(bag[i]), &head);
        bag[i]->bagn = i+1; 
    }

    //for (int i=0; i <25; i++){
    //    printf("%s\n", bag[2]->items[i]->name);
    //}
    randSearch(b, n, bag, &head);
    randSearch(b, n, bag, &head);

    while(head->prev!=NULL){
        head = head->prev;
    }

    insertionSort(&head);

    for (int i=0; i <n; i++){
        printf("%s  %i\n", head->name, head->str);
        head = head->next;
    }

    free(buf);
 return 0;
}