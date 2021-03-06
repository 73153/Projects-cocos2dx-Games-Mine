//  This file was generated by LevelHelper
//  http://www.levelhelper.org
//
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
#include "LHBezier.h"
#include "../LevelHelperLoader.h"
#include "LHPathNode.h"
#include "LHSettings.h"
#include "LHSprite.h"
#include "lhConfig.h"
#include "../CustomClasses/LHAbstractClass.h"
#include "../CustomClasses/LHCustomClasses.h"

typedef struct _ccV3F_C4B_T2F_Triangle
{
	//! top left
	ccV3F_C4B_T2F	tl;
    //! top right
	ccV3F_C4B_T2F	tr;
	//! bottom
	ccV3F_C4B_T2F	bc;
    
} lhV3F_C4B_T2F_Triangle;


typedef struct lhV3F_C4B
{
    ccVertex3F point;
    ccColor4B color;
} lhV3F_C4B;



typedef struct lhV3F_Line
{
	lhV3F_C4B	A;
	lhV3F_C4B	B;
} lhV3F_Line;


//int LHBezierNode::numberOfBezierNodes = 0;
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void LHBezier::init(void){
    
}
////////////////////////////////////////////////////////////////////////////////
LHBezier::~LHBezier(void){
    
//    CCLog("LHBezierNode destructor %s", uniqueName.c_str());
    
	if(0 != body)
	{
		b2World* _world = body->GetWorld();
		if(0 != _world)
		{
			_world->DestroyBody(body);
			body = NULL;
		}
	}
    
    pathPoints.clear();
	linesHolder.clear();
    trianglesHolder.clear();
    
    
    if(userCustomInfo){
        delete userCustomInfo;
        userCustomInfo = NULL;
    }
}

void LHBezier::removeSelf()
{
    if(body){
        if(body->GetWorld()->IsLocked()){            
            LHSettings::sharedInstance()->markNodeForRemoval(this);
            return;
        }
    }
    removeFromParentAndCleanup(true);
}

LevelHelperLoader* LHBezier::parentLoader(){
    
    CCNode* layerParent = this->getParent();
    
    while (layerParent && !LHLayer::isLHLayer(layerParent)){
        layerParent = layerParent->getParent();
    }
    
    if(layerParent && LHLayer::isLHLayer(layerParent)) {
        return ((LHLayer*)layerParent)->parentLoader();
    }
    return NULL;
}

void LHBezier::onExit(){
//    CCLog("LH BEZIER %s onExit", uniqueName.c_str());
    removeTouchObserver();
}
////////////////////////////////////////////////////////////////////////////////
LHBezier::LHBezier(void){
 
    texture = NULL;
    body = NULL;
    
    touchBeginObserver = NULL;
    touchMovedObserver = NULL;
    touchEndedObserver = NULL;
    
    tagTouchBeginObserver = NULL;
    tagTouchMovedObserver = NULL;
    tagTouchEndedObserver = NULL;
    swallowTouches = false;
    touchIsDisabled = false;

    
//    numberOfBezierNodes++;
}

void LHBezier::loadUserCustomInfoFromDictionary(LHDictionary* dictionary){
    userCustomInfo = NULL;
    
    if(!dictionary)return;
    
    std::string className = dictionary->stringForKey("ClassName");
    
    userCustomInfo = LHCustomClassesMgr::customClassInstanceWithName(className);
    
    if(!userCustomInfo) return;
    
    LHDictionary* dict = dictionary->dictForKey("ClassRepresentation");
    
    if(dict){
        //        CCLog("SETTING PROPERTIES FROM DICT");
        ((LHAbstractClass*)userCustomInfo)->setPropertiesFromDictionary(dict);
    }
}
////////////////////////////////////////////////////////////////////////////////
bool LHBezier::initWithDictionary(LHDictionary* bezierDict){
    
    tagTouchBeginObserver = NULL;
    tagTouchMovedObserver = NULL;
    tagTouchEndedObserver = NULL;
    swallowTouches = false;

    LHDictionary* textureDict = bezierDict->dictForKey("TextureProperties");
    
    isClosed	= textureDict->boolForKey("IsClosed");
    isTile		= textureDict->boolForKey("IsTile");
    isVisible	= textureDict->boolForKey("IsDrawable");
    isLine		= textureDict->boolForKey("IsSimpleLine");
    isPath		= textureDict->boolForKey("IsPath");
    opacity     = textureDict->floatForKey("Opacity");
    if(textureDict->objectForKey("DrawBorder"))
        drawBorder = textureDict->boolForKey("DrawBorder");
    else
        drawBorder = true;
    
    uniqueName  = std::string(textureDict->stringForKey("UniqueName"));
    
    setTag(textureDict->intForKey("Tag"));
//    setVertexZ(textureDict->intForKey("ZOrder"));
    setZOrder(textureDict->intForKey("ZOrder"));

    std::string img = textureDict->stringForKey("ImageFile");
    imageSize = CCSizeZero;
    texture = NULL;
    
#if COCOS2D_VERSION >= 0x00020000
    setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionColor));
    mShaderProgram = CCShaderCache::sharedShaderCache()->programForKey(kCCShader_Position_uColor);
    mColorLocation = glGetUniformLocation( mShaderProgram->getProgram(), "u_color");
