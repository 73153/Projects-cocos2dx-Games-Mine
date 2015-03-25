//
//  BBDatamanager.cpp
//  BaccizBooks
//
//  Created by Manjunatha Reddy on 21/01/13.
//
//

#include "BBMainDataManager.h"
#include "cocos2d.h"

static BBMainDataManager *gSharedManager = NULL;

BBMainDataManager::BBMainDataManager(void){
    
}

BBMainDataManager::~BBMainDataManager(void){}

BBMainDataManager* BBMainDataManager::sharedManager(void) {
    
	BBMainDataManager *pRet = gSharedManager;
    
	if (! gSharedManager)
	{
		pRet = gSharedManager = new BBMainDataManager();
        
		if (! gSharedManager->init())
		{
			delete gSharedManager;
			gSharedManager = NULL;
			pRet = NULL;
		}
	}
	return pRet;
}

bool BBMainDataManager::init(void) {
	return true;
}

