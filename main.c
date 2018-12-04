#include <stdio.h>
#include "list.h"
#include "citizen.h"

#include <stdlib.h>
#include <assert.h>
#include "City.h"
void freeInt(void* e){
    free(e);
}

int main() {
City city=CityCreate();
CityChangeInformation(city,"Jadda",11);
//Citizen firstcitizen=CitizenCreate();
//CitizenChangeInformation(firstcitizen,31644,"Lina",3,20);
//Citizen secondCitizen=CitizenCreate();
//CitizenChangeInformation(secondCitizen,3188,"George",2,20);
   // Citizen thirdCitizen=CitizenCreate();
  //  CitizenChangeInformation(thirdCitizen,3688,"Julie<3",1,0);
//CityInsertCitizen(city,firstcitizen);
//CityInsertCitizen(city,secondCitizen);
  //  CityInsertCitizen(city,thirdCitizen);

CityPrint(city);

    return 0;
}
