#include "HelloWorldScene.h"
#include "CustomTableViewCell.h"

using namespace cocos2d;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

    
    //Add BG
    CCSprite *bgSpr = CCSprite::create("Images/background1.png");
    bgSpr->setPosition(ccp(512,384));
    this->addChild(bgSpr);
    
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    tableView = CCTableView::create(this, CCSizeMake(1004, 768));
    tableView->setDirection(kCCScrollViewDirectionHorizontal);
    tableView->setPosition(ccp(10,200));
    tableView->setDelegate(this);
    this->addChild(tableView);
    tableView->reloadData();
    
    
    // Font Item
    CCMenuItemFont* goRightMenuItem = CCMenuItemFont::create("Right", this, menu_selector(HelloWorld::goRight));
    goRightMenuItem->setPosition(CCPointMake(900, 200));
    
    
    // Font Item
    CCMenuItemFont* goLeftMenuItem = CCMenuItemFont::create("Left", this, menu_selector(HelloWorld::goLeft));
    goLeftMenuItem->setPosition(CCPointMake(200, 200));

    CCMenu* menu = CCMenu::create( goRightMenuItem, goLeftMenuItem, NULL);
    menu->setPosition(CCPointZero);
    this->addChild(menu);
       
    return true;
}

void HelloWorld::goRight()
{
    tableView->setContentOffset(CCPointMake(-300, 0),true);
}

void HelloWorld::goLeft()
{
    tableView->setContentOffset(CCPointMake(+300, 0),true);

}



void HelloWorld::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
    CCLOG("cell touched at index: %i", cell->getIdx());
    
    CCLog("tableview COntent Offset is %f %f",table->getContentOffset().x,table->getContentOffset().y);

}

CCSize HelloWorld::cellSizeForTable(CCTableView *table)
{
    return CCSizeMake(335,471);
}

CCTableViewCell* HelloWorld::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCTableViewCell *cell = table->dequeueCell();
    if (!cell) {
        cell = new CustomTableViewCell();
        cell->autorelease();
        
        CCSprite *spriteBG = CCSprite::create("Images/tileYellow.png");
        spriteBG->setAnchorPoint(CCPointZero);
        spriteBG->setPosition(ccp(0, 0));
        cell->addChild(spriteBG);

        
        CCSprite *sprite = CCSprite::create("Images/CarMainPage.png");
        //sprite->setAnchorPoint(CCPointZero);
        sprite->setScale(0.6);
        sprite->setPosition(ccp(spriteBG->getContentSize().width/2, spriteBG->getContentSize().height/2));
        spriteBG->addChild(sprite);
    }
   
    return cell;
}

unsigned int HelloWorld::numberOfCellsInTableView(CCTableView *table)
{
    return 20;
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
