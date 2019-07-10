#include <CppUTest/TestHarness.h>

extern "C"
{
#include <linear_sequence.h>
}

TEST_GROUP(StressTests)
{
    LSQ_HandleT handle = NULL;
    void setup()
    {
        handle = LSQ_CreateSequence();
    }

    void teardoen()
    {
        LSQ_DestroySequence(handle);
    }
};

