#ifndef ATM_H
#define ATM_H

#define MAX_TRANSACTIONS 10
#define MAX_ACCOUNTS 10
#define DATA_FILE "accounts.dat"

// Structure for a single transaction
typedef struct {
    char type; // 'W' for Withdrawal, 'D' for Deposit, 'T' for Transfer
    double amount;
    char date[20]; // Simple date/time string
} Transaction;

// Structure for a single account
typedef struct {
    int account_number;
    int pin;
    double balance_checking;
    double balance_savings;
    Transaction history[MAX_TRANSACTIONS];
    int num_transactions;
} Account;

// Global array to hold all accounts in memory
extern Account accounts[MAX_ACCOUNTS];
extern int num_accounts;

// Function Prototypes
void load_accounts();
void save_accounts();
int authenticate_user(int account_num, int pin);
void display_menu(int account_index);
void record_transaction(int account_index, char type, double amount);

#endif // ATM_H
