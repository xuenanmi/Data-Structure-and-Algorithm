#include "cs225/PNG.h"
#include <list>
#include <iostream>

#include "colorPicker/ColorPicker.h"
#include "imageTraversal/ImageTraversal.h"

#include "Point.h"
#include "Animation.h"
#include "FloodFilledImage.h"

using namespace cs225;

/**
 * Constructs a new instance of a FloodFilledImage with a image `png`.
 * 
 * @param png The starting image of a FloodFilledImage
 */
FloodFilledImage::FloodFilledImage(const PNG & png) {
  /** @todo [Part 2] */
  image_ = png;
}

/**
 * Adds a FloodFill operation to the FloodFillImage.  This function must store the operation,
 * which will be used by `animate`.
 * 
 * @param traversal ImageTraversal used for this FloodFill operation.
 * @param colorPicker ColorPicker used for this FloodFill operation.
 */
void FloodFilledImage::addFloodFill(ImageTraversal & traversal, ColorPicker & colorPicker) {
  /** @todo [Part 2] */
  ImageTraversal* t = &traversal;
  traversal_vec.push_back(t);
  ColorPicker* c = &colorPicker;
  color_vec.push_back(c);
  //traversal_ = &traversal;
  //color_ = &colorPicker;
}

/**
 * Creates an Animation of frames from the FloodFill operations added to this object.
 * 
 * Each FloodFill operation added by `addFloodFill` is executed based on the order
 * the operation was added.  This is done by:
 * 1. Visiting pixels within the image based on the order provided by the ImageTraversal iterator and
 * 2. Updating each pixel to a new color based on the ColorPicker
 * 
 * While applying the FloodFill to the image, an Animation is created by saving the image
 * after every `frameInterval` pixels are filled.  To ensure a smooth Animation, the first
 * frame is always the starting image and the final frame is always the finished image.
 * 
 * (For example, if `frameInterval` is `4` the frames are:
 *   - The initial frame
 *   - Then after the 4th pixel has been filled
 *   - Then after the 8th pixel has been filled
 *   - ...
 *   - The final frame, after all pixels have been filed)
 */ 
Animation FloodFilledImage::animate(unsigned frameInterval) const {
  Animation animation;
  /** @todo [Part 2] */
  PNG image = image_;  
  animation.addFrame(image);
  
  for (int i = 0; i < (int)traversal_vec.size(); i++){
    unsigned framecount = 0;
    for (ImageTraversal::Iterator it = traversal_vec[i]->begin(); it != traversal_vec[i]->end(); ++it){
       if (framecount == frameInterval){
         animation.addFrame(image);
         framecount = 0;
       }
       framecount++;
       HSLAPixel& pixel1 = image.getPixel((*it).x, (*it).y);
       HSLAPixel pixel2 = color_vec[i]->getColor((*it).x, (*it).y);
       pixel1 = pixel2;
    }
  }
  animation.addFrame(image);
  return animation;
}

/*
Animation FloodFilledImage::animate(unsigned frameInterval) const {
  Animation animation;
  unsigned framecount = 0;
  PNG image = image_;
  animation.addFrame(image);
  for (ImageTraversal::Iterator it = traversal_->begin(); it != traversal_->end(); ++it) {
    framecount++;
    HSLAPixel& pixel1 = image.getPixel((*it).x, (*it).y); 
    HSLAPixel pixel2 = color_->getColor((*it).x, (*it).y);
    pixel1 = pixel2;
    if (framecount % frameInterval == 0) animation.addFrame(image);
  }
  animation.addFrame(image);
  return animation;
}*/
