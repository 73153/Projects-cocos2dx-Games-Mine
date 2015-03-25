//
//  CocosScene.m
//  testEraseCocos
//
//  Created by i-CRG Labs on 5/3/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "CocosScene.h"
#import "Singleton.h"
#import "Drawing_Subclasses.h"

#define PTM_RATIO 32

@implementation CocosScene


+(id) scene
{
	// 'scene' is an autorelease object.
	CCScene *scene = [CCScene node];
	
	// 'layer' is an autorelease object.
	CocosScene *layer = [CocosScene node];
	
	// add layer as a child to scene
	[scene addChild: layer];
	
	// return the scene
	return scene;
}

-(id) init
{
	// always call "super" init
	// Apple recommends to re-assign "self" with the "super" return value
	if( (self=[super init] )) 
	{
		self.isTouchEnabled = YES;
        self.isAccelerometerEnabled = YES;
        
		////NSLog(@"Init In Cocos LaYer");
		
		CGSize screend = [[CCDirector sharedDirector] winSize];	
		
		// create a render texture, this is what we're going to draw into
		target = [[CCRenderTexture renderTextureWithWidth:screend.width height:screend.height] retain];
		[target setPosition:ccp(screend.width/2, screend.height/2)];
		
		
		// It's possible to modify the RenderTexture blending function by
        [[target sprite] setBlendFunc:(ccBlendFunc) {GL_SRC_ALPHA, GL_SRC_ALPHA}];
		
		// note that the render texture is a CCNode, and contains a sprite of its texture for convience,
		// so we can just parent it to the scene like any other CCNode
		[self addChild:target z:1]; 
		
		// create a brush image to draw into the texture with
		brush = [[CCSprite spriteWithFile:@"fire.png"] retain]; 
		brush.scale = 0.8; 
		brush.color = ccc3(150, 100, 200);
		[brush setOpacity:15];
        
        // Slate Frames for Cocos
        SF1 = [CCSprite spriteWithFile:@"SlateFrame1.png"];
        SF1.position = ccp((screend.width/2)-10, screend.height/2);
        SF1.visible = FALSE;    
        SF1.rotation = 90;
        [self addChild:SF1 z:2];
        
        SF2 = [CCSprite spriteWithFile:@"SlateFrame2.png"];
        SF2.position = ccp((screend.width/2)-10, screend.height/2);
        SF2.visible = FALSE;
        SF2.rotation = 90;
        [self addChild:SF2 z:2];
        
        SF3 = [CCSprite spriteWithFile:@"SlateFrame3.png"];
        SF3.position = ccp((screend.width/2)-8, screend.height/2);
        SF3.visible = FALSE;
        SF3.rotation = 90;
        [self addChild:SF3 z:2];
        
        SF4 = [CCSprite spriteWithFile:@"SlateFrame4.png"];
        SF4.position = ccp((screend.width/2)-10, screend.height/2);
        SF4.visible = FALSE;
        SF4.rotation = 90;
        [self addChild:SF4 z:2];
        
        // Initialization of the Variables
        mBrushSize = 1;
        r = 0;
        g = 0;
        b = 0;
        selectColorCount = 0;
        mSelectedTab = 1;
        
        pallet1Color.r = 0;
        pallet1Color.g = 0;
        pallet1Color.b = 0;
        
        isTouchedOnPallete = FALSE;
        
        [Singleton sharedMySingleton]._pointsArray1 = [[NSMutableArray alloc] init];
	        
        _colorsArray = [[NSMutableArray alloc] init];
        _colorsArray4 = [[NSMutableArray alloc] init];
       
               
        //Box2d
        // Define the gravity vector.
		b2Vec2 gravity;
		gravity.Set(20.0f, 0.0f);
		
		// Do we want to let bodies sleep?
		// This will speed up the physics simulation
		bool doSleep = FALSE;
		
		// Construct a world object, which will hold and simulate the rigid bodies.
		world = new b2World(gravity, doSleep);
		
		//world->SetContinuousPhysics(true); 
		
		// Debug Draw functions
		m_debugDraw = new GLESDebugDraw( PTM_RATIO );
		world->SetDebugDraw(m_debugDraw);
        
        uint32 flags = 0;
        //flags += b2DebugDraw::e_shapeBit;
        //		flags += b2DebugDraw::e_jointBit;
        //		flags += b2DebugDraw::e_aabbBit; 
        //		flags += b2DebugDraw::e_pairBit;
        //		flags += b2DebugDraw::e_centerOfMassBit;
        m_debugDraw->SetFlags(flags);
        
        b2BodyDef groundBodyDef; 
		groundBodyDef.position.Set(0, 0); // bottom-left corner 
		
		// Call the body factory which allocates memory for the ground body
		// from a pool and creates the ground box shape (also from a pool).
		// The body is also added to the world.
		groundBody = world->CreateBody(&groundBodyDef);
        
     //   [self createBalls];
        [self createBoundary];
        
        // Creating Pallete
        mPallete = [CCSprite spriteWithFile:@"water-colour_palette_1.png"];
        mPallete.position = ccp(350,150);
        mPallete.anchorPoint = ccp(0,0);
        mPallete.rotation = 270;
        [self addChild:mPallete z:10];
        mPallete.visible = FALSE;
        
        mPalletTab1 = [CCSprite spriteWithFile:@"Pallet_Tab_1.png"];
        mPalletTab1.position = ccp(140,236);
        mPalletTab1.rotation = 270;
        mPalletTab1.scale = 1.2;
        [self addChild:mPalletTab1 z:8];
        mPalletTab1.visible = FALSE;
        
        mPalletTab2 = [CCSprite spriteWithFile:@"Pallet_Tab_2.png"];
        mPalletTab2.position = ccp(212,276);
        mPalletTab2.rotation = 270;
        mPalletTab2.scale = 1.08;
        [self addChild:mPalletTab2 z:8];
        mPalletTab2.visible = FALSE;
        
        mPalletTab1_h = [CCSprite spriteWithFile:@"Pallet_Tab_1_h.png"];
        mPalletTab1_h.position = ccp(137,234);
        mPalletTab1_h.rotation = 270;
        [self addChild:mPalletTab1_h z:11];
        mPalletTab1_h.visible = FALSE;

        mPalletTab2_h = [CCSprite spriteWithFile:@"Pallet_Tab_2_h.png"];
        mPalletTab2_h.position = ccp(206,280);
		//mPalletTab2_h.scale = 0.95;
        mPalletTab2_h.rotation = 270;
        [self addChild:mPalletTab2_h z:11];
        mPalletTab2_h.visible = FALSE;
    
        CCMenuItemImage * menuItem1 = [CCMenuItemImage itemFromNormalImage:@"white.png"
                                                             selectedImage: @"white.png"
                                                                    target:self
                                                                  selector:@selector(whiteColor)];
        menuItem1.position = ccp(40, 225);
        
        CCMenuItemImage* menuItem2 = [CCMenuItemImage itemFromNormalImage:@"blue.png"
                                                            selectedImage: @"blue.png"
                                                                   target:self
                                                                 selector:@selector(blueColor)];
        menuItem2.position = ccp(105, 235);
        
        CCMenuItemImage* menuItem3 = [CCMenuItemImage itemFromNormalImage:@"green.png"
                                                            selectedImage: @"green.png"
                                                                   target:self
                                                                 selector:@selector(greenColor)];
        menuItem3.position = ccp(150, 185);
        
        CCMenuItemImage* menuItem4 = [CCMenuItemImage itemFromNormalImage:@"yellow.png"
                                                            selectedImage: @"yellow.png"
                                                                   target:self
                                                                 selector:@selector(yellowColor)];
        menuItem4.position = ccp(160, 118);
        
        CCMenuItemImage* menuItem5 = [CCMenuItemImage itemFromNormalImage:@"red.png"
                                                            selectedImage: @"red.png"
                                                                   target:self
                                                                 selector:@selector(redColor)];
        menuItem5.position = ccp(150, 50);
        
        
        CCMenuItemImage* menuItem6 = [CCMenuItemImage itemFromNormalImage:@"black.png"
                                                            selectedImage: @"black.png"
                                                                   target:self
                                                                 selector:@selector(blackColor)];
        menuItem6.position = ccp(110, -5);
        
        CCMenuItemImage* menuItem7 = [CCMenuItemImage itemFromNormalImage:@"Clear_Button.png"
                                                            selectedImage: @"Clear_Button_h.png"
                                                                   target:self
                                                                 selector:@selector(clearPaletteColor)];
        menuItem7.position = ccp(6, 92);
        
        
        myMenu = [CCMenu menuWithItems:menuItem1, menuItem2, menuItem3, menuItem4, menuItem5, menuItem6, menuItem7,nil];
        myMenu.position = ccp(50, 50);
        [mPallete addChild:myMenu z:10];
        
    }
	return self;
}

