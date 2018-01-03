namespace ourlibs{
	class diffTree{
	private:
		diffTree** diff;
		values* values;
		char ourOperator[4];
                double n;
	public:
		//constructeur pour les 3 cas possibles
		diffTree(diffTree, diffTree);
		diffTree(values, diffTree);
		diffTree(values, values);
                diiffTree(diffTree, double);
		diffTree~();

		//crée un difftree a partir de deux éléments
                diffTree& operator=(diffTree&);
		diffTree operator*(double);
		diffTree operator*(values);
		diffTree operator*(diffTree&);
		diffTree operator*(double);
		diffTree operator+(values);
		diffTree operator+(diffTree&);


		//forme d'un objet values (@)
		values* resolution();

	};
};
