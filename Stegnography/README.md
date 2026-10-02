# BMP Steganography in C

A C programming project implementing image steganography using the **Least Significant Bit (LSB)** technique to hide and extract secret data inside a BMP image.

## 📌 Project Overview

Steganography is the technique of hiding information inside another medium so that the existence of the information is not obvious.

This project:
- Hides a secret text file inside a BMP image.
- Stores secret data in the LSBs of image bytes.
- Extracts the hidden data from the stego image.
- Encodes and decodes a magic string.
- Encodes and decodes the secret file extension and size.
- Preserves the BMP header.

## 🧠 LSB Steganography

LSB stands for **Least Significant Bit**.

For example:

```text
Original image byte : 10110100
Secret bit          :        1
Modified byte       : 10110101
```

Only the least significant bit is changed.

One secret byte contains 8 bits, so **8 image bytes are used to store one secret byte**.

```text
Image Byte 1 → Secret Bit 0
Image Byte 2 → Secret Bit 1
Image Byte 3 → Secret Bit 2
Image Byte 4 → Secret Bit 3
Image Byte 5 → Secret Bit 4
Image Byte 6 → Secret Bit 5
Image Byte 7 → Secret Bit 6
Image Byte 8 → Secret Bit 7
```

## 📦 Data Layout

```text
+---------------------------+
| BMP Header                |
| 54 bytes                  |
+---------------------------+
| Magic String              |
+---------------------------+
| Secret Extension Size     |
| 32 bits                   |
+---------------------------+
| Secret File Extension     |
+---------------------------+
| Secret File Size          |
| 32 bits                   |
+---------------------------+
| Secret File Data          |
+---------------------------+
| Remaining Image Data      |
+---------------------------+
```

## 🔐 Encoding Flow

```text
Input BMP
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
```

## 🔓 Decoding Flow

```text
Stego BMP
    ↓
Validate Arguments
    ↓
Open Files
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
Output Secret File
```

## 🛠️ Important Functions

### Encoding

| Function | Purpose |
|---|---|
| `read_and_validate_encode_args()` | Validates command-line arguments |
| `open_files()` | Opens source, secret and output files |
| `get_image_size_for_bmp()` | Gets BMP image dimensions |
| `check_capacity()` | Checks image capacity |
| `copy_bmp_header()` | Copies the BMP header |
| `encode_magic_string()` | Encodes the magic string |
| `encode_secret_file_extn_size()` | Encodes extension size |
| `encode_secret_file_extn()` | Encodes secret file extension |
| `encode_secret_file_size()` | Encodes secret file size |
| `encode_secret_file_data()` | Encodes secret data |
| `encode_byte_to_lsb()` | Encodes one byte using LSBs |
| `encode_size_to_lsb()` | Encodes a size using LSBs |
| `copy_remaining_img_data()` | Copies remaining image data |

### Decoding

| Function | Purpose |
|---|---|
| `read_and_validate_decode_args()` | Validates decoding arguments |
| `open_decode_files()` | Opens stego and output files |
| `decode_magic_string()` | Extracts and verifies the magic string |
| `decode_data_to_int()` | Decodes 32 bits into an integer |
| `decode_Secret_file_extn_size()` | Decodes extension size |
| `decode_Secret_file_extn()` | Decodes secret file extension |
| `decode_secret_file_size()` | Decodes secret file size |
| `decode_secret_data()` | Extracts secret file data |
| `decode_lsb_to_byte()` | Reconstructs one byte from 8 image bytes |
| `decode_image_to_data()` | Converts image LSBs into data |

## 📁 Project Structure

```text
Stegnography/
├── README.md
├── encode.c
├── encode.h
├── decode.c
├── decode.h
├── common.h
├── types.h
└── test_encode.c
```

## 💻 Technologies Used

- C Programming
- GCC
- Linux / WSL
- File Handling
- Pointers
- Structures
- Bit Manipulation
- Command-Line Arguments
- BMP File Format
- LSB Steganography

## ⚙️ Compilation

```bash
gcc *.c
```

With compiler warnings:

```bash
gcc *.c -Wall -Wextra
```

## ▶️ Usage

### Encode

```bash
./a.out -e source.bmp secret.txt
```

Or specify the output BMP:

```bash
./a.out -e source.bmp secret.txt stego.bmp
```

### Decode

```bash
./a.out -d stego.bmp output.txt
```

## 🧪 Testing

Compare the original and decoded files:

```bash
diff secret.txt output.txt
```

Or:

```bash
cmp secret.txt output.txt
```

If there is no output, the files are identical.

## 📚 Concepts Learned

- Command-line arguments
- File pointers
- `fopen()`
- `fread()`
- `fwrite()`
- `fseek()`
- `ftell()`
- Binary file handling
- Pointers
- Structures
- Arrays
- Strings
- Bitwise operators
- LSB manipulation
- Modular programming
- Header files
- Function prototypes
- Data validation
- File size handling
- BMP file structure
- Encoding and decoding algorithms

## 🔁 Encoding and Decoding Relationship

Encoding and decoding are inverse operations.

### Encoding

```text
Secret Data
    ↓
Convert data into bits
    ↓
Store bits in image LSBs
    ↓
Stego Image
```

### Decoding

```text
Stego Image
    ↓
Read image LSBs
    ↓
Reconstruct bits
    ↓
Secret Data
```

The decoder must follow the same data layout used by the encoder.

## 🚀 Future Improvements

- Support additional secret file extensions.
- Improve argument validation.
- Improve error handling.
- Support larger secret files.
- Avoid large VLAs for large files.
- Add more robust BMP validation.
- Add automated test cases.
- Improve portability using binary file modes.

## ✅ Project Status

| Component | Status |
|---|---|
| BMP Header Handling | ✅ Completed |
| Image Capacity Check | ✅ Completed |
| Magic String Encoding | ✅ Completed |
| Magic String Decoding | ✅ Completed |
| File Extension Encoding | ✅ Completed |
| File Extension Decoding | ✅ Completed |
| File Size Encoding | ✅ Completed |
| File Size Decoding | ✅ Completed |
| Secret Data Encoding | ✅ Completed |
| Secret Data Decoding | ✅ Completed |
| BMP LSB Steganography | ✅ Completed |

## 👨‍💻 Author

**Omkar More**

B.Tech Electrical Engineering

Interests:
- Embedded Systems
- Embedded C
- Automotive Systems
- EV Systems
- Firmware Development

## 📌 Project Purpose

This project was developed to strengthen **Advanced C programming and embedded-systems fundamentals** through hands-on implementation.

It focuses on understanding how data is represented at the **byte and bit level** and how C can be used to manipulate binary files directly.