#endif
    
    if(img!= "" && img != "No Image")
    {
        
#if COCOS2D_VERSION >= 0x00020100
        std::string path = CCFileUtils::sharedFileUtils()->fullPathForFilename(img.c_str());
#elif COCOS2D_VERSION >= 0x00020000
        std::string path = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(img.c_str());
#else
        std::string path = CCFileUtils::fullPathFromRelativePath(img.c_str());
#endif
        texture = CCTextureCache::sharedTextureCache()->addImage(path.c_str());
//        texture = [[CCTextureCache sharedTextureCache] addImage:path];
        
        if( texture ) {
            texture->retain();

#if COCOS2D_VERSION >= 0x00020000
            setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColor));
#endif
            
            imageSize = texture->getContentSize();
        }
    }    
    
    winSize = CCDirector::sharedDirector()->getWinSize();
//    float scale = CCDirector::sharedDirector()->getContentScaleFactor();

    
    color       = textureDict->rectForKey("Color");
    lineColor   = textureDict->rectForKey("LineColor");
    lineWidth   = textureDict->floatForKey("LineWidth");//*scale;
    
    
    loadUserCustomInfoFromDictionary(bezierDict->dictForKey("CustomClassInfo"));
    
    
    LHDictionary* physicsDict = bezierDict->dictForKey("PhysicsProperties");
    
    initTileVerticesFromDictionary(textureDict, physicsDict->arrayForKey("TileVertices"));
    initPathPointsFromDictionary(textureDict);	
    
    b2World* world = LHSettings::sharedInstance()->getActiveBox2dWorld();
    if(NULL != world)
        createBodyFromDictionary(physicsDict,world);
    
    LevelHelperLoader::setTouchDispatcherForBezierWithTag(this, getTag());
    
    return true;
}
////////////////////////////////////////////////////////////////////////////////
LHBezier* LHBezier::bezierWithDictionary(LHDictionary* properties)
{
    LHBezier *pobBNode = new LHBezier();
	if (pobBNode && pobBNode->initWithDictionary(properties))
    {
	    pobBNode->autorelease();
        return pobBNode;
    }
    CC_SAFE_DELETE(pobBNode);
	return NULL;
}
////////////////////////////////////////////////////////////////////////////////
CCPoint LHBezier::pointOnCurve(CCPoint p1, CCPoint p2, CCPoint p3, CCPoint p4, float t){    
	float var1, var2, var3;
    CCPoint vPoint(0.0f, 0.0f);
    
    var1 = 1 - t;
    var2 = var1 * var1 * var1;
    var3 = t * t * t;
    vPoint.x = var2*p1.x + 3*t*var1*var1*p2.x + 3*t*t*var1*p3.x + var3*p4.x;
    vPoint.y = var2*p1.y + 3*t*var1*var1*p2.y + 3*t*t*var1*p3.y + var3*p4.y;
    return(vPoint);				
}

void LHBezier::setZOrder(int z)
{
    _setZOrder(z);
    if (m_pParent)
    {
        m_pParent->reorderChild(this, z);
    }
}

