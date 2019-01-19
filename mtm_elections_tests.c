/*
 * mtm_elections_tests.c
 *
 *  Created on: Nov 8, 2018
 *      Author: ameeraam
 */

#include "mtm_elections_tests.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define CHECK(b,res) if((b) != (res)) do{ mtmElectionsDestroy(mtmElections);return false;} while(0)
#define CHECK_WITH_FREE(b,res,f) if((b) != (res)) do{ mtmElectionsDestroy(mtmElections);free(f);return false;} while(0)
#define CHECK_WITH_FREE_UOL(b,res,uol) if((b) != (res)) do{ mtmElectionsDestroy(mtmElections);uniqueOrderedListDestroy(uol);return false;} while(0)

bool testMtmElectionsAddCity(){
	MtmElections mtmElections = mtmElectionsCreate();
	CHECK(mtmElectionsAddCity(NULL,"haifa",1),MTM_ELECTIONS_NULL_ARGUMENT);
	CHECK(mtmElectionsAddCity(mtmElections,NULL,1),MTM_ELECTIONS_NULL_ARGUMENT);
	CHECK(mtmElectionsAddCity(mtmElections,"haifa",-1),MTM_ELECTIONS_ILLEGAL_ID);
	CHECK(mtmElectionsAddCity(NULL,"haifa",-1),MTM_ELECTIONS_NULL_ARGUMENT);
	CHECK(mtmElectionsAddCity(mtmElections,NULL,-1),MTM_ELECTIONS_NULL_ARGUMENT);
	CHECK(mtmElectionsAddCity(mtmElections,"haifa",1),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsAddCity(mtmElections,"haifa",0),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsAddCity(mtmElections,NULL,1),MTM_ELECTIONS_NULL_ARGUMENT);
	CHECK(mtmElectionsAddCity(mtmElections,"tel-aviv",1),MTM_ELECTIONS_CITY_ALREADY_EXISTS);

	mtmElectionsDestroy(mtmElections);
	return true;
}

bool testMtmElectionsAddCitizen(){
	MtmElections mtmElections = mtmElectionsCreate();
	CHECK(mtmElectionsAddCitizen(NULL,"ameer",555,22,16,1),MTM_ELECTIONS_NULL_ARGUMENT);
	CHECK(mtmElectionsAddCitizen(mtmElections,NULL,555,22,16,1),MTM_ELECTIONS_NULL_ARGUMENT);
	CHECK(mtmElectionsAddCitizen(NULL,NULL,555,22,16,1),MTM_ELECTIONS_NULL_ARGUMENT);
	CHECK(mtmElectionsAddCitizen(mtmElections,NULL,0,22,16,1),MTM_ELECTIONS_NULL_ARGUMENT);
	CHECK(mtmElectionsAddCitizen(mtmElections,NULL,555,0,16,1),MTM_ELECTIONS_NULL_ARGUMENT);
	CHECK(mtmElectionsAddCitizen(mtmElections,"ameer",-555,0,16,1),MTM_ELECTIONS_ILLEGAL_ID);
	CHECK(mtmElectionsAddCitizen(mtmElections,"ameer",555,0,16,-1),MTM_ELECTIONS_ILLEGAL_ID);
	CHECK(mtmElectionsAddCitizen(mtmElections,"ameer",555,0,16,1),MTM_ELECTIONS_ILLEGAL_AGE);
	CHECK(mtmElectionsAddCitizen(mtmElections,"ameer",555,0,-16,1),MTM_ELECTIONS_ILLEGAL_AGE);
	CHECK(mtmElectionsAddCitizen(mtmElections,"ameer",555,10,-16,1),MTM_ELECTIONS_ILLEGAL_NUMBER_OF_YEARS);

	CHECK(mtmElectionsAddCitizen(mtmElections,"ameer",555,10,0,1),MTM_ELECTIONS_CITY_DOES_NOT_EXIST);
	CHECK(mtmElectionsAddCity(mtmElections,"haifa",1),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsAddCitizen(mtmElections,"ameer",555,10,16,1),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsAddCitizen(mtmElections,"ameer",555,10,16,1),MTM_ELECTIONS_CITIZEN_ALREADY_EXISTS);
	CHECK(mtmElectionsAddCitizen(mtmElections,"abeer",555,1,15,10),MTM_ELECTIONS_CITIZEN_ALREADY_EXISTS);
	CHECK(mtmElectionsAddCitizen(mtmElections,"abeer",555,1,15,1),MTM_ELECTIONS_CITIZEN_ALREADY_EXISTS);
	CHECK(mtmElectionsAddCity(mtmElections,"tel-aviv",2),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsAddCitizen(mtmElections,"khalid",555,25,13,2),MTM_ELECTIONS_CITIZEN_ALREADY_EXISTS);

	mtmElectionsDestroy(mtmElections);
	return true;
}

