namespace ourlibs{
	class values{
	private:
		double value;
		double* tabvalues;
	public:
		//constructeur pour les 3 cas possibles
		diffTree(ourlibs::diffTree,ourlibs::diffTree);
		diffTree(ourlibs::values,ourlibs::diffTree);
		diffTree(ourlibs::values,ourlibs::values);
		diffTree~();

		//crée un difftree a partir de deux éléments
		// "values && values" ou "difftree && values"
		// ou bien "difftree && double"
		values* operator*(double);
		values* operator*(ourlibs::values*);
		diffTree* operator*(ourlibs::diffTree*);

		values* operator+(double);
		values* operator+(ourlibs::values*);
		diffTree* operator+(ourlibs::diffTree*);

	};
};
