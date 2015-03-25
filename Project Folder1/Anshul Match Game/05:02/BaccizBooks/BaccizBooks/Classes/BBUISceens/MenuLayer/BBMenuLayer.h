//
//  BBMenuLayer.h
//  BaccizBooks
//
//  Created by Manjunatha Reddy on 21/01/13.
//
//

#ifndef __BaccizBooks__BBMenuLayer__
#define __BaccizBooks__BBMenuLayer__

#include"cocos2d.h"
class BBMenuLayer : public cocos2d::CCLayer {
    
public:
    
    BBMenuLayer();
    ~BBMenuLayer();
    
    //Buttons
    void action(cocos2d::CCMenuItemImage* sender);

};


#endif /* defined(__BaccizBooks__BBMenuLayer__) */
