#include <sqlite3.h>
#include <iostream>
#include <limits>
#include <string>

void resetStream();


int main()
{

    return 0;
}

void resetStream()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
