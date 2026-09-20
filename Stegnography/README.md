C Projects

A collection of C programming projects focused on low-level programming,
file handling, bit manipulation, data structures, and embedded-systems
fundamentals.

Projects

BMP Steganography

A C-based image steganography project that hides secret file data inside
a BMP image using Least Significant Bit (LSB) encoding.

The project demonstrates how image bytes can be modified at the bit
level to store information while preserving the visual appearance of the
image.

Encoding Flow

                    BMP Image
                        |
                        v
              +-------------------+
              | Copy BMP Header   |
              +-------------------+
                        |
                        v
              +-------------------+
              | Encode Magic      |
              | String             |
              +-------------------+
                        |
                        v
              +-------------------+
              | Encode Secret     |
              | Extension Size    |
              +-------------------+
                        |
                        v
              +-------------------+
              | Encode Secret     |
              | File Extension    |
              +-------------------+
                        |
                        v
              +-------------------+
              | Encode Secret     |
              | File Size         |
              +-------------------+
                        |
                        v
              +-------------------+
              | Encode Secret     |
              | File Data         |
              +-------------------+
                        |
                        v
              +-------------------+
              | Copy Remaining    |
              | Image Data        |
              +-------------------+
                        |
                        v
                   Stego BMP

How LSB Encoding Works

Each character of the secret data is represented using 8 bits.

For every bit of the secret character, the least significant bit of one
image byte is modified.

For example:

Image byte:       10110110
Secret bit:              1
                         |
                         v
Encoded byte:     10110111

Only the least significant bit is changed, which keeps the visual
difference in the image extremely small.

Features

BMP image file handling

LSB-based data encoding

Magic string encoding

Secret file extension encoding

Secret file size encoding

Secret file data encoding

BMP header preservation

Image capacity validation

Binary file operations

Modular C implementation

Technologies & Concepts

C Programming

GCC

Linux / WSL

File I/O

Pointers

Structures

Bit Manipulation

String Handling

Memory Management

Git & GitHub

Project Structure

c-projects/
│
├── README.md
│
└── Steganography/
    ├── encode.c
    ├── encode.h
    ├── common.h
    ├── types.h
    └── test_encode.c

Build

Compile the project using GCC:

gcc encode.c test_encode.c -o steganography

Run:

./steganography

The exact compilation command may depend on the final project
structure and the source files included in the project.

Learning Objectives

This project is part of my ongoing C programming and embedded-systems
learning journey.

Through this project, I am strengthening my understanding of:

Binary file handling

Bit-level operations

Pointers and arrays

Structures

Function modularity

File pointers and file positions

Memory handling

Debugging in C

Linux development

Git and GitHub workflow

Future Improvements

Implement the decoding functionality

Improve command-line argument validation

Improve error handling

Add support for more image formats

Improve memory management

Support larger secret files

Add automated tests

Document the decoding algorithm

Author

Omkar More

Electrical Engineering | Embedded Systems | C Programming

GitHub: OMKAR3404
