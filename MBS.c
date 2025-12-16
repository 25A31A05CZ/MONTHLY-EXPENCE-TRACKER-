#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ACCOUNTS 100
#define FILENAME "bank_accounts.dat"

// Account structure
struct Account {
    int acc_no;
    char name[50];
    char acc_type[10];
    double balance;
};

// Function prototypes
void createAccount(struct Account accounts[], int *count);
void depositWithdraw(struct Account accounts[], int count);
void checkBalance(struct Account accounts[], int count);
void loadAccounts(struct Account accounts[], int *count);
void saveAccounts(struct Account accounts[], int count);
int findAccount(struct Account accounts[], int count, int acc_no);

int main() {
    struct Account accounts[MAX_ACCOUNTS];
    int count = 0;
    int choice;
    
    loadAccounts(accounts, &count);
    
    printf("=== MINI BANK MANAGEMENT SYSTEM ===\n");
    
    while (1) {
        printf("\n1. Create Account\n");
        printf("2. Deposit/Withdraw\n");
        printf("3. Check Balance\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                createAccount(accounts, &count);
                break;
            case 2:
                depositWithdraw(accounts, count);
                break;
            case 3:
                checkBalance(accounts, count);
                break;
            case 4:
                saveAccounts(accounts, count);
                printf("Thank you for using Bank Management System!\n");
                exit(0);
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
    
    return 0;
}

// Load accounts from file
void loadAccounts(struct Account accounts[], int *count) {
    FILE *file = fopen(FILENAME, "rb");
    if (file == NULL) {
        *count = 0;
        return;
    }
    
    while (fread(&accounts[*count], sizeof(struct Account), 1, file)) {
        (*count)++;
        if (*count >= MAX_ACCOUNTS) break;
    }
    fclose(file);
}

// Save accounts to file
void saveAccounts(struct Account accounts[], int count) {
    FILE *file = fopen(FILENAME, "wb");
    if (file == NULL) {
        printf("Error saving data!\n");
        return;
    }
    
    for (int i = 0; i < count; i++) {
        fwrite(&accounts[i], sizeof(struct Account), 1, file);
    }
    fclose(file);
}

// Find account by account number
int findAccount(struct Account accounts[], int count, int acc_no) {
    for (int i = 0; i < count; i++) {
        if (accounts[i].acc_no == acc_no) {
            return i;
        }
    }
    return -1;
}

// Create new account
void createAccount(struct Account accounts[], int *count) {
    if (*count >= MAX_ACCOUNTS) {
        printf("Maximum accounts limit reached!\n");
        return;
    }
    
    struct Account new_acc;
    new_acc.acc_no = rand() % 9000 + 1000; // Random 4-digit account number
    
    printf("Enter customer name: ");
    fflush(stdin);
    fgets(new_acc.name, 50, stdin);
    new_acc.name[strcspn(new_acc.name, "\n")] = 0;
    
    printf("Enter account type (savings/current): ");
    scanf("%s", new_acc.acc_type);
    
    printf("Enter initial deposit: ");
    scanf("%lf", &new_acc.balance);
    
    accounts[*count] = new_acc;
    (*count)++;
    
    printf("Account created successfully!\n");
    printf("Account Number: %d\n", new_acc.acc_no);
    printf("Name: %s\n", new_acc.name);
    printf("Account Type: %s\n", new_acc.acc_type);
    printf("Balance: %.2lf\n", new_acc.balance);
    
    saveAccounts(accounts, *count);
}

// Deposit and Withdraw
void depositWithdraw(struct Account accounts[], int count) {
    int acc_no, index, choice;
    double amount;
    
    printf("Enter account number: ");
    scanf("%d", &acc_no);
    
    index = findAccount(accounts, count, acc_no);
    if (index == -1) {
        printf("Account not found!\n");
        return;
    }
    
    printf("\nAccount Details:\n");
    printf("Name: %s\n", accounts[index].name);
    printf("Current Balance: %.2lf\n", accounts[index].balance);
    
    printf("\n1. Deposit\n2. Withdraw\nEnter choice: ");
    scanf("%d", &choice);
    
    printf("Enter amount: ");
    scanf("%lf", &amount);
    
    if (choice == 1) {
        // Deposit
        accounts[index].balance += amount;
        printf("Deposited %.2lf successfully!\n", amount);
        printf("New Balance: %.2lf\n", accounts[index].balance);
    } else if (choice == 2) {
        // Withdraw
        if (amount > accounts[index].balance) {
            printf("Insufficient balance!\n");
            return;
        }
        accounts[index].balance -= amount;
        printf("Withdrawn %.2lf successfully!\n", amount);
        printf("New Balance: %.2lf\n", accounts[index].balance);
    } else {
        printf("Invalid choice!\n");
        return;
    }
    
    saveAccounts(accounts, count);
}

// Check balance
void checkBalance(struct Account accounts[], int count) {
    int acc_no, index;
    
    printf("Enter account number: ");
    scanf("%d", &acc_no);
    
    index = findAccount(accounts, count, acc_no);
    if (index == -1) {
        printf("Account not found!\n");
        return;
    }
    
    printf("\n=== ACCOUNT BALANCE ===\n");
    printf("Account Number: %d\n", accounts[index].acc_no);
    printf("Name: %s\n", accounts[index].name);
    printf("Account Type: %s\n", accounts[index].acc_type);
    printf("Balance: %.2lf\n", accounts[index].balance);
}