/*
 * mtm_elections_tests.h
 *
 *  Created on: Nov 8, 2018
 *      Author: ameeraam
 */

#ifndef TESTS_MTM_ELECTIONS_TESTS_H_
#define TESTS_MTM_ELECTIONS_TESTS_H_
#include "mtm_elections.h"
#include "mtm_uol/uniqueOrderedList.h"
#include <stdbool.h>
#include <stdio.h>

bool testMtmElectionsAddCity();
bool testMtmElectionsAddCitizen();
bool testMtmElectionsCitizenGetName();
bool testMtmElectionsCitizenGetCity();
bool testMtmElectionsCitizenGetAge();
bool testMtmElectionsCitizenGetEducation();
bool testMtmElectionsAddCandidate();
bool testMtmElectionsWithdrawCandidate();
bool testMtmElectionsSupportCandidate();
bool testMtmElectionsCancelSupport();
bool testMtmElectionsChangeAddress();
bool testMtmElectionsRankByAge();
bool testMtmElectionsMayorOfCity();
bool testMtmElectionsPerformElections();

#endif /* TESTS_MTM_ELECTIONS_TESTS_H_ */
