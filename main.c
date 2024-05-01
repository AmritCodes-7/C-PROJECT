#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define ENTER 13
#define TAB 9
#define BCKSPC 8
// 6894
// 6989
//   all functions
void HidePassword(char[]);
// creating a structure that will store the information of the user
typedef struct
{
    char name[20];
    char email[30];
    char password[10];
    float balance;
    int pin;
} user;

typedef struct
{
    char name[20];
    char email[30];
    char password[10];
    float balance;
    int pin;

} user_Rd;

typedef struct
{
    float amount;
    char name[20];
    int receiver_acc;
    char r_or_s; // R for received
} struct_for_transfer;

int main()
{
    system("color 0b");

    user user_me;

    user_Rd user_read;

    struct_for_transfer user_transfer;
    struct_for_transfer user_deposit;

    FILE *ptr_signin;
    FILE *ptr_deposit;
    FILE *ptr_transfer;

    int choice_at_login;
    char choice_of_option;

HOMEPAGE:
    system("cls");

    printf("\n\n\t\t\t\t\t\t\t\t------------- BANKING SYSTEM -------------\n");
    printf("\n\n------------- LOG-IN PAGE -------------\n");
    printf("\t   1. SignUp\n");
    printf("\t   2. Log in\n");
    printf("\t   3. Log in as Admin\n");
    printf("\t   4. Exit\n");
    printf("\nEnter the task you want to perform: ");
    scanf("%d", &choice_at_login);

    switch (choice_at_login)
    {
    case 1: // sign up
        char password2[10];
        printf("\n\t\t\tEnter your name:\t");
        fflush(stdin);
        gets(user_me.name);
        printf("\t\t\tEnter your email:\t");
        scanf("%s", user_me.email);
        printf("\t\t\tEnter the password:\t");
        HidePassword(user_me.password);
        printf("\n\t\t\tConfirm your password:\t");
        HidePassword(password2);
        printf("\n\n");

        if (strcmp(user_me.password, password2) == 0)
        {
            printf("\nPassword matched");
            printf("\nSuccessfully signed in....\n");

            srand(time(0));
            int randomNumber = rand() % 9000 + 1000;
            user_me.pin = randomNumber;
            printf("\n\nREMEMBER YOUR PIN:%d", user_me.pin);
            ptr_signin = fopen("sign_info.txt", "a+");
            fwrite(&user_me, sizeof(user), 1, ptr_signin);

            fclose(ptr_signin);
            fflush(stdin);
            printf("\nDo you want to perform any other task[y/n]:\t");
            choice_of_option = getchar();
            if (choice_of_option == 'y' || choice_of_option == 'Y')
            {
                goto HOMEPAGE;
            }
            else
            {
                exit(1);
            }
        }
        else
        {
            printf("\nPassword didn't matched.");
            printf("\nAccess not granted");
            Beep(750, 350); // it takes two arguments frequency and time in ms
        }

        break;

    case 2: // log in
    ENTERPASSWORD:
        printf("\n\n\t\t\t\tEnter your Username:\t");
        fflush(stdin);
        gets(user_me.name);
        printf("\t\t\t\tEnter your password:\t");
        HidePassword(user_me.password);

        ptr_signin = fopen("sign_info.txt", "r");
        while (fread(&user_read, sizeof(user_Rd), 1, ptr_signin))
        {
            if (strcmp(user_me.name, user_read.name) == 0)
            {
                if (strcmp(user_me.password, user_read.password) == 0)
                {
                    printf("\n\n");
                    char presskey;
                    printf("\n\nSuccessfully logged in!!");
                    printf("\nWELCOME %s", user_read.name);
                    printf("\n\nPress ENTER to continue, TAB to return to home page and any other key to exit the program....\n\n");
                    presskey = getch();
                    if (presskey == ENTER)
                    {
                    INVALID:
                        // user_read.balance = user_me.balance;
                        system("cls");
                        int choiceOfBanking;
                        printf("\n\n\t\t\t\t\t\t\t\t------------- BANKING SYSTEM -------------\n");
                        printf("\n\n%s\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t%.2f\n%s", user_read.name, user_read.balance, user_read.email);
                        printf("\n\n\t\t\t\t\t\t\t\t1.SATEMENTS\t\t2.TRANSFER\n\t\t\t\t\t\t\t\t3.DEPOSIT\t\t4.EXIT");
                        printf("\n\nEnter operation you want to perform: ");
                        scanf("%d", &choiceOfBanking);

                        // statements
                        if (choiceOfBanking == 1)
                        {
                            // ptr_statement = fopen("statements.txt", "r");
                            ptr_deposit = fopen("deposit.txt", "r");
                            ptr_transfer = fopen("transfer.txt", "r");
                            printf("\n\n");
                            // if (ptr_statement == NULL)
                            // {
                            //     printf("\n\nError openeing the file......");
                            //     printf("\nExiting.........");
                            //     Sleep(500);
                            //     goto INVALID;
                            // }

                            while (fread(&user_transfer, sizeof(struct_for_transfer), 1, ptr_transfer))
                            {
                                printf("%s\t%f\t%d\t%c\n", user_transfer.name, user_transfer.amount, user_transfer.receiver_acc, user_transfer.r_or_s);
                            }
                            while (fread(&user_transfer, sizeof(struct_for_transfer), 1, ptr_deposit))
                            {
                                printf("%s\t%f\t%d\t%c\n", user_transfer.name, user_transfer.amount, user_transfer.receiver_acc, user_transfer.r_or_s);
                            }
                            // fclose(ptr_statement);
                            fclose(ptr_deposit);
                            fclose(ptr_transfer);
                        }
                        else if (choiceOfBanking == 2) // transfer
                        {
                            int pin;
                            user_transfer.r_or_s = 'S';
                            strcpy(user_transfer.name, user_read.name);
                            printf("\n\t\t\tEnter the amount you want to transfer:\t");
                            scanf("%f", &user_transfer.amount);
                            printf("\n\t\t\tEnter the account number of the receiver:\t");
                            scanf("%d", &user_transfer.receiver_acc);
                            fflush(stdin);
                            printf("\n\t\t\tEnter your PIN:\t");
                            scanf("%d", &pin);
                            if (pin == user_read.pin)
                            {

                                if (user_transfer.amount > user_read.balance)
                                {
                                    printf("Insufficient Amount.......");
                                    Sleep(2000);
                                    goto INVALID;
                                }
                                ptr_signin = fopen("sign_info.txt", "a+");
                                printf("\n\t\t\tBalanced Transfered to account number %d", user_transfer.receiver_acc);
                                user_read.balance = user_read.balance - user_transfer.amount;
                                while (fread(&user_me, sizeof(user), 1, ptr_signin))
                                {
                                    if (strcmp(user_me.name, user_transfer.name) == 0)
                                    {
                                        user_me.balance = user_read.balance;
                                    }
                                }

                                ptr_transfer = fopen("transfer.txt", "a+");
                                fprintf(ptr_transfer, "%s\t\t%f\t\t%d\t\t%c\n", user_transfer.name, user_transfer.amount, user_transfer.receiver_acc, user_transfer.r_or_s);
                                fclose(ptr_transfer);
                                fclose(ptr_signin);
                                printf("\nReturning to main page.... ");
                                Sleep(4000);
                                goto INVALID;
                            }
                            else
                            {
                                printf("\nTransaction failed.......");
                                printf("\nReturning to MAINpage.......");
                                Sleep(4000);
                                goto INVALID;
                            }
                            fclose(ptr_transfer);
                        }
                        else if (choiceOfBanking == 3)
                        {
                            int pin;
                            user_deposit.r_or_s = 'R';
                            printf("\n\t\t\tEnter the amount you wwant to deposit:\t");
                            scanf("%f", &user_deposit.amount);
                            printf("\n\t\t\tEnter your PIN:\t");
                            scanf("%d", &pin);
                            if (pin == user_read.pin)
                            {
                                printf("\n\t\tEnter your account number:\t");
                                scanf("%d", &user_deposit.receiver_acc);
                                fflush(stdin);
                                printf("\n\t\tAmount deposited:\t%f", user_deposit.amount);
                                ptr_deposit = fopen("deposit.txt", "a+");
                                fprintf(ptr_deposit, "%s\t%f\t%d\t%c\n", user_deposit.name, user_deposit.amount, user_deposit.receiver_acc, user_deposit.r_or_s);
                                ptr_signin = fopen("sign_info.txt", "a+");
                                user_read.balance = user_read.balance + user_deposit.amount;
                                while (fread(&user_me, sizeof(user), 1, ptr_signin))
                                {
                                    if (strcmp(user_me.name, user_transfer.name) == 0)
                                    {
                                        user_me.balance = user_read.balance;
                                    }
                                }
                                printf("\nReturning to main page.... ");
                                Sleep(4000);
                                fclose(ptr_signin);
                                fclose(ptr_deposit);
                                goto INVALID;
                            }
                        }
                        else if (choiceOfBanking == 4)
                        {
                            goto HOMEPAGE;
                        }
                        else
                        {
                            char choiceOfInvalid;
                            printf("\nInvalid option.....");
                            printf("\nDo you want to enter the choice again [y/n]: ");
                            fflush(stdin);
                            choiceOfInvalid = getchar();
                            if (choiceOfInvalid == 'y' || choiceOfInvalid == 'Y')
                            {
                                goto INVALID;
                            }
                            else
                            {
                                exit(1);
                            }
                        }
                    }
                    else if (presskey == TAB)
                    {
                        goto HOMEPAGE;
                    }
                    else
                    {
                        exit(1);
                    }
                    printf("\n\n");
                }
            }
            else
            {
                char optionOfPw;
                printf("\n\n\nNo username with this password is found.");
                printf("\nDo you want to try again[y/n]:\t");
                optionOfPw = getchar();
                if (optionOfPw == 'y' || optionOfPw == 'Y')
                {
                    goto ENTERPASSWORD;
                }
                else
                {
                    goto HOMEPAGE;
                }
            }
        }
        fclose(ptr_signin);

        break;
    case 3:
        system("cls");
        printf("\n\n\t\t\t\t\t\t\t\t------------- BANKING SYSTEM -------------\n");
        ptr_signin = fopen("sign_info.txt", "r+");
        printf("\n\n");
        printf("");
        while (fread(&user_read, sizeof(user_Rd), 1, ptr_signin))
        {
            printf("NAME:%s\nEMAIL:%s\nPASSWORD:%s\nPIN:%d\n\n", user_read.name, user_read.email, user_read.password, user_read.pin);
        }
        fclose(ptr_signin);
        break;
    case 4:

        break;
    default:
        printf("\n\nInvalid choice returning to the main page.\n");
        printf("Exiting.....................");
        Sleep(800);
        goto HOMEPAGE;
        break;
    }
    return 0;
}

void HidePassword(char pwd[10])
{
    int i = 0;
    char ch;
    while (1)
    {
        ch = getch();
        if (ch == ENTER || ch == TAB)
        {
            pwd[i] = '\0'; // as we know string is always terminated by null character
            break;
        }
        else if (ch == BCKSPC)
        {
            if (i > 0)
            {
                i--;
                printf("\b \b"); // this will erase the last element if backspace key is pressed
            }
        }
        else
        {
            pwd[i] = ch;
            i++;
            printf("* \b");
        }
    }
}