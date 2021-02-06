/* Write your test code for the ULListStr in this file */
#include <iostream>
#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"
using namespace std;


int main(int argc, char* argv[])
{
  ULListStr dat;
  dat.push_back("7");
  dat.push_front("8");
  dat.push_back("9");
  cout << dat.get(0) << " " << dat.get(1) << " " << dat.get(2) << endl;
  
  dat.pop_back();
  dat.push_front("21");
  dat.push_back("1");

  cout << dat.get(0) << " " << dat.get(1) << " " << dat.get(2) << " " << dat.get(3) << " " << endl;
  cout << dat.front() << " " << dat.back() << endl;
  cout << dat.size() << endl; 
  
  return 0;
}
