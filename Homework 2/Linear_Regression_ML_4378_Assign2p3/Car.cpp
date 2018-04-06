#include"Car.h"

void Car::init(float mpg, float cylinders,float displacement, float horsepower, float weight, float acceleration){
  this->mpg =mpg;
  this->cylinders = cylinders;
  this->displacement = displacement;
  this-> horsepower = horsepower;
  this->weight = weight;
  this->acceleration = acceleration;
}

Car::Car(float mpg, float cylinders, float displacement, float horsepower, float weight, float acceleration, int type){
  init(mpg, cylinders, displacement,  horsepower,  weight,  acceleration, int type)
// we have 6 attributes and we want to predict 1 of them
}
Car::Car(float mpg, float cylinders, float displacement, float horsepower, float weight, float acceleration, std::string attributeName){
  init(mpg, cylinders, displacement,  horsepower,  weight,  acceleration, int type)
//implement labeling of attributes by indices later. mpg=0, cylinders=1, displacement=2, horsepower=3, weight =4, acceleration =5; )
}
float Car::getMPG(){
  return mpg;
}
float Car::getCylinders(){
  return mpg;
}
float Car::getDisplacement(){
  return displacement;

}
float Car::getHorsepower(){
  return horsepower;
}
float Car::getWeight(){
  return weight;
}
float Car::getAcceleration(){
  return acceleration;
}
int Car::getType(){
  return type;
}
