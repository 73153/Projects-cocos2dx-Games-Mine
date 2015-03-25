//
//  DNBackground.h
//  Dominoes
//
//  Created by ICRG LABS on 08/08/12.
//
//

#ifndef Dominoes_DNBackground_h
#define Dominoes_DNBackground_h

#include "DNCustomSprite.h"
#include "DNDomino.h"

class DNBackground : public DNCustomSprite {
    
public:
    
    DNBackground();
    virtual ~DNBackground();
    
    // Creation of sprite!
    DNBackground* spriteWithFile(const char *pszFileName);
    
    void createBackground(CCPoint position, int tag);
    
    CCRenderTexture *backgroundTexture;
};

#endif
