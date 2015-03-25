//
//  LMStoreLayer.cpp
//  LMGame
//
//  Created by Pavitra on 03/09/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "LMStoreLayer.h"
#include "LMMainScreen.h"
#include "LMDataManager.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "LMObjectiveCCalls.h"

#else

#endif


#define kGetMButtonTag 100
#define kGetLivesButtonTag 200
#define kGetRelicsButtonTag 300
#define kGetMapsButtonTag 400

#define kMapsMenuTag 401

using namespace cocos2d;



LMStoreLayer::LMStoreLayer(){
    
    //IAP & others
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    
    LMObjectiveCCalls::loadIAP();
    moneyCount = LMObjectiveCCalls::getTotalMoney();
#else
    
#endif
    
    //Initiliase Variables
    this->purchasedMoneyCount = 0;
    this->isPurchasingMaps = false;
    this->canPressButtons = true;
    
    
    LMDataManager::sharedManager()->canMainMenuStoreBtnWork =  true;
    LMDataManager::sharedManager()->canStoreButtonsWork=true;
    
    // Loading the plist...
    const char *pszPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("LMStoreData.plist");
    
    // Getting the dictionaries into...
    this->allStoreDataDict = CCDictionary::createWithContentsOfFileThreadSafe(pszPath);
    
    //bgLayer
    bgLayer=new CCLayer();
    this->addChild(bgLayer,18);
    
    //lives layer
    livesLayer=new CCLayer();
    this->addChild(livesLayer,20);
    
      
    float width=CCDirector::sharedDirector()->getWinSize().width;
    float height=CCDirector::sharedDirector()->getWinSize().height;
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("LMStoreScene.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("LMStoreScene.plist");
   
    //bg
    CCSprite *storeBG=CCSprite::create("ui_popup_bg.png");
    storeBG->setPosition(CCPointMake(width/2, height/2));
    this->addChild(storeBG,10);
    
    //add buttons
    this->addIntialButtonsWithBG();
    if(LMDataManager::sharedManager()->toGoStoreScene == 2)
    {
        this->loadRelicsData();
    }
    else if(LMDataManager::sharedManager()->toGoStoreScene == 3)
    {
        this->loadWorldMapData();
    }
    else{
        
       
        this->loadRelicsData();
    }
    
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(LMStoreLayer::purchaseSuccesfull), "Purchase Succesful", NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(LMStoreLayer::purchaseFailed), "Purchase Failed", NULL);

}

#pragma mark - Initialise View
void LMStoreLayer::addIntialButtonsWithBG()
{
    float width=CCDirector::sharedDirector()->getWinSize().width;
    float height=CCDirector::sharedDirector()->getWinSize().height;

    CCSprite *normalSprite;
    CCSprite *selectedSprite;
    //store_icon
    CCSprite *topStoreIcon = CCSprite::createWithSpriteFrameName("store_icon.png");
    topStoreIcon->setPosition(CCPointMake(width/2-150, height-180));
    bgLayer->addChild(topStoreIcon,11);
    
    //store Number label
    //char mNumber[5];
    
    char moneyCountStr[15];
    sprintf(moneyCountStr, "%d",moneyCount);
    
    
    this->mNumberLabel = CCLabelTTF::create(moneyCountStr, "LMVeraHumana95Bold", 65);
    this->mNumberLabel->setPosition(CCPointMake(width/2+15, height-180));
    this->mNumberLabel->setColor(ccc3(76,54,12));
    bgLayer->addChild(this->mNumberLabel,14);
    
        
    // relics menu
    normalSprite=CCSprite::createWithSpriteFrameName("relics_btn1.png");
    selectedSprite=CCSprite::createWithSpriteFrameName("relics_btn_hvr1.png");
   relicsMenuItem=CCMenuItemSprite::create(selectedSprite, normalSprite, this, menu_selector(LMStoreLayer::action));
    relicsMenuItem->setTag(2);
    relicsMenuItem->setPosition(CCPointMake(width-700, height-265));
    
    
    //Maps menu
    normalSprite=CCSprite::createWithSpriteFrameName("map_btn.png");
    selectedSprite=CCSprite::createWithSpriteFrameName("map_btn_hvr.png");
    mapMenuitem=CCMenuItemSprite::create(selectedSprite, normalSprite, this, menu_selector(LMStoreLayer::action));
    mapMenuitem->setTag(9);
    mapMenuitem->setPosition(CCPointMake(width-509, height-265));
    

    
    // Get menu
    normalSprite=CCSprite::createWithSpriteFrameName("get_m_btn.png");
    selectedSprite=CCSprite::createWithSpriteFrameName("get_m_btn_hvr.png");
    getMenuItem=CCMenuItemSprite::create(selectedSprite, normalSprite, this, menu_selector(LMStoreLayer::action));
    getMenuItem->setTag(3);
    getMenuItem->setPosition(CCPointMake(width-308, height-265));
           
    //Menu
    topMainMenu=CCMenu::create(relicsMenuItem,getMenuItem,mapMenuitem, NULL);
    bgLayer->addChild(topMainMenu,11);
    topMainMenu->setPosition(CCPointMake(0, 0));
    
  
    
    CCSprite *livesColumn=CCSprite::createWithSpriteFrameName("store_colm_bg.png");
    livesColumn->setPosition(CCPointMake(width/2+5, height/2-100));
    bgLayer->addChild(livesColumn,11);
    

    this->updateMoneyCountInView();

}