#pragma mark Balls
-(void) createBoundary
{
    // Boundaries for the Balls
	
    CCSprite* _strip1 = [CCSprite spriteWithFile:@"Strip1.png"];
    _strip1.position = ccp(62,560);
    _strip1.anchorPoint = ccp(0,0);
    _strip1.visible = FALSE;
    [self addChild: _strip1 z:5];
    [self staticBox: _strip1];
    
    CCSprite* _strip2 = [CCSprite spriteWithFile:@"Strip1.png"];
    _strip2.position = ccp(115,560);
    _strip2.anchorPoint = ccp(0,0);
    _strip2.visible = FALSE;
    [self addChild: _strip2 z:5];
    [self staticBox: _strip2];
    
    CCSprite* _strip3 = [CCSprite spriteWithFile:@"Strip1.png"];
    _strip3.position = ccp(122,560);
    _strip3.anchorPoint = ccp(0,0);
    _strip3.visible = FALSE;
    [self addChild: _strip3 z:5];
    [self staticBox: _strip3];
    
    CCSprite* _strip4 = [CCSprite spriteWithFile:@"Strip1.png"];
    _strip4.position = ccp(174,560);
    _strip4.anchorPoint = ccp(0,0);
    _strip4.visible = FALSE;
    [self addChild: _strip4 z:5];
    [self staticBox: _strip4];
    
    CCSprite* _strip5 = [CCSprite spriteWithFile:@"Strip1.png"];
    _strip5.position = ccp(185,560);
    _strip5.anchorPoint = ccp(0,0);
    _strip5.visible = FALSE;
    [self addChild: _strip5 z:5];
    [self staticBox: _strip5];
    
    CCSprite* _strip6 = [CCSprite spriteWithFile:@"Strip1.png"];
    _strip6.position = ccp(237,560);
    _strip6.anchorPoint = ccp(0,0);
    _strip6.visible = FALSE;
    [self addChild: _strip6 z:5];
    [self staticBox: _strip6];
    
    CCSprite* _strip7 = [CCSprite spriteWithFile:@"Strip1.png"];
    _strip7.position = ccp(248,560);
    _strip7.anchorPoint = ccp(0,0);
    _strip7.visible = FALSE;
    [self addChild: _strip7 z:5];
    [self staticBox: _strip7];
    
    CCSprite* _strip8 = [CCSprite spriteWithFile:@"Strip1.png"];
    _strip8.position = ccp(301,560);
    _strip8.anchorPoint = ccp(0,0);
    _strip8.visible = FALSE;
    [self addChild: _strip8 z:5];
    [self staticBox: _strip8];
    
    CCSprite* _strip9 = [CCSprite spriteWithFile:@"Strip1.png"];
    _strip9.position = ccp(310,560);
    _strip9.anchorPoint = ccp(0,0);
    _strip9.visible = FALSE;
    [self addChild: _strip9 z:5];
    [self staticBox: _strip9];
    
    CCSprite* _strip10 = [CCSprite spriteWithFile:@"Strip1.png"];
    _strip10.position = ccp(361,560);
    _strip10.anchorPoint = ccp(0,0);
    _strip10.visible = FALSE;
    [self addChild: _strip10 z:5];
    [self staticBox: _strip10];
    
    CCSprite* _strip13 = [CCSprite spriteWithFile:@"Strip1.png"];
    _strip13.position = ccp(371,560);
    _strip13.anchorPoint = ccp(0,0);
    _strip13.visible = FALSE;
    [self addChild: _strip13 z:5];
    [self staticBox: _strip13];
    
    CCSprite* _strip14 = [CCSprite spriteWithFile:@"Strip1.png"];
    _strip14.position = ccp(422,560);
    _strip14.anchorPoint = ccp(0,0);
    _strip14.visible = FALSE;
    [self addChild: _strip14 z:5];
    [self staticBox: _strip14];
    
    CCSprite* _strip15 = [CCSprite spriteWithFile:@"Strip1.png"];
    _strip15.position = ccp(434,560);
    _strip15.anchorPoint = ccp(0,0);
    _strip15.visible = FALSE;
    [self addChild: _strip15 z:5];
    [self staticBox: _strip15];
    
    CCSprite* _strip16 = [CCSprite spriteWithFile:@"Strip1.png"];
    _strip16.position = ccp(486,560);
    _strip16.anchorPoint = ccp(0,0);
    _strip16.visible = FALSE;
    [self addChild: _strip16 z:5];
    [self staticBox: _strip16];
    
    CCSprite* _strip17 = [CCSprite spriteWithFile:@"Strip1.png"];
    _strip17.position = ccp(498,560);
    _strip17.anchorPoint = ccp(0,0);
    _strip17.visible = FALSE;
    [self addChild: _strip17 z:5];
    [self staticBox: _strip17];
    
    CCSprite* _strip18 = [CCSprite spriteWithFile:@"Strip1.png"];
    _strip18.position = ccp(550,560);
    _strip18.anchorPoint = ccp(0,0);
    _strip18.visible = FALSE;
    [self addChild: _strip18 z:5];
    [self staticBox: _strip18];
    
    CCSprite* _strip19 = [CCSprite spriteWithFile:@"Strip1.png"];
    _strip19.position = ccp(562,560);
    _strip19.anchorPoint = ccp(0,0);
    _strip19.visible = FALSE;
    [self addChild: _strip19 z:5];
    [self staticBox: _strip19];
    
    CCSprite* _strip20 = [CCSprite spriteWithFile:@"Strip1.png"];
    _strip20.position = ccp(614,560);
    _strip20.anchorPoint = ccp(0,0);
    _strip20.visible = FALSE;
    [self addChild: _strip20 z:5];
    [self staticBox: _strip20];
    
    CCSprite* _strip21 = [CCSprite spriteWithFile:@"Strip1.png"];
    _strip21.position = ccp(618,560);
    _strip21.anchorPoint = ccp(0,0);
    _strip21.visible = FALSE;
    [self addChild: _strip21 z:5];
    [self staticBox: _strip21];
    
    CCSprite* _strip22 = [CCSprite spriteWithFile:@"Strip1.png"];
    _strip22.position = ccp(670,560);
    _strip22.anchorPoint = ccp(0,0);
    _strip22.visible = FALSE;
    [self addChild: _strip22 z:5];
    [self staticBox: _strip22];
    
    CCSprite* _strip23 = [CCSprite spriteWithFile:@"Strip1.png"];
    _strip23.position = ccp(64,575);
    _strip23.anchorPoint = ccp(0,0);
    _strip23.rotation = 90;
    _strip23.visible = FALSE;
    [self addChild: _strip23 z:5];
    [self staticBox: _strip23];
    
    CCSprite* _strip24 = [CCSprite spriteWithFile:@"Strip1.png"];
    _strip24.position = ccp(64,996);
    _strip24.anchorPoint = ccp(0,0);
    _strip24.rotation = 90;
    _strip24.visible = FALSE;
    [self addChild: _strip24 z:5];
    [self staticBox: _strip24];
}

