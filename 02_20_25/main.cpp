#include <sqlite3.h>
#include <iostream>
#include <limits>
#include <string>

void resetStream();
void makeSale(sqlite3 *);
int startTransaction(sqlite3 *);
int rollback(sqlite3 *);
int commit(sqlite3 *);
int pickCustomer(sqlite3 *);
bool checkForError(int, sqlite3 *, sqlite3_stmt *, std::string);
int addCustomer(sqlite3 *);
int createInvoice(sqlite3 *, int);

int main()
{
    sqlite3 *saleCo;
    int returnCode;
    returnCode = sqlite3_open_v2("SaleCo.db", &saleCo, SQLITE_OPEN_READWRITE, NULL);
    if (returnCode != SQLITE_OK)
    {
        std::cout << "Error opening database: " << sqlite3_errmsg(saleCo) << std::endl;
        sqlite3_close(saleCo);
        return 0;
    }
    makeSale(saleCo);
    sqlite3_close(saleCo);

    return 0;
}

void resetStream()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

/*
    steps for making a sale
    todo create a new customer invoice
        //todo pick customer or
        todo add new customer
        todo create new invoice row using the cus_code
        todo add products to the invoice
            todo pick product
            todo add line record for that product
    todo update the qoh for teh products in the lines
    todo update the customer balance
    todo update payments if necessary

*/
void makeSale(sqlite3 *db)
{
    int rc = startTransaction(db);
    if (rc != SQLITE_OK)
    {
        return;
    }
    int cusCode = pickCustomer(db);
    if (cusCode == -1)
    {
        std::cout << "No customer infomation available" << std::endl;
        rollback(db);
        return;
    }
    int invNumber = createInvoice(db, cusCode);
    if (invNumber == -1)
    {
        std::cout << "Error inserting a new invoice" << std::endl;
        rollback(db);
        return;
    }
}

int startTransaction(sqlite3 *db)
{
    int rc = sqlite3_exec(db, "begin transaction", NULL, NULL, NULL);
    if (rc != SQLITE_OK)
    {
        std::cout << "There was an error in start transaction: "
                  << sqlite3_errmsg(db) << std::endl;
        return rc;
    }
    return SQLITE_OK;
}

int rollback(sqlite3 *db)
{
    int rc = sqlite3_exec(db, "rollback", NULL, NULL, NULL);
    if (rc != SQLITE_OK)
    {
        std::cout << "There was an error - rolling back the transaction: "
                  << sqlite3_errmsg(db) << std::endl;
        return rc;
    }
    return SQLITE_OK;
}

int pickCustomer(sqlite3 *db)
{
    const int CUS_CODE = 0;
    const int CUS_NAME = 1;
    std::string query = "select cus_code, cus_lname || ', ' || cus_fname as name\n"
                        "from customer\n";
    sqlite3_stmt *result;
    int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &result, NULL);
    if (checkForError(rc, db, result, "There was an error with the customer query:"))
    {
        std::cout << query << std::endl;
        return -1;
    }
    int i = 1;
    int choice = 0;
    std::cout << "Please choose a customer:" << std::endl;
    rc = sqlite3_step(result);
    while (rc == SQLITE_ROW)
    {
        std::cout << i << ". " << sqlite3_column_text(result, CUS_CODE);
        std::cout << " - " << sqlite3_column_text(result, CUS_NAME);
        std::cout << std::endl;
        i++;
        rc = sqlite3_step(result);
    }
    std::cout << i << ". Add New Customer" << std::endl;
    std::cin >> choice;
    while (!std::cin || choice < 1 || choice > i)
    {
        if (!std::cin)
            resetStream();
        std::cout << "That is not a valid choice! Try again!" << std::endl;
        std::cin >> choice;
    }
    if (choice == i)
    {
        sqlite3_finalize(result);
        return addCustomer(db);
    }
    sqlite3_reset(result);
    for (int j = 0; j < choice; j++)
    {
        sqlite3_step(result);
    }
    int cusCode = sqlite3_column_int(result, CUS_CODE);
    sqlite3_finalize(result);

    return cusCode;
}

bool checkForError(int rc, sqlite3 *db, sqlite3_stmt *r, std::string msg)
{
    if (rc != SQLITE_OK)
    {
        sqlite3_finalize(r);
        std::cout << msg << " " << sqlite3_errmsg(db) << std::endl;
        return true;
    }
    return false;
}

int addCustomer(sqlite3 *db)
{
    return 10010;
}

int createInvoice(sqlite3 *db, int customer)
{

    return -1;
}
