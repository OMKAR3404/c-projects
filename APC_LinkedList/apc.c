#include "apc.h"
#include<string.h>
#include<stdio.h>
#include <stdlib.h>
Status validate_arg(int argc , char** argv){
    if(argc == 4){
        for(int i=0;i<strlen(argv[1]);i++){
            if(!(argv[1][i] >= '0' && argv[1][i] <= '9') == 1){
                printf("Enter valid ARG 1\n");
                return e_failure;
            }
        }

         for(int i=0;i<strlen(argv[3]);i++){
            if(!(argv[3][i] >= '0' && argv[3][i] <= '9') == 1){
                printf("Enter valid ARG 3\n");
                return e_failure;
            }
        }

        if(!(argv[2][0] == '+' || argv[2][0] == '-' || argv[2][0] == '*' || argv[2][0] == '/') == 1 ){
            printf("Enter valid ARG 2\n");
            return e_failure;
        }
        return e_success;

    }else{
        return e_failure;
    }
}


void insert_at_last(Slist **head ,Slist **tail, int data){
    if(*head == NULL){
        Slist *newnode = (Slist*)malloc(sizeof(Slist));
        newnode->data = data;
        *head = newnode;
        *tail = *head;
    }else{
        Slist *newnode = (Slist*)malloc(sizeof(Slist));
        newnode->data = data;
        (*tail)->next = newnode;
        newnode->prev = *tail;
        *tail = newnode;
        (*tail)->next = NULL;
    }
                
}

Status add_arg_to_list(char** argv , Slist **head,Slist **Tail,Slist **head2,Slist **Tail2){

int i=0;

    while(argv[1][i] != '\0'){ 
        insert_at_last(head ,Tail, argv[1][i] -'0');
        i++;
    }

int j=0;

    while(argv[3][j] != '\0'){
        insert_at_last(head2 ,Tail2, argv[3][j] - '0');
        j++;
    }

    return e_success;

}
void insert_at_first(Slist **Head, Slist **Tail, int data)
{
    Slist *newnode = malloc(sizeof(Slist));

    newnode->data = data;
    newnode->prev = NULL;
    newnode->next = *Head;

    if (*Head == NULL)
    {
        *Head = newnode;
        *Tail = newnode;
    }
    else
    {
        (*Head)->prev = newnode;
        *Head = newnode;
    }
}

Slist* Add(Slist **Tail1,Slist **Tail2){

    
    if(*Tail1 == NULL && *Tail2 == NULL){
        printf("Add elemet to list");
        return NULL;
    }else{
        Slist *res = (Slist*)malloc(sizeof(Slist));
        Slist **r_t = &res;
        res = NULL;
        int sum =0,carry = 0;
        while((*Tail1)!= NULL && (*Tail2)!= NULL ){

            sum = (*Tail1)->data + (*Tail2)->data + carry;
            carry = sum / 10;
            sum = sum % 10;
            insert_at_first(&res,r_t,sum);

            (*Tail1) = (*Tail1)->prev;
            (*Tail2) = (*Tail2)->prev;
            
        }
        while ((*Tail1) != NULL)
    {
        sum =(*Tail1)->data + carry;

        carry = sum / 10;
        sum = sum % 10;

        insert_at_first(&res,r_t,sum);

    (*Tail1) =(*Tail1)->prev;
    }

    /* Remaining digits of second number */
    while ((*Tail2) != NULL)
    {
        sum = (*Tail2) ->data + carry;

        carry = sum / 10;
        sum = sum % 10;

        insert_at_first(&res,r_t,sum);

        (*Tail2)  = (*Tail2) ->prev;
    }


         if(carry){
                //sum += carry;
                insert_at_first(&res,r_t,carry);
            }
             return res;

    }

   
    
}

int compare_lists(Slist *tail1, Slist *tail2)
{
    int count1 = 0, count2 = 0;

    Slist *temp1 = tail1;
    Slist *temp2 = tail2;

    // Count digits
    while (temp1 != NULL) {
        count1++;
        temp1 = temp1->prev;
    }

    while (temp2 != NULL) {
        count2++;
        temp2 = temp2->prev;
    }

    // Different number of digits
    if (count1 > count2)
        return 1;

    if (count1 < count2)
        return -1;

    // Same number of digits
    // Move to most significant digit
    temp1 = tail1;
    temp2 = tail2;

    while (temp1 != NULL && temp2 != NULL) {
        if (temp1->data > temp2->data)
            return 1;

        if (temp1->data < temp2->data)
            return -1;

        temp1 = temp1->prev;
        temp2 = temp2->prev;
    }

    return 0;
}
void subtract(Slist **Tail1, Slist **Tail2, Slist **res)
{
    Slist**r_t = res;
    int diff;
    int borrow = 0;
    int sign = 0;

    Slist *t1 = *Tail1;
    Slist *t2 = *Tail2;

    int cmp = compare_lists(t1, t2);

    // Numbers are equal
    if (cmp == 0) {
        insert_at_first(res,r_t, 0);
        return;
    }

    // If Tail2 > Tail1, calculate Tail2 - Tail1
    if (cmp < 0) {
        Slist *temp = t1;
        t1 = t2;
        t2 = temp;

        sign = 1;
    }

    // Subtract while both have digits
    while (t1 != NULL && t2 != NULL) {

        diff = t1->data - t2->data - borrow;

        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        insert_at_first(res,r_t,diff);

        t1 = t1->prev;
        t2 = t2->prev;
    }

    // Remaining digits of larger number
    while (t1 != NULL) {

        diff = t1->data - borrow;

        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        insert_at_first(res,r_t, 0); 

        t1 = t1->prev;
    }

    // Print negative sign if required
    if (sign)
        printf("-");
}

int count_digits(Slist*tail1 , Slist*tail2){

    int count1 = 0, count2 = 0;

    Slist *temp1 = tail1;
    Slist *temp2 = tail2;

    // Count digits
    while (temp1 != NULL) {
        count1++;
        temp1 = temp1->prev;
    }

    while (temp2 != NULL) {
        count2++;
        temp2 = temp2->prev;
    }

    return (count1 > count2) ? count1 : count2;


}

void mult(Slist **Tail1, Slist **Tail2, Slist **res)
{
    Slist *t1 = *Tail1;

    Slist *result = NULL;
    Slist *result_tail = NULL;

    int shift = 0;

    while (t1 != NULL)
    {
        Slist *partial = NULL;
        Slist *partial_tail = NULL;

        Slist *t2 = *Tail2;

        int carry = 0;

        while (t2 != NULL)
        {
            int pro = (t1->data * t2->data) + carry;

            carry = pro / 10;

            insert_at_first(&partial, &partial_tail, pro % 10);

            t2 = t2->prev;
        }

        if (carry)
        {
            insert_at_first(&partial, &partial_tail, carry);
        }

        /* Add zeros for shifting */
        for (int i = 0; i < shift; i++)
        {
            insert_at_last(&partial, &partial_tail, 0);
        }

        /* First partial product */
        if (result == NULL)
        {
            result = partial;
        }
        else
        {
            Slist *partial_tail_temp = partial_tail;

            result_tail = result;

            while (result_tail->next != NULL)
            {
                result_tail = result_tail->next;
            }

            result = Add(&result_tail, &partial_tail_temp);
        }

        shift++;
        t1 = t1->prev;
    }

    *res = result;
}







void display_list(Slist *head)
{
    Slist *temp = head;

    while (temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }

    printf("\n");
}

