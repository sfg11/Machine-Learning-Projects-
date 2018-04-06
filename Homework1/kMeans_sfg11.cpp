// Sarah Gibbons
// part 1 to compile g++ kMeans_sfg11.cpp -o ./run
// to run ./run

#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <ctime>

#include <exception>
#include <iomanip>

#include <time.h>
using namespace std;

struct Coord{
  string name = "";
  double x;
  double y;
};


void generateRandomClustersInSet();
void generateRandomClusters();
void runRounds();
int init();
void initSet(int index, double x, double y); // Initializes the set of data samples
Coord argMin(int samplePoint);
double sim(Coord dataSetPoint, Coord clusterPoint); // Calculates simularity using distance formula
void recalcClusters();
void run(); // recalculates centroids and reassigns datapoints to clusters
void reassignToClusters();
void outputResult();
void runRounds();


const int SIZE = 8;
vector<Coord> S (SIZE); // set of data samples
vector<Coord> S2 (SIZE);
vector<Coord> C; // c[k] be the vectors for cluster centers;
vector<Coord> A; // set of associate clusters for each data sample
int k = 0; // number of clusters
int main() {
  int choice;
  srand(time(NULL));

  initSet(0,2,10);
  initSet(1,2,5);
  initSet(2,8,4);
  initSet(3,5,8);
  initSet(4,7,5);
  initSet(5,6,4);
  initSet(6,1,2);
  initSet(7,4,9);

  S2 = S; // Let S' = S;

  cout << "Initial Set:\n";
  for(int i = 0; i<S.size(); i++){
    cout << S.at(i).x << " " << S.at(i).y << endl;
  }
  cout << endl;


  cout << "Choose starting # of clusters: "; cin >> k;
  cout << "\n Option: \n";
  cout << "1: Generate random cluster centers from within set\n";
  cout << "2: Generate random cluster centers with a max of either 10 or 15\n";
  cout << "3: Pick from the set\n";
  cout << "Enter choice: "; cin >> choice;

  switch(choice){
    case 1: generateRandomClustersInSet();
    break;
    case 2: generateRandomClusters();
    break;
    case 3: runRounds();
    break;
  }

  cout << "Initial Cluster Coordinates:\n";
  for(int i = 0; i<k; i++){
    cout << C.at(i).x << " " << C.at(i).y << endl;
  }
  cout << endl;

  for(int i = 0; i<S.size(); i++){
    A.push_back(argMin(i));
  }

  run();

  cout << "\n Final cluster assignments: \n";

  for(int i = 0; i<A.size(); i++){
    cout << i << " - " << A.at(i).x <<" " << A.at(i).y << endl;
  }

  cout << "\n Final clustering mean values: \n";

  for(int i = 0; i<k; i++) {
    cout << fixed << setprecision(2) << C.at(i).x << " " << C.at(i).y << endl;
  }

  outputResult();
  return 0;
}

void initSet(int index, double x, double y){
  S.at(index).x = x;
  S.at(index).y = y;
}

Coord argMin(int dataIndex){ // finds the closest cluster for a data point
  double mostSimilar = sim(S.at(dataIndex), C.at(0)); // smallest value
  double simValue;
  int mostSimilarIndex = 0;
  for(int j = 0; j<k; j++){
    simValue = sim(S.at(dataIndex), C.at(j));
    if(simValue < mostSimilar){
      mostSimilar = simValue;
      mostSimilarIndex = j;
    }
  }
  return C.at(mostSimilarIndex); // returns the coord that is the most similar
}


double sim(Coord dataSetPoint, Coord clusterPoint){
  return sqrt(pow((clusterPoint.x - dataSetPoint.x), 2)+ pow((clusterPoint.y - dataSetPoint.y),2));
}


void run(){ reassignToClusters(); }

void recalcCentroids(){

  for(int i = 0; i<k; i++){
    double meanX = 0, meanY = 0, count = 0;
    for(int j = 0; j<S.size(); j++){
      if(A.at(j).x == C.at(i).x && A.at(j).y == C.at(i).y){

        meanX += S.at(j).x;
        meanY += S.at(j).y;
        count++;
      }
    }

    if(count > 0){ // make sure centroids are recalculated
      C.at(i).x = meanX/count;
      C.at(i).y = meanY/count;
      C.at(i).name = "Cluster " + i;
    }
  }
}

void reassignToClusters(){
  Coord a;
  bool change = true;
  recalcCentroids();

  while(change){
    change = false;
    for(int i = 0; i<S.size(); i++){
      a = argMin(i);
      if(a.x != A.at(i).x || a.y != A.at(i).y){
        A[i].x = a.x;
        A[i].y = a.y;
        change = true;
      }
    }
    if(change){
      recalcCentroids();
    }
  }
}

void outputResult(){

  cout << "Final Clustering Results: " << endl;
  for(int i = 0; i<k; i++){
    cout << "Cluster " << i << ": {";
    for(int j = 0; j<S.size(); j++){
      if(A.at(j).x == C.at(i).x && A.at(j).y == C.at(i).y){
        cout << "A" << j << ",";
      }
    }
    cout << "}" << endl;
  }

}

void runRounds(){

  int cluster1, cluster2, cluster3;
  cout << "Cluster 1: ";  cin >> cluster1;
  cout << "Cluster 2: ";  cin >> cluster2;
  cout << "Cluster 3: ";  cin >> cluster3;
  C.push_back(S2.at(cluster1));
  C.push_back(S2.at(cluster2));
  C.push_back(S2.at(cluster3));
}

void generateRandomClustersInSet(){

  int j;
  for(int i = 0; i<k; i++){
    j = rand() % S2.size();
    C.push_back(S2.at(j));
    S2.erase(S2.begin() + j);
  }
  cout << endl;
}

void generateRandomClusters(){

  int choice;
  cout << "Choose a max:\n";
  cout << "1: Max Point is (10,10)\n";
  cout << "2: Max Point is (15,15)\n";
  cout << "Choice: ";  cin >> choice;

  Coord newCoord;

  switch(choice){
    case 1:
    for (int i = 0; i<k; i++){
      newCoord.x = rand() % 10;
      newCoord.y = rand() % 10;
      C.push_back(newCoord);
    }
    break;
    case 2:
    for (int i = 0; i<k; i++){
      newCoord.x = rand() % 15;
      newCoord.y = rand() % 15;
      C.push_back(newCoord);
    }
    break;
  }
}
