#ifndef DECODE_H
#define DECODE_H

#include<stdio.h>
#include"types.h"
  
#define MAX_SECRET_BUF_SIZE 1
#define MAX_IMAGE_BUF_SIZE (MAX_SECRET_BUF_SIZE * 8)
#define MAX_FILE_SUFFIX 4


typedef struct DecodeInfo
{
    /* otput txt file info */
    char *out_fname;
    FILE *fptr_out;
    int Secret_file_extn_size ;
    int Secret_file_size ;
    char extn_input_file[MAX_FILE_SUFFIX];
    char input_data[MAX_SECRET_BUF_SIZE];
    long size_input_file;

    

    /* input bmp File Info */
    char *in_fname;
    FILE *fptr_in;
    char in_image_data[MAX_IMAGE_BUF_SIZE];
    

} DecodeInfo;

Status read_and_validate_decode_args(char *argv[], DecodeInfo *decInfo);

Status open_decode_files(DecodeInfo *decInfoInfo);

Status decode_magic_string(DecodeInfo *decInfo);

Status decode_data_to_int(int*,DecodeInfo*);

Status decode_Secret_file_extn_size(DecodeInfo*);

Status decode_Secret_file_extn(DecodeInfo*);

Status decode_Secret_file_size(DecodeInfo*);

Status decode_Secret_data(DecodeInfo*);

Status decode_lsb_to_byte(char* data,DecodeInfo *decinfo);

Status do_decoding(DecodeInfo *decInfo);









#endif