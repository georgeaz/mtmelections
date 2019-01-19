
#include "uniqueOrderedListTest.h"
#include <stdio.h>
#include <stdlib.h>
#define CHECK(b,res) if((b) != (res)) do{ uniqueOrderedListDestroy(uol);return false;} while(0)
#define CHECK_WITH_FREE(b,res,f) if((b) != (res)) do{ uniqueOrderedListDestroy(uol);free(f);return false;} while(0)

static Element copyInt(Element e){
	int* newInt = malloc(sizeof(*newInt));
	if(!newInt){
		return NULL;
	}
	*newInt = *((int*)e);
	return newInt;
}

static void freeInt(Element e){
	free(e);
}

static bool intEquals(Element e1, Element e2){
	return *((int*)e1) == *((int*)e2);
}

static bool intGreaterThan(Element e1, Element e2){
	return *((int*)e1) > *((int*)e2);
}

bool testUniqueOrderedListCopy(){
	UniqueOrderedList uol = uniqueOrderedListCreate(copyInt,freeInt,intEquals,intGreaterThan);
	int n[] = {1,2,4,0,2};
	CHECK(uniqueOrderedListInsert(uol,n),UNIQUE_ORDERED_LIST_SUCCESS);
	CHECK(uniqueOrderedListInsert(uol,n+1),UNIQUE_ORDERED_LIST_SUCCESS);
	CHECK(uniqueOrderedListInsert(uol,n+2),UNIQUE_ORDERED_LIST_SUCCESS);
	CHECK(uniqueOrderedListInsert(uol,n+3),UNIQUE_ORDERED_LIST_SUCCESS);
	CHECK(uniqueOrderedListInsert(uol,n+4),UNIQUE_ORDERED_LIST_ITEM_ALREADY_EXISTS);
	UniqueOrderedList copy = uniqueOrderedListCopy(uol);
	CHECK(copy!=NULL,true);
	CHECK(uniqueOrderedListRemove(copy,n),UNIQUE_ORDERED_LIST_SUCCESS);
	CHECK(uniqueOrderedListContains(uol,n),true);
	CHECK(uniqueOrderedListSize(uol),4);
	CHECK(uniqueOrderedListSize(copy),3);
	CHECK(uniqueOrderedListInsert(copy,n),UNIQUE_ORDERED_LIST_SUCCESS);
	CHECK(*((int*)uniqueOrderedListGetLowest(uol)),0);
	CHECK(*((int*)uniqueOrderedListGetNext(uol)),1);
	CHECK(*((int*)uniqueOrderedListGetLowest(copy)),0);
	CHECK(*((int*)uniqueOrderedListGetNext(uol)),2);
	uniqueOrderedListDestroy(copy);
	uniqueOrderedListDestroy(uol);
	return true;
}

bool testUniqueOrderedListSize(){
	UniqueOrderedList uol = uniqueOrderedListCreate(copyInt,freeInt,intEquals,intGreaterThan);
	CHECK(uniqueOrderedListSize(uol),0);
	int n[] = {1,2,4,0,2};
	CHECK(uniqueOrderedListInsert(uol,n),UNIQUE_ORDERED_LIST_SUCCESS);
	CHECK(uniqueOrderedListSize(uol),1);
	CHECK(uniqueOrderedListInsert(uol,n+1),UNIQUE_ORDERED_LIST_SUCCESS);
	CHECK(uniqueOrderedListSize(uol),2);
	CHECK(uniqueOrderedListInsert(uol,n+2),UNIQUE_ORDERED_LIST_SUCCESS);
	CHECK(uniqueOrderedListSize(uol),3);
	CHECK(uniqueOrderedListInsert(uol,n+3),UNIQUE_ORDERED_LIST_SUCCESS);
	CHECK(uniqueOrderedListSize(uol),4);
	CHECK(uniqueOrderedListInsert(uol,n+4),UNIQUE_ORDERED_LIST_ITEM_ALREADY_EXISTS);
	CHECK(uniqueOrderedListSize(uol),4);
	int i = 5;
	CHECK(uniqueOrderedListRemove(uol,&i),UNIQUE_ORDERED_LIST_ITEM_DOES_NOT_EXIST);
	CHECK(uniqueOrderedListSize(uol),4);
	CHECK(uniqueOrderedListRemove(uol,n),UNIQUE_ORDERED_LIST_SUCCESS);
	CHECK(uniqueOrderedListSize(uol),3);

	uniqueOrderedListDestroy(uol);
	return true;
}

