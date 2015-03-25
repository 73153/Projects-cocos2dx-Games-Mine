//
//  ZIGameConstants.h
//  ZergInvasion
//
//  Created by ICRG LABS on 13/09/12.
//
//

#ifndef ZergInvasion_ZIGameConstants_h
#define ZergInvasion_ZIGameConstants_h

// Short forms
#define DataManager ZIDataManager::sharedManager()
#define MainGameLayer this->gameLayer
#define MonsterManager this->gameLayer->monsterManager
#define UIManager this->gameLayer->uiManager

// Constants
#define PTM_RATIO 32
#define GridSize (ZIMonster *)(this->gameLayer->monsterManager->monstersArray->ObjectAtIndex(0))->getContentSize.width();

#endif
