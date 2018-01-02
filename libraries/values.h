namespace ourlibs{
	
	class values{
	
	
	private:
		int m_size;
		double m_v;
		double* m_tabdiv;
		
	public:
		//constructeur et déstructeur
		values(double  , int ,int);
		values(double  , int );
		
		//déstructeur
		~values();

		//accesseur 

		double getvalue();
		const int gettaille();
		double values::gettabdiv( int i);

		
		//crée un difftree a partir de deux éléments

		values operator*(double);
		//values* operator*(ourlibs::values*); on a pas besoin 
		//diffTree* operator*(ourlibs::diffTree*); on a pas besoin 
   		//values operator*(double a, ourlibs::values v); en bas

		values* operator+(double);
		values* operator+(ourlibs::values v);
		//diffTree* operator+(ourlibs::diffTree*); on a pas besoin 

	};

    
    values operator*(double a, ourlibs::values v);

}
