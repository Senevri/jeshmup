/** ZA WARUDO implementations 
 **/
#include "object.h"

Object::Object() {

}
Object::~Object(){

}

std::string Object::getName(){
	return this->m_name;
}
void Object::setName(std::string name){
	this->m_name = name;

}
