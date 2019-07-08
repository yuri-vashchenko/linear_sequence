#include <CppUTest/TestHarness.h>
#include <linear_sequence.h>

TEST_GROUP(BasicTests)
{
};

TEST(BasicTests, CreateContainer)
{
    LSQ_HandleT handle LSQ_CreateSequence();
    CHECK_TEXT(handle != NULL, "LSQ_CreateSequence returned NULL");
}
