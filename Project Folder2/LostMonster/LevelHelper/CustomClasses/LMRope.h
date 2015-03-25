//This header file was generated automatically by LevelHelper
//based on the class template defined by the user.
//For more info please visit: www.levelhelper.org


#ifndef LH_LMRope_H
#define LH_LMRope_H

#include <string>
#include <vector>
#include "LHAbstractClass.h"
class LHDictionary;

class LMRope :public LHAbstractClass
{

public:

	LMRope(void){}
	virtual ~LMRope(void);

	virtual std::string className(){return std::string("LMRope");}

	virtual void setPropertiesFromDictionary(LHDictionary* dictionary);

	std::string& getTopBoltName(void){return topBoltName;}
	void setTopBoltName(const std::string& val){topBoltName = val;}

	std::string& getBottomBoltName(void){return bottomBoltName;}
	void setBottomBoltName(const std::string& val){bottomBoltName = val;}

	std::string& getJointName(void){return jointName;}
	void setJointName(const std::string& val){jointName = val;}



	std::string topBoltName;
	std::string bottomBoltName;
	std::string jointName;

};

#endif
