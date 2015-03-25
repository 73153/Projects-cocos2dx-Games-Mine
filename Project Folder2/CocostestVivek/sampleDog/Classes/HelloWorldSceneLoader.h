//
//  HelloWorldSceneLoader.h
//  sampleDog
//
//  Created by Manjunatha Reddy on 06/02/13.
//
//

#ifndef sampleDog_HelloWorldSceneLoader_h
#define sampleDog_HelloWorldSceneLoader_h

#include "HelloWorldScene.h"

/* Forward declaration. */
class CCBReader;

class HelloWorldSceneLoader : public cocos2d::extension::CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(HelloWorldSceneLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(HelloWorld);
};

#endif



