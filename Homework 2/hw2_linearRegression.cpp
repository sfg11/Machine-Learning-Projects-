//HW: #2


#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
const float a = 0.006; // learning rate
const int NUM_INSTANCES = 398, NUM_FEATURES = 6;
float y[NUM_INSTANCES]; // predict feature
float theta[NUM_FEATURES+1]; // the finding theta (includingtheta 0)
float Inputs[NUM_INSTANCES][NUM_FEATURES]; // input array
float minimum[NUM_FEATURES], maximum[NUM_FEATURES];
/* Calculate minimum for a specific feature at index n*/
float minimum_input( float inputs[][NUM_FEATURES], int n)
{
  float minimum = Inputs[0][n];
  for(int i=1;i<NUM_INSTANCES;i++)
  {
    if(Inputs[i][n] < minimum)
    {
      minimum = Inputs[i][n];
    }
  }
  return minimum;
}
/* Calculate maximum for a specific feature at index n */
float maximum_input ( float Inputs[][NUM_FEATURES], int n )
{
  float maximum = Inputs[0][n];
  for(int i=1;i<NUM_INSTANCES;i++)
  {
    if(Inputs[i][n] > maximum)
    {
      maximum = Inputs[i][n];
    }
  }
  return maximum;
}
//Normalize inputs
void normalization ( float Inputs[][NUM_FEATURES], int size)
{
  for(int i=1;i<NUM_FEATURES;i++)
  {
    minimum[i] = minimum_input(Inputs,i);
    maximum[i] = maximum_input(Inputs,i);
  }
  for(int i=1;i<NUM_FEATURES;i++)
  {
    for(int j=0;j<size;j++)
    {
      Inputs[j][i] = (Inputs[j][i] - minimum[i])/
      (maximum[i] - minimum[i]);
    }
  }
}
//Normalize test data
void normalizeTestSample ( float Inputs[][NUM_FEATURES], int
  size)
  {
    for(int i=1;i<NUM_FEATURES;i++)
    {
      for(int j=0;j<size;j++)
      {
        Inputs[j][i] = (Inputs[j][i] - minimum[i])/
        (maximum[i] - minimum[i]);
      }
    }
  }
  /*
  Calculate the current_h due to current thetas and the instance
  */
  float Current_h(int n)
  {
    float current_h = theta[0];
    for(int i=1;i<NUM_FEATURES;i++)
    {
      current_h += theta[i]*Inputs[n][i];
    }
    return current_h;
  }
  /* Print a test sample */
  void print_test_samples ( float test[][NUM_FEATURES], int n)
  {
    for(int i = 0; i<n;i++)
    {
      cout << "Test sample " << i+1 << ": (";
      for(int j=0;j<NUM_FEATURES;j++)
      {
        if(j==0)
        cout << " ? ";
        else
        cout << test[i][j] <<" ";
      }
      cout << ")" << endl;
    }
  }
  int main()
  {
    string line;
    int counter = 0;
    float h;
    ifstream inFile;
    inFile.open("linear_regression_data.txt");
    if(!inFile)
    {
      cout <<"Error opening the input file!\n";
      return 1;
    }
    cout <<"/**********Linear regression Program***********/\n";
    while(!inFile.eof() && counter < NUM_INSTANCES)
    {
      Inputs[counter][0] = 1.0;
      inFile >> y[counter]
      >> Inputs[counter][1] >> Inputs[counter][2]
      >> Inputs[counter][3]>> Inputs[counter][4]
      >> Inputs[counter][5];
      counter++;
    }
    /***********************************************************************/
    // Testing part: Before normalization
    for(int i=0;i<counter;i++)
    {
      cout << i+1 <<"- " << y[i] <<" ";
      for(int j=0;j<NUM_FEATURES;j++)
      {
        cout << Inputs[i][j] <<" ";
      }
      cout << endl;
    }
    cout << "counter: " << counter << endl;
    /************************************************************************/
    //Normalize data
    normalization(Inputs, NUM_INSTANCES);
    /***********************************************************************/
    //Printing out maximum and minimum
    for(int i=0;i<NUM_FEATURES;i++)
    {
      cout << minimum[i] <<" " <<maximum[i] << endl;
    }
    cout <<"After normalization...\n";
    for(int i=0;i<counter;i++)
    {
      cout << i+1 <<"- " << y[i] <<" ";
      for(int j=0;j<NUM_FEATURES;j++)
      {
        cout << Inputs[i][j] <<" ";
      }
      cout << endl;
    }
    /************************************************************************/
    // Initialize all thetas to 0 at the first time
    for(int i=0;i<NUM_FEATURES +1 ; i++)
    {
      theta[i] = 0.0;
    }
    // Linear regression algorithm for finding thetas
    float sum;
    for(int k=0; k<100000; k++) // 100000 iterations
    {
      for(int j=0; j<NUM_FEATURES; j++)
      {
        sum = 0;
        for(int i=0; i<NUM_INSTANCES; i++)
        {
          h= Current_h(i);
          sum += (y[i] - h) * Inputs[i][j];
        }
        theta[j] = theta[j] + a * sum;
      }
    }
    const int NUM_SAMPLES = 3;
    float predict_y[NUM_SAMPLES];
    //test samples (x0=1)
    float test_samples[NUM_SAMPLES][NUM_FEATURES] ={{1,4,95,92,2043,19.1},
    {1,6,168,96,2981,14.7},
    {1,4,98,68,2147,18.3}};
    /***********************************************************************
    // Use for testing
    {1,8,307,130,3504,12},
    {1,4,119,82,2720,19.4},
    {1,4,135,84,2295,11.6},
    {1,4,120,79,2625,18.6}};
    /***********************************************************************/
    //Printing all test samples
    cout << "\n\nTest Sample: "<<"(cylinders displacement horsepower weight acceleration)\n\n";
    print_test_samples(test_samples,NUM_SAMPLES);
    normalizeTestSample(test_samples,NUM_SAMPLES);
    /***********************************************************************/
    cout <<"After normalization\n";
    for(int i=0;i<NUM_SAMPLES;i++)
    {
      for(int j=0;j<NUM_FEATURES;j++)
      {
        cout << test_samples[i][j] <<" ";
      }
      cout << endl;
    }
    /***********************************************************************/
    // Get the predicted values for them
    for (int i=0;i<NUM_SAMPLES;i++){
      predict_y[i] = 0;
      for(int j=0;j<NUM_FEATURES;j++) {
        predict_y[i] += theta[j]*test_samples[i][j];
      }
      cout <<"\nPredicted mpg for test sample " << i+1 << " is: " << predict_y[i] << endl;
    }
    return 0;
  }
