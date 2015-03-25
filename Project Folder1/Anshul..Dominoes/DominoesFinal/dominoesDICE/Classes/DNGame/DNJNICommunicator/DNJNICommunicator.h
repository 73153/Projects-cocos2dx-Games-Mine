//
//  DNJNICommunicator.h
//  Dominoes
//
//  Created by ICRG LABS on 07/09/12.
//
//

#ifndef Dominoes_DNJNICommunicator_h
#define Dominoes_DNJNICommunicator_h

#include "DNGameManager.h"
#include "cocos2d.h"

USING_NS_CC;

class DNJNICommunicator : DNGameManager {
    
public:
    
    DNJNICommunicator(void);
    virtual ~DNJNICommunicator(void);
    
    CCArray *array;
    void getArray(CCArray *array);
};


#endif
