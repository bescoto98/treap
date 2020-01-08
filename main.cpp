/**
Brenda Escoto
escot105@mail.chapman.edu
May 17, 2019
**/

#include <iostream>
#include "Treap.h"
#include <cstdlib>
#include <ctime>


using namespace std;

int main()
{
  //to test run time
  clock_t stop=clock();
  clock_t start=clock();
  Treap s;

  start=clock();

  //inserting 100 items in order
  for(int i=1;i<100;i++)
  {
    s.insert(i);
  }
  stop=clock();

  double time = double(stop-start) / CLOCKS_PER_SEC;
  cout << "\ntime taken: " <<time<< " seconds" <<endl;

  //removing a random node
  start=clock();
  cout << s.remove(49) << endl;
  stop=clock();

  time = double(stop-start) / CLOCKS_PER_SEC;
  cout << "\ntime taken: " <<time<< " seconds" <<endl;

  //searching for a random node
  start=clock();
  cout << s.search(85) << endl;
  stop=clock();

  time = double(stop-start) / CLOCKS_PER_SEC;
  cout << "\ntime taken: " <<time<< " seconds" <<endl;

}
