//
//  DNGameManager.h
//  Dominoes
//
//  Created by ICRG LABS on 10/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Dominoes_DNGameManager_h
#define Dominoes_DNGameManager_h

#include "cocos2d.h"

class MainGameController;

class DNGameManager : public cocos2d::CCObject {
        
public:
    
    DNGameManager(void);
    virtual ~DNGameManager(void);
    
    MainGameController *gameLayer;
};


#endif
