
#include "diffTree.h"
#include "values.h" 

namespace ourlibs {

  diffTree::diffTree() 
{   tabdiff = nullptr;
    tabvalues = nullptr;
    ourOperator = '0';
    n = 0.0;
}


   diffTree::diffTree(diffTree* d1, diffTree* d2, char op)
{    tabdiff= new diffTree*[2];
     tabvalues = new values[2];
     tabdiff[0] = d1;
     tabdiff[1] = d2;
     //tabvalues[0] = NULL;
    // tabvalues[1] = NULL;
     ourOperator = op; 
     n = 0.0;       
}

   diffTree::diffTree(values val1, diffTree* d1, char op)
{    tabdiff= new diffTree*[2];
     tabvalues = new values[2];
     tabdiff[0] = nullptr;
     tabdiff[1] = d1;
     tabvalues[0] = val1;
     //tabvalues[1] = NULL;
     ourOperator = op;
     n = 0.0;  
}

  diffTree::diffTree(diffTree* d1, double s, char op )
{    tabdiff= new diffTree*[2];
     tabvalues = new values[2];
     tabdiff[0] = nullptr;
     tabdiff[1] = d1;
     //tabvalues[0] = NULL;
     //tabvalues[1] = NULL;
     ourOperator = op; 
     n = s;   
}
  diffTree::diffTree(values val1, double s, char op  )
{    tabdiff= new diffTree*[2];
     tabvalues = new values[2];
     tabdiff[0] = nullptr;
     tabdiff[1] = nullptr;
     tabvalues[0] = val1;
     //tabvalues[1] = NULL;
     ourOperator = op; 
     n = s;   
}
  diffTree::~diffTree()
{  
  for(int i=0; i<2 ; i++)
  {
    delete[] tabdiff[i];
  }
  delete[] tabdiff;
  delete[] tabvalues;
}

//crée un difftree a partir de deux éléments

  diffTree diffTree::operator*(double s)
{    
    diffTree branche(this,s, 'm');    
}

  diffTree diffTree::operator*(values val1 )
{
    diffTree branche(val1, this, 'm'); 
}

  diffTree diffTree::operator*(diffTree* d1)
{
    diffTree branche(this, d1, 'm'); 
}

  diffTree diffTree::operator+(values val1)
{
    diffTree branche(val1, this, 'a');
}
  diffTree diffTree::operator+(diffTree* d1)
{
    diffTree branche(this, d1, 'a'); 
}
diffTree diffTree::operator+(double s)
{
    diffTree branche(this, s, 'a'); 
}
diffTree diffTree::operator-(values val1)
{
    diffTree branche(val1, this, 's'); 
}
 diffTree diffTree::operator-(diffTree* d1)
{
    diffTree branche(this, d1, 's'); 
}
diffTree diffTree::operator-(double s)
{
    diffTree branche(this, s, 's'); 
}

diffTree diffTree::puissance(values val1, double s)
{
    diffTree branche(val1, s, 'p'); 
}



diffTree operator*(double s, diffTree d1 )   
{
    diffTree branche(&d1, s, 'm'); 
}

diffTree operator*(values val1, diffTree* d1 )
{
    diffTree branche(val1, d1, 'm'); 
}

diffTree operator+(values val1, diffTree* d1)
{
    diffTree branche(val1, d1, 'a');
}
diffTree operator+(double s, diffTree d1)  
{
    diffTree branche(&d1, s, 'a'); 
}

diffTree operator-(values val1, diffTree* d1)
{
    diffTree branche(val1, d1, 's'); 
}
diffTree operator-(double s, diffTree d1)
{
    diffTree branche(&d1, s, 's'); 

}

/*
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






