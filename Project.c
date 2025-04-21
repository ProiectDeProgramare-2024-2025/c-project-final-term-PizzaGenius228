#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>



typedef struct {
    int orderID[100];
    char userName[20];
    char restaurant[50];
    char items[512];
    char location[100];
    char dateTime[20];
} Order;

Order orderHistory[100]; //storing order history
int orderCount = 0;
char deliveryAdress[100] = "";
int order_number;

struct pizza{
    char size[4]; //S (small), M (medium), L (large), XL (extra-large), XXL (extra-extra large)
    char toppings[256]; 
    char sauces[256];
    char pizza_name[50];
    double Price;
} P1[50];

struct burger{
    char burger_name[50];
}burger1[50];

struct Pasta{
    char pasta_name[50];
}pasta1[50];


void SystemClear()
{
    system("cls");
}

void loadOrdersFromFile() {
    FILE* file = fopen("orders.txt", "r");
    if (file == NULL) {
        printf("No order history found.\n");
        return;
    }

    char line[512];
    orderCount = 0;
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "--------", 8) == 0) continue;
        sscanf(line, "%d,%[^,],%[^,],%[^,],%[^,],%[^\n]",
               &orderHistory[orderCount].orderID[0],
               orderHistory[orderCount].userName,
               orderHistory[orderCount].restaurant,
               orderHistory[orderCount].items,
               orderHistory[orderCount].location,
               orderHistory[orderCount].dateTime);
        orderCount++;
    }
    fclose(file);
    printf("Orders loaded successfully.\n");
}