void LMStoreLayer::updateMoneyCountInView()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    
    moneyCount = LMObjectiveCCalls::getTotalMoney();
#else
    
#endif
    
    char moneyCountStr[15];
    sprintf(moneyCountStr, "%d",moneyCount);
    this->mNumberLabel->setString(moneyCountStr);
}

#pragma mark - Tabs action

void LMStoreLayer::action(cocos2d::CCMenuItemImage *sender){
    
    if (this->canPressButtons == false) {
        return;
    }
    
    int tag=sender->getTag();
    
    switch (tag) {
            
        case 2:
        {
            //relics button
            livesLayer->removeAllChildrenWithCleanup(1);
            this->loadRelicsData();
            
        }
            break;
            
        case 3:
        {
            //getM button
            
            livesLayer->removeAllChildrenWithCleanup(1);
            this->loadGetMData();
        }
            break;
        case 5:
        {
            // back button
            livesLayer->removeAllChildrenWithCleanup(1);
            this->addIntialButtonsWithBG();
            this->loadRelicsData();
        }
            break;
        case 6:
        {
            //continue button action
            livesLayer->removeAllChildrenWithCleanup(1);
            this->addIntialButtonsWithBG();
            this->loadRelicsData();
        }
            break;
        case 7:
        {
            //close button
            this->removeAllChildrenWithCleanup(true);
            this->removeFromParentAndCleanup(true);
        }
            break;
        case 8:
        {
            //Get ButtonDetals getM button
            livesLayer->removeAllChildrenWithCleanup(1);
            this->addIntialButtonsWithBG();
         
            this->loadGetMData();
        }
            break;
        case 9:
        {
            //Map Details
            livesLayer->removeAllChildrenWithCleanup(true);
            
            this->loadWorldMapData();
            
            
        }
            break;
            
        default:
            break;
    }
}




#pragma mark - Relics
void LMStoreLayer::loadRelicsData()
{
    
    getMenuItem->unselected();
    mapMenuitem->unselected();
    relicsMenuItem->selected();
    
    

    CCDictionary *relicsDict = (CCDictionary *)this->allStoreDataDict->valueForKey("Relics");
    
    //Get the list of Lives from the LivesDict
    CCArray *relicsListArr = (CCArray *)relicsDict->valueForKey("RelicsList");
    
    CCDictionary *relicsDetailsDict = (CCDictionary *)relicsDict->valueForKey("RelicsDetails");
    
    //relics top label
    CCLabelTTF *topLabel=CCLabelTTF::create("Trade       for Relic Packs", "LMVeraHumana95Bold", 25);
    topLabel->setPosition(CCPointMake(345, 450));
    topLabel->setColor(ccc3(236, 213, 139));
    livesLayer->addChild(topLabel,14);
    
    CCSprite *smallMIcon=CCSprite::createWithSpriteFrameName("m_icon_small.png");
    smallMIcon->setPosition(CCPointMake(90, 15));
    topLabel->addChild(smallMIcon,14);
    
    CCObject *aRelicsDetailsObj = NULL;
    float xOffset=515;
    float yOffset=365;
    
    int buyRelicsButtonTag = kGetRelicsButtonTag;

    
    CCARRAY_FOREACH(relicsListArr, aRelicsDetailsObj)
    {
        CCString *aRelicsDetailsDict = (CCString *)aRelicsDetailsObj;
        
        //store column
        CCSprite *storeColumn=CCSprite::createWithSpriteFrameName("store_colm.png");
        storeColumn->setPosition(CCPointMake(xOffset, yOffset));
        livesLayer->addChild(storeColumn,14);
        
        //live icon
        CCSprite *livesIcon=CCSprite::createWithSpriteFrameName("relics_icon1.png");
        livesIcon->setPosition(CCPointMake(xOffset-275, yOffset));
        livesLayer->addChild(livesIcon,14);
        
        //lives label
        char noOfLivesNumber[5];
        sprintf(noOfLivesNumber, "%s",aRelicsDetailsDict->getCString());
        CCLabelTTF *earningNumberLabel=CCLabelTTF::create(noOfLivesNumber, "LMVeraHumana95Bold", 30);
        earningNumberLabel->setPosition(CCPointMake(xOffset-170, yOffset));
        earningNumberLabel->setColor(ccc3(138,108,24));
        livesLayer->addChild(earningNumberLabel,14);
        
        //equal symbol
        CCLabelTTF *equalsSymbol=CCLabelTTF::create("=", "LMVeraHumana95Bold", 40);
        equalsSymbol->setPosition(CCPointMake(xOffset-80, yOffset-5));
        equalsSymbol->setColor(ccc3(138,108,24));
        livesLayer->addChild(equalsSymbol,14);
        
        //storeIcon2
        CCSprite *storeIcon2=CCSprite::createWithSpriteFrameName("store_icon_2.png");
        storeIcon2->setPosition(CCPointMake(xOffset-20, yOffset));
        livesLayer->addChild(storeIcon2,14);
        
        //mlabel nummer
        char mlabelNumber[10];
        sprintf(mlabelNumber, "%s",relicsDetailsDict->valueForKey(aRelicsDetailsDict->getCString())->getCString());
        
        CCLabelTTF *mRelicsLbl=CCLabelTTF::create(mlabelNumber, "LMVeraHumana95Bold", 30);
        mRelicsLbl->setPosition(CCPointMake(xOffset+103, yOffset-3));
        mRelicsLbl->setColor(ccc3(76,54,12));
        livesLayer->addChild(mRelicsLbl,14);
        
        //m_icon
        CCSprite *mIcon=CCSprite::createWithSpriteFrameName("m_icon.png");
        mIcon->setPosition(CCPointMake(xOffset+55, yOffset));
        livesLayer->addChild(mIcon,14);
        
        // Get menu
        CCSprite *normalSprite=CCSprite::createWithSpriteFrameName("get_btn.png");
        CCSprite *selectedSprite=CCSprite::createWithSpriteFrameName("get_btn_hvr.png");
        CCMenuItemSprite *getMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(LMStoreLayer::purchaseRelics));
        getMenuItem->setTag(buyRelicsButtonTag);
        getMenuItem->setPosition(CCPointMake(xOffset+235, yOffset));
        
        // Button menu
        CCMenu *topMenu=CCMenu::create(getMenuItem,NULL);
        livesLayer->addChild(topMenu,14);
        topMenu->setPosition(CCPointMake(0, 0));
        
        //incrementing y value
        yOffset=yOffset-73;
        
        buyRelicsButtonTag ++;
        
    }
}

