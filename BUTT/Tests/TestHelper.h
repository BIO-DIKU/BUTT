#ifndef TESTHELPER_H
#define TESTHELPER_H

#include <string>

namespace BUTTTest{
    bool assertEquals(const std::string &expected, const std::string &actual, std::string message);
    bool assertEquals(int expected, int actual, std::string message);
    bool assertTrue(const bool &actual, std::string message);
    bool assertFalse(const bool &actual, std::string message);
}

#define BUTT_ASSERT_EQUALS(expected, actual, message) if(!BUTTTest::assertEquals(expected,actual,message)) return false;
#define BUTT_ASSERT_TRUE(actual, message) if(!BUTTTest::assertTrue(actual,message)) return false;
#define BUTT_ASSERT_FALSE(actual, message) if(!BUTTTest::assertFalse(actual,message)) return false;

#endif // TESTHELPER_H