void header()
{
    SystemClear();
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
    printf("Welcome to \" Food Delivery System \"\n\n");
    printf("Please choose a partner Restaurant to see their menu:\n\n");
    printf("1 - El Diablo\n");
    printf("2 - Mind Space\n");
    printf("3 - Taglatele\n");
    printf("4 - Crazy Pizza\n");
    printf("5 - Indian Bistro\n");
    printf("6 - Review Odrer History\n");
    printf("7 - Load From File\n");
    printf("0 - EXIT\n\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
}

void getAdress()
{
    // if i would like to order food at different addresses, i have to comment out the if. Otherwise, the address will be saved.
    SystemClear();
    char name[50] = "";
    printf("Enter Your Name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

     if(strlen(deliveryAdress) == 0)
     {
    strcpy(orderHistory[orderCount].userName, name);
    printf("\nPlease enter your delivery adress:");
    fgets(deliveryAdress, sizeof(deliveryAdress), stdin);
    deliveryAdress[strcspn(deliveryAdress, "\n")] = '\0';
    printf("Adress Saved Successfully!\n");
    }
}

// void loadOrdersFromFile() {
//     FILE* file = fopen("C:\\Users\\sosim\\Desktop\\test\\c-project-menu-PizzaGenius228\\orders_history.txt", "r");
//     if (!file) {
//         printf("No existing orders found. Starting fresh.\n");
//         return;
//     }
//     while (fscanf(file, "%d. Name: %s, Restaurant: %s, Item Ordered: %s, Address: %s, Date: %s\n",
//                   orderCount, orderHistory[orderCount].userName,
//                   orderHistory[orderCount].restaurant, orderHistory[orderCount].items,
//                   orderHistory[orderCount].location, orderHistory[orderCount].dateTime) != EOF) {
//         orderCount++;
//     }
//     fclose(file);
// }

// void saveAllOrdersToFile() {
//     FILE* file = fopen("orders_history.txt", "w");
//     if (!file) {
//         printf("Failed to open file for writing");
//         return;
//     }
//     for (int i = 0; i < orderCount; i++) {
//         fprintf(file, "%d. Name: %s, Restaurant: %s, Item Ordered: %s, Address: %s, Date: %s\n",
//                 orderHistory[i].orderID, orderHistory[i].userName, orderHistory[i].restaurant,
//                 orderHistory[i].items, orderHistory[i].location, orderHistory[i].dateTime);
//     }
//     fclose(file);
// }

// void displayMenuFromFile(const char* restaurant, const char* fileName)
// {
//     FILE * file; 
//     file = fopen(fileName, "r");
//     if(file == NULL)
//     {
//         printf("Error: Unable to open the menu file for %s.\n", restaurant);
//         return;
//     }
//     char line[256];
//     while(fgets(line, sizeof(line), file))
//         printf("%s", line); //print each line from the file
//     fclose(file);
// }

void placeOrder(const char* restaurant)
{
    SystemClear();
    getAdress();
    time_t t = time(NULL);
    struct tm* date = localtime(&t);
    char formattedTime[20];
    snprintf(formattedTime, sizeof(formattedTime), "%02d/%02d/%04d %02d:%02d", date->tm_mday, date->tm_mon + 1, date->tm_year + 1900, date->tm_hour, date->tm_min);

    
    strcpy(orderHistory[orderCount].restaurant, restaurant);
    strcpy(orderHistory[orderCount].location, deliveryAdress);
    strcpy(orderHistory[orderCount].dateTime, formattedTime);
    orderHistory[orderCount].orderID[0] = orderCount;
    
    FILE* file = fopen("orders.txt", "a");
    static char lastDate[20] = ""; //for holding the last date written
    if(strcmp(lastDate, orderHistory->dateTime) != 0)
        {
            strcpy(lastDate, orderHistory->dateTime);
            fprintf(file, "-------- Orders from %s --------\n", lastDate);
        }
    if (file != NULL) {
        fprintf(file, "%d,%s,%s,%s,%s,%s\n",
                orderHistory[orderCount].orderID[0],
                orderHistory[orderCount].userName,
                orderHistory[orderCount].restaurant,
                orderHistory[orderCount].items,
                orderHistory[orderCount].location,
                orderHistory[orderCount].dateTime);
        fclose(file);
    } else {
        perror("Failed to open file");
    }

    orderCount++;
    printf("Order Placed Successfully!\n");
}

void viewOrders()
{
    int ret = 0;

    SystemClear();

    if(orderCount == 0)
    {
        printf("\nNo previous orders!\n");
        return;
    }

    printf("\nOrder History: \n");

    for(int i=0; i < orderCount; i++)
    {
        printf("\nOrder ID: %d\n", orderHistory[i].orderID);
        printf("User Name: %s\n", orderHistory[i].userName);
        printf("Restaurant: %s\n", orderHistory[i].restaurant);
        printf("Items ordered: %s\n", orderHistory[i].items);
        printf("Delivery Address: %s\n", orderHistory[i].location);
        printf("Order Time: %s\n", orderHistory[i].dateTime);
    }

    printf("If you would like to go back to Restaurnat List, press 1.\n Enter Choice: ");
    scanf("%d", &ret);
    if(ret == 1)
        header();

}

void customize_pizza(int customize)
{
    char size[4], toppings[256], sauces[256];

    SystemClear();

    printf("Choose Size: S - Small, M - Medium, L - Large, XL - Extra Large, XXL - Extra Extra Large \nEnter Option: ");
    scanf("%s", size);
    getchar();
    strcpy(P1[orderCount].size, size);
    if(customize)
    {
        printf("Toppings: Corn, Pepperoni, Chili, Chicken Breast, Pickels, Olives. YOU CAN ONLY CHOOSE 3 TOPPINGS!\nIf you don't want toppings, press enter to skip...\n");
        
        fgets(toppings, sizeof(toppings), stdin);
        strcpy(toppings, strlwr(toppings));
        toppings[strcspn(toppings, "\n")] = '\0';  //searching index of \n and replacing it with \0
        strcpy(P1[orderCount].toppings, toppings);
        
        printf("Sauces: Ketchup, Mayonnaise, Mustard, Hot Sauce, Sour Souce.\nYOU CAN ONLY CHOOSE 2 SAUCES!\nIf you don't want sauces, press enter to skip...\n");
        fgets(sauces, sizeof(sauces), stdin);
        strcpy(sauces, strlwr(sauces));
        sauces[strcspn(sauces, "\n")] = '\0';
        strcpy(P1[orderCount].sauces, sauces);
    }
            
}

int Meniu_El_diablo(int nr)
{
    int b, customize = 0;
    char answer;

    SystemClear();

    switch (nr)
    {
        if(nr == 6)
            break;
        case 1:
            printf("1. Pizza Diavola - Ingredients: Dough, Tomato sauce, pepperoni, Chilli \n");
            printf("2. Pizza Americana - Ingredients: Dough, Tomato sauce, Corn, Ham \n");
            printf("3. Pizza Prosciutto - Ingredients: Dough, Tomato sauce, Ham, Mushrooms, Olives \n");
            printf("4. Pizza Hawaii - Ingredients: Dough, Tomato sauce, Ananas, Ham \n");
            printf("5. Back\n");
            printf("Choose pizza: ");
            scanf("%d", &b);
            getchar();
            if(b == 5)
                break;
            SystemClear();
            printf("Do you want to customize your pizza?(Y/N): ");
            scanf("%c", &answer);
            answer = tolower(answer);
            if(answer == 'y')
                customize = 1;

            switch (b)
            {
                case 1:
                    SystemClear();
                    customize_pizza(customize);
                    strcpy(P1[orderCount].pizza_name, "Pizza Diavola");
                    P1[orderCount].Price += 50;
                    if(customize) 
                        strcat(P1[orderCount].pizza_name, " Customized: \nSize: ");
                    else strcat(P1[orderCount].pizza_name, "\nSize:");
                    break;
                case 2: 
                    customize_pizza(customize);
                    strcpy(P1[orderCount].pizza_name, "Pizza Americana");
                    if(customize) 
                        strcat(P1[orderCount].pizza_name, " Customized: \nSize: ");
                    else strcat(P1[orderCount].pizza_name, "\nSize:");
                    break;
                case 3: 
                    customize_pizza(customize);
                    strcpy(P1[orderCount].pizza_name, "Pizza Prosciutto");
                    if(customize) 
                        strcat(P1[orderCount].pizza_name, " Customized: \nSize: ");
                    else strcat(P1[orderCount].pizza_name, "\nSize:");
                    break;
                case 4: 
                    customize_pizza(customize);
                    strcpy(P1[orderCount].pizza_name, "Pizza Hawaii");
                    if(customize) 
                        strcat(P1[orderCount].pizza_name, " Customized: \nSize: ");
                    else strcat(P1[orderCount].pizza_name, "\nSize:");
                    break;
                default:
                    printf("Invalid choice!");
                    // there might be a problem here, might escape without ordering a pizza
                    break;
            }
            strcpy(orderHistory[orderCount].items, P1[orderCount].pizza_name);
            strcat(orderHistory[orderCount].items, P1[orderCount].size);
            

            if(strlen(P1[orderCount].toppings))
            {
                strcat(orderHistory[orderCount].items, "\nToppings: ");
                strcat(orderHistory[orderCount].items, P1[orderCount].toppings);
            }
            else 
                strcat(orderHistory[orderCount].items, "\nToppings: None");

            if(strlen(P1[orderCount].sauces))
            {
                strcat(orderHistory[orderCount].items, "\nSauces: ");
                strcat(orderHistory[orderCount].items, P1[orderCount].sauces);   
            }
            else 
                strcat(orderHistory[orderCount].items, "\nSauces: None");
            break;
        case 2:
            SystemClear();
            printf("1. Double Cheese Burger - Ingredients: Bun, Tomato, Beef, Lettuce, Onions, Cheese x2, BBQ Sauce\n");
            printf("2. Cheese Burger - Ingredients: Dough, Tomato sauce, pepperoni, Chilli\n");
            printf("3. Royal Burger - Ingredients: Dough, Tomato sauce, pepperoni, Chilli\n");
            printf("4. Back\n");
            printf("Enter Choice: ");
            scanf("%d", &b);
            getchar();
            if(b == 4)
                break;
            switch (b)
            {
                case 1:
                    strcpy(burger1[orderCount].burger_name, "Double Cheese Burger");
                    strcpy(orderHistory[orderCount].items, burger1[orderCount].burger_name);
                    break;
                case 2:
                    strcpy(orderHistory[orderCount].items, "Cheese Burger");
                    break;
                case 3:
                    strcpy(orderHistory[orderCount].items, "Royal Burger");
                    break;
                default:
                    printf("Enter a valid option");
                    break;
            }
            break;
        case 3:
            SystemClear();
            printf("1. Spaghetti - Ingredients: Spaghetti, Tomato Sauce, Beef\n");
            printf("2. Shrimp Pasta - Ingredients: Tagliattele, Shrimp, Sauce, Onions, Garlic\n");
            printf("3. Carbonara - Ingredients: Penne, Tomato Sauce, Ground Beef, Onions\n");
            printf("4. Back\n");
            printf("Enter Choice: ");
            scanf("%d", &b);
            getchar();
            if(b == 4)
                break;
            switch (b)
            {
                case 1:
                    strcpy(pasta1[orderCount].pasta_name, "Spaghetti");
                    strcpy(orderHistory[orderCount].items, pasta1[orderCount].pasta_name);
                    break;
                case 2:
                    strcpy(orderHistory[orderCount].items, "Shrimp Pasta");
                    break;
                case 3:
                    strcpy(orderHistory[orderCount].items, "Carbonara");
                    break;
                default:
                    printf("Enter a valid option");
                    break;
            }
            break;  
        case 4:
            SystemClear();
            printf("1. Water\n");
            printf("2. Mineral Water\n");
            printf("3. Cappy - Pear\n");
            printf("4. Cappy - Apple\n");
            printf("5. Coca-Cola\n");
            printf("6. Coca-Cola Zero\n");
            printf("7. Back\n");
            printf("Enter Choice: ");
            scanf("%d", &b);
            getchar();
            if(b == 7)
                break;
            switch (b)
            {
                case 1:
                    strcat(orderHistory[orderCount].items, "Water");
                    break;
                case 2:
                    strcpy(orderHistory[orderCount].items, "Mineral Water");
                    break;
                case 3:
                    strcpy(orderHistory[orderCount].items, "Cappy - Pear");
                    break;
                case 4:
                    strcpy(orderHistory[orderCount].items, "Cappy - Apple");
                    break;
                case 5:
                    strcpy(orderHistory[orderCount].items, "Coca-Cola");    
                    break;
                case 6:
                    strcpy(orderHistory[orderCount].items, "Coca-Cola Zero");
                    break;
                default:
                    printf("Enter a valid option");
                    break;
            }
            break;
        case 5:
            SystemClear();
            printf("1. Wine\n");
            printf("2. Tequila\n");
            printf("3. Jack Daniel's\n");
            printf("4. Hugo\n");
            printf("5. Beer\n");
            printf("6. Rum\n");
            printf("7. Back\n");
            printf("Enter Choice: ");
            scanf("%d", &b);
            getchar();
            if(b == 7)
                break;
            switch (b)
            {
                case 1:
                    strcat(orderHistory[orderCount].items, "Wine");
                    break;
                case 2:
                    strcpy(orderHistory[orderCount].items, "Tequila");
                    break;
                case 3:
                    strcpy(orderHistory[orderCount].items, "Jack Daniel's");
                    break;
                case 4:
                    strcpy(orderHistory[orderCount].items, "Hugo");
                    break;
                case 5:
                    strcpy(orderHistory[orderCount].items, "Beew");    
                    break;
                case 6:
                    strcpy(orderHistory[orderCount].items, "Rum");
                    break;
                case 7:
                    Meniu_El_diablo(nr); 
                    break;
                default:
                    printf("Enter a valid option");
                    break;
            }
        break;
        
    }
}

void Meniu_Indian_Bistro(int nr)
{
    int b;
    SystemClear();
    
    switch (nr)
    {
        if(nr == 6)
            break;
        case 1:
            strcpy(orderHistory[orderCount].items, "Coffee");
            break;
        case 2:
            strcpy(orderHistory[orderCount].items, "Ice Coffee");
            break;
        case 3:
            strcpy(orderHistory[orderCount].items, "Tea");
            break;
        case 4:
        SystemClear();
            printf("Sodas:\n1. Coca-Cola\n2. Sprite\n3. Mountain Dew\n4. Pepsi\n5.Back\nEnter Option: ");
            scanf("%d", &b);
            getchar();

            if(b == 5)
                break;

            switch (b)
            {
                case 1:
                    strcpy(orderHistory[orderCount].items, "Coca-Cola");
                    break;
                case 2:
                    strcpy(orderHistory[orderCount].items, "Sprite");
                    break;
                case 3:
                    strcpy(orderHistory[orderCount].items, "Mountain Dew");
                    break;
                case 4:
                    strcpy(orderHistory[orderCount].items, "Pepsi");
                    break;
                default:
                    printf("Enter a valid Option...");
                    break;
            }
            break;
        case 5:
            SystemClear();
            printf("Cocktails:\n1. Spicy Margarita\n2. White Russian\n3. Bloody Mary\n4. Hurricane Cocktail\n5. Back\nEnter Option: ");
            scanf("%d", &b);
            getchar();

            if(b == 5)
                break;

            switch (b)
            {
                case 1:
                    strcpy(orderHistory[orderCount].items, "Spicy Margarita");
                    break;
                case 2:
                    strcpy(orderHistory[orderCount].items, "White Russian");
                    break;
                case 3:
                    strcpy(orderHistory[orderCount].items, "Bloody Mary");
                    break;
                case 4:
                    strcpy(orderHistory[orderCount].items, "Hurricane Cocktail");
                    break;
                default:
                    printf("Enter a valid Option...");
                    break;
            }
            break;
        default:
        printf("Enter a valid option...");
            break;
    }
}

void El_Diablo()
{

    SystemClear();

    printf("---------------------\n");
    printf("El Diablo Menu\n");
    printf("---------------------\n");
    printf("1. Pizza Catalog\n");
    printf("2. Burger Catalog\n");
    printf("3. Pasta Catalog\n");
    printf("4. Non-Alcoholic Drinks\n");
    printf("5. Alcoholic Drinks\n");
    printf("6. Back\n");
    printf("Enter choice of interest: ");
    scanf("%d", &order_number);
    Meniu_El_diablo(order_number);
    placeOrder("El Diablo");
    
}

void Mind_Space()
{

    SystemClear();

    printf("---------------------\n");
    printf("Mind Space Menu\n");
    printf("---------------------\n");
    printf("1. Pizza Catalog\n");
    printf("2. Burger Catalog\n");
    printf("3. Pasta Catalog\n");
    printf("4. Non-Alcoholic Drinks\n");
    printf("5. Alcoholic Drinks\n");
    printf("6. Back\n");
    printf("Enter choice of interest: ");
    scanf("%d", &order_number);
    Meniu_El_diablo(order_number);
    placeOrder("Mind Space");

}
    
void Taglatele()
{

    SystemClear();

    printf("---------------------\n");
    printf("Taglatele Menu\n");
    printf("---------------------\n");
    printf("1. Pizza Catalog\n");
    printf("2. Burger Catalog\n");
    printf("3. Pasta Catalog\n");
    printf("4. Non-Alcoholic Drinks\n");
    printf("5. Alcoholic Drinks\n");
    printf("6. Back\n");
    printf("Enter choice of interest: ");
    scanf("%d", &order_number);
    Meniu_El_diablo(order_number);
    placeOrder("Taglatele");

}

void Crazy_Pizza()
{
    SystemClear();

    printf("---------------------\n");
    printf("Crazy Pizza Menu\n");
    printf("---------------------\n");
    printf("1. Pizza Catalog\n");
    printf("2. Burger Catalog\n");
    printf("3. Pasta Catalog\n");
    printf("4. Non-Alcoholic Drinks\n");
    printf("5. Alcoholic Drinks\n");
    printf("6. Back\n");
    printf("Enter choice of interest: ");
    scanf("%d", &order_number);
    Meniu_El_diablo(order_number);
    placeOrder("Crazy Pizza");
}

// DO NOT FORGET TO IMPLEMENT THE TEST CASES FOR INPUTS, ----
// MAKE SURE THE TOPPINGS THAT THE USER INSERTS ARE ON THE LIST, ----
// TEST FOR "INVALID OPTIONS" WHEN CHOOSING RESTAURANT ok
// TEST FOR "INVALID OPTION" WHEN CHOOSING FOOD / DRINKS ok
// MAKE SURE THE DELIVERY ADDRESS IS A REAL ADDRESS ---
// MAKE BACK BUTTONS IN CASE USE DOESN"T WANT TO ORDER A PIZZA FOR EX, SO HE CAN GO BACK TO THE CATALOGUES!! ok

void Indian_Bistro()
{

    SystemClear();

    printf("---------------------\n");
    printf("Indian Bistro Menu\n");
    printf("---------------------\n");
    printf("1. Coffee\n");
    printf("2. Ice Coffee\n");
    printf("3. Tea\n");
    printf("4. Soda\n");
    printf("5. Cocktails\n");
    printf("6. Back\n");
    printf("Enter choice of interest: ");
    scanf("%d", &order_number);
    Meniu_Indian_Bistro(order_number);
    placeOrder("Indian Bistro");

}

int main()
{
    int option;
    do{
        header();
        printf("Enter option: ");
        scanf("%d", &option);
        switch(option)
        {
            case 1:
                El_Diablo();
                break;
            case 2:
                Mind_Space();
                break;
            case 3:
                Taglatele();
                break;
            case 4:
                Crazy_Pizza();
                break;
            case 5:
                Indian_Bistro();
                break;
            case 6:
                printf("Review Orders: \n");
                viewOrders();
                break;
            case 7:
                loadOrdersFromFile();
                viewOrders();
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid Operation!\n");
                break;
        }
    } while(option > 0);
    return 0;
}