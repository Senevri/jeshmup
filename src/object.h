/*
 * object.h
 * by: Esa Karjalainen 
 * has: lol wut?
 */

#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <string>

class ObjectFinder;
class DrawEngine;

class Object{
public:
    Object();
    virtual ~Object();

    virtual void update(int ticks) = 0;
    virtual void draw(DrawEngine &drawEngine) = 0;

private:
    std::string name;
    unsigned int type; /* if complicated types, go polymorphic */
    unsigned int id;
};

#endif //_OBJECT_H_
