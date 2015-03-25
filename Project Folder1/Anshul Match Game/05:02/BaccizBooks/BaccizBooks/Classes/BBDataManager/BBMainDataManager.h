//
//  BBDatamanager.h
//  BaccizBooks
//
//  Created by Manjunatha Reddy on 21/01/13.
//
//

#ifndef __BaccizBooks__BBDatamanager__
#define __BaccizBooks__BBDatamanager__

#include "cocos2d.h"
#include "BBConfig.h"

class BBMainDataManager: public cocos2d::CCObject  {
    
private:
    
    BBMainDataManager(void);
    ~BBMainDataManager(void);
    
public:
    
    static BBMainDataManager* sharedManager(void);
    bool init(void);
        
    //gamePlay type
    GamePlaySelection gamePlayType;

};


#endif /* defined(__BaccizBooks__BBDatamanager__) */
