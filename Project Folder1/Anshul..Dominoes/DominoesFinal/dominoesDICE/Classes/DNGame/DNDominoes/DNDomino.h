
//  DNDomino.h
//  Dominoes
//
//  Created by ICRG LABS on 23/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Dominoes_DNDomino_h
#define Dominoes_DNDomino_h

#include "DNCustomSprite.h"
#include "DNPlayerPanel.h"
#include "DNBackgroundManager.h"
#include "DNBackground.h"

// Possible states of Tile...
typedef enum {    
    
    kTileWithPlayer,
    kTileInBoard,
    kTileOnMovement
    
} TileState;

struct AvailabilityDetails {
  
    bool isAvailableForLeftMovement;
    bool isAvailableForRightMovement;
    bool isVertical;
    bool isHorizontal;
    float leftRotationAngle;
    float rightRotationAngle;
};

struct PlacementDetailsObject {
    
    bool isPlaced;
    bool isLeft;
    bool isTargetHorizontal;
    bool isTargetVertical;
    
    CCPoint targetPosition;
};

class DNDomino : public DNCustomSprite {
    
public:
    
    DNDomino(void);
    virtual ~DNDomino(void);
    
    // Creation of a tile...
    DNDomino* spriteWithFile(const char *pszFileName);
    DNDomino* spriteWithFrame(const char *pszFileName);
    DNDomino* create(CCSpriteFrame *pSpriteFrame);
   
    void createSpriteAtPosition(CCPoint position,int tag, int zOrder, int topValue, int bottomValue, int locationInRow, int playerID, int panelTag, int numberOfTilesPerPlayer);
    
    void checkCollision();
    void moveBackToPlayer();
    void addToOwner();
    PlacementDetailsObject checkTileEdgePointsMatched(DNDomino *aTile);
    //void arrangeTileOnBoard(PlacementDetailsObject obj);
    void arrangeTileOnBoard(bool isLeft);
    void tilePlacementIndicator(bool isCorrect);
    void removeTileGlow(CCObject *sender);
    void rotateTileForAI(float angle);
    void updateValuesForTile();
    void updateCallBack();
    void pause();
    void restart();
    void playerWinAnimation();
    void playerWinAnimationForOneOpponent();
    void callback();
    void startTimer();
//    void tick();
    
    // Helper functions
    float getCurrentAngle();
    void rotateToAppropriateAngle(float currentAngle);
    bool checkForCorrectRotation();
    int getCurrentAnglesTileValues(bool isLeft,DNDomino *aTile);
    float getAdjacentValue();

    // Tile Properties!
    int topValue;
    int bottomValue;
    int totalValue;
    int location;
    int valuecount;
    
    TileState state;
    DNPlayerPanel *tilesOwnerPanel;
    CCLabelTTF *score;
    
    int touchId; // For multitouch tracking purpose!
    int playerID;
    
    CCPoint position;       // Position on it's panel
    CCPoint worldPosition; // Full size world coordinate
    CCPoint scaleDownWorldCoordinate; // After scale down panels tile position
    CCLabelTTF *label;
    CCSprite *illegalpos;
    
    bool isVertical;
    bool isHorizontal;
    bool isLeftCollidable;
    bool isRightCollidable;
    
    float toRotateAngle;
    
    // Only for AI
    // Used for internally know that the tile is availability
    AvailabilityDetails movementDetail;
};

#endif
