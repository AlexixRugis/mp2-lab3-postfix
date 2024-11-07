#include "postfix.h"
#include "gtest/gtest.h"

TEST(Postfix, can_create_postfix)
{
    ASSERT_NO_THROW(Postfix p("a+b"));
}