// Creating the Balls and the Boundaries
-(void) createBalls
{
    // Creating the Balls 
    int x = 106;
    int y = 620;
    int _count = 0;
    
    for(int i = 1; i <= 10; i++)
    {
        for (int j = 1; j <= i; j++) 
        {
            _count++;
            //NSLog(@"%d",_count);
            switch (j) {
                case 1:
                    _ball[_count] = [CCSprite spriteWithFile:@"blue_ball.png"];
                    break;
                case 2:
                    _ball[_count] = [CCSprite spriteWithFile:@"yellow_ball.png"];
                    break;
                case 3:
                    _ball[_count] = [CCSprite spriteWithFile:@"violet_ball.png"];
                    break;
                case 4:
                    _ball[_count] = [CCSprite spriteWithFile:@"violet_1_ball.png"];
                    break;
                case 5:
                    _ball[_count] = [CCSprite spriteWithFile:@"skyblue_ball.png"];
                    break;
                case 6:
                    _ball[_count] = [CCSprite spriteWithFile:@"sap_green_ball.png"];
                    break;
                case 7:
                    _ball[_count] = [CCSprite spriteWithFile:@"red_ball.png"];
                    break;
                case 8:
                    _ball[_count] = [CCSprite spriteWithFile:@"orange_ball.png"];
                    break;
                case 9:
                    _ball[_count] = [CCSprite spriteWithFile:@"green_ball.png"];
                    break;
                case 10:
                    _ball[_count] = [CCSprite spriteWithFile:@"green_1_ball.png"];
                    break;
                default:
                    break;
            }
            
            _ball[_count].position = ccp(x,y);
			_ball[_count].scale = 1.3;
            [self addChild:_ball[_count] z:5];
            [self addStone1Box:_ball[_count]];
            //_ball[_count].opacity = 0;
            y = y + 30;

        }
        x = x + 60;
        y = 620;
    }
	
    [self schedule:@selector(tick:)];
}


// Enable the Balls when we click the particular slate
-(void) enableBalls
{
    
    for(int i = 1; i <= 55; i++)
    {
        if([_ball[i] respondsToSelector:@selector(setVisible:)])
            _ball[i].visible = TRUE;
    }
}

