#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#define ENTER 13
#define TAB 9
#define BCKSPC 8

struct user
{
    char name[20];
    char phone[10];
    char ac[10];
    char password[10];
    float balance;
};

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

    struct user user, usr;
    char filename[50], phone[50], password[50], phone2[10];
    FILE *fp, *fptr;
    int opt, choice;
    int amount;
    char cont = 'y';
HOMEPAGE:
    system("clear");
    printf("\n\n\t\t\t\t\t\t\t\t------------- BANKING SYSTEM -------------\n");
    printf("\n\n------------- HOMEPAGE PAGE -------------\n\n");
    printf("\t   1. SignUp\n");
    printf("\t   2. Log in\n");
    printf("\t   3. Exit\n");

    printf("\n\nPlease enter your choice:\t");
    scanf("%d", &opt);
    if (opt == 1)
    {
        char pass[10];
        char choiceOfOption;
        // system("clear");
        printf("\n\t\t\tEnter your account number:\t");
        scanf("%s", user.ac);
        fflush(stdin);
        printf("\n\t\t\tEnter your  Username:\t\t");
        gets(user.name);
        fflush(stdin);
        printf("\n\t\t\tEnter your phone number:\t");
        scanf("%s", user.phone);
        fflush(stdin);
        printf("\n\t\t\tEnter your new password:\t");
        HidePassword(user.password);
        printf("\n\n\t\t\tConfirm your password:\t\t");
        HidePassword(pass);

        if (strcmp(pass, user.password) == 0)
        {
            user.balance = 0;
            strcpy(filename, user.phone);
            fp = fopen(strcat(filename, ".dat"), "w");
            fwrite(&user, sizeof(user), 1, fp);
            if (fwrite != 0)
            {
                printf("\n\nSuccesfully registered");
            }
            fclose(fp);
        }
        else
        {
            printf("\nPassword didn't matched.");
            printf("\nAccess not granted");
            Beep(750, 350); // it takes two arguments frequency and time in ms
        }
        printf("\nDo you want to perform any other task[y/n]:\t");
        choiceOfOption = getchar();
        if (choiceOfOption == 'y' || choiceOfOption == 'Y')
        {
            goto HOMEPAGE;
        }
        else
        {
            exit(1);
        }
    }
    else if (opt == 2)
    {
        // system("clear");
        printf("\n\t\t\tPhone No.:\t");
        scanf("%s", phone);
        fflush(stdin);
        printf("\n\t\t\tPassword:\t");
        HidePassword(password);
        fp = fopen(strcat(phone, ".dat"), "r");
        if (fp == NULL)
            printf("Account number not registered");
        else
        {
            fread(&user, sizeof(struct user), 1, fp);
            fclose(fp);
            if (!strcmp(password, user.password))
            {
                while (cont == 'y')
                {
                    system("clear");
                    printf("\n\nSuccessfully logged in!!");
                    printf("\n\n\n\tWelcome %s", user.name);

                    printf("\n\n\t\t\t\t\t\t\t\t------------- BANKING SYSTEM -------------\n");
                    printf("\n\n%s\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t%.2f\n%s", user.name, user.balance, user.phone);
                    printf("\n\n\t\t\t\t\t\t\t\t1.DEPOSIT\t\t2.WITHDRAW\n\t\t\t\t\t\t\t\t3.TRANSFER\t\t4.CHANGE PASSWORD\n\t\t\t\t\t\t\t\t5.EXIT");
                    printf("\n\nEnter operation you want to perform:\t");
                    scanf("%d", &choice);
                    switch (choice)
                    {
                    case 1:
                        //   system("clear");
                        printf("\n\t\t\tEnter amount to be added:\t");
                        scanf("%d", &amount);
                        user.balance += amount;
                        fp = fopen(phone, "w");
                        fwrite(&user, sizeof(struct user), 1, fp);
                        if (fwrite != 0)
                            printf("\n\nYou have depostied Rs.%d", amount);
                        fclose(fp);
                        break;

                    case 2:

                        // system("clear");
                        printf("\n\t\t\tEnter withdrawl amount:\t");
                        scanf("%d", &amount);
                        if (amount % 500 != 0)
                            printf("\nSorry amount should be multiple of 500");
                        else if (amount > user.balance)
                            printf("\nSorry insufficeint balance");
                        else
                        {
                            user.balance -= amount;
                            fp = fopen(phone, "w");
                            fwrite(&user, sizeof(struct user), 1, fp);
                            if (fwrite != 0)
                                printf("\n\n\t\t\tYou have withdrawn Rs.%d", amount);
                            fclose(fp);
                        }
                        break;

                    case 3:
                        printf("\n\t\t\tPlease enter the phone number to trasnfer balance:\t");
                        scanf("%s", phone);
                        printf("\n\t\t\tEnter the amount to transfer:\t");
                        scanf("%d", &amount);
                        if (amount > user.balance)
                            printf("\nSorry insufficent balance");
                        else
                        {
                            fptr = fopen(strcat(phone, ".dat"), "r");
                            if (fptr == NULL)
                                printf("\n\nSorry number is not registered");
                            else
                            {
                                fread(&usr, sizeof(struct user), 1, fptr);
                                fclose(fptr);

                                usr.balance += amount;

                                fptr = fopen(strcat(phone, ".dat"), "w");
                                fwrite(&usr, sizeof(struct user), 1, fptr);
                                if (fwrite != 0)
                                {
                                    printf("\n\t\t\tYour trasfer is completed. You have trasnfered Rs.%d to %s", amount, usr.phone);
                                    fclose(fptr);
                                    user.balance -= amount;
                                    strcpy(filename, user.phone);
                                    fp = fopen(strcat(filename, ".dat"), "w");
                                    fwrite(&user, sizeof(struct user), 1, fp);
                                    fclose(fp);
                                }
                            }
                        }
                        break;
                    case 4:
                        printf("\n\n\t\t\tPlease enter your old password:\t");
                        HidePassword(password);
                        if (!strcmp(password, user.password))
                        {
                            printf("\n\n\t\t\tPlease enter your new password:\t");
                            HidePassword(password);
                            strcpy(user.password, password);
                            strcpy(filename, user.phone);
                            fp = fopen(strcat(filename, ".dat"), "w");
                            fwrite(&user, sizeof(struct user), 1, fp);
                            fclose(fp);
                            printf("\nPassword succesfullly changed");
                        }
                        else
                        {
                            printf("\nSorry your password is wrong");
                        }

                    case 5:
                        exit(1);
                        break;
                    default:
                        break;
                    } // switch ends here
                    printf("\n\nDo you want to continue?[y/n]:\t");
                    scanf("%s", &cont);
                }
            }
            else
            {
                printf("\n\nInvalid password");
            }
        }
        printf("\n\n***Thank you for banking with US***\n\n");
    }
    else
    {
        exit(1);
    }

    return 0;
}