void LMStoreLayer::purchaseRelics(CCMenuItemImage *sender)
{
    int senderTag = sender->getTag();
    
    int moneyToDeduct = 0;
    int randomRelicsToGet = 0;
    
    switch (senderTag) {
        case kGetRelicsButtonTag:
        {
            //Required M  5 RELICS = 60
            if(moneyCount<60)
            {
                this->loadNotEnoughCredit();
            }
            else
            {
                moneyToDeduct = 60;
                randomRelicsToGet = 5;
            }
        }
            break;
            
        case kGetRelicsButtonTag+1:
        {
            //Required M 10 RELICS = 100
            if(moneyCount<100)
            {
                this->loadNotEnoughCredit();
            }
            else
            {
                moneyToDeduct = 100;
                randomRelicsToGet = 10;
            }
        }
            break;
            
        case kGetRelicsButtonTag+2:
        {
            //Required M  20 RELICS = 160
            if(moneyCount<160)
            {
                this->loadNotEnoughCredit();
            }
            else
            {
                moneyToDeduct = 160;
                randomRelicsToGet = 20;
            }
        }
            break;
            
                    
        default:
            break;
    }
    
    if(moneyToDeduct!=0)
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        LMObjectiveCCalls::addMoneyToDatabaseWithMoney(-moneyToDeduct);
        LMObjectiveCCalls::obtainRandomRelicsWithCount(randomRelicsToGet);
#else
        
#endif
        this->updateMoneyCountInView();
        this->showRelicsRecievedScene(randomRelicsToGet);

    }
    //Clear the Random Relics arr
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    
    LMObjectiveCCalls::clearRandomRelicsArr();
    
#else
    
    
#endif

}

