/*
 * cocos2d+ext for iPhone
 *
 * Copyright (c) 2011 - Ngo Duc Hiep
 * Copyright (c) 2012 - YangLe
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include "TouchTrailLayer.h"
#include "CCBlade.h"

#define kFileStreak "streak.png"

USING_NS_CC;

TouchTrailLayer::TouchTrailLayer()
{
    setTouchEnabled(false);
}


TouchTrailLayer::~TouchTrailLayer()
{
}

  

TouchTrailLayer* TouchTrailLayer::create()
{
    TouchTrailLayer *pRet = new TouchTrailLayer();
    pRet->autorelease();
    return pRet;
}



#pragma mark - Custom Special For Lost Monster
//This function created the blade from start Point to End Point
void TouchTrailLayer::createBlade()
{
    blade = CCBlade::create(kFileStreak, 4, 50);
    addChild(blade);
    
    blade->setColor(ccc3(255,215,0));
    blade->setOpacity(150);
    blade->setDrainInterval(0.0000001);
    
    //Imp formula here getting the points on a straight line
    for (float i=0; i<=1; i=i+0.5)
    {
        float Delta_X = this->startPoint.x-this->endPoint.x;
        float Delta_Y = this->startPoint.y-this->endPoint.y;
                
        float xp = startPoint.x + i * -Delta_X;
        float yp = startPoint.y + i * -Delta_Y;

        blade->push(CCPoint(xp, yp));
    }
    blade->autoCleanup();
}