bool testUniqueOrderedListContains(){
	UniqueOrderedList uol = uniqueOrderedListCreate(copyInt,freeInt,intEquals,intGreaterThan);
	CHECK(uniqueOrderedListSize(uol),0);
	int n[] = {1,2,4,0,2};
	CHECK(uniqueOrderedListInsert(uol,n),UNIQUE_ORDERED_LIST_SUCCESS);
	CHECK(uniqueOrderedListContains(uol,n),true);
	CHECK(uniqueOrderedListInsert(uol,n+1),UNIQUE_ORDERED_LIST_SUCCESS);
	CHECK(uniqueOrderedListContains(uol,n+1),true);
	CHECK(uniqueOrderedListInsert(uol,n+2),UNIQUE_ORDERED_LIST_SUCCESS);
	CHECK(uniqueOrderedListContains(uol,n+2),true);
	CHECK(uniqueOrderedListInsert(uol,n+3),UNIQUE_ORDERED_LIST_SUCCESS);
	CHECK(uniqueOrderedListContains(uol,n+3),true);
	CHECK(uniqueOrderedListInsert(uol,n+4),UNIQUE_ORDERED_LIST_ITEM_ALREADY_EXISTS);
	int i = 5;
	CHECK(uniqueOrderedListRemove(uol,&i),UNIQUE_ORDERED_LIST_ITEM_DOES_NOT_EXIST);
	CHECK(uniqueOrderedListContains(uol,&i),false);
	CHECK(uniqueOrderedListRemove(uol,n+1),UNIQUE_ORDERED_LIST_SUCCESS);
	CHECK(uniqueOrderedListContains(uol,n+1),false);

	uniqueOrderedListDestroy(uol);
	return true;
}

bool testUniqueOrderedListInsert(){
	UniqueOrderedList uol = uniqueOrderedListCreate(copyInt,freeInt,intEquals,intGreaterThan);
	CHECK(uniqueOrderedListSize(uol),0);
	int n[] = {1,2,4,0,2};
	CHECK(uniqueOrderedListInsert(uol,n),UNIQUE_ORDERED_LIST_SUCCESS);
	CHECK(uniqueOrderedListInsert(uol,n),UNIQUE_ORDERED_LIST_ITEM_ALREADY_EXISTS);
	n[0] = 6;
	CHECK(uniqueOrderedListContains(uol,n),false);
	CHECK(uniqueOrderedListSize(uol),1);
	uniqueOrderedListDestroy(uol);
	return true;
}
typedef struct pair{
	int x;
	int y;
}*Pair;

static Element copyPair(Element e){
	Pair newPair = malloc(sizeof(*newPair));
	if(!newPair){
		return NULL;
	}
	newPair->x = ((Pair)e)->x;
	newPair->y = ((Pair)e)->y;
	return newPair;
}

static void freePair(Element e){
	free(e);
}

static bool pairEquals(Element e1, Element e2){
	return ((Pair)e1)->x == ((Pair)e2)->x;
}

