#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#include"apc.h"
#include <stdlib.h>
int main(int argc ,char* argv[] ){

    if(validate_arg(argc , argv)== e_success){
        printf("INFO : Validation Succesed\n");
        Slist *Head1 = NULL, *Tail1 = NULL ;
        Slist *Head2 = NULL ,*Tail2 = NULL;
        Slist *res = NULL;
        //printf("1\n");
        if(add_arg_to_list(argv,&Head1,&Tail1,&Head2,&Tail2)== e_success){
            printf("INFO  added to list\n");
            display_list(Head1);
            display_list(Head2);

            if(*argv[2] == '+'){
            Slist* r = Add(&Tail1,&Tail2);
            display_list(r);
        }else if(*argv[2] == '-'){
            subtract(&Tail1,&Tail2,&res);
            display_list(res);
        }else if(*argv[2] == '*'){
            mult(&Tail1,&Tail2,&res);
            display_list(res);
        }
            
            //printf("tail %p ",*(s1->next));

            
        }else{
            printf("Failed to add in list");
            return 0;
        }
    }else{
        printf("Failed to Validate");
        return 0;
    }
   
}