void LMStoreLayer:: showRelicsRecievedScene(int randomRelicsToGet)
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("LMRelicsSceneImages.plist");
    
    //Remove other layers
    bgLayer->removeAllChildrenWithCleanup(1);
    livesLayer->removeAllChildrenWithCleanup(1);
    
    float width=CCDirector::sharedDirector()->getWinSize().width;
    float height=CCDirector::sharedDirector()->getWinSize().height;
    
    CCLabelTTF *topLabel=CCLabelTTF::create("Relics Recieved!", "LMVeraHumana95Bold", 45);
    topLabel->setPosition(CCPointMake(width/2, height-160));
    topLabel->setColor(ccc3(56, 6, 2));
    livesLayer->addChild(topLabel,14);
    
    //No Of Relics Label
    char noRelics[5];
    
    sprintf(noRelics, "You have recieved a Relic Pack of %d Relics",randomRelicsToGet);

    
    CCLabelTTF *topSubLabel = CCLabelTTF::create(noRelics, "LMVeraHumana95Bold", 25);
    topSubLabel->setPosition(CCPointMake(width/2, height-200));
    livesLayer->addChild(topSubLabel,20);
    topSubLabel->setColor(ccc3(183,71,13));
    
        
    //Relics column image
    CCSprite *relicsColm=CCSprite::create("relics_receivd_colm.png");
    relicsColm->setPosition(CCPointMake(512, 320));
   
    livesLayer->addChild(relicsColm,20);
    
    CCLabelTTF *notEnoughColmSubLabel=CCLabelTTF::create("Your relics indicator are listed below,Visit your collection page \n to see if you can claim a new Monster. ", "LMVeraHumana95Bold", 22);
    notEnoughColmSubLabel->setPosition(CCPointMake(400, 335));
    relicsColm->addChild(notEnoughColmSubLabel,20);
    notEnoughColmSubLabel->setColor(ccc3(132, 81, 23));
    
    //Relics icon in column
    CCSprite *livesIcon=CCSprite::createWithSpriteFrameName("relics_icon.png");
    livesIcon->setPosition(CCPointMake(70, 340));
    relicsColm->addChild(livesIcon,14);
    
    //buttons
    //continueMenuItem Button
    CCSprite *normalSprite=CCSprite::create("continue_bt.png");
    CCSprite *selectedSprite=CCSprite::create("continue_bt_hvr.png");
    CCMenuItemSprite *continueMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(LMStoreLayer::action));
    continueMenuItem->setTag(6);
    continueMenuItem->setPosition(CCPointMake(512, 130));
    
    
    //button Menu
    CCMenu *bottomButtonsMenu=CCMenu::create(continueMenuItem,NULL);
    livesLayer->addChild(bottomButtonsMenu,20);
    bottomButtonsMenu->setPosition(CCPointMake(0, 0));
    
    
    //Add Relics in ScrollView
    
    CCLayer *scrollLayer = CCLayer::create();
        
    CCScrollView *scrollView = CCScrollView::create(CCSize(764,300));
    scrollView->setDirection(kCCScrollViewDirectionVertical);
    scrollView->setBounceable(true);
    scrollView->setContainer(scrollLayer);
    livesLayer->addChild(scrollView,20);
    
    scrollView->setPosition(CCPointMake(200,170));
    
    int totalCards = randomRelicsToGet;
    int totalRows = totalCards/4;
    
    //Check whether we have 4 cards in each row
    int remainder = totalCards%4;
    
    if (remainder!=0) {
        totalRows++;
    }
    
    int xPos = 70;
    int yPos = (totalRows*250);
    
    int scrlHeight = 0;
    
    int index = 1;
    
    for (int i = 0; i<totalCards; i++) {
        
        //Get random Relic Name
        
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        
        const char *randomRelicName = LMObjectiveCCalls::getRandomRelicNameAtIndex(i);
        
#else
        
        
#endif
        
        //Add Monster Card BG
        CCSprite *aRelicsCardBGSpr = CCSprite::createWithSpriteFrameName("relics_card_bg.png");
        aRelicsCardBGSpr->setPosition(CCPointMake(xPos, yPos));
        scrollLayer->addChild(aRelicsCardBGSpr);

        char aRelicsName[60];
        sprintf(aRelicsName, "%s.png",randomRelicName);
        
        CCSprite *aRelic = CCSprite::create(aRelicsName);
        aRelic->setPosition(CCPointMake(xPos, yPos+15));
        scrollLayer->addChild(aRelic);

        xPos = xPos + 160;
        
        if(index%4==0)
        {
            xPos = 70;
            yPos = yPos-250;
            scrlHeight = scrlHeight + 250;
        }
        index++;

        
    }
    scrollView->setContentSize(CCSize(898,totalRows*250+150));
    scrollView->setContentOffset(CCPointMake(0,-totalRows*250+150), false);
}