// Disabling the balls if clicked on other type of slates
-(void) disableBalls
{
	[self unschedule:@selector(tick:)];
	[self destroyBox];
}

-(void)destroyBox
{
	b2Body *spriteBody = NULL;
    for(b2Body *bvt = world->GetBodyList(); bvt; bvt=bvt->GetNext()) {
        cin++;
        if (bvt->GetType() == b2_dynamicBody) {
			CCSprite *curSprite = (CCSprite *)bvt->GetUserData();
			spriteBody = bvt;
			world->DestroyBody(spriteBody);
			[self removeChild:curSprite cleanup:YES];
            
		}
	} 
}

#pragma mark Ad Boxes
// Ad box to Balls
-(void)	addStone1Box:(CCSprite *)spri 
{
	b2BodyDef stoneBodyDef;	
	b2FixtureDef stoneShapeDef;
	stoneBodyDef.type = b2_dynamicBody;
	stoneBodyDef.position.Set(spri.position.x/PTM_RATIO,spri.position.y/PTM_RATIO);
	stoneBodyDef.userData=spri;
	b2Body* _body2=world->CreateBody(&stoneBodyDef);
	
	b2CircleShape st;
	st.m_radius = 21.0f/PTM_RATIO;

	stoneShapeDef.shape = &st;
	stoneShapeDef.density = 1.0f;
	//stoneShapeDef.friction = 10.2f;
	//stoneShapeDef.restitution = 0.0f;
	_body2->CreateFixture(&stoneShapeDef);	 
}

// Ad Box to the strips 
-(void) staticBox :(CCSprite *) sprite 
{
	b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody; 
	bodyDef.position.Set(sprite.position.x/PTM_RATIO, sprite.position.y/PTM_RATIO);
	bodyDef.userData = sprite; 
	b2Body *_boxa;
	
	//b2MassData* massData;
//	massData->mass = 0.5f;
//	_boxa->SetMassData(massData); 
	
    _boxa = world->CreateBody(&bodyDef);
    b2FixtureDef fixtureDef;
    
    b2PolygonShape dynamicBox; 
    dynamicBox.SetAsBox(sprite.contentSize.width/PTM_RATIO/2, 
                        sprite.contentSize.height/PTM_RATIO/2, 
                        b2Vec2(sprite.contentSize.width/PTM_RATIO/2,
                               sprite.contentSize.height/PTM_RATIO/2),0);
    fixtureDef.shape = &dynamicBox;	
    
	fixtureDef.density = 5000.0f; 
	//fixtureDef.friction = 0.3f; 
    _boxa->CreateFixture(&fixtureDef);
	//_boxa->ResetMassData();
}

#pragma mark Palette
// Creating the Brush Color palette
-(void) createPallete
{
    mPallete.visible = TRUE;
    mPalletTab1.visible = TRUE;
    mPalletTab2.visible = TRUE;
    if(mSelectedTab == 1)
    {
        mPalletTab1_h.visible = TRUE;
    }
    else
    {
        mPalletTab2_h.visible = TRUE; 
    }
}

// Closing the Color Mixing Palette
-(void)CPallete
{
//j    //NSLog(@"cpallet caled");
    mPallete.visible = FALSE;
    mPalletTab1.visible = FALSE;
    mPalletTab2.visible = FALSE;
    mPalletTab1_h.visible = FALSE;
    mPalletTab2_h.visible = FALSE;
}

#pragma mark Actions for Brush Palette
// Brush Selection Menu Actions functions
-(void)whiteColor
{
    [self selectBrushColor:2];
} 

-(void)yellowColor
{
    [self selectBrushColor:6];
}

-(void)redColor
{
    [self selectBrushColor:5];
}

-(void)blueColor
{
    [self selectBrushColor:3];
}

-(void)blackColor
{
    [self selectBrushColor:1];
}

-(void)greenColor
{
    [self selectBrushColor:4];
}

-(void)clearPaletteColor
{
    if(mSelectedTab == 1)
    {
        mPalletTab1.color = ccc3(255, 255, 255);
        [_colorsArray removeAllObjects];
        currentColor = mPalletTab2.color;
    }
    else
    {
        mPalletTab2.color = ccc3(255, 255, 255);
        [_colorsArray4 removeAllObjects];
        currentColor = mPalletTab1.color; 
    }
}

#pragma mark Draw function
// Debug draw function 
-(void) draw
{
    glDisable(GL_TEXTURE_2D);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	
    world->DrawDebugData();
	
	// restore default GL states
    
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    
    // Give color for the drawing lines
    
    glColor4f(255,2, 23,255);
	
    // Displaying the particular CGRect
//    CGRect rect = mPalletTabRect1;
//    
//    float x = rect.origin.x;
//    float y = rect.origin.y; 
//    float w = rect.size.width;
//    float h = rect.size.height;
//    CGPoint vertices2[] = {
//        ccp(x,y),
//        ccp(x+w,y),
//        ccp(x+w,y+h),
//        ccp(x,y+h)
//    };
//    ccDrawPoly(vertices2, 4, YES);
}

#pragma mark Game Tick
// Tick for the Box2d objects
-(void) tick: (ccTime) dt
{
	world->Step(dt, 10, 10);
    
    for(b2Body *bt = world->GetBodyList(); bt; bt=bt->GetNext()) 
    {    
        if (bt->GetType() == b2_dynamicBody ) {
            CCSprite *manData = (CCSprite *)bt->GetUserData();
            manData.position = ccp(bt->GetPosition().x * PTM_RATIO,
								   bt->GetPosition().y * PTM_RATIO);
		}
        if(bt->GetType() != b2_dynamicBody){
			
            CCSprite *sprite = (CCSprite *)bt->GetUserData();
            
            b2Vec2 b2Position = b2Vec2(sprite.position.x/PTM_RATIO, sprite.position.y/PTM_RATIO);
            float32 b2Angle = -1 * CC_DEGREES_TO_RADIANS(sprite.rotation);
            
            bt->SetTransform(b2Position, b2Angle);
        }
	}
} 

