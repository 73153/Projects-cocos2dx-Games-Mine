//
//  LMMainScreenLoader.h
//  LMMainScreenLoader
//
//  Created by Krithik B on 05/02/13.
//
//

#include "LMLevelSelection.h"

/* Forward declaration. */
class CCBReader;

class LMLevelSelectionLoader : public CCLayerLoader {

public:    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(LMLevelSelectionLoader, loader);
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(LMLevelSelection);
};


