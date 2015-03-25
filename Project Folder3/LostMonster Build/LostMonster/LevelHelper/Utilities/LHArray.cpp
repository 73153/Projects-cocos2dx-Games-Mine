//
//  LHInfoObjects.h
//  plistReaderProject
//
//  Created by Bogdan Vladu on 15.12.2011.
//  Copyright (c) 2011 Bogdan Vladu. All rights reserved.
//

#include "LHArray.h"
#include "LHDictionary.h"
#include "LHObject.h"
#include <stdlib.h>

#include "cocoa/CCNS.h"
int LHArray::numberOfArrays = 0;
//------------------------------------------------------------------------------
LHArray::LHArray()
{
    ++numberOfArrays;
}
//------------------------------------------------------------------------------
LHArray::~LHArray(){
    
//    printf("ARRAY DEALLOC %d\n", --numberOfArrays);
    for(size_t i = 0; i< objects.size(); ++i){
        delete objects[i];
    }
    objects.clear();
}
//------------------------------------------------------------------------------
LHArray::LHArray(LHArray* other){
    
    ++numberOfArrays;
    for(int i = 0; i< (int)other->objects.size(); ++i)
    {
        LHObject* obj = other->objects[i];
        objects.push_back(new LHObject(obj));
    }
}
//------------------------------------------------------------------------------
void LHArray::addObject(LHObject* obj){
    
    if(0 != obj)
        objects.push_back(obj);
    
    //printf("Add obj to A\n");
}
//------------------------------------------------------------------------------
void LHArray::print(void){
    
    printf("Print ARRAY........\n");
    for(int i = 0; i< (int)objects.size(); ++i)
    {
        LHObject* obj = objects[i];
        obj->print();
    }
    printf("ARRAY END..........\n");
}
//------------------------------------------------------------------------------
LHArray::LHArray(std::stringstream& fileIN){

    ++numberOfArrays;
    int objCounter = 0;
    std::string objText;
    
    //file needs to start with <dict> else its not a LHDictionary file
    
    //printf("ARRAY START\n");
    //printf("........................................................\n");
    //std::cout << fileIN.str() << std::endl;
    //printf("........................................................\n");
    
    while(!fileIN.eof())
    {
        std::string line;
        getline(fileIN,line);
        
        //printf("A: c:%d %s\n", objCounter, line.c_str());
        
        if (std::string::npos != line.find("<key>")){
            if(1 < objCounter){
                objText+= line+"\n";
            }
        }
        else if (std::string::npos != line.find("<string>")){
            
            if(1 < objCounter){
                objText+= line+"\n";
            }else{
                addObject(new LHObject(valueForField(line)));
            }
        }
        else if (std::string::npos != line.find("<real>")){
            if(1 < objCounter){
                objText+= line+"\n";
            }else{
                addObject(new LHObject(floatFromString(valueForField(line))));
            }
        }
        else if (std::string::npos != line.find("<integer>")){
            if(1 < objCounter){
                objText+= line+"\n";
            }else{
                addObject(new LHObject(intFromString(valueForField(line))));
            }
        }
        else if (std::string::npos != line.find("<true/>")){
            if(1 < objCounter){
                objText+= line+"\n";
            }else{
                addObject(new LHObject(true));
            }
        }
        else if (std::string::npos != line.find("<false/>")){
            if(1 < objCounter){
                objText+= line+"\n";
            }else{
                addObject(new LHObject(false));
            }
        }
        else if (std::string::npos != line.find("<dict>")){
            ++objCounter;
            if(1 < objCounter){
                objText+= line+"\n";
            }
        }
        else if (std::string::npos != line.find("</dict>")){
            if(1 < objCounter){
                objText+= line+"\n";
            }
            
            --objCounter;
            if(1 == objCounter)
            {
                std::stringstream infoText(objText);
                addObject(new LHObject(new LHDictionary(infoText)));
                objText = "";
            }
            
            if(0 > objCounter)
            {
                objText = "";
                objCounter = 1;
            }
        }
        else if (std::string::npos != line.find("<dict/>")){
            addObject(new LHObject(new LHDictionary()));
        }
        else if (std::string::npos != line.find("<array>")){
            ++objCounter;
            if(1 != objCounter){
                objText+= line+"\n";
            }
        }
        else if (std::string::npos != line.find("</array>")){
            if(1 != objCounter){
                objText+= line+"\n";
            }
            
            --objCounter;
            
            if(1 == objCounter)
            {
                std::stringstream infoText(objText);
                addObject(new LHObject(new LHArray(infoText)));
                objText = "";
            }
            
            if(0 > objCounter)
            {
                objText = "";
                objCounter = 1;
            }
        }
        else if (std::string::npos != line.find("<array/>")){
            addObject(new LHObject(new LHArray()));
            //objText = "";
            //objCounter = 1;
        }
    }
    
    //printf("ARRAY END ........................................................\n");
}
//------------------------------------------------------------------------------
LHObject* LHArray::objectAtIndex(const int& idx){

    if(idx >= 0 && idx < (int)objects.size())
    {
        return objects[idx];
    }
    
    printf("ERROR: Index out of bounds");
    return 0;
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
cocos2d::CCRect LHArray::rectAtIndex(const int& idx){
    
    LHObject* obj = objectAtIndex(idx);
    if(obj){
        if(obj->type() != LHObject::STRING_TYPE){
            printf("rectAtIndex %d is not a string\n", idx);
        }
        else {
            return cocos2d::CCRectFromString(obj->stringValue().c_str());
        }
    }
    return cocos2d::CCRectMake(0, 0, 0, 0);
}
//------------------------------------------------------------------------------
float LHArray::floatAtIndex(const int& idx){
    LHObject* obj = objectAtIndex(idx);
    if(obj){
        if(obj->type() != LHObject::FLOAT_TYPE){
            printf("floatAtIndex %d is not a float\n", idx);
        }
        else {
            return obj->floatValue();
        }
    }
    return 0.0f;
}
//------------------------------------------------------------------------------
int LHArray::intAtIndex(const int& idx){
    LHObject* obj = objectAtIndex(idx);
    if(obj){
        if(obj->type() != LHObject::INT_TYPE){
            printf("intAtIndex %d is not a int\n", idx);
        }
        else {
            return obj->intValue();
        }
    }    
    return 0;
}
//------------------------------------------------------------------------------
bool LHArray::boolAtIndex(const int& idx){
    LHObject* obj = objectAtIndex(idx);
    if(obj){
        if(obj->type() != LHObject::BOOL_TYPE){
            printf("boolAtIndex %d is not a bool\n", idx);
        }
        else {
            return obj->boolValue();
        }
    }    
    return false;
}
//------------------------------------------------------------------------------
cocos2d::CCPoint LHArray::pointAtIndex(const int& idx){
    LHObject* obj = objectAtIndex(idx);
    if(obj){
        if(obj->type() != LHObject::STRING_TYPE){
            printf("pointAtIndex %d is not a string\n", idx);
        }
        else {
            return cocos2d::CCPointFromString(obj->stringValue().c_str());
        }
    }    
    return cocos2d::CCPointMake(0, 0); 
}
//------------------------------------------------------------------------------
cocos2d::CCSize LHArray::sizeAtIndex(const int& idx){
    LHObject* obj = objectAtIndex(idx);
    if(obj){
        if(obj->type() != LHObject::STRING_TYPE){
            printf("sizeAtIndex %ds is not a string\n", idx);
        }
        else {
            return cocos2d::CCSizeFromString(obj->stringValue().c_str());
        }
    }    
    return cocos2d::CCSizeMake(0, 0);
}
//------------------------------------------------------------------------------
cocos2d::ccColor3B LHArray::colorAtIndex(const int& idx){
    LHObject* obj = objectAtIndex(idx);
    if(obj){
        if(obj->type() != LHObject::STRING_TYPE){
            printf("colorAtIndex %d is not a string\n", idx);
        }
        else {
            cocos2d::CCRect rect = cocos2d::CCRectFromString(obj->stringValue().c_str());
            return cocos2d::ccc3(rect.origin.x*255.0f, rect.origin.y*255.0f, rect.size.width*255.0f);
        }
    }    
    return cocos2d::ccc3(255.0f, 255.0f, 255.0f);
}
//------------------------------------------------------------------------------
std::string LHArray::stringAtIndex(const int& idx){
    LHObject* obj = objectAtIndex(idx);
    if(obj){
        if(obj->type() != LHObject::STRING_TYPE){
            printf("stringAtIndex %d is not a string\n", idx);
        }
        else {
            return obj->stringValue();
        }
    }    
    return std::string();
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
int LHArray::count(void){
    return (int)objects.size();
}
//------------------------------------------------------------------------------
std::string LHArray::valueForField(const std::string& field)
{
    std::size_t posStart = field.find_first_of(">");
    std::size_t posEnd = field.find_last_of("<");
    return field.substr(posStart+1, posEnd-posStart-1);
}
//------------------------------------------------------------------------------
int LHArray::intFromString(const std::string& str)
{
    return atoi(str.c_str());
}
//------------------------------------------------------------------------------
float LHArray::floatFromString(const std::string& str)
{
    return atof(str.c_str());
}
//------------------------------------------------------------------------------
LHDictionary* LHArray::dictAtIndex(const int& idx){

    LHObject* obj = objectAtIndex(idx);
    if(obj){
        if(obj->type() != LHObject::LH_DICT_TYPE){
            printf("dictAtIndex %d is not a dictionary\n", idx);
        }
        else {
            return obj->dictValue();
        }
    }    
    return NULL;
}
//------------------------------------------------------------------------------
LHArray* LHArray::arrayAtIndex(const int& idx){
    LHObject* obj = objectAtIndex(idx);
    if(obj){
        if(obj->type() != LHObject::LH_ARRAY_TYPE){
            printf("arrayAtIndex %d is not a array\n", idx);
        }
        else {
            return obj->arrayValue();
        }
    }    
    return NULL;    
}
//------------------------------------------------------------------------------
void LHArray::insertObjectsInVector(std::vector<std::string>* vec){
    for(int i = 0; i< count(); ++i)
    {
        LHObject* obj = objectAtIndex(i);
        if(obj){
            if(obj->type() == LHObject::STRING_TYPE){
                vec->push_back(obj->stringValue());
            }
        }    
    }
}
//------------------------------------------------------------------------------
void LHArray::insertObjectsInVector(std::vector<float>* vec){
    for(int i = 0; i< count(); ++i)
    {
        LHObject* obj = objectAtIndex(i);
        if(obj){
            if(obj->type() == LHObject::FLOAT_TYPE){
                vec->push_back(obj->floatValue());
            }
        }    
    }
}
//------------------------------------------------------------------------------
void LHArray::insertObjectsInVector(std::vector<bool>* vec){
    for(int i = 0; i< count(); ++i)
    {
        LHObject* obj = objectAtIndex(i);
        if(obj){
            if(obj->type() == LHObject::BOOL_TYPE){
                vec->push_back(obj->boolValue());
            }
        }    
    }
}
//------------------------------------------------------------------------------