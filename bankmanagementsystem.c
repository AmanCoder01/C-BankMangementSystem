#include <stdio.h>
#include <windows.h>
#include <stdlib.h>

int main_exit;
void menu();

// -> Structure to store date-----------------------------------------------------------
struct date
{
    int month, day, year;
};

// -> Structure to store account details------------------------------------------------
struct AccountDetails
{
    char name[60];
    double acc_no;
    int age;
    char address[60];
    double phone;
    char acc_type[10];
    float amt;
    struct date dob;
    struct date deposit;
    struct date withdraw;

} add, check, rem, transac;

// -> Delay function to delay the program-----------------------------------------------
void fordelay(int j)
{
    int i, k;
    for (i = 0; i < j; i++)
        k = i;
}

// -> Close function to exit the program------------------------------------------------
void close(void)
{
    printf("\n\nThis C Mini Project is developed by Aman and his team!");
}

// -> Interest function to calculate interest--------------------------------------------
float interest(float t, float amount, int rate)
{
    float SI;
    SI = (rate * t * amount) / 100.0;
    return (SI);
}

// -> Menu 1 Option to create new account-----------------------------------------------
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
    scanf("%lf", &check.acc_no);

    while (fscanf(ptr, "%lf %s %d/%d/%d %d %s %lf %s %f %d/%d/%d\n", &add.acc_no, add.name, &add.dob.day, &add.dob.month, &add.dob.year, &add.age, add.address, &add.phone, add.acc_type, &add.amt, &add.deposit.day, &add.deposit.month, &add.deposit.year) != EOF)
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

    printf("\nEnter the amount to deposit:INR ");
    scanf("%f", &add.amt);

    printf("\nType of account:\n\t#Saving\n\t#Current\n\n\tEnter your choice:");
    scanf("%s", add.acc_type);

    fprintf(ptr, "%lf %s %d/%d/%d %d %s %lf %s %f %d/%d/%d\n", add.acc_no, add.name, add.dob.day, add.dob.month, add.dob.year, add.age, add.address, add.phone, add.acc_type, add.amt, add.deposit.day, add.deposit.month, add.deposit.year);

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

// -> Menu 2 Option to do transactions--------------------------------------------------
void transaction()
{
    int choice, test = 0;
    FILE *old, *newrec;
    old = fopen("record.dat", "r");
    newrec = fopen("new.dat", "w");

    printf("Enter the account no. of the customer:");
    scanf("%lf", &transac.acc_no);

    while (fscanf(old, "%lf %s %d/%d/%d %d %s %lf %s %f %d/%d/%d\n", &add.acc_no, add.name, &add.dob.day, &add.dob.month, &add.dob.year, &add.age, add.address, &add.phone, add.acc_type, &add.amt, &add.deposit.day, &add.deposit.month, &add.deposit.year) != EOF)
    {

        if (add.acc_no == transac.acc_no)
        {
            test = 1;
        transac_choice:
            printf("\n\nDo you want to\n1.Deposit\n2.Withdraw?\n\nEnter your choice(1 for deposit and 2 for withdraw):");
            scanf("%d", &choice);

            if (choice == 1)
            {
                printf("Enter the amount you want to deposit:INR ");
                scanf("%f", &transac.amt);

                add.amt = add.amt + transac.amt;

                fprintf(newrec, "%lf %s %d/%d/%d %d %s %lf %s %f %d/%d/%d\n", add.acc_no, add.name, add.dob.day, add.dob.month, add.dob.year, add.age, add.address, add.phone, add.acc_type, add.amt, add.deposit.day, add.deposit.month, add.deposit.year);

                printf("\n\nDeposited successfully!");
            }
            else if (choice == 2)
            {
                printf("Enter the amount you want to withdraw:INR ");
                scanf("%f", &transac.amt);

                if (transac.amt > add.amt || transac.amt < 0)
                {
                    system("cls");
                    printf("\nInsufficient balance!\a");
                    goto transac_choice;
                }

                add.amt = add.amt - transac.amt;

                fprintf(newrec, "%lf %s %d/%d/%d %d %s %lf %s %f %d/%d/%d\n", add.acc_no, add.name, add.dob.day, add.dob.month, add.dob.year, add.age, add.address, add.phone, add.acc_type, add.amt, add.deposit.day, add.deposit.month, add.deposit.year);
                printf("\n\nWithdrawn successfully!");
            }
            else
            {
                system("cls");
                printf("\nInvalid choice!\a");
                goto transac_choice;
            }
        }
        else
        {
            fprintf(newrec, "%lf %s %d/%d/%d %d %s %lf %s %f %d/%d/%d\n", add.acc_no, add.name, add.dob.day, add.dob.month, add.dob.year, add.age, add.address, add.phone, add.acc_type, add.amt, add.deposit.day, add.deposit.month, add.deposit.year);
        }
    }

    fclose(old);
    fclose(newrec);
    remove("record.dat");
    rename("new.dat", "record.dat");
    if (test != 1)
    {
        printf("\n\nRecord not found!!");
    transact_invalid:
        printf("\n\n\nEnter 0 to try again,1 to return to main menu and 2 to exit:");
        scanf("%d", &main_exit);
        system("cls");
        if (main_exit == 0)
            transaction();
        else if (main_exit == 1)
            menu();
        else if (main_exit == 2)
            close();
        else
        {
            printf("\nInvalid!");
            goto transact_invalid;
        }
    }
    else
    {
        printf("\nEnter 1 to go to the main menu and 0 to exit:");
        scanf("%d", &main_exit);
        system("cls");
        if (main_exit == 1)
            menu();
        else
            close();
    }
}

