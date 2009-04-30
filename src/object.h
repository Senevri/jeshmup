#pragma once
#include <string>

typedef struct {
  int x;
  int y;
  int z;
} coordinate;

class Object{
 public:
  Object();
  ~Object();
  std::string name;
  coordinate coord;
  int setLocation(int x, int y, int z);


};
