//This header file was generated automatically by LevelHelper
//based on the class template defined by the user.
//For more info please visit: www.levelhelper.org


#ifndef LH_LMConveyorBelt_H
#define LH_LMConveyorBelt_H

#include <string>
#include <vector>
#include "LHAbstractClass.h"
class LHDictionary;

class LMConveyorBelt :public LHAbstractClass
{

public:

	LMConveyorBelt(void){}
	virtual ~LMConveyorBelt(void);

	virtual std::string className(){return std::string("LMConveyorBelt");}

	virtual void setPropertiesFromDictionary(LHDictionary* dictionary);

	float getVelocity(void){return velocity;}
	void setVelocity(float val){velocity = val;}



	float velocity;

};

#endif
