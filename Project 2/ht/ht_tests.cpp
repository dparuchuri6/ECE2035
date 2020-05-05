// Inform the compiler that this included module is written in C instead of C++.
extern "C" {
	#include "hash_table.h"
}
#include "gtest/gtest.h"


// Use the TEST macro to define your tests.
//
// TEST has two parameters: the test case name and the test name.
// After using the macro, you should define your test logic between a
// pair of braces.  You can use a bunch of macros to indicate the
// success or failure of a test.  EXPECT_TRUE and EXPECT_EQ are
// examples of such macros.  For a complete list, see gtest.h.
//
// <TechnicalDetails>
//
// In Google Test, tests are grouped into test cases.  This is how we
// keep test code organized.  You should put logically related tests
// into the same test case.
//
// The test case name and the test name should both be valid C++
// identifiers.  And you should not use underscore (_) in the names.
//
// Google Test guarantees that each test you define is run exactly
// once, but it makes no guarantee on the order the tests are
// executed.  Therefore, you should write your tests in such a way
// that their results don't depend on their order.
//
// </TechnicalDetails>

// The #define directive defines a constant value that can be accessed throughout
// your code. Here it defines the default number of buckets in the hash table.
// You can change this number, but make sure to update the hash function with
// the right algorithm to compute the indices for buckets.
// For example, if the BUCKET_NUM is set to 5, the hash function should map a
// positive number to an integer between 0 and 4.
#define BUCKET_NUM  10

// Dummy value to store in hash table entry
// Please beware that any type of data (e.g. int, double, struct and etc.) can
// be stored in hash table for testing your hash table. Only the pointer to
// the data will be stored in the HashTableEntry.

struct HTItem {
};

struct _HashTable {
  HashTableEntry** buckets;
  HashFunction hash;
  unsigned int num_buckets;
};

// Helper function for creating a lot of dummy values.
void make_items(HTItem* result[], unsigned n)
{
	// Populate the array with pointers to the dummy values.
	while(n--)
	{
		result[n] = (HTItem*) malloc(sizeof(HTItem));
	}
}

// A simple hash function that maps a positive number to an integer between 0~(BUCKET_NUM-1).
unsigned int hash(unsigned int key) {
	return key % BUCKET_NUM;
}



//////////////////////////
// Initialization tests //
//////////////////////////


//Initalizing table given valid number of buckets
TEST(InitTest, CreateDestroyEmptyHashTable)
{
	HashTable* ht = createHashTable(hash, BUCKET_NUM);
	for (int i = 0; i < BUCKET_NUM; i++) {
		EXPECT_EQ(NULL, (ht -> buckets)[i]);
	}

	destroyHashTable(ht);
}


//Initalizing and Destroying a non-empty table
TEST(InitTest, CreateDestroyNonEmptyHashTable)
{
	HashTable* ht = createHashTable(hash, BUCKET_NUM);

	 // Create list of items
    size_t num_items = 6;
    HTItem* m[num_items];
    make_items(m, num_items);

    insertItem(ht, 0, m[0]);
    insertItem(ht, 10, m[1]);
    insertItem(ht, 20, m[2]);
    insertItem(ht, 1, m[3]);
    insertItem(ht, 11, m[4]);
    insertItem(ht, 2, m[5]);

	destroyHashTable(ht);
}

/*
//Creating/Destroying a null table
//Test succeeds if no Seg Fault during testing
//Does nothing to table
TEST(InitTest, CreateDestroyNULLHashTable)
{
	HashTable* ht = NULL;
	destroyHashTable(ht);
}
*/

//////////////////
// Access tests //
//////////////////


//Access items from an empty table
TEST(AccessTest, GetKey_TableEmpty)
{
	HashTable* ht = createHashTable(hash, BUCKET_NUM);

	// Test when table is empty.
	EXPECT_EQ(NULL, getItem(ht, 0));
	EXPECT_EQ(NULL, getItem(ht, 1));
	EXPECT_EQ(NULL, getItem(ht, 2));

	// Test with index greater than the number of buckets.
	EXPECT_EQ(NULL, getItem(ht, 10));

	//EXPECT_EQ(NULL, getItem(ht, -5));

	destroyHashTable(ht);
}


