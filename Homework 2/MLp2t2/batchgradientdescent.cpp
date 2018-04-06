#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <climits>

using namespace std;

#define SAMPLES 398
#define NEWDATA 3
#define TOTALSIZE 401
#define DIM 5
#define DIMINCLY 6
#define ALPHA 5



// read in data from the provided ifstream
// puts -1 in the MPG placeholders for the test data
void readTrainingData( ifstream & fin, double trainingData[SAMPLES][DIMINCLY] ) {
    string line;
    int count = 0;

    while (getline(fin, line))
    {
        istringstream ss(line);

        for (int i = 0; i < DIMINCLY; ++i) {
            ss >> trainingData[count][i];
        }
        count++;
    }
}

void readTestingData( ifstream & in, double trainingData[SAMPLES][DIMINCLY] ) {
    string line;
    int count = 0;

    while (getline(in, line))
    {
        istringstream ss(line);

        for (int i = 0; i < DIMINCLY; ++i) {
            if (i == 0) {
                ss.ignore(1);
                trainingData[count][i] = -1;
                continue;
            }
            ss >> trainingData[count][i];
        }
        count++;
    }
}

void normalizeTrainingData(double trainingData[SAMPLES][DIMINCLY]) {
    double sums[DIMINCLY] = {0, 0, 0, 0, 0, 0};
    double mins[DIMINCLY] = {INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX};
    double maxs[DIMINCLY] = {INT_MIN, INT_MIN, INT_MIN, INT_MIN, INT_MIN, INT_MIN};

    for (int sample = 0; sample < SAMPLES; sample++) {
        for (int feature = 0; feature < DIMINCLY; feature++) {
            double element = trainingData[sample][feature];
            sums[feature] += element;
            mins[feature] = (element < mins[feature]) ? element : mins[feature];
            maxs[feature] = (element > maxs[feature]) ? element : maxs[feature];
        }
    }

    for (int sample = 0; sample < SAMPLES; sample++) {
        for (int feature = 0; feature < DIMINCLY; feature++) {
            double element = trainingData[sample][feature];
            trainingData[sample][feature] = ((element - mins[feature]) / (maxs[feature] - mins[feature]));
        }
    }
}

// initialize the values for theta to 0 for all values
void initializeThetaVector(double thetaVector[DIMINCLY]) {
    for (int i = 1; i < DIM; ++i) {
        thetaVector[i] = 0;
    }
}

void printEverythingPlusOne(double theVector[DIMINCLY+1]) {
    cout << "Thetas: ";
    for (int feature = 0; feature < DIMINCLY; ++feature) {
        cout << feature << ": " << theVector[feature] << "  ";
    }
    cout << endl;
}
void printEverything(double theVector[DIMINCLY]) {
    cout << "Thetas: ";
    for (int feature = 0; feature < DIMINCLY; ++feature) {
        cout << feature << ": " << theVector[feature] << "  ";
    }
    cout << endl;
}


double calculatehThetaXi (double thetaVector[DIMINCLY], double trainingRow[DIMINCLY]) {
    cout << "====================calculateHThetaXi====================" << endl;
    double xi[DIMINCLY];
    for (int i = 0; i < DIMINCLY; ++i) {
        if (i == 0) {
            xi[i] = 1;
        }
        else
            xi[i] = trainingRow[i];
    }
    cout << "----xi----" << endl;
    printEverything(xi);

    double expectedValue = 0;

    cout << "----thetaVector----" << endl;
    printEverything(thetaVector);

    cout << "expectedValue: ";
    for (int i = 0; i < DIMINCLY; ++i) {
        expectedValue += thetaVector[i] * xi[i];
        cout << expectedValue << "  ";
    }
    cout << endl;

    cout << "hThetaXi : " << expectedValue << endl;

    return expectedValue;
}

