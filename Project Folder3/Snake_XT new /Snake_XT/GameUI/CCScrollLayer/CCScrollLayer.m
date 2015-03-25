//
//  CCScrollLayer.m
//  CCExtensions
//
//  Created by Jerrod Putman on 7/29/11.
//  Copyright 2011 Tiny Tim Games. All rights reserved.
//
//  Portions created by Sangwoo Im.
//
//	Permission is hereby granted, free of charge, to any person obtaining a copy
//	of this software and associated documentation files (the "Software"), to deal
//	in the Software without restriction, including without limitation the rights
//	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//	copies of the Software, and to permit persons to whom the Software is
//	furnished to do so, subject to the following conditions:
//
//	The above copyright notice and this permission notice shall be included in
//	all copies or substantial portions of the Software.
//
//	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//	THE SOFTWARE.
//

#import "CCScrollLayer.h"


#if __has_feature(objc_arc) == 0
#warning This code was designed to run under ARC. Without it, you will experience lots of memory leaks.
#endif


#define SCROLL_DECEL_DIST			1.0f
#define BOUNCE_DURATION				0.25f


const float CCScrollLayerDecelerationRateNormal = 0.95f;
const float CCScrollLayerDecelerationRateFast = 0.85f;



@interface CCScrollLayer ()

@property (nonatomic, strong) CCLayer *container;

- (void)scrollLayerDidScroll;

@end


#pragma mark -


@implementation CCScrollLayer
{
	CGPoint lastGesturePoint;
    CGPoint scrollDistance;
	
	CCGestureRecognizer *ccPanGestureRecognizer;
	CCGestureRecognizer *ccPinchGestureRecognizer;
}

@synthesize scrollEnabled;
@synthesize direction;
@synthesize clipToBounds;
@synthesize viewSize;
@synthesize bounces;
@synthesize alwaysBounceHorizontal;
@synthesize alwaysBounceVertical;
@synthesize decelerationRate;
@synthesize decelerating;
@synthesize bouncesZoom;
@synthesize minimumZoom;
@synthesize maximumZoom;
@synthesize zoomBouncing;
@synthesize delegate;
@synthesize container;

@dynamic contentOffset;


#pragma mark - Private

- (CGPoint)maxContainerOffset
{
    return ccp(0.0f, 0.0f);
}


- (CGPoint)minContainerOffset
{
    return ccp(viewSize.width - self.contentSize.width, viewSize.height - self.contentSize.height);
}


- (void)relocateContainer:(BOOL)animated
{
    CGPoint oldPoint, min, max;
    CGFloat newX, newY;
    
    min = [self minContainerOffset];
    max = [self maxContainerOffset];
    
    oldPoint = container.position;
    newX     = MIN(oldPoint.x, max.x);
    newX     = MAX(newX, min.x);
    newY     = MIN(oldPoint.y, max.y);
    newY     = MAX(newY, min.y);
    if (newY != oldPoint.y || newX != oldPoint.x)
	{
        [self setContentOffset:ccp(newX, newY) animated:animated];
    }
}


- (void)decelerateScrolling:(ccTime)dt
{
    if(self.dragging)
	{
		decelerating = NO;
        [self unschedule:@selector(decelerateScrolling:)];
        return;
    }
	
	decelerating = YES;
    
    CGPoint maxInset, minInset;
    
    container.position = ccpAdd(container.position, scrollDistance);

    maxInset = [self maxContainerOffset];
    minInset = [self minContainerOffset];
    
	if(container.position.x >= minInset.x
	   && container.position.y >= minInset.y
	   && container.position.x < maxInset.x
	   && container.position.y < maxInset.y)
		scrollDistance     = ccpMult(scrollDistance, decelerationRate);
	else
		scrollDistance		= ccpMult(scrollDistance, decelerationRate / 2.0f);
	
    [self scrollLayerDidScroll];
    
    if (ccpLengthSQ(scrollDistance) <= SCROLL_DECEL_DIST * SCROLL_DECEL_DIST)
	{
        [self unschedule:@selector(decelerateScrolling:)];
		[self setContentOffset:container.position animated:YES];
    }
}


- (void)scrollLayerDidScroll
{
	if(delegate != nil
	   && [delegate respondsToSelector:@selector(scrollLayerDidScroll:)])
		[delegate scrollLayerDidScroll:self];
}


- (void)performedAnimatedScroll:(ccTime)dt
{
    if(self.dragging
	   || self.zooming)
	{
		[self unschedule:@selector(performedAnimatedScroll:)];
        return;
    }
	
    [self scrollLayerDidScroll];
}


#pragma mark - Properties

