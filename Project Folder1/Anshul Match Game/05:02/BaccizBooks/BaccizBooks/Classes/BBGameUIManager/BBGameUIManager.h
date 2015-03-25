//
//  BBGameUIManager.h
//  BaccizBooks
//
//  Created by Manjunatha Reddy on 21/01/13.
//
//

#ifndef __BaccizBooks__BBGameUIManager__
#define __BaccizBooks__BBGameUIManager__

#include "cocos2d.h"
#include "BBGameManager.h"
#include "BBMenuLayer.h"


using namespace cocos2d;
class BBGameUIManager:public BBGameManager {
     
public:
    BBGameUIManager();
    ~BBGameUIManager();
    
    BBMenuLayer *menuLayer;
    
    void intialiseUI();
   
};

#endif /* defined(__BaccizBooks__BBGameUIManager__) */
