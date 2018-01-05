#include "diffTree.h"
#include "values.h" 
namespace ourlibs {
  
  diffTree::diffTree() 
{   tabdiff = nullptr;
    tabvalues = nullptr;
    ourOperator = "";
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

// arbre de résolution recursive 
values* resolution() {   
  if(tabdiff[0] != nullptr) 
    tabdiff[0].resolution(); 

  if(tabdiff[1] != nullptr) 
    tabdiff[1].resolution();

  tab_size = tabvalues[0].size();
    
  swicth (ourOperator) :   
    case ("add") : {
     
      values tmp = values(tab_size) ;  
      tmp = tabvalues[0] + tabvalues[1] ;
      return tmp;
      break;
    }

    case ("sub") : {

      values tmp = values(tab_size) ;  
      tmp = tabvalues[0] - tabvalues[1] ;
      return tmp;       
      break;
    } 

    case ("pow") : {
    // le double du diffTree est considéré comme une puissance 
    // power  *  x puissance (power - 1)
    values tmp = values(tab_size) ; 
    if (this.n == 0)
      tmp.tabvalues = 1;
    tmp.tabvalues = n * std::pow(tabvalues[0], n-1);
    
    return tmp;
    break;
    } 

    case ("mul") : {        
      
      values tmp    = values(tab_size) ; 
      
      // diff & double 
      if(this.n != 0 )
          tmp.tabvalues = n * tabvalues[0] + n *tabvalues[1] ;      

      //return tmp; 
    break;
    }     
  }
}




