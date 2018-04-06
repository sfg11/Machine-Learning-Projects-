
/*
#include "stdafx.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <assert.h>
#include "CS534-Imp1.hpp"

using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	doGradients();

	batchPerceptron();

	votedPerceptron();

	return 0;
}

void doGradients(
	void
	) {
	// loop var
	int i;

	// read in regression training
	double gradientLearningRate;
	vector<vector<double>> trainingData;

	ifstream trainingFile("regression-train.csv");
	while(trainingFile.good()) {
		double x1, x2, x3, y;
		trainingFile >> x1;
		trainingFile.get();
		trainingFile >> x2;
		trainingFile.get();
		trainingFile >> x3;
		trainingFile.get();
		trainingFile >> y;
		trainingFile.get();

		std::vector<double> example;
		// first parameter is added to allow for w_0
		example.push_back(1);
		example.push_back(x1);
		example.push_back(x2);
		example.push_back(x3);
		example.push_back(y);

		//cout << example[0] << " " << example[1] << " " << example[2] << " " << example[3] << " " << example[4] << " " << example.size() << endl;

		trainingData.push_back(example);
	}
	// remove duplicate final element
	trainingData.pop_back();


	vector<double> batchGradientWeights (trainingData[0].size()-1);
	vector<double> stochasticGradientWeights (trainingData[0].size()-1);
	vector<double> batchGradientTrainingError;
	vector<double> stochasticGradientTrainingError;

	//init weight vectors
	for(vector<double>::size_type i = 0; i<trainingData[0].size()-1; i++){
		batchGradientWeights[i] = 0;
		stochasticGradientWeights[i] = 0;
	}

	// run batch gradient descent training
	for(i = 0; i<num_epochs; i++){
		gradientLearningRate = (0.5f / trainingData.size());
		batchGradientTrainingError.push_back(batchGradientDescent(trainingData, batchGradientWeights, gradientLearningRate));
	}
	// run stochastic gradient descent training
	for(i = 0; i<num_epochs; i++){
		// randomize order for stochastic
		random_shuffle(trainingData.begin(), trainingData.end());
		stochasticGradientTrainingError.push_back(stochasticGradientDescent(trainingData, stochasticGradientWeights, gradientLearningRate));
	}

	// read in regression test
	vector<vector<double>> testData;
	ifstream testFile("regression-test.csv");
	while(testFile.good()) {
		double x1, x2, x3, y;
		testFile >> x1;
		testFile.get();
		testFile >> x2;
		testFile.get();
		testFile >> x3;
		testFile.get();
		testFile >> y;
		testFile.get();

		std::vector<double> example;
		// first parameter is added to allow for w_0
		example.push_back(1);
		example.push_back(x1);
		example.push_back(x2);
		example.push_back(x3);
		example.push_back(y);

		testData.push_back(example);
	}
	// remove duplicate final element
	testData.pop_back();

	random_shuffle(testData.begin(), testData.end());

	double batchGradientTestError;
	double stochasticGradientTestError;

	// run accuracy test trials
	batchGradientTestError = testGradientDescent(testData, batchGradientWeights);
	stochasticGradientTestError = testGradientDescent(testData, stochasticGradientWeights);


	// DO THIS: output trial results in some format
	ofstream gradientOut;
	gradientOut.open("gradientOut.txt");
	gradientOut << "gradient descent learning weight: " << gradientLearningRate * trainingData.size() << "/" << trainingData.size() << endl;
	gradientOut << "batch gradient weights: " << batchGradientWeights[0] << ", " << batchGradientWeights[1] << ", " << batchGradientWeights[2] << ", " << batchGradientWeights[3] << endl;
	gradientOut << "batch gradient sse: " << endl;
	for(vector<double>::size_type i = 0; i<batchGradientTrainingError.size(); i++){
		 gradientOut << batchGradientTrainingError[i] << endl;
	}
	gradientOut << "batch gradient test sse: " << batchGradientTestError << endl;

	gradientOut << "stochastic gradient weights: " << stochasticGradientWeights[0] << ", " << stochasticGradientWeights[1] << ", " << stochasticGradientWeights[2] << ", " << stochasticGradientWeights[3] << endl;
	gradientOut << "stochastic gradient sse: " << endl;
	for(vector<double>::size_type i = 0; i<stochasticGradientTrainingError.size(); i++){
		gradientOut << stochasticGradientTrainingError[i] << endl;
	}
	gradientOut << "stochastic gradient test sse: " << stochasticGradientTestError << endl;
	gradientOut.close();


}

// takes initial weights, test & training data, returns weight vector & total SSE error
double batchGradientDescent(
	vector<vector<double>> training,
	vector<double> &weights,
	double learningRate
	) {
		double result1, result2, sse;
		vector<double> gradient (weights.size());

		//  psuedocode:
		// [outside: init weights to 0]
		//	sse = 0
		//	foreach (weights(size)) gradient = 0
		//	run foreach(i) training:
		//			result1 = 0;
		//		for (j) from 0 to weights(size-1)
		//			result1 += weights[j] * training[i][j]
		//			result2 = result1 - training[i][weights(size-1)]
		//		sse += 0.5 * pow(result2, 2)
		//		for (j) from 0 to training[i] size-2
		//			gradient[j] += result2 * training[i][j]
		//	foreach(i) weights
		//		weights[i] = weights[i] - (learnrate) * gradient[i]
		//	[return from function, then store sse in vector.  End program by outputting error vector.]
		sse = 0;
		for(vector<double>::size_type i = 0; i<weights.size(); i++){
			gradient[i] = 0;
		}
		for(vector<vector<double>>::size_type i = 0; i<training.size(); i++){
			result1 = 0;
			for(vector<double>::size_type j = 0; j<weights.size(); j++){
				result1 += weights[j] * training[i][j];
				result2 = result1 - training[i][weights.size()];
			}
			sse += 0.5 * pow(result2, 2);
			for(vector<double>::size_type j = 0; j<weights.size(); j++){
				gradient[j] += result2 * training[i][j];
			}
		}
		for(vector<double>::size_type i = 0; i<weights.size(); i++){
			weights[i] = weights[i] - learningRate * gradient[i];
		}

	return sse;
}

// takes initial weights, test & training data (already randomized), returns weight vector & total SSE error
double stochasticGradientDescent(
	vector<vector<double>> training,
	vector<double> &weights,
	double learningRate
	) {
		double result1, result2, sse;
		vector<double> gradient (weights.size());

		//  psuedocode:
		// [outside: init weights to 0]
		//	sse = 0
		//	foreach (weights(size)) gradient = 0
		//	run foreach(i) training:
		//			result1 = 0;
		//		for (j) from 0 to weights(size-1)
		//			result1 += weights[j] * training[i][j]
		//			result2 = result1 - training[i][weights(size-1)]
		//		sse += 0.5 * pow(result2, 2)
		//		for (j) from 0 to training[i] size-2
		//			gradient[j] += result2 * training[i][j]
		//		foreach(j) weights
		//			weights[j] = weights[j] - (learnrate) * gradient[j]
		//
		//	[return from function, then store sse in vector.  End program by outputting error vector.]
		sse = 0;
		for(vector<double>::size_type i = 0; i<weights.size(); i++){
			gradient[i] = 0;
		}
		for(vector<vector<double>>::size_type i = 0; i<training.size(); i++){
			result1 = 0;
			for(vector<double>::size_type j = 0; j<weights.size(); j++){
				result1 += weights[j] * training[i][j];
				result2 = result1 - training[i][weights.size()];
			}
			sse += 0.5 * pow(result2, 2);
			for(vector<double>::size_type j = 0; j<weights.size(); j++){
				gradient[j] += result2 * training[i][j];
			}
			for(vector<double>::size_type j = 0; j<weights.size(); j++){
				weights[j] = weights[j] - learningRate * gradient[j];
			}
		}

	// note: for simplicity, this is the sse per epoch.
	// more formally, an sse could be produced per update step
	// we chose this method for consistency of comparison with the batch algorithm
	return sse;
}

double testGradientDescent(
		vector<vector<double>> test,
		vector<double> &weights
	){
		double sse, result1, result2;

		sse = 0;
		for(vector<vector<double>>::size_type i = 0; i<test.size(); i++){
			result1 = 0;

			for(vector<double>::size_type j = 0; j<weights.size(); j++){
				result1 += weights[j] * test[i][j];
				result2 = result1 - test[i][weights.size()];
			}
			sse += 0.5 * pow(result2, 2);
		}

		return sse;
}

// runs all the batch perceptron-related stuff, from file input to eventual output (TODO)
void batchPerceptron(
	void
	) {
	// read in classification training data
	vector<pair<int, vector<double>>> twoGaussian;
	ifstream twoGaussianCSV("twogaussian.csv");
	while(twoGaussianCSV.good()) {
		int y;
		double x1, x2;
		twoGaussianCSV >> y;
		twoGaussianCSV.get();
		twoGaussianCSV >> x1;
		twoGaussianCSV.get();
		twoGaussianCSV >> x2;
		twoGaussianCSV.get();

		std::vector<double> example;
		example.push_back(1.0f); // dummy feature for w0
		example.push_back(x1);
		example.push_back(x2);

		twoGaussian.push_back(make_pair(y, example));
	}

	vector<double> errors;
	double currentError;
	vector<int> misClassHistory;
	int misClass;

	// initial weight 0 for 2 features
	vector<double> weights(twoGaussian[0].second.size(), 0);

	do {
		currentError = batchPerceptronEpoch(twoGaussian, weights, misClass);
		errors.push_back(currentError);
		misClassHistory.push_back(misClass);
	} while(abs(currentError) > 0.01); // never converges to <.06, but <.07 works
	// TODO: write weights, currentError to CSV files
}

// takes initial weights, training data, returns weight vector & error (norm of delta)
// runs through data set once
double batchPerceptronEpoch(
	const vector<pair<int, vector<double>>> training,
	vector<double>& weights,
	int & misClass
	) {
	// delta vector as 0s
	vector<double> delta(weights.size(), 0);
	misClass = 0;

	// go through all examples
	for(auto example : training) {
		// make sure none of the examples are invalid
		assert(weights.size() == example.second.size());

		double um = 0;
		for(int i = 0; i < weights.size(); i++) {
			um += (weights[i] * example.second[i]);
		}
		if((example.first * um) <= 0) {
			misClass++;
			for(int i = 0; i < delta.size(); i++) {
				delta[i] -= example.first * example.second[i];
			}
		}
	}

	double norm = 0;
	for(int i = 0; i < delta.size(); i++) {
		delta[i] /= training.size();
		weights[i] -= 1.0*delta[i]; // learning rate = 1
		norm += pow(delta[i], 2); // sum of squares for vector norm
	}
	norm = sqrt(norm); // sqrt of sum of squares for vector norm


	return norm;
}

// takes initial weights, training data, returns weight vector & total SSE error
void votedPerceptron(
	void
	) {
	// read in classification training data
	vector<pair<int, vector<double>>> dataset;
	ifstream fin("data.txt");
	while(fin.good()) {
		int y;
		double x1, x2,x3,x4,x5;
		fin >> y;
		fin.get();
		fin >> x1;
		fin.get();
		fin >> x2;
		fin.get();
		fin >> x3;
		fin.get();
		fin >> x4;
		fin.get();
		fin >> x5;
		fin.get();

		std::vector<double> example;
		example.push_back(1.0f);
		example.push_back(x1);
		example.push_back(x2);
		example.push_back(x3);
		example.push_back(x4);
		example.push_back(x5);

		irisData.push_back(make_pair(y, example));
	}

	vector<double> vWeights(dataset[0].second.size(), 0);
	vector<vector<double>> weightHistory;
	weightHistory.push_back(vWeights);
	vector<int> c(1, 0); // c_0 = 0
	int n = 0; // n = number of weight sets
	for(int t = 0; t < 100; t++) {
		// randomize for each epoch
		random_shuffle(irisData.begin(), irisData.end());
		c.push_back(0);

		for(auto example : irisData) {
			double um = 0;
			for(int i = 0; i < vWeights.size(); i++) {
				um += (vWeights[i] * example.second[i]);
			}
			if((um * example.first) <= 0) {
				for(int i = 0; i < vWeights.size(); i++) {
					vWeights[i] += (example.second[i] * example.first);
				}
				weightHistory.push_back(vWeights);
				n++; // still equal to weightHistory.size() I think
				c.push_back(0);
			}
			else {
				c[n]++;
			}
		}
	}

	// time to vote!
	// want to see each vote from history of size 1 to n
	vector<int> errorHistory(n, 0);
	for(int i = 0; i < n; i++) {
		// voting on all examples
		for(auto example : dataset) {
			// all weight sets up to this point will vote
			double voteResult = 0;
			for(int j = 0; j <= i; j++) {
				double thisVote = 0;
				for(int k = 0; k < vWeights.size(); k++) {
					thisVote += weightHistory[j][k] * example.second[k];
				}
				voteResult += sign(thisVote);
			}
			if(example.first != sign(voteResult)) {
				errorHistory[i]++;
			}
		}
	}
}
*/