- (void)setScrollEnabled:(BOOL)se
{
	ccPanGestureRecognizer.gestureRecognizer.enabled = se;
	ccPinchGestureRecognizer.gestureRecognizer.enabled = se;
}


- (BOOL)dragging
{
	return (ccPanGestureRecognizer.gestureRecognizer.state == UIGestureRecognizerStateChanged);
}


- (BOOL)zooming
{
	return (ccPinchGestureRecognizer.gestureRecognizer.state == UIGestureRecognizerStateChanged);
}


- (void)setContentOffset:(CGPoint)offset
{
    [self setContentOffset:offset animated:NO];
}


- (CGPoint)contentOffset
{
    return container.position;
}


- (void)setZoomScale:(float)zoomScale
{
	[self setZoomScale:zoomScale animated:NO];
}


- (float)zoomScale
{
	return container.scale;
}


- (UIPanGestureRecognizer *)panGestureRecognizer
{
	return (UIPanGestureRecognizer *)ccPanGestureRecognizer.gestureRecognizer;
}


- (UIPinchGestureRecognizer *)pinchGestureRecognizer
{
	return (UIPinchGestureRecognizer *)ccPinchGestureRecognizer.gestureRecognizer;
}


#pragma mark - Creating a scroll view

+ (id)scrollLayerWithViewSize:(CGSize)size
{
    return [[CCScrollLayer alloc] initWithViewSize:size];
}


- (id)initWithViewSize:(CGSize)size
{
    if ((self = [super init]))
	{
        viewSize = size;
        bounces = YES;
		decelerationRate = CCScrollLayerDecelerationRateNormal;
        clipToBounds = YES;
        direction = CCScrollLayerDirectionBoth;
		minimumZoom = 1.0f;
		maximumZoom = 1.0f;

        container = [CCLayer node];
        container.contentSize = CGSizeZero;
        container.position = ccp(0.0f, 0.0f);
        [self addChild:container];
    }
	
    return self;
}


- (id)init
{
    self = [self initWithViewSize:[[CCDirector sharedDirector] winSize]];
	
	return self;
}


#pragma mark - Scene presentation

- (void)onEnterTransitionDidFinish
{
	UIPanGestureRecognizer *pan = [[UIPanGestureRecognizer alloc] init];
	ccPanGestureRecognizer = [CCGestureRecognizer recognizerWithRecognizer:pan target:self action:@selector(handlePanGesture:)];
	[self addGestureRecognizer:ccPanGestureRecognizer];
	
	UIPinchGestureRecognizer *pinch = [[UIPinchGestureRecognizer alloc] init];
	ccPinchGestureRecognizer = [CCGestureRecognizer recognizerWithRecognizer:pinch target:self action:@selector(handlePinchGesture:)];
	[self addGestureRecognizer:ccPinchGestureRecognizer];	
}


- (void)onExit
{
	[self removeGestureRecognizer:ccPanGestureRecognizer];
	[self removeGestureRecognizer:ccPinchGestureRecognizer];
}


#pragma mark - Managing scrolling

- (void)scrollRectToVisible:(CGRect)rect animated:(BOOL)aniamted
{
	CGPoint centerOfRect = CGPointMake(rect.origin.x + rect.size.width / 2 - viewSize.width / 2, rect.origin.y + rect.size.height / 2 - viewSize.height / 2);
	[self setContentOffset:centerOfRect animated:YES];
}


#pragma mark - Panning and zooming

- (void)setContentOffset:(CGPoint)offset animated:(BOOL)animated
{
    CGPoint oldPoint, min, max;
    CGFloat newX, newY;
    
    min = [self minContainerOffset];
    max = [self maxContainerOffset];
    
    oldPoint = container.position;
    newX     = MIN(offset.x, max.x);
    newX     = MAX(newX, min.x);
    newY     = MIN(offset.y, max.y);
    newY     = MAX(newY, min.y);

    if (newY == oldPoint.y && newX == oldPoint.x)
        return;

    if (animated)	//animate scrolling
	{
		[container runAction:
		 [CCSequence actions:
		  [CCEaseSineInOut actionWithAction:[CCMoveTo actionWithDuration:BOUNCE_DURATION position:CGPointMake(newX, newY)]],
		  [CCCallBlock actionWithBlock:^{
			 [self unschedule:@selector(performedAnimatedScroll:)];
			 
			 if(decelerating)
			 {
				 decelerating = NO;
				 
				 if(delegate != nil
					&& [delegate respondsToSelector:@selector(scrollLayerDidEndDecelerating:)])
					 [delegate scrollLayerDidEndDecelerating:self];
			 }
			 else
			 {
				 if(delegate != nil
					&& [delegate respondsToSelector:@selector(scrollLayerDidEndScrollingAnimation:)])
					 [delegate scrollLayerDidEndScrollingAnimation:self];
			 }
		 }],
		  nil]];
    }
	else			//set the container position directly
	{
        container.position = CGPointMake(newX, newY);
        [self scrollLayerDidScroll];
    }
}


