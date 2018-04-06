#ifndef KNN_H
#define KNN_H
#include "attribute-type.h"
#include "iris.h"

#include <vector>
#include <cmath>


class KNN {
public:
	KNN(const std::vector<Iris*> &trainingData, unsigned int k = 5, bool normalization = false);
	int group(float sepalLength, float sepalWidth, float petalLength, float petalWidth);
private:
	unsigned int k;
	unsigned int k1=1;
	unsigned int k3=3;
	unsigned int k5=5; 

	std::vector<Iris*> trainingData;
	void findMaxMin();
	float normalize(float attribute, AttributeType type);
	bool normalization;
	float maxSepalLength;
	float minSepalLength;
	float maxSepalWidth;
	float minSepalWidth;
	float maxPetalLength;
	float minPetalLength;
	float maxPetalWidth;
	float minPetalWidth;
};

#endif