// CS534-Imp1.cpp : Defines the entry point for the console application.
//

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <assert.h>
#include "Impl1.hpp"

using namespace std;


int main()
{
	//doGradients();

	//batchPerceptron();

	votedPerceptron();

	return 0;
}

void doGradients(
	void
	) {
	// loop var
	int i;

	// read in regression training
	double gradientLearningRate;
	vector<vector<double>> trainingData;

	ifstream trainingFile("regression-train.csv");
	while(trainingFile.good()) {
		double x1, x2, x3, y;
		trainingFile >> x1;
		trainingFile.get();
		trainingFile >> x2;
		trainingFile.get();
		trainingFile >> x3;
		trainingFile.get();
		trainingFile >> y;
		trainingFile.get();

		std::vector<double> example;
		// first parameter is added to allow for w_0
		example.push_back(1);
		example.push_back(x1);
		example.push_back(x2);
		example.push_back(x3);
		example.push_back(y);

		//cout << example[0] << " " << example[1] << " " << example[2] << " " << example[3] << " " << example[4] << " " << example.size() << endl;

		trainingData.push_back(example);
	}
	// remove duplicate final element
	trainingData.pop_back();


	vector<double> batchGradientWeights (trainingData[0].size()-1);
	vector<double> stochasticGradientWeights (trainingData[0].size()-1);
	vector<double> batchGradientTrainingError;
	vector<double> stochasticGradientTrainingError;

	//init weight vectors
	for(vector<double>::size_type i = 0; i<trainingData[0].size()-1; i++){
		batchGradientWeights[i] = 0;
		stochasticGradientWeights[i] = 0;
	}

	// run batch gradient descent training
	for(i = 0; i<num_epochs; i++){
		gradientLearningRate = (0.5f / trainingData.size());
		batchGradientTrainingError.push_back(batchGradientDescent(trainingData, batchGradientWeights, gradientLearningRate));
	}
	// run stochastic gradient descent training
	for(i = 0; i<num_epochs; i++){
		// randomize order for stochastic
		random_shuffle(trainingData.begin(), trainingData.end());
		stochasticGradientTrainingError.push_back(stochasticGradientDescent(trainingData, stochasticGradientWeights, gradientLearningRate));
	}

	// read in regression test
	vector<vector<double>> testData;
	ifstream testFile("regression-test.csv");
	while(testFile.good()) {
		double x1, x2, x3, y;
		testFile >> x1;
		testFile.get();
		testFile >> x2;
		testFile.get();
		testFile >> x3;
		testFile.get();
		testFile >> y;
		testFile.get();

		std::vector<double> example;
		// first parameter is added to allow for w_0
		example.push_back(1);
		example.push_back(x1);
		example.push_back(x2);
		example.push_back(x3);
		example.push_back(y);

		testData.push_back(example);
	}
	// remove duplicate final element
	testData.pop_back();

	random_shuffle(testData.begin(), testData.end());

	double batchGradientTestError;
	double stochasticGradientTestError;

	// run accuracy test trials
	batchGradientTestError = testGradientDescent(testData, batchGradientWeights);
	stochasticGradientTestError = testGradientDescent(testData, stochasticGradientWeights);


	// DO THIS: output trial results in some format
	ofstream gradientOut;
	gradientOut.open("gradientOut.txt");
	gradientOut << "gradient descent learning weight: " << gradientLearningRate * trainingData.size() << "/" << trainingData.size() << endl;
	gradientOut << "batch gradient weights: " << batchGradientWeights[0] << ", " << batchGradientWeights[1] << ", " << batchGradientWeights[2] << ", " << batchGradientWeights[3] << endl;
	gradientOut << "batch gradient sse: " << endl;
	for(vector<double>::size_type i = 0; i<batchGradientTrainingError.size(); i++){
		 gradientOut << batchGradientTrainingError[i] << endl;
	}
	gradientOut << "batch gradient test sse: " << batchGradientTestError << endl;

	gradientOut << "stochastic gradient weights: " << stochasticGradientWeights[0] << ", " << stochasticGradientWeights[1] << ", " << stochasticGradientWeights[2] << ", " << stochasticGradientWeights[3] << endl;
	gradientOut << "stochastic gradient sse: " << endl;
	for(vector<double>::size_type i = 0; i<stochasticGradientTrainingError.size(); i++){
		gradientOut << stochasticGradientTrainingError[i] << endl;
	}
	gradientOut << "stochastic gradient test sse: " << stochasticGradientTestError << endl;
	gradientOut.close();


}