- (void)setZoomScale:(CGFloat)zoom animated:(BOOL)animated
{
	zoom = MIN(zoom, maximumZoom);
	zoom = MAX(zoom, minimumZoom);

	CGSize oldSize = [self contentSize];

	if(animated)
	{
		if(zoomBouncing == NO
		   && delegate != nil
		   && [delegate respondsToSelector:@selector(scrollLayerDidEndZooming:atScale:)])
			[delegate scrollLayerDidEndZooming:self atScale:zoom];

		[container runAction:
		 [CCSequence actions:
		  [CCEaseSineInOut actionWithAction:[CCScaleTo actionWithDuration:BOUNCE_DURATION scale:zoom]],
		  [CCCallBlock actionWithBlock:^{ 
			 if(zoomBouncing
				&& delegate != nil
				&& [delegate respondsToSelector:@selector(scrollLayerDidEndZooming:atScale:)])
				 [delegate scrollLayerDidEndZooming:self atScale:zoom];

			 zoomBouncing = NO;
		 }],
		  nil]];
	}
	else
	{
		container.scale = zoom;
	}

	CGSize newSize = CGSizeMake(zoom * container.contentSize.width, zoom * container.contentSize.height);
	CGSize deltaSize = CGSizeMake(oldSize.width - newSize.width, oldSize.height - newSize.height);
	CGPoint pointPercent = CGPointMake(lastGesturePoint.x / container.contentSize.width, lastGesturePoint.y / container.contentSize.height);
	container.position = ccpAdd(container.position, CGPointMake(deltaSize.width * pointPercent.x, deltaSize.height * pointPercent.y));
	[self setContentOffset:container.position animated:YES];
}


#pragma mark - Gesture recognizer actions

- (void)handlePanGesture:(UIPanGestureRecognizer *)gestureRecognizer
{
	switch(gestureRecognizer.state)
	{
		case UIGestureRecognizerStateBegan:
		{
			lastGesturePoint = [gestureRecognizer locationInView:gestureRecognizer.view];
			scrollDistance = ccp(0.0f, 0.0f);
			
			if(delegate != nil
			   && [delegate respondsToSelector:@selector(scrollLayerWillBeginDragging:)])
				[delegate scrollLayerWillBeginDragging:self];
			
			break;
		}
			
		case UIGestureRecognizerStateChanged:
		{
			CGPoint newPoint = [gestureRecognizer locationInView:gestureRecognizer.view];
			CGPoint moveDistance = ccpSub(newPoint, lastGesturePoint);
			lastGesturePoint = newPoint;
			
			moveDistance.y *= -1;
            CGPoint tempPosition = ccpAdd(container.position, moveDistance);
            
            CGPoint maxInset = [self maxContainerOffset];
            CGPoint minInset = [self minContainerOffset];
            
			if(tempPosition.x < minInset.x
			   || tempPosition.x >= maxInset.x)
				moveDistance.x = (bounces && (self.contentSize.width > viewSize.width || alwaysBounceHorizontal)) ? moveDistance.x * 0.25f : 0.0f;
			if(tempPosition.y < minInset.y
			   || tempPosition.y >= maxInset.y)
				moveDistance.y = (bounces && (self.contentSize.width > viewSize.width || alwaysBounceVertical)) ? moveDistance.y * 0.25f : 0.0f;
			
			container.position = ccpAdd(container.position, moveDistance);
			scrollDistance = moveDistance;
			
			[self scrollLayerDidScroll];
			
			break;
		}
			
		default:
		{
			BOOL willDecelerate = NO;
			if(ccpLengthSQ(scrollDistance) >= SCROLL_DECEL_DIST * SCROLL_DECEL_DIST)
			{
				[self schedule:@selector(decelerateScrolling:)];
				willDecelerate = YES;
				
				if(delegate != nil
				   && [delegate respondsToSelector:@selector(scrollLayerWillBeginDecelerating:)])
					[delegate scrollLayerWillBeginDecelerating:self];
			}
			else
			{
				[self setContentOffset:container.position animated:YES];
			}
			
			if(delegate != nil
			   && [delegate respondsToSelector:@selector(scrollLayerDidEndDragging:willDecelerate::)])
				[delegate scrollLayerDidEndDragging:self willDecelerate:YES];
			
			break;
		}
	}
}


