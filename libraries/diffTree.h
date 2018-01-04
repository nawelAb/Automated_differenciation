#include "values.h"
#include <string>

namespace ourlibs{
	class diffTree{
	private:
		diffTree** tabdiff;
		values* tabvalues;
		std::string ourOperator;
        double n;
	public:
		
		//constructeur pour les 3 cas possibles
		
		diffTree();
		diffTree(diffTree*, diffTree*, char);
		diffTree(values*, diffTree*, char);
		diffTree(values*, values*, char);
                diffTree(diffTree*, double, char);
		diffTree(values*, double, char);
		~diffTree();

/*
		//crée un difftree a partir de deux éléments
                diffTree& operator=(diffTree&);
		diffTree operator*(double);
		diffTree operator*(values*);
		diffTree operator*(diffTree*);
		
		//forme d'un objet values (@)
		values* resolution();

	};

                diffTree operator*(double,diffTree*);
		diffTree operator+(values*, diffTree*);
		*/

};
}


