#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "atm.h"

// Global variables defined in atm.h
Account accounts[MAX_ACCOUNTS];
int num_accounts = 0;

/**
 * @brief Clears the input buffer.
 */
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * @brief Loads account data from the persistent file.
 */
void load_accounts() {
    FILE *file = fopen(DATA_FILE, "rb");
    if (file == NULL) {
        printf("Data file not found. Initializing with default accounts.\n");
        // Initialize a few default accounts for first run
        accounts[0] = (Account){1001, 1234, 5000.00, 2500.00, {}, 0};
        accounts[1] = (Account){1002, 5678, 1000.00, 10000.00, {}, 0};
        num_accounts = 2;
        save_accounts(); // Save the defaults
        return;
    }

    // Read the number of accounts
    fread(&num_accounts, sizeof(int), 1, file);

    // Read the account data
    fread(accounts, sizeof(Account), num_accounts, file);

    fclose(file);
    printf("Loaded %d accounts from %s.\n", num_accounts, DATA_FILE);
}

/**
 * @brief Saves all account data to the persistent file.
 */
void save_accounts() {
    FILE *file = fopen(DATA_FILE, "wb");
    if (file == NULL) {
        perror("Error opening data file for writing");
        return;
    }

    // Write the number of accounts
    fwrite(&num_accounts, sizeof(int), 1, file);

    // Write the account data
    fwrite(accounts, sizeof(Account), num_accounts, file);

    fclose(file);
    printf("Saved %d accounts to %s.\n", num_accounts, DATA_FILE);
}

/**
 * @brief Authenticates a user with account number and PIN.
 * @return The index of the account in the global array, or -1 if authentication fails.
 */
int authenticate_user(int account_num, int pin) {
    for (int i = 0; i < num_accounts; i++) {
        if (accounts[i].account_number == account_num && accounts[i].pin == pin) {
            return i; // Authentication successful, return account index
        }
    }
    return -1; // Authentication failed
}

/**
 * @brief Records a transaction to the account's history.
 */
void record_transaction(int account_index, char type, double amount) {
    Account *acc = &accounts[account_index];

    // Shift history to make room for the new transaction (circular buffer logic)
    if (acc->num_transactions == MAX_TRANSACTIONS) {
        // Shift all transactions up by one
        for (int i = 0; i < MAX_TRANSACTIONS - 1; i++) {
            acc->history[i] = acc->history[i+1];
        }
        acc->num_transactions = MAX_TRANSACTIONS - 1;
    }

    // Add new transaction
    Transaction *new_trans = &acc->history[acc->num_transactions];
    new_trans->type = type;
    new_trans->amount = amount;

    // Get current time for the transaction date
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    strftime(new_trans->date, sizeof(new_trans->date), "%Y-%m-%d %H:%M:%S", tm);

    acc->num_transactions++;
}

// --- Core ATM Functions (To be implemented in Phase 2) ---

void do_withdrawal(int account_index) {
    Account *acc = &accounts[account_index];
    int account_type;
    double amount;

    printf("\n--- Withdrawal ---\n");
    printf("1. Checking\n");
    printf("2. Savings\n");
    printf("Select account to withdraw from: ");
    if (scanf("%d", &account_type) != 1 || (account_type != 1 && account_type != 2)) {
        clear_input_buffer();
        printf("Invalid account selection.\n");
        return;
    }
    clear_input_buffer();

    printf("Enter amount to withdraw: $");
    if (scanf("%lf", &amount) != 1 || amount <= 0) {
        clear_input_buffer();
        printf("Invalid amount.\n");
        return;
    }
    clear_input_buffer();

    double *balance = (account_type == 1) ? &acc->balance_checking : &acc->balance_savings;
    char *account_name = (account_type == 1) ? "Checking" : "Savings";

    if (*balance >= amount) {
        *balance -= amount;
        record_transaction(account_index, 'W', amount);
        printf("Successfully withdrew $%.2lf from your %s account.\n", amount, account_name);
        printf("New %s balance: $%.2lf\n", account_name, *balance);
    } else {
        printf("Insufficient funds in your %s account. Current balance: $%.2lf\n", account_name, *balance);
    }
}

void do_deposit(int account_index) {
    Account *acc = &accounts[account_index];
    int account_type;
    double amount;

    printf("\n--- Deposit ---\n");
    printf("1. Checking\n");
    printf("2. Savings\n");
    printf("Select account to deposit to: ");
    if (scanf("%d", &account_type) != 1 || (account_type != 1 && account_type != 2)) {
        clear_input_buffer();
        printf("Invalid account selection.\n");
        return;
    }
    clear_input_buffer();

    printf("Enter amount to deposit: $");
    if (scanf("%lf", &amount) != 1 || amount <= 0) {
        clear_input_buffer();
        printf("Invalid amount.\n");
        return;
    }
    clear_input_buffer();

    double *balance = (account_type == 1) ? &acc->balance_checking : &acc->balance_savings;
    char *account_name = (account_type == 1) ? "Checking" : "Savings";

    *balance += amount;
    record_transaction(account_index, 'D', amount);
    printf("Successfully deposited $%.2lf into your %s account.\n", amount, account_name);
    printf("New %s balance: $%.2lf\n", account_name, *balance);
}

