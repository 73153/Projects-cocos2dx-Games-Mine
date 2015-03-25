//
//  DNGameConstants.h
//  Dominoes
//
//  Created by ICRG LABS on 27/07/12.
//
//

#ifndef Dominoes_DNGameConstants_h
#define Dominoes_DNGameConstants_h

// Short forms
#define DataManager DNDataManager::sharedManager()
#define MainGameLayer this->gameLayer
#define DominoManager this->gameLayer->dominoManager
#define BackgroundManager this->gameLayer->backgroundManager
#define UIManager this->gameLayer->uiManager
#define ScheduleManager this->gameLayer->scheduleManager
#define JNICommunicator this->gameLayer->jniCommunicator
#define PlayerPanel this->gameLayer->playerpanel

// Constant Values
#define kTotalNumberOfTiles 28
#define kPlayerTileTag 1000
#define kTileWidth 58
#define kPanelsScaleValue 0.6f

// Tags
#define kPlayerPanelStartingTag 10000
#define kPlayerPanel1Tag 10001
#define kPlayerPanel2Tag 10002
#define kPlayerPanel3Tag 10003

#define kPanelClosingActionTag 4444

// Enums

typedef enum {
    
    kPanelOpened,
    kPanelClosed,
    kPanelOnTransition
} PlayerPanelState;

#endif
