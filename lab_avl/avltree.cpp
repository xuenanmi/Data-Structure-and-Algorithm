/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include <algorithm>

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::updateHeight(Node*& subtree){
  subtree->height = 1 + std::max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right));
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node* temp = t->right;
    t->right = temp->left;
    temp->left = t;
    updateHeight(t);
    t = temp;
    updateHeight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node* temp = t->left;
    t->left = temp->right;
    temp->right = t;
    updateHeight(t); //update the t's height, otherwise, t and temp height are both wrong//attention
    t = temp;
    updateHeight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    if (subtree == NULL) return;
    int balance = heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left);
    if (balance == -2){
      int leftbalance = heightOrNeg1(subtree->left->right) - heightOrNeg1(subtree->left->left);
      if (leftbalance == -1) {rotateRight(subtree);}
      else {rotateLeftRight(subtree);} 
    }

    if (balance == 2){
      int rightbalance = heightOrNeg1(subtree->right->right) - heightOrNeg1(subtree->right->left);
      if (rightbalance == 1) {rotateLeft(subtree);}
      else {rotateRightLeft(subtree);}
    }
    
    updateHeight(subtree);   
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
   if(subtree == NULL) {subtree = new Node(key, value);}
   else if (key < subtree->key) {insert(subtree->left, key, value);}
   else if (key > subtree->key) {insert(subtree->right, key, value);}
   //updateHeight(subtree);
   rebalance(subtree);
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree->left, key);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree = NULL;
            //std::cout << "delete" <<std::endl;

        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node* curr = subtree->left;
            while (curr->right != NULL){
              curr = curr->right;
            }
            swap(subtree, curr);
            
            remove(subtree->left, key);
        } else {
            /* one-child remove */
            // your code here
            
            Node * right = subtree->right;
            Node * left = subtree->left;
            if (left) {
               delete subtree; 
               subtree = left;
            }
            else if (right){
               delete subtree;
               subtree = right;
            }
            else {
              delete subtree;
              subtree = NULL;
            }
        }
        // your code here
    }
    rebalance(subtree);
}
