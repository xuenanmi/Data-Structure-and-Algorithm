/**
 * @file HSLAPixel.cpp
 * Implementation of the HSLAPixel class for use in with the PNG library.
 *
 * @author CS 225: Data Structures
 * @version 2018r1-lab1
 */

#include "HSLAPixel.h"
#include <cmath>
#include <iostream>
using namespace std;

namespace cs225 {
  HSLAPixel::HSLAPixel(){
    l = 1;
    a = 1;
    s = 0;
    h = 0;
  }; 

  HSLAPixel::HSLAPixel(double hue, double saturation, double luminance){
    h = hue;
    a = 1;
    s = saturation;
    l = luminance;
  };

  HSLAPixel::HSLAPixel(double hue, double saturation, double luminance, double alpha){
    h = hue;
    a = alpha;
    s = saturation;
    l = luminance;
  };
}