// -> Menu 3 Option to check details of existing account---------------------------------
void see()
{
    int test = 0, rate;
    float time;
    float intrst;
    FILE *ptr;

    ptr = fopen("record.dat", "r");

    printf("Enter your account number: ");
    scanf("%lf", &check.acc_no);

    while (fscanf(ptr, "%lf %s %d/%d/%d %d %s %lf %s %f %d/%d/%d\n", &add.acc_no, add.name, &add.dob.day, &add.dob.month, &add.dob.year, &add.age, add.address, &add.phone, add.acc_type, &add.amt, &add.deposit.day, &add.deposit.month, &add.deposit.year) != EOF)
    {
        if (check.acc_no == add.acc_no)
        {
            system("cls");
            test = 1;

            printf("\nAccount NO.:%lf\nName:%s \nDOB:%d/%d/%d \nAge:%d \nAddress:%s \nPhone number:%.0lf \nType Of Account:%s \nAvailable Amount:INR  %.2f \nDate Of Deposit:%d/%d/%d\n", add.acc_no, add.name, add.dob.month, add.dob.day, add.dob.year, add.age, add.address, add.phone, add.acc_type, add.amt, add.deposit.day, add.deposit.month, add.deposit.year);

            if (strcmpi(add.acc_type, "saving") == 0)
            {
                time = (1.0 / 12.0);
                rate = 8;
                intrst = interest(time, add.amt, rate);
                printf("\nYou will get INR %.2f as interest on %d of every month", intrst, add.deposit.day);
            }
            else if (strcmpi(add.acc_type, "current") == 0)
            {

                printf("\nYou will get no interest\a\a");
            }
        }
    }

    fclose(ptr);

    if (test != 1)
    {
        system("cls");
        printf("\nRecord not found!!\a\a\a");
    see_invalid:
        printf("\nEnter 0 to try again,1 to return to main menu and 2 to exit:");
        scanf("%d", &main_exit);
        system("cls");
        if (main_exit == 1)
            menu();
        else if (main_exit == 2)
            close();
        else if (main_exit == 0)
            see();
        else
        {
            system("cls");
            printf("\nInvalid!\a");
            goto see_invalid;
        }
    }
    else
    {
        printf("\nEnter 1 to go to the main menu and 0 to exit:");
        scanf("%d", &main_exit);
    }
    if (main_exit == 1)
    {
        system("cls");
        menu();
    }

    else
    {
        system("cls");
        close();
    }
}

