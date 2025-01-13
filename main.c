#include <stdio.h>
#include <stdlib.h>
#include "bank.h"


int main(){
    FILE *file = fopen("accounts.dat", "rb+");
    if(!file){
        file = fopen("account.dat", "wb+");
        if(!file){
            printf("Error: Unable to open file\n");
            return 1;
        }
    }
    
    int choice, accountNumber;
    double amount;
    
    do{
        printf("\nBanking System Menu:\n");
        printf("1. Create Account\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. View Account\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice){
            case 1:
                createAccount(file);
                break;
            case 2:
                printf("Enter Account Number:");
                scanf("%d", &accountNumber);
                printf("Enter Deposit Amount: ");
                scanf("%lf", &amount);
                deposit(file, accountNumber, amount);
                break;
            case 3:
                printf("Enter Account Number: ");
                scanf("%d", &accountNumber);
                printf("Enter Withdraw Amount: ");
                scanf("%lf", &amount);
                withdraw(file, accountNumber, amount);
                break;
            case 4:
                printf("Enter Account Number: ");
                scanf("%d", &accountNumber);
                printf("Viewing Account... ");
                viewAccount(file, accountNumber);
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice please try again.\n");
        }
    }while(choice != 5);
    
    fclose(file);
    return 0;
    
}
