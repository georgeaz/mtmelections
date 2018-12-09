//
// Created by George on 12/7/2018.
//

#ifndef INC_3011_VOTE_H
#define INC_3011_VOTE_H
#include "typedefs_and_general_functions.h"
#include <stdbool.h>

Vote VoteCreate();
void VoteInsertInformation(Vote vote,int candidate_id, Name candidate_name, int
candidate_votes);
Vote  VoteCopy(Vote vote);
void VoteDestroy(Vote vote);
bool VoteIsEqual(Vote vote_old,Vote vote_new);
bool VoteGreaterThan(Vote vote_old,Vote vote_new);
int VoteCandidateGetId(Vote vote);
int VoteCandidateGetVotes(Vote vote);
bool VoteElectionsGreaterThan(Vote ,Vote );
void VotePrint(Vote vote);
#endif //INC_3011_VOTE_H
