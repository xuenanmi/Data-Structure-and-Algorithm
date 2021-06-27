/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
    MosaicCanvas* result = new MosaicCanvas(theSource.getRows(), theSource.getColumns());

    vector<Point<3>> average_color(theTiles.size());
    map<Point<3>, int> Map;

    //get the average color of TileImage and convert the color to the 3D Point
    //map each 3D point to an index
    for (size_t i = 0; i < theTiles.size(); i++){
       average_color[i] = convertToXYZ(theTiles[i].getAverageColor());
       Map[average_color[i]] = i;
    }

    //use the vector of average color to build a KD tree
    KDTree<3> Tree(average_color);
   
    //for each region of source image, find the closest average color
    //find the index of the closest color
    //place that TileImage with the index into the MosaicCanvas in the same region
    for (int x = 0; x < theSource.getRows(); x++){
      for (int y = 0; y < theSource.getColumns(); y++){
         int idx = Map[Tree.findNearestNeighbor(convertToXYZ(theSource.getRegionColor(x, y)))];
         result->setTile(x, y, &theTiles[idx]);
      }
    }
   
    return result;
}

