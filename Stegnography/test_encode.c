#include <stdio.h>
#include "encode.h"
#include"decode.h"
#include "types.h"
#include <string.h>

OperationType check_operation_type(char *argv[]){

    if(strcmp(argv[1], "-e") == 0 ){
        return e_encode ; 
    }else if (strcmp(argv[1], "-d") == 0){
        return e_decode;
    }else{
        return e_unsupported;
    }

}

int main(int argc , char* argv[])
{
    EncodeInfo e1;
    int res = check_operation_type(argv);
     //return 0;
     if(argc > 3 && res == e_encode){
            printf("Encoding is selected \n");

            if(read_and_validate_encode_args(argv,&e1)== e_success){

                printf("INFO : Read and validate encode args is success\n");
                
                if(open_files(&e1) == e_success){

                    printf("INFO : files opened successfully\n");

                    if(do_encoding(&e1) == e_success){

                        printf("INFO : Encoding is success\n");

                    }else{

                        printf("Error : Encoding failed \n");

                        return 0;
                    }

                }else{
                    printf("INFO : file opening failed");
                }
            }else{
                printf("INFO : Read and validate encode args is failure\n");
                return 0;
            }
        }else if(res == e_decode && argc <= 4 ){
            // DEcoding Selected ;
        printf("Info :Decoding is selected \n");
        DecodeInfo d1;
        if(read_and_validate_decode_args(argv,&d1)== e_success){
            printf("INFO : Read and Validate Decode Args is Success\n");
            if(open_decode_files(&d1) == e_success){
                printf("INFO : files open Success\n");

               if(do_decoding(&d1) == e_success){
                    printf("INFO : decoding done\n ");
                }else{
                    printf("Error : decoding failed\n");
                }

            }else{
                printf("Error : failed to open files\n");
            }
        }else{
            printf("INFO : Read and validate encode args is failure\n");
        }

    }else {
        printf("Invalid option\n");
        printf("For Encoding : ./a.out -e beautiful.bmp secret.txt [stegno.bmp]\n");
         printf("For Decoding : ./a.out -d stegno.bmp default.txt\n");
    }
}
