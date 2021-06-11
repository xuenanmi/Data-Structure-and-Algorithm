#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

#include <math.h> 
using namespace cs225;

MyColorPicker::MyColorPicker(double intensity) {
  hue = 0;
  intensity_ = intensity;
}
/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
  HSLAPixel pixel(hue, 1, 0.5);
  hue = intensity_ * sin(0.05 * x) * sin(0.05 * y) +200;
  if (hue >= 360) { hue -= 360; }
  return pixel;
}
