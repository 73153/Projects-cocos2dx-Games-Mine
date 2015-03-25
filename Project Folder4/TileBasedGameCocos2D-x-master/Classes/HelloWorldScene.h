//
//  HelloWorldScene.h
//  TileBasedGame
//
//  Created by Clawoo on 8/17/11.
//  Copyright __MyCompanyName__ 2011. All rights reserved.
//

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::CCLayer
{
public:
    ~HelloWorld();
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();

	void setViewpointCenter(cocos2d::CCPoint point);
	
	// implement the "static node()" method manually
	LAYER_NODE_FUNC(HelloWorld);
    
    CC_SYNTHESIZE(cocos2d::CCTMXTiledMap*, _tileMap, TileMap);
    
    CC_SYNTHESIZE(cocos2d::CCTMXLayer*, _background, Background);
	
	CC_SYNTHESIZE(cocos2d::CCSprite *, _player, Player);
};

#endif // __HELLOWORLD_SCENE_H__
