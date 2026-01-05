# Advanced ATM System in C

This is an advanced ATM simulation project written in C. It features user authentication, support for multiple accounts (Checking and Savings), transaction history tracking, and persistent data storage using a binary file.

## Features

*   **User Authentication:** Secure login using Account Number and PIN.
*   **Multiple Accounts:** Separate balances for Checking and Savings accounts.
*   **Core Transactions:** Withdrawal, Deposit, and Transfer between accounts.
*   **Transaction History:** Records the last 10 transactions for each account.
*   **Data Persistence:** Account data is loaded from and saved to a file (`accounts.dat`), ensuring data is preserved between sessions.

## Compilation

The project uses a simple `Makefile` for compilation.

1.  **Ensure you have GCC installed.**
2.  **Compile the project:**
    ```bash
    make
    ```
    This will create an executable file named `atm`.

## Usage

1.  **Run the executable:**
    ```bash
    ./atm
    ```
2.  **Initial Setup:** On the very first run, the program will create a default `accounts.dat` file with the following accounts:

| Account Number | PIN | Checking Balance | Savings Balance |
| :------------- | :-- | :--------------- | :-------------- |
| **1001**       | 1234 | $5000.00         | $2500.00        |
| **1002**       | 5678 | $1000.00         | $10000.00       |

3.  **Login:** Enter one of the default account numbers and the corresponding PIN.
4.  **Menu:** Follow the on-screen menu to perform transactions.
5.  **Exit:** Select option `6. Exit and Save` to save all changes (balances and transaction history) to the `accounts.dat` file before closing the program.

## Project Files

*   `atm.c`: The main source code file containing all the logic and functions.
*   `atm.h`: The header file defining the data structures (`Account`, `Transaction`) and function prototypes.
*   `Makefile`: Used to compile the project.
*   `accounts.dat`: The binary file used for persistent data storage (created on first run).
