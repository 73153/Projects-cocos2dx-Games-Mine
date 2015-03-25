//
//  DNPlayerPanel.h
//  Dominoes
//
//  Created by ICRG LABS on 29/08/12.
//
//

#ifndef Dominoes_DNPlayerPanel_h
#define Dominoes_DNPlayerPanel_h

#include "DNCustomSprite.h"
#include "DNGameConstants.h"

class DNPlayerPanel : public DNCustomSprite {
    
public:
    
    DNPlayerPanel();
    virtual ~DNPlayerPanel();
                                   
    // Functions!
    DNPlayerPanel* spriteWithFrame(const char *pszFileName);
    DNPlayerPanel* create(CCSpriteFrame *pSpriteFrame);

    void createPanel(CCPoint position, CCPoint anchorPoint, bool isFlipY, int tag);
    void expandPanel();
    void closePanel();
    void changeState();
    void menuCallbacks(CCObject* sender);
    void youngBunnyPass();
    void giraffePass();
    
    // Vars!
    PlayerPanelState state;
    CCMenu *passMenu;
    int tileCount;
    
    bool istouched;
};

#endif