////////////////////////////////////////////////////////////////////////////////
void LHBezier::initTileVerticesFromDictionary(LHDictionary* dictionary,
                                              LHArray* fixtures)
{
//    float scale = CCDirector::sharedDirector()->getContentScaleFactor();
    
//	CCPoint convert = LHSettings::sharedInstance()->convertRatio();
    
    if(NULL != fixtures)
    {
        for(int i = 0; i < fixtures->count(); ++i)
        {
            LHArray* fix = fixtures->arrayAtIndex(i);
        
            std::vector<CCPoint> triagle;
        
            for(int j = 0; j < fix->count(); ++j)
            {
                CCPoint point = fix->pointAtIndex(j);
			
                point = LHSettings::sharedInstance()->transformedPointToCocos2d(point);
                
                triagle.push_back(point);
            }
            trianglesHolder.push_back(triagle);
        }	
	}
	
	if(isVisible)
	{
		LHArray* curvesInShape = dictionary->arrayForKey("Curves");
		
		int MAX_STEPS = 25;
		
        for(int i = 0; i < curvesInShape->count(); ++i)
		{
            LHDictionary* curvDict = curvesInShape->dictAtIndex(i);
            
			CCPoint endCtrlPt   = curvDict->pointForKey("EndControlPoint");
			CCPoint startCtrlPt = curvDict->pointForKey("StartControlPoint");
			CCPoint endPt       = curvDict->pointForKey("EndPoint");
			CCPoint startPt     = curvDict->pointForKey("StartPoint");
			
//            CCPoint pos_offset = LHSettings::sharedInstance()->possitionOffset();
            
			if(!isLine)
			{
				CCPoint prevPoint;
				bool firstPt = true;
				
				for(float t = 0; t <= (1 + (1.0f / MAX_STEPS)); t += 1.0f / MAX_STEPS)
				{
					CCPoint vPoint = LHBezier::pointOnCurve(startPt,
                                                            startCtrlPt,
                                                            endCtrlPt,
                                                            endPt,
                                                            t);
					
					if(!firstPt)
					{
                        CCPoint pt1 = LHSettings::sharedInstance()->transformedPointToCocos2d(prevPoint);
                        CCPoint pt2 = LHSettings::sharedInstance()->transformedPointToCocos2d(vPoint);
                        linesHolder.push_back(pt1);
                        linesHolder.push_back(pt2);
                        
					}
					prevPoint = vPoint;
					firstPt = false;					
				}
			}
			else
			{
				
                CCPoint pos1 = LHSettings::sharedInstance()->transformedPointToCocos2d(startPt);
                CCPoint pos2 = LHSettings::sharedInstance()->transformedPointToCocos2d(endPt);
                linesHolder.push_back(pos1);
                linesHolder.push_back(pos2);				
			}
		}
	}
}
////////////////////////////////////////////////////////////////////////////////
void LHBezier::initPathPointsFromDictionary(LHDictionary* bezierDict)
{	
    LHArray* curvesInShape = bezierDict->arrayForKey("Curves");    
    int MAX_STEPS = 25;    
//	CCPoint conv = LHSettings::sharedInstance()->convertRatio();
	
	int i = 0;
    for(int j = 0; j < curvesInShape->count(); ++j)
    {
        LHDictionary* curvDict = curvesInShape->dictAtIndex(j);
        
        CCPoint endCtrlPt   = curvDict->pointForKey("EndControlPoint");
        CCPoint startCtrlPt = curvDict->pointForKey("StartControlPoint");
        CCPoint endPt       = curvDict->pointForKey("EndPoint");
        CCPoint startPt     = curvDict->pointForKey("StartPoint");
		
//		CCPoint pos_offset = LHSettings::sharedInstance()->possitionOffset();
        
		if(!isLine)
        {
            for(float t = 0; t <= (1 + (1.0f / MAX_STEPS)); t += 1.0f / MAX_STEPS)
            {
                CCPoint vPoint = LHBezier::pointOnCurve(startPt,
                                                        startCtrlPt,
                                                        endCtrlPt,
                                                        endPt,
                                                        t);
				
                vPoint = LHSettings::sharedInstance()->transformedPointToCocos2d(vPoint);
                pathPoints.push_back(vPoint);
            }
			
            pathPoints.pop_back();
        }
        else
        {
            CCPoint sPoint = LHSettings::sharedInstance()->transformedPointToCocos2d(startPt);
            pathPoints.push_back(sPoint);

            
            if(i == curvesInShape->count()-1)
            {
                CCPoint ePoint = LHSettings::sharedInstance()->transformedPointToCocos2d(endPt);
                pathPoints.push_back(ePoint);
            }
            ++i;            
        }
	}		
}
////////////////////////////////////////////////////////////////////////////////
void LHBezier::createBodyFromDictionary(LHDictionary* bezierDict, b2World* world)
{
	if(isPath)
		return;
	
	if((int)pathPoints.size() < 2)
		return;
	
	b2BodyDef bodyDef;	
	
	int bodyType = bezierDict->intForKey("Type");
	if(bodyType > 2)
        return;
        
	bodyDef.type = (b2BodyType)bodyType;
    
	bodyDef.position.Set(0.0f, 0.0f);
	bodyDef.angle = 0.0f;
	
	bodyDef.userData = this;
	
	body = world->CreateBody(&bodyDef);
	
	float ptm = LHSettings::sharedInstance()->lhPtmRatio();
        
    for(int k =0; k< (int)trianglesHolder.size();++k)
    {
        std::vector<CCPoint> fix = trianglesHolder[k];
        
        int size = fix.size();
        b2Vec2 *verts = new b2Vec2[size];
        int i = 0;
        for(int j = size -1; j >=0; --j)
//        for(int j = 0; j < size; ++j)
        {
            CCPoint pt = fix[j];
            
            verts[i].x =pt.x/ptm;
            verts[i].y =pt.y/ptm;
            ++i;
        }

        b2PolygonShape shape;
        shape.Set(verts, size);		
        
        b2FixtureDef fixture;
        
        fixture.density     = bezierDict->floatForKey("Density");
		fixture.friction    = bezierDict->floatForKey("Friction");
		fixture.restitution = bezierDict->floatForKey("Restitution");
		
		fixture.filter.categoryBits = bezierDict->intForKey("Category");
		fixture.filter.maskBits     = bezierDict->intForKey("Mask");
		fixture.filter.groupIndex   = bezierDict->intForKey("Group");
		
		fixture.isSensor = bezierDict->boolForKey("IsSensor");
        
        fixture.shape = &shape;
        body->CreateFixture(&fixture);
        delete[] verts;
    }		
    
    
    b2Vec2 * verts = new b2Vec2 [(int) pathPoints.size ()];
    for (int i = 0; i <(int) pathPoints.size ();++ i)
    {
        verts [i]. x = pathPoints [i] .x / ptm;
        verts [i]. y = pathPoints [i] .y / ptm;
    }
    b2ChainShape shape;
    shape.CreateChain (verts, (int) pathPoints.size ());
    
    b2FixtureDef fixture;
    
    fixture.density     = bezierDict-> floatForKey ("Density");
    fixture.friction    = bezierDict-> floatForKey ("Friction");
    fixture.restitution = bezierDict-> floatForKey ("Restitution");
    
    fixture.filter.categoryBits = bezierDict-> intForKey ("Category");
    fixture.filter.maskBits     = bezierDict-> intForKey ("Mask");
    fixture.filter.groupIndex   = bezierDict-> intForKey ("Group");
    
    fixture.isSensor = bezierDict-> boolForKey ("IsSensor");
    
    fixture.shape = &shape;
    body-> CreateFixture (& fixture);
    delete [] verts;
}
////////////////////////////////////////////////////////////////////////////////
void LHBezier::pushBlendingTextureNamed(const std::string& texName, 
                                            bool tile,
                                            GLenum blendSource, 
                                            GLenum blendDestination){

    if(!isTile)
        return;
    
    CCTexture2D* tex = CCTextureCache::sharedTextureCache()->addImage(texName.c_str());
    if(NULL != tex){
        LHBezierBlendingInfo info = {tex, blendSource, blendDestination, tile};
        blendingTextures.push_back(info);
    }
}
////////////////////////////////////////////////////////////////////////////////
//void LHBezier::visit()
//{
//	CCNode::visit();
//}
#if COCOS2D_VERSION >= 0x00020000
void LHBezier::draw(void)
{
    if(!isVisible){
        return;
    }
    
    CCNode::draw();
    
    CC_NODE_DRAW_SETUP();
    
//    float scale = 1;
    
    int size = (int)trianglesHolder.size();
    
    lhV3F_C4B_T2F_Triangle* points = new lhV3F_C4B_T2F_Triangle[size];

    //visual studio does not like this
//    lhV3F_C4B_T2F_Triangle points[size];

    
    ccColor4B colorVert = { (GLubyte)(color.origin.x*255.0f),
        (GLubyte)(color.origin.y*255.0f),
        (GLubyte)(color.size.width*255.0f),
        (GLubyte)(opacity*255.0f)};
    
    for(int k = 0; k < (int)size; ++k)
    {
        std::vector<CCPoint> fix = trianglesHolder[k];
        
        for(int j = 0; j < 3; ++j)
        {
            CCPoint pt = fix[j];
            
            ccVertex3F vert = {pt.x, pt.y, 0};
            ccTex2F tex = { (pt.x/imageSize.width),
                ((winSize.height - pt.y)/imageSize.height)};
            
            if(j == 0)
            {
                points[k].tl.vertices = vert;
                points[k].tl.colors = colorVert;
                points[k].tl.texCoords = tex;
            }
            else if(j == 1)
            {
                points[k].tr.vertices = vert;
                points[k].tr.colors = colorVert;
                points[k].tr.texCoords = tex;
            }
            else if (j == 2)
            {
                points[k].bc.vertices = vert;
                points[k].bc.colors = colorVert;
                points[k].bc.texCoords = tex;
            }
        }
    }
    
    
    ccBlendFunc	blendFunc_;				// Needed for the texture protocol
    
    blendFunc_.src = GL_SRC_ALPHA;
    blendFunc_.dst = GL_ONE_MINUS_SRC_ALPHA;
    
    
    ccGLEnableVertexAttribs( kCCVertexAttribFlag_PosColorTex );
    
    ccGLBlendFunc( blendFunc_.src, blendFunc_.dst );
    
    if(texture)
    {
        ccGLBindTexture2D( texture->getName());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }
    
#define kPointSize sizeof(ccV3F_C4B_T2F)
    long offset = (long)points;
    
    // vertex
    int diff = offsetof( ccV3F_C4B_T2F, vertices);
    glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, kPointSize, (void*) (offset + diff));
    
    // texCoods
    diff = offsetof( ccV3F_C4B_T2F, texCoords);
    glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, kPointSize, (void*)(offset + diff));
    
    // color
    diff = offsetof( ccV3F_C4B_T2F, colors);
    glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, kPointSize, (void*)(offset + diff));
    
    glDrawArrays(GL_TRIANGLES, 0, 3*size);
    
    
    delete[] points;
    
    bool wasBlend = glIsEnabled(GL_BLEND);
    glEnable(GL_BLEND);
    
    for(int b = 0; b < (int)blendingTextures.size(); ++b)
    {
        LHBezierBlendingInfo info = blendingTextures[b];

        CCTexture2D* tex = info.texture;
        if(NULL != tex)
        {
            glBlendFunc(info.blendSource, info.blendDestination);
            glBindTexture(GL_TEXTURE_2D, tex->getName());
            
            if(info.tile){
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            }
            
            glDrawArrays(GL_TRIANGLES, 0, 3*size);
        }
    }
    
    if(!wasBlend)
        glDisable(GL_BLEND);
    
    if(drawBorder)
    {
        float oldLineWidth = 1.0f;
        glGetFloatv(GL_LINE_WIDTH, &oldLineWidth);
        
        glLineWidth(lineWidth);
        
    //    int linesNo = (int)linesHolder.size();
            
        mShaderProgram->use();
        
    
#if COCOS2D_VERSION >= 0x00020100
        mShaderProgram->setUniformsForBuiltins();
#else
        mShaderProgram->setUniformForModelViewProjectionMatrix();
#endif
        mShaderProgram->setUniformLocationWith4f(mColorLocation,
                                                 lineColor.origin.x,
                                                 lineColor.origin.y,
                                                 lineColor.size.width,
                                                 opacity);
        
        
        ccColor4B lineColorVert = { (GLubyte)(lineColor.origin.x*255.0f),
                                    (GLubyte)(lineColor.origin.y*255.0f),
                                    (GLubyte)(lineColor.size.width*255.0f),
                                    (GLubyte)(opacity*255.0f)};
        

        lhV3F_Line* lines_verts = new lhV3F_Line[linesHolder.size()];
        //visual studio does not like this
//        lhV3F_Line lines_verts[linesHolder.size()];
        
        int l = 0;
        for(int i = 0; i < (int)linesHolder.size(); i+=2)
        {
            CCPoint pt1 = linesHolder[i];
            CCPoint pt2 = linesHolder[i+1];

            lines_verts[l].A.point.x = pt1.x;
			lines_verts[l].A.point.y = pt1.y;
			lines_verts[l].A.point.z = 0.0f;

            lines_verts[l].A.color = lineColorVert;
            
			lines_verts[l].B.point.x = pt2.x;
			lines_verts[l].B.point.y = pt2.y;
			lines_verts[l].B.point.z = 0.0f;
            lines_verts[l].B.color = lineColorVert;
            
            l++;
        }
        
        ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position | kCCVertexAttribFlag_Color );
            
    #define line_kPointSize sizeof(lhV3F_C4B)
        long line_offset = (long)lines_verts;
        
        // vertex
        int line_diff = offsetof( lhV3F_C4B, point);
        glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, line_kPointSize, (void*) (line_offset + line_diff));
        
        // color
        line_diff = offsetof( lhV3F_C4B, color);
        glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, line_kPointSize, (void*)(line_offset + line_diff));
        
        glDrawArrays(GL_LINES, 0, linesHolder.size());
         
		delete[] lines_verts;
    }
    
	CC_INCREMENT_GL_DRAWS(1);
    
	CHECK_GL_ERROR_DEBUG();
}
#else
void LHBezier::draw(void)
{
    
    float scale = CCDirector::sharedDirector()->getContentScaleFactor();
    
	if(0.0f != LHSettings::sharedInstance()->customAlpha())
	{
		glColor4f(color.origin.x, 
				  color.origin.y, 
				  color.size.width, 
				  color.size.height*LHSettings::sharedInstance()->customAlpha());
		glPushMatrix();
		
        glDisableClientState(GL_COLOR_ARRAY);
        
//        if(NULL != texture)
//        {
            if(texture)
            {
                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, texture->getName());
		
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            }
        else
        {
            glDisable(GL_TEXTURE_2D);
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);

        }
            
            int size = (int)trianglesHolder.size();
            CCPoint* verts = new CCPoint[size* 3];
        
            CCPoint* texcoords = NULL;
            if(texture)
            {
                texcoords = new CCPoint[size* 3];
            }
            for(int k = 0; k < (int)trianglesHolder.size();++k)
            {
                std::vector<CCPoint> fix = trianglesHolder[k];
                
                for(int j = 0; j < 3; ++j)
                {
                    CCPoint pt = fix[j];
                
                    pt.x *= scale;
                    pt.y *= scale;
                    
                    verts[k*3 + j] = pt;
                    
                    if(texcoords)
                    {
                        texcoords[k*3 + j].x = pt.x/imageSize.width;
                        texcoords[k*3 + j].y = (winSize.height - pt.y)/imageSize.height;
                    }
                }
            }
                                
        if(texcoords)
        {
            glTexCoordPointer(2, GL_FLOAT, 0, texcoords);
        }
            glVertexPointer(2, GL_FLOAT, 0, verts);
            glDrawArrays(GL_TRIANGLES, 0, 3*size);
            
            bool wasBlend = glIsEnabled(GL_BLEND);
            glEnable(GL_BLEND);            
            int oldBlendDST = 0;
            glGetIntegerv(GL_BLEND_DST, &oldBlendDST);
            int oldBlendSRC = 0;
            glGetIntegerv(GL_BLEND_SRC, &oldBlendSRC);

            for(int i = 0; i < blendingTextures.size(); ++i)
            {
                CCTexture2D* tex = blendingTextures[i].texture;
                if(NULL != tex)
                {
                    glBlendFunc(blendingTextures[i].blendSource, blendingTextures[i].blendDestination);
                    glBindTexture(GL_TEXTURE_2D, tex->getName());
                    
                    if(blendingTextures[i].tile){
                        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                    }

                    if(texcoords)
                    {
                        glTexCoordPointer(2, GL_FLOAT, 0, texcoords);
                    }
                    
                    glVertexPointer(2, GL_FLOAT, 0, verts);
                    glDrawArrays(GL_TRIANGLES, 0, 3*size);                
                }
            }
            
            glBlendFunc(oldBlendSRC, oldBlendDST);
            if(!wasBlend)
                glDisable(GL_BLEND);
            
            delete [] verts;
            delete [] texcoords;