// takes initial weights, test & training data, returns weight vector & total SSE error
double batchGradientDescent(
	vector<vector<double>> training,
	vector<double> &weights,
	double learningRate
	) {
		double result1, result2, sse;
		vector<double> gradient (weights.size());

		//  psuedocode:
		// [outside: init weights to 0]
		//	sse = 0
		//	foreach (weights(size)) gradient = 0
		//	run foreach(i) training:
		//			result1 = 0;
		//		for (j) from 0 to weights(size-1)
		//			result1 += weights[j] * training[i][j]
		//			result2 = result1 - training[i][weights(size-1)]
		//		sse += 0.5 * pow(result2, 2)
		//		for (j) from 0 to training[i] size-2
		//			gradient[j] += result2 * training[i][j]
		//	foreach(i) weights
		//		weights[i] = weights[i] - (learnrate) * gradient[i]
		//	[return from function, then store sse in vector.  End program by outputting error vector.]
		sse = 0;
		for(vector<double>::size_type i = 0; i<weights.size(); i++){
			gradient[i] = 0;
		}
		for(vector<vector<double>>::size_type i = 0; i<training.size(); i++){
			result1 = 0;
			for(vector<double>::size_type j = 0; j<weights.size(); j++){
				result1 += weights[j] * training[i][j];
				result2 = result1 - training[i][weights.size()];
			}
			sse += 0.5 * pow(result2, 2);
			for(vector<double>::size_type j = 0; j<weights.size(); j++){
				gradient[j] += result2 * training[i][j];
			}
		}
		for(vector<double>::size_type i = 0; i<weights.size(); i++){
			weights[i] = weights[i] - learningRate * gradient[i];
		}

	return sse;
}

