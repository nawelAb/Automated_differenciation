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
		double gettabdiv( int i);
		
		//remplire (évité la recopie)
		
		double remplirval(double);
		double remplirtab(double,int);
		

		
		//crée un difftree a partir de deux éléments

		values operator*(double);
		values operator+(double);
		values operator+(values& v);
		values operator-(double);
		values operator-(values& v);
		//diffTree* operator+(ourlibs::diffTree*); Lynda
		//diffTree* operator*(ourlibs::diffTree*); Lynda

	};

    

	values operator*(double a, ourlibs::values v);
	values operator-(double a, ourlibs::values v);
	values operator+(double a, ourlibs::values v);


}

