/*
 * object.h
 * by: Esa Karjalainen 
 * has: lol wut?
 */

#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <string>

class Object{
 public:
  Object();
  ~Object();
  std::string name;
  unsigned int type; /* if complicated types, go polymorphic */
  unsigned int id;
};

#endif //_OBJECT_H_
