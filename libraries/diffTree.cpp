#include "diffTree.h"
#include "values.h" 
namespace ourlibs {
  
  diffTree::diffTree() 
{   tabdiff = nullptr;
    tabvalues = nullptr;
    ourOperator = " ";
    n = 0.0;
}


   diffTree::diffTree(diffTree* d1, diffTree* d2, char op[4])
{    tabdiff** tabdiff= new diffTree[2];
     tabvalues* tabvalues = new values[2];
     tabdiff[0] = d1;
     tabdiff[1] = d2;
     tabvalues[0] = NULL;
     tabvalues[1] = NULL;
     ourOperator = op; 
     n = 0.0;       
}
   diffTree::diffTree(values val1, diffTree* d1, char op[4])
{    tabdiff** tabdiff= new diffTree[2];
     tabvalues* tabvalues = new values[2];
     tabdiff[0] = nullptr;
     tabdiff[1] = d1;
     tabvalues[0] = val1;
     tabvalues[1] = NULL;
     ourOperator = op; 
     n = 0.0;  
}
  diffTree::diffTree(diffTree* d1, double s, char op[4] )
{    tabdiff** tabdiff= new diffTree[2];
     tabvalues* tabvalues = new values[2];
     tabdiff[0] = nullptr;
     tabdiff[1] = d1;
     tabvalues[0] = NULL;
     tabvalues[1] = NULL;
     ourOperator = op;
     n = s;   
}
  diffTree::diffTree(values* val1, double s, char op[4]  )
{    tabdiff** tabdiff= new diffTree[2];
     tabvalues* tabvalues = new values[2];
     tabdiff[0] = nullptr;
     tabdiff[1] = nullptr;
     tabvalues[0] = val1;
     tabvalues[1] = NULL;
     ourOperator = op;
     n = s;   
}
  diffTree::diffTree~()
{  delete diff[] diff;
   delete[] values;
}
/*
//crée un difftree a partir de deux éléments
  diffTree& operator=(diffTree& d1)
{      diff = d1.diff;
       values = d1.values;
       ourOperator = d1.ourOperator;
       n = d1.n;
}
  diffTree operator*(double n)
{    
    diffTree branche(this,n, "mul");    
}
  diffTree operator*(values* val1 )
{
    diffTree branche(val1, this, "mul"); 
}

  diffTree operator*(diffTree* d1)
{
    diffTree branche(this, d1, "mul"); 
}
  diffTree operator*(double n)
{
    diffTree branche(this, n, "mul"); 
}
  diffTree operator+(values* val1)
{
    diffTree branche(val1, this, "add");
}
  diffTree operator+(diffTree* d1)
{
    diffTree branche(this, d1, "add"); 
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
  */
}