//		}
        
        if(drawBorder)
        {
            float oldLineWidth = 1.0f;
            glGetFloatv(GL_LINE_WIDTH, &oldLineWidth); 
            
            glLineWidth(lineWidth);
            
            glDisable(GL_TEXTURE_2D);
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
            glColor4f(lineColor.origin.x, 
                      lineColor.origin.y, 
                      lineColor.size.width, 
                      lineColor.size.height*LHSettings::sharedInstance()->customAlpha());
            
            CCPoint* line_verts = new CCPoint[linesHolder.size()];
            for(int i = 0; i < (int)linesHolder.size(); i+=2)
            {
                CCPoint pt1 = linesHolder[i];
                CCPoint pt2 = linesHolder[i+1];
                line_verts[i] = pt1;
                line_verts[i+1] = pt2;            
            }
            
            glVertexPointer(2, GL_FLOAT, 0, line_verts);
            glDrawArrays(GL_LINES, 0, linesHolder.size());
            delete[] line_verts;
            
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            glEnableClientState(GL_COLOR_ARRAY);
            glLineWidth(oldLineWidth);
            glEnable(GL_TEXTURE_2D);	
            glPopMatrix();
        }
	}
}
#endif
////////////////////////////////////////////////////////////////////////////////
bool LHBezier::isLHBezier(CCNode* obj){
    
    if( 0 != dynamic_cast<LHBezier*>(obj))
        return true;
    
    return false;    
}

