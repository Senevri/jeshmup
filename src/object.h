/*
 * object.h
 * by: Esa Karjalainen 
 * has: lol wut?
 */

#pragma once
#include <string>

class Object{
 public:
  Object();
  ~Object();
  std::string name;
  unsigned int type; /* if complicated types, go polymorphic */
};