#pragma mark - Get M
void LMStoreLayer::loadGetMData()
{
    mapMenuitem->unselected();
    getMenuItem->selected();
    relicsMenuItem->unselected();
   
    CCDictionary *getMDict = (CCDictionary *)this->allStoreDataDict->valueForKey("GetM");
    
    //Get the list of Lives from the LivesDict
    CCArray *getMListArr = (CCArray *)getMDict->valueForKey("GetMList");
    
    CCDictionary *getMDetailsDict = (CCDictionary *)getMDict->valueForKey("GetMDetails");
    
    //getM top label
    CCLabelTTF *topLabel=CCLabelTTF::create("Get additional       with FB Credits", "LMVeraHumana95Bold", 25);
    topLabel->setPosition(CCPointMake(380, 450));
    topLabel->setColor(ccc3(236, 213, 139));
    livesLayer->addChild(topLabel,14);
    
    CCSprite *smallMIcon=CCSprite::createWithSpriteFrameName("m_icon_small.png");
    smallMIcon->setPosition(CCPointMake(180, 15));
    topLabel->addChild(smallMIcon,14);
    
    CCObject *aGetMDetailsObj = NULL;
    float xOffset=515;
    float yOffset=365;
    
    
    int buyButtonTag = kGetMButtonTag;
    
    CCARRAY_FOREACH(getMListArr, aGetMDetailsObj)
    {
        CCString *aGetDetailsDict = (CCString *)aGetMDetailsObj;
        
        //store column
        CCSprite *storeColumn=CCSprite::createWithSpriteFrameName("store_colm.png");
        storeColumn->setPosition(CCPointMake(xOffset, yOffset));
        livesLayer->addChild(storeColumn,14);
        
        //store icon
        CCSprite *livesIcon=CCSprite::createWithSpriteFrameName("store_icon_2.png");
        livesIcon->setPosition(CCPointMake(xOffset-265, yOffset));
        livesLayer->addChild(livesIcon,14);
        
        
        //mlabel nummer
        char mlabelNumber[10];
        sprintf(mlabelNumber, "%s",aGetDetailsDict->getCString());
        
        CCLabelTTF *requiredMLbl=CCLabelTTF::create(mlabelNumber, "LMVeraHumana95Bold", 30);
        requiredMLbl->setPosition(CCPointMake(xOffset-135, yOffset-3));
        requiredMLbl->setColor(ccc3(76,54,12));
        livesLayer->addChild(requiredMLbl,14);
        
        //m_icon
        CCSprite *mIcon=CCSprite::createWithSpriteFrameName("m_icon.png");
        mIcon->setPosition(CCPointMake(xOffset-182, yOffset));
        livesLayer->addChild(mIcon,14);
        
        //equal symbol
        CCLabelTTF *equalsSymbol=CCLabelTTF::create("=", "LMVeraHumana95Bold", 40);
        equalsSymbol->setPosition(CCPointMake(xOffset-75, yOffset-5));
        equalsSymbol->setColor(ccc3(76,54,12));
        livesLayer->addChild(equalsSymbol,14);
        
        //detail value label
        char detailLabelNumber[10];
        sprintf(detailLabelNumber, "%s",getMDetailsDict->valueForKey(aGetDetailsDict->getCString())->getCString());
        CCLabelTTF *detailNumberLabel=CCLabelTTF::create(detailLabelNumber, "LMVeraHumana95Bold", 30);
        detailNumberLabel->setPosition(CCPointMake(xOffset+25, yOffset-3));
        detailNumberLabel->setColor(ccc3(113,80,57));
        livesLayer->addChild(detailNumberLabel,14);
        
        // Get menu
        CCSprite *normalSprite=CCSprite::createWithSpriteFrameName("buy_btn.png");
        CCSprite *selectedSprite=CCSprite::createWithSpriteFrameName("buy_btn_hvr.png");
        CCMenuItemSprite *buyMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(LMStoreLayer::purchaseIAP));
        buyMenuItem->setTag(buyButtonTag);
        buyMenuItem->setPosition(CCPointMake(xOffset+225, yOffset));
        
        // Button menu
        CCMenu *topMenu=CCMenu::create(buyMenuItem,NULL);
        livesLayer->addChild(topMenu,14);
        topMenu->setPosition(CCPointMake(0, 0));
        
        //incerementing y value
        yOffset=yOffset-73;
        
        buyButtonTag ++;
        
    }
    
}


void LMStoreLayer::loadNotEnoughCredit()
{
    //Remove other layers
    bgLayer->removeAllChildrenWithCleanup(1);
    livesLayer->removeAllChildrenWithCleanup(1);
        
    float width=CCDirector::sharedDirector()->getWinSize().width;
    float height=CCDirector::sharedDirector()->getWinSize().height;
    
    CCLabelTTF *topLabel=CCLabelTTF::create("Not Enough Credit", "LMVeraHumana95Bold", 45);
    topLabel->setPosition(CCPointMake(width/2, height-160));
    topLabel->setColor(ccc3(56, 6, 2));
    livesLayer->addChild(topLabel,14);
    
    CCLabelTTF *topSubLabel=CCLabelTTF::create("Sorry you dont't have enough        to make this\n trade", "LMVeraHumana95Bold", 25);
    topSubLabel->setPosition(CCPointMake(width/2, height-218));
    livesLayer->addChild(topSubLabel,20);
    topSubLabel->setColor(ccc3(183,71,13));
    
    CCSprite *smallMIcon=CCSprite::createWithSpriteFrameName("m_icon_orange.png");
    smallMIcon->setPosition(CCPointMake(340, 43));
    topSubLabel->addChild(smallMIcon,14);

    
    //not_enough_credit_colm column image
    CCSprite *notEnoughColm=CCSprite::createWithSpriteFrameName("not_enough_credit_colm.png");
    notEnoughColm->setPosition(CCPointMake(470, 350));
    livesLayer->addChild(notEnoughColm,20);
    
    CCLabelTTF *notEnoughColmSubLabel=CCLabelTTF::create("Please get more Monster Gold\n to continue ", "LMVeraHumana95Bold", 26);
    notEnoughColmSubLabel->setPosition(CCPointMake(545, 225));
    notEnoughColm->addChild(notEnoughColmSubLabel,20);
    notEnoughColmSubLabel->setColor(ccc3(132, 81, 23));
    
    //store icon in column
    CCSprite *storeIcon=CCSprite::createWithSpriteFrameName("store_icon_2.png");
    storeIcon->setPosition(CCPointMake(390, 290));
    notEnoughColm->addChild(storeIcon,14);
    
    //buttons
    //back Button
    CCSprite *normalSprite=CCSprite::createWithSpriteFrameName("back_btn1.png");
    CCSprite *selectedSprite=CCSprite::createWithSpriteFrameName("back_btn_hvr1.png");
    CCMenuItemSprite *backMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(LMStoreLayer::action));
    backMenuItem->setTag(5);
    backMenuItem->setPosition(CCPointMake(365, 120));
    
    //getM Button
    normalSprite=CCSprite::createWithSpriteFrameName("getM_btn_hvr.png");
    selectedSprite=CCSprite::createWithSpriteFrameName("getM_btn_hvr-04.png");
    CCMenuItemSprite *getMMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(LMStoreLayer::action));
    getMMenuItem->setTag(8);
    getMMenuItem->setPosition(CCPointMake(635, 120));
    
    //button Menu
    CCMenu *bottomButtonsMenu=CCMenu::create(backMenuItem,getMMenuItem,NULL);
    livesLayer->addChild(bottomButtonsMenu,20);
    bottomButtonsMenu->setPosition(CCPointMake(0, 0));
    
}

