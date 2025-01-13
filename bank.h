#ifndef BANK_H
#define BANK_H

typedef struct{
    int accountNumber;
    char name[50];
    int age;
    double balance;
} Account;

void createAccount(FILE *file);
void deposit(FILE *file, int accountNumber, double amount);
void withdraw (FILE *file, int accountNumber, double amount);
void viewAccount(FILE *file, int accountNumber);
void deleteAccount(FILE *file, int accountNumber);

#endif
