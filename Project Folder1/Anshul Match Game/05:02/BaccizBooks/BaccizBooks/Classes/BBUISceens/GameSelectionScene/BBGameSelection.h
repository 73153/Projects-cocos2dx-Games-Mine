//
//  BBMainScreen.h
//  BaccizBooks
//
//  Created by Manjunatha Reddy on 21/01/13.
//
//

#ifndef __BaccizBooks__BBMainScreen__
#define __BaccizBooks__BBMainScreen__

#include"cocos2d.h"

class BBGameSelection : public cocos2d::CCLayer

{
private:
public:
      
    BBGameSelection();
    ~BBGameSelection();
    
    static cocos2d::CCScene* scene();
    
    //Buttons
    void action(cocos2d::CCMenuItemImage* sender);

    

};
#endif /* defined(__BaccizBooks__BBMainScreen__) */
