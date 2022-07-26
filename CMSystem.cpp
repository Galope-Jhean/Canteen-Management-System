#include <iostream>
#include <cstring>
#include <string>
#include <conio.h>
#include <fstream>
#include <iomanip>
using namespace std;

struct offers
{
    string name;
    double price = 0;
    int stocks = 0;
};

int intChoice(int &sub)
{
    while (!(cin >> sub))
    {
        cin.clear();
        cin.ignore(256, '\n');
        throw "Invalid Input";
        break;
    }

    return sub;
}

string hideWord()
{
    string word;
    char pass[32];
    char a;
    int i = 0;
    while (true)
    {
        a = _getch();
        if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z') || (a >= '0' && a <= '9'))
        {
            pass[i] = a;
            ++i;
            cout << "*";
        }
        if (a == '\b' && i >= 1)
        {
            cout << "\b \b";
            --i;
        }
        if (a == '\r')
        {
            pass[i] = '\0';
            break;
        }
    }

    int size = strlen(pass);
    for (size_t i = 0; i < size; i++)
    {
        word += pass[i];
    }

    return word;
}

bool logAdmin(string username[], string password[], string enteredName, string enteredPass)
{
    bool logged = true;
    fstream userData;
    userData.open("Data/accounts.txt", ios::in);
    if (userData.is_open())
    {
        int i = 0;
        while (userData >> username[i] >> password[i])
        {
            if (username[i] == enteredName && password[i] == enteredPass)
            {
                return true;
            }
            else
            {
                logged = false;
            }
            ++i;
        }
    }
    userData.close();
    return logged;
}

void registerUser(string username[], string password[], string enteredName, string enteredPass)
{
    fstream userData;
    userData.open("Data/accounts.txt", ios::app);
    if (userData.is_open())
    {
        userData << enteredName << " " << enteredPass << "\n";
    }
    userData.close();
}
bool registerAdmin(string username[], string password[], string enteredName, int *accOunter)
{

    fstream userData;
    userData.open("Data/accounts.txt", ios::in);
    if (userData.is_open())
    {
        int i = 0;
        while (userData >> username[i] >> password[i])
        {
            if (username[i] == enteredName)
            {
                return false;
            }
            ++i;
        }
        *accOunter = i;
    }
    return true;
}

bool logSystem(int choice)
{
    string username[17];
    string password[17];
    int users = 0;
    string logUser, logPass;
    string regUser, regPass;
    int logCounter = 0;
    bool logged = true;
    bool registered = true;
    if (choice == 1)
        do
        {
            system("cls");
            cout << "\n\n\t\t\t\t  =======================LOG-IN======================\n";
            cout << "\t\t\t\t\t   Please enter username: ";
            cin >> logUser;
            cout << "\t\t\t\t\t   Please enter password: ";
            logPass = hideWord();
            logged = logAdmin(username, password, logUser, logPass);
            if (!logged)
            {
                logCounter++;
                if (logCounter == 3)
                {
                    cout << "\n\n\t\t\t\t   Too many wrong attemps, please try again later";
                    logCounter = 0;
                    getch();
                    system("cls");
                    break;
                }
                cout << "\n\n\t\t\t\t\t   Wrong credentials, try again";
                _getch();
            }
            else
            {
                return true;
            }
        } while (!logged);
    else if (choice == 2)
    {
        do
        {
            system("cls");
            cout << "\n\n\t\t\t\t  =======================REGISTER======================\n";
            cout << "\t\t\t\t\t\t Enter username: ";
            cin >> regUser;
            cout << "\t\t\t\t\t\t Enter password: ";
            regPass = hideWord();
            registered = registerAdmin(username, password, regUser, &users);
            if (registered && users < 10)
            {
                registerUser(username, password, regUser, regPass);
                cout << "\n\n\t\t\t\t\t\t   Admin now registered!\n";
                cout << users;
                getch();
                system("cls");
            }
            else if (registered)
            {
                cout << "\n\n\t\t\t\t\tRegistration failed, admin slots are full\n";
                getch();
                system("cls");
            }
            else
            {
                cout << "\n\n\t\t\t\t\tUsername already used, please pick another one\n";
                getch();
                system("cls");
            }
        } while (!registered);
        return false;
    }
    return false;
}

