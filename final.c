#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define ENTER 13
#define TAB 9
#define BCKSPC 8

typedef struct
{
    char name[20];
    char email[30];
    char password[10];
    float balance;
    int pin;
} User;
typedef struct
{
    float balance;
    float amount;
    char name[20];
    int receiver_acc;
    char r_or_s; // R for received and S for recieved
} Transaction;

// functions name in PascalCase and variables name in camelCase
void HidePassword(char[]);
void SignUp();
void LogIn();
void WriteUserToFile(User);
void DisplayTansactions(FILE *file);
void PerformAnotherTask();
void TryAgain();
void DisplayMainMenu(User *);
void PerformTransfer(Transaction *);
void PerformDeposit(Transaction *);
// void DisplayStatements(User *user);

// structure to hold data

int main()
{
    system("color 0b");
HOMEPAGE:
    system("cls");
    int choice_at_login;
    printf("\n\n\t\t\t\t\t\t\t\t------------- BANKING SYSTEM -------------\n");
    printf("\n\n------------- LOG-IN PAGE -------------\n");
    printf("\t   1. SignUp\n");
    printf("\t   2. Log in\n");
    printf("\t   3. Exit\n");
    printf("\nEnter the task you want to perform: ");
    scanf("%d", &choice_at_login);

    switch (choice_at_login)
    {
    case 1:
        char choice_of_option;
        SignUp();
        fflush(stdin);
        printf("\n\nDo you want to perform any other task[y/n]:\t");
        choice_of_option = getchar();
        if (choice_of_option == 'y' || choice_of_option == 'Y')
        {
            goto HOMEPAGE;
        }
        else
        {
            exit(1);
        }
        break;

    case 2:

        LogIn();

    case 3:
        exit(1);
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
            pwd[i] = '\0';
            break;
        }
        else if (ch == BCKSPC)
        {
            if (i > 0)
            {
                i--;
                printf("\b \b");
            }
        }
        else
        {
            pwd[i] = ch;
            i++;
            printf("*");
        }
    }
}

void WriteUserToFile(User userMe)
{
    FILE *ptrUser = fopen("users.txt", "a");

    if (ptrUser == NULL)
    {
        printf("Error opening file for writing.\n");
        return;
    }
    fprintf(ptrUser, "%s,%s,%s,%.2f,%d\n", userMe.name, userMe.email, userMe.password, userMe.balance, userMe.pin);
    fclose(ptrUser);
}

void SignUp()
{
    User userMe;
    char toCheckPassword[10];
    printf("\n\t\t\tEnter your name:\t");
    fflush(stdin);
    gets(userMe.name);
    printf("\t\t\tEnter your email:\t");
    scanf("%s", userMe.email);
    printf("\t\t\tEnter the password:\t");
    HidePassword(userMe.password);
    printf("\n\t\t\tConfirm your password:\t");
    HidePassword(toCheckPassword);
    printf("\n\n");

    if (strcmp(userMe.password, toCheckPassword) == 0)
    {
        printf("\nPassword matched\n");
        printf("Successfully signed up.......\n");

        srand(time(NULL));
        userMe.pin = rand() % 9000 + 1000;
        printf("\nRemember your PIN: %d\n", userMe.pin);

        userMe.balance = 0.0; // Initial balance

        WriteUserToFile(userMe);
    }
    else
    {
        printf("\nPassword didn't match.\n");
        printf("Access not granted.\n");
        Beep(750, 350); // it takes two arguments frequency and time in ms
    }
}

// this will help to login
void LogIn()
{
ENTERPASSWORD:
    char username[20], password[10];
    printf("\n\n\t\t\t\tEnter your Username:\t");
    fflush(stdin);
    gets(username);
    printf("\t\t\t\tEnter your password:\t");
    HidePassword(password);
    FILE *ptrUser = fopen("users.txt", "r");
    if (ptrUser == NULL)
    {
        printf("Error opening file for reading.\n");
        return;
    }
    User userMe;

    while (fscanf(ptrUser, "%[^,],%[^,],%[^,],%f,%d\n", userMe.name, userMe.email, userMe.password, &userMe.balance, &userMe.pin) != EOF)
    {
        if (strcmp(username, userMe.name) == 0 && strcmp(password, userMe.password) == 0)
        {
            char presskey;
            printf("\nSuccessfully logged in!\n");
            printf("Welcome, %s\n", userMe.name);
            printf("\n\nPress ENTER to continue, TAB to return to home page and any other key to exit the program....\n\n");
            presskey = getch();
            fclose(ptrUser);
            DisplayMainMenu(&userMe);
            return;
        }
    }
    fclose(ptrUser);

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
        exit(1);
    }
}

void DisplayMainMenu(User *user)
{
    system("cls");
    printf("\n\n\t\t\t\t\t\t\t\t------------- BANKING SYSTEM -------------\n");
    printf("\n\n%s\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t%.2f\n%s", user->name, user->balance, user->email);
    printf("\n\n\t\t\t\t\t\t\t\t1.SATEMENTS\t\t2.TRANSFER\n\t\t\t\t\t\t\t\t3.DEPOSIT\t\t4.EXIT");
    int choiceOfBanking;
    printf("\n\n\t\t\tEnter the operation you want to perform:\t");
    scanf("%d", &choiceOfBanking);
    switch (choiceOfBanking)
    {
    case 1:
        FILE *file = fopen("transactions.txt", "a+");
        DisplayTransactions(file);
        break;
    case 2:
        // PerformTransfer(&currentUser);
        break;
    case 3:
        Transaction user;
        PerformDeposit(&user);
        break;
    case 4:
        exit(1);
    default:
        printf("\nInvalid option. Exiting...\n");
        Sleep(4000);
        exit(1);
    }
}

// it will display all the transactions
void DisplayTransactions(FILE *file)
{

    if (file == NULL)
    {
        printf("Error opening file for reading.\n");
        return;
    }
    Transaction transaction;
    while (fscanf(file, "%s %f %d %c", transaction.name, &transaction.amount, &transaction.receiver_acc, &transaction.r_or_s) != EOF)
    {
        printf("%s %.2f %d %c\n", transaction.name, transaction.amount, transaction.receiver_acc, transaction.r_or_s);
    }
    fclose(file);
    // DisplayMainMenu(&user);
}

// void PerformTransfer()
// {
// }

void PerformDeposit(Transaction *user)
{
    int pin;
    User userMe;

    printf("\n\t\t\tEnter your username:\t");
    scanf("%s", user->name);
    fflush(stdin);
    printf("\n\t\t\tEnter the amount you want to deposit:\t");
    scanf("%f", &user->amount);
    fflush(stdin);
    printf("\n\t\t\tEnter your account number:\t");
    scanf("%d", &user->receiver_acc);
    user->r_or_s = 'R';
    fflush(stdin);
    printf("\n\nEnter your PIN:\t");
    scanf("%d", &pin);
    FILE *file = fopen("users.txt", "r");
    while (fscanf(file, "%[^,],%[^,],%[^,],%f,%d\n", userMe.name, userMe.email, userMe.password, &userMe.balance, &userMe.pin) != EOF)
    {
        if (pin == userMe.pin && strcmp(userMe.name, user->name) == 0)
        {
            printf("\n\n\t\t\tAmount Transferred: %f", user->amount);
            user->balance = user->balance + user->amount;
            fclose(file);
            DisplayMainMenu(user);
            return;
        }
    }
    fclose(file);
}