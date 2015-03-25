//
//  LMLine.h
//  LostMonster
//
//  Created by Krithik B on 8/23/12.
//  Copyright (c) 2012 iCRG Labs. All rights reserved.
//

#ifndef LostMonster_LMLine_h
#define LostMonster_LMLine_h

#include "cocos2d.h"

using namespace cocos2d;


//
//  CLASS MANAGES DRAWING LINE FROM START POINT TO END POINT
//

class LMLine :public cocos2d::CCNode {
        
    //instance variables
   
        
public:
    
    LMLine();
    ~LMLine();
    
    //member functions
    virtual void draw();
    void startWithLocation(CCPoint startPosition);
    void resetLine();
    
    
    //variables
    bool isActive;
    CCPoint startPoint;
    CCPoint endPoint;
};


#endif
