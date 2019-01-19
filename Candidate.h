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
/**
* 	CandidateInsertInformation: adds candidate information to the new allocated candidate.
* @param id -
* @param name -
* @param education_years -
* @param age -
*               All of the above params are the new allocated candidate information.
* @param candidate -  the new allocated candidate
* @return
 */
void CandidateInsertInformation(Candidate,int);
/**
* CandidateCreate: Allocates a new empty Candidate.
* @return
* 	NULL - if allocations failed.
* 	A new Candidate in case of success.
*/
Candidate CandidateCreate();
/**
* CandidateDestroy: Deallocates an existing Candidate. Clears all elements.
*
* @param Candidate - Target Candidate to be deallocated.
 * If Candidate is NULL nothing will be done
*
*/
void CandidateDestroy(Candidate);
/**
* CandidateCopy: Creates a copy of target Candidate.
*
* @param Candidate - Target Candidate.
* @return
* 	NULL if a NULL was sent or a memory allocation failed.
* 	A Candidate containing the same elements as Candidate.
*/
Candidate CandidateCopy(Candidate );
/**CandidateCompare: checks if the Candidate id's are equal.
 *  @return
 *      0 - if the Candidate id's are equal.
 *      negative or positive int - otherwise.
* */
int CandidateCompare(Candidate ,Candidate);


#endif //INC_3011_CANDIDATE_H