#pragma mark - Map
void LMStoreLayer::loadWorldMapData()
{
    mapMenuitem->selected();
    getMenuItem->unselected();
    relicsMenuItem->unselected();
    CCDictionary *mapsDict = (CCDictionary *)this->allStoreDataDict->valueForKey("Maps");
    
    //Get the list of Lives from the LivesDict
    CCArray *mapsListArr = (CCArray *)mapsDict->valueForKey("MapsList");
    
    CCDictionary *mapsDetailsDict = (CCDictionary *)mapsDict->valueForKey("MapsDetails");
    
    //lives top label
    CCLabelTTF *topLabel=CCLabelTTF::create("Trade       for Worlds", "LMVeraHumana95Bold", 25);
    topLabel->setPosition(CCPointMake(345, 450));
    topLabel->setColor(ccc3(236, 213, 139));
    livesLayer->addChild(topLabel,14);
    
    CCSprite *smallMIcon=CCSprite::createWithSpriteFrameName("m_icon_small.png");
    smallMIcon->setPosition(CCPointMake(75, 15));
    topLabel->addChild(smallMIcon,14);
    
    //Add restore Btn to restore Purchases
    // Get menu
    CCSprite *normalSprite=CCSprite::createWithSpriteFrameName("restore_btn.png");
    CCSprite *selectedSprite=CCSprite::createWithSpriteFrameName("restore_btn_hvr.png");
    
    CCMenuItemSprite *buyMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(LMStoreLayer::restorePurchases));
    buyMenuItem->setPosition(CCPointMake(775,450));
    
    // Button menu
    CCMenu *restorePurchaseMenu = CCMenu::create(buyMenuItem,NULL);
    livesLayer->addChild(restorePurchaseMenu,20);
    restorePurchaseMenu->setPosition(CCPointMake(0, 0));

    CCObject *aMapsListArrDetailsObj = NULL;
    float xOffset = 515;
    float yOffset = 386;
    
    int buyButtonTag = kGetMapsButtonTag;
    
    CCARRAY_FOREACH(mapsListArr, aMapsListArrDetailsObj)
    {
        CCString *aMapsDetailsDict = (CCString *)aMapsListArrDetailsObj;
        
        //store column
        CCSprite *storeColumn = CCSprite::createWithSpriteFrameName("store_colm.png");
        storeColumn->setPosition(CCPointMake(xOffset, yOffset));
        storeColumn->setScaleY(0.9);
        storeColumn->setScaleX(1.07);
        livesLayer->addChild(storeColumn,14);
        
        
        //maps icon
        CCSprite *mapsIcon = CCSprite::createWithSpriteFrameName("map_icon.png");
        mapsIcon->setPosition(CCPointMake(xOffset-285, yOffset));
        livesLayer->addChild(mapsIcon,14);
        
        //lives label
        char mapNumber[5];
        sprintf(mapNumber, "%s",aMapsDetailsDict->getCString());
        CCLabelTTF *mapNumberLabel = CCLabelTTF::create(mapNumber, "LMVeraHumana95Bold", 22, CCSizeMake(0, 0),kCCTextAlignmentLeft);//create(mapNumber, "LMVeraHumana95Bold", 22);
        mapNumberLabel->setPosition(CCPointMake(xOffset-130, yOffset));
        mapNumberLabel->setColor(ccc3(138,108,24));
        livesLayer->addChild(mapNumberLabel,14);
        
        
        //equal symbol
        CCLabelTTF *equalsSymbol = CCLabelTTF::create("=", "LMVeraHumana95Bold", 40);
        equalsSymbol->setPosition(CCPointMake(xOffset+10, yOffset-5));
        equalsSymbol->setColor(ccc3(138,108,24));
        livesLayer->addChild(equalsSymbol,14);
        
        //storeIcon2
        CCSprite *storeIcon2=CCSprite::createWithSpriteFrameName("store_icon_2.png");
        storeIcon2->setPosition(CCPointMake(xOffset+60, yOffset));
        livesLayer->addChild(storeIcon2,14);
        
        //m_icon
        CCSprite *mIcon=CCSprite::createWithSpriteFrameName("m_icon.png");
        mIcon->setPosition(CCPointMake(xOffset+115, yOffset));
        livesLayer->addChild(mIcon,14);

        
        //mlabel nummer
        char mlabelNumber[10];
        sprintf(mlabelNumber, "%s",mapsDetailsDict->valueForKey(aMapsDetailsDict->getCString())->getCString());
        
        CCLabelTTF *mLivesLabel=CCLabelTTF::create(mlabelNumber, "LMVeraHumana95Bold", 30);
        mLivesLabel->setPosition(CCPointMake(xOffset+160, yOffset-3));
        mLivesLabel->setColor(ccc3(76,54,12));
        livesLayer->addChild(mLivesLabel,14);
        
                
        // Get menu
        CCSprite *normalSprite=CCSprite::createWithSpriteFrameName("buy_btn.png");
        CCSprite *selectedSprite=CCSprite::createWithSpriteFrameName("buy_btn_hvr.png");
        CCSprite *disabledSprite=CCSprite::createWithSpriteFrameName("buy_btn_dsble.png");
       
        CCMenuItemSprite *buyMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite,disabledSprite, this, menu_selector(LMStoreLayer::purchaseMaps));
        buyMenuItem->setTag(buyButtonTag);
        buyMenuItem->setPosition(CCPointMake(xOffset+260, yOffset));
        
        //Check Whether its already purchased
        bool isProductPurchased = this->checkIsProductPurchased(buyButtonTag);
        if (isProductPurchased) {
            buyMenuItem->setEnabled(false);
        }
        
        // Button menu
        CCMenu *topMenu = CCMenu::create(buyMenuItem,NULL);
        livesLayer->addChild(topMenu,14);
        topMenu->setTag(kMapsMenuTag);
        topMenu->setPosition(CCPointMake(0, 0));
        
        //increment y value
        yOffset=yOffset-64;
        
        buyButtonTag ++;
    }
}