// takes initial weights, test & training data (already randomized), returns weight vector & total SSE error
double stochasticGradientDescent(
	vector<vector<double>> training,
	vector<double> &weights,
	double learningRate
	) {
		double result1, result2, sse;
		vector<double> gradient (weights.size());

		//  psuedocode:
		// [outside: init weights to 0]
		//	sse = 0
		//	foreach (weights(size)) gradient = 0
		//	run foreach(i) training:
		//			result1 = 0;
		//		for (j) from 0 to weights(size-1)
		//			result1 += weights[j] * training[i][j]
		//			result2 = result1 - training[i][weights(size-1)]
		//		sse += 0.5 * pow(result2, 2)
		//		for (j) from 0 to training[i] size-2
		//			gradient[j] += result2 * training[i][j]
		//		foreach(j) weights
		//			weights[j] = weights[j] - (learnrate) * gradient[j]
		//
		//	[return from function, then store sse in vector.  End program by outputting error vector.]
		sse = 0;
		for(vector<double>::size_type i = 0; i<weights.size(); i++){
			gradient[i] = 0;
		}
		for(vector<vector<double>>::size_type i = 0; i<training.size(); i++){
			result1 = 0;
			for(vector<double>::size_type j = 0; j<weights.size(); j++){
				result1 += weights[j] * training[i][j];
				result2 = result1 - training[i][weights.size()];
			}
			sse += 0.5 * pow(result2, 2);
			for(vector<double>::size_type j = 0; j<weights.size(); j++){
				gradient[j] += result2 * training[i][j];
			}
			for(vector<double>::size_type j = 0; j<weights.size(); j++){
				weights[j] = weights[j] - learningRate * gradient[j];
			}
		}

	// note: for simplicity, this is the sse per epoch.
	// more formally, an sse could be produced per update step
	// we chose this method for consistency of comparison with the batch algorithm
	return sse;
}

