#include "TestHelper.h"

#include <iostream>


bool BUTTTest::assertEquals(const std::string &expected, const std::string &actual, std::string message)
{
    if(expected.compare(actual)!=0) {
        std::cerr<<"Error: "<<message<<std::endl;
        return false;
    }
    return true;
}
bool BUTTTest::assertEquals(int expected, int actual, std::string message)
{
    if(expected!=actual){
        std::cerr<<"Error: "<<message<<std::endl;
        return false;
    }
    return true;
}

bool BUTTTest::assertTrue(const bool &actual, std::string message)
{
    if(!actual) {
        std::cerr<<"Error: "<<message<<std::endl;
        return false;
    }
    return true;
}

bool BUTTTest::assertFalse(const bool &actual, std::string message)
{
    if(actual) {
        std::cerr<<"Error: "<<message<<std::endl;
        return false;
    }
    return true;
}


