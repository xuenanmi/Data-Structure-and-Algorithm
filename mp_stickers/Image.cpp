#include "Image.h"
#include <cmath>

using cs225::HSLAPixel;
using cs225::PNG;

void Image::lighten(){
  for (unsigned x = 0; x < width(); x++){
    for (unsigned y = 0; y < height(); y++){
       HSLAPixel & pixel = getPixel(x, y);
       if (pixel.l < 0.9) {pixel.l = pixel.l + 0.1;}
       else {pixel.l = 1;}
     }
  }
}

void Image::lighten(double amount){
  for (unsigned x = 0; x < width(); x++){
    for (unsigned y = 0; y < height(); y++){
      HSLAPixel & pixel = getPixel(x, y);
      if (pixel.l < (1-amount)) {pixel.l = pixel.l + amount;}
      else {pixel.l = 1;}
     }
  }
}

void Image::darken(){
  for (unsigned x = 0; x < width(); x++){
    for (unsigned y = 0; y < height(); y++){
       HSLAPixel & pixel = getPixel(x, y);
       if (pixel.l > 0.1) {pixel.l = pixel.l - 0.1;}
       else {pixel.l = 0;}
     }
  }
}

void Image::darken(double amount){
  for (unsigned x = 0; x < width(); x++){
    for (unsigned y = 0; y < height(); y++){
      HSLAPixel & pixel = getPixel(x, y);
      if (pixel.l > amount) {pixel.l = pixel.l - amount;}
      else {pixel.l = 0;}       
    }
  }  
}

void Image::saturate(){
  for (unsigned x = 0; x < width(); x++){
    for (unsigned y = 0; y < height(); y++){
      HSLAPixel & pixel = getPixel(x, y);
      if (pixel.s < 0.9) {pixel.s = pixel.s + 0.1;}
      else {pixel.s = 1;}     
    }
  }
}

void Image::saturate(double amount){
  for (unsigned x = 0; x < width(); x++){
    for (unsigned y = 0; y < height(); y++){
      HSLAPixel & pixel = getPixel(x, y);
      if (pixel.s < (1 - amount)) {pixel.s = pixel.s + amount;}
      else {pixel.s = 1;} 
    }
  }
}

void Image::desaturate(){
  for (unsigned x = 0; x < width(); x++){
    for (unsigned y = 0; y < height(); y++){
      HSLAPixel & pixel = getPixel(x, y);
      if (pixel.s > 0.1) {pixel.s = pixel.s - 0.1;}
      else {pixel.s = 0;} 
    }
  }
}

void Image::desaturate(double amount){
  for (unsigned x = 0; x < width(); x++){
    for (unsigned y = 0; y < height(); y++){
      HSLAPixel & pixel = getPixel(x, y);
      if (pixel.s > amount) {pixel.s = pixel.s - amount;}
      else {pixel.s = 0;}
    }
  }
}

void Image::grayscale(){
  for (unsigned x = 0; x < width(); x++){
    for (unsigned y = 0; y < height(); y++){
      HSLAPixel & pixel = getPixel(x, y);
      pixel.s = 0;
    }
  } 
}

void Image::rotateColor(double degrees){
  for (unsigned x = 0; x < width(); x++){
    for (unsigned y = 0; y < height(); y++){
      HSLAPixel & pixel = getPixel(x, y);
      if (pixel.h + degrees > 0 && pixel.h + degrees < 360) {pixel.h = pixel.h + degrees;}
      else if (pixel.h + degrees > 360) {pixel.h = pixel.h + degrees - 360;}
      else {pixel.h = pixel.h + degrees + 360;}
    }
  }
}

void Image::illinify(){
  for (unsigned x = 0; x < width(); x++){
    for (unsigned y = 0; y < height(); y++){
      HSLAPixel & pixel = getPixel(x, y);
      if (0 <= pixel.h && pixel.h <=113) {pixel.h = 11;}
      else if (114 <= pixel.h && pixel.h <=293) {pixel.h = 216;}
      else {pixel.h = 11;}
    }
  }
}

void Image::scale(double factor){
  unsigned newwidth = width() * factor;
  unsigned newheight = height() * factor;
  
  PNG copyimage = *this;
  //*copyimage = *this;
  this->resize(newwidth, newheight);

  for (unsigned x = 0; x < newwidth; x++){
    for (unsigned y = 0; y < newheight; y++){
      unsigned x_original = x / factor;
      unsigned y_original = y / factor;

      HSLAPixel & newpixel = getPixel(x, y);
      HSLAPixel & oldpixel = copyimage.getPixel(x_original, y_original);
      newpixel = oldpixel;
    }
  }  
}
    
void Image::scale(unsigned w, unsigned h){
  double factor1 = double (1.0*w) / width();
  double factor2 = double (1.0*h) / height();
  if (factor1 < factor2) {scale(factor1);}
  else {scale(factor2);} 
}