#pragma mark Selection functions from UIView
// Selecting the BrushType calling from the View
-(void)selectBrushType : (int) value
{
    switch (value)
    { 
        case 1: // Brush
            brush = [[CCSprite spriteWithFile:@"brush_5.png"] retain]; 
            brush.scale = mBrushSize;
            brush.opacity = 35;
            break;
            
        case 2: // Chalks
            brush = [[CCSprite spriteWithFile:@"brush_1.png"] retain]; 
            brush.scale = 1.2;
            brush.opacity = 60;
            break;
        
        case 3: // Color Pencils 
            brush = [[CCSprite spriteWithFile:@"fire.png"] retain]; 
            brush.scale = 0.2;
            brush.opacity = 50;
            break;
            
        case 4: // Slate Pencils 
            brush = [[CCSprite spriteWithFile:@"fire.png"] retain]; 
            brush.scale = 0.3;
            brush.opacity = 50;
            break;
        
        case 5: // Crayons
            brush = [[CCSprite spriteWithFile:@"brush_3.png"] retain]; 
            brush.scale = mBrushSize;
            brush.opacity = 255;
            break;                

        case 6: // Erasor
            brush = [[CCSprite spriteWithFile:@"fire.png"] retain]; 
            brush.scale = mBrushSize;
            brush.opacity = 50;
            break;
            
        default:
            break;
    }
}

// Selection of the Brush Size Calling from the View

-(void)selectBrushSize : (int) value
{
    switch (value) {
        case 1:
            mBrushSize = 0.3;
            break;
            
        case 2:
            mBrushSize = 0.6;
            break;
            
        case 3:
            mBrushSize = 0.9;
            break;
            
        case 4:
            mBrushSize = 1.2;
            break;
            
        case 5:
            mBrushSize = 1.5;
            break;
            
        case 6:
            mBrushSize = 1.8;
            break;
            
        default:
            break;
    }
}

// Selection of the brush color calling from the view
-(void)selectBrushColor : (int) value
{
    selectColorCount++;
    r = 0; g = 0; b = 0; 
    
    Byte pixelColor[3];
	pixelColor[0] = 0;
	pixelColor[1] = 0;
	pixelColor[2] = 0;
    
    switch (value)
    {
        case 1: // Black
            pixelColor[0] = 1;
            pixelColor[1] = 0;
            pixelColor[2] = 0;
            break;
            
        case 2: // White
            pixelColor[0] = 255;
            pixelColor[1] = 255;
            pixelColor[2] = 255;
            break;
            
        case 3: // Blue
            pixelColor[0] = 51;
            pixelColor[1] = 123;
            pixelColor[2] = 198;
            break;
            
        case 4: // Green
            pixelColor[0] = 91;
            pixelColor[1] = 124;
            pixelColor[2] = 21;
            break;
            
        case 5: // Red
            pixelColor[0] = 234;
            pixelColor[1] = 31;
            pixelColor[2] = 35;
            break;
            
        case 6: // Yellow 
            pixelColor[0] = 253;
            pixelColor[1] = 189;
            pixelColor[2] = 61;
            break;
            
        case 7: // Orange 
            pixelColor[0] = 254;
            pixelColor[1] = 144;
            pixelColor[2] = 59;
            break;
            
        case 8: // Chrome_Yellow
            pixelColor[0] = 238;
            pixelColor[1] = 205;
            pixelColor[2] = 45;
            break;
            
        case 9: // Crimson_red
            pixelColor[0] = 251;
            pixelColor[1] = 64;
            pixelColor[2] = 65;
            break;
            
        case 10: // Dark_blue
            pixelColor[0] = 57;
            pixelColor[1] = 129;
            pixelColor[2] = 198;
            break;
            
        case 11: // Dark_Green
            pixelColor[0] = 34;
            pixelColor[1] = 108;
            pixelColor[2] = 68;
            break;
            
        case 12: // Lemon_Yellow
            pixelColor[0] = 248;
            pixelColor[1] = 255;
            pixelColor[2] = 46;
            break;
            
        case 13: // Sap_Green
            pixelColor[0] = 97;
            pixelColor[1] = 136;
            pixelColor[2] = 28;
            break;
            
        case 14: // Scarlet_Red
            pixelColor[0] = 255;
            pixelColor[1] = 131;
            pixelColor[2] = 62;
            break;
            
        case 15: // Brown
            pixelColor[0] = 97;
            pixelColor[1] = 53;
            pixelColor[2] = 28;
            break;
            
        case 16: // Sky_Blue
            pixelColor[0] = 54;
            pixelColor[1] = 158;
            pixelColor[2] = 251;
            break;
            
        case 17: // Yellow_ocher
            pixelColor[0] = 251;
            pixelColor[1] = 190;
            pixelColor[2] = 54;
            break;
            
        default:
            break;
    }
    
    if([Singleton sharedMySingleton]._colour2 == 1)
    {
        // Create a color object
        // Mixing of colors logic
        Brush_Color *brushColor = [[Brush_Color alloc] init];
        brushColor.color = ccc3(pixelColor[0], pixelColor[1], pixelColor[2]);
        
        if(selectColorCount > 0)
        {
            
            if(mSelectedTab == 1)
            {  
                [_colorsArray addObject:brushColor];
                [brushColor release];
                
                for (Brush_Color *colort in _colorsArray) 
                {
                    bColorValue = colort.color;
                    
                    r += bColorValue.r;
                    g += bColorValue.g;
                    b += bColorValue.b;
                } 
                
                currentColor = ccc3(r/[_colorsArray count], g/[_colorsArray count], b/[_colorsArray count]);
                
                
                mPalletTab1.color = currentColor;
                pallet1Color = currentColor;
                
                id action = [CCFadeIn actionWithDuration:0.2];
                [mPalletTab1 runAction:action];
                
                _brushColor = currentColor;
            }
            else 
            {
                [_colorsArray4 addObject:brushColor];
                [brushColor release];
                
                for (Brush_Color *colort in _colorsArray4) 
                {
                    bColorValue = colort.color;
                    
                    r += bColorValue.r;
                    g += bColorValue.g;
                    b += bColorValue.b;
                } 
                
                currentColor = ccc3(r/[_colorsArray4 count], g/[_colorsArray4 count], b/[_colorsArray4 count]);
                
                mPalletTab2.color = currentColor;
                pallet2Color = currentColor; 
               
                id action = [CCFadeIn actionWithDuration:0.2];
                [mPalletTab2 runAction:action];
                
                _brushColor = currentColor;
            }
            
        }
    }
    else
    {
        currentColor = ccc3(pixelColor[0], pixelColor[1], pixelColor[2]);
    }
    
    // Allocate the final color of the brush type 
    if([Singleton sharedMySingleton]._colour2 == 2)
    {
        _chalkColor = currentColor;
    }
    else if([Singleton sharedMySingleton]._colour2 == 3)
    {
        _slatePencilColor = currentColor;
    }
    else if([Singleton sharedMySingleton]._colour2 == 4)
    {
        _crayonColor = currentColor;
    }
    else if([Singleton sharedMySingleton]._colour2 == 5)
    {
        _pencilColor = currentColor;
    }
}

