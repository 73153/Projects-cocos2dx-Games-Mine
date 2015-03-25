//
//  LMDataManager.cpp
//  Lost Monster
//
//  Created by ICRG LABS on 10/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "LMDataManager.h"
#include "cocos2d.h"


static LMDataManager *gSharedManager = NULL;

LMDataManager::LMDataManager(void){}

LMDataManager::~LMDataManager(void){}

LMDataManager* LMDataManager::sharedManager(void) {
    
	LMDataManager *pRet = gSharedManager;
    
	if (! gSharedManager)
	{
		pRet = gSharedManager = new LMDataManager();
        
		if (! gSharedManager->init())
		{
			delete gSharedManager;
			gSharedManager = NULL;
			pRet = NULL;
		}
	}
	return pRet;
}

bool LMDataManager::init(void) {
	return true;
}

