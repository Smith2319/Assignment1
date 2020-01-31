//Assignment 1 for CS3310
//Written by Adam Smith
//everything works except for the merge function. I was very close, but couldn't iron it out
//before I had to submit it


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
    toupper(*(newitem->name));
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

void randSearch(int b, int n, bags *(bag[]), item **head){
    while((*head)->prev!=NULL){     //points head back to beginning
        (*head) = (*head)->prev;
        }
    for (int i=0; i<(rand()%n); i++){
        (*head) = (*head)->next;
    }
    printf("\nlooking for %s...\n", (*head)->name);

    for(int i=0; i<b; i++){
        int j = 0;
        while((*bag)->items->prev!=NULL){     //points (*bag) back to beginning
        (*bag)->items = (*bag)->items->prev;
        }
        do{
            if((*bag)->items->prev!=NULL){
            ((*bag)->items = (*bag)->items->next);
            }
            if (!strcmp((*bag)->items->name, (*head)->name) &&
            (*bag)->items->str == (*head)->str){
                printf("found in bag %i in slot %i. Strength: %i\n\n", i+1, j+1, (*bag)->items->str);
                i=b;
            }
            if((*bag)->items->prev){
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

void merge(bags *bag, int l, int mid, int r){
    item *bLeft =  (item*)malloc(sizeof(item));
    item *bRight =  (item*)malloc(sizeof(item));
    item *temp;
    bool test = false;
    int n1 = mid-l+1;
    int n2 = r-mid;
if (!test){
    
    while(bag->items->prev!=NULL){
        bag->items= bag->items->prev;
    }
    
    for(int i=0; i<l; i++){
        bag->items= bag->items->next;
    }
    bLeft = bag->items;


    for(int i=0; i<n1; i++){
        bag->items= bag->items->next;
    }
    bRight = bag->items;

    while(n1&&n2){ //fix, not work

    int comp = strcmp(bLeft->name, bRight->name); //finds lowest name in head
            if (comp>=0){ 
                if(comp || !(bLeft->str > bRight->str)){  //sorts weapon subgroup by highest damage
                    if(bRight->next!=NULL){                     //  |   places bRight before bLeft
                        temp = bRight->next;                    //  |
                        bRight->next->prev = bRight->prev;      //  V
                    }                                           //  
                    bRight->prev->next = bRight->next;          //


                    bRight->next = bLeft;
                        bRight->prev = bLeft->prev;
                    if(l){
                        bLeft->prev->next = bRight;
                    }
                    bLeft->prev = bRight;                       //  ^
                    bRight = temp;                              //  |
                    n1--;                                       //  |
                } else {
                    bLeft = bLeft->next;
                    n2--;
                }
            } else {
                bLeft = bLeft->next;
                n2--;
            }
    }

while(bag->items->prev!=NULL){
        bag->items= bag->items->prev;
    }
}

}

void mergeSort(bags *bag, int l, int r){
    if (r>l){
    int mid = (l+r)/2;
        mergeSort(bag, l, mid);
        mergeSort(bag, mid+1, r);
        merge(bag, l, mid, r);
    }
}

void mergeBags(bags *(bag[]), int n, int b){
    item *temp =  (item*)malloc(sizeof(item));
    for (int i=1;i<b; i++){
        while((*bag)->items->next!=NULL){
            (*bag)->items= (*bag)->items->next;
        }
        temp = (*bag)->items;
        *bag++;

        temp->next = (*bag)->items;
        (*bag)->items->prev=temp;
    }
    while((*bag)->items->prev!=NULL){
            (*bag)->items= (*bag)->items->prev;
        }
    mergeSort(*bag, 0, n);
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



    while(head->prev!=NULL){
        head = head->prev;
    }

    insertionSort(&head);

        printf("There are % bags.\nBags before sorting:\n", b);

    for (int i=0; i <b; i++){
        printf("    Bag %i:\n", i);
        for (int j=0; j<25; j++){
            printf("%s, %i\n", bag[i]->items->name, bag[i]->items->str);
            if(bag[i]->items->next!=NULL){
                bag[i]->items = bag[i]->items->next;
            }
        }
    }
    randSearch(b, n, bag, &head);


    for(int i=0; i<b; i++){
        insertionSort(&(bag[i]->items));
    }
        printf("Bags after sorting individually:\n");

    for (int i=0; i <b; i++){
        printf("    Bag %i:\n", i);
        for (int j=0; j<25; j++){
            printf("%s, %i\n", bag[i]->items->name, bag[i]->items->str);
            if(bag[i]->items->next!=NULL){
                bag[i]->items = bag[i]->items->next;
            }
        }
    }

    randSearch(b, n, bag, &head);

    //mergeBags(bag, n, b);

    free(buf);
 return 0;
}