//Access items in buckets of varying size
TEST(AccessTest, GetKey_NonEmptyTable)
{
  HashTable* ht = createHashTable(hash, BUCKET_NUM);

  // Create list of items
  size_t num_items = 6;
  HTItem* m[num_items];
  make_items(m, num_items);

  insertItem(ht, 0, m[0]);
  insertItem(ht, 10, m[1]);
  insertItem(ht, 20, m[2]);
  insertItem(ht, 1, m[3]);
  insertItem(ht, 11, m[4]);
  insertItem(ht, 2, m[5]);

  EXPECT_EQ(m[0], getItem(ht, 0));
  EXPECT_EQ(m[1], getItem(ht, 10));
  EXPECT_EQ(m[2], getItem(ht, 20));
  EXPECT_EQ(m[3], getItem(ht, 1));
  EXPECT_EQ(m[4], getItem(ht, 11));
  EXPECT_EQ(m[5], getItem(ht, 2));

  destroyHashTable(ht);   
}

// Access a key that is not in table by checking 
// buckets of varying size
TEST(AccessTest, GetKey_KeyNotPresent)
{
  HashTable* ht = createHashTable(hash, BUCKET_NUM);

  // Create list of items
  size_t num_items = 6;
  HTItem* m[num_items];
  make_items(m, num_items);

  insertItem(ht, 0, m[0]);
  insertItem(ht, 10, m[1]);
  insertItem(ht, 20, m[2]);
  insertItem(ht, 1, m[3]);
  insertItem(ht, 11, m[4]);
  insertItem(ht, 2, m[5]);

  EXPECT_EQ(NULL, getItem(ht, 100));
  EXPECT_EQ(NULL, getItem(ht, 21));
  EXPECT_EQ(NULL, getItem(ht, 12));
  EXPECT_EQ(NULL, getItem(ht, 3));

  destroyHashTable(ht);    
}


//////////////////////////////
// Removal and delete tests //
//////////////////////////////

TEST(RemoveTest, Remove_EmptyTable) {
	HashTable* ht = createHashTable(hash, BUCKET_NUM);

	EXPECT_EQ(NULL, removeItem(ht, 0));
	EXPECT_EQ(NULL, removeItem(ht, 1));
	EXPECT_EQ(NULL, removeItem(ht, 2));

	destroyHashTable(ht);
}


//Removes the only element in a bucket
TEST(RemoveTest, Remove_NonEmptyBucket_OneElement) {
	HashTable* ht = createHashTable(hash, BUCKET_NUM);

    size_t num_items = 1;
    HTItem* m[num_items];
	make_items(m, num_items);

	insertItem(ht, 0, m[0]);

	EXPECT_EQ(m[0], removeItem(ht, 0));
	EXPECT_EQ(NULL, getItem(ht, 0));

	destroyHashTable(ht);
	free(m[0]);
}

//Removes first element from different sized buckets
TEST(RemoveTest, Remove_NonEmptyBucket_FirstElement) {
	HashTable* ht = createHashTable(hash, BUCKET_NUM);

    size_t num_items = 6;
    HTItem* m[num_items];
	make_items(m, num_items);

	insertItem(ht, 0, m[0]);
	insertItem(ht, 1, m[1]);
	insertItem(ht, 11, m[2]);
	insertItem(ht, 2, m[3]);
	insertItem(ht, 12, m[4]);
	insertItem(ht, 22, m[5]);

	EXPECT_EQ(m[0], removeItem(ht, 0));
	EXPECT_EQ(m[1], removeItem(ht, 1));
	EXPECT_EQ(m[3], removeItem(ht, 2));

	EXPECT_EQ(NULL, getItem(ht, 0));
	EXPECT_EQ(NULL, getItem(ht, 1));
	EXPECT_EQ(NULL, getItem(ht, 2));
	EXPECT_EQ(m[2], getItem(ht, 11));
	EXPECT_EQ(m[4], getItem(ht, 12));
	EXPECT_EQ(m[5], getItem(ht, 22));


	destroyHashTable(ht);
	free(m[0]);
	free(m[1]);
	free(m[3]);
}

//Removes an element in middle of a bucket
TEST(RemoveTest, Remove_NonEmptyBucket_MiddleElement) {
	HashTable* ht = createHashTable(hash, BUCKET_NUM);

    size_t num_items = 4;
    HTItem* m[num_items];
	make_items(m, num_items);

	insertItem(ht, 0, m[0]);
	insertItem(ht, 10, m[1]);
	insertItem(ht, 20, m[2]);
	insertItem(ht, 30, m[3]);

	EXPECT_EQ(m[1], removeItem(ht, 10));
	EXPECT_EQ(NULL, getItem(ht, 10));

	EXPECT_EQ(m[0], getItem(ht, 0));
	EXPECT_EQ(m[2], getItem(ht, 20));
	EXPECT_EQ(m[3], getItem(ht, 30));


	destroyHashTable(ht);
	free(m[1]);
}

