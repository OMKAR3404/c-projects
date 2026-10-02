#include <stdio.h>
#include "encode.h"
#include "types.h"
#include <string.h>
#include "common.h"


/* Function Definitions */

/* Get image size
 * Input: Image file ptr
 * Output: width * height * bytes per pixel (3 in our case)
 * Description: In BMP Image, width is stored in offset 18,
 * and height after that. size is 4 bytes
 */
uint get_image_size_for_bmp(FILE *fptr_image)
{
    uint width, height;
    // Seek to 18th byte
    fseek(fptr_image, 18, SEEK_SET);

    // Read the width (an int)
    fread(&width, sizeof(int), 1, fptr_image);
    printf("width = %u\n", width);

    // Read the height (an int)
    fread(&height, sizeof(int), 1, fptr_image);
    printf("height = %u\n", height);

    // Return image capacity
    return width * height * 3;
}

/* 
 * Get File pointers for i/p and o/p files
 * Inputs: Src Image file, Secret file and
 * Stego Image file
 * Output: FILE pointer for above files
 * Return Value: e_success or e_failure, on file errors
 */
Status open_files(EncodeInfo *encInfo)
{
    // Src Image file
    encInfo->fptr_src_image = fopen(encInfo->src_image_fname, "r");
    // Do Error handling
    if (encInfo->fptr_src_image == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->src_image_fname);
    	return e_failure;
    }

    // Secret file
    encInfo->fptr_secret = fopen(encInfo->secret_fname, "r");
    // Do Error handling
    if (encInfo->fptr_secret == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->secret_fname);

    	return e_failure;
    }

    // Stego Image file
    encInfo->fptr_stego_image = fopen(encInfo->stego_image_fname, "w");
    // Do Error handling
    if (encInfo->fptr_stego_image == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->stego_image_fname);
    	return e_failure;
    }

    // No failure return e_success
    return e_success;
}


Status read_and_validate_encode_args(char *argv[], EncodeInfo *encInfo){
    // input files 
    if(strstr(argv[2],".bmp") !=  NULL){
        encInfo->src_image_fname = argv[2];
    }else{
        //printf("1");
        return e_failure;
    }
    // secret.txt file
    if(strstr(argv[3],".txt") != NULL){
        encInfo->secret_fname = argv[3];
    }else{
       // printf("2");
        return e_failure;
    }
    
    if(argv[4] != NULL){
    if(strstr(argv[4],".bmp") != NULL){
       // printf("3");
        encInfo->stego_image_fname = argv[4];
        }
    }
    else{
        //printf("4");
        encInfo->stego_image_fname = "default.bmp";
    }
return e_success;
}

uint get_file_size(FILE *fptr){
    fseek(fptr,0,SEEK_END);
    return ftell(fptr);
}

Status check_capacity(EncodeInfo *encInfo){

    encInfo->image_capacity = get_image_size_for_bmp(encInfo -> fptr_src_image);
    encInfo->size_secret_file = get_file_size(encInfo->fptr_secret);
    if(encInfo->image_capacity > 16+32+32+encInfo->size_secret_file*8){
        return e_success;
    }else{
        return e_failure;
    }
}

Status copy_bmp_header(FILE *fptr_src_image, FILE *fptr_dest_image){
    // read 54 bytes from source image ;
    char buffer[54];
    rewind(fptr_src_image);
    fread(buffer , 54 , 1 , fptr_src_image);
    //write 54 bytes to dest file/image;
    fwrite(buffer,54,1,fptr_dest_image);

    return e_success;
}

Status encode_byte_to_lsb(char data, char *image_buffer){
      for(int i=0;i<8;i++){
        image_buffer[i] =  (image_buffer[i] & 0xFE ) | ((data>>i) & (1));
      }
      return e_success;
}


Status encode_data_to_image(char *data, int size, EncodeInfo *encInfo){
    //read 8 byte data

    for(int i=0;i<size;i++){
    fread(encInfo->image_data , 8 ,1 , encInfo->fptr_src_image);
    // byte to lsb ;
    encode_byte_to_lsb(data[i],encInfo->image_data);
    //write encoded data to output ;
    fwrite(encInfo->image_data,8,1,encInfo->fptr_stego_image);
    }
}

