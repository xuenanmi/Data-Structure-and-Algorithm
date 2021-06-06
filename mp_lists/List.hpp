/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */
#include <iostream>
using std::cout;
using std::endl;

template <class T>
List<T>::List() { 
  // @TODO: graded in MP3.1
    //ListNode* head_ = NULL;
    //ListNode* tail_ = NULL;
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  //ListNode* first = head_;
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(NULL);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  ListNode* temp1 = head_;
  if (temp1 == NULL) {return;}
  
  ListNode* temp2;
  while (temp1 != NULL){
    temp2 = temp1 -> next;
    delete temp1;
    temp1 = temp2;
  }
  tail_ = NULL;
  length_ = 0;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  newNode -> next = head_;
  newNode -> prev = NULL;
 
  
  if (head_ != NULL) {
    head_ -> prev = newNode;
    //head_ = newNode;
  }
  if (tail_ == NULL) {
    tail_ = newNode;
  }
  
  head_ = newNode;  //revised by me
  length_++;

}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  newNode -> prev = tail_;
  newNode -> next = NULL;

  if (tail_ != NULL) {
    tail_ -> next = newNode;
  }
  if (head_ == NULL) {
    head_ = newNode;
    //tail_ = newNode;
  }

  tail_ = newNode;
  length_++;
  
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
  if (start == NULL) {return NULL;}
  if (splitPoint < 1) {return start;}
  if (splitPoint >= length_) {return NULL;}
  
  ListNode * curr = start;

  for (int i = 0; i < splitPoint && curr != NULL; i++) {
      curr = curr->next;
  }

  if (curr != NULL) {
      curr->prev->next = NULL;
      tail_ = curr->prev;
      curr->prev = NULL;
      return curr;
  }

  return NULL;
}

/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three 
  * elements in the list starting for the first three elements. If the 
  * end of the list has a set of 1 or 2 elements, no rotation all be done 
  * on the last 1 or 2 elements.
  * 
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate() {
  // @todo Graded in MP3.1
  if (length_ == 0) {return;}
  if (length_ < 3) {return;}
  
  ListNode* temp1 = head_;
  ListNode* temp2 = temp1 ->next;
  ListNode* temp3 = temp2 ->next;

  head_ = head_ -> next;
 
  if (length_ % 3 == 0){
    while (temp1 != NULL && temp2 != NULL && temp3 != NULL && temp3 != tail_) {

      temp1 -> next = temp3 -> next;
      temp3 -> next -> prev = temp1;
      temp3 -> next = temp1;
 
      temp1 = temp1 -> next;
      temp2 = temp1 -> next;
      temp3 = temp2 -> next;
      temp1 -> prev -> next = temp2; //
    }

    if (temp3 == tail_){
      temp1 -> next = NULL;
      temp3 -> next = temp1;
    }

    tail_ = temp1;
  }
   
  if (length_ % 3 == 1){
    for (int i = 0; i < length_ /3 ; i++) {

      temp1 -> next = temp3 -> next;
      temp3 -> next -> prev = temp1;
      temp3 -> next = temp1;
      temp1 = temp1->next;
  
      if (i < length_ / 3 - 1) {
        temp2 = temp1 -> next;
        temp3 = temp2 -> next;
        temp1 -> prev -> next = temp2;
      }
      else {tail_ = temp1;}
    }   
  }
  
  if (length_ % 3 == 2){
    for (int i = 0; i < length_ /3 ; i++) {

      temp1 -> next = temp3 -> next;
      temp3 -> next -> prev = temp1;
      temp3 -> next = temp1;
      temp1 = temp1->next;
      temp2 = temp1 -> next;

      if (i < length_ / 3 - 1) {
        temp3 = temp2 -> next;
        temp1 -> prev -> next = temp2;
      }
      else {tail_ = temp2;}
    }
  }
      
}


/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.2
  if(head_ == nullptr || tail_ == nullptr) return;
  if(startPoint == endPoint) return;
  
  ListNode *temp = nullptr;
  ListNode *curr = startPoint;
  ListNode *old_start = startPoint;
  ListNode *old_start_prev = startPoint->prev;
  ListNode *old_end = endPoint;
  ListNode *old_end_next = endPoint->next;

  while(curr != endPoint) {
    temp = curr->prev;
    curr->prev = curr->next;
    curr->next = temp;
    curr = curr->prev;
  }

  temp = curr->prev;
  curr->prev = old_start_prev;
  curr->next = temp;
  endPoint = old_start;
  endPoint->next = old_end_next;

  if(old_start_prev == nullptr){
    head_ = curr;
  } else {
    old_start_prev->next = old_end;
  }
  if(old_end_next == nullptr) {
    tail_ = endPoint;
  } else {
    old_end_next->prev = old_start;
  }
    
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.2
  if (length_ == 0 || length_ ==1) return;

  ListNode* start = head_;
  ListNode* end = start;
  
  while(end != NULL){
    for (int i = 0; i < n-1; i++){
      if (end -> next == NULL) {
         reverse(start, end);
         return;
       }
       end = end->next;
    }
    reverse(start, end);
    if (end -> next == NULL) return;
    start = end->next;
    end = start;
  }
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
  if (first == NULL && second == NULL) return NULL;
  if (first !=NULL && second == NULL) return first;
  if (first == NULL && second != NULL) return second;
  
  ListNode* currhead = nullptr;
  ListNode* currtail = nullptr;

  if (first->data < second->data){
    currhead = first;
    currtail = first;
    first = first->next;
  }
  else{
    currhead = second;
    currtail = second;
    second = second->next;
  }

  while (first != NULL && second != NULL){
    if (first->data < second->data){
      currtail->next = first;
      currtail = first;
      first = first->next;
    }
    else{
      currtail->next = second;
      currtail = second;
      second = second->next;
    }
  }
  if (first == NULL) {currtail->next = second;}
  else {currtail->next = first;}

  return currhead;  
  //return NULL;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  if(chainLength == 0 || chainLength ==1) return start;
  ListNode* half1 = start;
  ListNode* half2 = split(start, chainLength /2);
  
  half1 = mergesort(half1, chainLength /2);
  half2 = mergesort(half2, chainLength - chainLength/2);
  return merge(half1, half2);
  //return NULL;
}
