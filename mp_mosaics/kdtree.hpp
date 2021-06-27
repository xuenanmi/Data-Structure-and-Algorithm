/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

#include <cmath>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    double a = first[curDim];
    double b = second[curDim];
    if (a < b) return true;
    if (a > b) return false;
    return (first < second);
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
   double result1 = 0;
   double result2 = 0;

   for (unsigned i = 0; i < Dim; i++){
      double dis1_dim = (target[i] - currentBest[i]) * (target[i] - currentBest[i]);
      double dis2_dim = (target[i] - potential[i]) * (target[i] - potential[i]);
      result1 = result1 + dis1_dim;
      result2 = result2 + dis2_dim;
   }
   
   if (sqrt(result1) > sqrt(result2)) return true;
   if (sqrt(result1) < sqrt(result2)) return false;
   else return currentBest > potential;
   //  return false;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
 *      * @todo Implement this function!
 *           */
  for (size_t i =0; i < newPoints.size(); i++){
    points.push_back(newPoints[i]);
  }
  root = buildtree(0, 0, newPoints.size()-1);

}


template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::buildtree(int dim,int left, int right){
  if (left <= right) {
    int middle = floor((left + right) /2); ////
    select(dim, left, right, middle);
    KDTreeNode* subroot = new KDTreeNode(points[middle]);

    subroot->left = buildtree((dim + 1) % Dim, left, middle -1);
    subroot->right = buildtree((dim + 1) % Dim, middle + 1, right);
    return subroot;
  }
  return NULL;
}


template <int Dim>
void KDTree<Dim>::swap(int a, int b){
  Point<Dim> temp = points[a];
  points[a] = points[b];
  points[b] = temp;
}

template <int Dim>
int KDTree<Dim>::partition(int curDim, int left, int right, int pivotIndex){
  Point<Dim> pivotValue = points[pivotIndex];
  swap(pivotIndex, right);
  int storeIndex = left;
  //int i = left;
  for (int i = left; i < right; i++ ){
    if (smallerDimVal(points[i], pivotValue, curDim)) {
      swap(storeIndex, i);
      storeIndex++;
    }
  }
  swap(right, storeIndex);
  return storeIndex;
}

template <int Dim>
void KDTree<Dim>::select(int curDim, int left, int right,int k){
  if (right <= left) return ;
  int pivotIndex = floor((left + right)/2); ////
  int Index = partition(curDim, left, right, pivotIndex);
  if (k < Index) {select(curDim, left, Index - 1, k);}
  if (k > Index) {select(curDim, Index + 1, right, k);}
  if (k == Index) return;
  return ; 
}


template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
  this = new KDTree(other.points);
}

template <int Dim>
void KDTree<Dim>::destroy(KDTreeNode* root){
  if(!root) return;
  destroy(root->left);
  destroy(root->right);
  delete root;  
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  if (*this != rhs){
    destory(this);
    this = new KDTree(rhs);  
  }
  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
  destroy(root);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    // return Point<Dim>();
    return findNearestNeighbor(query, root->point, 0, root);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(Point<Dim> query, Point<Dim> curBest, int dim, KDTreeNode* curRoot) const
{
   if (!curRoot->left && !curRoot->right) return curRoot->point;
   
   bool searched_left = false;
   if (smallerDimVal(query, curRoot->point, dim)) {
      if (curRoot->left) {
         curBest = findNearestNeighbor(query, curBest, (dim + 1)%Dim, curRoot->left);
         searched_left = true;
      }
      else {curBest = findNearestNeighbor(query, curBest, (dim + 1)%Dim, curRoot->right);}
   }   
   else{
     if (curRoot->right) {curBest = findNearestNeighbor(query, curBest, (dim + 1)%Dim, curRoot->right);}
     else {
        curBest = findNearestNeighbor(query, curBest, (dim + 1)%Dim, curRoot->right);
        searched_left = true;}
   }  
 
   //std::cout << curRoot->point[0] << std::endl;
   if(shouldReplace(query, curBest, curRoot->point)) {
      curBest = curRoot->point;
   }

   double radius = 0.0;
   for (int i = 0; i< Dim; i++){
      radius = radius + (query[i] - curBest[i]) * (query[i] - curBest[i]);
   }   

  double splitDist = (curRoot->point[dim] - query[dim])*(curRoot->point[dim] - query[dim]);
  
  if (radius >= splitDist){
     if (searched_left) {
       if (curRoot->right){
       Point<Dim> tempNearest = findNearestNeighbor(query, curBest, (dim + 1)%Dim, curRoot->right);
       if (shouldReplace(query, curBest, tempNearest)) {curBest = tempNearest;}
       }
     }
     else {
       if (curRoot->left){ 
       Point<Dim> tempNearest = findNearestNeighbor(query, curBest, (dim + 1)%Dim, curRoot->left);
       if (shouldReplace(query, curBest, tempNearest)) {curBest = tempNearest;}
       }
     }
     
  }
    
  return curBest;  
}
          

