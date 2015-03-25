//This source file was generated automatically by LevelHelper
//based on the class template defined by the user.
//For more info please visit: www.levelhelper.org


#include "LMFloatingFountain.h"
#include "../Utilities/LHDictionary.h"
#include "../Utilities/LHArray.h"
#include "../Utilities/LHObject.h"

LMFloatingFountain::~LMFloatingFountain(){

}

void LMFloatingFountain::setPropertiesFromDictionary(LHDictionary* dictionary){

	if(dictionary->objectForKey("jointName"))
		setJointName(dictionary->objectForKey("jointName")->stringValue());

	if(dictionary->objectForKey("MaxHeight"))
		setMaxHeight(dictionary->objectForKey("MaxHeight")->floatValue());

	if(dictionary->objectForKey("minHeight"))
		setMinHeight(dictionary->objectForKey("minHeight")->floatValue());

}

