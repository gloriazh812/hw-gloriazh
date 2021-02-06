/*
CSCI 104: Homework 1 Problem 1

Write a recursive function to split a sorted singly-linked
list into two sorted linked lists, where one has the even 
numbers and the other contains the odd numbers. Students 
will receive no credit for non-recursive solutions. 
To test your program write a separate .cpp file and #include
split.h.  **Do NOT add main() to this file**.  When you submit
the function below should be the only one in this file.
*/

#include "split.h"
#include <cstddef>
#include <iostream>
using namespace std;

/* Add a prototype for a helper function here if you need */

void split(Node*& in, Node*& odds, Node*& evens)
{
  /* Add code here */

  //Base case: when hit the end of the linked list
  if (in == NULL){
    return;
  }
  //Function implement and recursive call 
  else{
    //if the value is odd 
    //check whether the odds linked list is empty
    //if yes, odds head = in 
    //otherwise, curr odds content = in content (address of Node)
    if (in->value % 2 != 0){
      //remember in->next because splitting process will need in->next = NULL
      Node* next_in = in->next;
      //corner case: 
      if (odds == NULL){
        odds = in;
        odds->next = NULL;
        split(next_in, odds, evens);
      }
      //general case:
      else{
        odds->next = in;
        in->next = NULL;
        split(next_in, odds->next, evens);
      }
    }
    //otherwise, the value is even 
    //check whether the evens linked list is empty
    //if yes, evens head = in 
    //otherwise, curr evens content = in content (address of Node)
    else{
      Node* next_in = in->next;
      //corner case:
      if (evens == NULL){
        evens = in;
        in->next = NULL;
        split(next_in, odds, evens);
      }
      //general case:
      else{
        evens->next = in;
        in->next = NULL;
        split(next_in, odds, evens->next);
      }
    }
  }
}

/* If you needed a helper function, write it here */
