#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}

/* Returns a pointer to the item at index, loc,
 * if loc is valid and NULL otherwise
 *   - MUST RUN in O(n)*/
std::string* ULListStr::getValAtLoc(size_t loc) const
{
  // access non-existent location, O(1) 
  if (loc > size_-1){
    return NULL;
  }

  int remain = loc;
  Item* currItem = head_;
  while (remain >= currItem->last - currItem->first)
  {
    remain -= (currItem->last - currItem->first);
    currItem = currItem->next;
  }
  return &(currItem->val[currItem->first + remain]);
};


/* Adds a new value to the back of the list
 *   - MUST RUN in O(1)*/
void ULListStr::push_back(const std::string& val)
{
  //------list empty----- create a new item in the ULList, size_++
  if (empty()){
    Item *item = new Item;
    head_ = item;
    tail_ = item;
    item->val[0] = val;
    item->last = 1;
  }
  //-----list not empty-----
  /* if the item has empty value(s) after the last pointer,
   * then just push the value next to the last pointer
   * and add size_
  */
  else if (tail_->last < ARRSIZE){
    tail_->val[tail_->last] = val;
    tail_->last++;
  }
  /* if the item is full, then add new item, size_++ */
  else{
    Item *item = new Item;
    tail_->next = item; //update next pointer of last item (before pushback)
    //update curr item (new one)
    item->prev = tail_; 
    //item->next = NULL;
    //item->first = 0;
    item->val[0] = val;
    item->last++;
    tail_ = item;
  }
  size_++;
};

/* Removes a value from the back of the list
 *   - MUST RUN in O(1)*/
void ULListStr::pop_back()
{
  //------list empty----- return
  if (empty()){
    return;
  }
  //-----list not empty-----
  // only one value in list
  if (size_ == 1){
    delete head_; //head_ = tail_, delete either one
    head_ = NULL;
    tail_ = NULL;
  }
  // only one value in item, multiple items in list
  else if (tail_->last == 1){
    tail_=tail_->prev;
    delete tail_->next; //the popped back item
    tail_->next = NULL;
  }
  // more than one values
  else{
    tail_->last--;
  }
  size_--;
};
  
/* Adds a new value to the front of the list.
  * If there is room before the 'first' value in
  * the head node add it there, otherwise, 
  * allocate a new head node.
  *   - MUST RUN in O(1)*/
void ULListStr::push_front(const std::string& val)
{
  //------list empty----- create a new item in the ULList, size_++
  if (empty()){
    Item *item = new Item;
    head_ = item;
    tail_ = item;
    item->val[0] = val;
    item->last = 1;
  }
  //-----list not empty-----
  /* if the item has empty value(s) before the first pointer,
   * then just push the value before the first pointer
   * and add size_
  */
  else if (head_->first != 0){
    head_->val[head_->first-1] = val;
    head_->first--;
  }
  /* if the item is full, then add new item before, size_++ */
  else{
    Item *item = new Item;
    item->next = head_;
    head_->prev = item; 
    //update curr item (new one)
    //item->prev = NULL; 
    item->first = ARRSIZE-1;
    item->val[ARRSIZE-1] = val;
    item->last = ARRSIZE;
    head_ = item;
  }
  size_++;
};

/* Removes a value from the front of the list
 *   - MUST RUN in O(1)*/
void ULListStr::pop_front()
{
  //------list empty----- return
  if (empty()){
    return;
  }
  //-----list not empty-----
  // only one value in list
  if (size_ == 1){
    delete head_; //head_ = tail_, delete either one
    head_ = NULL;
    tail_ = NULL;
  }
  // only one value in item, multiple items in list
  else if (head_->first == ARRSIZE-1){
    head_= head_->next;
    delete head_->prev; //the popped front item
    head_->prev = NULL;
  }
  // more than one values
  else{
    head_->first++;
  }
  size_--;
};
  
/**
 * Returns a const reference to the back element
 *   - MUST RUN in O(1)
 */
std::string const & ULListStr::back() const
{
  return tail_->val[tail_->last-1];
};

/**
 * Returns a const reference to the front element
 *   - MUST RUN in O(1)
 */
std::string const & ULListStr::front() const
{
  return head_->val[head_->first];
};