std::string LHBezier::uniqueNameForBody(b2Body* body){
    
    CCNode* spr = (CCNode*)body->GetUserData();
    
    if(LHSprite::isLHSprite(spr))
        return ((LHSprite*)spr)->getUniqueName();
    
    if(LHBezier::isLHBezier(spr))
        return ((LHBezier*)spr)->getUniqueName();
    
    return NULL;
}
//------------------------------------------------------------------------------
LHBezier* LHBezier::bezierForBody(b2Body* body){
    
    if(0 == body)
        return 0;
    
    CCNode* spr = (CCNode*)body->GetUserData();
    
    if(LHBezier::isLHBezier(spr))
    {
        return (LHBezier*)spr;
    }
    
    return 0;
}
//------------------------------------------------------------------------------
int LHBezier::tagForBody(b2Body* body){
    if(0 != body)
    {
        CCNode* spr = (CCNode*)body->GetUserData();
        if(NULL != spr)
        {
            return spr->getTag();
        }
    }
    return -1;
}
//------------------------------------------------------------------------------
std::string LHBezier::userInfoClassName(){
    if(userCustomInfo)
        return ((LHAbstractClass*)userCustomInfo)->className();
    return "No Class";
}
//------------------------------------------------------------------------------
void* LHBezier::userInfo(){
    return userCustomInfo;
}