//
double updateTheta(double thetaVector[DIMINCLY], double trainingData[SAMPLES][DIMINCLY], int feature) {
    double runningTotal = 0;

    cout << "====================updateTheta====================" << endl;

    cout << "----thetaVector----" << endl;

    printEverything(thetaVector);


    for (int i = 0; i < SAMPLES; ++i) {
        // calculate hThetaXi - yi
        double hThetaXi = calculatehThetaXi(thetaVector, trainingData[i]);
        hThetaXi -= trainingData[i][0];

        cout << "hThetaXi - yi in updateTheta: " << hThetaXi << endl;
        // multiply that by xij, as established by feature
        double xij = (feature == 0) ? 1 : trainingData[i][feature];
        hThetaXi *= xij;
        cout << "I'm going to multiply that by xij ( " << xij << " ) = " << hThetaXi << endl;
        // add it to the running total
        cout << "And add it to the sigma value being computed (currently: " << runningTotal << ")" << endl;
        runningTotal += hThetaXi;
        cout << "Now it's : " << runningTotal << endl;
    }

    // return ALPHA * (sigma: all entries (estimated value for x(i) - y_actual) * xji
    return runningTotal;

    // update theta performs the calculation
    // theta_j = theta_j - (sigma: all entries (estimated value for x(i) - y_actual) * xji
}

//look for convergence of theta values
// for every feature, assign the tempTheta[feature] value to be old theta[feature] - (a/m(sum of all of the hypothesis differences))
void findThetas(double thetaVector[DIMINCLY], double trainingData[SAMPLES][DIMINCLY]) {
    bool converged = false;
    double alpha = .001;

    int count = 0;

    double tempThetas[DIMINCLY];
    double deltaThetas[DIMINCLY];
    while (!converged && count < 1000) {
        cout << "\n\n\n\n\n================================================================================" << endl;
        cout << "================================================================================" << endl;
        cout << "LOOP START" << endl;
        cout << "================================================================================" << endl;
        cout << "================================================================================\n\n\n\n\n" << endl;

        for (int i = 0; i < DIMINCLY; ++i) {
            tempThetas[i] = 0;
        }

        for (int feature = 0; feature < DIMINCLY; ++feature) {
            double sum = updateTheta(thetaVector, trainingData, feature);
            cout << "Received sum (hThetaXi - yi) * xij = " << sum << endl;
            sum *= ALPHA;
            cout << "Multiply it by alpha ( " << ALPHA << " ) for : " << sum << endl;
            sum /= SAMPLES;
            cout << "Divide that by # of training samples ( " << SAMPLES << " ) for : " << sum << endl;
            tempThetas[feature] = thetaVector[feature] - sum;
            cout << "Which means our new Theta value for feature " << feature << " should be " << tempThetas[feature] << endl;
            printEverything(tempThetas);
            deltaThetas[feature] = fabs(tempThetas[feature] - thetaVector[feature]);
            cout << endl;
            printEverything(deltaThetas);


            double deltaAsPercentage;
            deltaAsPercentage = (thetaVector[feature] == 0) ? 1 : (deltaThetas[feature] / tempThetas[feature]);
            cout << "deltaAsPercentage: " << deltaAsPercentage << endl;

            converged = (deltaAsPercentage < .1 || isinf(deltaAsPercentage)) ? converged : false;

            cout << "converged: " << (int)converged << endl;
        }

        printEverything(tempThetas);

        for (int feature = 0; feature < DIMINCLY; ++feature) {
            thetaVector[feature] = tempThetas[feature];
        }

        printEverything(thetaVector);
        count++;
    }
}

int main() {

    double testData[NEWDATA][DIMINCLY];
    double trainingData[SAMPLES][DIMINCLY];

    ifstream infile;
    infile.open("linear_regression_data.txt");

    readTrainingData(infile, trainingData);
    normalizeTrainingData(trainingData);
    readTestingData(infile, testData);


/*  For manual validation purposes
    for (int i = 0; i < SAMPLES + NEWDATA; ++i) {
        for (int j = 0; j < DIMINCLY; ++j) {
            cout << trainingData[i][j] << "\t";
        }
        cout << "\n";
    }
*/

    infile.close();

    double thetaVector[DIMINCLY];

    initializeThetaVector(thetaVector);
    findThetas(thetaVector, trainingData);

    for (int i = 0; i < DIMINCLY; ++i) {
        cout << "Theta " << i << ": " << thetaVector[i] << endl;
    }

}