void LMStoreLayer::purchaseMaps(CCMenuItemImage *sender)
{
    if (this->canPressButtons == false) {
        return;
    }
    
    int senderTag = sender->getTag();
    
    //Handle IAP
    const char *productName;

    switch (senderTag) {
        case kGetMapsButtonTag:
        {
            this->isPurchasingMaps = true;
            productName = "com.icrglabs.LostMonsterTestIAP.world4";
        }
            break;
            
        case kGetMapsButtonTag+1:
        {
            this->isPurchasingMaps = true;
            productName = "com.icrglabs.LostMonsterTestIAP.world5";
        }
            break;
            
        case kGetMapsButtonTag+2:
        {
            this->isPurchasingMaps = true;
            productName = "com.icrglabs.LostMonsterTestIAP.world6";
        }
            break;
            
        case kGetMapsButtonTag+3:
        {
            this->isPurchasingMaps = true;
            productName = "com.icrglabs.LostMonsterTestIAP.world7";
        }
            break;
            
        case kGetMapsButtonTag+4:
        {
            this->isPurchasingMaps = true;
            productName = "com.icrglabs.LostMonsterTestIAP.allWorld";
        }
            break;
            
        default:
            break;
    }
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    LMObjectiveCCalls::purchaseIAP(productName);
#else
    
#endif
    this->addPopUpScreenBeforeBuy();
}

void LMStoreLayer::reloadMapsData()
{
    //Map Details
    livesLayer->removeAllChildrenWithCleanup(true);
    mapMenuitem->selected();
    getMenuItem->unselected();
    relicsMenuItem->unselected();
    this->loadWorldMapData();
}

void LMStoreLayer::restorePurchases(CCMenuItemImage *sender)
{
    if (this->canPressButtons == false) {
        return;
    }

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    LMObjectiveCCalls::restorePurchases();
#else
    
#endif
    
    this->addPopUpScreenBeforeBuy();
}


#pragma mark - IAP

void LMStoreLayer::purchaseIAP(CCMenuItemImage *sender)
{
    if (this->canPressButtons == false) {
        return;
    }
    
    int senderTag = sender->getTag();
    const char *productName;

    //Handle IAP
    
    switch (senderTag) {
        case kGetMButtonTag:
        {
            productName = "com.icrglabs.LostMonsterTestIAP.buy50M";
            this->purchasedMoneyCount = 50;
        }
           break;
            
        case kGetMButtonTag+1:
        {
            productName = "com.icrglabs.LostMonsterTestIAP.buy115M";
            this->purchasedMoneyCount = 115;

        }
            break;
            
        case kGetMButtonTag+2:
        {
            productName = "com.icrglabs.LostMonsterTestIAP.buy240M";
            this->purchasedMoneyCount = 240;

        }
            break;
            
        case kGetMButtonTag+3:
        {
            productName = "com.icrglabs.LostMonsterTestIAP.buy650M";
            this->purchasedMoneyCount = 650;

        }
            break;
            
        default:
            break;
    }
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    LMObjectiveCCalls::purchaseIAP(productName);
#else
    
#endif
    this->addPopUpScreenBeforeBuy();
}

//Purchase successfull so add the money to database !!!
//Money is stored in purchasedMoneyCount variable
//If it is Maps Purchase the Update the world Unlock things
void LMStoreLayer::purchaseSuccesfull(CCObject* obj)
{
    int state = (int)obj;

    if (state == 3) {
        this->updatePopUPBg(state);
        this->reloadMapsData();
        return;
    }
    
    if (this->purchasedMoneyCount != 0) //Coins Purchase
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        LMObjectiveCCalls::addMoneyToDatabaseWithMoney(this->purchasedMoneyCount);
#else
        
#endif
    }
 
    if (this->purchasedMoneyCount!=0) {
        this->updateMoneyCountInView();
    }
    if(this->isPurchasingMaps)
    {
        this->isPurchasingMaps = false;
        this->reloadMapsData();
    }
    this->updatePopUPBg(1);
    this->purchasedMoneyCount = 0;
}

