#include "Image.h"
#include "StickerSheet.h"

int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  //base picture
  Image icecream;
  icecream.readFromFile("icecream.png");
  //stickers;
  Image spongebob;
  spongebob.readFromFile("spongebob.png");
  spongebob.scale(0.6);
  Image kitty;
  kitty.readFromFile("kitty.png");
  Image minions;
  minions.readFromFile("minions.png");

  StickerSheet myart(icecream, 3);
  myart.addSticker(spongebob,600,170);
  myart.addSticker(kitty,400,200);
  myart.addSticker(minions,50,90);

  Image output = myart.render();
  output.writeToFile("myImage.png");
  
  return 0;
}