bool testMtmElectionsCitizenGetName(){
	MtmElections mtmElections = mtmElectionsCreate();
	CHECK(mtmElectionsAddCity(mtmElections,"haifa",1),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsAddCitizen(mtmElections,"ameer",555,10,16,1),MTM_ELECTIONS_SUCCESS);
	char* name = NULL;
	CHECK(MtmElectionsCitizenGetName(NULL,1,&name),MTM_ELECTIONS_NULL_ARGUMENT);
	CHECK(MtmElectionsCitizenGetName(mtmElections,1,NULL),MTM_ELECTIONS_NULL_ARGUMENT);
	CHECK(MtmElectionsCitizenGetName(mtmElections,-1,NULL),MTM_ELECTIONS_NULL_ARGUMENT);
	CHECK(MtmElectionsCitizenGetName(NULL,-1,&name),MTM_ELECTIONS_NULL_ARGUMENT);
	CHECK(MtmElectionsCitizenGetName(mtmElections,-1,&name),MTM_ELECTIONS_ILLEGAL_ID);
	CHECK(MtmElectionsCitizenGetName(mtmElections,444,&name),MTM_ELECTIONS_CITIZEN_DOES_NOT_EXIST);
	CHECK(MtmElectionsCitizenGetName(mtmElections,555,&name),MTM_ELECTIONS_SUCCESS);
	free(name);
	CHECK(MtmElectionsCitizenGetName(mtmElections,555,&name),MTM_ELECTIONS_SUCCESS);
	CHECK_WITH_FREE(strcmp(name,"ameer"),0,name);
	name[1] = 'b';
	CHECK_WITH_FREE(strcmp(name,"abeer"),0,name);
	free(name);
	CHECK(MtmElectionsCitizenGetName(mtmElections,555,&name),MTM_ELECTIONS_SUCCESS);
	CHECK_WITH_FREE(strcmp(name,"ameer"),0,name);
	free(name);
	mtmElectionsDestroy(mtmElections);
	return true;
}

bool testMtmElectionsCitizenGetCity(){
	MtmElections mtmElections = mtmElectionsCreate();
	CHECK(mtmElectionsAddCity(mtmElections,"haifa",1),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsAddCitizen(mtmElections,"ameer",555,10,16,1),MTM_ELECTIONS_SUCCESS);
	int city;
	CHECK(MtmElectionsCitizenGetCity(NULL,1,&city),MTM_ELECTIONS_NULL_ARGUMENT);
	CHECK(MtmElectionsCitizenGetCity(mtmElections,1,NULL),MTM_ELECTIONS_NULL_ARGUMENT);
	CHECK(MtmElectionsCitizenGetCity(mtmElections,-1,NULL),MTM_ELECTIONS_NULL_ARGUMENT);
	CHECK(MtmElectionsCitizenGetCity(NULL,-1,&city),MTM_ELECTIONS_NULL_ARGUMENT);
	CHECK(MtmElectionsCitizenGetCity(mtmElections,-1,&city),MTM_ELECTIONS_ILLEGAL_ID);
	CHECK(MtmElectionsCitizenGetCity(mtmElections,444,&city),MTM_ELECTIONS_CITIZEN_DOES_NOT_EXIST);
	CHECK(MtmElectionsCitizenGetCity(mtmElections,555,&city),MTM_ELECTIONS_SUCCESS);
	CHECK(city,1);

	mtmElectionsDestroy(mtmElections);
	return true;
}

