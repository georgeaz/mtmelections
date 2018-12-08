#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include "uniqueOrderedList/uniqueOrderedList.h"
#include "mtm_elections.h"


//int mtmElectionsRankByAge(MtmElections mtmElections, int citizen, void* pAge);

int ZERORANK(MtmElections mtmElections, int citizen, void* data){


    return 0;


}


int LegitRank(MtmElections mtmElections, int citizen, void* data) {


    int val = *((int *) data);

    int aaaa=5;
    int* age;
    age= &aaaa;


    MtmElectionsCitizenGetAge(mtmElections, citizen, age);

    return (*age)/val;

}

void delay(int number_of_seconds)
{
    int milli_seconds = 10 * number_of_seconds;

    clock_t start_time = clock();


    while (clock() < start_time + milli_seconds)
        ;
}





int main(){



    MtmElections e = mtmElectionsCreate();


    assert(mtmElectionsAddCity(NULL,"haifa",1)==MTM_ELECTIONS_NULL_ARGUMENT);
    assert(mtmElectionsAddCity(e,NULL,1)==MTM_ELECTIONS_NULL_ARGUMENT);
    assert(mtmElectionsAddCity(e,"haifa",-1)==MTM_ELECTIONS_ILLEGAL_ID);


    mtmElectionsAddCity(e,"haifa",1);
    mtmElectionsAddCity(e,"tel-aviv",2);
    mtmElectionsAddCity(e,"jerusalem",3);
    assert(mtmElectionsAddCity(e,"haifa",1)==MTM_ELECTIONS_CITY_ALREADY_EXISTS);
    //Adding citizens to haifa
    //primary checks in haifa:
    // add citizen, support candidate, cancel support

    assert(mtmElectionsAddCitizen(e, "a",1, 25,12, 1)==MTM_ELECTIONS_SUCCESS);
    assert(mtmElectionsAddCitizen(e, "a",2, 61,12, 1)==MTM_ELECTIONS_SUCCESS);
    assert(mtmElectionsAddCitizen(e, "a",3, 31,12, 1));
    assert(mtmElectionsAddCitizen(e, "a",4, 61,12, 1));
    assert(mtmElectionsAddCitizen(e, "a",5, 71,12, 1));
    assert(mtmElectionsAddCitizen(e, "a",6, 22,12, 1));
    assert(mtmElectionsAddCitizen(e, "a",7, 24,12, 1)==MTM_ELECTIONS_SUCCESS);
    assert(mtmElectionsAddCitizen(e, "a",8, 28,12, 1));
    assert(mtmElectionsAddCitizen(e, "a",9, 43,12, 1));
    assert(mtmElectionsAddCitizen(e, "a",10, 31,12, 1));
    assert(mtmElectionsAddCitizen(e, "a",11, 51,12, 1)==MTM_ELECTIONS_SUCCESS);
    assert(mtmElectionsAddCitizen(e, "a",12, 71,12, 1));
    assert(mtmElectionsAddCitizen(e, "a",13, 21,12, 1));
    assert(mtmElectionsAddCitizen(e, "a",14, 21,12, 1));
    assert(mtmElectionsAddCitizen(e, "a",15, 21,12, 1));
    assert(mtmElectionsAddCitizen(e, "b",15, 21,12, 1)==MTM_ELECTIONS_CITIZEN_ALREADY_EXISTS);
    assert(mtmElectionsAddCitizen(e, "c",15, 21,11, 1)==MTM_ELECTIONS_CITIZEN_ALREADY_EXISTS);
    assert(mtmElectionsAddCitizen(e, "a",16, 21,10, 1));
    assert(mtmElectionsAddCitizen(e, "a",17, 21,12, 1));
    assert(mtmElectionsAddCitizen(e, "a",18, 21,12, 1));
    assert(mtmElectionsAddCitizen(e, "a",19, 21,12, 1));
    assert(mtmElectionsAddCitizen(e, "a",20, 21,12, 1));
    assert(mtmElectionsAddCitizen(e, "a",21, 21,12, 1));
    assert(mtmElectionsAddCitizen(e, "a",22, 21,12, 1));
    assert(mtmElectionsAddCitizen(e, "a",23, 21,12, 1));
    assert(mtmElectionsAddCitizen(e, "a",24, 21,12, 1));
    assert(mtmElectionsAddCitizen(e, "a",25, 21,12, 1));
    assert(mtmElectionsAddCitizen(e, "a",26, 21,12, 1));
    assert(mtmElectionsAddCitizen(e, "a",27, 21,12, 1));
    assert(mtmElectionsAddCitizen(e, "a",28, 21,12, 1));

    assert(mtmElectionsAddCitizen(e, "a",2971, 21,12, 1));
    assert(mtmElectionsAddCitizen(e, "a",30, 21,12, 1)==MTM_ELECTIONS_SUCCESS);
    mtmElectionsAddCitizen(e, "a",35, 21,12, 1);
    mtmElectionsAddCitizen(e, "a",100, 21,12, 2);
    mtmElectionsAddCitizen(e, "a",101, 21,12, 2);
    mtmElectionsAddCitizen(e, "a",102, 21,12, 2);
    mtmElectionsAddCitizen(e, "a",103, 21,12, 2);
    mtmElectionsAddCitizen(e, "a",104, 21,12, 2);
    mtmElectionsAddCitizen(e, "a",105, 21,12, 2);

    assert(mtmElectionsAddCitizen(e, "a",29, 21,12, -1)==MTM_ELECTIONS_ILLEGAL_ID);
    assert(mtmElectionsAddCitizen(e, "a",-29, 21,12, 1)==MTM_ELECTIONS_ILLEGAL_ID);
    assert(mtmElectionsAddCitizen(e, NULL ,29, 21,12, 1)==MTM_ELECTIONS_NULL_ARGUMENT);
    assert(mtmElectionsAddCitizen(NULL, "a",29, 21,12, 1)==MTM_ELECTIONS_NULL_ARGUMENT);
    assert(mtmElectionsAddCitizen(e, "a",29, 21,12, 25)==MTM_ELECTIONS_CITY_DOES_NOT_EXIST);
    assert(mtmElectionsAddCitizen(e, "a",29, 21,12, 1));
    assert(mtmElectionsAddCitizen(e, "a",29, 21,-12, 25)==MTM_ELECTIONS_ILLEGAL_NUMBER_OF_YEARS);
    assert(mtmElectionsAddCitizen(e, "a",29, -1,12, 1)==MTM_ELECTIONS_ILLEGAL_AGE);



    mtmElectionsAddCitizen(e, "a",31, 21,12, 2);
    mtmElectionsAddCandidate(e, 31, 2);
    mtmElectionsAddCitizen(e, "a",32, 13,12, 1);


    assert(mtmElectionsAddCandidate(e, 27, 1)==MTM_ELECTIONS_SUCCESS);
    mtmElectionsAddCandidate(e, 28, 1);
    mtmElectionsAddCandidate(e, 29, 1);
    mtmElectionsAddCandidate(e, 2971, 1);
    assert(mtmElectionsAddCandidate(e, 30, 1)==MTM_ELECTIONS_SUCCESS);
    assert(mtmElectionsAddCandidate(NULL, 30, 1)==MTM_ELECTIONS_NULL_ARGUMENT);
    assert(mtmElectionsAddCandidate(e, 30, 1)==MTM_ELECTIONS_CANDIDATE_ALREADY_EXISTS);
    assert(mtmElectionsAddCandidate(e, 32, 1)==MTM_ELECTIONS_AGE_NOT_APPROPRIATE);
    assert(mtmElectionsAddCandidate(e, -29, 1)==MTM_ELECTIONS_ILLEGAL_ID);
    assert(mtmElectionsAddCandidate(e, 29, -1)==MTM_ELECTIONS_ILLEGAL_ID); ///////////##############3
    assert(mtmElectionsAddCandidate(e, 33330, 1)==MTM_ELECTIONS_CITIZEN_DOES_NOT_EXIST);
    assert(mtmElectionsAddCandidate(e, 30, 31)==MTM_ELECTIONS_CITY_DOES_NOT_EXIST);


    assert(mtmElectionsSupportCandidate(e, 1 ,27 ,-1 )==MTM_ELECTIONS_ILLEGAL_PRIORITY);
    assert(mtmElectionsSupportCandidate(e, 1 ,27 ,0 )==MTM_ELECTIONS_SUCCESS); //1 vote for can #27
    assert(mtmElectionsSupportCandidate(e, 1 ,28 ,0 )==MTM_ELECTIONS_PRIORITY_EXISTS);
    assert(mtmElectionsSupportCandidate(e, 1 ,29 ,0 )==MTM_ELECTIONS_PRIORITY_EXISTS);
    assert(mtmElectionsSupportCandidate(e, 1 ,27 ,1 )==MTM_ELECTIONS_ALREADY_SUPPORTED);
    assert(mtmElectionsSupportCandidate(NULL, 2 ,27 ,3 )==MTM_ELECTIONS_NULL_ARGUMENT);

    assert(mtmElectionsSupportCandidate(e, 2 ,31 ,3 )==MTM_ELECTIONS_NOT_SAME_CITY);//~
    assert(mtmElectionsSupportCandidate(e, 2 ,320 ,3 )==MTM_ELECTIONS_CANDIDATE_DOES_NOT_EXIST);
    assert(mtmElectionsSupportCandidate(e, 30 ,29 ,3 )==MTM_ELECTIONS_CAN_NOT_SUPPORT);//~


    mtmElectionsSupportCandidate(e, 2 ,27 ,3 ); // 1 vote for can #28
    mtmElectionsSupportCandidate(e, 2 ,28 ,0 );
    mtmElectionsSupportCandidate(e, 2 ,29 ,4 );
    mtmElectionsSupportCandidate(e, 2 ,30 ,5 );

    mtmElectionsSupportCandidate(e, 3 ,27 ,3 ); //2 votes for #27
    mtmElectionsSupportCandidate(e, 3 ,28 ,4 );
    mtmElectionsSupportCandidate(e, 3 ,29 ,5 );
    mtmElectionsSupportCandidate(e, 3 ,30 ,6 );

    mtmElectionsSupportCandidate(e, 4 ,27 ,3 );
    mtmElectionsSupportCandidate(e, 4 ,28 ,4 );
    mtmElectionsSupportCandidate(e, 4 ,29 ,5 );
    mtmElectionsSupportCandidate(e, 4 ,30 ,0 ); //1 vote for #30

    mtmElectionsSupportCandidate(e, 5 ,27 ,3 );
    mtmElectionsSupportCandidate(e, 5 ,28 ,4 );
    mtmElectionsSupportCandidate(e, 5 ,29 ,2 ); //1 vote for #29
    mtmElectionsSupportCandidate(e, 5 ,30 ,6 );

    mtmElectionsSupportCandidate(e, 6 ,27 ,1 ); //3 votes for #27
    mtmElectionsSupportCandidate(e, 6 ,28 ,1 );
    mtmElectionsSupportCandidate(e, 6 ,29 ,1 );
    assert(mtmElectionsSupportCandidate(e, 6 ,30 ,1 )==MTM_ELECTIONS_PRIORITY_EXISTS);

    assert(mtmElectionsSupportCandidate(NULL, 6 ,27 ,1 )==MTM_ELECTIONS_NULL_ARGUMENT); //3 v
    assert(mtmElectionsSupportCandidate(e, -6 ,28 ,1 )==MTM_ELECTIONS_ILLEGAL_ID);
    assert(mtmElectionsSupportCandidate(e, 6 ,-29 ,1 )==MTM_ELECTIONS_ILLEGAL_ID);
    assert(mtmElectionsSupportCandidate(e, 6 ,30 ,-1 )==MTM_ELECTIONS_ILLEGAL_PRIORITY);
    assert(mtmElectionsSupportCandidate(e, 31 ,27 ,5 )==MTM_ELECTIONS_NOT_SAME_CITY);


    mtmElectionsSupportCandidate(e, 7 ,27 ,5 );
    mtmElectionsSupportCandidate(e, 7 ,28 ,5 );
    mtmElectionsSupportCandidate(e, 7 ,29 ,5 );
    mtmElectionsSupportCandidate(e, 7 ,30 ,2 ); // 2 votes for #30

    //mtmElectionsSupportCandidate(e, 7 ,30 ,5 );//2 votes for #29
    //mtmElectionsSupportCandidate(e, 7 ,29 ,3 );//########!!!!#############3
    assert(mtmElectionsSupportCandidate(e, 7 ,30 ,0 )==MTM_ELECTIONS_ALREADY_SUPPORTED);
    assert(mtmElectionsSupportCandidate(e, 7 ,30 ,2 )==MTM_ELECTIONS_ALREADY_SUPPORTED);

    mtmElectionsSupportCandidate(e, 8 ,27 ,5 );//3 votes for #29
    mtmElectionsSupportCandidate(e, 8 ,28 ,3 );
    mtmElectionsSupportCandidate(e, 8 ,29 ,0 );
    mtmElectionsSupportCandidate(e, 8 ,30 ,2 );

    mtmElectionsSupportCandidate(e, 9 ,29 ,5 );
    mtmElectionsSupportCandidate(e, 9 ,29 ,3 );// 4 votes for #29
    mtmElectionsSupportCandidate(e, 9 ,30 ,10 );
    mtmElectionsSupportCandidate(e, 9 ,28 ,10 );

    mtmElectionsSupportCandidate(e, 10 ,27 ,5 );
    mtmElectionsSupportCandidate(e, 10 ,28 ,3 );//2 votes for #28
    mtmElectionsSupportCandidate(e, 10 ,29 ,10 );
    mtmElectionsSupportCandidate(e, 10 ,30 ,10 );

    mtmElectionsSupportCandidate(e, 11 ,27 ,1);//4 votes for 27
    mtmElectionsSupportCandidate(e, 11 ,28 ,2 );
    mtmElectionsSupportCandidate(e, 11 ,29 ,30 );
    mtmElectionsSupportCandidate(e, 11 ,30 ,10 );

    assert(mtmElectionsSupportCandidate(e, 12 ,27 ,10 )==MTM_ELECTIONS_SUCCESS);
    mtmElectionsSupportCandidate(e, 12 ,28 ,10 );
    mtmElectionsSupportCandidate(e, 12 ,29 ,10 );
    mtmElectionsSupportCandidate(e, 12 ,30 ,1 ); //3 votes for 30

    mtmElectionsSupportCandidate(e, 13 ,27 ,5 );
    assert(mtmElectionsSupportCandidate(e, 13 ,27 ,3 )==MTM_ELECTIONS_ALREADY_SUPPORTED);
    mtmElectionsSupportCandidate(e, 13 ,29 ,4 ); //5 votes for #29
    mtmElectionsSupportCandidate(e, 13 ,30 ,10 );


    mtmElectionsSupportCandidate(e, 14 ,28 ,5 );
    mtmElectionsSupportCandidate(e, 14 ,27 ,3 ); // 5 votes for 27
    mtmElectionsSupportCandidate(e, 14 ,29 ,4 );
    mtmElectionsSupportCandidate(e, 14 ,30 ,10 );

    mtmElectionsSupportCandidate(e, 13 ,30 ,0 );
    mtmElectionsSupportCandidate(e, 14 ,30 ,0 );
    mtmElectionsSupportCandidate(e, 15 ,30 ,0 );
    mtmElectionsSupportCandidate(e, 16 ,30 ,0 );
    mtmElectionsSupportCandidate(e, 17 ,30 ,0 );
    mtmElectionsSupportCandidate(e, 18 ,30 ,0 );
    mtmElectionsSupportCandidate(e, 19 ,30 ,0 );
    mtmElectionsSupportCandidate(e, 20 ,2971 ,0 );
    mtmElectionsSupportCandidate(e, 21 ,2971 ,0 );
    mtmElectionsSupportCandidate(e, 22 ,2971 ,0 );
    mtmElectionsSupportCandidate(e, 23 ,2971 ,0 );
    mtmElectionsSupportCandidate(e, 24 ,2971 ,0 );
    mtmElectionsSupportCandidate(e, 25 ,2971 ,0 );
    mtmElectionsSupportCandidate(e, 26 ,2971 ,0 );



    assert(mtmElectionsCancelSupport(e, 35,  30)==MTM_ELECTIONS_NOT_SUPPORTED);
    assert(mtmElectionsCancelSupport(e, 36,  30)==MTM_ELECTIONS_CITIZEN_DOES_NOT_EXIST);
    assert(mtmElectionsCancelSupport(e, 11,  33)==MTM_ELECTIONS_CANDIDATE_DOES_NOT_EXIST);
    assert(mtmElectionsCancelSupport(e, -18,  30)==MTM_ELECTIONS_ILLEGAL_ID);
    assert(mtmElectionsCancelSupport(e, 18,  -30)==MTM_ELECTIONS_ILLEGAL_ID);
    assert(mtmElectionsCancelSupport(e, 15,  30)==MTM_ELECTIONS_SUCCESS);
    assert(mtmElectionsCancelSupport(e, 30,  30)==MTM_ELECTIONS_MUST_SUPPORT);
    assert(mtmElectionsCancelSupport(NULL, 17,  30)==MTM_ELECTIONS_NULL_ARGUMENT);
    assert(mtmElectionsCancelSupport(e, 18,  30)==MTM_ELECTIONS_SUCCESS);
    mtmElectionsCancelSupport(e, 17,  30);
    mtmElectionsCancelSupport(e, 18,  30);
    mtmElectionsCancelSupport(e, 19,  30);
    mtmElectionsCancelSupport(e, 20,  30);
    mtmElectionsCancelSupport(e, 21,  30);
    mtmElectionsCancelSupport(e, 22,  30);
    mtmElectionsCancelSupport(e, 23,  30);
    mtmElectionsCancelSupport(e, 24,  30);
    mtmElectionsCancelSupport(e, 25,  28);
    mtmElectionsCancelSupport(e, 26,  29);

    int y;
    int* x = &y;

    assert(MtmElectionsCitizenGetCity(NULL, 30,  x)==MTM_ELECTIONS_NULL_ARGUMENT);
    assert(MtmElectionsCitizenGetCity(e, -30,  x)==MTM_ELECTIONS_ILLEGAL_ID);
    assert(MtmElectionsCitizenGetCity(e, 300,  x)==MTM_ELECTIONS_CITIZEN_DOES_NOT_EXIST);
    MtmElectionsCitizenGetCity(e, 30,  x);
    assert(*x==1);
    MtmElectionsCitizenGetCity(e, 31,  x);
    assert(*x==2);

    assert(MtmElectionsCitizenGetAge(NULL, 30, x)==MTM_ELECTIONS_NULL_ARGUMENT);
    assert(MtmElectionsCitizenGetAge(e, -30, x)==MTM_ELECTIONS_ILLEGAL_ID);
    assert(MtmElectionsCitizenGetAge(e, 230, x)==MTM_ELECTIONS_CITIZEN_DOES_NOT_EXIST);
    MtmElectionsCitizenGetAge(e, 30, x);
    assert(*x==21);

    assert(MtmElectionsCitizenGetEducation(NULL, 30, x)==MTM_ELECTIONS_NULL_ARGUMENT);
    assert(MtmElectionsCitizenGetEducation(e, -30, x)==MTM_ELECTIONS_ILLEGAL_ID);
    assert(MtmElectionsCitizenGetEducation(e, 230, x)==MTM_ELECTIONS_CITIZEN_DOES_NOT_EXIST);
    MtmElectionsCitizenGetEducation(e, 30, x);
    assert(*x==12);

    assert(mtmElectionsWithdrawCandidate(NULL, 2971, 1)==MTM_ELECTIONS_NULL_ARGUMENT);
    assert(mtmElectionsWithdrawCandidate(e, -2971, 1)==MTM_ELECTIONS_ILLEGAL_ID);
    assert(mtmElectionsWithdrawCandidate(e, 2971, 6)==MTM_ELECTIONS_CITY_DOES_NOT_EXIST);
    assert(mtmElectionsWithdrawCandidate(e, 271, 1)==MTM_ELECTIONS_CANDIDATE_DOES_NOT_EXIST);
    assert(mtmElectionsWithdrawCandidate(e, 2971, 1)==MTM_ELECTIONS_SUCCESS);
    assert(mtmElectionsSupportCandidate(e, 12 ,2971 ,10 )==MTM_ELECTIONS_CANDIDATE_DOES_NOT_EXIST);

    int mayor;
   // ElectionsPrint(e);
    mtmElectionsMayorOfCity(e, 1, &mayor, "A");
    if(mayor==27)printf("sex");

    assert(mayor==27);

    assert(mtmElectionsChangeAddress(NULL ,2971, 2)==MTM_ELECTIONS_NULL_ARGUMENT);
    assert(mtmElectionsChangeAddress(e ,-2971, 2)==MTM_ELECTIONS_ILLEGAL_ID);
    assert(mtmElectionsChangeAddress(e ,2971, 32)==MTM_ELECTIONS_CITY_DOES_NOT_EXIST);
    assert(mtmElectionsChangeAddress(e ,291, 2)==MTM_ELECTIONS_CITIZEN_DOES_NOT_EXIST);
    assert(mtmElectionsChangeAddress(e ,2971, 2)==MTM_ELECTIONS_SUCCESS);
    assert(mtmElectionsChangeAddress(e ,2971, 1)==MTM_ELECTIONS_SUCCESS);
    assert(mtmElectionsAddCandidate(e, 2971, 1)==MTM_ELECTIONS_SUCCESS);
    assert(mtmElectionsChangeAddress(e ,2971, 2)==MTM_ELECTIONS_SUCCESS);
    assert(mtmElectionsAddCandidate(e, 2971, 1)==MTM_ELECTIONS_CITIZEN_DOES_NOT_EXIST);
    assert(mtmElectionsAddCandidate(e, 2971, 2)==MTM_ELECTIONS_SUCCESS);
    assert(mtmElectionsChangeAddress(e ,2971, 1)==MTM_ELECTIONS_SUCCESS);
    assert(mtmElectionsAddCandidate(e, 2971, 1)==MTM_ELECTIONS_SUCCESS);
    mtmElectionsSupportCandidate(e, 22 ,2971 ,0 );
    mtmElectionsSupportCandidate(e, 23 ,2971 ,0 );
    mtmElectionsSupportCandidate(e, 24 ,2971 ,0 );
    mtmElectionsSupportCandidate(e, 25 ,2971 ,0 );
    mtmElectionsSupportCandidate(e, 26 ,2971 ,0 );


    mtmElectionsMayorOfCity(e, 1, &mayor, "A");

    assert(mayor==2971);

    assert(mtmElectionsChangeAddress(e ,2971, 2)==MTM_ELECTIONS_SUCCESS);




    mtmElectionsMayorOfCity(e, 1, &mayor, "A");

    assert(mayor==27);


//##############################################################################3



// part 2


    for(int i=0; i<101; i++) {
        mtmElectionsAddCitizen(e, "a", 1000+i, 21, 12, 3);
    }


    for(int i=0; i<101; i++){

        mtmElectionsAddCandidate(e, 1000+i, 3);
    }



    mtmElectionsMayorOfCity(e, 3, &mayor, "A");

    assert(mayor==1100);


    for(int i=0; i<96; i++) {


        mtmElectionsWithdrawCandidate(e, 1000 + i, 3);
    }

//1096-1100 are candidates

    mtmElectionsSupportCandidate(e, 1000, 1096, 3);
    mtmElectionsSupportCandidate(e, 1000, 1097, 4);
    mtmElectionsSupportCandidate(e, 1000, 1098, 5);
    mtmElectionsSupportCandidate(e, 1000, 1099, 6);
    mtmElectionsSupportCandidate(e, 1000, 1100, 7);

    mtmElectionsSupportCandidate(e, 1001, 1096, 3);
    mtmElectionsSupportCandidate(e, 1001, 1097, 4);
    mtmElectionsSupportCandidate(e, 1001, 1098, 5);
    mtmElectionsSupportCandidate(e, 1001, 1099, 6);
    mtmElectionsSupportCandidate(e, 1001, 1100, 7);

    mtmElectionsSupportCandidate(e, 1002, 1096, 3);
    mtmElectionsSupportCandidate(e, 1002, 1097, 4);
    mtmElectionsSupportCandidate(e, 1002, 1098, 5);
    mtmElectionsSupportCandidate(e, 1002, 1099, 6);
    mtmElectionsSupportCandidate(e, 1002, 1100, 7);


    mtmElectionsSupportCandidate(e, 1003, 1096, 3);
    mtmElectionsSupportCandidate(e, 1003, 1097, 4);
    mtmElectionsSupportCandidate(e, 1003, 1098, 5);
    mtmElectionsSupportCandidate(e, 1003, 1099, 6);
    mtmElectionsSupportCandidate(e, 1003, 1100, 7);

    mtmElectionsSupportCandidate(e, 1004, 1096, 3);
    mtmElectionsSupportCandidate(e, 1004, 1097, 4);
    mtmElectionsSupportCandidate(e, 1004, 1098, 5);
    mtmElectionsSupportCandidate(e, 1004, 1099, 6);
    mtmElectionsSupportCandidate(e, 1004, 1100, 7);

    mtmElectionsSupportCandidate(e, 1004, 1096, 3);
    mtmElectionsSupportCandidate(e, 1004, 1097, 4);
    mtmElectionsSupportCandidate(e, 1004, 1098, 5);
    mtmElectionsSupportCandidate(e, 1004, 1099, 6);
    mtmElectionsSupportCandidate(e, 1004, 1100, 7);

    mtmElectionsSupportCandidate(e, 1005, 1096, 3);
    mtmElectionsSupportCandidate(e, 1005, 1097, 4);
    mtmElectionsSupportCandidate(e, 1005, 1098, 5);
    mtmElectionsSupportCandidate(e, 1005, 1099, 6);
    mtmElectionsSupportCandidate(e, 1005, 1100, 7);

    mtmElectionsSupportCandidate(e, 1006, 1096, 3);
    mtmElectionsSupportCandidate(e, 1006, 1097, 4);
    mtmElectionsSupportCandidate(e, 1006, 1098, 5);
    mtmElectionsSupportCandidate(e, 1006, 1099, 6);
    mtmElectionsSupportCandidate(e, 1006, 1100, 7);

    mtmElectionsSupportCandidate(e, 1007, 1096, 3);
    mtmElectionsSupportCandidate(e, 1007, 1097, 4);
    mtmElectionsSupportCandidate(e, 1007, 1098, 5);
    mtmElectionsSupportCandidate(e, 1007, 1099, 6);
    mtmElectionsSupportCandidate(e, 1007, 1100, 7);

    mtmElectionsSupportCandidate(e, 1008, 1096, 3);
    mtmElectionsSupportCandidate(e, 1008, 1097, 4);
    mtmElectionsSupportCandidate(e, 1008, 1098, 5);
    mtmElectionsSupportCandidate(e, 1008, 1099, 6);
    mtmElectionsSupportCandidate(e, 1008, 1100, 7);

    mtmElectionsSupportCandidate(e, 1009, 1096, 3);
    mtmElectionsSupportCandidate(e, 1009, 1097, 4);
    mtmElectionsSupportCandidate(e, 1009, 1098, 5);
    mtmElectionsSupportCandidate(e, 1009, 1099, 6);
    mtmElectionsSupportCandidate(e, 1009, 1100, 7);

    mtmElectionsSupportCandidate(e, 1010, 1096, 3);
    mtmElectionsSupportCandidate(e, 1010, 1097, 4);
    mtmElectionsSupportCandidate(e, 1010, 1098, 5);
    mtmElectionsSupportCandidate(e, 1010, 1099, 6);
    mtmElectionsSupportCandidate(e, 1010, 1100, 7);

    mtmElectionsSupportCandidate(e, 1011, 1096, 3);
    mtmElectionsSupportCandidate(e, 1011, 1097, 4);
    mtmElectionsSupportCandidate(e, 1011, 1098, 5);
    mtmElectionsSupportCandidate(e, 1011, 1099, 6);
    mtmElectionsSupportCandidate(e, 1011, 1100, 7);

    mtmElectionsWithdrawCandidate(e, 1096, 3);

    mtmElectionsMayorOfCity(e, 3, &mayor, "A");

    assert(mayor==1097);

    mtmElectionsChangeAddress(e, 1097, 2);

    mtmElectionsMayorOfCity(e, 3, &mayor, "A");

    assert(mayor==1098);

    // 1096, 1097 are dead.


    mtmElectionsWithdrawCandidate(e, 1098, 3);
    mtmElectionsWithdrawCandidate(e, 1099, 3);
    mtmElectionsWithdrawCandidate(e, 1010, 3);
    mtmElectionsWithdrawCandidate(e, 1096, 3);
    mtmElectionsWithdrawCandidate(e, 1095, 3);
    mtmElectionsWithdrawCandidate(e, 1100, 3);
    mtmElectionsWithdrawCandidate(e, 1101, 3);

    assert(mtmElectionsMayorOfCity(e, 3, &mayor, "A")==MTM_ELECTIONS_NO_CANDIDATES_IN_CITY);


    /////////////////////////////////////////////////////////
    int sml=1;

// Should have take the job at mcdolands. could have been easier

    mtmElectionsAddCity(e, "headache", 5);

    mtmElectionsAddCitizen(e,"a", 10000, 30, 30, 5);
    mtmElectionsAddCitizen(e,"a", 10001, 30, 30, 5);
    mtmElectionsAddCitizen(e,"a", 10002, 30, 30, 5);
    mtmElectionsAddCitizen(e,"a", 10003, 30, 30, 5);
    mtmElectionsAddCitizen(e,"a", 10004, 30, 30, 5);
    mtmElectionsAddCitizen(e,"a", 10005, 30, 30, 5);
    mtmElectionsAddCitizen(e,"a", 10006, 30, 30, 5);
    mtmElectionsAddCitizen(e,"a", 10007, 30, 30, 5);
    mtmElectionsAddCitizen(e,"a", 10008, 30, 30, 5);
    mtmElectionsAddCitizen(e,"a", 10009, 30, 30, 5);
    mtmElectionsAddCitizen(e,"a", 10010, 30, 30, 5);
    mtmElectionsAddCitizen(e,"a", 10011, 30, 30, 5);
    mtmElectionsAddCitizen(e,"a", 10012, 30, 30, 5);
    assert(mtmElectionsAddCitizen(e,"a", 10013, 30, 30, 5)==MTM_ELECTIONS_SUCCESS);
    mtmElectionsAddCitizen(e,"a", 10014, 30, 30, 5);
    mtmElectionsAddCitizen(e,"a", 10015, 30, 30, 5);
    mtmElectionsAddCitizen(e,"a", 10016, 30, 30, 5);
    mtmElectionsAddCitizen(e,"a", 10017, 30, 30, 5);
    mtmElectionsAddCitizen(e,"a", 10018, 30, 30, 5);

    mtmElectionsAddCitizen(e,"a", 10019, 30, 30, 5);
    mtmElectionsAddCitizen(e,"a", 10020, 30, 30, 5);
    mtmElectionsAddCitizen(e,"a", 10030, 30, 30, 5);


    mtmElectionsAddCandidate(e, 10000, 5);
    mtmElectionsAddCandidate(e, 10001, 5);
    mtmElectionsAddCandidate(e, 10002, 5);
    mtmElectionsAddCandidate(e, 10003, 5);
    mtmElectionsAddCandidate(e, 10004, 5);

    MtmElectionsCitizenGetCity(e, 10030, x);

    assert(*x==5);


    mtmElectionsChangeAddress(e, 10030, 3);


    MtmElectionsCitizenGetCity(e, 10030, x);

    assert(*x==3);

    mtmElectionsChangeAddress(e, 10030, 5);
    MtmElectionsCitizenGetCity(e, 10030, x);


    assert(*x==5);

    mtmElectionsChangeAddress(e, 10030, 1);

    assert(mtmElectionsAddCandidate(e, 10030, 1)==MTM_ELECTIONS_SUCCESS);
    assert(mtmElectionsAddCandidate(e, 10030, 5)==MTM_ELECTIONS_CITIZEN_DOES_NOT_EXIST);
    mtmElectionsChangeAddress(e, 10030, 5);

    assert(mtmElectionsSupportCandidate(e, 10005, 10000, 1)==MTM_ELECTIONS_SUCCESS);
    mtmElectionsSupportCandidate(e, 10005, 10001, 2);
    mtmElectionsSupportCandidate(e, 10005, 10002, 3);
    mtmElectionsSupportCandidate(e, 10005, 10003, 4);
    mtmElectionsSupportCandidate(e, 10005, 10004, 5);

    mtmElectionsSupportCandidate(e, 10006, 10000, 1);
    mtmElectionsSupportCandidate(e, 10006, 10001, 2);
    mtmElectionsSupportCandidate(e, 10006, 10002, 3);
    mtmElectionsSupportCandidate(e, 10006, 10003, 4);
    assert(mtmElectionsSupportCandidate(e, 10006, 10004, 0)==MTM_ELECTIONS_SUCCESS);

    mtmElectionsSupportCandidate(e, 10007, 10000, 1);
    mtmElectionsSupportCandidate(e, 10007, 10001, 2);
    assert(mtmElectionsSupportCandidate(e, 10007, 10002, 0)==MTM_ELECTIONS_SUCCESS);
    mtmElectionsSupportCandidate(e, 10007, 10003, 4);
    mtmElectionsSupportCandidate(e, 10007, 10004, 5);

    mtmElectionsSupportCandidate(e, 10008, 10000, 1);
    mtmElectionsSupportCandidate(e, 10008, 10001, 2);
    mtmElectionsSupportCandidate(e, 10008, 10002, 3);
    mtmElectionsSupportCandidate(e, 10008, 10003, 0);
    mtmElectionsSupportCandidate(e, 10008, 10004, 5);

    mtmElectionsSupportCandidate(e, 10009, 10000, 1);
    mtmElectionsSupportCandidate(e, 10009, 10001, 2);
    mtmElectionsSupportCandidate(e, 10009, 10002, 3);
    mtmElectionsSupportCandidate(e, 10009, 10003, 4);
    assert(mtmElectionsSupportCandidate(e, 10009, 10004, 0)==MTM_ELECTIONS_SUCCESS);

    mtmElectionsSupportCandidate(e, 10010, 10000, 1);
    mtmElectionsSupportCandidate(e, 10010, 10001, 0);
    mtmElectionsSupportCandidate(e, 10010, 10002, 3);
    mtmElectionsSupportCandidate(e, 10010, 10003, 4);
    mtmElectionsSupportCandidate(e, 10010, 10004, 5);

    mtmElectionsSupportCandidate(e, 10011, 10000, 0);
    mtmElectionsSupportCandidate(e, 10011, 10001, 2);
    mtmElectionsSupportCandidate(e, 10011, 10002, 3);
    mtmElectionsSupportCandidate(e, 10011, 10003, 4);
    mtmElectionsSupportCandidate(e, 10011, 10004, 5);

    mtmElectionsSupportCandidate(e, 10012, 10000, 1);
    mtmElectionsSupportCandidate(e, 10012, 10001, 0);
    mtmElectionsSupportCandidate(e, 10012, 10002, 3);
    mtmElectionsSupportCandidate(e, 10012, 10003, 4);
    mtmElectionsSupportCandidate(e, 10012, 10004, 5);

    mtmElectionsSupportCandidate(e, 10013, 10000, 1);
    mtmElectionsSupportCandidate(e, 10013, 10001, 2);
    mtmElectionsSupportCandidate(e, 10013, 10002, 3);
    mtmElectionsSupportCandidate(e, 10013, 10003, 4);
    assert(mtmElectionsSupportCandidate(e, 10013, 10004, 0)==MTM_ELECTIONS_SUCCESS);

    mtmElectionsSupportCandidate(e, 10014, 10000, 1);
    mtmElectionsSupportCandidate(e, 10014, 10001, 2);
    mtmElectionsSupportCandidate(e, 10014, 10002, 3);
    mtmElectionsSupportCandidate(e, 10014, 10003, 0);
    mtmElectionsSupportCandidate(e, 10014, 10004, 5);


    assert(mtmElectionsSupportCandidate(e, 10015, 10000, 0)==MTM_ELECTIONS_SUCCESS);
    mtmElectionsSupportCandidate(e, 10015, 10001, 2);
    mtmElectionsSupportCandidate(e, 10015, 10002, 3);
    mtmElectionsSupportCandidate(e, 10015, 10003, 4);
    mtmElectionsSupportCandidate(e, 10015, 10004, 5);

    mtmElectionsSupportCandidate(e, 10016, 10000, 1);
    mtmElectionsSupportCandidate(e, 10016, 10001, 0);
    mtmElectionsSupportCandidate(e, 10016, 10002, 3);
    mtmElectionsSupportCandidate(e, 10016, 10003, 4);
    mtmElectionsSupportCandidate(e, 10016, 10004, 5);

    mtmElectionsSupportCandidate(e, 10017, 10000, 1);
    mtmElectionsSupportCandidate(e, 10017, 10001, 2);
    assert(mtmElectionsSupportCandidate(e, 10017, 10002, 0)==MTM_ELECTIONS_SUCCESS);
    mtmElectionsSupportCandidate(e, 10017, 10003, 4);
    mtmElectionsSupportCandidate(e, 10017, 10004, 5);

    mtmElectionsSupportCandidate(e, 10018, 10000, 1);
    mtmElectionsSupportCandidate(e, 10018, 10001, 2);
    assert(mtmElectionsSupportCandidate(e, 10018, 10002, 0)==MTM_ELECTIONS_SUCCESS);
    mtmElectionsSupportCandidate(e, 10018, 10003, 4);
    mtmElectionsSupportCandidate(e, 10018, 10004, 5);

    mtmElectionsSupportCandidate(e, 10019, 10000, 1);
    mtmElectionsSupportCandidate(e, 10019, 10001, 2);
    mtmElectionsSupportCandidate(e, 10019, 10002, 3);
    mtmElectionsSupportCandidate(e, 10019, 10003, 4);
    assert(mtmElectionsSupportCandidate(e, 10019, 10004, 0)==MTM_ELECTIONS_SUCCESS);

    mtmElectionsSupportCandidate(e, 10020, 10000, 1);
    assert(mtmElectionsSupportCandidate(e, 10020, 10001, 2)==MTM_ELECTIONS_SUCCESS);
    mtmElectionsSupportCandidate(e, 10020, 10002, 3);
    mtmElectionsSupportCandidate(e, 10020, 10003, 0);
    mtmElectionsSupportCandidate(e, 10020, 10004, 5);


    //4,4,4,4,4


    mtmElectionsMayorOfCity(e, 5, &mayor, "A");

    assert(mayor==10004);


    mtmElectionsWithdrawCandidate(e, 10004, 5);


    mtmElectionsMayorOfCity(e, 5, &mayor, "A");

    assert(mayor==10000);

    assert(mtmElectionsCancelSupport(e, 10015, 10000)==MTM_ELECTIONS_SUCCESS);
    mtmElectionsCancelSupport(e, 10013, 10000);
    mtmElectionsCancelSupport(e, 10011, 10000);
    mtmElectionsCancelSupport(e, 10009, 10000);
    mtmElectionsCancelSupport(e, 10012, 10000);
    mtmElectionsCancelSupport(e, 10014, 10000);
    mtmElectionsCancelSupport(e, 10016, 10000);
    mtmElectionsCancelSupport(e, 10018, 10000);
    mtmElectionsCancelSupport(e, 10020, 10000);

    mtmElectionsMayorOfCity(e, 5, &mayor, "A");

    assert(mayor==10001);

    mtmElectionsCancelSupport(e, 10013, 10001);
    mtmElectionsCancelSupport(e, 10011, 10001);
    mtmElectionsCancelSupport(e, 10009, 10001);
    mtmElectionsCancelSupport(e, 10012, 10001);
    mtmElectionsCancelSupport(e, 10014, 10001);
    mtmElectionsCancelSupport(e, 10016, 10001);
    mtmElectionsCancelSupport(e, 10018, 10001);
    mtmElectionsCancelSupport(e, 10020, 10001);

    mtmElectionsMayorOfCity(e, 5, &mayor, "A");

    assert(mayor==10002);

    mtmElectionsWithdrawCandidate(e, 10002, 5);


    mtmElectionsMayorOfCity(e, 5, &mayor, "A");

    assert(mayor==10003);


    assert(mtmElectionsCancelSupport(e, 10020, 10000)==MTM_ELECTIONS_NOT_SUPPORTED);
    assert(mtmElectionsSupportCandidate(e, 10020, 10000, 1)==MTM_ELECTIONS_SUCCESS);
    assert(mtmElectionsCancelSupport(e, 10020, 10000)==MTM_ELECTIONS_SUCCESS);
    assert(mtmElectionsCancelSupport(e, 10020, 10000)==MTM_ELECTIONS_NOT_SUPPORTED);
    assert(mtmElectionsCancelSupport(e, 20020, 10000)==MTM_ELECTIONS_CITIZEN_DOES_NOT_EXIST);
    assert(mtmElectionsCancelSupport(e, 10020, 30000)==MTM_ELECTIONS_CANDIDATE_DOES_NOT_EXIST);


    assert(mtmElectionsAddCity(e, "paris", 1)==MTM_ELECTIONS_CITY_ALREADY_EXISTS);
    mtmElectionsAddCity(e, "paris", 100);

    assert(mtmElectionsAddCitizen(e, "a",10000, 23,14, 100)==MTM_ELECTIONS_CITIZEN_ALREADY_EXISTS);
    mtmElectionsAddCitizen(e, "a",1111, 23,14, 100);
    assert(mtmElectionsAddCandidate(e, 1111, 1)==MTM_ELECTIONS_CITIZEN_DOES_NOT_EXIST);
    assert(mtmElectionsAddCandidate(e, 1111, 100)==MTM_ELECTIONS_SUCCESS);

    mtmElectionsMayorOfCity(e, 100, &mayor, "A");

    assert(mayor==1111);

    assert(mtmElectionsWithdrawCandidate(e,1111,100)==MTM_ELECTIONS_SUCCESS);

    assert(mtmElectionsMayorOfCity(e, 100, &mayor, "A")==MTM_ELECTIONS_NO_CANDIDATES_IN_CITY);

    assert(mtmElectionsAddCandidate(e, 1111, 100)==MTM_ELECTIONS_SUCCESS);


    mtmElectionsMayorOfCity(e, 100, &mayor, "A");

    assert(mayor==1111);

    mtmElectionsChangeAddress(e, 10000, 100);

    mtmElectionsAddCandidate(e, 10000, 100);

    mtmElectionsMayorOfCity(e, 100, &mayor, "A");

    assert(mayor==10000);

    mtmElectionsChangeAddress(e, 10000, 1);

    mtmElectionsMayorOfCity(e, 100, &mayor, "A");

    assert(mayor==1111);

    mtmElectionsChangeAddress(e, 1111, 1);

    assert(mtmElectionsMayorOfCity(e, 100, &mayor, "A")==MTM_ELECTIONS_NO_CANDIDATES_IN_CITY);

    mtmElectionsChangeAddress(e, 1, 100);
    mtmElectionsChangeAddress(e, 2, 100);
    mtmElectionsChangeAddress(e, 3, 100);
    mtmElectionsChangeAddress(e, 4, 100);
    mtmElectionsChangeAddress(e, 5, 100);
    mtmElectionsChangeAddress(e, 6, 100);
    mtmElectionsChangeAddress(e, 7, 100);
    mtmElectionsChangeAddress(e, 8, 100);
    mtmElectionsChangeAddress(e, 9, 100);
    mtmElectionsChangeAddress(e, 10, 100);
    mtmElectionsChangeAddress(e, 11, 100);
    mtmElectionsChangeAddress(e, 12, 100);
    mtmElectionsChangeAddress(e, 13, 100);
    mtmElectionsChangeAddress(e, 14, 100);
    mtmElectionsChangeAddress(e, 15, 100);
    mtmElectionsChangeAddress(e, 16, 100);
    mtmElectionsChangeAddress(e, 17, 100);
    mtmElectionsChangeAddress(e, 18, 100);
    mtmElectionsChangeAddress(e, 19, 100);
    mtmElectionsChangeAddress(e, 20, 100);
    mtmElectionsChangeAddress(e, 21, 100);
    mtmElectionsChangeAddress(e, 22, 100);
    mtmElectionsChangeAddress(e, 23, 100);
    mtmElectionsChangeAddress(e, 24, 100);
    mtmElectionsChangeAddress(e, 25, 100);
    mtmElectionsChangeAddress(e, 26, 100);
    mtmElectionsChangeAddress(e, 27, 100);
    mtmElectionsChangeAddress(e, 28, 100);
    mtmElectionsChangeAddress(e, 29, 100);
    mtmElectionsChangeAddress(e, 30, 100);
    mtmElectionsChangeAddress(e, 2971, 100);
    mtmElectionsChangeAddress(e, 35, 100);

    assert(mtmElectionsAddCandidate(e, 2971, 1)==MTM_ELECTIONS_CITIZEN_DOES_NOT_EXIST);
    assert(mtmElectionsAddCandidate(e, 30, 100)==MTM_ELECTIONS_SUCCESS);

    for(int i=1; i<20; i++){


        assert(mtmElectionsAddCandidate(e,i , 100)==MTM_ELECTIONS_SUCCESS);


    }



    mtmElectionsAddCitizen(e, "a",11111, 23,14, 100);
    mtmElectionsAddCitizen(e, "b",1111111, 23,14, 100);

    assert(mtmElectionsAddCandidate(e, 11111, 100)==MTM_ELECTIONS_SUCCESS);
    assert(mtmElectionsAddCandidate(e, 1111111, 100)==MTM_ELECTIONS_SUCCESS);

    mtmElectionsMayorOfCity(e, 100, &mayor, "A");

    assert(mayor==11111);

    mtmElectionsWithdrawCandidate(e, 11111, 100);
    assert(mtmElectionsWithdrawCandidate(e, 11111, 100)==MTM_ELECTIONS_CANDIDATE_DOES_NOT_EXIST);

    mtmElectionsMayorOfCity(e, 100, &mayor, "A");

    assert(mayor==30);


    for(int i=1; i<20; i++) {

        assert(mtmElectionsChangeAddress(e, i, 1)==MTM_ELECTIONS_SUCCESS);


    }


    for(int i=1; i<20; i++){


        assert(mtmElectionsAddCandidate(e,i , 100)==MTM_ELECTIONS_CITIZEN_DOES_NOT_EXIST);


    }


    for(int i=1; i<20; i++){


        assert(mtmElectionsAddCandidate(e,i , 100)==MTM_ELECTIONS_CITIZEN_DOES_NOT_EXIST);


    }


    for(int i=1; i<20; i++) {

        assert(mtmElectionsChangeAddress(e, i, 100)==MTM_ELECTIONS_SUCCESS);


    }


    for(int i=1; i<20; i++){


        assert(mtmElectionsAddCandidate(e,i , 100)==MTM_ELECTIONS_SUCCESS);


    }


    MtmElections p = mtmElectionsCreate();

    mtmElectionsAddCity(p, "haifa", 1);
    mtmElectionsAddCity(p, "tel-aviv", 2);
    mtmElectionsAddCity(p, "natania", 3);
    mtmElectionsAddCity(p, "jerusalem", 4);
    mtmElectionsAddCity(p, "lud", 5);

    mtmElectionsAddCitizen(p, "a",1, 21,12, 1);
    mtmElectionsAddCitizen(p, "a",2, 21,12, 1);
    mtmElectionsAddCitizen(p, "a",3, 21,12, 1);
    mtmElectionsAddCitizen(p, "a",4, 21,12, 1);
    mtmElectionsAddCitizen(p, "a",5, 21,12, 1);
    mtmElectionsAddCitizen(p, "a",6, 21,12, 1);
    mtmElectionsAddCitizen(p, "a",7, 21,12, 1);
    mtmElectionsAddCitizen(p, "a",8, 21,12, 1);
    mtmElectionsAddCitizen(p, "a",9, 21,12, 1);
    mtmElectionsAddCitizen(p, "a",10, 21,12, 1);
    mtmElectionsAddCitizen(p, "a",11, 21,12, 1);
    mtmElectionsAddCitizen(p, "a",12, 21,12, 1);
    mtmElectionsAddCitizen(p, "a",13, 21,12, 1);
    mtmElectionsAddCitizen(p, "a",14, 21,12, 1);
    mtmElectionsAddCitizen(p, "a",15, 21,12, 1);
    mtmElectionsAddCitizen(p, "a",16, 21,12, 1);
    mtmElectionsAddCitizen(p, "a",17, 21,12, 1);
    mtmElectionsAddCitizen(p, "b",18, 21,12, 1);
    mtmElectionsAddCitizen(p, "a",19, 21,12, 1);
    mtmElectionsAddCitizen(p, "a",20, 21,12, 1);

    mtmElectionsAddCitizen(p, "a",100, 21,12, 2);
    mtmElectionsAddCitizen(p, "a",101, 21,12, 2);
    mtmElectionsAddCitizen(p, "a",102, 21,12, 2);
    mtmElectionsAddCitizen(p, "a",103, 21,12, 2);
    mtmElectionsAddCitizen(p, "a",104, 21,12, 2);
    mtmElectionsAddCitizen(p, "a",105, 21,12, 2);
    mtmElectionsAddCitizen(p, "a",106, 21,12, 2);
    mtmElectionsAddCitizen(p, "a",107, 21,12, 2);
    mtmElectionsAddCitizen(p, "a",108, 21,12, 2);
    mtmElectionsAddCitizen(p, "a",109, 21,12, 2);
    mtmElectionsAddCitizen(p, "a",110, 21,12, 2);
    mtmElectionsAddCitizen(p, "a",111, 21,12, 2);
    mtmElectionsAddCitizen(p, "a",112, 21,12, 2);
    mtmElectionsAddCitizen(p, "a",113, 21,12, 2);
    mtmElectionsAddCitizen(p, "a",114, 21,12, 2);
    mtmElectionsAddCitizen(p, "a",115, 21,12, 2);
    mtmElectionsAddCitizen(p, "a",116, 21,12, 2);
    mtmElectionsAddCitizen(p, "a",117, 21,12, 2);
    mtmElectionsAddCitizen(p, "b",118, 21,12, 2);
    mtmElectionsAddCitizen(p, "a",119, 21,12, 2);
    mtmElectionsAddCitizen(p, "a",120, 21,12, 2);

    mtmElectionsAddCitizen(p, "a",200, 21,12, 3);
    mtmElectionsAddCitizen(p, "a",201, 21,12, 3);
    mtmElectionsAddCitizen(p, "a",202, 21,12, 3);
    mtmElectionsAddCitizen(p, "a",203, 21,12, 3);
    mtmElectionsAddCitizen(p, "a",204, 21,12, 3);
    mtmElectionsAddCitizen(p, "a",205, 21,12, 3);
    mtmElectionsAddCitizen(p, "a",206, 21,12, 3);
    mtmElectionsAddCitizen(p, "a",207, 21,12, 3);
    mtmElectionsAddCitizen(p, "a",208, 21,12, 3);
    mtmElectionsAddCitizen(p, "a",209, 21,12, 3);
    mtmElectionsAddCitizen(p, "a",210, 21,12, 3);
    mtmElectionsAddCitizen(p, "a",211, 21,12, 3);
    mtmElectionsAddCitizen(p, "a",212, 21,12, 3);
    mtmElectionsAddCitizen(p, "a",213, 21,12, 3);
    mtmElectionsAddCitizen(p, "a",214, 21,12, 3);
    mtmElectionsAddCitizen(p, "a",215, 21,12, 3);
    mtmElectionsAddCitizen(p, "a",216, 21,12, 3);
    mtmElectionsAddCitizen(p, "a",217, 21,12, 3);
    mtmElectionsAddCitizen(p, "z",218, 21,12, 3);
    mtmElectionsAddCitizen(p, "a",219, 21,12, 3);
    mtmElectionsAddCitizen(p, "a",220, 21,12, 3);

    mtmElectionsAddCitizen(p, "a",300, 21,12, 4);
    mtmElectionsAddCitizen(p, "a",301, 21,12, 4);
    mtmElectionsAddCitizen(p, "a",302, 21,12, 4);
    mtmElectionsAddCitizen(p, "a",303, 21,12, 4);
    mtmElectionsAddCitizen(p, "a",304, 21,12, 4);
    mtmElectionsAddCitizen(p, "a",305, 21,12, 4);
    mtmElectionsAddCitizen(p, "a",306, 21,12, 4);
    mtmElectionsAddCitizen(p, "a",307, 21,12, 4);
    mtmElectionsAddCitizen(p, "a",308, 21,12, 4);
    mtmElectionsAddCitizen(p, "a",309, 21,12, 4);
    mtmElectionsAddCitizen(p, "a",310, 21,12, 4);
    mtmElectionsAddCitizen(p, "a",311, 21,12, 4);
    mtmElectionsAddCitizen(p, "a",312, 21,12, 4);
    mtmElectionsAddCitizen(p, "a",313, 21,12, 4);
    mtmElectionsAddCitizen(p, "a",314, 21,12, 4);
    mtmElectionsAddCitizen(p, "a",315, 21,12, 4);
    mtmElectionsAddCitizen(p, "a",316, 21,12, 4);
    mtmElectionsAddCitizen(p, "a",317, 21,12, 4);
    mtmElectionsAddCitizen(p, "e",318, 21,12, 4);
    mtmElectionsAddCitizen(p, "a",319, 21,12, 4);
    mtmElectionsAddCitizen(p, "a",320, 21,12, 4);

    mtmElectionsAddCitizen(p, "z",417, 21,12, 5);
    mtmElectionsAddCitizen(p, "z",418, 21,12, 5);
    mtmElectionsAddCitizen(p, "z",419, 21,12, 5);
    mtmElectionsAddCitizen(p, "z",420, 21,12, 5);

    mtmElectionsAddCandidate(p,18, 1);
    mtmElectionsAddCandidate(p,19, 1);
    mtmElectionsAddCandidate(p,20, 1);

    mtmElectionsAddCandidate(p,118, 2);
    mtmElectionsAddCandidate(p,119, 2);
    mtmElectionsAddCandidate(p,120, 2);

    mtmElectionsAddCandidate(p,218, 3);
    mtmElectionsAddCandidate(p,219, 3);
    mtmElectionsAddCandidate(p,220, 3);

    mtmElectionsAddCandidate(p,318, 4);
    mtmElectionsAddCandidate(p,319, 4);
    mtmElectionsAddCandidate(p,320, 4);

    mtmElectionsAddCandidate(p,418, 5);
    mtmElectionsAddCandidate(p,419, 5);
    mtmElectionsAddCandidate(p,420, 5);


    mtmElectionsSupportCandidate(p, 1, 17 ,1);
    mtmElectionsSupportCandidate(p, 1, 18 ,0);
    mtmElectionsSupportCandidate(p, 1, 19 ,2); //1 vote for 18
    mtmElectionsSupportCandidate(p, 1, 20 ,3);

    mtmElectionsSupportCandidate(p, 2, 17 ,0);
    mtmElectionsSupportCandidate(p, 2, 18 ,1);
    mtmElectionsSupportCandidate(p, 2, 19 ,2);//1 vote for 19
    mtmElectionsSupportCandidate(p, 2, 20 ,3);

    mtmElectionsSupportCandidate(p, 3, 17 ,1);
    mtmElectionsSupportCandidate(p, 3, 18 ,3);
    mtmElectionsSupportCandidate(p, 3, 19 ,2);//1 vote 20
    mtmElectionsSupportCandidate(p, 3, 20 ,0);

    mtmElectionsSupportCandidate(p, 3, 17 ,1);//2 votes for 18
    mtmElectionsSupportCandidate(p, 3, 18 ,0);
    mtmElectionsSupportCandidate(p, 3, 19 ,2);
    mtmElectionsSupportCandidate(p, 3, 20 ,3);

    mtmElectionsSupportCandidate(p, 4, 17 ,1);
    mtmElectionsSupportCandidate(p, 4, 18 ,0); //3 votes for 18
    mtmElectionsSupportCandidate(p, 4, 19 ,2);
    mtmElectionsSupportCandidate(p, 4, 20 ,3);

    mtmElectionsSupportCandidate(p, 5, 17 ,1);
    mtmElectionsSupportCandidate(p, 5, 18 ,3);
    mtmElectionsSupportCandidate(p, 5, 19 ,2);
    mtmElectionsSupportCandidate(p, 5, 20 ,0);// 2 votes for 20

    mtmElectionsSupportCandidate(p, 6, 17 ,1);
    mtmElectionsSupportCandidate(p, 6, 18 ,3);
    mtmElectionsSupportCandidate(p, 6, 19 ,2); //3 votes for 20
    mtmElectionsSupportCandidate(p, 6, 20 ,0);

    mtmElectionsSupportCandidate(p, 7, 17 ,1);
    mtmElectionsSupportCandidate(p, 7, 18 ,2);
    mtmElectionsSupportCandidate(p, 7, 19 ,0); // 2 votes for 19
    mtmElectionsSupportCandidate(p, 7, 20 ,3);


    mtmElectionsSupportCandidate(p, 8, 17 ,1);
    mtmElectionsSupportCandidate(p, 8, 18 ,2);
    mtmElectionsSupportCandidate(p, 8, 19 ,0);
    mtmElectionsSupportCandidate(p, 8, 20 ,3); // 3 votes for 19


    mtmElectionsSupportCandidate(p, 9, 17 ,1);
    mtmElectionsSupportCandidate(p, 9, 18 ,0);
    mtmElectionsSupportCandidate(p, 9, 19 ,2); //4 vote for 18
    mtmElectionsSupportCandidate(p, 9, 20 ,3);

    mtmElectionsSupportCandidate(p, 10, 17 ,0);
    mtmElectionsSupportCandidate(p, 10, 18 ,1);
    mtmElectionsSupportCandidate(p, 10, 19 ,2);//4 votes for 19
    mtmElectionsSupportCandidate(p, 10, 20 ,3);

    mtmElectionsSupportCandidate(p, 11, 17 ,1);
    mtmElectionsSupportCandidate(p, 11, 18 ,3);
    mtmElectionsSupportCandidate(p, 11, 19 ,2);//4 vote 20
    mtmElectionsSupportCandidate(p, 11, 20 ,0);

    mtmElectionsSupportCandidate(p, 12, 17 ,1);//5 votes for 18
    mtmElectionsSupportCandidate(p, 12, 18 ,0);
    mtmElectionsSupportCandidate(p, 12, 19 ,2);
    mtmElectionsSupportCandidate(p, 12, 20 ,3);

    mtmElectionsSupportCandidate(p, 13, 17 ,1);
    mtmElectionsSupportCandidate(p, 13, 18 ,0); //6 votes for 18
    mtmElectionsSupportCandidate(p, 13, 19 ,2);
    mtmElectionsSupportCandidate(p, 13, 20 ,3);

    mtmElectionsSupportCandidate(p, 14, 17 ,1);
    mtmElectionsSupportCandidate(p, 14, 18 ,3);
    mtmElectionsSupportCandidate(p, 14, 19 ,2);
    mtmElectionsSupportCandidate(p, 14, 20 ,0);// 5 votes for 20

    mtmElectionsSupportCandidate(p, 15, 17 ,1);
    mtmElectionsSupportCandidate(p, 15, 18 ,3);
    mtmElectionsSupportCandidate(p, 15, 19 ,2); //6 votes for 20
    mtmElectionsSupportCandidate(p, 15, 20 ,0);

    mtmElectionsSupportCandidate(p, 16, 17 ,1);
    mtmElectionsSupportCandidate(p, 16, 18 ,2);
    mtmElectionsSupportCandidate(p, 16, 19 ,0); // 5 votes for 19
    mtmElectionsSupportCandidate(p, 16, 20 ,3);


    mtmElectionsSupportCandidate(p, 100, 117 ,1);
    mtmElectionsSupportCandidate(p, 100, 118 ,0);
    mtmElectionsSupportCandidate(p, 100, 119 ,2); //1 vote for 118
    mtmElectionsSupportCandidate(p, 100, 120 ,3);

    mtmElectionsSupportCandidate(p, 101, 117 ,0);
    mtmElectionsSupportCandidate(p, 101, 118 ,1);
    mtmElectionsSupportCandidate(p, 101, 119 ,2);//1 vote for 119
    mtmElectionsSupportCandidate(p, 101, 120 ,3);

    mtmElectionsSupportCandidate(p, 102, 117 ,1);
    mtmElectionsSupportCandidate(p, 102, 118 ,3);
    mtmElectionsSupportCandidate(p, 102, 119 ,2);//1 vote 120
    mtmElectionsSupportCandidate(p, 102, 120 ,0);

    mtmElectionsSupportCandidate(p, 103, 117 ,1);//2 votes for 118
    mtmElectionsSupportCandidate(p, 103, 118 ,0);
    mtmElectionsSupportCandidate(p, 103, 119 ,2);
    mtmElectionsSupportCandidate(p, 103, 120 ,3);

    mtmElectionsSupportCandidate(p, 104, 117 ,1);
    mtmElectionsSupportCandidate(p, 104, 118 ,0); //3 votes for 118
    mtmElectionsSupportCandidate(p, 104, 119 ,2);
    mtmElectionsSupportCandidate(p, 104, 120 ,3);

    mtmElectionsSupportCandidate(p, 105, 117 ,1);
    mtmElectionsSupportCandidate(p, 105, 118 ,3);
    mtmElectionsSupportCandidate(p, 105, 119 ,2);
    mtmElectionsSupportCandidate(p, 105, 120 ,0);// 2 votes for 120

    mtmElectionsSupportCandidate(p, 106, 117 ,1);
    mtmElectionsSupportCandidate(p, 106, 118 ,3);
    mtmElectionsSupportCandidate(p, 106, 119 ,2); //3 votes for 120
    mtmElectionsSupportCandidate(p, 106, 120 ,0);

    mtmElectionsSupportCandidate(p, 107, 117 ,1);
    mtmElectionsSupportCandidate(p, 107, 118 ,2);
    mtmElectionsSupportCandidate(p, 107, 119 ,0); // 2 votes for 119
    mtmElectionsSupportCandidate(p, 107, 120 ,3);


    mtmElectionsSupportCandidate(p, 108, 117 ,1);
    mtmElectionsSupportCandidate(p, 108, 118 ,2);
    mtmElectionsSupportCandidate(p, 108, 119 ,0);
    mtmElectionsSupportCandidate(p, 108, 120 ,3); // 3 votes for 119


    mtmElectionsSupportCandidate(p, 109, 117 ,1);
    mtmElectionsSupportCandidate(p, 109, 118 ,0);
    mtmElectionsSupportCandidate(p, 109, 119 ,2); //4 vote for 118
    mtmElectionsSupportCandidate(p, 109, 120 ,3);

    mtmElectionsSupportCandidate(p, 110, 117 ,0);
    mtmElectionsSupportCandidate(p, 110, 118 ,1);
    mtmElectionsSupportCandidate(p, 110, 119 ,2);//4 votes for 119
    mtmElectionsSupportCandidate(p, 110, 120 ,3);

    mtmElectionsSupportCandidate(p, 111, 117 ,1);
    mtmElectionsSupportCandidate(p, 111, 118 ,3);
    mtmElectionsSupportCandidate(p, 111, 119 ,2);//4 vote 120
    mtmElectionsSupportCandidate(p, 111, 120 ,0);

    mtmElectionsSupportCandidate(p, 112, 117 ,1);//5 votes for 118
    mtmElectionsSupportCandidate(p, 112, 118 ,0);
    mtmElectionsSupportCandidate(p, 112, 119 ,2);
    mtmElectionsSupportCandidate(p, 112, 120 ,3);

    mtmElectionsSupportCandidate(p, 113, 117 ,1);
    mtmElectionsSupportCandidate(p, 113, 118 ,0); //6 votes for 118
    mtmElectionsSupportCandidate(p, 113, 119 ,2);
    mtmElectionsSupportCandidate(p, 113, 120 ,3);

    mtmElectionsSupportCandidate(p, 114, 117 ,1);
    mtmElectionsSupportCandidate(p, 114, 118 ,3);
    mtmElectionsSupportCandidate(p, 114, 119 ,2);
    mtmElectionsSupportCandidate(p, 114, 120 ,0);// 5 votes for 120

    mtmElectionsSupportCandidate(p, 115, 117 ,1);
    mtmElectionsSupportCandidate(p, 115, 118 ,3);
    mtmElectionsSupportCandidate(p, 115, 119 ,2); //6 votes for 120
    mtmElectionsSupportCandidate(p, 115, 120 ,0);

    mtmElectionsSupportCandidate(p, 116, 117 ,1);
    mtmElectionsSupportCandidate(p, 116, 118 ,2);
    mtmElectionsSupportCandidate(p, 116, 119 ,0); // 5 votes for 119
    mtmElectionsSupportCandidate(p, 116, 120 ,3);


    mtmElectionsSupportCandidate(p, 200, 217 ,1);
    mtmElectionsSupportCandidate(p, 200, 218 ,0);
    mtmElectionsSupportCandidate(p, 200, 219 ,2); //1 vote for 218
    mtmElectionsSupportCandidate(p, 200, 220 ,3);

    mtmElectionsSupportCandidate(p, 201, 217 ,0);
    mtmElectionsSupportCandidate(p, 201, 218 ,1);
    mtmElectionsSupportCandidate(p, 201, 219 ,2);//1 vote for 219
    mtmElectionsSupportCandidate(p, 201, 220 ,3);

    mtmElectionsSupportCandidate(p, 202, 217 ,1);
    mtmElectionsSupportCandidate(p, 202, 218 ,3);
    mtmElectionsSupportCandidate(p, 202, 219 ,2);//1 vote 220
    mtmElectionsSupportCandidate(p, 202, 220 ,0);

    mtmElectionsSupportCandidate(p, 203, 217 ,1);//2 votes for 218
    mtmElectionsSupportCandidate(p, 203, 218 ,0);
    mtmElectionsSupportCandidate(p, 203, 219 ,2);
    mtmElectionsSupportCandidate(p, 203, 220 ,3);

    mtmElectionsSupportCandidate(p, 204, 217 ,1);
    mtmElectionsSupportCandidate(p, 204, 218 ,0); //3 votes for 218
    mtmElectionsSupportCandidate(p, 204, 219 ,2);
    mtmElectionsSupportCandidate(p, 204, 220 ,3);

    mtmElectionsSupportCandidate(p, 205, 217 ,1);
    mtmElectionsSupportCandidate(p, 205, 218 ,3);
    mtmElectionsSupportCandidate(p, 205, 219 ,2);
    mtmElectionsSupportCandidate(p, 205, 220 ,0);// 2 votes for 220

    mtmElectionsSupportCandidate(p, 206, 217 ,1);
    mtmElectionsSupportCandidate(p, 206, 218 ,3);
    mtmElectionsSupportCandidate(p, 206, 219 ,2); //3 votes for 220
    mtmElectionsSupportCandidate(p, 206, 220 ,0);

    mtmElectionsSupportCandidate(p, 207, 217 ,1);
    mtmElectionsSupportCandidate(p, 207, 218 ,2);
    mtmElectionsSupportCandidate(p, 207, 219 ,0); // 2 votes for 219
    mtmElectionsSupportCandidate(p, 207, 220 ,3);


    mtmElectionsSupportCandidate(p, 208, 217 ,1);
    mtmElectionsSupportCandidate(p, 208, 218 ,2);
    mtmElectionsSupportCandidate(p, 208, 219 ,0);
    mtmElectionsSupportCandidate(p, 208, 220 ,3); // 3 votes for 219


    mtmElectionsSupportCandidate(p, 209, 217 ,1);
    mtmElectionsSupportCandidate(p, 209, 218 ,0);
    mtmElectionsSupportCandidate(p, 209, 219 ,2); //4 vote for 218
    mtmElectionsSupportCandidate(p, 209, 220 ,3);

    mtmElectionsSupportCandidate(p, 210, 217 ,0);
    mtmElectionsSupportCandidate(p, 210, 218 ,1);
    mtmElectionsSupportCandidate(p, 210, 219 ,2);//4 votes for 219
    mtmElectionsSupportCandidate(p, 210, 220 ,3);

    mtmElectionsSupportCandidate(p, 211, 217 ,1);
    mtmElectionsSupportCandidate(p, 211, 218 ,3);
    mtmElectionsSupportCandidate(p, 211, 219 ,2);//4 vote 220
    mtmElectionsSupportCandidate(p, 211, 220 ,0);

    mtmElectionsSupportCandidate(p, 212, 217 ,1);//5 votes for 218
    mtmElectionsSupportCandidate(p, 212, 218 ,0);
    mtmElectionsSupportCandidate(p, 212, 219 ,2);
    mtmElectionsSupportCandidate(p, 212, 220 ,3);

    mtmElectionsSupportCandidate(p, 213, 217 ,1);
    mtmElectionsSupportCandidate(p, 213, 218 ,0); //6 votes for 218
    mtmElectionsSupportCandidate(p, 213, 219 ,2);
    mtmElectionsSupportCandidate(p, 213, 220 ,3);

    mtmElectionsSupportCandidate(p, 214, 217 ,1);
    mtmElectionsSupportCandidate(p, 214, 218 ,3);
    mtmElectionsSupportCandidate(p, 214, 219 ,2);
    mtmElectionsSupportCandidate(p, 214, 220 ,0);// 5 votes for 220

    mtmElectionsSupportCandidate(p, 215, 217 ,1);
    mtmElectionsSupportCandidate(p, 215, 218 ,3);
    mtmElectionsSupportCandidate(p, 215, 219 ,2); //6 votes for 220
    mtmElectionsSupportCandidate(p, 215, 220 ,0);

    mtmElectionsSupportCandidate(p, 216, 217 ,1);
    mtmElectionsSupportCandidate(p, 216, 218 ,2);
    mtmElectionsSupportCandidate(p, 216, 219 ,0); // 5 votes for 219
    mtmElectionsSupportCandidate(p, 216, 220 ,3);


    mtmElectionsSupportCandidate(p, 300, 317 ,1);
    mtmElectionsSupportCandidate(p, 300, 318 ,0);
    mtmElectionsSupportCandidate(p, 300, 319 ,2); //1 vote for 318
    mtmElectionsSupportCandidate(p, 300, 320 ,3);

    mtmElectionsSupportCandidate(p, 301, 317 ,0);
    mtmElectionsSupportCandidate(p, 301, 318 ,1);
    mtmElectionsSupportCandidate(p, 301, 319 ,2);//1 vote for 319
    mtmElectionsSupportCandidate(p, 301, 320 ,3);

    mtmElectionsSupportCandidate(p, 302, 317 ,1);
    mtmElectionsSupportCandidate(p, 302, 318 ,3);
    mtmElectionsSupportCandidate(p, 302, 319 ,2);//1 vote 320
    mtmElectionsSupportCandidate(p, 302, 320 ,0);

    mtmElectionsSupportCandidate(p, 303, 317 ,1);//2 votes for 318
    mtmElectionsSupportCandidate(p, 303, 318 ,0);
    mtmElectionsSupportCandidate(p, 303, 319 ,2);
    mtmElectionsSupportCandidate(p, 303, 320 ,3);

    mtmElectionsSupportCandidate(p, 304, 317 ,1);
    mtmElectionsSupportCandidate(p, 304, 318 ,0); //3 votes for 318
    mtmElectionsSupportCandidate(p, 304, 319 ,2);
    mtmElectionsSupportCandidate(p, 304, 320 ,3);

    mtmElectionsSupportCandidate(p, 305, 317 ,1);
    mtmElectionsSupportCandidate(p, 305, 318 ,3);
    mtmElectionsSupportCandidate(p, 305, 319 ,2);
    mtmElectionsSupportCandidate(p, 305, 320 ,0);// 2 votes for 320

    mtmElectionsSupportCandidate(p, 306, 317 ,1);
    mtmElectionsSupportCandidate(p, 306, 318 ,3);
    mtmElectionsSupportCandidate(p, 306, 319 ,2); //3 votes for 320
    mtmElectionsSupportCandidate(p, 306, 320 ,0);

    mtmElectionsSupportCandidate(p, 307, 317 ,1);
    mtmElectionsSupportCandidate(p, 307, 318 ,2);
    mtmElectionsSupportCandidate(p, 307, 319 ,0); // 2 votes for 319
    mtmElectionsSupportCandidate(p, 307, 320 ,3);

    mtmElectionsSupportCandidate(p, 308, 317 ,1);
    mtmElectionsSupportCandidate(p, 308, 318 ,2);
    mtmElectionsSupportCandidate(p, 308, 319 ,0);
    mtmElectionsSupportCandidate(p, 308, 320 ,3); // 3 votes for 319


    mtmElectionsSupportCandidate(p, 309, 317 ,1);
    mtmElectionsSupportCandidate(p, 309, 318 ,0);
    mtmElectionsSupportCandidate(p, 309, 319 ,2); //4 vote for 318
    mtmElectionsSupportCandidate(p, 309, 320 ,3);

    mtmElectionsSupportCandidate(p, 310, 317 ,0);
    mtmElectionsSupportCandidate(p, 310, 318 ,1);
    mtmElectionsSupportCandidate(p, 310, 319 ,2);//4 votes for 319
    mtmElectionsSupportCandidate(p, 310, 320 ,3);

    mtmElectionsSupportCandidate(p, 311, 317 ,1);
    mtmElectionsSupportCandidate(p, 311, 318 ,3);
    mtmElectionsSupportCandidate(p, 311, 319 ,2);//4 vote 320
    mtmElectionsSupportCandidate(p, 311, 320 ,0);

    mtmElectionsSupportCandidate(p, 312, 317 ,1);//5 votes for 318
    mtmElectionsSupportCandidate(p, 312, 318 ,0);
    mtmElectionsSupportCandidate(p, 312, 319 ,2);
    mtmElectionsSupportCandidate(p, 312, 320 ,3);

    mtmElectionsSupportCandidate(p, 313, 317 ,1);
    mtmElectionsSupportCandidate(p, 313, 318 ,0); //6 votes for 318
    mtmElectionsSupportCandidate(p, 313, 319 ,2);
    mtmElectionsSupportCandidate(p, 313, 320 ,3);

    mtmElectionsSupportCandidate(p, 314, 317 ,1);
    mtmElectionsSupportCandidate(p, 314, 318 ,3);
    mtmElectionsSupportCandidate(p, 314, 319 ,2);
    mtmElectionsSupportCandidate(p, 314, 320 ,0);// 5 votes for 320

    mtmElectionsSupportCandidate(p, 315, 317 ,1);
    mtmElectionsSupportCandidate(p, 315, 318 ,3);
    mtmElectionsSupportCandidate(p, 315, 319 ,2); //6 votes for 320
    mtmElectionsSupportCandidate(p, 315, 320 ,0);

    mtmElectionsSupportCandidate(p, 316, 317 ,1);
    mtmElectionsSupportCandidate(p, 316, 318 ,2);
    mtmElectionsSupportCandidate(p, 316, 319 ,0); // 5 votes for 319
    mtmElectionsSupportCandidate(p, 316, 320 ,3);



    UniqueOrderedList result = mtmElectionsPerformElections(p, NULL, NULL, "test5");

    int* ttt = uniqueOrderedListGetLowest(result);

    assert(*ttt==118);

    ttt = uniqueOrderedListGetNext(result);

    assert(*ttt==18);

    ttt = uniqueOrderedListGetNext(result);

    assert(*ttt==318);


    ttt = uniqueOrderedListGetNext(result);

    assert(*ttt==420);


    ttt = uniqueOrderedListGetNext(result);

    assert(*ttt==218);


    MtmElections b = mtmElectionsCreate();

    mtmElectionsAddCity(b, "haifa", 1);
    mtmElectionsAddCity(b, "tel-aviv", 2);
    mtmElectionsAddCity(b, "natania", 3);


    mtmElectionsAddCitizen(b, "a",1, 66,12, 1); //66
    mtmElectionsAddCitizen(b, "a",2, 21,12, 1);//21
    mtmElectionsAddCitizen(b, "a",3, 31,12, 1);//41
    mtmElectionsAddCitizen(b, "a",4, 71,12, 1);//71
    mtmElectionsAddCitizen(b, "a",5, 11,12, 1);//11
    mtmElectionsAddCitizen(b, "a",6, 90,12, 1);//90
    mtmElectionsAddCitizen(b, "a",7, 20,12, 1);//20
    mtmElectionsAddCitizen(b, "a",8, 20,12, 1);//40
    mtmElectionsAddCitizen(b, "a",9, 100,12, 1);//100
    mtmElectionsAddCitizen(b, "a",10, 74,12, 1);
    mtmElectionsAddCitizen(b, "a",11, 74,12, 1);
    mtmElectionsAddCandidate(b, 10, 1);
    mtmElectionsAddCandidate(b, 11, 1);
    mtmElectionsSupportCandidate(b, 1, 10, 1);
    mtmElectionsSupportCandidate(b, 2, 11, 1);
    mtmElectionsSupportCandidate(b, 3, 11, 1);
    mtmElectionsSupportCandidate(b, 4, 10, 1);
    mtmElectionsSupportCandidate(b, 5, 11, 1);
    mtmElectionsSupportCandidate(b, 6, 10, 1);
    mtmElectionsSupportCandidate(b, 7, 11, 1);
    mtmElectionsSupportCandidate(b, 8, 11, 1); //10 is the winner
    mtmElectionsSupportCandidate(b, 9, 10, 1);





    mtmElectionsAddCitizen(b, "a",10, 20,12, 2); //66
    mtmElectionsAddCitizen(b, "a",20, 20,12, 2);//21
    mtmElectionsAddCitizen(b, "a",30, 20,12, 2);//41
    mtmElectionsAddCitizen(b, "a",40, 18,12, 2);//71
    mtmElectionsAddCitizen(b, "a",50, 18,12, 2);//11
    mtmElectionsAddCitizen(b, "a",60, 98,12, 2);//90
    mtmElectionsAddCitizen(b, "a",70, 98,12, 2);//20
    mtmElectionsAddCitizen(b, "a",80, 100,12, 2);//40
    mtmElectionsAddCitizen(b, "a",90, 100,12, 2);//100
    mtmElectionsAddCitizen(b, "a",100, 74,12, 2);
    mtmElectionsAddCitizen(b, "a",110, 74,12, 2);
    mtmElectionsAddCandidate(b, 100, 2);
    mtmElectionsAddCandidate(b, 110, 2);

    mtmElectionsSupportCandidate(b, 10, 100, 2);
    mtmElectionsSupportCandidate(b, 20, 100, 2);
    mtmElectionsSupportCandidate(b, 30, 100, 2);
    mtmElectionsSupportCandidate(b, 40, 100, 2);
    mtmElectionsSupportCandidate(b, 50, 100, 2);
    mtmElectionsSupportCandidate(b, 60, 110, 2);
    mtmElectionsSupportCandidate(b, 70, 110, 2); //110 is the winner
    mtmElectionsSupportCandidate(b, 80, 110, 2);
    mtmElectionsSupportCandidate(b, 90, 110, 2);


    mtmElectionsAddCitizen(b, "a",100, 100,12, 3); //66
    mtmElectionsAddCitizen(b, "a",200, 110,12, 3);//21
    mtmElectionsAddCitizen(b, "a",300, 110,12, 3);//41
    mtmElectionsAddCitizen(b, "a",400, 17,12, 3);//71
    mtmElectionsAddCitizen(b, "a",500, 17,12, 3);//11
    mtmElectionsAddCitizen(b, "a",600, 17,12, 3);//90
    mtmElectionsAddCitizen(b, "a",700, 17,12, 3);//20
    mtmElectionsAddCitizen(b, "a",800, 17,12, 3);//40
    mtmElectionsAddCitizen(b, "a",900, 17,12, 3);//100
    mtmElectionsAddCitizen(b, "a",1000, 23,12, 3);
    mtmElectionsAddCitizen(b, "a",1100, 23,12, 3);
    mtmElectionsAddCandidate(b, 1000, 3);
    mtmElectionsAddCandidate(b, 1100, 3);
//



    mtmElectionsSupportCandidate(b, 100, 1000, 3);
    mtmElectionsSupportCandidate(b, 200, 1000, 3);
    mtmElectionsSupportCandidate(b, 300, 1000, 3);
    mtmElectionsSupportCandidate(b, 400, 1100, 3);
    mtmElectionsSupportCandidate(b, 500, 1100, 3);
    mtmElectionsSupportCandidate(b, 600, 1100, 3);
    mtmElectionsSupportCandidate(b, 700, 1100, 3); //1000 is the winner
    mtmElectionsSupportCandidate(b, 800, 1100, 3);
    mtmElectionsSupportCandidate(b, 900, 1100, 3);

    int *yyy;
    int yy = 6;
    yyy=&yy;

    uniqueOrderedListDestroy(result);

    result = mtmElectionsPerformElections(b,
                                          &LegitRank, yyy , "test66");


    ttt = uniqueOrderedListGetLowest(result);

    assert((*ttt)==1000);

    ttt = uniqueOrderedListGetNext(result);

    assert((*ttt)==110);


    ttt = uniqueOrderedListGetNext(result);

    assert((*ttt)==10);

    uniqueOrderedListDestroy(result);

    result = mtmElectionsPerformElections(b,
                                          &ZERORANK, yyy , "test66");


    ttt = uniqueOrderedListGetLowest(result);

    assert((*ttt)==1100);

    ttt = uniqueOrderedListGetNext(result);

    assert((*ttt)==110);


    ttt = uniqueOrderedListGetNext(result);

    assert((*ttt)==11);


    uniqueOrderedListDestroy(result);

    MtmElections u = mtmElectionsCreate();



    result = mtmElectionsPerformElections(NULL,
                                          NULL, yyy , "test66");

    assert(result==NULL);
    uniqueOrderedListDestroy(result);

    mtmElectionsAddCity(u,"haifa",1);
    mtmElectionsAddCity(u,"tel-aviv",2);
    mtmElectionsAddCity(u,"jerusalem",3);
    mtmElectionsAddCitizen(u, "a",1, 100,12, 1);
    mtmElectionsAddCitizen(u, "a",10, 100,12, 1); //2 cits for haifa
    mtmElectionsAddCandidate(u, 2, 0);
    mtmElectionsSupportCandidate(b, 1, 10, 1);
    mtmElectionsAddCitizen(u, "a",2, 100,12, 2);
    mtmElectionsAddCitizen(u, "a",20, 100,12, 2);//2 cits for telaviv
    mtmElectionsAddCandidate(u, 20, 0);
    mtmElectionsAddCitizen(u, "a",3, 100,12, 3);
    mtmElectionsAddCitizen(u, "a",30, 100,12, 3);//2 cits for jerusalem
    mtmElectionsAddCandidate(u, 30, 0);


    result = mtmElectionsPerformElections(u,
                                          &ZERORANK, yyy , "test66");

    assert(result==NULL);

    uniqueOrderedListDestroy(result);

    mtmElectionsDestroy(e);
    mtmElectionsDestroy(p);
    mtmElectionsDestroy(b);
    mtmElectionsDestroy(u);



    for(int i=0; i<240; i++){

        // delay(2);
        printf("%c ",sml);

    }





    printf("\n");
    printf("           In case it wasn't obvious enough, You successfully passed the tests.\n             Congratz, But don't get ahead of yourself, go do a valgrind test");



    return 0;
}



//****************************************
//The Winner of the Elections at: tel-aviv 2 is:
//Mayor:
//Name: b
//        ID:   118
//Age:  21
//Years of education:  12
//****************************************
//****************************************
//The Winner of the Elections at: haifa 1 is:
//Mayor:
//Name: b
//        ID:   18
//Age:  21
//Years of education:  12
//****************************************
//****************************************
//The Winner of the Elections at: jerusalem 4 is:
//Mayor:
//Name: e
//        ID:   318
//Age:  21
//Years of education:  12
//****************************************
//****************************************
//The Winner of the Elections at: lud 5 is:
//Mayor:
//Name: z
//        ID:   420
//Age:  21
//Years of education:  12
//****************************************
//****************************************
//The Winner of the Elections at: natania 3 is:
//Mayor:
//Name: z
//        ID:   218
//Age:  21
//Years of education:  12
//****************************************



