//
//  LostMonsterAppDelegate.h
//  LostMonster
//
//  Created by Krithik B on 8/20/12.
//  Copyright __MyCompanyName__ 2012. All rights reserved.
//

#ifndef  _LMAPP_DELEGATE_H_
#define  _LMAPP_DELEGATE_H_

#include "CCApplication.h"

/**
@brief    The cocos2d Application.

The reason for implement as private inheritance is to hide some interface call by CCDirector.
*/
class  LMAppDelegate : private cocos2d::CCApplication
{
public:
    LMAppDelegate();
    virtual ~LMAppDelegate();


    /**
    @brief    Implement CCDirector and CCScene init code here.
    @return true    Initialize success, app continue.
    @return false   Initialize failed, app terminate.
    */
    virtual bool applicationDidFinishLaunching();

    /**
    @brief  The function be called when the application enter background
    @param  the pointer of the application
    */
    virtual void applicationDidEnterBackground();

    /**
    @brief  The function be called when the application enter foreground
    @param  the pointer of the application
    */
    virtual void applicationWillEnterForeground();
};

#endif // _LMAPP_DELEGATE_H_

