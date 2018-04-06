#ifndef CAR_H
#define CAR_H
#include<string>/*
1. Title: Auto-Mpg Data
2. Number of Instances: 398
3. Number of Attributes: 6
4. Attribute Information:

    1. mpg:           continuous
    2. cylinders:     multi-valued discrete
    3. displacement:  continuous
    4. horsepower:    continuous
    5. weight:        continuous
    6. acceleration:  continuous

5. This is a dataset for regression problem. Attribute 1: mpg is the target value.
   Please use cylinders, displacement, horsepower, weight and acceleration to predict the mpg information.
float alpha= 0.0001; // corresponds to the size of the steps you wish to take
/*
W: weight vector,
M: mean vector,
R: range vector,
I: input vector,
X: processed input vector
Y: desired output vector,
B: training matrix
A: processed training matrix,

*/
class Car {
public:
  Car(float mpg, float cylinders, float displacement, float horsepower, float weight, float acceleration, int type);
  Car(float mpg, float cylinders, float displacement, float horsepower, float weight, float acceleration, std::string attributeName);

  float getMPG();
  float getCylinders();
  float getDisplacement();
  float getHorsepower();
  float getWeight();
  float getAcceleration();
  int getType();
private:
  void init(float mpg, float cylinders,float displacement, float horsepower, float weight, float acceleration, int typeIndex);
  float mpg;
  float cylinders;
  float displacement;
  float horsepower;
  float weight;
  float acceleration;
  int typeIdex;
};
#endif
