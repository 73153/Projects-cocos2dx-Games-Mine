//
//  BBGameUIManager.cpp
//  BaccizBooks
//
//  Created by Manjunatha Reddy on 21/01/13.
//
//

#include "BBGameUIManager.h"

using namespace cocos2d;

#pragma mark - Init

BBGameUIManager::BBGameUIManager()
{
   // this = BBDataManager::sharedManager()->gameLayer;
    
}

void BBGameUIManager::intialiseUI()
{
    //add menuLayer
    menuLayer = new BBMenuLayer();
   // this->addChild(menuLayer,0);

}
#pragma mark - Dealloc

BBGameUIManager::~BBGameUIManager()
{
    
   // this->removeChild(menuLayer, true);
    delete menuLayer;
}

