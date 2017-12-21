namespace ourlibs{
	class values{  /////lache moi
	private:
		double value;
		double* tabvalues;
	public:
		//constructeur pour les 3 cas possibles
		values(double,const std::size_t,const std::size_t);
		diffTree~();

		//crée un difftree a partir de deux éléments
		values* operator*(double);
		values* operator*(ourlibs::values*);
		diffTree* operator*(ourlibs::diffTree*);

		values* operator+(double);
		values* operator+(ourlibs::values*);
		diffTree* operator+(ourlibs::diffTree*);

	};
};