// Setting the slate frames in cocos2d view
-(void)selectFrame : (int) value
{    
    switch (value) {
        case 4:
            SF1.visible = TRUE;
            SF2.visible = FALSE;
            SF3.visible = FALSE;
            SF4.visible = FALSE;
            break;
            
        case 5:
            SF1.visible = FALSE;
            SF2.visible = TRUE;
            SF3.visible = FALSE;
            SF4.visible = FALSE;
            break;
            
        case 6:
            SF1.visible = FALSE;
            SF2.visible = FALSE;
            SF3.visible = TRUE;
            SF4.visible = FALSE;
            break;
            
        case 7:
            SF1.visible = FALSE;
            SF2.visible = FALSE;
            SF3.visible = FALSE;
            SF4.visible = TRUE;
            break;
            
        default:
            SF1.visible = FALSE;
            SF2.visible = FALSE;
            SF3.visible = FALSE;
            SF4.visible = FALSE;
            break;
    }
}

// Clearing the drawn things
-(void) clearDraw
{
    [target clear:0 g:0 b:0 a:0];
}

#pragma mark Touch Events
// Touch events of Cocos2d View
-(void) ccTouchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    ////NSLog(@"touch began");
    UITouch *touch = [touches anyObject];
	CGPoint start = [touch locationInView: [touch view]];	
	start = [[CCDirector sharedDirector] convertToGL: start];
        
    //NSLog(@"%f %f",start.x,start.y);
    // Create the Bounding Box for the Touch Detection
    mPalletTabRect1 = [mPalletTab1 boundingBox];
    
    if(CGRectContainsPoint(mPalletTabRect1, start) && mPallete.visible == TRUE)
    {
        mSelectedTab = 1;
        mPalletTab1_h.visible = TRUE;
        mPalletTab2_h.visible = FALSE;
        currentColor = pallet1Color;
    }
    
    mPalletTabRect2 = [mPalletTab2 boundingBox];

    if(CGRectContainsPoint(mPalletTabRect2, start) && mPallete.visible == TRUE)
    {
        mSelectedTab = 2;
        mPalletTab1_h.visible = FALSE;
        mPalletTab2_h.visible = TRUE;
        currentColor = pallet2Color;
    }
    
    mPalletRect =  [mPallete boundingBox];
    if(CGRectContainsPoint(mPalletRect, start) && mPallete.visible == TRUE)
    {
        isTouchedOnPallete = TRUE; 
        
        //gestureRecognizer = [[[UIPanGestureRecognizer alloc] initWithTarget:self action:@selector(handlePanFrom:)] autorelease];
        //[[[CCDirector sharedDirector] openGLView] addGestureRecognizer:gestureRecognizer];
      
        //  //NSLog(@"start x %f, start y %f, palette x %f, palette y %f",start.x,start.y,mPallete.position.x,mPallete.position.y);
        return;
    }
    
    // Switching the Brush Type
    mBrushType = [Singleton sharedMySingleton]._colour2;
    [self selectBrushType:[Singleton sharedMySingleton]._colour2];

    // Setting the Current Color for drawing
    brush.color = currentColor;
    
    mBrushOpacity = brush.opacity;
}

-(void)ccTouchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event 
{
    if (m_MouseJoint) 
	{
        world->DestroyJoint(m_MouseJoint);
        m_MouseJoint = NULL; 
    } 
} 

-(void)ccTouchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
    UITouch *touch = [touches anyObject];
	CGPoint start = [touch locationInView: [touch view]];	
	start = [[CCDirector sharedDirector] convertToGL: start];
	CGPoint end = [touch previousLocationInView:[touch view]];
	end = [[CCDirector sharedDirector] convertToGL:end];
    
    //Move the Palette on Touch Position 
    if(isTouchedOnPallete)
    {
        CGPoint touchLocation = [self convertTouchToNodeSpace:touch];
    
        CGPoint oldTouchLocation = [touch previousLocationInView:touch.view];
        oldTouchLocation = [[CCDirector sharedDirector] convertToGL:oldTouchLocation];
        oldTouchLocation = [self convertToNodeSpace:oldTouchLocation];
    
        CGPoint translation = ccpSub(touchLocation, oldTouchLocation);    
        translation = ccp(translation.y,translation.x);
        [self panForTranslation:translation];

        return;
    }
    
    Byte pixelColor[3];
	pixelColor[0] = 0;
	pixelColor[1] = 255;
	pixelColor[2] = 0;
    
