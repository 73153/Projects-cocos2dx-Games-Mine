#include "Enemy.h"

USING_NS_CC;

Enemy::Enemy(float speed) :
		__speed(speed)
{
}

/**
 * This method start enemy movement action.
 */
void
Enemy::go()
{
	ccTime duration = (ccTime)(CCDirector::sharedDirector()->getWinSize().height / __speed);
	float x = -__pSprite->boundingBox().size.width - 5;
	CCFiniteTimeAction* actionMove = CCMoveTo::actionWithDuration(duration, ccp(x, __pSprite->getPosition().y));
	__pSprite->runAction(actionMove);
}
