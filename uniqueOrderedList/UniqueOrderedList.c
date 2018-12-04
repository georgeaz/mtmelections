//
// Created by Lina & George on 18/11/2018.
//


#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include "uniqueOrderedList.h"
Element  uniqueOrderedListGetPreviousElemnt(UniqueOrderedList ,Element );
//we should check if we have to use for each
//should also check if we have to put the list struct in seperate.h file
//check if you have to return a macroin case of memory allocation failure
//
 struct List_t{
    Element element;
    struct List_t * next;
};

 void DestroyListNode(List node);
struct uniqueOrderedList_t {
    List  head;
    List iterator;
    copyElements copy;
    freeElements destroy;
    elementsEquals is_equal;
    elementGreaterThan compare;

};
void printiterator(UniqueOrderedList list) {
    printf("%d \n", *(int *) ((list->iterator->element)));

}
void print(UniqueOrderedList list){
if(list->iterator==NULL){printf("iterator is null");
return;}
    uniqueOrderedListGetLowest(list);
    while(list->iterator) {
        printf("%d \n", *(int *) ((list->iterator->element)));
       uniqueOrderedListGetNext(list);
    }
}
 void DestroyListNode(List node){//this should be inline
    free(node);
}
List ListCreate(Element element,UniqueOrderedList uniqueOrderedList){
    if (element==NULL)
        return NULL;
    List list=(List)malloc(sizeof(*list));
    if (list==NULL)
        return  NULL;
    list->element=uniqueOrderedList->copy(element);
    list->next=NULL;
    return list;
}
UniqueOrderedList uniqueOrderedListCopy(UniqueOrderedList uniqueorderedlist){

    UniqueOrderedList new_uniqueorderedlist =uniqueOrderedListCreate(
            uniqueorderedlist->copy,uniqueorderedlist->destroy,
            uniqueorderedlist->is_equal,uniqueorderedlist->compare);
            uniqueOrderedListGetLowest(uniqueorderedlist);
    while(uniqueorderedlist->iterator)
    {
        uniqueOrderedListInsert(new_uniqueorderedlist,uniqueorderedlist->iterator->element);
        uniqueOrderedListGetNext(uniqueorderedlist);
    }
    new_uniqueorderedlist->iterator=NULL;
    return  new_uniqueorderedlist;
}
int uniqueOrderedListSize(UniqueOrderedList uniqueorderedlist) {
    int counter = 0;
    if(uniqueorderedlist!=NULL&&uniqueorderedlist->head ==NULL)return 0;

    if(uniqueorderedlist==NULL||uniqueOrderedListGetLowest(uniqueorderedlist)==NULL)return -1;

    while (uniqueorderedlist->iterator){
        counter++;
        uniqueOrderedListGetNext(uniqueorderedlist);
    }
    return counter;
}
bool uniqueOrderedListContains(UniqueOrderedList uniqueOrderedList, Element element){

       if( uniqueOrderedList==NULL ||uniqueOrderedListGetLowest(uniqueOrderedList)==NULL || element==NULL)return false;
    do{
        if (uniqueOrderedList->is_equal(element, uniqueOrderedList->iterator->element))
            return true;
        uniqueOrderedListGetNext(uniqueOrderedList);

    }while (uniqueOrderedList->iterator);
    return  false;
}
UniqueOrderedListResult uniqueOrderedListInsert(UniqueOrderedList uniqueOrderedList, Element element) {
    if(uniqueOrderedList==NULL || element==NULL) {
        return UNIQUE_ORDERED_LIST_NULL_ARGUMENT;
    }
    if(uniqueOrderedListContains(uniqueOrderedList,element)) {
          return UNIQUE_ORDERED_LIST_ITEM_ALREADY_EXISTS;
    }
    uniqueOrderedListGetLowest(uniqueOrderedList);
    List new_list=ListCreate(element,uniqueOrderedList);
    if(new_list==NULL)
        return UNIQUE_ORDERED_LIST_OUT_OF_MEMORY;
    if(uniqueOrderedList->head==NULL){
        uniqueOrderedList->head=new_list;
        new_list->next=NULL;
        uniqueOrderedList->iterator=uniqueOrderedList->head;
        return UNIQUE_ORDERED_LIST_SUCCESS;
    }
    while (uniqueOrderedList->iterator) {
            if(uniqueOrderedList->compare(uniqueOrderedList->iterator->element,element)) {
                if(uniqueOrderedList->head==uniqueOrderedList->iterator){
                    new_list->next=uniqueOrderedList->iterator;
                    uniqueOrderedList->head=new_list;
                    uniqueOrderedList->iterator=uniqueOrderedList->head;
            } else
                {
                    uniqueOrderedListGetPreviousElemnt(uniqueOrderedList,uniqueOrderedList->iterator->element);
                    new_list->next=uniqueOrderedList->iterator->next;
                    uniqueOrderedList->iterator->next=new_list;
                }
                return UNIQUE_ORDERED_LIST_SUCCESS;
    }
    uniqueOrderedListGetNext(uniqueOrderedList);
    }
            uniqueOrderedListGetGreatest(uniqueOrderedList);
            uniqueOrderedList->iterator->next=new_list;
            new_list->next=NULL;
            return  UNIQUE_ORDERED_LIST_SUCCESS;
}
void uniqueOrderedListDestroy(UniqueOrderedList uniqueorderedlist)
{
    if(uniqueorderedlist==NULL)
        return;
    uniqueOrderedListClear(uniqueorderedlist);
    //  free(uniqueOrderedList->copy);
    // free(uniqueOrderedList->destroy);
    // free(uniqueOrderedList->is_equal);
    //free(uniqueOrderedList->compare);
    uniqueorderedlist->iterator=NULL;
    uniqueorderedlist->head=NULL;
    free(uniqueorderedlist);

}
void uniqueOrderedListClear(UniqueOrderedList uniqueorderedlist)
{
    if(uniqueOrderedListGetLowest(uniqueorderedlist)==NULL)return;
    do{
        uniqueOrderedListRemove(uniqueorderedlist,uniqueOrderedListGetLowest(uniqueorderedlist));
    }while(uniqueorderedlist->iterator);
    uniqueorderedlist->iterator=NULL;
    uniqueorderedlist->head=NULL;//check this




}
Element  uniqueOrderedListGetPreviousElemnt(UniqueOrderedList uniqueorderedlist,Element element)
{
    if(uniqueorderedlist==NULL || element==NULL) //we should check this later
        return NULL;

    uniqueOrderedListGetLowest(uniqueorderedlist);
    List previous_ptr=uniqueorderedlist->iterator;
    while (uniqueorderedlist->iterator) {
        if (uniqueorderedlist->is_equal(uniqueorderedlist->iterator->element,element))
        {
            uniqueorderedlist->iterator=previous_ptr;
            return element;
        }
        previous_ptr=uniqueorderedlist->iterator;
        uniqueOrderedListGetNext(uniqueorderedlist);
    }
    return NULL;
}
Element uniqueOrderedListGetNext(UniqueOrderedList uniqueorderedlist) {

    if(uniqueorderedlist->iterator==NULL || uniqueorderedlist->iterator->next==NULL) {
        uniqueorderedlist->iterator=NULL;
        return NULL;
    }

    uniqueorderedlist->iterator=uniqueorderedlist->iterator->next;

    return uniqueorderedlist->iterator->element;
}
Element uniqueOrderedListGetLowest(UniqueOrderedList uniqueorderedlist){
    if(uniqueorderedlist==NULL||uniqueorderedlist->head==NULL)
        return NULL;

    uniqueorderedlist->iterator=uniqueorderedlist->head;
    return uniqueorderedlist->head->element;

}
Element uniqueOrderedListGetGreatest(UniqueOrderedList uniqueorderedlist){
    if(uniqueorderedlist->head==NULL)
        return NULL;
   uniqueOrderedListGetLowest(uniqueorderedlist);
    while(uniqueorderedlist->iterator->next){
        uniqueOrderedListGetNext(uniqueorderedlist);
    }

    return (uniqueorderedlist->iterator->element);
}
UniqueOrderedList uniqueOrderedListCreate(copyElements copy,freeElements destroy, elementsEquals is_equal, elementGreaterThan compare)
{
    if(copy == NULL || destroy ==NULL || is_equal==NULL || compare==NULL)
        return NULL;
    UniqueOrderedList uniqueorderedlist = malloc(sizeof(*uniqueorderedlist));
    if (uniqueorderedlist==NULL) {
        return NULL;
    }
    uniqueorderedlist->head=NULL;
    uniqueorderedlist->iterator=uniqueorderedlist->head;
    uniqueorderedlist->copy=copy;
    uniqueorderedlist->compare=compare;
    uniqueorderedlist->destroy=destroy;
    uniqueorderedlist->is_equal=is_equal;
    return  uniqueorderedlist;
}
UniqueOrderedListResult uniqueOrderedListRemove
(UniqueOrderedList uniqueorderedlist, Element to_remove){

    if(to_remove==NULL || uniqueorderedlist==NULL){
        return UNIQUE_ORDERED_LIST_NULL_ARGUMENT;
    }
    if(!(uniqueOrderedListContains(uniqueorderedlist,to_remove))){
        return UNIQUE_ORDERED_LIST_ITEM_DOES_NOT_EXIST;
    }

    if(uniqueorderedlist->is_equal(uniqueOrderedListGetLowest(uniqueorderedlist),to_remove)){
        uniqueorderedlist->head=uniqueorderedlist->iterator->next;
        uniqueorderedlist->destroy(uniqueorderedlist->iterator->element);
        DestroyListNode(uniqueorderedlist->iterator);
        uniqueorderedlist->iterator=uniqueorderedlist->head;
        return UNIQUE_ORDERED_LIST_SUCCESS;
    }
    uniqueOrderedListGetPreviousElemnt(uniqueorderedlist,to_remove);
    List to_remove_ptr=uniqueorderedlist->iterator->next;
        uniqueorderedlist->iterator->next = to_remove_ptr->next;
        uniqueorderedlist->destroy(to_remove_ptr->element);
    DestroyListNode(to_remove_ptr);
        return UNIQUE_ORDERED_LIST_SUCCESS;

}
