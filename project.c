#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define ENTER 13
#define TAB 9
#define BCKSPC 8

// this is a structure which will be used to store the information of customer or simply user
typedef struct user
{
    char name[20];
    int pin;
    char email[30];
    char password[10];
} in;

typedef struct readUser
{
    char name[20];
    int pin;
    char email[30];
    char password[10];
} rd;
in customerIn;
rd customerRd;
FILE *fptrsign;

// writing a function which reads and hides the password at the same time
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

int main()
{
    system("color 0b");

    int choiceOfLogin;
    char choiceOfOption;
    char password2[10];
HOMEPAGE:
    system("cls");
    printf("\n\n\t\t\t\t\t\t\t\t------------- BANKING SYSTEM -------------\n");
    printf("\n\n------------- LOG-IN PAGE -------------\n");
    printf("\t   1. SignUp\n");
    printf("\t   2. Log in\n");
    printf("\t   3. Log in as Admin\n");
    printf("\t   4. Exit\n");
    printf("\nEnter the task you want to perform: ");
    scanf("%d", &choiceOfLogin);
    switch (choiceOfLogin)
    {
    case 1:

        printf("\n\t\t\tEnter your name:\t");
        fflush(stdin);
        gets(customerIn.name);
        printf("\t\t\tEnter your email:\t");
        scanf("%s", customerIn.email);
        printf("\t\t\tEnter the password:\t");
        HidePassword(customerIn.password);
        printf("\n\t\t\tConfirm your password:\t");
        HidePassword(password2);
        printf("\n\n");
        if (strcmp(customerIn.password, password2) == 0)
        {
            srand(time(0));
            int randomNumber = rand() % 9000 + 1000;
            customerIn.pin = randomNumber;
            printf("REMEMBER YOUR PIN:%d", customerIn.pin);
            fptrsign = fopen("signin_information.txt", "ab+");
            printf("\nPassword matched");
            printf("\nSuccessfully signed in....\n");
            fwrite(&customerIn, sizeof(struct user), 1, fptrsign);
            fclose(fptrsign);
            fflush(stdin);
            printf("\nDo you want to perform any other task[y/n]:\t");
            choiceOfOption = getchar();
            if (choiceOfOption == 'y' || choiceOfOption == 'Y')
            {
                goto HOMEPAGE;
            }
            else
            {
                exit(0);
            }
        }
        else
        {
            printf("\nPassword didn't matched.");
            printf("\nAccess not granted");
            Beep(750, 350); // it takes two arguments frequency and time in ms
        }

        printf("");
        break;
    case 2:

        printf("\n\n\t\t\t\tEnter your Username:\t");
        fflush(stdin);
        gets(customerIn.name);
        printf("\t\t\t\tEnter your password:\t");
        HidePassword(customerIn.password);
        fptrsign = fopen("signin_information.txt", "rb+");
        while (fread(&customerRd, sizeof(struct readUser), 1, fptrsign))
        {
            if (strcmp(customerIn.name, customerRd.name) == 0)
            {
                if (strcmp(customerIn.password, customerRd.password) == 0)
                {
                    printf("\n\n");
                    char presskey;
                    printf("\n\nSuccessfully logged in!!");
                    printf("\nWELCOME %s", customerRd.name);
                    printf("\n\nPress ENTER to continue, TAB to return to home page and any other key to exit the program....\n\n");
                    presskey = getch();
                    if (presskey == ENTER)
                    {
                    INVALID:
                        system("cls");
                        int choiceOfBanking;
                        printf("\n\n\t\t\t\t\t\t\t\t------------- BANKING SYSTEM -------------\n");
                        printf("\n\n%s\n%s", customerRd.name, customerRd.email);
                        printf("\n\n\t\t\t\t\t\t\t\t1.BALANCE INQUIRY\t\t2.TRANSFER\n\t\t\t\t\t\t\t\t3.DEPOSIT\t\t\t4.CHANGE PIN\n\t\t\t\t\t\t\t\t5.EXIT");
                        printf("\n\nEnter operation you want to perform: ");
                        scanf("%d", &choiceOfBanking);

                        if (choiceOfBanking == 1)
                        {
                            // balance inquiry
                        }
                        else if (choiceOfBanking == 2)
                        {
                            // tranfer
                        }
                        else if (choiceOfBanking == 3)
                        {
                            // deposit
                        }
                        else if (choiceOfBanking == 4)
                        {
                        }
                        else if (choiceOfBanking == 5)
                        {
                            exit(0);
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
                                exit(0);
                            }
                        }
                    }
                    else if (presskey == TAB)
                    {
                        goto HOMEPAGE;
                    }
                    else
                    {
                        exit(0);
                    }
                    printf("\n\n");
                }
            }
            else
            {
                printf("*");
            }
        }
        fclose(fptrsign);

        break;
    case 3:

        printf("\n\n\t\t\t\t\t\t\t\t------------- BANKING SYSTEM -------------\n");

        printf("\n\n\t\t\t\t\t\t\t\t1.SEARCH USER\t\t2.\n\t\t\t\t\t\t\t\t3.DEPOSIT\t\t\t4.CHANGE PIN\n\t\t\t\t\t\t\t\t5.EXIT");
        fptrsign = fopen("signin_information.txt", "rb+");
        printf("\n\n");
        printf("");
        while (fread(&customerRd, sizeof(struct readUser), 1, fptrsign))
        {
            printf("NAME:%s\nEMAIL:%s\nPASSWORD:%s\nPIN:%d\n\n", customerRd.name, customerRd.email, customerRd.password, customerRd.pin);
        }
        fclose(fptrsign);
        break;
    default:
        printf("Your option is invalid.");
    }

    return 0;
}