//    DR_Point *aPoint = [[DR_Point alloc] init]; 
//    
//    aPoint.startPoint = start;
//    aPoint.endPoint = end;
//    
//    [aCurve.arrCurvePoints addObject:aPoint];
//    
//    [aPoint release]; 
     
    if([Singleton sharedMySingleton]._colour2 != 6)
    {
        // Begin drawing to the render texture
        [target begin]; 
        
        // for extra points, we'll draw this smoothly from the last position and vary the sprite's
        // scale/rotation/offset
        float distance = ccpDistance(start, end);
        if (distance > 1)
        {
            int d = (int)distance;
            for (int i = 0; i < d; i++)
            { 
                float difx = end.x - start.x;
                float dify = end.y - start.y;
                float delta = (float)i / distance;
                [brush setPosition:ccp(start.x + (difx * delta), start.y + (dify * delta))];
                //brush.color = ccc3(arc4random()%(255 - 40) + 40, arc4random()%(255 - 40) + 40, arc4random()%(255 - 40) + 40);
                //[brush setRotation:rand()%360];
                //float r = ((float)(rand()%50)/50.f) + 0.25f;
                //[brush setScale:r];
                // Call visit to draw the brush, don't call draw... 
                [brush visit];
                if([Singleton sharedMySingleton]._colour2 == 5)
                i = i + 10;
            }
        } 
        // finish drawing and return context back to the screen 
        [target end];
    }
    else
    {
        // begin drawing to the render texture 
        [target begin]; 
    
        float distance = ccpDistance(start, end);
        if (distance > 1)
        {
            int d = (int)distance;
            for (int i = 0; i < d; i++)
            { 
                float difx = end.x - start.x;
                float dify = end.y - start.y;
                float delta = (float)i / distance;
                [brush setPosition:ccp(start.x + (difx * delta), start.y + (dify * delta))];
                
                //Call visit to draw the brush, don't call draw... 
                [brush visit]; 
                
                [brush setOpacity:10];
                glColorMask(FALSE, FALSE, FALSE, TRUE);
                glBlendFunc(GL_ZERO, GL_ONE_MINUS_SRC_ALPHA);
                glColor4ub(0.5, 0.5, 0.5, 255);
               // glLineWidth(10);
                //CGPoint vertices[] = { ccp(100,100), ccp(100,300), ccp(300,300), ccp(300,100) }; 
                //drawPoly( vertices, 4, YES);
                glColorMask(TRUE, TRUE, TRUE, TRUE);            
            }
        }
        // finish drawing and return context back to the screen 
        [target end]; 
    }
    [Singleton sharedMySingleton]._pageUpdated = YES;
    
    // MouseJoint movement of objects
    //if (m_MouseJoint == NULL) return;
    
    b2Vec2 locationWorld = b2Vec2(start.x/PTM_RATIO, start.y/PTM_RATIO);
	
    if (m_MouseJoint != NULL)
    {
        m_MouseJoint->SetTarget(locationWorld);
        return;
    } 
    
	b2AABB aabb;
	b2Vec2 d;
	d.Set(0.001f, 0.001f);
	aabb.lowerBound = locationWorld - d;
	aabb.upperBound = locationWorld + d;
    
	QueryCallback callback(locationWorld);
	world->QueryAABB(&callback, aabb);
	
	if (callback.m_fixture)
	{
        //NSLog(@"inside condition");
        _touchedOnObj = TRUE;
		b2Body* body = callback.m_fixture->GetBody();
		b2MouseJointDef md;
		md.bodyA = groundBody;
		md.bodyB = body;
		md.target = locationWorld; 
		md.maxForce = 155.0f * body->GetMass();
		m_MouseJoint = (b2MouseJoint*)world->CreateJoint(&md);
		body->SetAwake(true);
        //return;
	}
}

-(void)ccTouchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
    selectColorCount = 0;
    
    // Resetting the BOOL of Palette touch
    if(isTouchedOnPallete)
        isTouchedOnPallete = FALSE;
    
//    if([Singleton sharedMySingleton]._colour2 != 6)
//    {
//        [[Singleton sharedMySingleton]._pointsArray1 addObject:aCurve];
//        [aCurve release];
//    }
    
    // Releasing of Mouse Joints
    if (m_MouseJoint) {
        //NSLog(@"releasing mouse joint");
        _touchedOnObj = FALSE;
        world->DestroyJoint(m_MouseJoint);
        m_MouseJoint = NULL;
        return;
    }
}

// Movement of the Palette 
- (void)panForTranslation:(CGPoint)translation
{    
    mPallete.position = ccp(mPallete.position.y,mPallete.position.x);
    CGPoint newPos = ccpAdd(translation, mPallete.position);
    mPallete.position = ccp(newPos.y,newPos.x);
    
    mPalletTab1.position = ccp(mPallete.position.x - 216,mPallete.position.y + 88);
    mPalletTab2.position = ccp(mPallete.position.x - 142,mPallete.position.y + 130);
    mPalletTab1_h.position = ccp(mPallete.position.x - 213,mPallete.position.y + 84);
    mPalletTab2_h.position = ccp(mPallete.position.x - 144,mPallete.position.y + 130);
}

#pragma mark Accelerometer for Balls
- (void)accelerometer:(UIAccelerometer*)accelerometer didAccelerate:(UIAcceleration*)acceleration
{	
	static float prevX=0, prevY=0;
	
	// #define kFilterFactor 0.05f
#define kFilterFactor 1.0f	// don't use filter. the code is here just as an example
	
	float accelX = (float) acceleration.x * kFilterFactor + (1- kFilterFactor)*prevX;
	float accelY = (float) acceleration.y * kFilterFactor + (1- kFilterFactor)*prevY;
	
    // //NSLog(@"%f %f",accelX,accelY);
	prevX = accelX;
	prevY = accelY;
	
	UIDeviceOrientation orientation = [[UIDevice currentDevice] orientation];
    
    if(orientation == UIDeviceOrientationLandscapeLeft)
    {
        isOrientationLandscapeLeft = YES;
        //NSLog(@"isOrientationLandscapeLeft %d",isOrientationLandscapeLeft);
    }
    if(orientation == UIDeviceOrientationLandscapeRight)
    {
        isOrientationLandscapeLeft = NO;
        //NSLog(@"isOrientationLandscapeLeft %d",isOrientationLandscapeLeft);
    }
    
    if(isOrientationLandscapeLeft)
    {
        b2Vec2 gravity( -accelX * 20, -accelY * 20);
        world->SetGravity( gravity );
    }
    else
    {
        b2Vec2 gravity(accelX * 20, accelY * 20);
        world->SetGravity( gravity );
    }

}