int setRegularMenu(string names[], double price[], int stocks[], offers todaysMeals[], int size)
{
    for (int i = 0; i < size; i++)
    {
        todaysMeals[i].name = names[i];
        todaysMeals[i].price = price[i];
        todaysMeals[i].stocks = stocks[i];
    }
    return size;
}

int setCustomMenu(offers todaysMeals[], int mealCount, int mealNumber)
{
    for (int i = 0; i < mealCount; i++)
    {
        cin.ignore();
        cout << "\n\t\t\t\t\t\t   Enter name: ";
        getline(cin, todaysMeals[i].name);
        cout << "\t\t\t\t\t\t   Enter price: ";
        cin >> todaysMeals[i].price;
        cout << "\t\t\t\t\t Enter number of servings (stocks): ";
        cin >> todaysMeals[i].stocks;
        mealNumber++;
    }
    return mealNumber;
}

int addtoMenu(offers todaysMeals[], int mealCount, int mealNumber)
{
    for (int i = mealNumber; i < mealCount; i++)
    {
        cin.ignore();
        cout << "\t\t\t\t\t\t   Enter meal name: ";
        getline(cin, todaysMeals[i].name);
        cout << "\t\t\t\t\t\t   Enter price: ";
        cin >> todaysMeals[i].price;
        cout << "\t\t\t\t\t Enter number of servings (stocks): ";
        cin >> todaysMeals[i].stocks;
        mealNumber++;
    }
    return mealNumber;
}

void displayMenu(offers todaysOffer[], int mealNumber)
{
    for (int i = 0; i < mealNumber; i++)
    {
        if (todaysOffer[i].stocks > 0)
            cout << left << "\t\t\t\t     " << setw(16) << todaysOffer[i].name << "  .................  P" << fixed << setprecision(2) << todaysOffer[i].price << '\n';
    }
}

void displaymenuOrder(offers todaysOffer[], int mealNumber)
{
    for (int i = 0; i < mealNumber; i++)
    {
        if (todaysOffer[i].stocks > 0)
            cout << left << "\t\t\t\t  " << i + 1 << "\t" << setw(16) << todaysOffer[i].name << "  .................  P" << fixed << setprecision(2) << todaysOffer[i].price << '\n';
    }
}

void numberedInventory(offers todaysOffer[], int mealNumber)
{
    for (int i = 0; i < mealNumber; i++)
        cout << left << "\t\t\t\t  "
             << i + 1 << "   " << setw(15) << todaysOffer[i].name << "  .................  qty: " << todaysOffer[i].stocks << '\n';
}

void displayInventory(offers todaysOffer[], int mealNumber)
{
    for (int i = 0; i < mealNumber; i++)
        cout << left << "\t\t\t\t  "
             << "   " << setw(15) << todaysOffer[i].name << "  .................  qty: " << todaysOffer[i].stocks << '\n';
}

void viewCart(offers todaysMeals[10], offers todaysDrinks[10], offers todaysExtras[5], int mealOrder, int drinkOrder, int extraOrder)
{
    cout << left << setw(5) << "\t\t\t\t  ===================================================\n";
    cout << left << setw(5) << "\t\t\t\t  =====POLYTECHNIC UNIVERSITY OF THE PHILIPPINES=====\n";
    cout << left << setw(5) << "\t\t\t\t  ==================TAGUIG CANTEEN===================\n\n";
    cout << left << setw(5) << "\t\t\t\t                        CART\n";
    cout << left << setw(5) << "\n";
    if (mealOrder >= 0)
        cout << left << setw(5) << "\t\t\t\t\t\t    " << todaysMeals[mealOrder].name << '\n';
    if (drinkOrder >= 0)
        cout << left << setw(5) << "\t\t\t\t\t\t    " << todaysDrinks[drinkOrder].name << '\n';
    if (extraOrder >= 0)
        cout << left << setw(5) << "\t\t\t\t\t\t    " << todaysExtras[extraOrder].name << '\n';
    cout << "\n\n";
}

