#include "TestAll.h"

#include "TestFasta.h"
#include "TestSeqToKMers.h"
#include "TestTaxBuilder.h"
#include "TestTaxSearch.h"

#include <iostream>

TestAll::TestAll()
{
}

bool TestAll::runTests()
{
    TestFasta test_1("../BUTT/Tests/Fastas");
    bool test_1_status = test_1.runTests();
    std::cerr<<"TestAll::runTests: TestFasta "<<(test_1_status?"succesful":"failed")<<std::endl;

    return true;
}
