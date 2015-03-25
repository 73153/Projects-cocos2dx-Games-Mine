//
//  DNSplash.h
//  Dominoes
//
//  Created by Dinesh on 16/11/12.
//
//

#ifndef Dominoes_DNSplash_h
#define Dominoes_DNSplash_h

#include "cocos2d.h"

class DNSplash : public cocos2d::CCLayer
{
public:
  
    DNSplash();
    ~DNSplash();
    
    static cocos2d::CCScene* scene();

    void gotoGame();
    CREATE_FUNC(DNSplash);
};

#endif
