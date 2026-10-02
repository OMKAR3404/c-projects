BMP Steganography in C

A C-based BMP image steganography project that hides secret file data inside a BMP image using Least Significant Bit (LSB) manipulation.

The project implements both encoding and decoding of secret data.

📌 Project Overview

Steganography is the technique of hiding information inside another medium so that the existence of the hidden information is not obvious.

In this project, secret data is hidden inside a BMP image by modifying the Least Significant Bits of the image data.

The BMP image is used as the carrier, while the secret file is embedded into the image.

Basic Concept
Secret File
     ↓
Convert data into bits
     ↓
Store bits in image LSBs
     ↓
Stego BMP Image

During decoding:

Stego BMP Image
     ↓
Extract LSBs
     ↓
Reconstruct secret bytes
     ↓
Original Secret File
🚀 Features
Encoding
Validate command-line arguments
Open source BMP image
Open secret file
Check image capacity
Copy BMP header
Encode magic string
Encode secret file extension size
Encode secret file extension
Encode secret file size
Encode secret file data
Copy remaining image data
Generate stego BMP image
Decoding
Validate command-line arguments
Open stego BMP image
Open output file
Skip BMP header
Decode and validate magic string
Decode secret file extension size
Decode secret file extension
Decode secret file size
Decode secret file data
Write decoded data to output file
🧠 LSB Steganography

The project uses the Least Significant Bit (LSB) of image bytes to store secret information.

For example:

Original Image Byte

10110110
       ↑
      LSB

If the secret bit is 1, the image byte can become:

10110111

Only the least significant bit changes.

🔐 Encoding One Byte

One secret byte contains 8 bits.

For example:

Secret Byte

01000001

The 8 bits are stored in the LSBs of 8 image bytes.

Secret Bit       Image Byte LSB

    0        →       LSB of byte 1
    1        →       LSB of byte 2
    0        →       LSB of byte 3
    0        →       LSB of byte 4
    0        →       LSB of byte 5
    0        →       LSB of byte 6
    1        →       LSB of byte 7
    0        →       LSB of byte 8
🔓 Decoding One Byte

The decoding process reverses the encoding process.

8 Image Bytes
      ↓
Extract LSB from each byte
      ↓
Reconstruct 8 bits
      ↓
Original Secret Byte
📦 Data Stored Inside the BMP

The project stores hidden information in the following order:

BMP Header
     ↓
Magic String
     ↓
Secret File Extension Size
     ↓
Secret File Extension
     ↓
Secret File Size
     ↓
Secret File Data
     ↓
Remaining Image Data

The decoder follows the same sequence to recover the hidden data.

🔄 Encoding Flow
Source BMP
    ↓
Validate Arguments
    ↓
Open Files
    ↓
Check Image Capacity
    ↓
Copy BMP Header
    ↓
Encode Magic String
    ↓
Encode Secret File Extension Size
    ↓
Encode Secret File Extension
    ↓
Encode Secret File Size
    ↓
Encode Secret File Data
    ↓
Copy Remaining Image Data
    ↓
Stego BMP
🔓 Decoding Flow
Stego BMP
    ↓
Validate Arguments
    ↓
Open Files
    ↓
Skip BMP Header
    ↓
Decode Magic String
    ↓
Decode Secret File Extension Size
    ↓
Decode Secret File Extension
    ↓
Decode Secret File Size
    ↓
Decode Secret File Data
    ↓
Write Output File
🧩 Important Functions
Encoding Functions
read_and_validate_encode_args()

Validates the command-line arguments used for encoding.

open_files()

Opens:

Source BMP
Secret file
Stego BMP
check_capacity()

Checks whether the BMP image has enough capacity to store the secret data.

copy_bmp_header()

Copies the BMP header from the source image to the stego image.

encode_magic_string()

Stores the predefined magic string inside the image.

The magic string is later used during decoding to verify that the BMP contains encoded data.

encode_byte_to_lsb()

Stores one byte of secret data into the LSBs of 8 image bytes.

encode_size_to_lsb()

Stores a size value using the LSBs of 32 image bytes.

encode_secret_data()

Reads secret file data and embeds it into the image.

copy_remaining_img_data()

Copies the remaining image data after the secret information has been encoded.

🔍 Decoding Functions
decode_magic_string()

Starts decoding after the BMP header and extracts the magic string.

The decoded magic string is compared with the expected magic string.

Decoded Magic String
        ↓