//Removes last element from different sized buckets
TEST(RemoveTest, Remove_NonEmptyBucket_LastElement) {
	HashTable* ht = createHashTable(hash, BUCKET_NUM);

    size_t num_items = 6;
    HTItem* m[num_items];
	make_items(m, num_items);

	insertItem(ht, 0, m[0]);
	insertItem(ht, 1, m[1]);
	insertItem(ht, 11, m[2]);
	insertItem(ht, 2, m[3]);
	insertItem(ht, 12, m[4]);
	insertItem(ht, 22, m[5]);

	EXPECT_EQ(m[0], removeItem(ht, 0));
	EXPECT_EQ(m[2], removeItem(ht, 11));
	EXPECT_EQ(m[5], removeItem(ht, 22));

	EXPECT_EQ(NULL, getItem(ht, 0));
	EXPECT_EQ(NULL, getItem(ht, 11));
	EXPECT_EQ(NULL, getItem(ht, 22));

	EXPECT_EQ(m[1], getItem(ht, 1));
	EXPECT_EQ(m[3], getItem(ht, 2));
	EXPECT_EQ(m[4], getItem(ht, 12));

	destroyHashTable(ht);
	free(m[0]);
	free(m[2]);
	free(m[5]);
}

//Removes item from buckets of varying size given invalid key and returns NULL
TEST(RemoveTest, Remove_InvalidKey) {
	HashTable* ht = createHashTable(hash, BUCKET_NUM);

    size_t num_items = 6;
    HTItem* m[num_items];
	make_items(m, num_items);

	insertItem(ht, 0, m[0]);
	insertItem(ht, 1, m[1]);
	insertItem(ht, 11, m[2]);
	insertItem(ht, 2, m[3]);
	insertItem(ht, 12, m[4]);
	insertItem(ht, 22, m[5]);
	

	EXPECT_EQ(NULL, removeItem(ht, 100));
	EXPECT_EQ(NULL, removeItem(ht, 21));
	EXPECT_EQ(NULL, removeItem(ht, 42));

	destroyHashTable(ht);
}

//deletes key from empty table
TEST(DeleteTest, Delete_EmptyTable) {
	HashTable* ht = createHashTable(hash, BUCKET_NUM);

	deleteItem(ht, 0);
	deleteItem(ht, 1);
	deleteItem(ht, 2);

	destroyHashTable(ht);
}

//Deletes the only element in a bucket
TEST(DeleteTest, Remove_NonEmptyBucket_OneElement) {
	HashTable* ht = createHashTable(hash, BUCKET_NUM);

    size_t num_items = 1;
    HTItem* m[num_items];
	make_items(m, num_items);

	insertItem(ht, 0, m[0]);
	deleteItem(ht, 0);
	EXPECT_EQ(NULL, getItem(ht, 0));

	destroyHashTable(ht);
}

//Deletes first element from different sized buckets
TEST(DeleteTest, Delete_NonEmptyBucket_FirstElement) {
	HashTable* ht = createHashTable(hash, BUCKET_NUM);

    size_t num_items = 6;
    HTItem* m[num_items];
	make_items(m, num_items);

	insertItem(ht, 0, m[0]);
	insertItem(ht, 1, m[1]);
	insertItem(ht, 11, m[2]);
	insertItem(ht, 2, m[3]);
	insertItem(ht, 12, m[4]);
	insertItem(ht, 22, m[5]);


	deleteItem(ht, 0);
	deleteItem(ht, 1);
	deleteItem(ht, 2);

	EXPECT_EQ(NULL, getItem(ht, 0));
	EXPECT_EQ(NULL, getItem(ht, 1));
	EXPECT_EQ(NULL, getItem(ht, 2));
	EXPECT_EQ(m[2], getItem(ht, 11));
	EXPECT_EQ(m[4], getItem(ht, 12));
	EXPECT_EQ(m[5], getItem(ht, 22));

	destroyHashTable(ht);
}

//Deletes an element in middle of buckets
TEST(DeleteTest, Delete_NonEmptyBucket_MiddleElement) {
	HashTable* ht = createHashTable(hash, BUCKET_NUM);

    size_t num_items = 4;
    HTItem* m[num_items];
	make_items(m, num_items);

	insertItem(ht, 0, m[0]);
	insertItem(ht, 10, m[1]);
	insertItem(ht, 20, m[2]);
	insertItem(ht, 30, m[3]);

	deleteItem(ht, 10);
	EXPECT_EQ(NULL, getItem(ht, 10));

	EXPECT_EQ(m[0], getItem(ht, 0));
	EXPECT_EQ(m[2], getItem(ht, 20));
	EXPECT_EQ(m[3], getItem(ht, 30));

	destroyHashTable(ht);
}

