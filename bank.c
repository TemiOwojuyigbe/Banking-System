#include <stdio.h>
#include <string.h>
#include "bank.h"

void createAccount(FILE *file){
    Account account;
    printf("Enter Account number: ");
    scanf("%d", &account.accountNumber);
    printf("Enter Name: ");
    scanf("%s", account.name);
    printf("Enter Age: ");
    scanf("%d", &account.age);
    printf("Enter Initial Balance: ");
    scanf("%lf", &account.balance);
    
    fseek(file,0,SEEK_END);
    fwrite(&account, sizeof(Account), 1, file);
    printf("Account created successfully!\n");
}
void deposit(FILE *file, int accountNumber, double amount){
    Account account;
    rewind(file);
    while(fread(&account, sizeof(Account), 1, file)){
        if(account.accountNumber == accountNumber){
            account.balance += amount;
            fseek(file, -sizeof(Account), SEEK_CUR);
            fwrite(&account, sizeof(Account), 1, file);
            printf("Deposit successfully! New balance: %.2lf\n", account.balance);
            return;
        }
    }
    printf("Account not found!\n");
}
void withdraw(FILE *file, int accountNumber, double amount){
    Account account;
    rewind(file);
    while(fread(&account, sizeof(Account), 1, file)){
        if(account.accountNumber == accountNumber){
            if(account.balance >= amount){
                account.balance -= amount;
                fseek(file, -sizeof(Account), SEEK_CUR);
                fwrite(&account, sizeof(Account), 1, file);
                printf("Withdraw successfully! New balance: %.2lf\n", account.balance);
            }else{
                printf("Withdraw failed! insuffcient balance. Current balance: %.2lf\n", account.balance);
            }
            return;
           
        }
    }
    printf("Account not found!\n");
}
void viewAccount(FILE *file, int accountNumber){
    Account account;
    rewind(file);
    while(fread(&account, sizeof(Account), 1, file)){
        if(account.accountNumber == accountNumber){
            printf("Account number: %d\n", account.accountNumber);
            printf("Name: %s\n", account.name);
            printf("Age: %d\n", account.age);
            printf("Balance: %.2lf", account.balance);
            return;
            
        }
    }
    printf("Account not found!\n");
}
void deleteAccount(FILE *file, int accountNumber){
    Account account;
    FILE *tempfile = fopen("temp.dat","wb");
    if(!tempfile){
        printf("Error: Unable to create temporary file.\n");
        return;
    }
    
    int found = 0;
    
    rewind(file);
    while(fread(&account, sizeof(Account), 1, file)){
        if(account.accountNumber == accountNumber){
            found = 1;
            continue;
            
        }
        fwrite(&account, sizeof(Account), 1, file);
    }
    fclose(file);
    fclose(tempfile);
    
    if(found){
        remove("account.dat");
        rename("temp.dat", "account.dat");
        printf("Account deleted successfully!\n");
    }else{
        remove("temp.dat");
        printf("Account not found!\n");
    }
}
