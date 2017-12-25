namespace ourlibs{
	class values{
	private:
		double value;
		double* tabvalues;
	public:
		//constructeur pour les 3 cas possibles
		values(double,const std::size_t,const std::size_t);
		diffTree~();

		//crée un difftree a partir de deux éléments
		// "values && values" ou "difftree && values"
		// ou bien "difftree && double"
		values* operator*(double);
		values* operator*(values*);
		diffTree* operator*(diffTree*);

		values* operator+(double);
		values* operator+(values*);
		diffTree* operator+(diffTree*);

	};
};