bool testMtmElectionsCitizenGetAge(){
	MtmElections mtmElections = mtmElectionsCreate();
	CHECK(mtmElectionsAddCity(mtmElections,"haifa",1),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsAddCitizen(mtmElections,"ameer",555,10,16,1),MTM_ELECTIONS_SUCCESS);
	int age;
	CHECK(MtmElectionsCitizenGetAge(NULL,1,&age),MTM_ELECTIONS_NULL_ARGUMENT);
	CHECK(MtmElectionsCitizenGetAge(mtmElections,1,NULL),MTM_ELECTIONS_NULL_ARGUMENT);
	CHECK(MtmElectionsCitizenGetAge(mtmElections,-1,NULL),MTM_ELECTIONS_NULL_ARGUMENT);
	CHECK(MtmElectionsCitizenGetAge(NULL,-1,&age),MTM_ELECTIONS_NULL_ARGUMENT);
	CHECK(MtmElectionsCitizenGetAge(mtmElections,-1,&age),MTM_ELECTIONS_ILLEGAL_ID);
	CHECK(MtmElectionsCitizenGetAge(mtmElections,444,&age),MTM_ELECTIONS_CITIZEN_DOES_NOT_EXIST);
	CHECK(MtmElectionsCitizenGetAge(mtmElections,555,&age),MTM_ELECTIONS_SUCCESS);
	CHECK(age,10);

	mtmElectionsDestroy(mtmElections);
	return true;
}

bool testMtmElectionsCitizenGetEducation(){
	MtmElections mtmElections = mtmElectionsCreate();
	CHECK(mtmElectionsAddCity(mtmElections,"haifa",1),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsAddCitizen(mtmElections,"ameer",555,10,16,1),MTM_ELECTIONS_SUCCESS);
	int years;
	CHECK(MtmElectionsCitizenGetEducation(NULL,1,&years),MTM_ELECTIONS_NULL_ARGUMENT);
	CHECK(MtmElectionsCitizenGetEducation(mtmElections,1,NULL),MTM_ELECTIONS_NULL_ARGUMENT);
	CHECK(MtmElectionsCitizenGetEducation(mtmElections,-1,NULL),MTM_ELECTIONS_NULL_ARGUMENT);
	CHECK(MtmElectionsCitizenGetEducation(NULL,-1,&years),MTM_ELECTIONS_NULL_ARGUMENT);
	CHECK(MtmElectionsCitizenGetEducation(mtmElections,-1,&years),MTM_ELECTIONS_ILLEGAL_ID);
	CHECK(MtmElectionsCitizenGetEducation(mtmElections,444,&years),MTM_ELECTIONS_CITIZEN_DOES_NOT_EXIST);
	CHECK(MtmElectionsCitizenGetEducation(mtmElections,555,&years),MTM_ELECTIONS_SUCCESS);
	CHECK(years,16);

	mtmElectionsDestroy(mtmElections);
	return true;
}

bool testMtmElectionsAddCandidate(){
	MtmElections mtmElections = mtmElectionsCreate();
	CHECK(mtmElectionsAddCity(mtmElections,"haifa",1),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsAddCandidate(NULL,-1,-1),MTM_ELECTIONS_NULL_ARGUMENT);
	CHECK(mtmElectionsAddCandidate(mtmElections,-1,-1),MTM_ELECTIONS_ILLEGAL_ID);
	CHECK(mtmElectionsAddCandidate(mtmElections,1,2),MTM_ELECTIONS_CITY_DOES_NOT_EXIST);
	CHECK(mtmElectionsAddCandidate(mtmElections,1,1),MTM_ELECTIONS_CITIZEN_DOES_NOT_EXIST);
	CHECK(mtmElectionsAddCity(mtmElections,"tel-aviv",2),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsAddCitizen(mtmElections,"ameer",555,10,16,1),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsAddCandidate(mtmElections,555,2),MTM_ELECTIONS_CITIZEN_DOES_NOT_EXIST);
	CHECK(mtmElectionsAddCandidate(mtmElections,555,1),MTM_ELECTIONS_AGE_NOT_APPROPRIATE);
	CHECK(mtmElectionsAddCitizen(mtmElections,"samir",444,22,16,1),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsAddCandidate(mtmElections,444,1),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsAddCandidate(mtmElections,444,1),MTM_ELECTIONS_CANDIDATE_ALREADY_EXISTS);

	mtmElectionsDestroy(mtmElections);
	return true;
}

