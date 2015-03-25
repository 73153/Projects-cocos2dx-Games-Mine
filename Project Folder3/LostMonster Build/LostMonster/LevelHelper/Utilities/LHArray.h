//
//  LHInfoObjects.h
//  plistReaderProject
//
//  Created by Bogdan Vladu on 15.12.2011.
//  Copyright (c) 2011 Bogdan Vladu. All rights reserved.
//

#ifndef __LH_ARRAY_TYPE__
#define __LH_ARRAY_TYPE__

#include <iostream>
#include "assert.h"
#include "sstream"
#include "fstream"
#include <string>
#include <vector>
#include <map>

#include "cocos2d.h"
using namespace std;

class LHObject;
class LHDictionary;

class LHArray
{
public:
//------------------------------------------------------------------------------
    LHArray(std::stringstream& fileIN);
    LHArray();
    LHArray(LHArray* other);
    virtual ~LHArray();
//------------------------------------------------------------------------------
    LHObject* objectAtIndex(const int& idx);
    
    void addObject(LHObject* obj);
    int count(void);
    
    void print(void);
    
    cocos2d::CCRect     rectAtIndex(const int& idx);
    float               floatAtIndex(const int& idx);
    int                 intAtIndex(const int& idx);
    bool                boolAtIndex(const int& idx);
    cocos2d::CCPoint    pointAtIndex(const int& idx);
    cocos2d::CCSize     sizeAtIndex(const int& idx);
    cocos2d::ccColor3B  colorAtIndex(const int& idx);
    std::string         stringAtIndex(const int& idx);
    
    LHDictionary*       dictAtIndex(const int& idx);
    LHArray*            arrayAtIndex(const int& idx);
    
    void insertObjectsInVector(std::vector<std::string>* vec);
    void insertObjectsInVector(std::vector<float>* vec);    
    void insertObjectsInVector(std::vector<bool>* vec);
    
private:
//------------------------------------------------------------------------------    
    std::vector<LHObject*> objects;
    
    static int numberOfArrays;
    
    int intFromString(const std::string& str);
    float floatFromString(const std::string& str);
    std::string valueForField(const std::string& field);
};

typedef LHArray LHMutableArray;

#endif
