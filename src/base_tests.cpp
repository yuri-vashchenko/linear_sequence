#include <CppUTest/TestHarness.h>

extern "C"
{
#include <linear_sequence.h>
}

TEST_GROUP(BasicTests)
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

TEST(BasicTests, CreateContainer)
{
    CHECK_TEXT(handle != NULL, "LSQ_CreateSequence returned NULL");
}

TEST(BasicTests, DestroyContainer)
{
}

TEST(BasicTests, AddFrontElement)
{
    CHECK_EQUAL(0, LSQ_GetSize(handle));
    LSQ_BaseTypeT element = 123;
    LSQ_InsertFrontElement(handle, element);
    // Check number of Elements
    CHECK_EQUAL(1, LSQ_GetSize(handle));
    // Check front Element
    // Create iterator
    LSQ_IteratorT iterator = LSQ_GetFrontElement(handle);
    CHECK_TEXT(iterator != NULL, "LSQ_GetFrontElement returned NULL");
    // Check it is dereferencable
    CHECK_TEXT(LSQ_IsIteratorDereferencable(iterator), "Created iterator is not dereferencable");
    // Check value
    CHECK_EQUAL(element, *LSQ_DereferenceIterator(iterator));
}

TEST(BasicTests, AddRearElement)
{
    CHECK_EQUAL(0, LSQ_GetSize(handle));
    LSQ_BaseTypeT element = 321;
    LSQ_InsertRearElement(handle, element);
    // Check number of Elements
    CHECK_EQUAL(1, LSQ_GetSize(handle));
    // Check front Element
    // Create iterator
    LSQ_IteratorT iterator = LSQ_GetFrontElement(handle);
    CHECK_TEXT(iterator != NULL, "LSQ_GetFrontElement returned NULL");
    // Check it is dereferencable
    CHECK_TEXT(LSQ_IsIteratorDereferencable(iterator), "Created iterator is not dereferencable");
    // Check value
    CHECK_EQUAL(element, *LSQ_DereferenceIterator(iterator));
}

