/* Copyright 2015 BIO-DIKU */

#ifndef BUTT_TESTS_TESTHELPER_H_
#define BUTT_TESTS_TESTHELPER_H_

#include <string>

namespace BUTTTest {
    bool assertEquals(const std::string &expected, const std::string &actual,
                      std::string message);
    bool assertEquals(int expected, int actual, std::string message);
    bool assertTrue(const bool &actual, std::string message);
    bool assertFalse(const bool &actual, std::string message);
}

#define BUTT_ASSERT_EQUALS(expected, actual, message) \
    if (!BUTTTest::assertEquals(expected, actual, message)) return false;

#define BUTT_ASSERT_TRUE(actual, message) \
    if (!BUTTTest::assertTrue(actual, message)) return false;

#define BUTT_ASSERT_FALSE(actual, message) \
    if (!BUTTTest::assertFalse(actual, message)) return false;

#define BUTT_PRE_TESTS() bool status = true; bool testStatus;
#define BUTT_POST_TESTS() return status;
#define BUTT_RUN_TEST(message, function) \
    testStatus = function; \
    status&=testStatus; \
    std::cerr << message << ": " << (testStatus ? "successful" : "failed") \
              << std::endl;
#endif   // BUTT_TESTS_TESTHELPER_H_
