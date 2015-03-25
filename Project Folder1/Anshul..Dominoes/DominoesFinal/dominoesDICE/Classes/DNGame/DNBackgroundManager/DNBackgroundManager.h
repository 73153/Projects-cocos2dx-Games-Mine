//
//  DNBackgroundManager.h
//  Dominoes
//
//  Created by ICRG LABS on 08/08/12.
//
//

#ifndef Dominoes_DNBackgroundManager_h
#define Dominoes_DNBackgroundManager_h

#include "DNGameManager.h"
#include "cocos2d.h"

#include "DNDomino.h"
#include "DNDominoManager.h"

class DNBackground;
using namespace cocos2d;

class DNBackgroundManager : DNGameManager {
   
public:

    DNBackgroundManager(void);
    virtual ~DNBackgroundManager(void);

    // Creating Background...
    void createBackground();

    // Adjustments
    void adjustBackgroundToTilePosition(bool isToAdjustLeft,float leftEdgeTilePosition,float rightEdgeTilePosition);
    void moveBackgroundToCenter();
    void draw();
    
    // Touch Methods
    void backgroundManagerTouchesBegan(CCSet *touches);
    void backgroundManagerTouchesMoved(CCSet *touches);
    void backgroundManagerTouchesEnded(CCSet *touches);
    void backgroundManagerTouchesCancelled(CCSet *touches);

    // iVars
    DNBackground *gameBackground;
    
    CCTexture2D *textureLeft;
    CCTexture2D *textureRight;
    CCTexture2D *textureLeft1;
    CCTexture2D *textureRight1;
    
    CCImage *imageLeft;
    CCImage *imageRight;
    CCImage *imageLeft1;
    CCImage *imageRight1;

    float xDifference;
    float scrollimit;
    float leftDifference;
    float rightDifference;

    bool isScrollEnabled;
    bool isTouchedOnTop;
    bool isSwipedLeft;
    bool isReachedLeftEdge;
    bool isReachedRightEdge;
    bool istouchedPanel;
};

#endif
