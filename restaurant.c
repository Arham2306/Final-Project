#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#ifdef _WIN32 // Will work if running on 32-bit windows
#define CLEAR_SCREEN "cls"
#else
#define CLEAR_SCREEN "clear"
#endif

// RESTAURANT STRUCTURES

struct items
{
    char item[20];
    float price;
    int qty;
};

struct orders
{
    char customer[50];
    char date[50];
    int numOfItems;
    struct items itm[50];
};

// RESTAURANT STRUCTURES END

// functions to generate biils
void generateBillHeader(char name[50], char date[30])
{
    printf("\n\n");
    printf("\t    AHM. Restaurant");
    printf("\n\t   -----------------");
    printf("\nDate:%s", date);
    printf("\nInvoice To: %s", name);
    printf("\n");
    printf("---------------------------------------\n");
    printf("Items\t\t");
    printf("Qty\t\t");
    printf("Total\t\t");
    printf("\n---------------------------------------");
    printf("\n\n");
}
void generateBillBody(char item[30], int qty, float price)
{
    printf("%s\t\t", item);
    printf("%d\t\t", qty);
    printf("%.2f\t\t", qty * price);
    printf("\n");
}

void generateBillFooter(float total)
{
    printf("\n");
    float dis = 0.1 * total;
    float netTotal = total - dis;
    float cgst = 0.09 * netTotal, grandTotal = netTotal + 2 * cgst; // netTotal + cgst + sgst
    printf("---------------------------------------\n");
    printf("Sub Total\t\t\t%.2f", total);
    printf("\nDiscount @10%s\t\t\t%.2f", "%", dis);
    printf("\n\t\t\t\t-------");
    printf("\nNet Total\t\t\t%.2f", netTotal);
    printf("\nCGST @9%s\t\t\t%.2f", "%", cgst);
    printf("\nSGST @9%s\t\t\t%.2f", "%", cgst);
    printf("\n---------------------------------------");
    printf("\nGrand Total\t\t\t%.2f", grandTotal);
    printf("\n---------------------------------------\n");
}

// This is a function to authenticate admin or manager users
int authenticate(char inputUsername[50], char inputPassword[50], char expectedUsername[50], char expectedPassword[50])
{
    if (strcmp(expectedUsername, inputUsername) == 0 && strcmp(expectedPassword, inputPassword) == 0)
    {
        printf("\nLogin successful!\n");
        return 1;
    }
    else
    {
        printf("\nLogin failed. Incorrect username or password.\n");
        return 0;
    }
}

//    MANAGER OPERATIONS START HERE

struct employees
{
    int empID;
    char emp_name[50];
    int emp_salary;
    char emp_desg[50];
};

// EMPLOYEES DATA DISPLAY FUNCTION
void displayEmpData(int ID, char name[50], char desig[50], float salary)
{
    printf("%d\t\t", ID);
    printf("%s\t", name);
    printf("\t\t%s\t", desig);
    printf("\t\t%.2f", salary);
}

// Function to check if employee with same id exists
int employeeExists(int empID)
{
    FILE *fp = fopen("EmployeeData.txt", "r");
    if (fp != NULL)
    {
        struct employees empData;
        while (fread(&empData, sizeof(struct employees), 1, fp))
        {
            if (empData.empID == empID)
            {
                fclose(fp);
                return 1; // Employee with the given ID already exists
            }
        }
        fclose(fp);
    }
    return 0; // Employee with the given ID does not exist
}

