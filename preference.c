//
// Created by George on 12/1/2018.
//

#include "preference.h"
struct Preference_t{
  Id candidate_id;
  int * preference_score;
};

Vote PreferenceCreate() {
    Vote preference = (Vote) malloc(sizeof(*preference));
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
void PreferenceDestroy(Vote preference){
    if(preference==NULL)return;
    free(preference->candidate_id);
    free(preference);
}
void PreferenceChangeInformation(Vote preference,int candidate_id,int preference_score){
    *(preference->candidate_id)=candidate_id;
    *(preference->preference_score)=preference_score;
}
Vote PreferenceCopy(Vote source_prefernce){
    if(source_prefernce==NULL)return NULL;
    Vote new_prefernece=PreferenceCreate();
    if(new_prefernece==NULL){
        PreferenceDestroy(new_prefernece);
        return NULL;
    }
    new_prefernece->preference_score=source_prefernce->preference_score;
    new_prefernece->preference_score=source_prefernce->candidate_id;
    return new_prefernece;
}
bool PreferenceIsEquals(Vote source_preference,Vote new_preference){
    return source_preference->candidate_id==new_preference->candidate_id;
}
bool PreferenceCompare(Vote old_preference,Vote new_preference){
    return *(old_preference->preference_score)<=*(new_preference->preference_score);
}

int PreferenceGetId(Vote preference){
    return *(preference->candidate_id);
}