double testGradientDescent(
		vector<vector<double>> test,
		vector<double> &weights
	){
		double sse, result1, result2;

		sse = 0;
		for(vector<vector<double>>::size_type i = 0; i<test.size(); i++){
			result1 = 0;

			for(vector<double>::size_type j = 0; j<weights.size(); j++){
				result1 += weights[j] * test[i][j];
				result2 = result1 - test[i][weights.size()];
			}
			sse += 0.5 * pow(result2, 2);
		}

		return sse;
}

// runs all the batch perceptron-related stuff, from file input to eventual output (TODO)
void batchPerceptron(
	void
	) {
	// read in classification training data
	vector<pair<int, vector<double>>> twoGaussian;
	ifstream twoGaussianCSV("twogaussian.csv");
	while(twoGaussianCSV.good()) {
		int y;
		double x1, x2;
		twoGaussianCSV >> y;
		twoGaussianCSV.get();
		twoGaussianCSV >> x1;
		twoGaussianCSV.get();
		twoGaussianCSV >> x2;
		twoGaussianCSV.get();

		std::vector<double> example;
		example.push_back(1.0f); // dummy feature for w0
		example.push_back(x1);
		example.push_back(x2);

		twoGaussian.push_back(make_pair(y, example));
	}
	twoGaussianCSV.close();

	vector<double> errors;
	double currentError;
	vector<int> misClassHistory;
	int misClass;

	// initial weight 0 for 2 features
	vector<double> weights(twoGaussian[0].second.size(), 0);

	do {
		currentError = batchPerceptronEpoch(twoGaussian, weights, misClass);
		errors.push_back(currentError);
		misClassHistory.push_back(misClass);
	} while(abs(currentError) > 0.01);
	// TODO: write weights, currentError to CSV files

	ofstream twoGaussianWeights("twoGaussianWeights.csv");
	twoGaussianWeights << weights[0] << "," << weights[1] << "," << weights[2];
	twoGaussianWeights.close();

	ofstream twoGaussianHistory("twoGaussianHistory.csv");
	for(int i = 0; i < misClassHistory.size(); i++) {
		twoGaussianHistory << i << "," << misClassHistory[i] << "\n";
	}
	twoGaussianHistory.close();
}

