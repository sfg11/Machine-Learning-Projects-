
/*1. Title: Auto-Mpg Data
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
double alpha= 0.0001; // corresponds to the size of the steps you wish to take

*/

#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<math.h>
#include<vector>
#include <sstream>
#include "LinearRegression.h"
#include "auxiliary.h"
using namespace std;
/*
m = length(y);
costs = zeros(m,1); %// New

for iter =1:1:iterations
delta=zeros(2,1); %// Place here
for i=1:1:m
   delta(1,1)= delta(1,1)+( X(i,:)*theta - y(i,1))  ;
   delta(2,1)=delta(2,1)+ (( X(i,:)*theta - y(i,1))*X(i,2)) ;
end
theta= theta-( delta*(alpha/m) );
costs(iter) = computeCost(X,y,theta); // New
end
end

vector< vector<double> > readMatrix(string filename){
	ifstream f;
	string line;
	stringstream ss;
	vector< vector<double> > M;

	f.open(filename);
	while ( getline (f,line) )
    {
    	double value;
    	vector<double> V;
      	ss << line;
      	while(ss>>value){
      		V.push_back(value);
      	}
      	M.push_back(V);
      	ss.clear();
    }
    f.close();

    return M;
}
*/
/*
template <typename T>
void printVector( vector<T> V){
	cout<<"[ ";
	for(int i = 0 ; i < V.size() ; i++){
		cout<<V[i]<<" ";
	}
	cout<<"]"<<endl;
}

int main(){

	vector< vector<double> > B = readMatrix("data/train.txt");
	vector< vector<double> > T = readMatrix("data/test.txt");
	vector<double> Y,W;

	for(int i = 0; i < B.size() ; i++){
		Y.push_back( B[i].back() );
		B[i].pop_back();
	}


	LinearRegression *lr = new LinearRegression();

	lr->adaptiveAlpha = true;
	lr->alpha = 0.5;
	lr->iterationCount = 100;
	lr->featureScaling = true;

	cout<<"---------- TRAINING ----------"<<endl;
	cout<<"Alpha: "<<lr->alpha<<endl;
	cout<<"Iteration Count: "<<lr->iterationCount<<endl;
	cout<<"Adaptive Alpha: "<<((lr->adaptiveAlpha)?("Yes"):("No"))<<endl;
	cout<<"Feature Scaling: "<<((lr->featureScaling)?("Yes"):("No"))<<endl;
	cout<<"Cost: "<<lr->train(B,Y)<<endl;
	W = lr->getWeights();
	cout<<"Weights: ";
	printVector(W);

	cout<<"\n---------- TEST ----------"<<endl;
	for (int i = 0; i < T.size(); i++)
	{
		cout<<"Prediction from: ";
		printVector(T[i]);
		cout<<"Result: "<<lr->predict(T[i])<<endl<<endl;
	}

	return 0;
}


double LinearRegression::h(vector<double> &X){
	vector<double> V = multiplyVectors(X,W);
	return sumVectorValues( V );
}

double LinearRegression::error( vector<double> &X, double y){
	return h(X)-y;
}

double LinearRegression::cost( vector< vector<double> > &A, vector<double>&Y){
	double cost = 0;

	for(int i = 0 ; i < A.size() ; i++){
		cost += pow( error( A[i], Y[i] ), 2 );
	}

	return cost / ( 2 * A.size() );
}

vector<double> LinearRegression::costDerivativeVector( vector< vector<double> > &A, vector<double>&Y){
	vector<double> D(W.size(),0);

	for(int i = 0 ; i < W.size() ; i++){
		for(int j = 0 ; j < A.size() ; j++){
			D[i] += error( A[j], Y[j] )*A[j][i];
		}
		D[i] = D[i]/A.size();
	}

	return D;
}

double LinearRegression::gradient_descent(vector< vector<double> > &A, vector<double>&Y){
	double pCost,cCost;

	pCost = cCost = cost(A,Y);

	for(int i = 0 ; i < iterationCount ; i++){
		vector<double> D = costDerivativeVector(A,Y);
		D = multiplyVectorWithScalar( D, alpha);
		W = subtractVectors( W, D );

		if(adaptiveAlpha){
			pCost = cCost;
			cCost = cost(A,Y);
			if( pCost < cCost ){
				alpha = 0.9*alpha;
			}
		}

	}
	return cost(A,Y);
}

vector<double> LinearRegression::scaleFeatures( vector<double> &I){
	vector<double> Z = subtractVectors( I , M );
	Z = divideVectors( Z , R );
	return Z;
}

LinearRegression::LinearRegression(){

	alpha = 0.001;
	iterationCount = 10;
	adaptiveAlpha = false;
	featureScaling = false;

}

double LinearRegression::train(vector< vector<double> > &B, vector<double> &Y){
	vector< vector<double> > A(B);

	if(featureScaling){
		M = calculateMeanVector(B);
		R = calculateRangeVector(B);
	}

	for(int i = 0; i < A.size(); i++){
		if(featureScaling) A[i] = scaleFeatures(A[i]);
		A[i].push_back(1);
	}
	W.resize(A[0].size(),0);

	return gradient_descent(A,Y);
}

double LinearRegression::predict(vector<double> &I){
	vector<double> Z(I);
	if(featureScaling) Z = scaleFeatures(Z);
	Z.push_back(1);
	return h(Z);
}

vector<double> LinearRegression::getWeights(){
	return W;
}
*/
double LinearRegression::h(vector<double> &X){
	vector<double> V = multiplyVectors(X,W);
	return sumVectorValues( V );
}

