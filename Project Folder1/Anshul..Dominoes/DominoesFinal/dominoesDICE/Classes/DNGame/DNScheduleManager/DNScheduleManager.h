//
//  DNScheduleManager.h
//  Dominoes
//
//  Created by ICRG LABS on 03/09/12.
//
//

#ifndef Dominoes_DNScheduleManager_h
#define Dominoes_DNScheduleManager_h

#include "DNGameManager.h"

class DNScheduleManager : DNGameManager {
    
public:
    
    DNScheduleManager(void);
    virtual ~DNScheduleManager(void);

    // Functions!
    void passTurnToNextPlayer();

    // Vars!
    int currentPlayerNumber;
};

#endif
