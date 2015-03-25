
#ifndef Dominoes_DNDominoManager_h
#define Dominoes_DNDominoManager_h

#include "DNGameManager.h"

#include "cocos2d.h"
#include "DNBackgroundManager.h"

class DNDomino;
class DNBackground;
class DNUIManager;

using namespace cocos2d;

struct EdgeTiles {
    
    DNDomino *left;
    DNDomino *right;
};

class DNDominoManager : public DNGameManager {
    
public:
    
    DNDominoManager(void);
    virtual ~DNDominoManager(void);
    
    // Methods
//    void dominoManagerTick();
    
    void suffleTiles();
    void serveTilesForPlayer(int playerNumber);
    void arrangeTilesOfPlayer(int playerNumber,int tileLocation);
    bool isLastTileForPlayer(int playerNumber, int tileLocation);
    int numberOfTilesWithPlayer(int playerNumber);
    void assignDownScaleWorldCoordinates();
    
    // AI
    void playOpponentMove();
    CCArray* getPossibleTilesForOpponents(int playerNumber);
    bool checkCurrentTileValueForEdgeValues(bool isLeft, DNDomino *tile, CCArray *possibleTilesArray);
    
    CCDictionary* getDetailsOfTile(int tileNumber);
    
    // Touch Methods
    void dominoesManagerTouchesBegan(CCSet *touches);
    void dominoesManagerTouchesMoved(CCSet *touches);
    void dominoesManagerTouchesEnded(CCSet *touches);
    void dominoesManagerTouchesCancelled(CCSet *touches);
    
    // Touch Helper Methods
    void addTouchToArray(CCSet *touches);
    void removeTouchFromArray(CCSet *touches);
    void getSelectedTile(CCTouch *touch);
    void rotateAndMoveTile(CCPoint touchPoint);
    void getDoubleTappedAngleAndNullifySelectedTile();
    void callback();
    void pause();
    void restart();
    void youngBunnyExcited();
    void giraffeExcited();
    
    CCLabelTTF *score;
    CCLabelTTF *clockLabel;
    
    // iVars
    CCArray *dominoesArray;
    CCArray *playerArray;
    
    CCArray *touchesArray;
    CCArray *lineOfPlayArray;
    CCArray *backTileArray;
    
    CCArray *opponentOneArray;
    CCArray *opponentTwoArray;
    
    // Reference holder!
    DNDomino *selectedTile;
    DNUIManager *dnui;
    CCDictionary *dominoDetailsDict;
    EdgeTiles edgeTile;
    DNPlayerPanel *playerPanel1;
    DNPlayerPanel *playerPanel2;
    DNPlayerPanel *playerPanel3;
    
    CCSprite *cup;
    CCSprite * ziraffe;
    CCSprite *rabit;
    CCSprite *playerName;
    CCSprite *opponentOneName;
    CCSprite *opponentTwoName;
    CCSprite *gamerWinBackGrd;
    CCSprite *spr;
    
    int suffledValues[28];
    int *slots;
    int possibleTileCount;
    int selectedtilecount;
    int passcount;
    int valuecount;
    int remainingtilecount;
    
    int opponentOneScore;
    int opponentTwoScore;
    int playerScore;
    
    float startingAngle;
    float doubleTappedAngle;
    float leftMostEdgeSize;
    float rightMostEdgeSize;
    CCLabelTTF *label;
    
    CCParticleSystem *zigzag; // player win animation in gameover scene
    
    DNBackground *gameBackground;  
    DNDomino *domino;
    
    bool isFirstThrow;
    bool isHorizontal;
    bool isVertical;
    
    CCMenu *tempItem1;
    CCMenu *tempItem2;
    CCMenu *tempItem0;
    
    CCLabelTTF *playerLabel;
    CCLabelTTF *opponentOneLabel;
    CCLabelTTF *opponentTwoLabel;
};

#endif