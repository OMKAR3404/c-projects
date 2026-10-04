#ifndef APC_H
#define APC_H
#include<stdio.h>

typedef struct Node{
    struct Node* prev;
    int data;
    struct Node* next;

}Slist;

typedef enum Status{
    e_success,
    e_failure
}Status;


Status validate_arg(int argc , char**argv);

void insert_at_last(Slist **head ,Slist **tail, int data);

Status add_arg_to_list(char** argv , Slist **head,Slist **Tail,Slist **head2,Slist **Tail2);

void insert_at_first(Slist **Head, Slist **Tail, int data);

Slist* Add(Slist **head,Slist ** head2);

int compare_lists(Slist *tail1, Slist *tail2);

void subtract(Slist **Tail1,Slist **Tail2,Slist **res);

void mult(Slist **Tail1 , Slist ** Tail2,Slist **res);

void display_list(Slist *head);

#endif