static bool pairGreaterThan(Element e1, Element e2){
	return ((Pair)e1)->y > ((Pair)e2)->y;
}
bool testUniqueOrderedListInsertAdvanced(){
	UniqueOrderedList uol = uniqueOrderedListCreate(copyPair,freePair,pairEquals,pairGreaterThan);
	struct pair p[] = {{1,7},{2,6},{3,5},{4,2},{5,1},{1,3}};
	CHECK(uniqueOrderedListInsert(uol,p),UNIQUE_ORDERED_LIST_SUCCESS);
	CHECK(uniqueOrderedListInsert(uol,p+1),UNIQUE_ORDERED_LIST_SUCCESS);
	CHECK(uniqueOrderedListInsert(uol,p+2),UNIQUE_ORDERED_LIST_SUCCESS);
	CHECK(uniqueOrderedListInsert(uol,p+3),UNIQUE_ORDERED_LIST_SUCCESS);
	CHECK(uniqueOrderedListInsert(uol,p+4),UNIQUE_ORDERED_LIST_SUCCESS);
	CHECK(uniqueOrderedListInsert(uol,p+5),UNIQUE_ORDERED_LIST_ITEM_ALREADY_EXISTS);
	uniqueOrderedListDestroy(uol);
	return true;
}
bool testUniqueOrderedListRemove(){
	UniqueOrderedList uol = uniqueOrderedListCreate(copyInt,freeInt,intEquals,intGreaterThan);
	CHECK(uniqueOrderedListSize(uol),0);
	int n[] = {1,2,4,0,2};
	CHECK(uniqueOrderedListRemove(uol,n),UNIQUE_ORDERED_LIST_ITEM_DOES_NOT_EXIST);
	CHECK(uniqueOrderedListInsert(uol,n),UNIQUE_ORDERED_LIST_SUCCESS);
	CHECK(uniqueOrderedListRemove(uol,n),UNIQUE_ORDERED_LIST_SUCCESS);
	CHECK(uniqueOrderedListSize(uol),0);
	uniqueOrderedListDestroy(uol);
	return true;
}

bool testUniqueOrderedListLowest(){
	UniqueOrderedList uol = uniqueOrderedListCreate(copyInt,freeInt,intEquals,intGreaterThan);
	int arr[] = {1,2,3,-1,0,10,11,-11,4};
	for(int i = 0 ; i < sizeof(arr)/sizeof(*arr); i++){
		CHECK(uniqueOrderedListInsert(uol,arr+i),UNIQUE_ORDERED_LIST_SUCCESS);
	}
	CHECK(*((int*)uniqueOrderedListGetLowest(uol)),-11);
	uniqueOrderedListDestroy(uol);
	return true;
}

bool testUniqueOrderedListGreatest(){
	UniqueOrderedList uol = uniqueOrderedListCreate(copyInt,freeInt,intEquals,intGreaterThan);
	int arr[] = {1,2,3,-1,0,10,11,-11,4};
	for(int i = 0 ; i < sizeof(arr)/sizeof(*arr); i++){
		CHECK(uniqueOrderedListInsert(uol,arr+i),UNIQUE_ORDERED_LIST_SUCCESS);
	}
	CHECK(*((int*)uniqueOrderedListGetGreatest(uol)),11);
	uniqueOrderedListDestroy(uol);
	return true;
}

bool testUniqueOrderedListNext(){
	UniqueOrderedList uol = uniqueOrderedListCreate(copyInt,freeInt,intEquals,intGreaterThan);
	int arr[] = {1,2,3,-1,0,10,11,-11,4};
	for(int i = 0 ; i < sizeof(arr)/sizeof(*arr); i++){
		CHECK(uniqueOrderedListInsert(uol,arr+i),UNIQUE_ORDERED_LIST_SUCCESS);
	}
	int sorted[] = {-11,-1,0,1,2,3,4,10,11};
	int i = 0;
	for(int* num = uniqueOrderedListGetLowest(uol);num;num = uniqueOrderedListGetNext(uol)){
		CHECK(*num,sorted[i++]);
	}
	uniqueOrderedListDestroy(uol);
	return true;
}



