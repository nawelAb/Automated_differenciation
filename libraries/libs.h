#include <assert.h>
namespace ad
{
	class ad_value
	{
		public:
		inline auto value() { return v; }
		inline const auto value() const { return v; }

		inline ad_value(){
			v=0.;
			dv=nullptr;
			n=0;
		}
		inline ad_value(double a,int b, int p){
			v=a;
			n=b;
			dv=new double[n];
			for (int i=0; i<n; i++)
			{
				if(i == p-1)
				{ 
					dv[i]=1; 
				}
				else
				{
					dv[i]=0;
				}
			}
		}
               /* ~ad_value()
                        {
                          delete [] dv;
                         }
               */
		inline auto gradient(int i) { return dv[i]; }
		inline const auto gradient(int i) const { return dv[i]; }
		
		//inline const size(){return n;}

		private:
		double v;
		double* dv;
		int n; //nombre de variables/dérivées
	};
        
	///structure multiplication pour le traitement des valeurs de multiplications et de leurs derivees
	struct mult
	{
		inline static auto value(double left, double right)
		{
			return left * right;
		}

		inline static auto gradient(double left, double dleft, double right, double dright)
		{
			return dleft * right + left * dright;
		}
	};
	///structure division pour le traitement des valeurs de division et de leurs derivees
	struct divs
	{
		inline static auto value(double left, double right)
		{
			assert(right!=0.); //verification si le dénomminateur est non nul
		  	return left / right;	
		}

		inline static auto gradient(double left, double dleft, double right, double dright)
		{
			assert(right!=0.); //verification si le dénomminateur est non nul
		  	return (dleft * right - left * dright)/(right*right);
		}

	};

	///structure addition pour le traitement des valeurs d'addition et de leurs derivees
	struct add
	{
		inline static auto value(double left, double right)
		{
			return left + right;
		}

		inline static auto gradient(double left, double dleft, double right, double dright)
		{
			return dleft + dright;
		}
	};

	///structure soustraction pour le traitement des valeurs de soustraction et de leurs derivees
	struct sub
	{
		inline static auto value(double left, double right)
		{	
			return left - right;
		}
		inline static auto gradient(double left, double dleft, double right, double dright)
		{
			return dleft - dright;
		}
	};

	///structure puissance pour le traitement des valeurs de puissance et de leurs derivees
	struct pui
	{
		inline static auto value(double left, double power)
		{
			return pow(left,power);
		}

		inline static auto gradient(double left, double dleft, double power, double dright)
		{
			return power * pow(left,power-1.)*dleft;
		}
	};

	///structure expo pour le traitement des valeurs de cosinus et de leurs derivees
	struct cosi
	{
		inline static auto value(double left, double power)
		{
			return cos(left);
		}

		inline static auto gradient(double left, double dleft, double right, double dright)
		{
			return dleft*sin(left);
		}
	};

	///structure expo pour le traitement des valeurs de sinus et de leurs derivees
	struct sinu
	{
		inline static auto value(double left, double power)
		{
			return sin(left);
		}

		inline static auto gradient(double left, double dleft, double right, double dright)
		{
			return -dleft*cos(left);
		}
	};

	///structure expo pour le traitement des valeurs d'exponetiels et de leurs derivees
	struct expo
	{
		inline static auto value(double left, double power)
		{
			return exp(left);
		}

		inline static auto gradient(double left, double dleft, double right, double dright)
		{
			return dleft*exp(left);
		}
	};

	/// structure binop pour le cas général entre des ad_value et des binop
	template<class E1, class E2, class op>
	struct binop
	{

	  const E1 left;
	  const E2 right;

	  inline binop(const E1 left, const E2 right)
		: left(left)
		, right(right) {}

	  inline double value() const { return op::value(left.value(), right.value()); }
	  inline double gradient(int i) const
	  {
		return op::gradient(left.value(), left.gradient(i),
							right.value(), right.gradient(i));
	  }
	};

	/// specialisation de la structure binop pour le cas d'un double à gauche
	template<class E2, class op>
	struct binop<double , E2 , op>
	{

		const double left;
		const E2 right;

		inline binop(const double left, const E2 right)
			: left(left)
			, right(right) {}

		inline double value() const { return op::value(left, right.value()); }
		inline double gradient(int i) const
		{
			return op::gradient(left, 0.,
								right.value(), right.gradient(i));
		}
	};

	/// specialisation de la structure binop pour le cas d'un double à droite
	template<class E1, class op>
	struct binop<E1 , double , op>
	{

		const E1 left;
		const double right;

		inline binop(const E1 left, const double right)
			: left(left)
			, right(right) {}

		inline double value() const { return op::value(left.value(), right); }
		inline double gradient(int i) const
		{
			return op::gradient(left.value(), left.gradient(i),
								right, 0.);
		}

	};

	/// operateur multiplier pour les objets ad_value ou binop
	template<class E1, class E2>
	binop<E1, E2, mult>  operator*(const E1 left, const E2 right)
	{
	  	return binop<E1, E2, mult>(left, right);
	}

	/// operateur diviser pour les objets ad_value ou binop	
	template<class E1, class E2>
	binop<E1, E2, divs>  operator/(const E1 left, const E2 right)
	{
	  	return binop<E1, E2, divs>(left, right);
	}

	/// operateur addition pour les objets ad_value ou binop	
	template<class E1, class E2>
	binop<E1, E2, add>  operator+(const E1 left, const E2 right)
	{
	  	return binop<E1, E2,add> (left, right); 
	}

	/// operateur soustraction pour les objets ad_value ou binop	
	template<class E1, class E2>
	binop<E1, E2, sub>  operator-(const E1 left, const E2 right)
	{
	  	return binop<E1, E2, sub>(left, right); 
	}

	/// operateur moins unitaire pour les objets ad_value ou binop	
	template< class E2>
	binop<double, E2, sub>  operator-( const E2 right)
	{
	  	return binop<double, E2, sub>(0., right); 
	}

	/// operateur puissance pour les objets ad_value ou binop avec un double pour puissance	
	template< class E1>
	binop<E1, double, pui>  puis( const E1 left,double power)
	{
	  	return binop<E1, double, pui>(left, power); 
	}

	/// operateur cosinus pour les objets ad_value ou binop	
	template< class E1>
	binop<E1, double, cosi>  cos( const E1 left)
	{
	  	return binop<E1, double, cosi>(left, 0.); 
	}

	/// operateur sinus pour les objets ad_value ou binop	
	template< class E1>
	binop<E1, double, sinu>  sin( const E1 left)
	{
	  	return binop<E1, double, sinu>(left, 0.); 
	}

	/// operateur exponentiel pour les objets ad_value ou binop	
	template< class E1>
	binop<E1, double, expo>  exp( const E1 left)
	{
	  	return binop<E1, double, expo>(left,0.); 
	}
}
