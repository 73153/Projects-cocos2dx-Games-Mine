//
//  DNScheduleManager.cpp
//  Dominoes
//
//  Created by ICRG LABS on 03/09/12.
//
//

#include "DNScheduleManager.h"
#include "DNDataManager.h"
#include "DNDominoManager.h"

DNScheduleManager::DNScheduleManager(void) {
    
    this->gameLayer = DataManager->gameLayer;
    this->currentPlayerNumber = 0; // Always the player is the first server...
}

DNScheduleManager::~DNScheduleManager() {}

// In Schedule Manager player numbers starting from 1!
// Player numbers are 1 player!
// 2 and 3 are AI
void DNScheduleManager::passTurnToNextPlayer() {
    
    this->currentPlayerNumber++;
    
    if (this->currentPlayerNumber % (DataManager->opponentCount + 1) == 0) {
        
        this->currentPlayerNumber = 0;
    }
    printf("\n in schedule manager currentPlayerNumber is %d",this->currentPlayerNumber);
    
    DominoManager->playOpponentMove();
    
    if (currentPlayerNumber != 0) {  // disable touch to tiles when gammer is not in play
        
        this->gameLayer->dominoManager->selectedtilecount = 0;
    }
    else { // enable only 1 tile to drag when gammer is in play
        
        this->gameLayer->dominoManager->selectedtilecount = 1;
    }
}