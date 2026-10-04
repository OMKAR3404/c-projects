# Arbitrary Precision Calculator using Doubly Linked List

## 📌 Overview

This project implements an **Arbitrary Precision Calculator (APC)** in C using a **Doubly Linked List**.

The calculator performs arithmetic operations on integers that may exceed the limits of standard C data types such as `int`, `long`, and `long long`.

Each digit of the number is stored as a separate node in a doubly linked list.

---

## 🎯 Objectives

- Implement arithmetic operations on large integers.
- Understand and implement Doubly Linked Lists.
- Practice pointers and double pointers.
- Understand dynamic memory allocation.
- Implement carry and borrow handling.
- Use Command Line Arguments in C.
- Develop a modular C project.

---

## 🛠️ Technologies Used

- **Language:** C
- **Data Structure:** Doubly Linked List
- **Compiler:** GCC
- **Environment:** Linux / WSL
- **Version Control:** Git & GitHub

---

## 📂 Project Structure

```text
APC_LinkedList/
│
├── main.c
├── add.c
├── subtract.c
├── multiplication.c
├── division.c
├── apc.h
├── types.h
└── README.md
```

> File names may vary depending on the current implementation.

---

# 💻 Command Line Arguments

The APC calculator accepts input through **Command Line Arguments (CLA)**.

General syntax:

```bash
./a.out <number1> <operator> <number2>
```

Example:

```bash
./a.out 123 + 456
```

The command line arguments are received by `main()` using:

```c
int main(int argc, char *argv[])
```

### `argc`

`argc` represents the **number of command line arguments**.

For:

```bash
./a.out 123 + 456
```

the value is:

```text
argc = 4
```

The program name is also counted.

### `argv`

`argv` is an array of strings containing the command line arguments.

```text
argv[0] → ./a.out
argv[1] → 123
argv[2] → +
argv[3] → 456
```

The operands are initially stored as strings. Each digit is converted into an integer using:

```c
argv[1][i] - '0'
```

and then stored in the doubly linked list.

---

# 🔍 Input Validation

The program validates:

### Number of Arguments

Exactly four arguments are required:

```text
./a.out number1 operator number2
```

### Operand Validation

Both operands must contain only digits.

Valid:

```text
12345
987654
```

Invalid:

```text
12a45
```

### Operator Validation

The supported operators are:

```text
+
-
*
/
```

---

# ⚙️ Supported Operations

| Operator | Operation | Status |
|---|---|---|
| `+` | Addition | ✅ Implemented |
| `-` | Subtraction | ✅ Implemented |
| `*` | Multiplication | 🚧 In Progress |
| `/` | Division | 🚧 In Progress |

---

# ➕ Addition

Addition is performed digit-by-digit starting from the least significant digit.

Example:

```text
   999
 + 123
 -----
  1122
```

The implementation handles:

- Digit addition
- Carry propagation
- Different number lengths
- Final carry

---

# ➖ Subtraction

Before subtraction, the numbers are compared to determine the larger operand.

Example:

```text
   1000
 -  123
 ------
    877
```

The implementation handles:

- Digit-by-digit subtraction
- Borrow propagation
- Numbers with different lengths
- Comparison of operands

---

# ✖️ Multiplication

Multiplication follows the traditional long multiplication approach.

Example:

```text
       123
     × 123
     -----
       369
      2460
     12300
     ------
     15129
```

Each partial product is generated using digit-by-digit multiplication.

The partial products are shifted according to their position and accumulated using the addition operation.

The implementation handles:

- Digit-by-digit multiplication
- Carry propagation
- Partial products
- Positional shifting
- Addition of partial products

---

# ➗ Division

Division is planned as part of the APC project and will use the same linked-list representation to support large integers without relying on standard C integer limits.

---

# 🔗 Number Representation

Consider the number:

```text
12345
```

It is represented using a doubly linked list:

```text
HEAD
 ↓
1 <-> 2 <-> 3 <-> 4 <-> 5
                         ↑
                        TAIL
```

Each node stores one digit.

The least significant digit is available from the `TAIL`, allowing arithmetic operations to begin from the rightmost digit.

Example traversal:

```text
TAIL → 5 → 4 → 3 → 2 → 1
```

---

# 🚀 Compilation

Compile all source files using GCC:

```bash
gcc *.c
```

This generates:

```text
a.out
```

---

# ▶️ Execution

General format:

```bash
./a.out <number1> <operator> <number2>
```

### Addition

```bash
./a.out 123 + 456
```

Expected result:

```text
579
```

### Subtraction

```bash
./a.out 456 - 123
```

Expected result:

```text
333
```

### Multiplication

```bash
./a.out 123 '*' 123
```

Expected result:

```text
15129
```

> When using `*` in Linux shells, it is safer to write `'*'` or `\*` so the shell does not expand `*` into filenames.

---

# 🧠 Concepts Practiced

- Structures
- Pointers
- Double Pointers
- Doubly Linked Lists
- Dynamic Memory Allocation
- Command Line Arguments
- String Handling
- Functions
- Modular Programming
- Pointer Traversal
- Carry Handling
- Borrow Handling
- Large Number Representation
- Algorithm Design
- Debugging
- Git and GitHub

---

# 🔄 Program Flow

```text
Command Line Input
        ↓
Input Validation
        ↓
Convert Numbers to DLL
        ↓
Identify Operator
        ↓
Perform Operation
        ↓
Store Result in DLL
        ↓
Display Result
```

---

# 📈 Future Improvements

- [ ] Complete multiplication implementation
- [ ] Complete division implementation
- [ ] Add modulus operation
- [ ] Support negative operands
- [ ] Remove leading zeros
- [ ] Improve memory cleanup
- [ ] Add automated test cases
- [ ] Improve error handling
- [ ] Optimize large-number operations

---

# 👨‍💻 Author

**Omkar More**

GitHub: [OMKAR3404](https://github.com/OMKAR3404)

---

## 📄 License

This project is created for educational and learning purposes.
