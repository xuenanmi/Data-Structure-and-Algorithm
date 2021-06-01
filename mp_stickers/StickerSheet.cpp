#include "StickerSheet.h"
using cs225::PNG;
using cs225::HSLAPixel;


StickerSheet::StickerSheet(const Image & picture, unsigned max){ 
  base = picture;
  max_stickers = max;
  stickerCount = 0;
  imagesheet = new Image * [max_stickers];
  x_coord = new unsigned[max_stickers];
  y_coord = new unsigned[max_stickers];
  
}

void StickerSheet::copy(const StickerSheet & other){
  base = other.base;
  max_stickers = other.max_stickers;
  stickerCount = other.stickerCount;
  
  x_coord = new unsigned[max_stickers];
  y_coord = new unsigned[max_stickers];
  imagesheet = new Image * [max_stickers];

  for (unsigned i = 0; i < stickerCount; i++){
    x_coord[i] = other.x_coord[i];
    y_coord[i] = other.y_coord[i];
    imagesheet[i] = new Image();
    *(imagesheet[i]) = *(other.imagesheet[i]);
    //imagesheet[i] = other.imagesheet[i];
  }
}

void StickerSheet::clear(){
  delete [] x_coord;
  x_coord = NULL;
  delete [] y_coord;
  y_coord = NULL;
  for (unsigned i = 0; i < stickerCount; i++){
    delete imagesheet[i];
    imagesheet[i] = NULL;
  }
  delete [] imagesheet;
  imagesheet = NULL;
}

StickerSheet::~StickerSheet(){
  clear(); 
}


StickerSheet::StickerSheet(const StickerSheet & other){
  copy(other);
}

const StickerSheet & StickerSheet::operator=(const StickerSheet & other){
  if (this != &other){
    clear();
    copy(other);
  }
  return *this;
}

//////
void StickerSheet::changeMaxStickers(unsigned max){
  Image **imagesheet_tmp = new Image * [stickerCount];
  unsigned *x_coord_tmp = new unsigned[stickerCount];
  unsigned *y_coord_tmp = new unsigned[stickerCount];
  
  for (unsigned i = 0; i < stickerCount; i++){
    imagesheet_tmp[i] = imagesheet[i];
    x_coord_tmp[i] = x_coord[i];
    y_coord_tmp[i] = y_coord[i];
  }  
  
  //clear();
  delete [] imagesheet;
  delete [] x_coord;
  delete [] y_coord;

  imagesheet = new Image * [max];
  x_coord = new unsigned[max];
  y_coord = new unsigned[max];
  
  if (max >= stickerCount){
    for (unsigned i = 0; i < stickerCount; i++){
      imagesheet[i] = imagesheet_tmp[i];
      x_coord[i] = x_coord_tmp[i];
      y_coord[i] = y_coord_tmp[i];
    }
  }
  else if (max < stickerCount) {
    for (unsigned i = 0; i < max; i++){
      imagesheet[i] = imagesheet_tmp[i];
      x_coord[i] = x_coord_tmp[i];
      y_coord[i] = y_coord_tmp[i];
    }
    
    for (unsigned i = max; i < stickerCount; i++){
      delete imagesheet_tmp[i];
      imagesheet_tmp[i]= NULL;
    }
    stickerCount = max;    
  }
  max_stickers = max;  
  delete [] imagesheet_tmp;
  delete [] x_coord_tmp;
  delete [] y_coord_tmp;
 
}
////////

int StickerSheet::addSticker(Image & sticker, unsigned x, unsigned y){
  for (unsigned i = stickerCount; i < max_stickers; i++){
      imagesheet[i] = new Image(sticker);
      x_coord[i] = x;
      y_coord[i] = y;
      stickerCount++;
      return i;    
  } 
  return -1; 
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y){
  if (index < stickerCount) {
    x_coord[index] = x;
    y_coord[index] = y;
    return true;
  }
  
  else {return false;}
}

void StickerSheet::removeSticker(unsigned index){
  if (index < max_stickers && imagesheet[index] != NULL){
    delete imagesheet[index];
    
    for (unsigned i = index; i < max_stickers -1; i++){
      imagesheet[i] = imagesheet[i+1];
      x_coord[i] = x_coord[i+1];
      y_coord[i] = y_coord[i+1];
    }

    imagesheet[max_stickers -1] = NULL;
    x_coord[max_stickers -1] = 0;
    y_coord[max_stickers -1] = 0;
    stickerCount--;
  }  
}

Image * StickerSheet::getSticker(unsigned index){
  if (index >= stickerCount) {return NULL;}
  return imagesheet[index];
}

Image StickerSheet::render() const{
  Image result(base);
  for (unsigned i = 0; i < stickerCount; i++){
    unsigned sticker_w = imagesheet[i]->width();
    unsigned sticker_h = imagesheet[i]->height();
    //resize the base
    if (sticker_w + x_coord[i] > result.width()) {result.resize(sticker_w + x_coord[i], result.height());}
    if (sticker_h + y_coord[i] > result.height()) {result.resize(result.width(), sticker_h + y_coord[i]);}
    //overwrite the pixel from sticker on base
    for (unsigned j= 0; j < sticker_w; j++){
      for (unsigned k = 0; k < sticker_h; k++){
        HSLAPixel & sticker_pixel = imagesheet[i]->getPixel(j, k);
        HSLAPixel & base_pixel = result.getPixel(j + x_coord[i], k + y_coord[i]);
        if (sticker_pixel.a != 0) {base_pixel = sticker_pixel;} 
      }
    }
  }
  return result;

}
