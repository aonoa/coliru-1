// Tripcode@Home Rules!
//
// Author: LLD!5DeRpYLOvE

#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;
using std::cout;
using std::endl;

// Proof m00t is a faggot.
void my_funky_func()
{
   // Initialize two string vectors.
   vector<string> moot{"m00t", "moot", "m0ot"};
   vector<string> faggot{"faggot", "fag00t", "fagOOt"};
   vector<string> moot_is_faggot(3);

   for (int idx = 0; idx < 3; ++idx)
      moot_is_faggot[idx] = moot[idx] + " is " + faggot[idx];

   for (int idx = 0; idx < 3; ++idx)
      cout << moot_is_faggot[idx] << endl;
}

// the entry point for all C++ apps
int main()
{
    my_funky_func();
}