Status encode_magic_string(const char *magic_string, EncodeInfo *encInfo){
    encode_data_to_image(MAGIC_STRING , strlen(MAGIC_STRING) , encInfo);
    return e_success;
}

Status encode_size_to_lsb(int size,EncodeInfo *encInfo){
    char str[32];
    fread(str , 32 , 1 , encInfo->fptr_src_image);
    
    for(int i=0;i<32;i++){
        str[i] = (str[i] & 0xFE) | ((size>>i)&1);
    }
    
    fwrite(str,32,1,encInfo->fptr_stego_image);
}
Status encode_secret_file_extn_size(int size, EncodeInfo *encInfo){
    encode_size_to_lsb(size,encInfo);
    return e_success;
}
Status encode_secret_file_extn(const char *file_extn, EncodeInfo *encInfo){
     encode_data_to_image(encInfo->extn_secret_file , strlen(encInfo->extn_secret_file) , encInfo);
    return e_success;
}

Status encode_secret_file_size(long file_size, EncodeInfo *encInfo){
    encode_size_to_lsb(file_size,encInfo);
    return e_success;
}

Status encode_secret_file_data(EncodeInfo *encInfo){
    char data[encInfo->size_secret_file];
    rewind(encInfo->fptr_secret);
    fgets(data,encInfo->size_secret_file,encInfo->fptr_secret);
    encode_data_to_image(data ,encInfo->size_secret_file, encInfo);
    return e_success;
}

/*Status copy_remaining_img_data(FILE *fptr_src, FILE *fptr_dest){
    char data[MAX_IMAGE_BUF_SIZE];
    size_t bytes_read;

    while ((bytes_read = fread(data, 1, MAX_IMAGE_BUF_SIZE, fptr_src)) > 0)
    {
        fwrite(data, 1, bytes_read, fptr_dest);
    }

    return e_success;
}*/


Status copy_remaining_img_data(FILE *fptr_src, FILE *fptr_dest,EncodeInfo *encInfo){
    
    int size = 54 + encInfo->image_capacity - ftell(fptr_src);
    char data[size];

    fread(data,size,1,fptr_src);
    fwrite(data,size,1,fptr_dest);

    return e_success;
}

Status do_encoding(EncodeInfo *encInfo){
    if (check_capacity(encInfo) == e_success){
        printf("INFO : Check capacity is success\n");
        if(copy_bmp_header(encInfo->fptr_src_image , encInfo->fptr_stego_image) == e_success){
            printf("INFO : Copied bmp header successfully\n");
            if(encode_magic_string(MAGIC_STRING,encInfo) == e_success){
                printf("INFO : Magic String encodded Successfully \n");

                strcpy(encInfo->extn_secret_file,strstr(encInfo->secret_fname , "."));
                if(encode_secret_file_extn_size( strlen(encInfo->extn_secret_file) , encInfo ) == e_success){
                    printf("INFO : encoded secret file extension size\n");
                   // printf("%s %d",encInfo->extn_secret_file,strlen(encInfo->extn_secret_file));
                   if(encode_secret_file_extn(encInfo->extn_secret_file , encInfo) == e_success){
                    printf("INFO : Encoded secretfile extension\n");
                    if(encode_secret_file_size(encInfo->size_secret_file,encInfo) == e_success){
                        printf("INFO : Encoded secret file size\n");
                        if(encode_secret_file_data(encInfo) == e_success){
                            printf("INFO : Encoded secret file data\n");
                            copy_remaining_img_data(encInfo->fptr_src_image,encInfo->fptr_stego_image,encInfo);


                        }else{
                            printf("Error : Failed to Encode Secret file data ");
                            return e_failure;
                        }
                    }else{
                        printf("Error : Failed to encode secret file size\n"); 
                        return e_failure;                   
                    }
                   }else{
                    printf("Error : Failed encoding secretfile extension\n");
                    return e_failure;
                   
                   }

                }else{
                    printf("Error : failed to encode secret filr extension size\n");
                    return e_failure;
                }



            }
        else{
            printf("INFO : magic string encoding failed\n");
            return e_failure;
        }
             


        }else{
            printf("INFO : bmp header copy failed\n");
            return e_failure;
        }
    }else{
        printf("Error : Secret data cannot br fit in given image\n");
        return e_failure;
    }
    
    return e_success;
}

