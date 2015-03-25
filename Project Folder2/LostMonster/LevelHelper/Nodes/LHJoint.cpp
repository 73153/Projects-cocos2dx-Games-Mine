//  This file was generated by LevelHelper
//  http://www.levelhelper.org
//
//  LevelHelperLoader.mm
//  Created by Bogdan Vladu
//  Copyright 2011 Bogdan Vladu. All rights reserved.
////////////////////////////////////////////////////////////////////////////////
//
//  This software is provided 'as-is', without any express or implied
//  warranty.  In no event will the authors be held liable for any damages
//  arising from the use of this software.
//  Permission is granted to anyone to use this software for any purpose,
//  including commercial applications, and to alter it and redistribute it
//  freely, subject to the following restrictions:
//  The origin of this software must not be misrepresented; you must not
//  claim that you wrote the original software. If you use this software
//  in a product, an acknowledgment in the product documentation would be
//  appreciated but is not required.
//  Altered source versions must be plainly marked as such, and must not be
//  misrepresented as being the original software.
//  This notice may not be removed or altered from any source distribution.
//  By "software" the author refers to this code file and not the application 
//  that was used to generate this file.
//
////////////////////////////////////////////////////////////////////////////////
#include "LHJoint.h"
#include "LHSettings.h"
#include "../LevelHelperLoader.h"
#include "LHSprite.h"
#include "../Utilities/LHDictionary.h"
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//void LHJoint::removeJoint(LHJoint* jt){
//    if(!jt)return;
//        [jointsInLevel removeObjectForKey:[jt uniqueName]];
//}

////////////////////////////////////////////////////////////////////////////////
LHJoint::~LHJoint(){
	
//    printf("LHJoint dealloc\n");
    
    if(shouldDestroyJointOnDealloc)
        removeJointFromWorld();
}
//------------------------------------------------------------------------------
bool LHJoint::initWithDictionary(LHDictionary* dictionary, b2World* box2d, LevelHelperLoader* pLoader){
    
    if(box2d == NULL)
        return false;
    
    joint = NULL;
    shouldDestroyJointOnDealloc = true;
    uniqueName = std::string(dictionary->stringForKey("UniqueName"));
    tag = 0;
    type = LH_DISTANCE_JOINT;
    boxWorld = box2d;
    parentLoader = pLoader;
        
    createBox2dJointFromDictionary(dictionary);
    
    return true;
}
//------------------------------------------------------------------------------
LHJoint::LHJoint(){
    
}
//------------------------------------------------------------------------------
LHJoint* LHJoint::jointWithDictionary(LHDictionary* dictionary, b2World* box2d, LevelHelperLoader* pLoader){
    LHJoint *pobNode = new LHJoint();
	if (pobNode && pobNode->initWithDictionary(dictionary, box2d, pLoader))
    {
	    pobNode->autorelease();
        return pobNode;
    }
    CC_SAFE_DELETE(pobNode);
	return NULL;
}
//------------------------------------------------------------------------------
bool LHJoint::removeJointFromWorld()
{
    if(0 != joint){
        b2Body *body = joint->GetBodyA();
        
        if(0 == body){
            body = joint->GetBodyB();
            
            if(0 == body)
                return false;
        }
        b2World* _world = body->GetWorld();
        
        if(0 == _world)
            return false;
        
        _world->DestroyJoint(joint);
        return true;
	}
    return false;
}

