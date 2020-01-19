#include "Location.h"
void Location::setX(float x){
	this->x = x;
}
void Location::setY(float y){
	this->y = y;
}
void Location::set(float x,float y){
	this->x = x;
	this->y = y;
}
float Location::getX(){
	return x;
}
float Location::getY(){
	return y;
}
bool Location::operator==(const Location& loc){
	return loc.x == x && loc.y == y;
}