bool testMtmElectionsWithdrawCandidate(){
	MtmElections mtmElections = mtmElectionsCreate();
	CHECK(mtmElectionsWithdrawCandidate(NULL,-1,-1),MTM_ELECTIONS_NULL_ARGUMENT);
	CHECK(mtmElectionsWithdrawCandidate(NULL,1,1),MTM_ELECTIONS_NULL_ARGUMENT);
	CHECK(mtmElectionsWithdrawCandidate(NULL,-1,1),MTM_ELECTIONS_NULL_ARGUMENT);
	CHECK(mtmElectionsWithdrawCandidate(NULL,1,-1),MTM_ELECTIONS_NULL_ARGUMENT);
	CHECK(mtmElectionsWithdrawCandidate(mtmElections,1,-1),MTM_ELECTIONS_ILLEGAL_ID);
	CHECK(mtmElectionsWithdrawCandidate(mtmElections,-1,1),MTM_ELECTIONS_ILLEGAL_ID);
	CHECK(mtmElectionsWithdrawCandidate(mtmElections,1,1),MTM_ELECTIONS_CITY_DOES_NOT_EXIST);

	CHECK(mtmElectionsAddCity(mtmElections,"haifa",1),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsWithdrawCandidate(mtmElections,1,1),MTM_ELECTIONS_CANDIDATE_DOES_NOT_EXIST);
	CHECK(mtmElectionsAddCitizen(mtmElections,"samir",444,22,16,1),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsAddCandidate(mtmElections,444,1),MTM_ELECTIONS_SUCCESS);
	char* name;
	CHECK(MtmElectionsCitizenGetName(mtmElections,444,&name),MTM_ELECTIONS_SUCCESS);
	CHECK_WITH_FREE(strcmp(name,"samir"),0,name);
	CHECK_WITH_FREE(mtmElectionsAddCitizen(mtmElections,"ameer",555,22,16,1),MTM_ELECTIONS_SUCCESS,name);
	CHECK_WITH_FREE(mtmElectionsSupportCandidate(mtmElections,555,444,0),MTM_ELECTIONS_SUCCESS,name);
	CHECK_WITH_FREE(mtmElectionsWithdrawCandidate(mtmElections,444,1),MTM_ELECTIONS_SUCCESS,name);
	name[2] = 'b';
	CHECK_WITH_FREE(strcmp(name,"sabir"),0,name);
	CHECK_WITH_FREE(mtmElectionsWithdrawCandidate(mtmElections,444,1),MTM_ELECTIONS_CANDIDATE_DOES_NOT_EXIST,name);
	CHECK_WITH_FREE(mtmElectionsAddCitizen(mtmElections,"khalid",333,22,16,1),MTM_ELECTIONS_SUCCESS,name);
	CHECK_WITH_FREE(mtmElectionsAddCandidate(mtmElections,333,1),MTM_ELECTIONS_SUCCESS,name);
	CHECK_WITH_FREE(mtmElectionsSupportCandidate(mtmElections,555,333,0),MTM_ELECTIONS_SUCCESS,name);

	free(name);
	mtmElectionsDestroy(mtmElections);
	return true;
}

