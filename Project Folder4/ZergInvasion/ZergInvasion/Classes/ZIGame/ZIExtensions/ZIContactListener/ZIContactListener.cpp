//
//  MyContactListener.m
//  Box2DPong
//
//  Created by Ray Wenderlich on 2/18/10.
//  Copyright 2010 Ray Wenderlich. All rights reserved.
//

#include "ZIContactListener.h"

ZIContactListener::ZIContactListener() : _contacts() {
}

ZIContactListener::~ZIContactListener() {
}

void ZIContactListener::BeginContact(b2Contact* contact) {
    // We need to copy out the data because the b2Contact passed in
    // is reused.
    MyContact myContact = { contact->GetFixtureA(), contact->GetFixtureB() };
    _contacts.push_back(myContact);
}

void ZIContactListener::EndContact(b2Contact* contact) {
    MyContact myContact = { contact->GetFixtureA(), contact->GetFixtureB() };
    std::vector<MyContact>::iterator pos;
    pos = std::find(_contacts.begin(), _contacts.end(), myContact);
    if (pos != _contacts.end()) {
        _contacts.erase(pos);
    }
}

void ZIContactListener::PreSolve(b2Contact* contact, 
                                 const b2Manifold* oldManifold) {
}

void ZIContactListener::PostSolve(b2Contact* contact, 
                                  const b2ContactImpulse* impulse) {
}