Compare
        ↓
MATCH → Continue decoding
NO MATCH → Decoding fails
decode_lsb_to_byte()

Extracts 8 LSBs from 8 image bytes and reconstructs one byte.

Image Byte 0 LSB → Bit 0
Image Byte 1 LSB → Bit 1
Image Byte 2 LSB → Bit 2
...
Image Byte 7 LSB → Bit 7
decode_image_to_data()

Repeatedly reads 8 image bytes and reconstructs secret data one byte at a time.

8 image bytes → 1 decoded byte
8 image bytes → 1 decoded byte
8 image bytes → 1 decoded byte
...
decode_data_to_int()

Extracts 32 LSBs from 32 image bytes and reconstructs an integer.

This is used for:

Secret file extension size
Secret file size
decode_Secret_file_extn_size()

Decodes the size of the secret file extension.

decode_Secret_file_extn()

Decodes the secret file extension using the previously decoded extension size.

Example:

4
↓
.txt
decode_secret_file_size()

Decodes the size of the secret file.

decode_secret_data()

Decodes the exact number of bytes specified by the secret file size and writes them to the output file.

📁 Project Structure
Stegnography/
│
├── encode.c
├── encode.h
│
├── decode.c
├── decode.h
│
├── common.h
├── types.h
│
├── test_encode.c
│
└── README.md
🛠️ Technologies Used
C Programming
GCC
Linux
File Handling
Binary File Processing
Bitwise Operators
Structures
Pointers
Command-Line Arguments
BMP File Format
LSB Steganography
💻 Compilation

Compile all C files:

gcc *.c

Compile with compiler warnings:

gcc *.c -Wall -Wextra
🔐 Encoding

Basic command:

./a.out -e source.bmp secret.txt

This creates:

default.bmp

You can also specify the output BMP:

./a.out -e source.bmp secret.txt stego.bmp
🔓 Decoding

Decode the hidden file:

./a.out -d stego.bmp output.txt

The recovered secret data is written to:

output.txt
🧪 Testing

After encoding and decoding, compare the original secret file with the decoded file.

diff secret.txt output.txt

If there is no output from diff, the files contain identical data.

You can also use:

cmp secret.txt output.txt
📊 Complete Example
Step 1 — Encode
./a.out -e beautiful.bmp secret.txt stego.bmp
beautiful.bmp
      +
secret.txt
      ↓
   Encoder
      ↓
stego.bmp
Step 2 — Decode
./a.out -d stego.bmp output.txt
stego.bmp
    ↓
 Decoder
    ↓
output.txt
Step 3 — Verify
diff secret.txt output.txt

No output means the decoded file matches the original file.

🧠 Concepts Learned

This project helped practice several important C programming concepts:

Structures
Pointers
Pointer-to-structure
Character arrays
Strings
Command-line arguments
File pointers
fopen()
fread()
fwrite()
fseek()
ftell()
File modes
Bitwise AND
Bitwise OR
Bit shifting
LSB manipulation
Binary file handling
Modular programming
Function prototypes
Header files
Error handling
Encoding and decoding algorithms
📌 Key Learning

The most important concept learned from this project is that encoding and decoding are inverse operations.

Encoding
Secret Bit
    ↓
Image LSB
Decoding
Image LSB
    ↓
Secret Bit

Similarly:

8 secret bits
     ↓
8 image bytes

During decoding:

8 image bytes
     ↓
8 secret bits
     ↓
1 secret byte

Understanding this relationship makes it possible to design the decoder directly from the encoder's data layout.

🚧 Future Improvements

Possible improvements for the project:

Support more secret file types
Improve BMP validation
Support larger secret files
Use dynamic memory allocation for large files
Decode data in chunks instead of storing the complete secret file on the stack
Improve error handling
Validate fread() and fwrite() return values
Use binary file modes (rb / wb)
Improve command-line argument validation
Add more test cases
Add support for different BMP formats
👨‍💻 Author

Omkar More

C Programming | Embedded Systems | Automotive & EV Enthusiast

⭐ Project Status
Component	Status
Encoding	✅ Completed
Decoding	✅ Completed
Magic String	✅ Implemented
Extension Encoding	✅ Implemented
Extension Decoding	✅ Implemented
File Size Encoding	✅ Implemented
File Size Decoding	✅ Implemented
Secret Data Encoding	✅ Implemented
Secret Data Decoding	✅ Implemented
BMP LSB Steganography	✅ Implemented