bool testMtmElectionsSupportCandidate(){
	MtmElections mtmElections = mtmElectionsCreate();
	CHECK(mtmElectionsSupportCandidate(NULL,-1,-1,1),MTM_ELECTIONS_NULL_ARGUMENT);
	CHECK(mtmElectionsSupportCandidate(NULL,1,1,1),MTM_ELECTIONS_NULL_ARGUMENT);
	CHECK(mtmElectionsSupportCandidate(NULL,-1,1,1),MTM_ELECTIONS_NULL_ARGUMENT);
	CHECK(mtmElectionsSupportCandidate(NULL,1,-1,1),MTM_ELECTIONS_NULL_ARGUMENT);
	CHECK(mtmElectionsSupportCandidate(NULL,-1,1,-1),MTM_ELECTIONS_NULL_ARGUMENT);
	CHECK(mtmElectionsSupportCandidate(mtmElections,1,-1,1),MTM_ELECTIONS_ILLEGAL_ID);
	CHECK(mtmElectionsSupportCandidate(mtmElections,-1,1,1),MTM_ELECTIONS_ILLEGAL_ID);
	CHECK(mtmElectionsSupportCandidate(mtmElections,-1,1,1),MTM_ELECTIONS_ILLEGAL_ID);
	CHECK(mtmElectionsSupportCandidate(mtmElections,-1,1,-1),MTM_ELECTIONS_ILLEGAL_ID);
	CHECK(mtmElectionsSupportCandidate(mtmElections,1,-1,-1),MTM_ELECTIONS_ILLEGAL_ID);
	CHECK(mtmElectionsSupportCandidate(mtmElections,1,1,-1),MTM_ELECTIONS_ILLEGAL_PRIORITY);
	CHECK(mtmElectionsSupportCandidate(mtmElections,1,1,0),MTM_ELECTIONS_CITIZEN_DOES_NOT_EXIST);

	CHECK(mtmElectionsAddCity(mtmElections,"haifa",1),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsSupportCandidate(mtmElections,555,1,0),MTM_ELECTIONS_CITIZEN_DOES_NOT_EXIST);
	CHECK(mtmElectionsAddCitizen(mtmElections,"ameer",555,10,16,1),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsSupportCandidate(mtmElections,555,444,0),MTM_ELECTIONS_CANDIDATE_DOES_NOT_EXIST);
	CHECK(mtmElectionsAddCity(mtmElections,"tel-aviv",2),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsAddCitizen(mtmElections,"samir",444,22,16,2),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsAddCandidate(mtmElections,444,2),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsSupportCandidate(mtmElections,444,444,0),MTM_ELECTIONS_ALREADY_SUPPORTED);
	CHECK(mtmElectionsSupportCandidate(mtmElections,555,444,0),MTM_ELECTIONS_NOT_SAME_CITY);
	CHECK(mtmElectionsChangeAddress(mtmElections,444,1),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsSupportCandidate(mtmElections,555,444,0),MTM_ELECTIONS_CANDIDATE_DOES_NOT_EXIST);
	CHECK(mtmElectionsAddCandidate(mtmElections,444,1),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsSupportCandidate(mtmElections,555,444,0),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsAddCitizen(mtmElections,"khalid",333,22,16,1),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsAddCandidate(mtmElections,333,1),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsSupportCandidate(mtmElections,555,333,0),MTM_ELECTIONS_PRIORITY_EXISTS);
	CHECK(mtmElectionsSupportCandidate(mtmElections,555,333,1),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsSupportCandidate(mtmElections,333,444,1),MTM_ELECTIONS_CAN_NOT_SUPPORT);


	mtmElectionsDestroy(mtmElections);
	return true;
}

