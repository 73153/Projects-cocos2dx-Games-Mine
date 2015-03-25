//
//  UsercarQueryCallback.h
//  DarkCityRider
//
//  Created by Krithik on 12/10/11.
//  Copyright 2011 i-CRG Labs. All rights reserved.
//

//
//  QueryCallback.h
//  Gelly_Bean_Effect
//
//  Created by i-CRG Labs on 3/31/11.
//  Copyright 2011 i-CRG Labs. All rights reserved.
//

#import "Box2D.h"

class MouseJointQueryCallback : public b2QueryCallback {
public:
	MouseJointQueryCallback(const b2Vec2& point)
	{
		m_point = point;
		m_fixture = NULL;
        tagVal = 200;
	}
	
	bool ReportFixture(b2Fixture* fixture) 
	{
        bool inside = fixture->TestPoint(m_point);
        b2Body* body = fixture->GetBody();
        CCSprite *tempSpr = (CCSprite *)body->GetUserData();

        if (inside)
        {
            //This condition is necessary to detect only certain bodies
            if (tempSpr->getTag()==SOFTWOOD||tempSpr->getTag()==BOLTWOOD||tempSpr->getTag()==ICE)
            {
                m_fixture = fixture;
                // We are done, terminate the query.
                return true;
            }           
        }
        else
        {
            b2Body* body = fixture->GetBody();
            CCSprite *tempSpr = (CCSprite *)body->GetUserData();
            if (body->GetType() == b2_dynamicBody)
            {
                bool inside = fixture->TestPoint(m_point);
                
                if(inside)
                {
                    if (tempSpr->getTag()==SOFTWOOD||tempSpr->getTag()==BOLTWOOD||tempSpr->getTag()==ICE)
                    {
                        m_fixture = fixture;
                        
                        // We are done, terminate the query.
                        return false;
                    }
                }
            }
        }        
		return true;
	}
	
	b2Vec2 m_point;
	b2Fixture* m_fixture;
    
    int tagVal;
};