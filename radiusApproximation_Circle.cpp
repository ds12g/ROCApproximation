/*
  Approximating the radius of curvature, given a constant arc length and a constant interval. Approximation 1: cycle through different radii until the resulting value is within an appropriate range.

  s(x,r) = 2*radius*arcsin(x/(2*radius))

  Start: 05/22/16
*/
# include <iostream>
# include <cmath>
# include <fstream>
# include <iomanip>

double pi = 3.141592654;

using namespace std;

struct Data{
  double xInterval; //Interval :: originalLength - change -> [0,L_0 - lambda*n] lambda = length/turn, n = number of turns.
  double originalLength;
  double testRadius;
  double averageRadius;
  double arcLength;
  double ratioOfArcLength;
  double minimumThreshold;
  double maximumThreshold;
  double increment;
};


void mainMessage();
double calculateArcLength(double, double);
double checkArcLengthRatio(double, double);
double arcLengthRatioWithAverageRadius(double, double, double);





int main(){
  Data radiusData;

  ofstream outputFile("../data_014.txt", ofstream::out);

  if (outputFile.is_open()){
    outputFile << "Daniel Suarez\nRadius Meter Radius Approximation using a circular assumption and splitting interval into 1000 equal parts (for increment).\n\n";
  }

  double maxLength,sum;
  double deltaX = 2.5;
  int moddingNumber = 63;
  double totalSearchInterval;
  double maximumXValueFound;
  bool outputFileCondition = false;


  mainMessage();
  maxLength = 7000;
  radiusData.originalLength = maxLength;
  radiusData.minimumThreshold = .999;
  radiusData.maximumThreshold = 1.01;
  radiusData.increment = .1;
  int j,k,counter = 0, counterTwo = 0;//Keeps track of the number of numbers for the sum -> used as the denominator for calculating the averageRadius that meets the initial condition.

  //Loop that cycles through each deltaX to try and solve for R for  3480 < x < 3500.


  for (double x = maxLength + deltaX; x > 2283.2 ; x = x - deltaX ){

    totalSearchInterval = maxLength + deltaX;

    // Reset all Values to solve the next problem.

    radiusData.testRadius = 0;
    radiusData.averageRadius = 0;
    sum = 0;
    j = 0;
    k = 0;

    //Brute Force method of solving for the radius. Increment r and check S(r): S_0. If the ratio is between minimum and maximum thresholds then it is accurate enough to say that it is the radius that meets the condition with some margin of error.

    for (int i = 0; i < 1000000 ; i++){

      radiusData.testRadius = radiusData.testRadius + radiusData.increment;
      radiusData.arcLength = calculateArcLength(radiusData.testRadius, x);
      radiusData.ratioOfArcLength = checkArcLengthRatio(radiusData.arcLength,radiusData.originalLength);

      if((radiusData.ratioOfArcLength < radiusData.maximumThreshold) && (radiusData.ratioOfArcLength > radiusData.minimumThreshold)){

        j++;

          if((j == 1) && (k == 0)){

          counter++;

          /* An additional solution for generating data is available.*/

          radiusData.averageRadius = radiusData.testRadius;


          //This For Loop runs through the independent variables at some radius such that the original condition is met -> calculates f(x,r) for all x in [-maxLength/2,maxLength/2) with inrement being 10.

            if (counter % moddingNumber == 1){

            counterTwo++;

            cout << x/2 << "\t\t" <<setprecision(8)<< radiusData.averageRadius << "\t\t" << calculateArcLength(radiusData.averageRadius, x) <<"\n";
            outputFile << "\nFor X = " << x << " Average Radius = " << radiusData.averageRadius << "\n\n";
            outputFile << "\nx(R=" << radiusData.averageRadius << ")" << "\t\tf(x,"<< radiusData.averageRadius << ")" <<"\n";

          for (double m = -maxLength/2; m <= maxLength/2 ; m = m + 10){

            if (x/2 > 1000){
              outputFile << m << "\t\t" << sqrt(pow(radiusData.averageRadius,2) - pow(m,2)) - sqrt(pow(radiusData.averageRadius,2)-pow(x/2,2)) << "\n";
            }
          }

        }
          k++;
}
      }
    }

    // if((x == 2500 || x < 2550) && (x > 2220)){
    //   deltaX = .05;
    //   radiusData.increment = .1;
    // }else{
    //   deltaX = 2.5;
    // }

  }


  if (outputFile.is_open()){
    outputFile.close();
  }

  cout << "DONE!\n";
  cout << "moddingNumber = " << moddingNumber << endl;
  cout << "deltaX = " << deltaX << endl;
  cout << counter << endl;
  cout << "number to mod by = " << counter/16 - 1 << endl;
  cout << counterTwo << endl;

  return 0;
}

void mainMessage(){

  cout << "\n***This program approximates the values for radius at different intervals given some maximum Interval, which corresponds to the maximum length of the film.***\n";
  cout << "Stage Length/ Film Length: 7mm -> 7000 microns" << endl;
}

double calculateArcLength(double r, double x){
  double arcLength;
  arcLength = 2*r*asin(x/(2*r)); // When checking take into account radians. 180/pi ~ 57.2958...
  return arcLength;
}
double checkArcLengthRatio(double originalArcLength, double calculatedArcLength){

  return calculatedArcLength/originalArcLength;

}

double arcLengthRatioWithAverageRadius(double original, double averageRadius, double x){
  return calculateArcLength(x,averageRadius)/original;
}
