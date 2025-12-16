#include <stdio.h>
#include <string.h>

struct Expense {
    char description[50];
    float amount;
    char category[20]; // category stored as string
};

int main() {
    FILE *fp;
    struct Expense exp;
    int choice, cat;

    while(1) {
        printf("\n===== MONTHLY EXPENSE TRACKER =====\n");
        printf("1. Add Daily Expense\n");
        printf("2. View Monthly Summary\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // ------------------------------------
        // ADD EXPENSE
        // ------------------------------------
        if(choice == 1) {
            fp = fopen("expenses.txt", "a");
            if(fp == NULL) {
                printf("Error opening file!\n");
                return 1;
            }

            printf("\nEnter description: ");
            scanf(" %[^\n]", exp.description);

            printf("Enter amount: ");
            scanf("%f", &exp.amount);

            printf("\nChoose Category:\n");
            printf("1. Lifestyle\n");
            printf("2. Basic Needs\n");
            printf("3. Secondary Expenses\n");
            printf("4. Investments\n");
            printf("Enter category: ");
            scanf("%d", &cat);

            // Convert number → string
            if(cat == 1) strcpy(exp.category, "Lifestyle");
            else if(cat == 2) strcpy(exp.category, "BasicNeeds");
            else if(cat == 3) strcpy(exp.category, "Secondary");
            else if(cat == 4) strcpy(exp.category, "Investments");
            else strcpy(exp.category, "Unknown");

            // Store string in file
            fprintf(fp, "%s %.2f %s\n", exp.description, exp.amount, exp.category);
            fclose(fp);

            printf("\nExpense Added Successfully!\n");
        }

        // ------------------------------------
        // VIEW SUMMARY
        // ------------------------------------
        else if(choice == 2) {
            fp = fopen("expenses.txt", "r");
            if(fp == NULL) {
                printf("No expenses found! Add data first.\n");
                continue;
            }

            float lifestyle = 0, basic = 0, secondary = 0, investment = 0;

            printf("\n---------- MONTHLY SUMMARY ----------\n");

            while(fscanf(fp, "%s %f %s", exp.description, &exp.amount, exp.category) != EOF) {
                if(strcmp(exp.category, "Lifestyle") == 0) lifestyle += exp.amount;
                else if(strcmp(exp.category, "BasicNeeds") == 0) basic += exp.amount;
                else if(strcmp(exp.category, "Secondary") == 0) secondary += exp.amount;
                else if(strcmp(exp.category, "Investments") == 0) investment += exp.amount;
            }

            fclose(fp);

            printf("Lifestyle Expenses: ₹%.2f\n", lifestyle);
            printf("Basic Needs: ₹%.2f\n", basic);
            printf("Secondary Expenses: ₹%.2f\n", secondary);
            printf("Investments: ₹%.2f\n", investment);

            printf("\nTotal Monthly Spending: ₹%.2f\n",
                lifestyle + basic + secondary + investment);
        }

        else if(choice == 3) {
            printf("Exiting... Thank You!\n");
            break;
        }

        else {
            printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}
