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
    CHECK_TEXT(handle != LSQ_HandleInvalid, "LSQ_CreateSequence returned NULL");
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
    LSQ_DestroyIterator(iterator);
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
    LSQ_DestroyIterator(iterator);
}

TEST(BasicTests, AddTwoElementsFront)
{
    CHECK_EQUAL(0, LSQ_GetSize(handle));
    LSQ_BaseTypeT element1 = 321;
    LSQ_BaseTypeT element2 = 322;
    LSQ_InsertFrontElement(handle, element1);
    LSQ_InsertFrontElement(handle, element2);
    // Check number of Elements
    CHECK_EQUAL(2, LSQ_GetSize(handle));
    // Check front Element
    // Create iterator
    LSQ_IteratorT iterator = LSQ_GetFrontElement(handle);

    CHECK_TEXT(iterator != NULL, "LSQ_GetFrontElement returned NULL");
    // Check it is dereferencable
    CHECK_TEXT(LSQ_IsIteratorDereferencable(iterator), "Created iterator is not dereferencable");
    // Check value
    CHECK_EQUAL(element2, *LSQ_DereferenceIterator(iterator));
    LSQ_AdvanceOneElement(iterator);
    CHECK_TEXT(LSQ_IsIteratorDereferencable(iterator), "Created iterator is not dereferencable");
    CHECK_EQUAL(element1, *LSQ_DereferenceIterator(iterator));
    LSQ_DestroyIterator(iterator);
}

TEST(BasicTests, AddTwoElementsBack)
{
CHECK_EQUAL(0, LSQ_GetSize(handle));
LSQ_BaseTypeT element1 = 321;
LSQ_BaseTypeT element2 = 322;
LSQ_InsertRearElement(handle, element1);
LSQ_InsertRearElement(handle, element2);
// Check number of Elements
CHECK_EQUAL(2, LSQ_GetSize(handle));
// Check front Element
// Create iterator
LSQ_IteratorT iterator = LSQ_GetFrontElement(handle);

CHECK_TEXT(iterator != NULL, "LSQ_GetFrontElement returned NULL");
// Check it is dereferencable
CHECK_TEXT(LSQ_IsIteratorDereferencable(iterator), "Created iterator is not dereferencable");
// Check value
CHECK_EQUAL(element1, *LSQ_DereferenceIterator(iterator));
LSQ_AdvanceOneElement(iterator);
CHECK_TEXT(LSQ_IsIteratorDereferencable(iterator), "Created iterator is not dereferencable");
CHECK_EQUAL(element2, *LSQ_DereferenceIterator(iterator));
LSQ_DestroyIterator(iterator);
}

TEST(BasicTests, DeleteElement)
{
    CHECK_EQUAL(0, LSQ_GetSize(handle));
    LSQ_InsertFrontElement(handle, 555);
    LSQ_DeleteFrontElement(handle);
    CHECK_EQUAL(0, LSQ_GetSize(handle));
}

TEST(BasicTests, AddTwoElementsFrontBack)
{
CHECK_EQUAL(0, LSQ_GetSize(handle));
LSQ_BaseTypeT element1 = 321;
LSQ_BaseTypeT element2 = 322;
LSQ_InsertFrontElement(handle, element1);
LSQ_InsertRearElement(handle, element2);
// Check number of Elements
CHECK_EQUAL(2, LSQ_GetSize(handle));
// Check front Element
// Create iterator
LSQ_IteratorT iterator = LSQ_GetFrontElement(handle);

CHECK_TEXT(iterator != NULL, "LSQ_GetFrontElement returned NULL");
// Check it is dereferencable
CHECK_TEXT(LSQ_IsIteratorDereferencable(iterator), "Created iterator is not dereferencable");
// Check value
CHECK_EQUAL(element1, *LSQ_DereferenceIterator(iterator));
LSQ_AdvanceOneElement(iterator);
CHECK_TEXT(LSQ_IsIteratorDereferencable(iterator), "Created iterator is not dereferencable");
CHECK_EQUAL(element2, *LSQ_DereferenceIterator(iterator));
LSQ_DestroyIterator(iterator);
}

TEST(BasicTests, InsertMiddle)
{
CHECK_EQUAL(0, LSQ_GetSize(handle));
LSQ_BaseTypeT element1 = 1;
LSQ_BaseTypeT element2 = 2;
LSQ_BaseTypeT element3 = 3;

LSQ_InsertFrontElement(handle, element1);
LSQ_InsertRearElement(handle, element3);

CHECK_EQUAL(2, LSQ_GetSize(handle));

LSQ_IteratorT iterator = LSQ_GetElementByIndex(handle, 1);
CHECK_TEXT(iterator != NULL, "LSQ_GetFrontElement returned NULL");
CHECK_TEXT(LSQ_IsIteratorDereferencable(iterator), "Created iterator is not dereferencable");

LSQ_InsertElementBeforeGiven(iterator, element2);

CHECK_EQUAL(3, LSQ_GetSize(handle));

LSQ_SetPosition(iterator, 0);

CHECK_TEXT(iterator != NULL, "LSQ_GetFrontElement returned NULL");
CHECK_TEXT(LSQ_IsIteratorDereferencable(iterator), "Created iterator is not dereferencable");

// Check value
CHECK_EQUAL(element1, *LSQ_DereferenceIterator(iterator));

LSQ_AdvanceOneElement(iterator);
CHECK_TEXT(LSQ_IsIteratorDereferencable(iterator), "Created iterator is not dereferencable");
// Check value
CHECK_EQUAL(element2, *LSQ_DereferenceIterator(iterator));



LSQ_AdvanceOneElement(iterator);
CHECK_TEXT(LSQ_IsIteratorDereferencable(iterator), "Created iterator is not dereferencable");
CHECK_EQUAL(element3, *LSQ_DereferenceIterator(iterator));

LSQ_DestroyIterator(iterator);
}