void editMenu(offers todaysOffer[], int editOffer, string newName, int newPrice, int newStocks)
{
    todaysOffer[editOffer - 1].name = newName;
    todaysOffer[editOffer - 1].price = newPrice;
    todaysOffer[editOffer - 1].stocks = newStocks;
}

int inventorySystem(offers todaysMeals[10], offers todaysDrinks[10], offers todaysExtras[5], bool *setMenu, int *mealNumber, int *drinkNumber, int *extraNumber)
{
    //=======Program Variables
    int mealCount = 0;
    int input = 0;
    bool check = true;
    bool overwrite = false;
    //====================
    //============Menu Variables
    string regularMeals[5] = {"Hotdogs", "Chop Suey", "Chicken Adobo", "Pork Sinigang", "Fish Fillet"};
    double mealPrices[5] = {15, 25, 35, 40, 50};
    int mealStocks[5] = {30, 30, 40, 40, 30};
    string regularDrinks[3] = {"Bottled Water", "Coca-Cola", "Iced Tea"};
    double drinkPrices[5] = {15, 20, 20};
    int drinkStocks[5] = {200, 100, 100};
    string regularExtras[3] = {"Plain Rice", "Fried Rice", "Water Refill"};
    double extraPrices[5] = {15, 15, 10};
    int extraStocks[5] = {200, 50, 200};
    //=========================
    do
    {
        system("cls");
        cout << "\n\n\t\t\t\t========================ADMIN MENU======================\n";
        cout << "\t\t\t\t\t\t   1. Set Regular Menu\n";
        cout << "\t\t\t\t\t\t   2. Set Customized Menu\n";
        cout << "\t\t\t\t\t\t   3. Edit Menu\n";
        cout << "\t\t\t\t\t\t   4. Add to menu\n";
        cout << "\t\t\t\t\t\t   5. Add/Refill Stocks\n";
        cout << "\t\t\t\t\t\t   6. Display Inventory\n";
        cout << "\t\t\t\t\t\t   7. Display Menu\n";
        cout << "\t\t\t\t\t\t   8. Exit & Log-out\n";
        cout << "\t\t\t\t========================================================\n";
        cout << "\t\t\t\t\t\t  Enter Choice: ";

        input = intChoice(input);
        if (input == 1)
        {
            char progress;
            if (overwrite == true)
            {
                system("cls");
                cin.ignore();
                cout << "\n\n\t\t\t\t   Setting regular menu will overwrite existing custom menu\n";
                cout << "\t\t\t\t   Are you sure to continue?\n";
                cout << "\t\t\t\t   [enter y if YES or n for NO] : ";
                cin >> progress;
                progress = tolower(progress);
            }
            if (progress == 'y' || overwrite == false)
            {
                check = false;
                *mealNumber = setRegularMenu(regularMeals, mealPrices, mealStocks, todaysMeals, 5);      // set regular meals
                *drinkNumber = setRegularMenu(regularDrinks, drinkPrices, drinkStocks, todaysDrinks, 3); // set regular drinks
                *extraNumber = setRegularMenu(regularExtras, extraPrices, extraStocks, todaysExtras, 3); // set regular extras
                system("cls");
                cout << "\n\n\t\t\t\t   Regular Menu has been set for today!\n";
                *setMenu = true;
            }
            else
            {
            }
            getch();
        }
        else if (input == 2)
        {
            if (check)
            {
                system("cls");
                int option = 0;
                cout << "\n\n\t\t\t\t====================CUSTOMIZE MENU===================\n";
                cout << "\t\t\t\t\t\t  1. Customize Meals\n";
                cout << "\t\t\t\t\t\t  2. Customize Drinks\n";
                cout << "\t\t\t\t\t\t  3. Customize Extras\n";
                cout << "\t\t\t\t\t\t  4. Exit\n";
                cout << "\t\t\t\t\t\t  enter choice: ";
                option = intChoice(option);
                if (option == 1)
                {
                    cout << "\t\t\t\t   How many types of meals are we serving today?";
                    mealCount = intChoice(mealCount);
                    *mealNumber = setCustomMenu(todaysMeals, mealCount, *mealNumber);
                    overwrite = true;
                }
                else if (option == 2)
                {
                    cout << "\t\t\t\t   How many types of drinks are we serving today?";
                    mealCount = intChoice(mealCount);
                    *drinkNumber = setCustomMenu(todaysDrinks, mealCount, *drinkNumber);
                    overwrite = true;
                }
                else if (option == 3)
                {
                    cout << "\t\t\t\t   How many types of extras are we serving today?";
                    mealCount = intChoice(mealCount);
                    *extraNumber = setCustomMenu(todaysExtras, mealCount, *extraNumber);
                    overwrite = true;
                }
                else
                {
                }
                *setMenu = true;
            }
            else
            {
                system("cls");
                cout << "\n\n\t\t\t   sorry, but it seems like the menu has already been set for today";
            }
            cout << "\n\n\t\t\t\t\t   Press [ANY KEY] to continue";
            getch();
        }
        else if (input == 3)
        {
            system("cls");
            if (!check)
            {
                int editReg;
                cout << "\n\n\t\t\t\t========================EDIT MENU======================\n";
                cout << "\t\t\t\t\t\t   1. Edit Meals\n";
                cout << "\t\t\t\t\t\t   2. Edit Drinks\n";
                cout << "\t\t\t\t\t\t   3. Edit Extras\n";
                cout << "\t\t\t\t\t\t   4. Exit\n";
                cout << "\t\t\t\t\t\t   Enter Choice: ";
                editReg = intChoice(editReg);
                if (editReg == 1)
                {
                    system("cls");
                    cout << "\n\n";
                    numberedInventory(todaysMeals, *mealNumber);
                    int editOffer;
                    string newName;
                    int newPrice;
                    int newStocks;
                    cout << "\n\n\t\t\t\t\t   enter number to edit: ";
                    editOffer = intChoice(editOffer);
                    cin.ignore();
                    cout << "\t\t\t\t\t   enter new product name: ";
                    getline(cin, newName);
                    cout << "\t\t\t\t\t   enter new product price: ";
                    newPrice = intChoice(newPrice);
                    cout << "\t\t\t\t\t   enter new product stock: ";
                    newStocks = intChoice(newStocks);
                    editMenu(todaysMeals, editOffer, newName, newPrice, newStocks);
                    cout << "\n\t\t\t\t\t   Change Successfuly Created!\n";
                    getch();
                }
                else if (editReg == 2)
                {
                    system("cls");
                    cout << "\n\n";
                    numberedInventory(todaysDrinks, *drinkNumber);
                    int editOffer;
                    string newName;
                    int newPrice;
                    int newStocks;
                    cout << "\n\n\t\t\t\t\t   enter number to edit: ";
                    editOffer = intChoice(editOffer);
                    cin.ignore();
                    cout << "\t\t\t\t\t   enter new product name: ";
                    getline(cin, newName);
                    cout << "\t\t\t\t\t   enter new product price: ";
                    newPrice = intChoice(newPrice);
                    cout << "\t\t\t\t\t   enter new product stock: ";
                    newStocks = intChoice(newStocks);
                    editMenu(todaysDrinks, editOffer, newName, newPrice, newStocks);
                    cout << "\n\t\t\t\t\t   Change Successfuly Created!\n";
                    getch();
                }
                else if (editReg == 3)
                {
                    system("cls");
                    cout << "\n\n";
                    numberedInventory(todaysExtras, *extraNumber);
                    int editOffer;
                    string newName;
                    int newPrice;
                    int newStocks;
                    cout << "\n\n\t\t\t\t\t   enter number to edit: ";
                    editOffer = intChoice(editOffer);
                    cin.ignore();
                    cout << "\t\t\t\t\t   enter new product name: ";
                    getline(cin, newName);
                    cout << "\t\t\t\t\t   enter new product price: ";
                    newPrice = intChoice(newPrice);
                    cout << "\t\t\t\t\t   enter new product stock: ";
                    newStocks = intChoice(newStocks);
                    editMenu(todaysExtras, editOffer, newName, newPrice, newStocks);
                    cout << "\n\t\t\t\t\t   Change Successfuly Created!\n";
                    getch();
                }
                else if (editReg == 4)
                {
                }
            }
            else
            {
                cout << "Menu has not been set\n";
                getch();
            }
        }
        else if (input == 4)
        {
            system("cls");
            int option = 0;
            cout << "\n\n\t\t\t\t========================ADD MENU======================\n";
            cout << "\t\t\t\t\t\t   1. Add Meals\n";
            cout << "\t\t\t\t\t\t   2. Add Drinks\n";
            cout << "\t\t\t\t\t\t   3. Add Extras\n";
            cout << "\t\t\t\t\t\t   4. Exit\n";
            cout << "\t\t\t\t\t\t   enter choice: ";
            option = intChoice(option);
            if (option == 1)
            {
                cout << "\t\t\t\t\t How many types of meals are going to add?";
                mealCount = intChoice(mealCount);
                int addIndex = *mealNumber + mealCount;
                *mealNumber = addtoMenu(todaysMeals, addIndex, *mealNumber);
                cout << "\n\n\t\t\t\t\t\t Successfully Added";
            }
            else if (option == 2)
            {
                int count = 0;
                cout << "\t\t\t\t\t How many types of drinks are we going to add?";
                count = intChoice(count);
                int addIndex = *drinkNumber + count;
                *drinkNumber = addtoMenu(todaysDrinks, addIndex, *drinkNumber);
                cout << "\n\n\t\t\t\t\t\t Successfully Added";
            }
            else if (option == 3)
            {
                int count = 0;
                cout << "\t\t\t\t\t How many types of extras are we going to add?";
                mealCount = intChoice(mealCount);
                int addIndex = *extraNumber + count;
                *extraNumber = addtoMenu(todaysExtras, addIndex, *extraNumber);
                cout << "\n\n\t\t\t\t\t\t Successfully Added";
            }
            else
            {
            }
            cout << "\n\t\t\t\t\t  Press [ANY KEY] to continue";
            getch();
        }
        else if (input == 5)
        {
            if (!check)
            {
                int editStocks;
                system("cls");
                cout << "\n\n\t\t\t\t========================ADD-STOCKS======================\n";
                cout << "\t\t\t\t\t\t   1. Edit Meal Stocks\n";
                cout << "\t\t\t\t\t\t   2. Edit Drink Stocks\n";
                cout << "\t\t\t\t\t\t   3. Edit Extra Stocks\n";
                cout << "\t\t\t\t\t\t   4. Exit\n";
                cout << "\t\t\t\t\t\t     ENTER CHOICE:";
                editStocks = intChoice(editStocks);

                if (editStocks == 1)
                {
                    system("cls");
                    int get, add;
                    cout << "\t\t\t\t=====================================================\n";
                    cout << "\t\t\t\t========================MEALS========================\n";
                    numberedInventory(todaysMeals, *mealNumber);
                    cout << "\n";
                    cout << "\t\t\t\tenter number of product stock to edit: ";
                    get = intChoice(get);
                    cout << "\t\t\t\tenter number of stocks to add: ";
                    add = intChoice(add);
                    todaysMeals[get - 1].stocks += add;
                    cout << "\t\t\t\tSTOCKS ADDED SUCCESSFULY!";
                    _getch();
                }
                else if (editStocks == 2)
                {
                    system("cls");
                    int get, add;
                    cout << "\t\t\t\t=====================================================\n";
                    cout << "\t\t\t\t========================MEALS========================\n";
                    numberedInventory(todaysDrinks, *drinkNumber);
                    cout << "\n";
                    cout << "\t\t\t\tenter number of product stock to edit: ";
                    get = intChoice(get);
                    cout << "\t\t\t\tenter number of stocks to add: ";
                    add = intChoice(add);
                    todaysDrinks[get - 1].stocks += add;
                    cout << "\t\t\t\tSTOCKS ADDED SUCCESSFULY!";
                    _getch();
                }
                else if (editStocks == 3)
                {
                    system("cls");
                    int get, add;
                    cout << "\t\t\t\t=====================================================\n";
                    cout << "\t\t\t\t========================MEALS========================\n";
                    numberedInventory(todaysExtras, *extraNumber);
                    cout << "\n";
                    cout << "\t\t\t\tenter number of product stock to edit: ";
                    get = intChoice(get);
                    cout << "\t\t\t\tenter number of stocks to add: ";
                    add = intChoice(add);
                    todaysExtras[get - 1].stocks += add;
                    cout << "\t\t\t\tSTOCKS ADDED SUCCESSFULY!";
                    _getch();
                }
                else
                {
                }
            }
            else
            {
                cout << "\t\t\t\t\t\t   Menu has not been set\n";
            }
        }
        else if (input == 6)
        {
            system("cls");
            cout << "\n\n\t\t\t\t=====================================================\n";
            cout << "\t\t\t\t========================MEALS========================\n";
            displayInventory(todaysMeals, *mealNumber);
            cout << "\t\t\t\t=====================================================\n";
            cout << "\t\t\t\t=======================DRINKS========================\n";
            displayInventory(todaysDrinks, *drinkNumber);
            cout << "\t\t\t\t=====================================================\n";
            cout << "\t\t\t\t=======================EXTRAS========================\n";
            displayInventory(todaysExtras, *extraNumber);
            getch();
            system("cls");
        }
        else if (input == 7)
        {
            system("cls");
            cout << "\n\n\t\t\t\t=====================================================\n";
            cout << "\t\t\t\t========================MEALS========================\n";
            displayMenu(todaysMeals, *mealNumber);
            cout << "\t\t\t\t=====================================================\n";
            cout << "\t\t\t\t=======================DRINKS========================\n";
            displayMenu(todaysDrinks, *drinkNumber);
            cout << "\t\t\t\t=====================================================\n";
            cout << "\t\t\t\t=======================EXTRAS========================\n";
            displayMenu(todaysExtras, *extraNumber);
            getch();
        }
        else if (input == 8)
        {
            return 8;
        }

    } while (input != 8);

    return 0;
}

