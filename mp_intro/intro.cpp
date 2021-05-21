#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <string>
#include <math.h> 

using namespace cs225;

void rotate(std::string inputFile, std::string outputFile) {
  // TODO: Part 2
  PNG *image = new PNG();
  image->readFromFile(inputFile);
  unsigned h = image->height();
  unsigned w = image->width();
  PNG *out = new PNG(w, h);
  
  for (unsigned int x = 0; x < w; x++){
    for (unsigned int y = 0; y < h; y++){
      HSLAPixel &pixel1 = image->getPixel(x, y);
      HSLAPixel &pixel2 = out->getPixel(w-1-x, h-1-y);
      pixel2 = pixel1;
    }
  }
  out->writeToFile(outputFile);
}

cs225::PNG myArt(unsigned int width, unsigned int height) {
  cs225::PNG png(width, height);
  // TODO: Part 3
  for (unsigned int x = 0; x < width; x++){
    for (unsigned int y = 0; y < height; y++){
      HSLAPixel &pixel0 = png.getPixel(x, y);
      double inten = sin(0.05*x) * sin(0.05*y);
      pixel0.h = inten * 100 + 200;
      pixel0.s = 1.0;
      pixel0.l = 0.5;
      pixel0.a = 1.0;
 
    }
  }  

  return png;
}
