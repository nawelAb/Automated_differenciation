namespace ourlibs{
	class values{
	private:
		double value;
		double* tabvalues;
	public:
		//constructeur pour les 3 cas possibles
		diffTree(diffTree,diffTree);
		diffTree(values, diffTree);
		diffTree(values, values);
		diffTree~();

		//crée un difftree a partir de deux éléments
		values* operator*(double);
		values* operator*(values*);
		diffTree* operator*(diffTree*);

		values* operator+(double);
		values* operator+(values*);
		diffTree* operator+(diffTree*);

	};
};
