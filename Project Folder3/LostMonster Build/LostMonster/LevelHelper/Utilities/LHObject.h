//
//  LHInfoObjects.h
//  plistReaderProject
//
//  Created by Bogdan Vladu on 15.12.2011.
//  Copyright (c) 2011 Bogdan Vladu. All rights reserved.
//

#ifndef __LH_OBJECT_TYPE__
#define __LH_OBJECT_TYPE__

#include <iostream>
#include "assert.h"
#include "sstream"
#include "fstream"
#include <string>
#include <map>

using namespace std;

class LHDictionary;
class LHArray;
class LHBatch;

class LHObject
{
public:
    
    enum OBJECT_TYPE
    {
        INT_TYPE    = 0,
        FLOAT_TYPE  = 1,
        BOOL_TYPE   = 2,
        STRING_TYPE = 3,
        LH_DICT_TYPE = 4,
        LH_ARRAY_TYPE = 5,
        LH_VOID_TYPE = 6 //week pointer - needs to be release by you
    };
//------------------------------------------------------------------------------
    LHObject(const int& obj);
    LHObject(const float& obj);
    LHObject(const bool& obj);
    LHObject(const std::string& obj);
    LHObject(LHDictionary* obj);
    LHObject(LHArray* obj);
    LHObject(void* obj);
    LHObject(LHObject* obj);
//------------------------------------------------------------------------------
    LHDictionary* dictValue();
    LHArray* arrayValue();
    std::string stringValue();
    float floatValue();
    int intValue();
    bool boolValue();
    void* voidValue();
    virtual ~LHObject(void);
    
    void print(void);
    
    OBJECT_TYPE type(void){return m_type;}
    
private:
//------------------------------------------------------------------------------
    LHObject(){}
    void* m_object;
    OBJECT_TYPE m_type;
    
    static int numberOfObjects;
};

#endif
