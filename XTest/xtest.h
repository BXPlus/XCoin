#pragma once

#include <iomanip>
#include <iostream>

#define BEGIN_TEST(TestSuite, TestName) bool test__##TestSuite##__##TestName(void){ bool isTrue{ true };
#define END_TEST return isTrue;
}

#define EXPECT_EQ(arg1, arg2) isTrue &= (arg1 == arg2);

bool test__TestSuite__TestName()
{
    bool isTrue{ true };
    {
        isTrue &= (arg1 == arg2);
    }
    return isTrue;
}