void onePage()
{
    system("cls");
    system("Color E4");
    cout << "\n\n\t\t\t\t  ===================================================\n";
    cout << "\t\t\t\t  =====POLYTECHNIC UNIVERSITY OF THE PHILIPPINES=====\n";
    cout << "\t\t\t\t  ==================TAGUIG CANTEEN===================\n\n";
    cout << "\t\t\t\t                     [CONTINUE]";
}

int userMode()
{
    int mode;
    system("cls");
    system("Color E4");
    cout << "\n\n\t\t\t\t  ===================================================\n";
    cout << "\t\t\t\t                 1. ADMIN MODE\n";
    cout << "\t\t\t\t                 2. USER MODE\n";
    cout << "\t\t\t\t                 3. EXIT\n";
    cout << "\t\t\t\t  ===================================================\n";
    cout << "\t\t\t\t                 Enter choice: ";
    mode = intChoice(mode);

    return mode;
}

int main()
{
    offers todaysMeals[10];
    offers todaysDrinks[10];
    offers todaysExtras[5];
    int extraNumber = 0;
    int drinkNumber = 0;
    int mealNumber = 0;
    int mealOrder = 0;
    int mealorderQuantity = 0;
    double mealPrice = 0;
    int drinkOrder = 0;
    int drinkorderQuantity = 0;
    double drinkPrice;
    int extraOrder = 0;
    int extraorderQuantity = 0;
    double extraPrice;
    int mode;
    int orderNumber = 0;
    bool loggedIn;
    int number = 0;
    double tax = 0;
    double total = 0;
    bool setMenu = false;

    do
    {
        onePage();
        getch();
        try
        {
            mode = userMode();

            if (mode == 1)
            {
                do
                {
                    system("cls");
                    int choice;
                    cout << "\n\n\t\t\t\t  =======================ADMIN======================\n";
                    cout << "\t\t\t\t\t\t      1. Log in\n";
                    cout << "\t\t\t\t\t\t      2. Register\n";
                    cout << "\t\t\t\t\t\t      3. Exit\n";
                    cout << "\t\t\t\t  ==================================================\n";
                    cout << "\t\t\t\t\t\t     Enter choice: ";

                    try
                    {
                        choice = intChoice(choice);
                        if (choice == 3)
                        {
                            break;
                        }
                        else if (choice == 1 || choice == 2)
                        {
                            loggedIn = logSystem(choice);
                        }
                        if (loggedIn)
                        {
                            number = inventorySystem(todaysMeals, todaysDrinks, todaysExtras, &setMenu, &mealNumber, &drinkNumber, &extraNumber);
                        }
                    }
                    catch (const char *prompt)
                    {
                        cout << "Exception Handled: " << prompt << endl;
                        getch();
                        system("cls");
                    }
                    catch (...)
                    {
                        cout << "Exception Handled: ERROR" << endl;
                        getch();
                        system("cls");
                    }
                } while (number != 8);
            }
            else if (mode == 2)
            {
                system("cls");
                if (setMenu)
                {
                    system("Color E1");
                    system("cls");
                    cout << "\n\n\t\t\t\t                   NOW AVAILABLE  \n\n";
                    cout << "\t\t\t\t=====================================================\n";
                    cout << "\t\t\t\t========================MEALS========================\n";
                    displayMenu(todaysMeals, mealNumber);
                    cout << "\t\t\t\t=====================================================\n";
                    cout << "\t\t\t\t=======================DRINKS========================\n";
                    displayMenu(todaysDrinks, drinkNumber);
                    cout << "\t\t\t\t=====================================================\n";
                    cout << "\t\t\t\t=======================EXTRAS========================\n";
                    displayMenu(todaysExtras, extraNumber);
                    cout << "\n\t\t\t\t            PRESS [ENTER] TO ORDER NOW";
                    getch();
                    system("cls");
                    cout << "\n\n\t\t\t\t=====================================================\n";
                    cout << "\t\t\t\t========================MEALS========================\n";
                    displaymenuOrder(todaysMeals, mealNumber);
                    cout << "\n\t\t\t\t\t\t    enter 0 to skip\n\n";
                    cout << "\t\t\t\tenter meal number: ";
                    mealOrder = intChoice(mealOrder);
                    mealOrder -= 1;
                    cout << "\t\t\t\tenter quantity: ";
                    mealorderQuantity = intChoice(mealorderQuantity);
                    cout << "\t\t\t\t=====================================================\n";
                    cout << "\t\t\t\t========================DRINKS========================\n";
                    displaymenuOrder(todaysDrinks, drinkNumber);
                    cout << "\n\t\t\t\t\t\t    enter 0 to skip\n\n";
                    cout << "\t\t\t\tenter drink number: ";
                    drinkOrder = intChoice(drinkOrder);
                    drinkOrder -= 1;
                    cout << "\t\t\t\tenter quantity: ";
                    drinkorderQuantity = intChoice(drinkorderQuantity);
                    cout << "\t\t\t\t=====================================================\n";
                    cout << "\t\t\t\t========================EXTRAS========================\n";
                    displaymenuOrder(todaysExtras, extraNumber);
                    cout << "\n\t\t\t\t\t\t    enter 0 to skip\n\n";
                    cout << "\t\t\t\tenter extra number: ";
                    extraOrder = intChoice(extraOrder);
                    extraOrder -= 1;
                    cout << "\t\t\t\tenter quantity: ";
                    extraorderQuantity = intChoice(extraorderQuantity);
                    cout << "\n\nPress Enter to proceed";
                    _getch();
                    system("cls");
                    try
                    {
                        if (mealOrder == -1 && drinkOrder == -1 && extraOrder == -1)
                        {
                            throw "Order Empty";
                        }
                        viewCart(todaysMeals, todaysDrinks, todaysExtras, mealOrder, drinkOrder, extraOrder);
                        int yoyoy;

                        cout << "\t\t\t\t\t\t press 1 to proceed\n";
                        cout << "\t\t\t\t\t\t press 2 to cancel\n";
                        cout << "\t\t\t\t\t\t enter choice: ";
                        yoyoy = intChoice(yoyoy);
                        if (yoyoy == 1)
                        {
                            cout << "\n\n";
                            mealPrice = todaysMeals[mealOrder].price * mealorderQuantity;
                            drinkPrice = todaysDrinks[drinkOrder].price * drinkorderQuantity;
                            extraPrice = todaysExtras[extraOrder].price * extraorderQuantity;
                            todaysMeals[mealOrder].stocks -= mealorderQuantity;
                            todaysDrinks[drinkOrder].stocks -= drinkorderQuantity;
                            todaysExtras[extraOrder].stocks -= extraorderQuantity;
                            tax = (mealPrice + drinkPrice + extraPrice) * 0.12;
                            ++orderNumber;
                            system("cls");
                            cout << left << setw(5) << "\t\t\t\t  ===================================================\n";
                            cout << left << setw(5) << "\t\t\t\t  =====POLYTECHNIC UNIVERSITY OF THE PHILIPPINES=====\n";
                            cout << left << setw(5) << "\t\t\t\t  ==================TAGUIG CANTEEN===================\n\n";
                            cout << left << setw(5) << "\t\t\t\t                       ORDER #" << orderNumber << '\n';
                            cout << left << setw(5) << "\n";
                            if (mealorderQuantity > 0)
                                cout << left << "\t\t\t\t            " << mealorderQuantity << setw(5) << " " << todaysMeals[mealOrder].name << "\t     P" << mealPrice << '\n';
                            if (drinkorderQuantity > 0)
                                cout << left << "\t\t\t\t            " << drinkorderQuantity << setw(5) << " " << todaysDrinks[drinkOrder].name << "\t     P" << drinkPrice << '\n';
                            if (extraorderQuantity > 0)
                                cout << left << "\t\t\t\t            " << extraorderQuantity << setw(5) << " " << todaysExtras[extraOrder].name << "\t     P" << extraPrice << '\n';
                            cout << left << setw(5) << "\t\t\t\t            Subtotal                 P" << mealPrice + drinkPrice + extraPrice << '\n';
                            cout << left << setw(5) << "\t\t\t\t            Tax                      P" << tax << '\n';
                            cout << left << setw(5) << "\t\t\t\t            Total                    P" << mealPrice + drinkPrice + extraPrice + tax << '\n';
                            cout << left << setw(5) << "\t\t\t\t    \n";
                            cout << left << setw(5) << "\n";
                            cout << left << setw(5) << "\t\t\t\t  ===================================================\n";
                            cout << left << setw(5) << "\t\t\t\t  ===============Thank you for ordering==============\n";
                            cout << left << setw(5) << "\t\t\t\t  ===================================================\n\n";
                            _getch();
                        }
                        else if (yoyoy = 2)
                        {
                            throw "Order Cancelled\n";
                        }
                    }
                    catch (const char *prmpt)
                    {
                        cout << "EXCEPTION HAPPENED: " << prmpt;
                        getch();
                    }
                    catch (...)
                    {
                        cout << "exception handled\n";
                        getch();
                    }
                }

                else
                {
                    cout << "\n\n\t\t\t\t   Menu has not been set yet, please ask for assistance.";
                    _getch();
                }
            }
            else if (mode == 3)
            {
                exit(0);
            }
        }
        catch (const char *msg)
        {
            cout << "\n\nException Handled: " << msg << endl;
            getch();
            system("cls");
        }
        catch (...)
        {
            cout << "\n\nException Handled: ERROR" << endl;
            getch();
            system("cls");
        }
        system("cls");
    } while (mode != 3);
}
