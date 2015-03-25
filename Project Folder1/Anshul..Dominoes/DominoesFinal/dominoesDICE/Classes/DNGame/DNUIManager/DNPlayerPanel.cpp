//
//  DNPlayerPanel.cpp
//  Dominoes
//
//  Created by ICRG LABS on 29/08/12.
//
//

#include "DNPlayerPanel.h"
#include "DNDataManager.h"
#include "SimpleAudioEngine.h"

DNPlayerPanel::DNPlayerPanel(void) {
    
    this->gameLayer = DataManager->gameLayer;
    this->tileCount = 0;
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("btn_animal_timer.plist");
}

DNPlayerPanel::~DNPlayerPanel(void) {

    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrameByName("btn_animal_timer.plist");
}

// To create sprite from sprite sheet!
DNPlayerPanel* DNPlayerPanel::spriteWithFrame(const char *pszFileName) {
    
    CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pszFileName);
    
    char msg[256] = {0};
    sprintf(msg, "Invalid spriteFrameName: %s", pszFileName);
    CCAssert(pFrame != NULL, msg);
    
    DNPlayerPanel *tempSpr = DNPlayerPanel::create(pFrame);
    
    return tempSpr;
}

DNPlayerPanel* DNPlayerPanel::create(CCSpriteFrame *pSpriteFrame) {
    
    DNPlayerPanel *pobSprite = new DNPlayerPanel();
    if (pobSprite && pobSprite->initWithSpriteFrame(pSpriteFrame))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

void DNPlayerPanel::createPanel(CCPoint position, CCPoint anchorPoint, bool isFlipY, int tag) {
    
    this->setPosition(position);
    this->setAnchorPoint(anchorPoint);
    this->setFlipY(isFlipY);
    this->setTag(tag);
    this->state = kPanelClosed;
    DataManager->UILayer->addChild(this);
    
    DNCustomSprite *namePanel = namePanel->spriteWithFrame("player_area.png");
    namePanel->setOpacity(0);
    
    if (!isFlipY) { // Player one
        
        namePanel->setPosition(ccp(this->getPosition().x, this->getPosition().y + namePanel->getContentSize().height/2));
        
        DNCustomSprite *passBtn = passBtn->spriteWithFrame("usr_pass.png");
        DNCustomSprite *passBtnSelected = passBtnSelected->spriteWithFrame("usr_pass.png");
       
        CCMenuItemSprite *playButton = CCMenuItemSprite::create(passBtn,passBtnSelected,this,menu_selector(DNPlayerPanel::menuCallbacks));
        playButton->setPosition( ccp(namePanel->getPosition().x + namePanel->getContentSize().width/5 - 13,namePanel->getPosition().y - 44));
        playButton->setTag(tag + 100);
        
        CCLabelTTF *dragLabel = CCLabelTTF::create("IRENET", "Helvetica", 20);
        dragLabel->setPosition(ccp(dragLabel->getContentSize().width/5 + 550,dragLabel->getPosition().y+ 50));
        DataManager->UILayer->addChild(dragLabel);
        
        CCMenu *passMenu1 = CCMenu::create(playButton,NULL);
        passMenu1->setPosition(CCPointZero);
        passMenu1->setTag(tag + 1000);
        passMenu1->setVisible(true);
        passMenu1->setEnabled(false);

        DataManager->UILayer->addChild(passMenu1);
    }
    else {      // Opponents
        
        namePanel->setPosition(ccp(this->getPosition().x,(this->getPosition().y - namePanel->getContentSize().height/2)));

        CCSprite *ok_normal = CCSprite::createWithSpriteFrameName("ok_btn.png");
        CCSprite *ok_selected = CCSprite::createWithSpriteFrameName("ok_btn_hvr.png");
        
        CCMenuItemSprite *playButton = CCMenuItemSprite::create(ok_normal,ok_selected,this,menu_selector(DNPlayerPanel::menuCallbacks));
        
        playButton->setPosition(ccp(namePanel->getPosition().x + namePanel->getContentSize().width/5 + 50,namePanel->getPosition().y + 35));
        
        playButton->setTag(tag + 100);
  
        
        CCSprite *spr =CCSprite::createWithSpriteFrameName("pass1.png");
        
        spr->setPosition(ccp(namePanel->getPosition().x + namePanel->getContentSize().width/5 + 10,namePanel->getPosition().y + 70));
        
        spr->setTag(tag + 100);
        
        DataManager->UILayer->addChild(spr);
        
        spr->setVisible(false);

        passMenu = CCMenu::create(playButton,NULL);
        passMenu->setPosition(CCPointZero);
        passMenu->setTag(tag + 1000);
        passMenu->setVisible(false);
        DataManager->UILayer->addChild(passMenu);
    }
    namePanel->setFlipY(isFlipY);
    DataManager->UILayer->addChild(namePanel);
}

void DNPlayerPanel::youngBunnyPass() {
    
    CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->addSpriteFramesWithFile("dominoes_new.plist");

    CCSprite *sprite = CCSprite::createWithSpriteFrameName("youngbunny-disappointed0001.png");
    sprite->setPosition(ccp(sprite->getContentSize().width/5 + 340,sprite->getPosition().y + 75));
    
    this->gameLayer->uiManager->playerPanel2->addChild(sprite);
    
    CCArray *animFrames = CCArray::create();
    char tmp[50];
    
    for (int j = 1; j <= 7; j++){
        
        sprintf(tmp, "youngbunny-disappointed000%d.png", j);
        CCSpriteFrame *frame = cache->spriteFrameByName(tmp);
        animFrames->addObject(frame);
    }
    
    CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames,0.3f);
    sprite->runAction(CCAnimate::create(animation));
    sprite->setRotation(180);
    
//    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Aww.mp3");
}


