//This header file was generated automatically by LevelHelper
//based on the class template defined by the user.
//For more info please visit: www.levelhelper.org


#ifndef LH_CUSTOM_CLASS_MGR
#define LH_CUSTOM_CLASS_MGR
#include "LMRollo.h"
#include "LMRope.h"

class LHCustomClassesMgr{

public:
	static LHAbstractClass* customClassInstanceWithName(const std::string& className){
		if(className == "LMRollo"){return new LMRollo();}

		if(className == "LMRope"){return new LMRope();}

		return 0;
	}
};

#endif
