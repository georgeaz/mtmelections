//
// Created by George on 12/1/2018.
//

#include "preference.h"
#include <stdio.h>
struct Preference_t{
  Id candidate_id;
  int * preference_score;
};
void PrintPreference(Preference preference){
    printf("Prefferd candidate:%d\n",*preference->candidate_id);
    printf("score:%d\n",*preference->preference_score);
}

Preference PreferenceCreate() {
    Preference preference = (Preference) malloc(sizeof(*preference));
    int * preference_score = (int*) malloc(sizeof(*preference_score));
    Id candidate_id = (Id) malloc(sizeof(*candidate_id));
    if(preference==NULL||preference_score==NULL||candidate_id==NULL){
        free(preference_score);
        free(candidate_id);
        free(preference);
        return NULL;
    }
    preference->candidate_id=candidate_id;
    preference->preference_score=preference_score;
    return preference;
}
void PreferenceDestroy(Preference preference){
    if(preference==NULL)return;
    free(preference->preference_score);
    free(preference->candidate_id);
    free(preference);
}
void PreferenceInsertInformation(Preference preference, int candidate_id, int preference_score){
    *(preference->candidate_id)=candidate_id;
    *(preference->preference_score)=preference_score;
}
Preference PreferenceCopy(Preference source_prefernce){
    if(source_prefernce==NULL)return NULL;
    Preference new_prefernece=PreferenceCreate();
    if(new_prefernece==NULL){
        PreferenceDestroy(new_prefernece);
        return NULL;
    }
    *new_prefernece->preference_score=*source_prefernce->preference_score;
    *new_prefernece->candidate_id=*source_prefernce->candidate_id;
    return new_prefernece;
}
bool PreferenceIsEqual(Preference source_preference, Preference new_preference){
    return *(source_preference->candidate_id)==*(new_preference->candidate_id)||
    (*source_preference->preference_score==*new_preference->preference_score);
}
bool PreferenceCompare(Preference old_preference,Preference new_preference){
    return *(old_preference->preference_score)>*(new_preference->preference_score);
}
int PreferenceGetCandidateId(Preference preference){
    if(preference==NULL)return NOT_FOUND;
    return *(preference->candidate_id);
}