bool testMtmElectionsCancelSupport(){
	MtmElections mtmElections = mtmElectionsCreate();
	CHECK(mtmElectionsCancelSupport(NULL,-1,-1),MTM_ELECTIONS_NULL_ARGUMENT);
	CHECK(mtmElectionsCancelSupport(NULL,1,1),MTM_ELECTIONS_NULL_ARGUMENT);
	CHECK(mtmElectionsCancelSupport(NULL,-1,1),MTM_ELECTIONS_NULL_ARGUMENT);
	CHECK(mtmElectionsCancelSupport(NULL,1,-1),MTM_ELECTIONS_NULL_ARGUMENT);
	CHECK(mtmElectionsCancelSupport(mtmElections,1,-1),MTM_ELECTIONS_ILLEGAL_ID);
	CHECK(mtmElectionsCancelSupport(mtmElections,-1,1),MTM_ELECTIONS_ILLEGAL_ID);
	CHECK(mtmElectionsCancelSupport(mtmElections,-1,-1),MTM_ELECTIONS_ILLEGAL_ID);
	CHECK(mtmElectionsCancelSupport(mtmElections,1,1),MTM_ELECTIONS_CITIZEN_DOES_NOT_EXIST);
	CHECK(mtmElectionsAddCity(mtmElections,"haifa",1),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsAddCitizen(mtmElections,"ameer",555,10,16,1),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsCancelSupport(mtmElections,555,1),MTM_ELECTIONS_CANDIDATE_DOES_NOT_EXIST);
	CHECK(mtmElectionsAddCity(mtmElections,"tel-aviv",2),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsAddCitizen(mtmElections,"samir",444,22,16,2),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsAddCandidate(mtmElections,444,2),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsCancelSupport(mtmElections,555,444),MTM_ELECTIONS_NOT_SUPPORTED);
	CHECK(mtmElectionsCancelSupport(mtmElections,444,444),MTM_ELECTIONS_MUST_SUPPORT);
	CHECK(mtmElectionsChangeAddress(mtmElections,444,1),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsAddCandidate(mtmElections,444,1),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsSupportCandidate(mtmElections,555,444,1),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsCancelSupport(mtmElections,555,444),MTM_ELECTIONS_SUCCESS);

	mtmElectionsDestroy(mtmElections);
	return true;
}

bool testMtmElectionsChangeAddress(){
	MtmElections mtmElections = mtmElectionsCreate();
	CHECK(mtmElectionsChangeAddress(NULL,1,2),MTM_ELECTIONS_NULL_ARGUMENT);
	CHECK(mtmElectionsChangeAddress(NULL,-1,2),MTM_ELECTIONS_NULL_ARGUMENT);
	CHECK(mtmElectionsChangeAddress(NULL,1,-2),MTM_ELECTIONS_NULL_ARGUMENT);
	CHECK(mtmElectionsChangeAddress(NULL,-1,-2),MTM_ELECTIONS_NULL_ARGUMENT);
	CHECK(mtmElectionsChangeAddress(mtmElections,-1,2),MTM_ELECTIONS_ILLEGAL_ID);
	CHECK(mtmElectionsChangeAddress(mtmElections,-1,-2),MTM_ELECTIONS_ILLEGAL_ID);
	CHECK(mtmElectionsChangeAddress(mtmElections,1,-2),MTM_ELECTIONS_ILLEGAL_ID);
	CHECK(mtmElectionsChangeAddress(mtmElections,1,2),MTM_ELECTIONS_CITIZEN_DOES_NOT_EXIST);
	CHECK(mtmElectionsAddCity(mtmElections,"haifa",1),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsChangeAddress(mtmElections,1,1),MTM_ELECTIONS_CITIZEN_DOES_NOT_EXIST);
	CHECK(mtmElectionsAddCity(mtmElections,"tel-aviv",2),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsAddCitizen(mtmElections,"ameer",555,22,16,2),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsChangeAddress(mtmElections,555,1),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsAddCitizen(mtmElections,"samir",444,22,16,1),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsAddCitizen(mtmElections,"khalid",333,22,16,1),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsAddCitizen(mtmElections,"omar jaml",222,22,16,1),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsAddCandidate(mtmElections,444,1),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsAddCandidate(mtmElections,333,1),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsAddCandidate(mtmElections,222,1),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsSupportCandidate(mtmElections,555,333,0),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsSupportCandidate(mtmElections,555,444,1),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsChangeAddress(mtmElections,555,2),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsSupportCandidate(mtmElections,555,222,0),MTM_ELECTIONS_NOT_SAME_CITY);
	CHECK(mtmElectionsSupportCandidate(mtmElections,555,444,0),MTM_ELECTIONS_NOT_SAME_CITY);
	CHECK(mtmElectionsChangeAddress(mtmElections,555,1),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsSupportCandidate(mtmElections,555,333,0),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsSupportCandidate(mtmElections,555,444,1),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsChangeAddress(mtmElections,333,2),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsSupportCandidate(mtmElections,555,222,0),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsSupportCandidate(mtmElections,555,333,2),MTM_ELECTIONS_CANDIDATE_DOES_NOT_EXIST);
	CHECK(mtmElectionsSupportCandidate(mtmElections,333,333,0),MTM_ELECTIONS_CANDIDATE_DOES_NOT_EXIST);

	mtmElectionsDestroy(mtmElections);
	return true;
}

