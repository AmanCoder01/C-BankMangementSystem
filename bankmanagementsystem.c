#include <stdio.h>
#include <windows.h>
#include <stdlib.h>

int main_exit;
void menu();

struct date
{
    int month, day, year;
};

struct AccountDetails
{
    char name[60];
    int acc_no, age;
    char address[60];
    double phone;
    char acc_type[10];
    float amt;
    struct date dob;
    struct date deposit;
    struct date withdraw;

} add, upd, check, rem, transaction;

void fordelay(int j)
{
    int i, k;
    for (i = 0; i < j; i++)
        k = i;
}

void close(void)
{
    printf("\n\nThis C Mini Project is developed by Aman and his team!");
}

float interest(float t, float amount, int rate)
{
    float SI;
    SI = (rate * t * amount) / 100.0;
    return (SI);
}

void new_account()
{
    int choice;
    FILE *ptr;

    ptr = fopen("record.dat", "a+");

account_no:
    system("cls");
    printf("\t\t\t\xB2\xB2\xB2 ADD RECORD  \xB2\xB2\xB2\xB2");
    printf("\n\n\nEnter today's date(dd/mm/yyyy):");
    scanf("%d/%d/%d", &add.deposit.day, &add.deposit.month, &add.deposit.year);
    printf("\nEnter the account number:");
    scanf("%d", &check.acc_no);

    while (fscanf(ptr, "%d %s %d/%d/%d %d %s %lf %s %f %d/%d/%d\n", &add.acc_no, add.name, &add.dob.day, &add.dob.month, &add.dob.year, &add.age, add.address, &add.phone, add.acc_type, &add.amt, &add.deposit.month, &add.deposit.day, &add.deposit.year) != EOF)
    {
        if (check.acc_no == add.acc_no)
        {
            printf("Account no. already in use!");
            fordelay(1000000000);
            goto account_no;
        }
    }

    add.acc_no = check.acc_no;
    printf("\nEnter the name:");
    scanf("%s", add.name);

    printf("\nEnter the date of birth(dd/mm/yyyy):");
    scanf("%d/%d/%d", &add.dob.day, &add.dob.month, &add.dob.year);

    printf("\nEnter the age:");
    scanf("%d", &add.age);

    printf("\nEnter the address:");
    scanf("%s", add.address);

    printf("\nEnter the phone number: ");
    scanf("%lf", &add.phone);

    printf("\nEnter the amount to deposit:$");
    scanf("%f", &add.amt);

    printf("\nType of account:\n\t#Saving\n\t#Current\n\n\tEnter your choice:");
    scanf("%s", add.acc_type);

    fprintf(ptr, "%d %s %d/%d/%d %d %s %lf %s %f %d/%d/%d\n", add.acc_no, add.name, add.dob.day, add.dob.month, add.dob.year, add.age, add.address, add.phone, add.acc_type, add.amt, add.deposit.day, add.deposit.month, add.deposit.year);

    fclose(ptr);
    printf("\nAccount created successfully!");

add_invalid:
    printf("\n\n\n\t\tEnter 1 to go to the main menu and 0 to exit:");
    scanf("%d", &main_exit);
    system("cls");
    if (main_exit == 1)
        menu();
    else if (main_exit == 0)
        close();
    else
    {
        printf("\nInvalid!\a");
        goto add_invalid;
    }
}

void see()
{
    int test = 0, rate;
    int choice;
    float time;
    float intrst;
    FILE *ptr;

    ptr = fopen("record.dat", "r");
    printf("Do you want to check by\n1.Account no\n2.Name\nEnter your choice:");
    scanf("%d", &choice);

    if (choice == 1)
    {
        printf("Enter the account number:");
        scanf("%d", &check.acc_no);

        while (fscanf(ptr, "%d %s %d/%d/%d %d %s %lf %s %f %d/%d/%d\n", &add.acc_no, add.name, &add.dob.day, &add.dob.month, &add.dob.year, &add.age, add.address, &add.phone, add.acc_type, &add.amt, &add.deposit.month, &add.deposit.day, &add.deposit.year) != EOF)
        {
            if (check.acc_no == add.acc_no)
            {
                system("cls");
                test = 1;

                printf("\nAccount NO.:%d\nName:%s \nDOB:%d/%d/%d \nAge:%d \nAddress:%s \nPhone number:%.0lf \nType Of Account:%s \nAmount deposited:$ %.2f \nDate Of Deposit:%d/%d/%d\n\n", add.acc_no, add.name, add.dob.month, add.dob.day, add.dob.year, add.age, add.address, add.phone, add.acc_type, add.amt, add.deposit.month, add.deposit.day, add.deposit.year);

                if (strcmpi(add.acc_type, "saving") == 0)
                {
                    time = (1.0 / 12.0);
                    rate = 8;
                    intrst = interest(time, add.amt, rate);
                    printf("\nYou will get $.%.2f as interest on %d of every month", intrst, add.deposit.day);
                }
                else if (strcmpi(add.acc_type, "current") == 0)
                {

                    printf("\n\nYou will get no interest\a\a");
                }
            }
        }
    }
}

void menu(void)
{
    int choice;

    system("cls");
    system("color 9");
    printf("\n\n\t\tCUSTOMER ACCOUNT BANKING MANAGEMENT SYSTEM");

    printf("\n\n\t\t1.Create new account\n\t\t2.Update information of existing account\n\t\t3.For transactions\n\t\t4.Check the details of existing account\n\t\t5.Removing existing account\n\t\t6.View customer's list\n\t\t7.Exit\n\n\n\t\t Enter your choice:");
    scanf("%d", &choice);

    system("cls");

    switch (choice)
    {
    case 1:
        new_account();
        break;
    case 4:
        see();
        break;
    case 7:
        close();
        break;
    }
}

int main()
{
    char pass[10];
    char password[10] = "gniot";

    printf("Enter the password to login: ");
    scanf("%s", pass);

    if (strcmp(pass, password) == 0)
    {
        printf("\n\nPassword Match!\nLOADING");
        for (int i = 0; i <= 6; i++)
        {
            fordelay(100000000);
            printf(".");
        }
        system("cls");
        menu();
    }
    else
    {
        printf("\n\nWrong password!!\a\a\a");

    login_try:
        printf("\nEnter 1 to try again and 0 to exit:");
        scanf("%d", &main_exit);

        if (main_exit == 1)
        {

            system("cls");
            main();
        }
        else if (main_exit == 0)
        {
            system("cls");
            close();
        }
        else
        {
            printf("\nInvalid!");
            fordelay(1000000000);
            system("cls");
            goto login_try;
        }
    }
}