// takes initial weights, training data, returns weight vector & error (norm of delta)
// runs through data set once
double batchPerceptronEpoch(
	const vector<pair<int, vector<double>>> training,
	vector<double>& weights,
	int & misClass
	) {
	// delta vector as 0s
	vector<double> delta(weights.size(), 0);
	misClass = 0;

	// go through all examples
	for(auto example : training) {
		// make sure none of the examples are invalid
		assert(weights.size() == example.second.size());

		double um = 0;
		for(int i = 0; i < weights.size(); i++) {
			um += (weights[i] * example.second[i]);
		}
		if((example.first * um) <= 0) {
			misClass++;
			for(int i = 0; i < delta.size(); i++) {
				delta[i] -= example.first * example.second[i];
			}
		}
	}

	double norm = 0;
	for(int i = 0; i < delta.size(); i++) {
		delta[i] /= training.size();
		weights[i] -= 1.0*delta[i]; // learning rate = 1
		norm += pow(delta[i], 2); // sum of squares for vector norm
	}
	norm = sqrt(norm); // sqrt of sum of squares for vector norm


	return norm;
}

// takes initial weights, training data, returns weight vector & total SSE error
void votedPerceptron(
	void
	) {
	// read in classification training data
	vector<pair<int, vector<double>>> irisData;
	ifstream irisCSV("iris-twoclass.csv");
	while(irisCSV.good()) {
		int y;
		double x1, x2;
		irisCSV >> y;
		irisCSV.get();
		irisCSV >> x1;
		irisCSV.get();
		irisCSV >> x2;
		irisCSV.get();

		std::vector<double> example;
		example.push_back(1.0f);
		example.push_back(x1);
		example.push_back(x2);

		irisData.push_back(make_pair(y, example));
	}
	irisCSV.close();

	vector<double> vWeights(irisData[0].second.size(), 0);
	vector<vector<double>> weightHistory;
	weightHistory.push_back(vWeights);
	vector<int> c(1, 0); // c_0 = 0
	int n = 0; // n = number of weight sets
	for(int t = 0; t < 100; t++) {
		// randomize for each epoch
		random_shuffle(irisData.begin(), irisData.end());
		c.push_back(0);

		for(auto example : irisData) {
			double um = 0;
			for(int i = 0; i < vWeights.size(); i++) {
				um += (vWeights[i] * example.second[i]);
			}
			if((um * example.first) <= 0) {
				for(int i = 0; i < vWeights.size(); i++) {
					vWeights[i] += (example.second[i] * example.first);
				}
				weightHistory.push_back(vWeights);
				n++; // still equal to weightHistory.size() I think
				c.push_back(0);
			}
			else {
				c[n]++;
			}
		}
	}

	// time to vote!
	// want to see each vote from history of size 1 to n
	vector<int> errorHistory(n, 0);
	for(int i = 0; i < n; i++) {
		// voting on all examples
		for(auto example : irisData) {
			// all weight sets up to this point will vote
			double voteResult = 0;
			for(int j = 0; j <= i; j++) {
				double thisVote = 0;
				for(int k = 0; k < vWeights.size(); k++) {
					thisVote += weightHistory[j][k] * example.second[k];
				}
				voteResult += c[j] * sign(thisVote);
			}
			if(example.first != sign(voteResult)) {
				errorHistory[i]++;
			}
		}
	}

	ofstream irisHistory("irisHistory.csv");
	for(int i = 0; i < errorHistory.size(); i++) {
		irisHistory << i << "," << errorHistory[i] << "\n";
	}
	irisHistory.close();

	// find decision boundary
	vector<pair<int, vector<double>>> boundaryData;
	// feature 1 ranges from 1 to 7, feature 2 from 0 to 2.5
	for(int i = 100; i < 700; i++) {
		for(int j = 0; j < 300; j++) {
			vector<double> fakeFeatures;
			fakeFeatures.push_back(1.0f);
			fakeFeatures.push_back(i/100.0f);
			fakeFeatures.push_back(j/100.0f);
			boundaryData.push_back(make_pair(0, fakeFeatures));
		}
	}
	for(auto & example : boundaryData) {
		// all weight sets up to this point will vote
		double voteResult = 0;
		for(int j = 0; j <= n; j++) {
			double thisVote = 0;
			for(int k = 0; k < vWeights.size(); k++) {
				thisVote += weightHistory[j][k] * example.second[k];
			}
			voteResult += c[j] * sign(thisVote);
		}
		example.first = sign(voteResult);
	}
	ofstream irisBoundary("irisBoundary.csv");
	for(int i = 0; i < boundaryData.size(); i++) {
		irisBoundary << boundaryData[i].first << "," << boundaryData[i].second[1] << "," << boundaryData[i].second[2] << "\n";
	}
	irisBoundary.close();

	// find average weight
	vector<double> wAvg(vWeights.size(), 0);
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < vWeights.size(); j++) {
			wAvg[j] += c[i] * weightHistory[i][j];
		}
	}
	ofstream irisAvg("irisAvg.csv");
	irisAvg << wAvg[0] << "," << wAvg[1] << "," << wAvg[2];
}
