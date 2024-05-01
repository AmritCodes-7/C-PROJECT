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
    char name[20];
    int pin;
    float amount;
    float balance;
    int receiver_acc;
    char rOrS;
} Transaction;
void HidePassword(char pwd[10]);
void WriteUserToFile(User);
void ReadTransactionFromFile();
void SignUp();
void LogIn();
void DisplayMainMenu();
void Deposit(User *);
void Transfer();

int main()
{
    system("color 0b");
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
        SignUp();
        break;
    case 2:
        LogIn();

        break;
    default:
        break;
    }
    return 0;
}

void WriteUserToFile(User userMe)
{
    FILE *ptrUser = fopen("users.txt", "a");

    if (ptrUser == NULL)
    {
        printf("Error opening file for writing.\n");
        return;
    }
    fprintf(ptrUser, "%s %s %s %.2f %d\n", userMe.name, userMe.email, userMe.password, userMe.balance, userMe.pin);
    fclose(ptrUser);
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
            printf("* \b");
        }
    }
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
        DisplayMainMenu(&userMe);
    }
    else
    {
        printf("\nPassword didn't match.\n");
        printf("Access not granted.\n");
        Beep(750, 350); // it takes two arguments frequency and time in ms
    }
}

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

    while (fscanf(ptrUser, "%[^\n]s %s %s %f %d\n", userMe.name, userMe.email, userMe.password, &userMe.balance, &userMe.pin) != EOF)
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
    printf("\n\n\n\t\\ttEnter the operation you want to perform:\t");
    scanf("%d", &choiceOfBanking);

    switch (choiceOfBanking)
    {
    case 1:
        ReadTransactionFromFile();
        break;
    case 2:
        break;
    case 3:
        Deposit(&user);
        break;
    case 4:
        exit(1);
        break;
    default:
        break;
    }
}

void ReadTransactionFromFile()
{
    Transaction user;
    FILE *file = fopen("transactions.txt", "r");
    while (fscanf(file, "%s %d %f %c\n", user.name, &user.receiver_acc, &user.amount, &user.rOrS) != EOF)
    {
        printf("%s %d %f %c\n", user.name, user.receiver_acc, user.amount, user.rOrS);
    }
    fclose(file);
}

void Deposit(User *userU)
{
    Transaction userT;
    printf("\n\t\t\tEnter the amount you want to deposit:\t ");
    scanf("%d", &userT.amount);
    printf("\n\t\t\tEnter your PIN:\t");
    scanf("%d", &userT.pin);

    if (userU->pin == userT.pin)
    {
        printf("\n\t\t\tAmount deposited:\t");
        scanf("%f", userT.amount);
        userU->balance += userT.amount;
    }
}