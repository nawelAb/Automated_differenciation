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

    values* resolution() {   // arbre de résolution recursive 
   
  	if(diff[0] != nullptr) 
      diff[0].resolution(); 

    if(diff[1] != nullptr) 
      diff[1].resolution();

 
    swicth (ourOperator) : 
    case ("pow") : {
      // l entier de la classe diffTree est considéré 
      //comme une puissance 
      values tmp = values(m_tabdiv[0].size()) ; // cree un objet tmp 
     // power  *  x puissance (power - 1)
      tmp.values = m_tabdiv[0];
    // vérif du contenu de values pour voire si 
    //il faut faire appel au opérations values
     

    break;
    } 

    case ("mul") : {
      values tmp = values(m_tabdiv[1].size()) ;  
      tmp.values = m_tabdiv[1];

    break;
    } 

    case ("add") : {
      values tmp = values(m_tabdiv[1].size()) ;  
      tmp.m_tabdiv = m_tabdiv[1]; // result 

    break;
    } 
  }


}






