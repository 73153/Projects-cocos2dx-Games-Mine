//
//  LMMainScreenLoader.h
//  LMMainScreenLoader
//
//  Created by Krithik B on 05/02/13.
//
//

#include "LMWorldSelection.h"

/* Forward declaration. */
class CCBReader;

class LMWorldSelectionScreenLoader : public CCLayerLoader {

public:    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(LMWorldSelectionScreenLoader, loader);
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(LMWorldSelection);
};