void managerPage()
{

    int choice, noe;
    struct employees empData;
    struct employees employee;
    char save_emp = 'y';
    char cont_op = 'y';
    FILE *fp;
    do
    {
        printf("\n\n******** Employee Management System ******\n\n");
        printf("1. Add Employee\n");
        printf("2. Display Employees\n");
        printf("3. Search Employee\n");
        printf("4. Exit\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            system(CLEAR_SCREEN);
            printf("Enter Employee ID: ");
            scanf("%d", &empData.empID);
            getchar();

            if (employeeExists(empData.empID))
            {
                printf("Error: Employee with ID %d already exists.\n", empData.empID);
                break;
            }

            printf("\nEnter Employee Name: ");
            fgets(empData.emp_name, 50, stdin);
            empData.emp_name[strlen(empData.emp_name) - 1] = '\0';

            printf("\nEnter Employee Designation: ");
            fgets(empData.emp_desg, 50, stdin);
            empData.emp_desg[strlen(empData.emp_desg) - 1] = '\0';

            printf("\nEnter Employee Salary: ");
            scanf("%d", &empData.emp_salary);

            printf("\nDo you want to save the record [y/n]:\t");
            scanf(" %c", &save_emp);

            if (save_emp == 'y')
            {
                fp = fopen("EmployeeData.txt", "a+");
                fwrite(&empData, sizeof(struct employees), 1, fp);
                if (fwrite != 0)
                    printf("\nSuccessfully saved\n");
                else
                    printf("\nError saving");
                fclose(fp);
            }
            break;

        case 2:
            system(CLEAR_SCREEN);
            fp = fopen("EmployeeData.txt", "r");
            if (fp != NULL)
            {
                printf("\t****** EMPLOYEE DETAILS *****\n\n");
                printf("---------------------------------------------------------------------------------------\n");
                printf("ID\t\t");
                printf("Name\t");
                printf("\t\tDesignation");
                printf("\t\tSalary");
                printf("\n---------------------------------------------------------------------------------------\n");
                while (fread(&empData, sizeof(struct employees), 1, fp))
                {
                    displayEmpData(empData.empID, empData.emp_name,empData.emp_desg, empData.emp_salary);
                    printf("\n\n");
                }
                fclose(fp);
            }
            else
            {
                printf("\nError opening file for reading");
            }
            break;
        case 3:
        {
            system(CLEAR_SCREEN);
            printf("Enter Employee ID to search: ");
            int searchID;
            scanf("%d", &searchID);

            fp = fopen("EmployeeData.txt", "r");
            int found = 0;

            if (fp != NULL)
            {
                printf("\n\n");
                printf("****** EMPLOYEE DETAILS *****\n");
                printf("---------------------------------------------------------------------------------------\n");
                printf("ID\t\t");
                printf("Name\t");
                printf("\t\tDesignation");
                printf("\t\tSalary");
                printf("\n---------------------------------------------------------------------------------------\n");
                while (fread(&empData, sizeof(struct employees), 1, fp))
                {
                    if (empData.empID == searchID)
                    {

                        displayEmpData(empData.empID, empData.emp_name,empData.emp_desg, empData.emp_salary);
                        printf("\n");
                        found = 1;
                        break; // Stops searching after finding the employee
                    }
                }

                fclose(fp);

                if (!found)
                {
                    printf("\nEmployee with ID %d not found.\n", searchID);
                }
            }
            else
            {
                printf("\nError opening file for reading");
            }
            break;
        }
        printf("\nDo you want to perform another operation?[y/n]:\t");
        scanf("%s", &cont_op);

        case 4:
            system(CLEAR_SCREEN);
            printf("Exiting program.\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 4);
    
}

//    MANAGER OPERATIONS START HERE

// ADMIN OPERATIONS START HERE

void adminPage()
{
    int opt, n;
    struct orders ord;
    struct orders order;
    char saveBill = 'y', contFlag = 'y';
    char name[50];
    FILE *fp;
    while (contFlag == 'y')
    {
        system(CLEAR_SCREEN);
        float total = 0;
        int invoiceFound = 0;

        printf("\t============AHM. RESTAURANT============");
        printf("\n\nPlease select your preferred operation");
        printf("\n\n1.Generate Invoice");
        printf("\n2.Show all Invoices");
        printf("\n3.Search Invoice");
        printf("\n4.Exit");

        printf("\n\nYour choice:\t");
        scanf("%d", &opt);
        fgetc(stdin);

        switch (opt)
        {
        case 1:
            system(CLEAR_SCREEN);
            printf("\nPlease enter the name of the customer:\t");
            fgets(ord.customer, 50, stdin);
            ord.customer[strlen(ord.customer) - 1] = 0;

            // Get the current time
            time_t t;
            time(&t);

            // Format the time and copy it to ord.date
            struct tm *currentDate = localtime(&t);
            strftime(ord.date, sizeof(ord.date), "%Y-%m-%d", currentDate);

            printf("\nPlease enter the number of items:\t");
            scanf("%d", &n);
            ord.numOfItems = n;

            for (int i = 0; i < n; i++)
            {
                fgetc(stdin);
                printf("\n\n");
                printf("Please enter the item %d:\t", i + 1);
                fgets(ord.itm[i].item, 20, stdin);
                ord.itm[i].item[strlen(ord.itm[i].item) - 1] = 0; // we do this to read all the characters and break when there is a null character
                printf("Please enter the quantity:\t");
                scanf("%d", &ord.itm[i].qty);
                printf("Please enter the unit price:\t");
                scanf("%f", &ord.itm[i].price);
                total += ord.itm[i].qty * ord.itm[i].price;
            }

            generateBillHeader(ord.customer, ord.date);
            for (int i = 0; i < ord.numOfItems; i++)
            {
                generateBillBody(ord.itm[i].item, ord.itm[i].qty, ord.itm[i].price);
            }
            generateBillFooter(total);

            printf("\nDo you want to save the invoice [y/n]:\t");
            scanf(" %c", &saveBill); // We used %c here with a space instead of %s because we are only inputting a single character

            if (saveBill == 'y')
            {
                fp = fopen("RestaurantBill.txt", "a+");
                fwrite(&ord, sizeof(struct orders), 1, fp); // This line reads the size of the characters or values that were input in the variables of the structure.
                if (fwrite != 0)
                    printf("\nSuccessfully saved\n");
                else
                    printf("\nError saving");
                fclose(fp);
            }
            break;

        case 2:
            system(CLEAR_SCREEN);
            fp = fopen("RestaurantBill.txt", "r");
            printf("\n  Your Previous Invoices\n");
            while (fread(&order, sizeof(struct orders), 1, fp))
            {
                float tot = 0;
                generateBillHeader(order.customer, order.date);
                for (int i = 0; i < order.numOfItems; i++)
                {
                    generateBillBody(order.itm[i].item, order.itm[i].qty, order.itm[i].price);
                    tot += order.itm[i].qty * order.itm[i].price;
                }
                generateBillFooter(tot);
            }
            fclose(fp);
            break;

        case 3:
            printf("Enter the name of the customer:\t");
            fgets(name, 50, stdin);
            name[strlen(name) - 1] = 0;
            system(CLEAR_SCREEN);
            fp = fopen("RestaurantBill.txt", "r");
            printf("\t*Invoice of %s*", name);
            while (fread(&order, sizeof(struct orders), 1, fp))
            {
                float tot = 0;
                if (!strcmp(order.customer, name))
                {
                    generateBillHeader(order.customer, order.date);
                    for (int i = 0; i < order.numOfItems; i++)
                    {
                        generateBillBody(order.itm[i].item, order.itm[i].qty, order.itm[i].price);
                        tot += order.itm[i].qty * order.itm[i].price;
                    }
                    generateBillFooter(tot);
                    invoiceFound = 1;
                }
            }
            if (!invoiceFound)
            {
                printf("Sorry the invoice for %s doesnot exists", name);
            }
            fclose(fp);
            break;

        case 4:
            printf("\n\t\t Bye Bye :)\n\n");
            exit(0);
            break;

        default:
            printf("Sorry invalid option");
            break;
        }
        printf("\nDo you want to perform another operation?[y/n]:\t");
        scanf("%s", &contFlag);
    }
    printf("\n\t\t Bye Bye :)\n\n");
    printf("\n\n");
}

// ADMIN OPERATIONS END HERE

// MAIN CODE

int main()
{
    char managerUsername[50] = "manager";
    char managerPassword[50] = "manager@123";
    char adminUsername[50] = "admin";
    char adminPassword[50] = "admin@123";

    char inputUsername[50];
    char inputPassword[50];

    printf("\tWelcome to the AHM Restaurant\n");

    printf("\n\tEnter your username: ");
    fgets(inputUsername, 50, stdin);
    inputUsername[strlen(inputUsername) - 1] = 0;

    printf("\tEnter your password: ");
    fgets(inputPassword, 50, stdin);
    inputPassword[strlen(inputPassword) - 1] = 0;

    if (authenticate(inputUsername, inputPassword, managerUsername, managerPassword))
    {
        managerPage();
    }
    else if (authenticate(inputUsername, inputPassword, adminUsername, adminPassword))
    {
        adminPage();
    }
    else
    {
        printf("Exiting...\n");
    }

    return 0;
}

// MAIN CODE END