void LMStoreLayer::purchaseFailed(CCObject* obj)
{
    int state = (int)obj;
    this->updatePopUPBg(state);
}


bool LMStoreLayer::checkIsProductPurchased(int inProductIndex)
{
    bool isPurchased = false;
    const char *productName;
    if (inProductIndex == kGetMapsButtonTag) {
        productName = "com.icrglabs.LostMonsterTestIAP.world4";
    }
    else if (inProductIndex == kGetMapsButtonTag+1) {
        productName = "com.icrglabs.LostMonsterTestIAP.world5";
    }
    else if (inProductIndex == kGetMapsButtonTag+2) {
        productName = "com.icrglabs.LostMonsterTestIAP.world6";
    }
    else if (inProductIndex == kGetMapsButtonTag+3) {
        productName = "com.icrglabs.LostMonsterTestIAP.world7";
    }
    else if (inProductIndex == kGetMapsButtonTag+4) {
        productName = "com.icrglabs.LostMonsterTestIAP.allWorld";
    }
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    isPurchased = LMObjectiveCCalls::checkIsProductPurchased(productName);
#else
    
#endif

    return isPurchased;
}


#pragma mark - Pop Up BG
void LMStoreLayer::addPopUpScreenBeforeBuy()
{
    this->canPressButtons = false;
     this->topMainMenu->setEnabled(false);
    LMDataManager::sharedManager()->canMainMenuStoreBtnWork = false;
    
    
    this->popupBg=CCSprite ::createWithSpriteFrameName("loading_popup.png");
    this->popupBg->setPosition(CCPointMake(512, 384));
    this->addChild(this->popupBg,50);
    
    //wait label
    CCLabelTTF *waitLabel=CCLabelTTF::create("Please Wait.....","LMVeraHumana95Bold",30);
    waitLabel->setPosition(CCPointMake(250, 190));
    waitLabel->setColor(ccc3(51, 1, 2));
    popupBg->addChild(waitLabel,51);
    
}

void LMStoreLayer::updatePopUPBg(int state)
{
    this->popupBg->removeAllChildrenWithCleanup(true);
    if (state == 1) // Success
    {
        CCLabelTTF *purchaseSuccessfulLbl=CCLabelTTF::create("Purchase Successful","LMVeraHumana95Bold",30);
        purchaseSuccessfulLbl->setPosition(CCPointMake(250, 190));
        purchaseSuccessfulLbl->setColor(ccc3(51, 1, 2));
        popupBg->addChild(purchaseSuccessfulLbl,51);

    }
    else if (state  == 2) //Failed
    {
        CCLabelTTF *purchaseFailedLbl=CCLabelTTF::create("Purchase Failed","LMVeraHumana95Bold",30);
        purchaseFailedLbl->setPosition(CCPointMake(250, 210));
        purchaseFailedLbl->setColor(ccc3(51, 1, 2));
        popupBg->addChild(purchaseFailedLbl,51);
    }
    else if (state  == 3) //Purchases Restored
    {
        CCLabelTTF *purchaseFailedLbl=CCLabelTTF::create("Purchases Restored","LMVeraHumana95Bold",30);
        purchaseFailedLbl->setPosition(CCPointMake(250, 210));
        purchaseFailedLbl->setColor(ccc3(51, 1, 2));
        popupBg->addChild(purchaseFailedLbl,51);
    }
    else if (state  == 4) //Purchases Restored Failed
    {
        CCLabelTTF *purchaseFailedLbl=CCLabelTTF::create("Purchases Restore Failed","LMVeraHumana95Bold",30);
        purchaseFailedLbl->setPosition(CCPointMake(250, 210));
        purchaseFailedLbl->setColor(ccc3(51, 1, 2));
        popupBg->addChild(purchaseFailedLbl,51);
    }    
    
    //Add Continue Button
    
    CCSprite *normalSprite=CCSprite::create("continue_bt.png");
    CCSprite *selectedSprite=CCSprite::create("continue_bt_hvr.png");

    CCMenuItemSprite *cancelMenuItem = CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(LMStoreLayer::removePopUPBg));
    cancelMenuItem->setTag(20);
    cancelMenuItem->setPosition(CCPointMake(250, 130));

    // Button menu
    CCMenu *topMenu=CCMenu::create(cancelMenuItem,NULL);
    popupBg->addChild(topMenu,52);
    topMenu->setPosition(CCPointMake(0, 0));
}

void LMStoreLayer::removePopUPBg()
{
     this->topMainMenu->setEnabled(true);
    this->popupBg->removeAllChildrenWithCleanup(true);
    this->popupBg->removeFromParentAndCleanup(true);
    
    this->canPressButtons = true;
    LMDataManager::sharedManager()->canMainMenuStoreBtnWork = true;
   
}

#pragma mark - Dealloc

LMStoreLayer::~LMStoreLayer(){
    CCLog("Dealloc in ~LMStoreLayer");
    this->allStoreDataDict->release();
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("LMStoreScene.plist");
    
    //Remove Notification Observers
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, "Purchase Succesful");
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, "Purchase Failed");
}

