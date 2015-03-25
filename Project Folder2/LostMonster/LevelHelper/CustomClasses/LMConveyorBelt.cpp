//This source file was generated automatically by LevelHelper
//based on the class template defined by the user.
//For more info please visit: www.levelhelper.org


#include "LMConveyorBelt.h"
#include "../Utilities/LHDictionary.h"
#include "../Utilities/LHArray.h"
#include "../Utilities/LHObject.h"

LMConveyorBelt::~LMConveyorBelt(){

}

void LMConveyorBelt::setPropertiesFromDictionary(LHDictionary* dictionary){

	if(dictionary->objectForKey("velocity"))
		setVelocity(dictionary->objectForKey("velocity")->floatValue());

}

