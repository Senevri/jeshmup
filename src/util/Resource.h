#ifndef _RESOURCE_H_
#define _RESOURCE_H_
#include <string>

#ifdef WIN32
const char * const MODELPATH_ = "..\\data\\model\\";
const char * const FONTPATH_ = "..\\data\\fonts\\";
const char _SEPARATOR_ = '\\';
#else
//assume unix

const char * const MODELPATH_ = "data/model/";
const char * const FONTPATH_ = "data/fonts/";
const char _SEPARATOR_ = '/';
#endif

//std::string path(const std::string path)



#endif
