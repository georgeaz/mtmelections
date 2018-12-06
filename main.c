#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
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





int main() {

    MtmElections e = mtmElectionsCreate();

    assert(mtmElectionsAddCity(NULL, "haifa", 1) == MTM_ELECTIONS_NULL_ARGUMENT);
    assert(mtmElectionsAddCity(e, NULL, 1) == MTM_ELECTIONS_NULL_ARGUMENT);
    assert(mtmElectionsAddCity(e, "haifa", -1) == MTM_ELECTIONS_ILLEGAL_ID);


     mtmElectionsAddCity(e, "haifa", 1);
    mtmElectionsAddCity(e, "tel-aviv", 2);
    mtmElectionsAddCity(e, "jerusalem", 3);
    assert(mtmElectionsAddCity(e, "haifa", 1));
    //Adding citizens to haifa
    //primary checks in haifa:
    // add citizen, support candidate, cancel support

    assert(mtmElectionsAddCitizen(e, "a", 1, 25, 12, 1) == MTM_ELECTIONS_SUCCESS);
    assert(mtmElectionsAddCitizen(e, "a", 2, 61, 12, 1) == MTM_ELECTIONS_SUCCESS);
    assert(mtmElectionsAddCitizen(e, "a", 3, 31, 12, 1));
    assert(mtmElectionsAddCitizen(e, "a", 4, 61, 12, 1));
    assert(mtmElectionsAddCitizen(e, "a", 5, 71, 12, 1));
    assert(mtmElectionsAddCitizen(e, "a", 6, 22, 12, 1));
    assert(mtmElectionsAddCitizen(e, "a", 7, 24, 12, 1) == MTM_ELECTIONS_SUCCESS);
    assert(mtmElectionsAddCitizen(e, "a", 8, 28, 12, 1));
    assert(mtmElectionsAddCitizen(e, "a", 9, 43, 12, 1));
    assert(mtmElectionsAddCitizen(e, "a", 10, 31, 12, 1));
    assert(mtmElectionsAddCitizen(e, "a", 11, 51, 12, 1) == MTM_ELECTIONS_SUCCESS);
    assert(mtmElectionsAddCitizen(e, "a", 12, 71, 12, 1));
    assert(mtmElectionsAddCitizen(e, "a", 13, 21, 12, 1));
    assert(mtmElectionsAddCitizen(e, "a", 14, 21, 12, 1));
    assert(mtmElectionsAddCitizen(e, "a", 15, 21, 12, 1));
    assert(mtmElectionsAddCitizen(e, "b", 15, 21, 12, 1) == MTM_ELECTIONS_CITIZEN_ALREADY_EXISTS);
    assert(mtmElectionsAddCitizen(e, "c", 15, 21, 11, 1) == MTM_ELECTIONS_CITIZEN_ALREADY_EXISTS);
    assert(mtmElectionsAddCitizen(e, "a", 16, 21, 10, 1));
    assert(mtmElectionsAddCitizen(e, "a", 17, 21, 12, 1));
    assert(mtmElectionsAddCitizen(e, "a", 18, 21, 12, 1));
    assert(mtmElectionsAddCitizen(e, "a", 19, 21, 12, 1));
    assert(mtmElectionsAddCitizen(e, "a", 20, 21, 12, 1));
    assert(mtmElectionsAddCitizen(e, "a", 21, 21, 12, 1));
    assert(mtmElectionsAddCitizen(e, "a", 22, 21, 12, 1));
    assert(mtmElectionsAddCitizen(e, "a", 23, 21, 12, 1));
    assert(mtmElectionsAddCitizen(e, "a", 24, 21, 12, 1));
    assert(mtmElectionsAddCitizen(e, "a", 25, 21, 12, 1));
    assert(mtmElectionsAddCitizen(e, "a", 26, 21, 12, 1));
    mtmElectionsAddCitizen(e, "a", 27, 21, 12, 1);
    assert(mtmElectionsAddCitizen(e, "a", 28, 21, 12, 1));

    assert(mtmElectionsAddCitizen(e, "a", 2971, 21, 12, 1));
    assert(mtmElectionsAddCitizen(e, "a", 30, 21, 12, 1) == MTM_ELECTIONS_SUCCESS);
    mtmElectionsAddCitizen(e, "a", 35, 21, 12, 1);
    mtmElectionsAddCitizen(e, "a", 100, 21, 12, 2);
    mtmElectionsAddCitizen(e, "a", 101, 21, 12, 2);
    mtmElectionsAddCitizen(e, "a", 102, 21, 12, 2);
    mtmElectionsAddCitizen(e, "a", 103, 21, 12, 2);
    mtmElectionsAddCitizen(e, "a", 104, 21, 12, 2);
    mtmElectionsAddCitizen(e, "a", 105, 21, 12, 2);

    assert(mtmElectionsAddCitizen(e, "a", 29, 21, 12, -1) == MTM_ELECTIONS_ILLEGAL_ID);
    assert(mtmElectionsAddCitizen(e, "a", -29, 21, 12, 1) == MTM_ELECTIONS_ILLEGAL_ID);
    assert(mtmElectionsAddCitizen(e, NULL, 29, 21, 12, 1) == MTM_ELECTIONS_NULL_ARGUMENT);
    assert(mtmElectionsAddCitizen(NULL, "a", 29, 21, 12, 1) == MTM_ELECTIONS_NULL_ARGUMENT);
    assert(mtmElectionsAddCitizen(e, "a", 29, 21, 12, 25) == MTM_ELECTIONS_CITY_DOES_NOT_EXIST);
    assert(mtmElectionsAddCitizen(e, "a", 29, 21, 12, 1));
    assert(mtmElectionsAddCitizen(e, "a", 29, 21, -12, 25) == MTM_ELECTIONS_ILLEGAL_NUMBER_OF_YEARS);
    assert(mtmElectionsAddCitizen(e, "a", 29, -1, 12, 1) == MTM_ELECTIONS_ILLEGAL_AGE);


    mtmElectionsAddCitizen(e, "a", 31, 21, 12, 2);
    mtmElectionsAddCandidate(e, 31, 2);
    mtmElectionsAddCitizen(e, "a", 32, 13, 12, 1);


    assert(mtmElectionsAddCandidate(e, 27, 1) == MTM_ELECTIONS_SUCCESS);
    mtmElectionsAddCandidate(e, 28, 1);
    mtmElectionsAddCandidate(e, 29, 1);
    mtmElectionsAddCandidate(e, 2971, 1);
    assert(mtmElectionsAddCandidate(e, 30, 1) == MTM_ELECTIONS_SUCCESS);
    assert(mtmElectionsAddCandidate(NULL, 30, 1) == MTM_ELECTIONS_NULL_ARGUMENT);
    assert(mtmElectionsAddCandidate(e, 30, 1) == MTM_ELECTIONS_CANDIDATE_ALREADY_EXISTS);
    assert(mtmElectionsAddCandidate(e, 32, 1) == MTM_ELECTIONS_AGE_NOT_APPROPRIATE);
    assert(mtmElectionsAddCandidate(e, -29, 1) == MTM_ELECTIONS_ILLEGAL_ID);
    assert(mtmElectionsAddCandidate(e, 29, -1) == MTM_ELECTIONS_ILLEGAL_ID); ///////////##############3
    assert(mtmElectionsAddCandidate(e, 33330, 1) == MTM_ELECTIONS_CITIZEN_DOES_NOT_EXIST);
    assert(mtmElectionsAddCandidate(e, 30, 31) == MTM_ELECTIONS_CITY_DOES_NOT_EXIST);

    assert(mtmElectionsSupportCandidate(e, 1, 27, -1) == MTM_ELECTIONS_ILLEGAL_PRIORITY);
    assert(mtmElectionsSupportCandidate(e, 1, 27, 0) == MTM_ELECTIONS_SUCCESS); //1 vote for can #27
    assert (mtmElectionsSupportCandidate(e, 1, 28, 0) == MTM_ELECTIONS_PRIORITY_EXISTS);
    assert(mtmElectionsSupportCandidate(e, 1, 29, 0) == MTM_ELECTIONS_PRIORITY_EXISTS);
    assert(mtmElectionsSupportCandidate(e, 1, 27, 1) == MTM_ELECTIONS_ALREADY_SUPPORTED);
    assert(mtmElectionsSupportCandidate(NULL, 2, 27, 3) == MTM_ELECTIONS_NULL_ARGUMENT);

    assert(mtmElectionsSupportCandidate(e, 2, 31, 3) == MTM_ELECTIONS_NOT_SAME_CITY);//~
    assert(mtmElectionsSupportCandidate(e, 2, 320, 3) == MTM_ELECTIONS_CANDIDATE_DOES_NOT_EXIST);
    assert(mtmElectionsSupportCandidate(e, 30, 29, 3) == MTM_ELECTIONS_CAN_NOT_SUPPORT);//~


    mtmElectionsSupportCandidate(e, 2, 27, 3); // 1 vote for can #28
    mtmElectionsSupportCandidate(e, 2, 28, 0);
    mtmElectionsSupportCandidate(e, 2, 29, 4);
    mtmElectionsSupportCandidate(e, 2, 30, 5);

    mtmElectionsSupportCandidate(e, 3, 27, 3); //2 votes for #27
    mtmElectionsSupportCandidate(e, 3, 28, 4);
    mtmElectionsSupportCandidate(e, 3, 29, 5);
    mtmElectionsSupportCandidate(e, 3, 30, 6);

    mtmElectionsSupportCandidate(e, 4, 27, 3);
    mtmElectionsSupportCandidate(e, 4, 28, 4);
    mtmElectionsSupportCandidate(e, 4, 29, 5);
    mtmElectionsSupportCandidate(e, 4, 30, 0); //1 vote for #30

    mtmElectionsSupportCandidate(e, 5, 27, 3);
    mtmElectionsSupportCandidate(e, 5, 28, 4);
    mtmElectionsSupportCandidate(e, 5, 29, 2); //1 vote for #29
    mtmElectionsSupportCandidate(e, 5, 30, 6);

    mtmElectionsSupportCandidate(e, 6, 27, 1); //3 votes for #27
    mtmElectionsSupportCandidate(e, 6, 28, 1);
    mtmElectionsSupportCandidate(e, 6, 29, 1);
    assert(mtmElectionsSupportCandidate(e, 6, 30, 1) == MTM_ELECTIONS_PRIORITY_EXISTS);

    assert(mtmElectionsSupportCandidate(NULL, 6, 27, 1) == MTM_ELECTIONS_NULL_ARGUMENT); //3 v
    assert(mtmElectionsSupportCandidate(e, -6, 28, 1) == MTM_ELECTIONS_ILLEGAL_ID);
    assert(mtmElectionsSupportCandidate(e, 6, -29, 1) == MTM_ELECTIONS_ILLEGAL_ID);
    assert(mtmElectionsSupportCandidate(e, 6, 30, -1) == MTM_ELECTIONS_ILLEGAL_PRIORITY);
    assert(mtmElectionsSupportCandidate(e, 31, 27, 5) == MTM_ELECTIONS_NOT_SAME_CITY);


    mtmElectionsSupportCandidate(e, 7, 27, 5);
    mtmElectionsSupportCandidate(e, 7, 28, 5);
    mtmElectionsSupportCandidate(e, 7, 29, 5);
    mtmElectionsSupportCandidate(e, 7, 30, 2); // 2 votes for #30

    //mtmElectionsSupportCandidate(e, 7 ,30 ,5 );//2 votes for #29
    //mtmElectionsSupportCandidate(e, 7 ,29 ,3 );//########!!!!#############3
    assert(mtmElectionsSupportCandidate(e, 7, 30, 0) == MTM_ELECTIONS_ALREADY_SUPPORTED);
    assert(mtmElectionsSupportCandidate(e, 7, 30, 2) == MTM_ELECTIONS_ALREADY_SUPPORTED);

    mtmElectionsSupportCandidate(e, 8, 27, 5);//3 votes for #29
    mtmElectionsSupportCandidate(e, 8, 28, 3);
    mtmElectionsSupportCandidate(e, 8, 29, 0);
    mtmElectionsSupportCandidate(e, 8, 30, 2);

    mtmElectionsSupportCandidate(e, 9, 29, 5);
    mtmElectionsSupportCandidate(e, 9, 29, 3);// 4 votes for #29
    mtmElectionsSupportCandidate(e, 9, 30, 10);
    mtmElectionsSupportCandidate(e, 9, 28, 10);

    mtmElectionsSupportCandidate(e, 10, 27, 5);
    mtmElectionsSupportCandidate(e, 10, 28, 3);//2 votes for #28
    mtmElectionsSupportCandidate(e, 10, 29, 10);
    mtmElectionsSupportCandidate(e, 10, 30, 10);

    mtmElectionsSupportCandidate(e, 11, 27, 1);//4 votes for 27
    mtmElectionsSupportCandidate(e, 11, 28, 2);
    mtmElectionsSupportCandidate(e, 11, 29, 30);
    mtmElectionsSupportCandidate(e, 11, 30, 10);

    assert(mtmElectionsSupportCandidate(e, 12, 27, 10) == MTM_ELECTIONS_SUCCESS);
    mtmElectionsSupportCandidate(e, 12, 28, 10);
    mtmElectionsSupportCandidate(e, 12, 29, 10);
    mtmElectionsSupportCandidate(e, 12, 30, 1); //3 votes for 30

    mtmElectionsSupportCandidate(e, 13, 27, 5);
    assert(mtmElectionsSupportCandidate(e, 13, 27, 3) == MTM_ELECTIONS_ALREADY_SUPPORTED);
    mtmElectionsSupportCandidate(e, 13, 29, 4); //5 votes for #29
    mtmElectionsSupportCandidate(e, 13, 30, 10);


    mtmElectionsSupportCandidate(e, 14, 28, 5);
    mtmElectionsSupportCandidate(e, 14, 27, 3); // 5 votes for 27
    mtmElectionsSupportCandidate(e, 14, 29, 4);
    mtmElectionsSupportCandidate(e, 14, 30, 10);

    mtmElectionsSupportCandidate(e, 13, 30, 0);
    mtmElectionsSupportCandidate(e, 14, 30, 0);
    mtmElectionsSupportCandidate(e, 15, 30, 0);
    mtmElectionsSupportCandidate(e, 16, 30, 0);
    mtmElectionsSupportCandidate(e, 17, 30, 0);
    mtmElectionsSupportCandidate(e, 18, 30, 0);
    mtmElectionsSupportCandidate(e, 19, 30, 0);
    mtmElectionsSupportCandidate(e, 20, 2971, 0);
    mtmElectionsSupportCandidate(e, 21, 2971, 0);
    mtmElectionsSupportCandidate(e, 22, 2971, 0);
    mtmElectionsSupportCandidate(e, 23, 2971, 0);
    mtmElectionsSupportCandidate(e, 24, 2971, 0);
    mtmElectionsSupportCandidate(e, 25, 2971, 0);
    mtmElectionsSupportCandidate(e, 26, 2971, 0);


    assert(mtmElectionsCancelSupport(e, 35, 30) == MTM_ELECTIONS_NOT_SUPPORTED);
    assert(mtmElectionsCancelSupport(e, 36, 30) == MTM_ELECTIONS_CITIZEN_DOES_NOT_EXIST);
    assert(mtmElectionsCancelSupport(e, 11, 33) == MTM_ELECTIONS_CANDIDATE_DOES_NOT_EXIST);
    assert(mtmElectionsCancelSupport(e, -18, 30) == MTM_ELECTIONS_ILLEGAL_ID);
    assert(mtmElectionsCancelSupport(e, 18, -30) == MTM_ELECTIONS_ILLEGAL_ID);
    assert(mtmElectionsCancelSupport(e, 15, 30) == MTM_ELECTIONS_SUCCESS);
    assert(mtmElectionsCancelSupport(e, 30, 30) == MTM_ELECTIONS_MUST_SUPPORT);
    assert(mtmElectionsCancelSupport(NULL, 17, 30) == MTM_ELECTIONS_NULL_ARGUMENT);
    assert(mtmElectionsCancelSupport(e, 18, 30) == MTM_ELECTIONS_SUCCESS);
    mtmElectionsCancelSupport(e, 17, 30);
    mtmElectionsCancelSupport(e, 18, 30);
    mtmElectionsCancelSupport(e, 19, 30);
    mtmElectionsCancelSupport(e, 20, 30);
    mtmElectionsCancelSupport(e, 21, 30);
    mtmElectionsCancelSupport(e, 22, 30);
    mtmElectionsCancelSupport(e, 23, 30);
    mtmElectionsCancelSupport(e, 24, 30);
    mtmElectionsCancelSupport(e, 25, 28);
    mtmElectionsCancelSupport(e, 26, 29);

    int y;
    int *x = &y;

    assert(MtmElectionsCitizenGetCity(NULL, 30, x) == MTM_ELECTIONS_NULL_ARGUMENT);
    assert(MtmElectionsCitizenGetCity(e, -30, x) == MTM_ELECTIONS_ILLEGAL_ID);
    assert(MtmElectionsCitizenGetCity(e, 300, x) == MTM_ELECTIONS_CITIZEN_DOES_NOT_EXIST);
    MtmElectionsCitizenGetCity(e, 30, x);
    assert(*x == 1);
    MtmElectionsCitizenGetCity(e, 31, x);
    assert(*x == 2);

    assert(MtmElectionsCitizenGetAge(NULL, 30, x) == MTM_ELECTIONS_NULL_ARGUMENT);
    assert(MtmElectionsCitizenGetAge(e, -30, x) == MTM_ELECTIONS_ILLEGAL_ID);
    assert(MtmElectionsCitizenGetAge(e, 230, x) == MTM_ELECTIONS_CITIZEN_DOES_NOT_EXIST);
    MtmElectionsCitizenGetAge(e, 30, x);
    assert(*x == 21);

    assert(MtmElectionsCitizenGetEducation(NULL, 30, x) == MTM_ELECTIONS_NULL_ARGUMENT);
    assert(MtmElectionsCitizenGetEducation(e, -30, x) == MTM_ELECTIONS_ILLEGAL_ID);
    assert(MtmElectionsCitizenGetEducation(e, 230, x) == MTM_ELECTIONS_CITIZEN_DOES_NOT_EXIST);
    MtmElectionsCitizenGetEducation(e, 30, x);
    assert(*x == 12);

    assert(mtmElectionsWithdrawCandidate(NULL, 2971, 1) == MTM_ELECTIONS_NULL_ARGUMENT);
    assert(mtmElectionsWithdrawCandidate(e, -2971, 1) == MTM_ELECTIONS_ILLEGAL_ID);
    assert(mtmElectionsWithdrawCandidate(e, 2971, 6) == MTM_ELECTIONS_CITY_DOES_NOT_EXIST);
    assert(mtmElectionsWithdrawCandidate(e, 271, 1) == MTM_ELECTIONS_CANDIDATE_DOES_NOT_EXIST);
    assert(mtmElectionsWithdrawCandidate(e, 2971, 1) == MTM_ELECTIONS_SUCCESS);
    assert(mtmElectionsSupportCandidate(e, 12, 2971, 10) == MTM_ELECTIONS_CANDIDATE_DOES_NOT_EXIST);
    return 0;
}