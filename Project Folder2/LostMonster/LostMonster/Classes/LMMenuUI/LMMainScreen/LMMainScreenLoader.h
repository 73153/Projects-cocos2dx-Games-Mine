//
//  LMMainScreenLoader.h
//  LMMainScreenLoader
//
//  Created by Krithik B on 05/02/13.
//
//

#ifndef testCocosXCocosBuilder_IntroLayer_h
#define testCocosXCocosBuilder_IntroLayer_h

#include "LMMainScreen.h"

/* Forward declaration. */
class CCBReader;

class LMMainScreenLoader : public cocos2d::extension::CCLayerLoader {

public:    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(LMMainScreenLoader, loader);
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(LMMainScreen);
};


#endif