double LinearRegression::error( vector<double> &X, double y){
	return h(X)-y;
}

double LinearRegression::cost( vector< vector<double> > &A, vector<double>&Y){
	double cost = 0;

	for(int i = 0 ; i < A.size() ; i++){
		cost += pow( error( A[i], Y[i] ), 2 );
	}

	return cost / ( 2 * A.size() );
}

vector<double> LinearRegression::costDerivativeVector( vector< vector<double> > &A, vector<double>&Y){
	vector<double> D(W.size(),0);

	for(int i = 0 ; i < W.size() ; i++){
		for(int j = 0 ; j < A.size() ; j++){
			D[i] += error( A[j], Y[j] )*A[j][i];
		}
		D[i] = D[i]/A.size();
	}

	return D;
}

double LinearRegression::gradient_descent(vector< vector<double> > &A, vector<double>&Y){
	double pCost,cCost;

	pCost = cCost = cost(A,Y);

	for(int i = 0 ; i < iterationCount ; i++){
		vector<double> D = costDerivativeVector(A,Y);
		D = multiplyVectorWithScalar( D, alpha);
		W = subtractVectors( W, D );

		if(adaptiveAlpha){
			pCost = cCost;
			cCost = cost(A,Y);
			if( pCost < cCost ){
				alpha = 0.9*alpha;
			}
		}

	}
	return cost(A,Y);
}

vector<double> LinearRegression::scaleFeatures( vector<double> &I){
	vector<double> Z = subtractVectors( I , M );
	Z = divideVectors( Z , R );
	return Z;
}

LinearRegression::LinearRegression(){

	alpha = 0.01;
	iterationCount = 1000;
	adaptiveAlpha = false;
	featureScaling = false;

}

double LinearRegression::train(vector< vector<double> > &B, vector<double> &Y){
	vector< vector<double> > A(B);

	if(featureScaling){
		M = calculateMeanVector(B);
		R = calculateRangeVector(B);
	}

	for(int i = 0; i < A.size(); i++){
		if(featureScaling) A[i] = scaleFeatures(A[i]);
		A[i].push_back(1);
	}
	W.resize(A[0].size(),0);

	return gradient_descent(A,Y);
}

double LinearRegression::predict(vector<double> &I){
	vector<double> Z(I);
	if(featureScaling) Z = scaleFeatures(Z);
	Z.push_back(1);
	return h(Z);
}

vector<double> LinearRegression::getWeights(){
	return W;
}