//Removes last element from different sized buckets
TEST(DeleteTest, delete_NonEmptyBucket_LastElement) {
	HashTable* ht = createHashTable(hash, BUCKET_NUM);

    size_t num_items = 6;
    HTItem* m[num_items];
	make_items(m, num_items);

	insertItem(ht, 0, m[0]);
	insertItem(ht, 1, m[1]);
	insertItem(ht, 11, m[2]);
	insertItem(ht, 2, m[3]);
	insertItem(ht, 12, m[4]);
	insertItem(ht, 22, m[5]);


	deleteItem(ht, 0);
	deleteItem(ht, 11);
	deleteItem(ht, 22);

	EXPECT_EQ(NULL, getItem(ht, 0));
	EXPECT_EQ(NULL, getItem(ht, 11));
	EXPECT_EQ(NULL, getItem(ht, 22));

	EXPECT_EQ(m[1], getItem(ht, 1));
	EXPECT_EQ(m[3], getItem(ht, 2));
	EXPECT_EQ(m[4], getItem(ht, 12));

	destroyHashTable(ht);
}

//Removes item from buckets of varying size given invalid key and returns NULL
TEST(DeleteTest, Delete_InvalidKey) {
	HashTable* ht = createHashTable(hash, BUCKET_NUM);

    size_t num_items = 6;
    HTItem* m[num_items];
	make_items(m, num_items);

	insertItem(ht, 0, m[0]);
	insertItem(ht, 1, m[1]);
	insertItem(ht, 11, m[2]);
	insertItem(ht, 2, m[3]);
	insertItem(ht, 12, m[4]);
	insertItem(ht, 22, m[5]);

	deleteItem(ht, 100);
	deleteItem(ht, 21);
	deleteItem(ht, 42);

	destroyHashTable(ht);
}

/////////////////////
// Insersion tests //
/////////////////////

//Tests insert into a blank bucket
TEST(InsertTest, Insert_EmptyBucket) {

	HashTable* ht = createHashTable(hash, BUCKET_NUM);

	unsigned int num_items = 1;
	HTItem* m[num_items];
	make_items(m, num_items);
	
	EXPECT_EQ(NULL, insertItem(ht, 0, m[0]));
	EXPECT_EQ(m[0], getItem(ht, 0));

	destroyHashTable(ht);
}

//Tests insert into a non empty bucket
TEST(InsertTest, Insert_NonEmptBucket) {
	
	HashTable* ht = createHashTable(hash, BUCKET_NUM); 

	unsigned int num_items = 2;
	HTItem* m[num_items];
	make_items(m, num_items);

	insertItem(ht, 0, m[0]);
	
	EXPECT_EQ(NULL, insertItem(ht, 10, m[1]));
	EXPECT_EQ(m[1], getItem(ht, 10));

	destroyHashTable(ht);
}

//Tests inserting an entry with same key and different value at beginning of bucket
TEST(InsertTest, OverWrite_FirstItem)
{
	HashTable* ht = createHashTable(hash, BUCKET_NUM);

	// Create list of items to be added to the hash table.
	size_t num_items = 2;
	HTItem* m[num_items];
	make_items(m, num_items);

	insertItem(ht, 0, m[0]);

	EXPECT_EQ(m[0], insertItem(ht, 0, m[1]));
	EXPECT_EQ(m[1], getItem(ht,0));

	destroyHashTable(ht);
	free(m[0]);    // don't forget to free item 0
}

//Tests inserting an entry with same key and different value in the middle of a bucket
TEST(InsertTest, OverWrite_MiddleItem)
{
	HashTable* ht = createHashTable(hash, BUCKET_NUM);

	size_t num_items = 4;
	HTItem* m[num_items];
	make_items(m, num_items);

	insertItem(ht, 0, m[0]);
	insertItem(ht, 10, m[1]);
	insertItem(ht, 20, m[2]);

	
	EXPECT_EQ(m[1], insertItem(ht, 10, m[3]));
	EXPECT_EQ(m[3], getItem(ht,10));

	destroyHashTable(ht);
	free(m[1]);
}

//Tests inserting an entry with same key and different value at the end of a bucket
TEST(InsertTest, OverWrite_LastItem)
{
	HashTable* ht = createHashTable(hash, BUCKET_NUM);

	size_t num_items = 4;
	HTItem* m[num_items];
	make_items(m, num_items);

	insertItem(ht, 0, m[0]);
	insertItem(ht, 10, m[1]);
	insertItem(ht, 20, m[2]);

	
	EXPECT_EQ(m[2], insertItem(ht, 20, m[3]));
	EXPECT_EQ(m[3], getItem(ht,20));

	destroyHashTable(ht);
	free(m[2]);
}