bool testMtmElectionsRankByAge(){
	MtmElections mtmElections = mtmElectionsCreate();
	CHECK(mtmElectionsRankByAge(NULL,1,NULL),0);
	CHECK(mtmElectionsRankByAge(NULL,-1,NULL),0);
	CHECK(mtmElectionsRankByAge(mtmElections,1,NULL),0);
	int age = 1;
	CHECK(mtmElectionsRankByAge(mtmElections,1,&age),0);
	CHECK(mtmElectionsAddCity(mtmElections,"haifa",1),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsAddCitizen(mtmElections,"ameer",555,22,16,1),MTM_ELECTIONS_SUCCESS);
	age = 11;
	CHECK(mtmElectionsRankByAge(mtmElections,555,&age),2);
	age = 10;
	CHECK(mtmElectionsRankByAge(mtmElections,555,&age),2);
	age = 5;
	CHECK(mtmElectionsRankByAge(mtmElections,555,&age),4);
	age = 22;
	CHECK(mtmElectionsRankByAge(mtmElections,555,&age),1);
	age = 23;
	CHECK(mtmElectionsRankByAge(mtmElections,555,&age),0);

	mtmElectionsDestroy(mtmElections);
	return true;
}

bool testMtmElectionsMayorOfCity(){
	MtmElections mtmElections = mtmElectionsCreate();
	CHECK(mtmElectionsMayorOfCity(NULL,1,NULL,NULL),MTM_ELECTIONS_NULL_ARGUMENT);
	CHECK(mtmElectionsMayorOfCity(mtmElections,1,NULL,NULL),MTM_ELECTIONS_NULL_ARGUMENT);
	CHECK(mtmElectionsMayorOfCity(mtmElections,1,NULL,"out"),MTM_ELECTIONS_NULL_ARGUMENT);
	CHECK(mtmElectionsMayorOfCity(mtmElections,-1,NULL,NULL),MTM_ELECTIONS_NULL_ARGUMENT);
	int mayor;
	CHECK(mtmElectionsMayorOfCity(mtmElections,-1,&mayor,NULL),MTM_ELECTIONS_NULL_ARGUMENT);
	CHECK(mtmElectionsMayorOfCity(mtmElections,-1,&mayor,"out"),MTM_ELECTIONS_ILLEGAL_ID);
	CHECK(mtmElectionsMayorOfCity(mtmElections,1,&mayor,"out"),MTM_ELECTIONS_CITY_DOES_NOT_EXIST);
	CHECK(mtmElectionsAddCity(mtmElections,"haifa",1),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsMayorOfCity(mtmElections,1,&mayor,"out"),MTM_ELECTIONS_NO_CANDIDATES_IN_CITY);
	CHECK(mtmElectionsAddCitizen(mtmElections,"ameer",555,22,16,1),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsMayorOfCity(mtmElections,1,&mayor,"out"),MTM_ELECTIONS_NO_CANDIDATES_IN_CITY);
	CHECK(mtmElectionsAddCandidate(mtmElections,555,1),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsMayorOfCity(mtmElections,1,&mayor,"out"),MTM_ELECTIONS_SUCCESS);
	CHECK(mayor,555);
	CHECK(mtmElectionsMayorOfCity(mtmElections,1,&mayor,"out"),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsWithdrawCandidate(mtmElections,555,1),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsMayorOfCity(mtmElections,1,&mayor,"out"),MTM_ELECTIONS_NO_CANDIDATES_IN_CITY);
	CHECK(mtmElectionsAddCitizen(mtmElections,"samir",444,22,16,1),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsAddCitizen(mtmElections,"khalid",333,22,16,1),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsAddCandidate(mtmElections,444,1),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsAddCandidate(mtmElections,333,1),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsMayorOfCity(mtmElections,1,&mayor,"out"),MTM_ELECTIONS_SUCCESS);
	CHECK(mayor,333);
	CHECK(mtmElectionsSupportCandidate(mtmElections,555,333,1),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsSupportCandidate(mtmElections,555,444,0),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsMayorOfCity(mtmElections,1,&mayor,"out"),MTM_ELECTIONS_SUCCESS);
	CHECK(mayor,444);
	CHECK(mtmElectionsAddCitizen(mtmElections,"aomar",222,22,16,1),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsAddCandidate(mtmElections,222,1),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsSupportCandidate(mtmElections,555,222,3),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsAddCity(mtmElections,"tel-aviv",2),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsChangeAddress(mtmElections,444,2),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsMayorOfCity(mtmElections,1,&mayor,"out"),MTM_ELECTIONS_SUCCESS);
	CHECK(mayor,333);
	CHECK(mtmElectionsAddCitizen(mtmElections,"samir",445,22,16,2),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsChangeAddress(mtmElections,555,2),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsAddCandidate(mtmElections,444,2),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsAddCandidate(mtmElections,445,2),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsMayorOfCity(mtmElections,2,&mayor,"out"),MTM_ELECTIONS_SUCCESS);
	CHECK(mayor,445);
	CHECK(mtmElectionsSupportCandidate(mtmElections,555,444,3),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsMayorOfCity(mtmElections,2,&mayor,"out"),MTM_ELECTIONS_SUCCESS);
	CHECK(mayor,444);

	mtmElectionsDestroy(mtmElections);
	return true;
}