//------------------------------------------------------------------------------
bool LHBezier::isTouchedAtPoint(CCPoint point){
    
    if(body != NULL){
        b2Fixture* stFix = body->GetFixtureList();
        while(stFix != 0){
            if(stFix->TestPoint(b2Vec2(point.x/LHSettings::sharedInstance()->lhPtmRatio(), 
                                       point.y/LHSettings::sharedInstance()->lhPtmRatio()))){
                return true;
            }
            stFix = stFix->GetNext();
        }
    }
    return false;    
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void LHBezier::registerTouchBeginObserver(CCObject* observer, 
                                        SEL_CallFuncO selector){
    this->registerTouchBeganObserver(observer, selector);
}

void LHBezier::registerTouchBeganObserver(CCObject* observer, SEL_CallFuncO selector){

    removeTouchObserver();
    
    CCTouchDispatcher* touchDispatcher = NULL;
#if COCOS2D_VERSION >= 0x00020000
    touchDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
#else
    touchDispatcher = CCTouchDispatcher::sharedDispatcher();
#endif
    
    if(touchDispatcher){
        
        CCTouchHandler* handler = touchDispatcher->findHandler(this);
        
        //if is not already added to the touch dispatcher - then lets add it
        if(!handler)
        {
            touchDispatcher->addTargetedDelegate(this, touchPriority, swallowTouches);
        }
    }
    
    if(NULL == touchBeginObserver)
        touchBeginObserver = new LHObserverPair();
    
    if(touchBeginObserver){
        touchBeginObserver->object = observer;
        touchBeginObserver->selector = selector;
    }
}
//------------------------------------------------------------------------------
void LHBezier::registerTouchMovedObserver(CCObject* observer, 
                                              SEL_CallFuncO selector){
    if(NULL == touchMovedObserver)
        touchMovedObserver = new LHObserverPair();
    
    if(touchMovedObserver){
        touchMovedObserver->object = observer;
        touchMovedObserver->selector = selector;
    }
}
//------------------------------------------------------------------------------
void LHBezier::registerTouchEndedObserver(CCObject* observer, 
                                              SEL_CallFuncO selector){
    if(NULL == touchEndedObserver)
        touchEndedObserver = new LHObserverPair();
    
    if(touchEndedObserver){
        touchEndedObserver->object = observer;
        touchEndedObserver->selector = selector;    
    }
}
void LHBezier::removeTouchObserver()
{
    if(tagTouchBeginObserver || touchBeginObserver)
        LevelHelperLoader::removeTouchDispatcherFromBezier(this);
    
    if(touchBeginObserver)
        delete touchBeginObserver;
    
    if(touchMovedObserver)
        delete touchMovedObserver;
    
    if(touchEndedObserver)
        delete touchEndedObserver;
    
    touchBeginObserver = NULL;
    touchMovedObserver = NULL;
    touchEndedObserver = NULL;
    
    tagTouchBeginObserver = NULL;
    tagTouchEndedObserver = NULL;
    tagTouchMovedObserver = NULL;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
bool LHBezier::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) 
{    
    if(touchIsDisabled)
        return false;
    
    if(NULL == touchBeginObserver && NULL == tagTouchBeginObserver)
        return false;
    
#if COCOS2D_VERSION >= 0x00020000
    CCPoint touchPoint =     pTouch->getLocationInView();
#else
    
#if LH_COCOS2DX_VERSION == 0x00010103
    //cocos2d-1.0.1-x-0.13.0-beta
    CCPoint touchPoint =     pTouch->locationInView();
#else
    //cocos2d-1.0.1-x-0.12.0
    CCPoint touchPoint =     pTouch->locationInView(pTouch->view());
#endif
    
    
#endif
    
    
    touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);
    
    if(isTouchedAtPoint(touchPoint))
    {
        LHTouchInfo* info = LHTouchInfo::touchInfo();
        info->relativePoint = CCPointMake(touchPoint.x - getPosition().x,
                                          touchPoint.y - getPosition().y);
        info->glPoint = touchPoint;
        info->event = pEvent;
        info->touch = pTouch;
        info->bezier = this;
        info->delta = CCPointZero;
        
        if(touchBeginObserver){
            if(touchBeginObserver->object){
                (touchBeginObserver->object->*touchBeginObserver->selector)(info);
            }        
        }
        
        if(tagTouchBeginObserver){
            if(tagTouchBeginObserver && tagTouchBeginObserver->object){
                (tagTouchBeginObserver->object->*tagTouchBeginObserver->selector)(info);
            }
        }
        return swallowTouches;
    }
    return false;
}
//------------------------------------------------------------------------------
void LHBezier::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){
    
    
    if(touchIsDisabled)
        return;
    
    if(NULL == touchMovedObserver && NULL == tagTouchMovedObserver)
        return;
    
#if COCOS2D_VERSION >= 0x00020000
    CCPoint touchPoint =     pTouch->getLocationInView();
#else
    
#if LH_COCOS2DX_VERSION == 0x00010103
    //cocos2d-1.0.1-x-0.13.0-beta
    CCPoint touchPoint =     pTouch->locationInView();
#else
    //cocos2d-1.0.1-x-0.12.0
    CCPoint touchPoint =     pTouch->locationInView(pTouch->view());
#endif
#endif

    touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);
    