#pragma mark Redraw 
// Function for redraw the lines again by storing the points of movement
-(void)redraw
{
  //  //NSLog(@"in redraw %d", [[Singleton sharedMySingleton]._pointsArray1 count]);
        
    [target clear:0 g:0 b:0 a:0];
    
    for(int k = 0; k < [[Singleton sharedMySingleton]._pointsArray1 count]; k++)
    {
        DR_Curve *curDrawObject1 = [[Singleton sharedMySingleton]._pointsArray1 objectAtIndex:k];
        
        [self selectBrushType:curDrawObject1.brushType]; 
        [self selectBrushColor:curDrawObject1.brushColor];
        
        for (DR_Point *aPoint in curDrawObject1.arrCurvePoints) 
        {
            CGPoint the_sPoint = aPoint.startPoint;
            CGPoint the_ePoint = aPoint.endPoint;
            
            [target begin]; 
            
            float distance = ccpDistance(the_sPoint, the_ePoint);
            
            int d = (int)distance;
            for (int i = 0; i < d; i++)
            { 
                float difx = the_ePoint.x - the_sPoint.x;
                float dify = the_ePoint.y - the_sPoint.y;
                float delta = (float)i / distance;
                [brush setPosition:ccp(the_sPoint.x + (difx * delta), the_sPoint.y + (dify * delta))];
                [brush visit];
            }
            
            [target end];
        }
    }
}

#pragma mark Save OpenGL Part
// For saving the OpenGL part 
void releaseData(void *info, const void *data, size_t dataSize) 
{
	free((void*)data); // free the
}

-(UIImage *)saveImage:(NSString *)inFilename
{
    [self CPallete];
  //  static int i=0;
	CGRect rect = CGRectMake(0, 0,1024, 768);
	int width = rect.size.width;
	int height = rect.size.height;
	NSInteger myDataLength = width * height * 4;
	GLubyte *buffer = (GLubyte *) malloc(myDataLength);
	GLubyte *buffer2 = (GLubyte *) malloc(myDataLength);
	glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
    glClearColor(0, 0, 0, 0);
	for(int y = 0; y <height; y++) 
	{ 
		for(int x = 0; x <width * 4; x++)
		{
			int leftIndex = ((height - 1 - y) * width * 4 + x);
			int rightIndex = (y * 4 * width + x);
			buffer2[leftIndex] = buffer[rightIndex];
		}
	}
	free(buffer);
	
    CGDataProviderRef provider = CGDataProviderCreateWithData(NULL,buffer2,myDataLength,releaseData);
	int bitsPerComponent = 8;
	int bitsPerPixel = 32;
	int bytesPerRow = 4 * width;
	CGColorSpaceRef colorSpaceRef = CGColorSpaceCreateDeviceRGB();
    // Make the image as png transparent one 
	CGBitmapInfo bitmapInfo = kCGImageAlphaPremultipliedLast;
	CGColorRenderingIntent renderingIntent = kCGRenderingIntentDefault;
	CGImageRef imageRef = CGImageCreate(width, height, bitsPerComponent,bitsPerPixel, bytesPerRow, colorSpaceRef, bitmapInfo, provider, NULL, NO,renderingIntent);
	CGColorSpaceRelease(colorSpaceRef);
	CGDataProviderRelease(provider);
	
	UIImage *mCurrentScreenshotImage = [[UIImage alloc] initWithCGImage:imageRef];
	CGImageRelease(imageRef);
    
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
	NSString *basePath = ([paths count] > 0) ? [paths objectAtIndex:0] : nil;
    basePath= [basePath stringByAppendingPathComponent:@"DrawApp"];
    
    NSFileManager *fileManager=[NSFileManager defaultManager];
    BOOL isDir;
    if ([fileManager fileExistsAtPath:basePath isDirectory:&isDir] && isDir) {
    }
    else {
        NSError *error;
        BOOL   success = [fileManager createDirectoryAtPath:basePath withIntermediateDirectories:NO attributes:nil error:&error];
        if (!success) NSLog(@"ERROR:%@", error);
    }
    basePath= [basePath stringByAppendingPathComponent:[NSString stringWithFormat: @"%@.png",inFilename]];

    //NSLog(@"basePath os and date%@,,,%@",basePath,[NSDate date]);

    NSData *imageData = [NSData dataWithData:UIImagePNGRepresentation(mCurrentScreenshotImage)];
	[imageData writeToFile:basePath atomically:YES];
    
    //Save the image into the photoalbum
   // UIImageWriteToSavedPhotosAlbum(mCurrentScreenshotImage, nil, nil, nil);
    
//	[mCurrentScreenshotImage autorelease];
    return mCurrentScreenshotImage;
}

#pragma EditOpenGL Image
-(void) setTopLayer:(NSString*)fileName
{
    CCSprite *brusht = [CCSprite spriteWithFile:[NSString stringWithFormat:@"%@",fileName]];
    [self addChild:brusht];
    brusht.rotation = 270;
  //  brusht.anchorPoint = ccp(0,0);
    
    CGSize screend = [[CCDirector sharedDirector] winSize];
    [target begin]; 
    
    [brusht setPosition:ccp(screend.width/2, screend.height/2 )];
    [brusht visit]; 
	
    // finish drawing and return context back to the screen 
    [target end]; 
    [self removeChild:brusht cleanup:YES];
}

-(void) dealloc
{
    CCLOG(@"dealloc in scene CCSprite");
    
    [brush release];
	[target release];
    
    [_colorsArray release];
    _colorsArray = nil;
    
    [_colorsArray4 release];
    _colorsArray4 = nil;
    
    [super dealloc];
} 

@end
