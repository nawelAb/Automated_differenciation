#include "diffTree.h"
#include "values.h" 
namespace ourlibs {
   diffTree::diffTree() 
{   diff = new diffTree[2];
    values = new values[2];;
    ourOperator = ("");
    power = 0.0;
}


   diffTree::diffTree(const diffTree& d1, const diffTree& d2)
{    diff[0] = d1;
     diff[1] = d2;      
}
   diffTree::diffTree(values val1, diffTree& d1)
{   
    values[0] = val1;
    diff[0] = d1.diff;
    ourOperator = d1.ourOperator;
}
  diffTree::diffTree(values val1, values val2)
{       values[0] = val1;
        values[1] = val2;
}
  diffTree::diffTree~()
{  delete[] diff;
   delete[] values;
}
//crée un difftree a partir de deux éléments
  diffTree& operator=(diffTree& d1)
{      diff = d1.diff;
       values = d1.values;
       ourOperator = d1.ourOperator;
}
  diffTree& operator*(double n)
{
}
  diffTree& operator*(values& )
{
}
  diffTree& operator*(diffTree*)
{
}
  diffTree& operator*(double)
{
}
  diffTree& operator+(values*)
{
}
  diffTree& operator+(diffTree*)
{
}

  void replaceDiff(int, values)
{
}

  values* resolution()
{
}
}