#if COCOS2D_VERSION >= 0x00020000
    CCPoint prevLocation = pTouch->getPreviousLocationInView();
#else
    
#if LH_COCOS2DX_VERSION == 0x00010103
    //cocos2d-1.0.1-x-0.13.0-beta
    CCPoint prevLocation =     pTouch->previousLocationInView();
#else
    //cocos2d-1.0.1-x-0.12.0
    CCPoint prevLocation =     pTouch->previousLocationInView(pTouch->view());
#endif
    
#endif

    
    
    prevLocation =  CCDirector::sharedDirector()->convertToGL(prevLocation);
    
    LHTouchInfo* info = LHTouchInfo::touchInfo();
    info->relativePoint = CCPointMake(touchPoint.x - getPosition().x,
                                      touchPoint.y - getPosition().y);
    info->glPoint = touchPoint;
    info->event = pEvent;
    info->touch = pTouch;
    info->bezier = this;
    info->delta = CCPointMake(touchPoint.x - prevLocation.x,
                              touchPoint.y - prevLocation.y);
    
    
    if(touchMovedObserver){
        if(touchMovedObserver->object){
            (touchMovedObserver->object->*touchMovedObserver->selector)(info);
        }  
    }
    
    if(tagTouchMovedObserver){
        if(tagTouchMovedObserver && tagTouchMovedObserver->object){
            (tagTouchMovedObserver->object->*tagTouchMovedObserver->selector)(info);
        }
    }
}
//------------------------------------------------------------------------------
void LHBezier::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){
    
    if(touchIsDisabled)
        return;
    
    if(NULL == touchEndedObserver && NULL == tagTouchEndedObserver)
        return;

    
    
#if COCOS2D_VERSION >= 0x00020000
    CCPoint touchPoint =     pTouch->getLocationInView();
#else
    
#if LH_COCOS2DX_VERSION == 0x00010103
    //cocos2d-1.0.1-x-0.13.0-beta
    CCPoint touchPoint =     pTouch->locationInView();
#else
    //cocos2d-1.0.1-x-0.12.0
    CCPoint touchPoint =     pTouch->locationInView(pTouch->view());
#endif

#endif
    
    touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);
    
    
