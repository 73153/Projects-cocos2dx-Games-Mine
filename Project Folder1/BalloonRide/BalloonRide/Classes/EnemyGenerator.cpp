#include "EnemyGenerator.h"
#include "GameObjects/AnimatedObject.h"

USING_NS_CC;
using namespace Osp::Base;
using namespace Osp::Base::Utility;
using namespace Osp::System;

EnemyGenerator::EnemyGenerator() :
	__pLayer(NULL),
	__pEnemies(NULL),
	__winSize(),
	__enemySpeed(0)
{
}

/**
 * Set balloon properties and schedule movement update.
 * @param layer Layer that will hold sprites of generated objects.
 */
void
EnemyGenerator::init(CCLayer* layer)
{
	__pEnemies = new CCMutableArray<Enemy*>();
	__winSize = CCDirector::sharedDirector()->getWinSize();
	__pLayer = layer;
	__pLayer->addChild(this);
	__enemySpeed = 200.0f;
	Math::Srand((unsigned)time(NULL));
}

/**
 * Schedule object generation.
 */
void
EnemyGenerator::start()
{
	schedule(schedule_selector(EnemyGenerator::generate), (ccTime)0.5f);
}

/**
 * This callback will create
 */
void
EnemyGenerator::generate(ccTime dt)
{
	//create new enemy object
	Enemy* enemy = new Enemy(__enemySpeed);
	__enemySpeed += 1.0f;

	String textureFileName = "plane.png";
	AnimatedObject::AnimTag tag = AnimatedObject::ANIM_PLANE_SPRITESHEET;

	int r = Math::Rand() % 100;
	if(r > 50)
	{
		// Change enemy
		textureFileName = "twitter.png";
		tag = AnimatedObject::ANIM_TWITTER_SPRITESHEET;
	}

	enemy->init(textureFileName, __pLayer, tag);

	// Choose random starting position
	CCSize enemySize = enemy->getSize();
	r = Math::Rand() % (int)(__winSize.height - enemySize.height) + enemySize.height / 2;
	float x = __winSize.width + enemySize.width;
	float y = r;
	enemy->setPosition(ccp(x, y));

	__pEnemies->addObject(enemy);
	__pLayer->addChild(enemy);
	enemy->go();
}

CCMutableArray<Enemy*>*
EnemyGenerator::getEnemies()
{
	return __pEnemies;
}

/**
 * Remove off screen or colliding objects.
 * @param pEnemies Array of enemy objects that should be removed.
 */
void
EnemyGenerator::remove(CCMutableArray<Enemy*>* pEnemies)
{
	CCMutableArray<Enemy*>::CCMutableArrayIterator it;
	for(it = pEnemies->begin(); it != pEnemies->end(); it++)
	{
		Enemy* pEnemy = *it;
		pEnemy->destroy();
	}
	__pEnemies->removeObjectsInArray(pEnemies);
}