void do_transfer(int account_index) {
    Account *acc = &accounts[account_index];
    int from_type, to_type;
    double amount;

    printf("\n--- Transfer ---\n");
    printf("1. Checking to Savings\n");
    printf("2. Savings to Checking\n");
    printf("Select transfer direction: ");
    if (scanf("%d", &from_type) != 1 || (from_type != 1 && from_type != 2)) {
        clear_input_buffer();
        printf("Invalid selection.\n");
        return;
    }
    clear_input_buffer();

    printf("Enter amount to transfer: $");
    if (scanf("%lf", &amount) != 1 || amount <= 0) {
        clear_input_buffer();
        printf("Invalid amount.\n");
        return;
    }
    clear_input_buffer();

    double *balance_from, *balance_to;
    char *name_from, *name_to;

    if (from_type == 1) { // Checking to Savings
        balance_from = &acc->balance_checking;
        balance_to = &acc->balance_savings;
        name_from = "Checking";
        name_to = "Savings";
    } else { // Savings to Checking
        balance_from = &acc->balance_savings;
        balance_to = &acc->balance_checking;
        name_from = "Savings";
        name_to = "Checking";
    }

    if (*balance_from >= amount) {
        *balance_from -= amount;
        *balance_to += amount;
        // Record as a Transfer transaction
        record_transaction(account_index, 'T', amount);
        printf("Successfully transferred $%.2lf from %s to %s.\n", amount, name_from, name_to);
        printf("New %s balance: $%.2lf\n", name_from, *balance_from);
        printf("New %s balance: $%.2lf\n", name_to, *balance_to);
    } else {
        printf("Insufficient funds in your %s account. Current balance: $%.2lf\n", name_from, *balance_from);
    }
}

void view_balance(int account_index) {
    Account *acc = &accounts[account_index];
    printf("\n--- Account Balances ---\n");
    printf("Checking Account Balance: $%.2lf\n", acc->balance_checking);
    printf("Savings Account Balance:  $%.2lf\n", acc->balance_savings);
}

void view_history(int account_index) {
    Account *acc = &accounts[account_index];
    printf("\n--- Transaction History (Last %d) ---\n", MAX_TRANSACTIONS);

    if (acc->num_transactions == 0) {
        printf("No transactions recorded.\n");
        return;
    }

    printf("%-20s %-10s %-10s\n", "Date/Time", "Type", "Amount");
    printf("-------------------- ---------- ----------\n");

    for (int i = 0; i < acc->num_transactions; i++) {
        Transaction t = acc->history[i];
        char type_str[15];
        if (t.type == 'W') strcpy(type_str, "Withdrawal");
        else if (t.type == 'D') strcpy(type_str, "Deposit");
        else if (t.type == 'T') strcpy(type_str, "Transfer");
        else strcpy(type_str, "Unknown");

        printf("%-20s %-10s $%-9.2lf\n", t.date, type_str, t.amount);
    }
}

/**
 * @brief Displays the main ATM menu and handles user input.
 */
void display_menu(int account_index) {
    int choice;
    do {
        printf("\n--- ATM Main Menu ---\n");
        printf("1. View Balance\n");
        printf("2. Withdraw\n");
        printf("3. Deposit\n");
        printf("4. Transfer\n");
        printf("5. View Transaction History\n");
        printf("6. Exit and Save\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            clear_input_buffer();
            choice = 0; // Force re-loop
            printf("Invalid input. Please enter a number.\n");
            continue;
        }
        clear_input_buffer();

        switch (choice) {
            case 1: view_balance(account_index); break;
            case 2: do_withdrawal(account_index); break;
            case 3: do_deposit(account_index); break;
            case 4: do_transfer(account_index); break;
            case 5: view_history(account_index); break;
            case 6: printf("Thank you for using the ATM. Exiting...\n"); break;
            default: printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);
}

/**
 * @brief Main function for the ATM program.
 */
int main() {
    int account_num, pin, account_index;

    load_accounts();

    printf("--- Welcome to the Advanced ATM ---\n");

    // Authentication loop
    do {
        printf("Enter Account Number (or 0 to exit): ");
        if (scanf("%d", &account_num) != 1) {
            clear_input_buffer();
            account_num = -1;
            printf("Invalid input.\n");
            continue;
        }
        clear_input_buffer();

        if (account_num == 0) {
            printf("Exiting program.\n");
            return 0;
        }

        printf("Enter PIN: ");
        if (scanf("%d", &pin) != 1) {
            clear_input_buffer();
            pin = -1;
            printf("Invalid input.\n");
            continue;
        }
        clear_input_buffer();

        account_index = authenticate_user(account_num, pin);

        if (account_index != -1) {
            printf("\nAuthentication successful! Welcome, Account %d.\n", account_num);
            display_menu(account_index);
        } else {
            printf("\nAuthentication failed. Invalid account number or PIN.\n");
        }

    } while (account_index == -1);

    save_accounts();

    return 0;
}
