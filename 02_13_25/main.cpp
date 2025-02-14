#include <iostream>
#include <limits>
#include <string>
#include <sqlite3.h>

void viewAssignmentsByProject(sqlite3 *);
void resetStream();

int main()
{
    sqlite3 *db;
    int rc = sqlite3_open_v2("ConstructCo.db", &db, SQLITE_OPEN_READWRITE,NULL);
    if(rc != SQLITE_OK)
    {
        std::cout << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
    }
    viewAssignmentsByProject(db);
    sqlite3_close(db);
    return 0;
}
void resetStream()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void viewAssignmentsByProject(sqlite3 * db)
{
    std::string query;
    sqlite3_stmt *result;
    query = "select proj_num, proj_name "
    "from project";//proj_num is 0 proj_name is 1
    const int PROJNUM = 0;
    const int PROJNAME = 1;
    int rc = sqlite3_prepare_v2(db, query.c_str(),-1,&result,NULL);
    if(rc != SQLITE_OK)
    {
        sqlite3_finalize(result);
        std::cout << "There was an error with the project query: " << sqlite3_errmsg(db) << std::endl;
        std::cout << query << std::endl;
        return;
    }
    int i = 1;
    int choice;
    std::cout << std::left;
    std::cout << "Please choose the project: " << std::endl;
    rc = sqlite3_step(result);
    while(rc == SQLITE_ROW)
    {
        std::cout << i << "." << sqlite3_column_text(result, 0);
        std::cout << " - " << sqlite3_column_text(result, 1);
        std::cout << std::endl;
        i++;
        rc = sqlite3_step(result);
    }
    std::cin >> choice;
    while(!std::cin || choice < 1 || choice >= i)
    {
        if(!std::cin)
        {
            resetStream();
        }
        std::cout << "That is not a valid choice! Try again!" << std::endl;
        std::cin >> choice;
    }
    sqlite3_reset(result);
    for(int j = 0; j < choice; j++)
    {
        sqlite3_step(result);
    }
    int proj_num = sqlite3_column_int(result, 0);
    sqlite3_finalize(result);

}