// -> Menu 4 Option to remove existing account-------------------------------------------
void erase()
{
    FILE *olf, *newrec;
    int test = 0;
    olf = fopen("record.dat", "r");
    newrec = fopen("new.dat", "w");
    printf("Enter the account no. of the customer you want to delete:");
    scanf("%lf", &rem.acc_no);

    while (fscanf(olf, "%lf %s %d/%d/%d %d %s %lf %s %f %d/%d/%d", &add.acc_no, add.name, &add.dob.day, &add.dob.month, &add.dob.year, &add.age, add.address, &add.phone, add.acc_type, &add.amt, &add.deposit.day, &add.deposit.month, &add.deposit.year) != EOF)
    {
        if (add.acc_no != rem.acc_no)
            fprintf(newrec, "%lf %s %d/%d/%d %d %s %lf %s %f %d/%d/%d\n", add.acc_no, add.name, add.dob.day, add.dob.month, add.dob.year, add.age, add.address, add.phone, add.acc_type, add.amt, add.deposit.day, add.deposit.month, add.deposit.year);

        else
        {
            test++;
            printf("\nRecord deleted successfully!\n");
        }
    }
    fclose(olf);
    fclose(newrec);
    remove("record.dat");
    rename("new.dat", "record.dat");
    if (test == 0)
    {
        printf("\nRecord not found!!\a\a\a");
    erase_invalid:
        printf("\nEnter 0 to try again,1 to return to main menu and 2 to exit:");
        scanf("%d", &main_exit);

        if (main_exit == 1)
            menu();
        else if (main_exit == 2)
            close();
        else if (main_exit == 0)
            erase();
        else
        {
            printf("\nInvalid!\a");
            goto erase_invalid;
        }
    }
    else
    {
        printf("\nEnter 1 to go to the main menu and 0 to exit:");
        scanf("%d", &main_exit);
        system("cls");
        if (main_exit == 1)
            menu();
        else
            close();
    }
}

// -> Menu 5 Option to view list of customers-------------------------------------------
void view_list()
{
    FILE *view;
    view = fopen("record.dat", "r");
    int test = 0;
    system("cls");
    printf("\nACC. NO.\t\tNAME\t\tADDRESS\t\t\tPHONE\n");

    while (fscanf(view, "%lf %s %d/%d/%d %d %s %lf %s %f %d/%d/%d", &add.acc_no, add.name, &add.dob.day, &add.dob.month, &add.dob.year, &add.age, add.address, &add.phone, add.acc_type, &add.amt, &add.deposit.day, &add.deposit.month, &add.deposit.year) != EOF)
    {
        test = 1;
        printf("\n%10.0lf\t %10s\t\t%10s\t\t%.0lf", add.acc_no, add.name, add.address, add.phone);
        test++;
    }

    fclose(view);
    if (test == 0)
    {
        system("cls");
        printf("\nNO RECORDS!!\n");
    }

view_list_invalid:
    printf("\n\nEnter 1 to go to the main menu and 0 to exit:");
    scanf("%d", &main_exit);
    system("cls");
    if (main_exit == 1)
        menu();
    else if (main_exit == 0)
        close();
    else
    {
        printf("\nInvalid!\a");
        goto view_list_invalid;
    }
}

// ->Menu Options-----------------------------------------------------------------------
void menu()
{
    int choice;

    system("cls");
    system("color 9");
    printf("\n\n\t\tCUSTOMER ACCOUNT BANKING MANAGEMENT SYSTEM");

    printf("\n\n\t\t1.Create new account\n\t\t2.For transactions\n\t\t3.Check the details of existing account\n\t\t4.Removing existing account\n\t\t5.View customer's list\n\t\t6.Exit\n\n\n\t\t Enter your choice:");
    scanf("%d", &choice);

    system("cls");

    switch (choice)
    {
    case 1:
        new_account();
        break;
    case 2:
        transaction();
        break;
    case 3:
        see();
        break;
    case 4:
        erase();
        break;
    case 5:
        view_list();
        break;
    case 6:
        close();
        break;
    }
}

// -> Main Function---------------------------------------------------------------------
int main()
{
    char pass[10];
    char password[10] = "gniot"; // password to access bank management system

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