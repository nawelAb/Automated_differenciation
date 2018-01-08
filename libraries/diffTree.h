#include "values.h"
#include <string>

namespace ourlibs{
	class diffTree{
	private:
		diffTree** tabdiff;
		values* tabvalues;
		char ourOperator;
        double n;
	public:
		
		//constructeur pour les 3 cas possibles
		
		diffTree();
		diffTree(diffTree* d1, diffTree* d2, char op);
		diffTree(values val1, diffTree* d1, char op);
		diffTree(diffTree* d1, double s, char op );
		diffTree(values val1, double s, char op );
		~diffTree();
		


		//crée un difftree a partir de deux éléments
		diffTree operator*(double s);
		diffTree operator*(values val1 );
		diffTree operator*(diffTree* d1);
		diffTree operator+(values val1);
		diffTree operator+(diffTree* d1);
		diffTree operator+(double s);
		diffTree operator-(values val1);
		diffTree operator-(diffTree* d1);
		diffTree operator-(double s);

		diffTree puissance(values val1, double s);

/*

		
		//forme d'un objet values (@)
		values* resolution();
*/
	};

        diffTree operator*(double s, diffTree d1 ); 
		diffTree operator*(values val1, diffTree* d1 );

		diffTree operator+(values val1, diffTree* d1);
		diffTree operator+(double s, diffTree d1); 

		diffTree operator-(values val1, diffTree* d1);
		diffTree operator-(double s, diffTree d1); 




}


