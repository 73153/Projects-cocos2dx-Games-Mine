//
//  LHInfoObjects.h
//  plistReaderProject
//
//  Created by Bogdan Vladu on 15.12.2011.
//  Copyright (c) 2011 Bogdan Vladu. All rights reserved.
//

#include "LHObject.h"
#include "../Utilities/LHDictionary.h"
#include "../Utilities/LHArray.h"
#include "../Nodes/LHBatch.h"

#include <iostream>
#include "assert.h"
#include "sstream"
#include "fstream"
#include <string>
#include <map>

int LHObject::numberOfObjects = 0;

//------------------------------------------------------------------------------
LHObject::LHObject(const int& obj){ ++numberOfObjects; m_object = new int(obj); m_type = INT_TYPE;}
LHObject::LHObject(const float& obj){ ++numberOfObjects; m_object = new float(obj); m_type = FLOAT_TYPE;}
LHObject::LHObject(const bool& obj){ ++numberOfObjects; m_object = new bool(obj); m_type = BOOL_TYPE;}
LHObject::LHObject(const std::string& obj){ ++numberOfObjects; m_object = new std::string(obj); m_type = STRING_TYPE;}
LHObject::LHObject(LHDictionary* obj){ ++numberOfObjects; m_object = obj; m_type = LH_DICT_TYPE;}
LHObject::LHObject(LHArray* obj){ ++numberOfObjects; m_object = obj; m_type = LH_ARRAY_TYPE;}
LHObject::LHObject(void* obj){ ++numberOfObjects; m_object = obj; m_type = LH_VOID_TYPE;}

LHObject::LHObject(LHObject* obj){
    ++numberOfObjects; 
    m_type = obj->m_type;
    switch(obj->m_type)
    {
        case INT_TYPE:
            m_object = new int(*((int*)obj->m_object));
            break;
                
        case FLOAT_TYPE:
            m_object = new float(*((float*)obj->m_object));
            break;
                    
        case BOOL_TYPE:
            m_object = new bool(*((bool*)obj->m_object));
            break;
                    
        case STRING_TYPE:
            m_object = new std::string(*((std::string*)obj->m_object));
            break;
                    
        case LH_DICT_TYPE:
            m_object = new LHDictionary((LHDictionary*)obj->m_object);
            break;
                    
        case LH_ARRAY_TYPE:
            m_object = new LHArray((LHArray*)obj->m_object);
            break;

        case LH_VOID_TYPE:
            m_object = obj->m_object;
            break;

        default:
            printf("ERROR: Unknown object type in LHObject copy constructor\n");
            break;
    }
}
//------------------------------------------------------------------------------
LHDictionary* LHObject::dictValue()
{
    if(m_type != LH_DICT_TYPE)
    {
        printf("ERROR! Object is not a dictionary. It is a %d\n", m_type);
    }
        
    return ((LHDictionary*)m_object);
}
//------------------------------------------------------------------------------
LHArray* LHObject::arrayValue()
{
    if(m_type != LH_ARRAY_TYPE)
    {
        printf("ERROR! Object is not a array. It is a %d\n", m_type);
    }
        
    return ((LHArray*)m_object);
}
//------------------------------------------------------------------------------    
std::string LHObject::stringValue()
{ 
    if(m_type != STRING_TYPE)
    {
        printf("ERROR! Object is not a string. It is a %d\n", m_type);
    }
    
    return *((std::string*)m_object);
}
//------------------------------------------------------------------------------    
float LHObject::floatValue()
{ 
    if(m_type != FLOAT_TYPE)
    {
        printf("ERROR! Object is not a float. It is a %d\n", m_type);
    }
        
    return *((float*)m_object);
}
//------------------------------------------------------------------------------    
int LHObject::intValue()
{ 
    //if(this == NULL)
    //    return 0;
    
    if(m_type != INT_TYPE)
    {
        printf("ERROR! Object is not a int. It is a %d\n", m_type);
    }
    return *((int*)m_object);
}
//------------------------------------------------------------------------------    
bool LHObject::boolValue()
{ 
    if(m_type != BOOL_TYPE)
    {
        printf("ERROR! Object is not a bool. It is a %d\n", m_type);
    }
        
    return *((bool*)m_object);
}
//------------------------------------------------------------------------------    
void* LHObject::voidValue()
{
    if(m_type != LH_VOID_TYPE)
    {
        printf("ERROR! Object is not a void. It is a %d\n", m_type);
    }
    
    return ((LHBatch*)m_object);    
}
//------------------------------------------------------------------------------    
LHObject::~LHObject(void)
{
//    printf("OBJECT DEALLOC %d type %d\n", --numberOfObjects, m_type);
    
    switch (m_type) {
        case INT_TYPE:
            delete (int*)m_object;
            break;
            
        case FLOAT_TYPE:
            delete (float*)m_object;
            break;
                
        case BOOL_TYPE:
            delete (bool*)m_object;
            break;
                
        case STRING_TYPE:
            delete (std::string*)m_object;
            break;
                
        case LH_DICT_TYPE:
            delete (LHDictionary*)m_object;
            break;
            
        case LH_ARRAY_TYPE:
            delete (LHArray*)m_object;
            break;
        case LH_VOID_TYPE:
            printf("VOID TYPE SHOULD BE RELEASED BY USER \n");
            //delete (LHBatch*)m_object;
            break;
        default:
            printf("ERROR: Unknown object type on LHObject dealloc\n");
            break;
    }
}
//------------------------------------------------------------------------------    
void LHObject::print(void){

    switch (m_type) {
        case INT_TYPE:
            printf("Object: %d\n", *(int*)m_object);
            break;
            
        case FLOAT_TYPE:
            printf("Object: %f\n", *(float*)m_object);
            break;
            
        case BOOL_TYPE:
            printf("Object: %d\n", *(bool*)m_object);
            break;
            
        case STRING_TYPE:
            printf("Object: %s\n", (*(string*)m_object).c_str());
            break;
            
        case LH_DICT_TYPE:
            printf("Object: Dict \n");
            ((LHDictionary*)m_object)->print();
            break;
            
        case LH_ARRAY_TYPE:
            printf("Object: Array \n");
            ((LHArray*)m_object)->print();
            break;
        case LH_VOID_TYPE:
            printf("Object: Void \n");
            //delete (LHBatch*)m_object;
            break;
        default:
            printf("Object: Unknown object \n");
            printf("ERROR: Unknown object type on LHObject dealloc\n");
            break;
    }
    
}
//------------------------------------------------------------------------------    