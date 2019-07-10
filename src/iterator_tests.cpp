#include <CppUTest/TestHarness.h>

extern "C"
{
#include <linear_sequence.h>
}

TEST_GROUP(IteratorTests)
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

TEST(IteratorTests, CheckDereferencable)
{
CHECK_EQUAL(0, LSQ_GetSize(handle));

LSQ_InsertFrontElement(handle, 555);
// Check number of Elements
CHECK_EQUAL(1, LSQ_GetSize(handle));
// Check front Element
// Create iterator
LSQ_IteratorT iterator = LSQ_GetFrontElement(handle);
CHECK_TEXT(iterator != NULL, "LSQ_GetFrontElement returned NULL");
// Check it is dereferencable
CHECK_TEXT(LSQ_IsIteratorDereferencable(iterator), "Created iterator is not dereferencable");

LSQ_DestroyIterator(iterator);
}

TEST(IteratorTests, CheckDereferencable2)
{
    LSQ_IteratorT iterator = LSQ_GetPastRearElement(handle);
    CHECK_TEXT(iterator != NULL, "LSQ_GetFrontElement returned NULL");
    // Check it is dereferencable
    CHECK_TEXT(!LSQ_IsIteratorDereferencable(iterator), "Created iterator is not dereferencable");
}