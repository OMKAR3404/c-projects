#include"decode.h"
#include<stdio.h>
#include"types.h"
#include <string.h>
#include"common.h"


Status read_and_validate_decode_args(char *argv[], DecodeInfo *decInfo){
    // input files   
    if(strstr(argv[2],".bmp") !=  NULL){
       decInfo->in_fname = argv[2];
    }else{
        printf("1");
        return e_failure;
    }
    // secret.txt file
    if(strstr(argv[3],".txt") != NULL){
        decInfo->out_fname = argv[3];
    }
    else{
        printf("2");
        decInfo->out_fname = "output.txt";
        return e_success;
    }
return e_success;
}

Status open_decode_files(DecodeInfo *decInfo)
{
    // input Image file
    decInfo->fptr_in = fopen(decInfo->in_fname, "r");
    // Do Error handling
    if (decInfo->fptr_in == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", decInfo->in_fname);
    	return e_failure;
    }

    // output file
    decInfo->fptr_out = fopen(decInfo->out_fname, "w");
    // Do Error handling
    if (decInfo->fptr_out == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", decInfo->out_fname);

    	return e_failure;
    }

    // No failure return e_success
    return e_success;
}

Status decode_data_to_int(int* size ,DecodeInfo *decInfo){
    char str[32];
    fread(str , 32 , 1 , decInfo->fptr_in);
    for(int i=0;i<32;i++){
        *size |= ((str[i] & 0x01)<<i);
        }
        return e_success;
}

//Status decode_Secret_file_extn_size();







Status decode_lsb_to_byte(char *data ,DecodeInfo *decInfo){
    *data = 0;
    for(int i=0;i<8;i++){
        *data = *data | ((decInfo->in_image_data[i] & 1) << i);
        // image_buffer[i] =  (image_buffer[i] & 0xFE ) | ((data>>i) & (1));
    }

    return e_success;
}



char* decode_image_to_data(char* data , int size,DecodeInfo *decInfo){
    
    for(int i=0;i<size;i++){
        fread(decInfo->in_image_data,8,1,decInfo->fptr_in);
        decode_lsb_to_byte(&data[i],decInfo);
       
    }
    //printf("%s\n",data);
    return data;
}

Status decode_Secret_file_extn(DecodeInfo *decInfo){
    char extn[decInfo->Secret_file_extn_size+1];
        decode_image_to_data(extn,decInfo->Secret_file_extn_size,decInfo);
    extn[decInfo->Secret_file_extn_size] = '\0' ;

    printf("%s\n",extn);
    if(strcmp(".txt",extn) == 0){
        return e_success;
    }return e_failure;
}

Status decode_magic_string(DecodeInfo *decInfo){
    char magic[strlen(MAGIC_STRING)+1];
    fseek(decInfo->fptr_in , 54 , SEEK_SET);
    decode_image_to_data(magic, strlen(MAGIC_STRING), decInfo);
    magic[strlen(MAGIC_STRING)] = '\0' ;
    if(strcmp(magic, MAGIC_STRING) == 0)
    {
        return e_success;
    }
    return e_failure;
}

Status decode_Secret_file_extn_size(DecodeInfo *decInfo){
    decInfo->Secret_file_extn_size = 0;
    decode_data_to_int(&decInfo->Secret_file_extn_size,decInfo);
    //printf("%d\n", decInfo->Secret_file_extn_size);
    return e_success;
    
}

Status decode_secret_file_size(DecodeInfo *decInfo){
    decInfo->Secret_file_size = 0;
    decode_data_to_int(&decInfo->Secret_file_size , decInfo);
    printf("%d",decInfo->Secret_file_size);
    return e_success;
}

Status decode_secret_data(DecodeInfo *decInfo){
    char Secrt_data[decInfo->Secret_file_size];
    //fseek(decInfo->fptr_in , 54 , SEEK_SET);
    decode_image_to_data(Secrt_data, decInfo->Secret_file_size-1, decInfo);
    Secrt_data[decInfo->Secret_file_size] = '\0' ;
    if(sizeof(Secrt_data) == decInfo->Secret_file_size){
        fwrite(Secrt_data,1,decInfo->Secret_file_size-1,decInfo->fptr_out);
        return e_success;
    }else{
        return e_failure;
    }
}
Status do_decoding(DecodeInfo *decInfo){
    if(decode_magic_string(decInfo) == e_success){
        printf("INFO : Magic String decoding successed\n");
            if(decode_Secret_file_extn_size(decInfo) == e_success){
                printf("INFO : Secret file Extn size  decoding SUCCESSED\n");
                    if(decode_Secret_file_extn(decInfo)== e_success){
                    printf("INFO : Secret file Extn decoding SUCCESSED\n");
                        if(decode_secret_file_size(decInfo) == e_success){
                            printf("INFO : Secret file size decoding SUCCESSED\n"); 
                                if(decode_secret_data(decInfo)){
                                    printf("INFO : Secret file decoding SUCCESSED\n");
                                    return e_success;
                    }
                
            }else{
                printf("ERROR : Failed decoding secrret file EXT \n");
                return e_failure;

            }
        }else{
            printf("ERROR : Failed decoding secrret file EXT SIZE\n");
            return e_failure;
        }
    }else{
        printf("Error : Magic String decoding failed\n");
        return e_failure;
    }
}
}
