//This header file was generated automatically by LevelHelper
//based on the class template defined by the user.
//For more info please visit: www.levelhelper.org


#ifndef LH_LMRollo_H
#define LH_LMRollo_H

#include <string>
#include <vector>
#include "LHAbstractClass.h"
class LHDictionary;

class LMRollo :public LHAbstractClass
{

public:

	LMRollo(void){}
	virtual ~LMRollo(void);

	virtual std::string className(){return std::string("LMRollo");}

	virtual void setPropertiesFromDictionary(LHDictionary* dictionary);

	bool getIsMovingRight(void){return isMovingRight;}
	void setIsMovingRight(bool val){isMovingRight = val;}



	bool isMovingRight;

};

#endif
