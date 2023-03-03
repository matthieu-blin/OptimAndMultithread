// IE2.cpp : Defines the entry point for the console application.
//

#define CATCH_CONFIG_RUNNER

#include "Catch.h"


int main(int argc, char* argv[])
{
    int result = Catch::Session().run(argc, argv);

    return result;
    return 0;
}

