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

TEST(StressTests, AddingManyElementsAdvance)
{
    int numElements = 200000;
    CHECK_EQUAL(0, LSQ_GetSize(handle));
    for (int i = 0; i < numElements; i++) {
        LSQ_InsertRearElement(handle, i);
    }
    CHECK_EQUAL(numElements, LSQ_GetSize(handle));

    int i = 0;

    LSQ_IteratorT iterator = LSQ_GetFrontElement(handle);

    while (!LSQ_IsIteratorPastRear(iterator)) {
        LSQ_BaseTypeT value = *LSQ_DereferenceIterator(iterator);
        CHECK_EQUAL(value, i);
        i++;
        LSQ_AdvanceOneElement(iterator);
    }

    CHECK_EQUAL(numElements, i);


}

TEST(StressTests, AddingManyElementsRewind)
{
    int numElements = 200000;
    CHECK_EQUAL(0, LSQ_GetSize(handle));
    for (int i = 0; i < numElements; i++) {
        LSQ_InsertRearElement(handle, i);
    }
    CHECK_EQUAL(numElements, LSQ_GetSize(handle));

    int i = numElements - 1;

    LSQ_IteratorT iterator = LSQ_GetPastRearElement(handle);
    LSQ_RewindOneElement(iterator);

    while (!LSQ_IsIteratorBeforeFirst(iterator)) {
        LSQ_BaseTypeT value = *LSQ_DereferenceIterator(iterator);
        CHECK_EQUAL(value, i);
        i--;
        LSQ_RewindOneElement(iterator);
    }

    CHECK_EQUAL(-1, i);
}

TEST(StressTests, AddingManyElementsSetPos)
{
    int numElements = 200000;
    CHECK_EQUAL(0, LSQ_GetSize(handle));
    for (int i = 0; i < numElements; i++) {
        LSQ_InsertRearElement(handle, i);
    }
    CHECK_EQUAL(numElements, LSQ_GetSize(handle));
    LSQ_IteratorT iterator = LSQ_GetFrontElement(handle);

    for (int i = 0; i < numElements; i++) {
        LSQ_SetPosition(iterator, i);
        LSQ_BaseTypeT value = *LSQ_DereferenceIterator(iterator);
        CHECK_EQUAL(value, i);
    }
}