bool testMtmElectionsPerformElections(){
	MtmElections mtmElections = mtmElectionsCreate();
	CHECK(mtmElectionsAddCity(mtmElections,"haifa",1),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsAddCitizen(mtmElections,"ameer",555,22,16,1),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsAddCitizen(mtmElections,"khalid",444,30,16,1),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsAddCitizen(mtmElections,"samir",333,22,16,1),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsAddCitizen(mtmElections,"haitham",222,22,16,1),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsAddCandidate(mtmElections,555,1),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsAddCandidate(mtmElections,444,1),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsAddCandidate(mtmElections,333,1),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsAddCandidate(mtmElections,222,1),MTM_ELECTIONS_SUCCESS);
	int age = 30;
	UniqueOrderedList electionsResults = mtmElectionsPerformElections(mtmElections,mtmElectionsRankByAge,&age,"performElectionsOut");
	CHECK_WITH_FREE_UOL(uniqueOrderedListSize(electionsResults),1,electionsResults);
	CHECK_WITH_FREE_UOL(*((int*)uniqueOrderedListGetLowest(electionsResults)),444,electionsResults);
	uniqueOrderedListDestroy(electionsResults);

	CHECK(mtmElectionsAddCity(mtmElections,"Nave-191",2),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsAddCitizen(mtmElections,"fadi",777,24,16,2),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsAddCitizen(mtmElections,"mahmoud",666,21,16,2),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsAddCitizen(mtmElections,"wafik",888,21,16,2),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsAddCandidate(mtmElections,777,2),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsAddCandidate(mtmElections,666,2),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsSupportCandidate(mtmElections,888,666,10),MTM_ELECTIONS_SUCCESS);
	CHECK(mtmElectionsAddCity(mtmElections,"empty",3),MTM_ELECTIONS_SUCCESS);
	age = 20;
	electionsResults = mtmElectionsPerformElections(mtmElections,mtmElectionsRankByAge,&age,"performElectionsOut");
	CHECK_WITH_FREE_UOL(uniqueOrderedListSize(electionsResults),2,electionsResults);
	CHECK_WITH_FREE_UOL(*((int*)uniqueOrderedListGetLowest(electionsResults)),555,electionsResults);
	CHECK_WITH_FREE_UOL(*((int*)uniqueOrderedListGetGreatest(electionsResults)),666,electionsResults);
	uniqueOrderedListDestroy(electionsResults);

	mtmElectionsDestroy(mtmElections);
	return true;
}
