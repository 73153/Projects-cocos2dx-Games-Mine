//
//  LHInfoObjects.h
//  plistReaderProject
//
//  Created by Bogdan Vladu on 15.12.2011.
//  Copyright (c) 2011 Bogdan Vladu. All rights reserved.
//

#ifndef __LH_DICTIONARY_TYPE__
#define __LH_DICTIONARY_TYPE__


#include "cocos2d.h"

#include <iostream>
#include "assert.h"
#include "sstream"
#include "fstream"
#include <string>
#include <map>
#include <vector>

using namespace std;

class LHObject;
class LHArray;

typedef std::map<std::string, LHObject*> LHDictionaryMap;
typedef std::map<std::string, LHObject*>::iterator LHDictionaryIterator;
typedef std::map<std::string, LHObject*>::const_iterator LHDictionaryConstIterator;

class LHDictionary
{
  
public:
//------------------------------------------------------------------------------
    LHDictionary(std::stringstream& fileIN);
    LHDictionary();
    LHDictionary(LHDictionary* other);

    virtual ~LHDictionary();
//------------------------------------------------------------------------------
    std::vector<std::string> allKeys(void);
    
    void printAllKeys(void);
    
    void print(void);
    
    LHObject* objectForKey(const std::string& key);
    LHObject* objectForKey(const char* key);
    
    LHDictionary* dictForKey(const char* str);
    LHArray* arrayForKey(const char* str);
    
    void* pointerForKey(const char* str);
        
    void removeObjectForKey(const std::string& key);
    void removeAllObjects(void);
    
    void setObjectForKey(const std::string& object, const std::string& key);
    void setObjectForKey(LHObject* obj, const std::string& key);
    
    void setDictForKey(LHDictionary* dic, const std::string& key);
    void setArrayForKey(LHArray* array, const std::string& key);
    
    cocos2d::CCRect     rectForKey(const std::string& key);
    float               floatForKey(const std::string& key);
    int                 intForKey(const std::string& key);
    bool                boolForKey(const std::string& key);
    cocos2d::CCPoint    pointForKey(const std::string& key);
    cocos2d::CCSize     sizeForKey(const std::string& key);
    cocos2d::ccColor3B  colorForKey(const std::string& key);
    std::string         stringForKey(const std::string& key);
    
    LHDictionary*       dictForKey(const std::string& key);
    LHArray*            arrayForKey(const std::string& key);
    
private:
//------------------------------------------------------------------------------
    LHDictionaryMap objects;
    LHDictionaryIterator m_it;
    
    static int numberOfDicts;
    
    int intFromString(const std::string& str);
    float floatFromString(const std::string& str);
    std::string valueForField(const std::string& field);
    
public:
//------------------------------------------------------------------------------    
    LHDictionaryIterator begin() { return objects.begin(); }
    LHDictionaryConstIterator begin() const { return objects.begin(); }
    LHDictionaryIterator end() { return objects.end(); }
    LHDictionaryConstIterator end() const { return objects.end(); }
};

typedef LHDictionary LHMutableDictionary;

#endif
