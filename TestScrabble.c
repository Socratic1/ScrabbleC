#include "Unity/src/unity.h"
#include "Scrabble.h"

void test_foo_should_IncrementByOne(void)
{
  TEST_ASSERT_EQUAL_INT(1, foo(0));
  TEST_ASSERT_EQUAL_INT(-4, foo(-5));
  TEST_ASSERT_EQUAL_INT(3, foo(2));
}

int main(void)
{
  UNITY_BEGIN();
  RUN_TEST(test_foo_should_IncrementByOne);
  return UNITY_END();
}
