#include <iostream>
#include "coordinates.h"
using namespace std;

// Main Function
int main() 
{
    int sdf;
    Coordinates ogden(41.2230, -111.970420);
    cout << "Ogden's Location: " << ogden << endl;
    cout << "GPS Format: " << ogden.gps() << endl;

  return 0;
}