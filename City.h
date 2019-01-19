//
// Created by User on 28/11/2018.
// Created by Lina Bshouty القمر

#ifndef UNTITLED1_CITY_H
#define UNTITLED1_CITY_H


#include "citizen.h"
#include "Candidate.h"
#include "Vote.h"
#include "preference.h"

typedef enum CityResult_t{
    CITY_MEMORY_ERROR,
    CITY_NULL_ARGUMENT,
    CITY_ALREADY_EXISTS,
    CITY_NOT_SAME_CITY,//maybe we wont use this
    CITY_DOES_NOT_EXIST,
    CITY_SUCCESS,
    CITY_CANDIDATE_DOES_NOT_EXIST,
    CITY_NOT_THE_SAME_CITY,
    CITY_CITIZEN_PRIORITY_EXISTS,
    CITY_CANDIDATE_ALREADY_SUPPORTED,
    CITY_CITIZEN_CAN_NOT_SUPPORT,
  CITY_NO_CANDIDATES_IN_CITY
}CityResult;
/**
*	CityGetId: returns the Id of target city
*
* @param city - The city for which to get id from.
* @return
* 	the city id
* 	-1 - if city is NULL
*/
int CityGetId(City);
/**
*	CityGetCitizens: returns the city citizens
*
* @param City - The city for which to get citizens from.
* @return
* 	set of citizens
* 	NULL - if the city does not exist or NULL was sent
*/
Set CityGetCitizens(City );
/**
*	CityGetCandidates: returns the city candidates
*
* @param City - The city for which to get candidates from.
* @return
* 	set of candidates
* 	NULL - if the city does not exist or NULL was sent
*/
Set CityGetCandidates(City );
/**
*	CityGetName: returns the city name
*
* @param City - The city for which to get name from.
* @return
* 	city name
* 	NULL - if the city does not exist or NULL was sent
*/
String CityGetName(City);
/**
* CityDestroy: Deallocates an existing City. Clears all elements.
*
* @param City - Target City to be deallocated.
 * If City is NULL nothing will be done
*
*/
void CityDestroy(City);
/**
* CityCreate: Allocates a new empty City.
* @return
* 	NULL - if allocations failed.
* 	A new City in case of success.
*/
City CityCreate();
/**
* CityCopy: Creates a copy of target City.
*
* @param City - Target City.
* @return
* 	NULL if a NULL was sent or a memory allocation failed.
* 	A City containing the same elements as City otherwise.
*/
City CityCopy(City);
/**CityCompare: checks if the City id's are equal.
 * * @param City - Target City.
 *  @return
 *      0 - if the City id's are equal.
 *      negative or positive int - otherwise.
* */
int CityCompare(City ,City );
/**CityIsCandidate: checks if the citizen is a candidate.
 * * @param City - Target City.
 *  @return
 *      true- if the citizen is a candidate
 *      false - otherwise.
* */
bool CityIsCandidate(City,int );
/**CitySupportCandidate: adds a prefernce to the citizens prefernces.
 * * @param City - Target City.
*    @param candidate_id - Target candidate.
 *  @return
 *      CITY_NOT_THE_SAME_CITY - if the candidate city and the citizen are not the same.
 *      CITY_CANDIDATE_ALREADY_SUPPORTED - if the citizen already supports the candiate.
 *      CITY_CITIZEN_CAN_NOT_SUPPORT - if the citizen is a candidate.
 *      CITY_CITIZEN_PRIORITY_EXISTS - if the citizen supports a candiate
 *      with the same priority.
 *      CITIZEN_SUCCESS - otherwise
 *
* */

CityResult  CitySupportCandidate(City,Citizen,int candidate_id,int priority);
/**CityGetCitizen: returns a pointer to the citizen of the city.
 * * @param City - Target City.
 *   @param citizen_id - Target citizen id.
 *  @return
 *      Citizen - if found
 *      NULL - otherwise
* */
Citizen CityGetCitizen(City ,int );
/**
* 	CityInsertCitizen: adds citizen to the city.
* @param id -
* @param name -
* @param education_years -
* @param age -
*               All of the above params are the n citizen information.
* @return   CITIZEN_NULL_ARGUMENT - if NULL was sent
 *          CITIZEN_MEMORY_ERROR - if there is no memory
 *          CITIZEN_ALREADY_EXISTS - if the citizen already exists.
 *             CITIZEN_SUCCESS - in case of success
 */

CitizenResult CityInsertCitizen(City ,const String citizen_name, int citizen_id,
                                 int citizen_age, int education_years);
/**
* 	CityInsertCandidate: adds Candidate to the city.
* @param id -candiate id
* @return   CANDIDATE_NULL_ARGUMENT - if NULL was sent
 *          CANDIDATE_MEMORY_ERROR - if there is no memory
 *          CANDIDATE_ALREADY_EXISTS - if the candidate already exists.
 *             CANDIDATE_SUCCESS - in case of success
 */
CandidateResult CityInsertCandidate(City, int);
/**
* 	CityRemoveCandidate: removes Candidate from the city.
* @param Candidate - the candiate to remove
* @param City - the City to which the candidate belong

* @return   CANDIDATE_NULL_ARGUMENT - if NULL was sent
 *          CANDIDATE_DOES_NOT_EXIST - if the candidate does not exists.
 *          CANDIDATE_SUCCESS - in case of success
 */
CandidateResult CityRemoveCandidate(City,Candidate);
/**
* 	CitizenInsertInformation: adds city information to the new allocated city.
* @param id - city id
* @param name - city name
*
 */
void CityInsertInformation(City, const String, int);
/**
* 	CityCitizenRemovePrefrence: removes a prefrence.
* @param id - candidate id
* @param city - city
*
 */
void CityCitizenRemovePrefrence(City,int candidate_id);
/**
* 	CityRemoveCitizen: removes Citizen from the city.
* @param Citizen - the Citizen to remove
* @param City - the City to which the Citizen belong

* @return   CITIZEN_NULL_ARGUMENT - if NULL was sent
 *          CITIZEN_DOES_NOT_EXIST - if the Citizen does not exist.
 *          CITIZEN_SUCCESS - in case of success
 */
CitizenResult CityRemoveCitizen(City city, Citizen citizen);
/**
* 	CityGetCandidateVote: returns the candidate votes.
* @param candidate_id - the candidate id

* @return   Vote - if at least one person supported the candidated so far
 *          NULL - otherwise
 */
Vote CityGetCandidateVote(UniqueOrderedList, int candidate_id);
/**
* 	CityUpdateCandidateVotes: updates the candidate votes while performing the
 * 	elections.
* @param votes - the candidate votes
 * @param new_vote - to be inserted
* @param old_vote - to be destroyed if exists

* @return   CITY_SUCCES - if insertion succceded
 *          CITY_MEMORY_ERROR - in case if allocation failure.
 */
CityResult CityUpdateCandidateVotes(UniqueOrderedList ,Vote new_vote, Vote
old_vote);
#endif //UNTITLED1_CITY_H