- (void)handlePinchGesture:(UIPinchGestureRecognizer *)gestureRecognizer
{
	switch(gestureRecognizer.state)
	{
		case UIGestureRecognizerStateBegan:
		{
			gestureRecognizer.scale = container.scale;
			
			if(delegate != nil
			   && [delegate respondsToSelector:@selector(scrollLayerWillBeginZooming:)])
				[delegate scrollLayerWillBeginZooming:self];
			
			break;
		}
			
		case UIGestureRecognizerStateChanged:
		{
			CGFloat zoomDistance = gestureRecognizer.scale;
			
			if(gestureRecognizer.scale > maximumZoom)
			{
				zoomDistance = (bouncesZoom) ? maximumZoom + ((gestureRecognizer.scale - maximumZoom) * 0.25f) : maximumZoom;
			}
			else if(gestureRecognizer.scale < minimumZoom)
			{
				zoomDistance = (bouncesZoom) ? minimumZoom - ((minimumZoom - gestureRecognizer.scale) * 0.25f) : minimumZoom;
			}
			
			lastGesturePoint = [container convertToNodeSpace:[[CCDirector sharedDirector] convertToGL:[gestureRecognizer locationInView:gestureRecognizer.view]]];
			CGSize oldSize = [self contentSize];
			
			container.scale = zoomDistance;
			
			CGSize newSize = [self contentSize];
			CGSize deltaSize = CGSizeMake(oldSize.width - newSize.width, oldSize.height - newSize.height);
			CGPoint pointPercent = CGPointMake(lastGesturePoint.x / container.contentSize.width, lastGesturePoint.y / container.contentSize.height);
			container.position = ccpAdd(container.position, CGPointMake(deltaSize.width * pointPercent.x, deltaSize.height * pointPercent.y));
			
			if(delegate != nil
			   && [delegate respondsToSelector:@selector(scrollLayerDidZoom:)])
				[delegate scrollLayerDidZoom:self];
			
			break;
		}
			
		default:
		{
			zoomBouncing = YES;
			[self setZoomScale:container.scale animated:YES];
			
			break;
		}
	}
}


#pragma mark - CCNode overrides

- (CGSize)contentSize
{
    return CGSizeMake(container.scaleX * container.contentSize.width, container.scaleY * container.contentSize.height); 
}


- (void)setContentSize:(CGSize)size
{
    container.contentSize = size;
}


- (void)addChild:(CCNode *)node  z:(int)z tag:(int)aTag
{
	// Make sure all children go to the container.
    node.isRelativeAnchorPoint = YES;
    node.anchorPoint = ccp(0.0f, 0.0f);
	
    if(container != node)
	{
        [container addChild:node z:z tag:aTag];
    }
	else
	{
        [super addChild:node z:z tag:aTag];
    }
}


- (void)beforeDraw
{
    if(clipToBounds)
	{
		// Clip this view so that outside of the visible bounds can be hidden.
        GLfloat planeTop[]    = {0.0f, -1.0f, 0.0f, viewSize.height};
        GLfloat planeBottom[] = {0.0f, 1.0f, 0.0f, 0.0f};
        GLfloat planeLeft[]   = {1.0f, 0.0f, 0.0f, 0.0f};
        GLfloat planeRight[]  = {-1.0f, 0.0f, 0.0f, viewSize.width};
        
        glClipPlanef(GL_CLIP_PLANE0, planeTop);
        glClipPlanef(GL_CLIP_PLANE1, planeBottom);
        glClipPlanef(GL_CLIP_PLANE2, planeLeft);
        glClipPlanef(GL_CLIP_PLANE3, planeRight);
        glEnable(GL_CLIP_PLANE0);
        glEnable(GL_CLIP_PLANE1);
        glEnable(GL_CLIP_PLANE2);
        glEnable(GL_CLIP_PLANE3);
    }
}


- (void)afterDraw
{
    if(clipToBounds)
	{
		// Retract what's done in beforeDraw so that there's no side effect to other nodes.
        glDisable(GL_CLIP_PLANE0);
        glDisable(GL_CLIP_PLANE1);
        glDisable(GL_CLIP_PLANE2);
        glDisable(GL_CLIP_PLANE3);
    }
}


// Override for the base CCNode visit method.
- (void)visit
{
	if(!visible_)
		return;
	
	glPushMatrix();
	
	if(grid_
	   && grid_.active)
	{
		[grid_ beforeDraw];
		[self transformAncestors];
	}
	
	[self transform];
	
	[self beforeDraw];
	
	for(CCNode *child in children_)
	{
		if(child.zOrder < 0)
			[child visit];
		else
			break;
	}
	
	[self draw];
	
	for(CCNode * child in children_)
	{
		if(child.zOrder >= 0)
			[child visit];
	}
	
	[self afterDraw];
	
	if(grid_
	   && grid_.active)
		[grid_ afterDraw:self];
	
	glPopMatrix();
}


@end