#if COCOS2D_VERSION >= 0x00020000
    CCPoint prevLocation = pTouch->getPreviousLocationInView();
#else
    
    
#if LH_COCOS2DX_VERSION == 0x00010103
    //cocos2d-1.0.1-x-0.13.0-beta
    CCPoint prevLocation =     pTouch->previousLocationInView();
#else
    //cocos2d-1.0.1-x-0.12.0
    CCPoint prevLocation =     pTouch->previousLocationInView(pTouch->view());
#endif
    
#endif

    prevLocation =  CCDirector::sharedDirector()->convertToGL(prevLocation);
    
    LHTouchInfo* info = LHTouchInfo::touchInfo();
    info->relativePoint = CCPointMake(touchPoint.x - getPosition().x,
                                      touchPoint.y - getPosition().y);
    info->glPoint = touchPoint;
    info->event = pEvent;
    info->touch = pTouch;
    info->bezier = this;
    info->delta = CCPointMake(touchPoint.x - prevLocation.x,
                              touchPoint.y - prevLocation.y);
    
    if(touchEndedObserver){
        if(touchEndedObserver->object){
            (touchEndedObserver->object->*touchEndedObserver->selector)(info);
        }
    }
    if(tagTouchEndedObserver){
        if(tagTouchEndedObserver && tagTouchEndedObserver->object){
            (tagTouchEndedObserver->object->*tagTouchEndedObserver->selector)(info);
        }
    }
}
//------------------------------------------------------------------------------
void LHBezier::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent){
    
}

void LHBezier::setTagTouchBeginObserver(LHObserverPair* pair){
    tagTouchBeginObserver = pair;
}
void LHBezier::setTagTouchMovedObserver(LHObserverPair* pair){
    tagTouchMovedObserver = pair;
}
void LHBezier::setTagTouchEndedObserver(LHObserverPair* pair){
    tagTouchEndedObserver = pair;
}