//This header file was generated automatically by LevelHelper
//based on the class template defined by the user.
//For more info please visit: www.levelhelper.org


#ifndef LH_LMFloatingFountain_H
#define LH_LMFloatingFountain_H

#include <string>
#include <vector>
#include "LHAbstractClass.h"
class LHDictionary;

class LMFloatingFountain :public LHAbstractClass
{

public:

	LMFloatingFountain(void){}
	virtual ~LMFloatingFountain(void);

	virtual std::string className(){return std::string("LMFloatingFountain");}

	virtual void setPropertiesFromDictionary(LHDictionary* dictionary);

	std::string& getJointName(void){return jointName;}
	void setJointName(const std::string& val){jointName = val;}

	float getMaxHeight(void){return MaxHeight;}
	void setMaxHeight(float val){MaxHeight = val;}

	float getMinHeight(void){return minHeight;}
	void setMinHeight(float val){minHeight = val;}



	std::string jointName;
	float MaxHeight;
	float minHeight;

};

#endif
