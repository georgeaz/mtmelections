//
// Created by George on 12/1/2018.
//

#ifndef INC_3011_CANDIDATE_H
#define INC_3011_CANDIDATE_H

#include "typedefs_and_general_functions.h"
#include "stdbool.h"


typedef enum CandidateResult_t{
  CANDIDATE_MEMORY_ERROR,
  CANDIDATE_NULL_ARGUMENT,
  CANDIDATE_ALREADY_EXISTS,
  CANDIDATE_DOES_NOT_EXIST,
  CANDIDATE_SUCCESS,
  CANDIDATE_CITIZEN_DOSE_NOT_EXIST,
  CANDIDATE_ILLEGAL_ID,
  CANDIDATE_AGE_NOT_APPROPRIATE
}CandidateResult;

int CandidateGetId(Candidate candidate);
void CandidateChangeId(Candidate,int);
Candidate CandidateCreate();
void CandidateDestroy(Candidate);
Candidate CandidateCopy(Candidate );
bool CandidateCompare(Candidate ,Candidate);


#endif //INC_3011_CANDIDATE_H