////////////////////////////////////////////////////////////////////////////////
LHSprite* LHJoint::getSpriteA(){
    if(joint)
        return LHSprite::spriteForBody(joint->GetBodyA());
    return NULL;
}
//------------------------------------------------------------------------------
LHSprite* LHJoint::getSpriteB()
{
    if(joint)
        return LHSprite::spriteForBody(joint->GetBodyB());
    return NULL;    
}
//------------------------------------------------------------------------------
void LHJoint::removeSelf()
{
//    printf("LH JOINT REMOVE SELF %s\n", getUniqueName().c_str());
    if(parentLoader){
        if(!boxWorld->IsLocked()){
            parentLoader->removeJoint(this);
        }
        else {
//            printf("MARKING\n");
            LHSettings::sharedInstance()->markNodeForRemoval(this);
        }
    }
}
//------------------------------------------------------------------------------
void LHJoint::createBox2dJointFromDictionary(LHDictionary* dictionary)
{
    joint = 0;
    
	if(NULL == dictionary)return;
	if(boxWorld == 0)return;
    
    
    LHSprite* sprA  = parentLoader->spriteWithUniqueName(dictionary->stringForKey("ObjectA"));
    b2Body* bodyA   = sprA->getBody();
	
    LHSprite* sprB  = parentLoader->spriteWithUniqueName(dictionary->stringForKey("ObjectB"));
    b2Body* bodyB   = sprB->getBody();
	
    CCPoint sprPosA = sprA->getPosition();
    CCPoint sprPosB = sprB->getPosition();
    
//    CCSize scaleA   = sprA->getRealScale();
//    CCSize scaleB   = sprB->getRealScale();
    
    CCSize scaleA   = CCSizeMake(sprA->getScaleX(), sprA->getScaleY());//[sprA realScale];
    CCSize scaleB   = CCSizeMake(sprB->getScaleX(), sprB->getScaleY());//[sprB realScale];
   
    scaleA = LHSettings::sharedInstance()->transformedSize(scaleA, sprA->getImageFile());
    scaleB = LHSettings::sharedInstance()->transformedSize(scaleB, sprB->getImageFile());
    
//    scaleA = [[LHSettings sharedInstance] transformedSize:scaleA forImage:[sprA imageFile]];
//    scaleB = [[LHSettings sharedInstance] transformedSize:scaleB forImage:[sprB imageFile]];
    
    
	if(NULL == bodyA || NULL == bodyB ) return;
	
	CCPoint anchorA = dictionary->pointForKey("AnchorA");
	CCPoint anchorB = dictionary->pointForKey("AnchorB");
    
	bool collideConnected = dictionary->boolForKey("CollideConnected");
	
    tag     = dictionary->intForKey("Tag");
    type    = (LH_JOINT_TYPE)dictionary->intForKey("Type");
    
	b2Vec2 posA, posB;
	
    float ptm = LHSettings::sharedInstance()->lhPtmRatio();
	float convertX = LHSettings::sharedInstance()->convertRatio().x;
	float convertY = LHSettings::sharedInstance()->convertRatio().y;
    
    if(!dictionary->boolForKey("CenterOfMass"))
    {        
        posA = b2Vec2((sprPosA.x + anchorA.x*scaleA.width)/ptm, 
                      (sprPosA.y - anchorA.y*scaleA.height)/ptm);
        
        posB = b2Vec2((sprPosB.x + anchorB.x*scaleB.width)/ptm, 
                      (sprPosB.y - anchorB.y*scaleB.height)/ptm);
        
    }
    else {		
        posA = bodyA->GetWorldCenter();
        posB = bodyB->GetWorldCenter();
    }
	
	if(0 != bodyA && 0 != bodyB)
	{
		switch ((int)type)
		{
			case LH_DISTANCE_JOINT:
			{
				b2DistanceJointDef jointDef;
				
				jointDef.Initialize(bodyA, 
									bodyB, 
									posA,
									posB);
				
				jointDef.collideConnected = collideConnected;
				
				jointDef.frequencyHz    = dictionary->floatForKey("Frequency");
				jointDef.dampingRatio   = dictionary->floatForKey("Damping");
				
				if(0 != boxWorld){
					joint = (b2DistanceJoint*)boxWorld->CreateJoint(&jointDef);
				}
			}	
				break;
				
			case LH_REVOLUTE_JOINT:
			{
				b2RevoluteJointDef jointDef;
				
				jointDef.lowerAngle     = CC_DEGREES_TO_RADIANS(dictionary->floatForKey("LowerAngle"));
				jointDef.upperAngle     = CC_DEGREES_TO_RADIANS(dictionary->floatForKey("UpperAngle"));
				jointDef.motorSpeed     = dictionary->floatForKey("MotorSpeed");
				jointDef.maxMotorTorque = dictionary->floatForKey("MaxTorque");
				jointDef.enableLimit    = dictionary->boolForKey("EnableLimit");
				jointDef.enableMotor    = dictionary->boolForKey("EnableMotor");
				jointDef.collideConnected = collideConnected;    
				
				jointDef.Initialize(bodyA, bodyB, posA);
				
				if(0 != boxWorld){
					joint = (b2RevoluteJoint*)boxWorld->CreateJoint(&jointDef);
				}
			}
				break;
				
			case LH_PRISMATIC_JOINT:
			{
				b2PrismaticJointDef jointDef;
				
				// Bouncy limit
				CCPoint axisPt = dictionary->pointForKey("Axis");
				
				b2Vec2 axis(axisPt.x, axisPt.y);
				axis.Normalize();
				
				jointDef.Initialize(bodyA, bodyB, posA, axis);
				
				jointDef.motorSpeed     = dictionary->floatForKey("MotorSpeed");
				jointDef.maxMotorForce  = dictionary->floatForKey("MaxMotorForce");
				
				jointDef.lowerTranslation =  CC_DEGREES_TO_RADIANS(dictionary->floatForKey("LowerTranslation"));
				jointDef.upperTranslation = CC_DEGREES_TO_RADIANS(dictionary->floatForKey("UpperTranslation"));
				
				jointDef.enableMotor = dictionary->boolForKey("EnableMotor");
				jointDef.enableLimit = dictionary->boolForKey("EnableLimit");
				jointDef.collideConnected = collideConnected;   
                
				if(0 != boxWorld){
					joint = (b2PrismaticJoint*)boxWorld->CreateJoint(&jointDef);
				}
			}	
				break;
				
			case LH_PULLEY_JOINT:
			{
				b2PulleyJointDef jointDef;
				
				CCPoint grAnchorA = dictionary->pointForKey("GroundAnchorRelativeA");
				CCPoint grAnchorB = dictionary->pointForKey("GroundAnchorRelativeB");
				
                b2Vec2 bodyAPos = bodyA->GetPosition();
                b2Vec2 bodyBPos = bodyB->GetPosition();
                
				b2Vec2 groundAnchorA = b2Vec2(bodyAPos.x + convertX*grAnchorA.x/ptm,
                                              bodyAPos.y - convertY*grAnchorA.y/ptm);
				b2Vec2 groundAnchorB = b2Vec2(bodyBPos.x + convertX*grAnchorB.x/ptm,
                                              bodyBPos.y - convertY*grAnchorB.y/ptm);
                
				float ratio = dictionary->floatForKey("Ratio");
				jointDef.Initialize(bodyA, bodyB, groundAnchorA, groundAnchorB,
                                    posA, posB, ratio);
				jointDef.collideConnected = collideConnected;   
				
				if(0 != boxWorld){
					joint = (b2PulleyJoint*)boxWorld->CreateJoint(&jointDef);
				}
			}
				break;
				
			case LH_GEAR_JOINT:
			{
				b2GearJointDef jointDef;
				
				jointDef.bodyA = bodyB;
				jointDef.bodyB = bodyA;
				
				if(bodyA == 0)
					return;
				if(bodyB == 0)
					return;
				
                LHJoint* jointAObj  = parentLoader->jointWithUniqueName(dictionary->stringForKey("JointA"));
                b2Joint* jointA     = jointAObj->getJoint();
                
                LHJoint* jointBObj  = parentLoader->jointWithUniqueName(dictionary->stringForKey("JointB"));
                b2Joint* jointB     = jointBObj->getJoint();
                
				if(jointA == 0)
					return;
				if(jointB == 0)
					return;
				
				
				jointDef.joint1 = jointA;
				jointDef.joint2 = jointB;
				
				jointDef.ratio  = dictionary->floatForKey("Ratio");
				jointDef.collideConnected = collideConnected;
                
				if(0 != boxWorld){
					joint = (b2GearJoint*)boxWorld->CreateJoint(&jointDef);
				}
			}	
				break;
				
				
			case LH_WHEEL_JOINT: //aka line joint
			{
				b2WheelJointDef jointDef;
				
				CCPoint axisPt = dictionary->pointForKey("Axis");
				b2Vec2 axis(axisPt.x, axisPt.y);
				axis.Normalize();
				
				jointDef.motorSpeed     = dictionary->floatForKey("MotorSpeed");
				jointDef.maxMotorTorque = dictionary->floatForKey("MaxTorque");
				jointDef.enableMotor    = dictionary->floatForKey("EnableMotor");
				jointDef.frequencyHz    = dictionary->floatForKey("Frequency");
				jointDef.dampingRatio   = dictionary->floatForKey("Damping");
				
				jointDef.Initialize(bodyA, bodyB, posA, axis);
				jointDef.collideConnected = collideConnected; 
				
				if(0 != boxWorld){
					joint = (b2WheelJoint*)boxWorld->CreateJoint(&jointDef);
				}
			}
				break;				
			case LH_WELD_JOINT:
			{
				b2WeldJointDef jointDef;
				
				jointDef.frequencyHz    = dictionary->floatForKey("Frequency");
				jointDef.dampingRatio   = dictionary->floatForKey("Damping");
				
				jointDef.Initialize(bodyA, bodyB, posA);
				jointDef.collideConnected = collideConnected; 
				
				if(0 != boxWorld){
					joint = (b2WheelJoint*)boxWorld->CreateJoint(&jointDef);
				}
			}
				break;
				
			case LH_ROPE_JOINT: //NOT WORKING YET AS THE BOX2D JOINT FOR THIS TYPE IS A TEST JOINT
			{
				
				b2RopeJointDef jointDef;
				
				jointDef.localAnchorA = bodyA->GetPosition();
				jointDef.localAnchorB = bodyB->GetPosition();
				jointDef.bodyA = bodyA;
				jointDef.bodyB = bodyB;
				jointDef.maxLength = dictionary->floatForKey("MaxLength");
				jointDef.collideConnected = collideConnected; 
				
				if(0 != boxWorld){
					joint = (b2RopeJoint*)boxWorld->CreateJoint(&jointDef);
				}
			}
				break;
				
			case LH_FRICTION_JOINT:
			{
				b2FrictionJointDef jointDef;
				
				jointDef.maxForce   = dictionary->floatForKey("MaxForce");
				jointDef.maxTorque  = dictionary->floatForKey("MaxTorque");
				
				jointDef.Initialize(bodyA, bodyB, posA);
				jointDef.collideConnected = collideConnected; 
				
				if(0 != boxWorld){
					joint = (b2FrictionJoint*)boxWorld->CreateJoint(&jointDef);
				}
				
			}
				break;
				
			default:
				CCLog("Unknown joint type in LevelHelper file.");
				break;
		}
	}
        
    joint->SetUserData(this);
}
//------------------------------------------------------------------------------
bool LHJoint::isLHJoint(CCNode* obj){
    
    if( 0 != dynamic_cast<LHJoint*>(obj))
        return true;
    
    return false;
}
//------------------------------------------------------------------------------
LHJoint* LHJoint::jointFromBox2dJoint(b2Joint* jt)
{    
    if(jt == NULL) return NULL;
    
    void* lhJt = jt->GetUserData();

    if(LHJoint::isLHJoint((CCNode*)lhJt)){
        return (LHJoint*)lhJt;
    }
    
    return NULL;    
}
//------------------------------------------------------------------------------
int LHJoint::tagFromBox2dJoint(b2Joint* joint)
{
    if(0 != joint){
        LHJoint* data = (LHJoint*)joint->GetUserData();
        if(NULL != data)return data->getTag();
    }
    return -1;
}
//------------------------------------------------------------------------------
enum LH_JOINT_TYPE LHJoint::typeFromBox2dJoint(b2Joint* joint)
{
    if(0 != joint){
        LHJoint* data = (LHJoint*)joint->GetUserData();
        if(NULL != data) return data->getType();
    }
    return LH_UNKNOWN_TYPE;    
}
//------------------------------------------------------------------------------
std::string LHJoint::uniqueNameFromBox2dJoint(b2Joint* joint)
{
    if(0 != joint){
        LHJoint* data = (LHJoint*)joint->GetUserData();
        if(0 != data)return data->getUniqueName();
    }
    return NULL;
}
