//
// Created by George on 12/7/2018.
//

#ifndef INC_3011_VOTE_H
#define INC_3011_VOTE_H
#include "typedefs_and_general_functions.h"
#include <stdbool.h>
/**
* VoteCreate: Allocates a new empty vote.
* @return
* 	NULL - if allocations failed.
* 	A new vote in case of success.
*/
Vote VoteCreate();
/**
* 	VoteInsertInformation: adds votes information to the new allocated vote.
* @param candidate_name - the candidate name
* @param candidate_votes - the votes numbers so far
* @param candidate_id - the candidate id
 */
void VoteInsertInformation(Vote vote,int candidate_id, Name candidate_name, int
candidate_votes);
/**
* VoteCopy: Creates a copy of target vote.
*
* @param vote - Target vote.
* @return
* 	NULL if a NULL was sent or a memory allocation failed.
* 	A vote containing the same elements as citizen otherwise.
*/
Vote  VoteCopy(Vote vote);
/**
* VoteDestroy: Deallocates an existing vote. Clears all elements.
*
* @param vote - Target cote to be deallocated.
 * If vote is NULL nothing will be done
*
*/
void VoteDestroy(Vote vote);
/**VoteIsEqual: checks if the two votes are equal.
 *  @return
 *      1 - if the votes are equal.
 *      0 - if the number of votes for the first vote is bigger,
 *      if they are the same, if the first candidate name is smaller lexocraphically
 *      or if the first candidate id is bigger
* */
bool VoteIsEqual(Vote vote_old,Vote vote_new);
bool VoteGreaterThan(Vote vote_old,Vote vote_new);
/**VoteCandidateGetId: returns the candidate id.
* */
int VoteCandidateGetId(Vote vote);
/**VoteCandidateGetVotes: returns the candidate votes number.
* */
int VoteCandidateGetVotes(Vote vote);
bool VoteElectionsGreaterThan(Vote ,Vote );
#endif //INC_3011_VOTE_H
