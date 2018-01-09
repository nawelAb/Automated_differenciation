#include <assert.h>
namespace ad
{
	class vector
	{
		public:
		inline auto value() { return v; }
		inline const auto value() const { return v; }

		inline vector(){
			v=0.;
			dv=nullptr;
		}
		inline vector(double a,int b, int p){
			v=a;
			dv=new double[b];
			for (int i=0; i<b; i++)
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

		inline auto gradient(int i) { return dv[i]; }
		inline const auto gradient(int i) const { return dv[i]; }
		
		private:
		double v;
		double* dv;
	};

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
	//structure division
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

	//structure addition 
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

	//structure substraction 
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

	//structure puissance 
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

	//structure cos 
	struct cosi
	{
		inline static auto value(double left, double power)
		{
			return cos(left);
		}

		inline static auto gradient(double left, double dleft, double power, double dright)
		{
			return dleft*sin(left);
		}
	};

	//structure sin 
	struct sinu
	{
		inline static auto value(double left, double power)
		{
			return sin(left);
		}

		inline static auto gradient(double left, double dleft, double power, double dright)
		{
			return -dleft*cos(left);
		}
	};

	//structure expo 
	struct expo
	{
		inline static auto value(double left, double power)
		{
			return exp(left);
		}

		inline static auto gradient(double left, double dleft, double power, double dright)
		{
			return dleft*exp(left);
		}
	};

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

	template<class E1, class E2>
	binop<E1, E2, mult>  operator*(const E1 left, const E2 right)
	{
	  	return binop<E1, E2, mult>(left, right);
	}

	// je fais meme chose pour /
	template<class E1, class E2>
	binop<E1, E2, divs>  operator/(const E1 left, const E2 right)
	{
	  	return binop<E1, E2, divs>(left, right);
	}

	// je fais meme chose pour +
	template<class E1, class E2>
	binop<E1, E2, add>  operator+(const E1 left, const E2 right)
	{
	  	return binop<E1, E2,add> (left, right); 
	}

	// je fais la meme chose pour -
	template<class E1, class E2>
	binop<E1, E2, sub>  operator-(const E1 left, const E2 right)
	{
	  	return binop<E1, E2, sub>(left, right); 
	}

	// je fais la meme chose pour - unitaire
	template< class E2>
	binop<double, E2, sub>  operator-( const E2 right)
	{
	  	return binop<double, E2, sub>(0., right); 
	}

	// je fais la meme chose pour puissance
	template< class E1>
	binop<E1, double, pui>  puis( const E1 left,double power)
	{
	  	return binop<E1, double, pui>(left, power); 
	}

	// je fais la meme chose pour cos
	template< class E1>
	binop<E1, double, cosi>  cos( const E1 left)
	{
	  	return binop<E1, double, cosi>(left, 0.); 
	}

	// je fais la meme chose pour sin
	template< class E1>
	binop<E1, double, sinu>  sin( const E1 left)
	{
	  	return binop<E1, double, sinu>(left, 0.); 
	}

	// je fais la meme chose pour expo
	template< class E1>
	binop<E1, double, expo>  exp( const E1 left)
	{
	  	return binop<E1, double, expo>(left,0.); 
	}
}