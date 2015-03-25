//
//  DNDataManager.cpp
//  Dominoes
//
//  Created by ICRG LABS on 10/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "ZIDataManager.h"

static ZIDataManager *gSharedManager = NULL;

ZIDataManager::ZIDataManager(void){}

ZIDataManager::~ZIDataManager(void){}

ZIDataManager* ZIDataManager::sharedManager(void) {

	ZIDataManager *pRet = gSharedManager;
    
	if (! gSharedManager)
	{
		pRet = gSharedManager = new ZIDataManager();
        
		if (! gSharedManager->init())
		{
			delete gSharedManager;
			gSharedManager = NULL;
			pRet = NULL;
		}
	}
    
	return pRet;
}

bool ZIDataManager::init(void) {
    
	return true;
}

