//
//  QueryCallback.h
//  Gelly_Bean_Effect
//
//  Created by i-CRG Labs on 3/31/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//  Using the creating the mousejoints for the box2d objects

#import "Box2D.h"

class QueryCallback : public b2QueryCallback {
public:
	QueryCallback(const b2Vec2& point)
	{
		m_point = point;
		m_fixture = NULL;
	}
	
	bool ReportFixture(b2Fixture* fixture)
	{
		b2Body* body = fixture->GetBody();
		if (body->GetType() == b2_dynamicBody)
		{
			bool inside = fixture->TestPoint(m_point);
			if (inside)
			{
				m_fixture = fixture;
				
				// We are done, terminate the query.
				return false;
			}
		}
		
		// Continue the query.
		return true;
	}
	
	b2Vec2 m_point;
	b2Fixture* m_fixture;
};