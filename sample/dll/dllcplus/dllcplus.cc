#include <iostream.h>
#include "dllcplus.h"

CTest::CTest()
{
    cout << "ctest constructor\n";
}

CTest::~CTest()
{
    cout << "ctest destructor\n";
}

int CTest::SayHello(void)
{
    cout << "Hello world\n";
    return 0;
}

int CTest::SayHello(char *str)
{
    cout << str;
    return 0;
}

