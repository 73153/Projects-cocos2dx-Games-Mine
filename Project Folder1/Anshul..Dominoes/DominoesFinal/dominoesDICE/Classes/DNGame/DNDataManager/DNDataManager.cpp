//
//  DNDataManager.cpp
//  Dominoes
//
//  Created by ICRG LABS on 10/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "DNDataManager.h"

static DNDataManager *gSharedManager = NULL;

DNDataManager::DNDataManager(void){}

DNDataManager::~DNDataManager(void){}

DNDataManager* DNDataManager::sharedManager(void) {

	DNDataManager *pRet = gSharedManager;
    
	if (! gSharedManager)
	{
		pRet = gSharedManager = new DNDataManager();
        
		if (! gSharedManager->init())
		{
			delete gSharedManager;
			gSharedManager = NULL;
			pRet = NULL;
		}
	}
    
	return pRet;
}

bool DNDataManager::init(void) {
    
    this->m_isRunning = false;
    this->isGameOver = false;
    this->isGameFinished = false;
    
    this->score = 0;
    this->opponentCount = 2;
    this->click = 1;
    this->count = 0;
    this->sec = 1;
    this->min = 0;
    this->opponenttilecount = 0;
    this->playerTileCount = 0;
    this->opponentOneTileCount = 0;
    this->opponentTwoTileCount = 0;
	return true;
}

