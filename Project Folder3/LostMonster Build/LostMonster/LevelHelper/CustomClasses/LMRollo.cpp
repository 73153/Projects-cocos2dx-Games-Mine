//This source file was generated automatically by LevelHelper
//based on the class template defined by the user.
//For more info please visit: www.levelhelper.org


#include "LMRollo.h"
#include "../Utilities/LHDictionary.h"
#include "../Utilities/LHArray.h"
#include "../Utilities/LHObject.h"

LMRollo::~LMRollo(){

}

void LMRollo::setPropertiesFromDictionary(LHDictionary* dictionary){

	if(dictionary->objectForKey("isMovingRight"))
		setIsMovingRight(dictionary->objectForKey("isMovingRight")->boolValue());

}

