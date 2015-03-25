//This header file was generated automatically by LevelHelper
//based on the class template defined by the user.
//For more info please visit: www.levelhelper.org


#ifndef LH_CUSTOM_CLASS_MGR
#define LH_CUSTOM_CLASS_MGR
#include "LMRollo.h"
#include "LMRope.h"
#include "LMConveyorBelt.h"
#include "LMFloatingFountain.h"

class LHCustomClassesMgr{

public:
	static LHAbstractClass* customClassInstanceWithName(const std::string& className){
		if(className == "LMRollo"){return new LMRollo();}

		if(className == "LMRope"){return new LMRope();}

		if(className == "LMConveyorBelt"){return new LMConveyorBelt();}

		if(className == "LMFloatingFountain"){return new LMFloatingFountain();}

		return 0;
	}
};

#endif