void DNPlayerPanel::giraffePass() {
    
    CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->addSpriteFramesWithFile("dominoes_new.plist");

    CCSprite *sprite = CCSprite::createWithSpriteFrameName("giraffe-disappointed0001.png");
    sprite->setPosition(ccp(sprite->getContentSize().width/5 + 340,sprite->getPosition().y + 75));
    
    this->gameLayer->uiManager->playerPanel3->addChild(sprite);
    
    CCArray *animFrames = CCArray::create();
    char tmp[50];
    for (int j = 1; j <= 7; j++){
        
        sprintf(tmp, "giraffe-disappointed000%d.png",j);
        CCSpriteFrame *frame = cache->spriteFrameByName(tmp);
        animFrames->addObject(frame);
    }
    
    CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames,0.3f);
    sprite->runAction(CCAnimate::create(animation));
    sprite->setRotation(180);
    
//    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Aww.mp3");
}


void DNPlayerPanel::expandPanel() {
    
    if (this->state == kPanelClosed) {
    
//     CCFiniteTimeAction *scaleAction = CCScaleTo::create(0.2, 1.0f);
        CCFiniteTimeAction *callBackN = CCCallFuncN::create(this, callfuncN_selector(DNPlayerPanel::changeState));
//       CCFiniteTimeAction *actionSequence = CCSequence::create(callBackN,NULL);
       this->runAction(callBackN);
       this->gameLayer->uiManager->playerPanel1->setColor(ccc3(255,0,0));
    }
   
    this->stopActionByTag(kPanelClosingActionTag);
    CCFiniteTimeAction *delayAction = CCDelayTime::create(3);
    CCFiniteTimeAction *actionCallBack = CCCallFuncN::create(this, callfuncN_selector(DNPlayerPanel::closePanel));
    CCFiniteTimeAction *actionSequence = CCSequence::create(delayAction,actionCallBack,NULL);
   this->runAction(actionSequence);
}

void DNPlayerPanel::closePanel() {
    
//  CCFiniteTimeAction *scaleAction = CCScaleTo::create(0.2, kPanelsScaleValue);
    CCFiniteTimeAction *callBackN = CCCallFuncN::create(this, callfuncN_selector(DNPlayerPanel::changeState));
//    CCFiniteTimeAction *actionSequence = CCSequence::create(callBackN,NULL);
    this->runAction(callBackN);
}

// Change the state after the transition is finished!
void DNPlayerPanel::changeState() {
    
    this->state = kPanelOpened;
    
/*    if (this->getScale() == 1.0f) {
        
        this->state = kPanelOpened;
        //printf("\n panel %d is opened",this->getTag() - 10000);
    }
    else if(this->getScale() == kPanelsScaleValue) {

        this->state = kPanelClosed;
        //printf("\n panel %d is closed",this->getTag() - 10000);
    }
*/
}

void DNPlayerPanel::menuCallbacks(CCObject* sender) {
    
    CCMenuItemImage *tempItem = (CCMenuItemImage *)sender;
    
    switch (tempItem->getTag()) {
            
        case kPlayerPanel1Tag + 100: // Player pass button
            
            if (!CCDirector::sharedDirector()->isPaused()) {
                
//                CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Subtle_Click.mp3");
                
                ScheduleManager->passTurnToNextPlayer();
                ((CCMenu *)DataManager->UILayer->getChildByTag(kPlayerPanel1Tag + 1000))->setVisible(true);
                
                ((CCMenu *)DataManager->UILayer->getChildByTag(kPlayerPanel1Tag + 1000))->setColor(ccc3(255,255,255));
                
                CCLog("player pass button pressed");
            }
            break;
            
        case kPlayerPanel2Tag + 100:
            
            if (!CCDirector::sharedDirector()->isPaused()) {
                
                ScheduleManager->passTurnToNextPlayer();
                
                this->youngBunnyPass();
                
                ((CCMenu *)DataManager->UILayer->getChildByTag(kPlayerPanel2Tag + 1000))->setVisible(false);
               ((CCSprite*)DataManager->UILayer->getChildByTag(kPlayerPanel2Tag+100))->setVisible(false);
            }
            break;
            
        case kPlayerPanel3Tag + 100:
            
            if (!CCDirector::sharedDirector()->isPaused()) {
                
                ScheduleManager->passTurnToNextPlayer();
                
                this->giraffePass();
                
                ((CCMenu *)DataManager->UILayer->getChildByTag(kPlayerPanel3Tag + 1000))->setVisible(false);
                ((CCSprite*)DataManager->UILayer->getChildByTag(kPlayerPanel3Tag+100))->setVisible(false);
            }
            break;
            
        default:
            break;
    }
}