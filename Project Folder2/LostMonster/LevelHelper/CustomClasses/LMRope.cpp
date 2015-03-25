//This source file was generated automatically by LevelHelper
//based on the class template defined by the user.
//For more info please visit: www.levelhelper.org


#include "LMRope.h"
#include "../Utilities/LHDictionary.h"
#include "../Utilities/LHArray.h"
#include "../Utilities/LHObject.h"

LMRope::~LMRope(){

}

void LMRope::setPropertiesFromDictionary(LHDictionary* dictionary){

	if(dictionary->objectForKey("topBoltName"))
		setTopBoltName(dictionary->objectForKey("topBoltName")->stringValue());

	if(dictionary->objectForKey("bottomBoltName"))
		setBottomBoltName(dictionary->objectForKey("bottomBoltName")->stringValue());

	if(dictionary->objectForKey("jointName"))
		setJointName(dictionary->objectForKey("jointName")->stringValue());

}

