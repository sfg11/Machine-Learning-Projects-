#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <vector>
#include <cstdlib>

#include "iris.h"
#include "knn.h"

using namespace std;

vector<Iris*> readFile(const string filePath){
  ifstream fin;
  fin.open(filePath.c_str()); // use c_str() to return const char* pointer to the string
  vector<Iris*> dataSet;
  while(!fin.eof()){
    string l; // read new line and build stream
    if(!getline(fin, l)){
      break; // ignore empty lines at end
    }
    stringstream lineStream(l);
    string item[5];
    for(int i =0; i < 5; ++i){
      getline(lineStream, item[i], ',');
    }
    float sepalLength = strtof(item[0].c_str(), 0);
    float sepalWidth = strtof(item[1].c_str(), 0);
    float petalLength = strtof(item[2].c_str(), 0);
    float petalWidth = strtof(item[3].c_str(), 0);
    string typeName = item[4];
    // push into vector/ build the object
    dataSet.push_back(new Iris(sepalLength, sepalWidth, petalLength, petalWidth, typeName));
  } // end while
  fin.close(); // close file
  return dataSet;
}

  int main(){

    int k = 0;
    bool isValid = false;
    bool normalize = 0;

    cout << "Iris foo" << endl;

    vector<Iris*> trainingData;
    vector<Iris*> testingData;

    cout << "Reading iris training data set... \n";

    trainingData = readFile("iris.data");
    cout << " The number of instances avaliable for training: " << trainingData.size() << endl;

    cout << "Reading the test examples... \n";
    testingData = readFile("iris-testing.data");
    cout << " The number of testing examples avaliable: " << testingData.size() << endl;
    cout << "KNN...\n";

    while(!isValid){
      cout << "Enter k to predict 1-NN, 3-NN or 5-NN nearest neighbors ";
      cin >> k;
      if(k == 1 || k == 3 || k == 5){
        isValid = true;
      } else {
        cout << "ERROR: Invalid K";
      }
      cout << "Normalizing data...\n";
        normalize = normalize > 1 || normalize < 0 ? 1 : normalize;
    } // end while
    KNN *knnAlgorithm;
    knnAlgorithm = new KNN(trainingData, k, normalize); // create knn object

    cout << "|===============================================|\n";
    cout << "|          Testing Iris DataSet                 |\n";
    cout << "|Iris-setosa | Iris-versicolor | Iris-virginica |\n";
    cout << "|     0      |       1         |     2          |\n";
    cout << "|===============================================|\n";

  int counter = 1;
  int hitCounter;
  hitCounter = 0;

  for (Iris* iris : testingData) {

    int approximation = knnAlgorithm->group(iris->getSepalLength(), iris->getSepalWidth(),
      iris->getPetalLength(), iris->getPetalWidth());

    cout << "Test Run # " << counter << ": ";
    cout << "Approximation -> " << approximation << " ";

    if (approximation == iris->getType()) {
      cout << "(OK)";
      hitCounter++;
    } else {
      cout << "(FAIL)";
    }

    cout << endl;

    counter++;
  }

    return 0;
  }
