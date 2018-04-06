#include <assert.h>
#include <omp.h>

/** \file libs.h
 * Ce fichier contient la totalite des classes et structures necessaires 
 * au fonctionnement de la differenciation automatique
 */

/** \namespace ad
 * espace de nommage regroupant les outils utilises pour la 
 * differentiation automatique
 */
namespace ad
{
	/** \class ad_value
	 * Cette classe contient la valeur de la variable ainsi que ses derivees
	 */
	class ad_value
	{
		public:

		/** 
		 * \brief Constructeur par defaut de ad_value
		 */
		inline ad_value(){
			v=0.;
			dv=nullptr;
			n=0;
		}
		/** 
		 * \brief Constructeur avec parametres de ad_value
		 * \param a : valeur de la variable
		 * \param b : nombre de derivees
		 * \param p : position de la derivee par rapport a la variable courante
		 */
		inline ad_value(double a,int b, int p){
			v=a;
			n=b;
			dv=new double[n];
			#pragma omp parallel for
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

		/** 
		 * \brief methode qui retourne la valeur de la variable
		 * \return v : valeur de la variable
		 */
		inline auto value() { return v; }

		/** 
		 * \brief methode qui retourne la valeur de la variable en constante
		 * \return v : valeur de la variable
		 */		
		inline const auto value() const { return v; }

		/** 
		 * \brief methode qui retourne la valeur de la variable en constante
		 * \param i : indice de la variable par laquelle on veut deriver
		 * \return dv[i] : valeur de la derivee de la variable selon la variable i
		 */
		inline auto gradient(int i) { return dv[i]; }

		/** 
		 * \brief methode qui retourne la valeur de la variable en constante
		 * \param i : indice de la variable par laquelle on veut deriver
		 * \return dv[i] : valeur de la derivee de la variable selon la variable i
		 */
		inline const auto gradient(int i) const { return dv[i]; }
		
		//inline const get_width(){return n;}

		private:
			/** \brief valeur de la variable
			 */
			double v;
			/** \brief tableau des derivees de la variable
			 */
			double* dv;
			/** \brief nombre de derivées de la valeur
			 */
			int n; 
	};

	/** \struct mult
	 * structure multiplication pour le traitement des valeurs de multiplications et de leurs derivees
	 */
	struct mult
	{
		/**
		 * \brief methode qui calcule la valeur de l'operation
		 * \param left : valeur de l'objet à gauche de l'operateur
		 * \param right : valeur de l'objet à droite de l'operateur
		 */
		inline static auto value(double left, double right)
		{
			return left * right;
		}

		/**
		 * \brief methode qui calcule la derivee en i de l'operation (derivee en a,b,c ...)
		 * \param left : valeur de l'objet à gauche de l'operateur
		 * \param right : valeur de l'objet à droite de l'operateur
		 * \param dleft : valeur de la derivee de l'objet à gauche de l'operateur
		 * \param dright : valeur de la derivee de l'objet à droite de l'operateur
		 */
		inline static auto gradient(double left, double dleft, double right, double dright)
		{
			return dleft * right + left * dright;
		}
	};

	/** \struct divs
	 * structure division pour le traitement des valeurs de division et de leurs derivees
	 */
	struct divs
	{
		/**
		 * \brief methode qui calcule la valeur de l'operation
		 * \param left : valeur de l'objet à gauche de l'operateur
		 * \param right : valeur de l'objet à droite de l'operateur
		 */
		inline static auto value(double left, double right)
		{
			assert(right!=0.); //verification si le dénomminateur est non nul
		  	return left / right;	
		}

		/**
		 * \brief methode qui calcule la derivee en i de l'operation (derivee en a,b,c ...)
		 * \param left : valeur de l'objet à gauche de l'operateur
		 * \param right : valeur de l'objet à droite de l'operateur
		 * \param dleft : valeur de la derivee de l'objet à gauche de l'operateur
		 * \param dright : valeur de la derivee de l'objet à droite de l'operateur
		 */
		inline static auto gradient(double left, double dleft, double right, double dright)
		{
			assert(right!=0.); //verification si le dénomminateur est non nul
		  	return (dleft * right - left * dright)/(right*right);
		}

	};

	/** \struct add
	 * structure addition pour le traitement des valeurs d'addition et de leurs derivees
	 */
	struct add
	{
		/**
		 * \brief methode qui calcule la valeur de l'operation
		 * \param left : valeur de l'objet à gauche de l'operateur
		 * \param right : valeur de l'objet à droite de l'operateur
		 */
		inline static auto value(double left, double right)
		{
			return left + right;
		}

		/**
		 * \brief methode qui calcule la derivee en i de l'operation (derivee en a,b,c ...)
		 * \param left : valeur de l'objet à gauche de l'operateur
		 * \param right : valeur de l'objet à droite de l'operateur
		 * \param dleft : valeur de la derivee de l'objet à gauche de l'operateur
		 * \param dright : valeur de la derivee de l'objet à droite de l'operateur
		 */
		inline static auto gradient(double left, double dleft, double right, double dright)
		{
			return dleft + dright;
		}
	};

	/** \struct sub
	 * structure soustraction pour le traitement des valeurs de soustraction et de leurs derivees
	 */
	struct sub
	{
		/**
		 * \brief methode qui calcule la valeur de l'operation
		 * \param left : valeur de l'objet à gauche de l'operateur
		 * \param right : valeur de l'objet à droite de l'operateur
		 */
		inline static auto value(double left, double right)
		{	
			return left - right;
		}

		/**
		 * \brief methode qui calcule la derivee en i de l'operation (derivee en a,b,c ...)
		 * \param left : valeur de l'objet à gauche de l'operateur
		 * \param right : valeur de l'objet à droite de l'operateur
		 * \param dleft : valeur de la derivee de l'objet à gauche de l'operateur
		 * \param dright : valeur de la derivee de l'objet à droite de l'operateur
		 */
		inline static auto gradient(double left, double dleft, double right, double dright)
		{
			return dleft - dright;
		}
	};

	/** \struct pui
	 * structure puissance pour le traitement des valeurs de puissance et de leurs derivees
	 */
	struct pui
	{
		/**
		 * \brief methode qui calcule la valeur de l'operation
		 * \param left : valeur de l'objet à gauche de l'operateur
		 * \param power : puissance de l'operation
		 */
		inline static auto value(double left, double power)
		{
			return pow(left,power);
		}

		/**
		 * \brief methode qui calcule la derivee en i de l'operation (derivee en a,b,c ...)
		 * \param left : valeur de l'objet à gauche de l'operateur
		 * \param right : valeur de l'objet à droite de l'operateur
		 * \param dleft : valeur de la derivee de l'objet à gauche de l'operateur
		 * \param dright : valeur de la derivee de l'objet à droite de l'operateur
		 */
		inline static auto gradient(double left, double dleft, double power, double dright)
		{
			return power * pow(left,power-1.)*dleft;
		}
	};

	/** \struct cosi
	 * structure cosinus pour le traitement des valeurs de cosinus et de leurs derivees
	 */
	struct cosi
	{
		/**
		 * \brief methode qui calcule la valeur de l'operation
		 * \param left : valeur de l'objet à gauche de l'operateur
		 * \param none : valeur non utilisée mise pour la cohérence des operateurs
		 */
		inline static auto value(double left, double none)
		{
			return cos(left);
		}

		/**
		 * \brief methode qui calcule la derivee en i de l'operation (derivee en a,b,c ...)
		 * \param left : valeur de l'objet à gauche de l'operateur
		 * \param right : valeur de l'objet à droite de l'operateur
		 * \param dleft : valeur de la derivee de l'objet à gauche de l'operateur
		 * \param dright : valeur de la derivee de l'objet à droite de l'operateur
		 */
		inline static auto gradient(double left, double dleft, double right, double dright)
		{
			return dleft*sin(left);
		}
	};

	/** \struct sinu
	 * structure sinus pour le traitement des valeurs de sinus et de leurs derivees
	 */
	struct sinu
	{
		/**
		 * \brief methode qui calcule la valeur de l'operation
		 * \param left : valeur de l'objet à gauche de l'operateur
		 * \param none : valeur non utilisée mise pour la cohérence des operateurs
		 */
		inline static auto value(double left, double none)
		{
			return sin(left);
		}

		/**
		 * \brief methode qui calcule la derivee en i de l'operation (derivee en a,b,c ...)
		 * \param left : valeur de l'objet à gauche de l'operateur
		 * \param right : valeur de l'objet à droite de l'operateur
		 * \param dleft : valeur de la derivee de l'objet à gauche de l'operateur
		 * \param dright : valeur de la derivee de l'objet à droite de l'operateur
		 */
		inline static auto gradient(double left, double dleft, double right, double dright)
		{
			return -dleft*cos(left);
		}
	};

	/** \struct expo
	 * structure exponentiel pour le traitement des valeurs d'exponentiel et de leurs derivees
	 */
	struct expo
	{
		/**
		 * \brief methode qui calcule la valeur de l'operation
		 * \param left : valeur de l'objet multipliable à gauche de l'operateur
		 * \param none : valeur non utilisée mise pour la cohérence des operateurs
		 */
		inline static auto value(double left, double none)
		{
			return exp(left);
		}

		/**
		 * \brief methode qui calcule la derivee en i de l'operation (derivee en a,b,c ...)
		 * \param left : valeur de l'objet à gauche de l'operateur
		 * \param right : valeur de l'objet à droite de l'operateur
		 * \param dleft : valeur de la derivee de l'objet à gauche de l'operateur
		 * \param dright : valeur de la derivee de l'objet à droite de l'operateur
		 */
		inline static auto gradient(double left, double dleft, double right, double dright)
		{
			return dleft*exp(left);
		}
	};

	/** \struct binop
	 * \brief structure binop pour le cas général entre des ad_value et des binop 
	 * \brief op est l'operateur qui a ete appelle
	 */
	template<class E1, class E2, class op>
	struct binop
	{
		/**
		 * \brief objet de type E1 qui est l'objet a gauche
		 */
		const E1 left;

		/**
		 * \brief objet de type E2 qui est l'objet a droite
		 */
		const E2 right;

		/**
		 * \brief Constructeur de la classe 
		 * \param left : objet de type ad_value ou binop qui correspond à l'element à gauche de l'operation
		 * \param right : objet de type ad_value ou binop qui correspond à l'element à droite de l'operation
		 */
		inline binop(const E1 left, const E2 right)
		: left(left)
		, right(right) {}

		/**
		 * \brief methode qui calcule la valeur de l'operation en demandant à l'operateur de faire les operations entre les valeurs
		 */
		inline double value() const { return op::value(left.value(), right.value()); }
		
		/**
		 * \brief methode qui calcule la derivee en i de l'operation en demandant à l'operateur de faire les operations entre les derivees
		 * \param i : indice des derivees
		 */
		inline double gradient(int i) const
		{
		return op::gradient(left.value(), left.gradient(i),
							right.value(), right.gradient(i));
		}
	};

	/// structure binop pour le cas d'un double à gauche
	/** \struct binop<double,E2,op>
	 * \brief structure binop pour le cas entre un double a gauche et des binop ou ad_value a droite
	 * \brief op est l'operateur qui a ete appelle
	 */
	template<class E2, class op>
	struct binop<double , E2 , op>
	{

		/**
		 * \brief objet de type double qui est l'objet a gauche
		 */
		const double left;
		/**
		 * \brief objet de type E2 qui est l'objet a droite
		 */
		const E2 right;

		/**
		 * \brief Constructeur de la classe 
		 * \param left : objet de type double qui correspond à l'element à gauche de l'operation
		 * \param right : objet de type ad_value ou binop qui correspond à l'element à droite de l'operation
		 */
		inline binop(const double left, const E2 right)
			: left(left)
			, right(right) {}

		/**
		 * \brief methode qui calcule la valeur de l'operation en demandant à l'operateur de faire les operations entre les valeurs
		 */
		inline double value() const { return op::value(left, right.value()); }
		/**
		 * \brief methode qui calcule la derivee en i de l'operation en demandant à l'operateur de faire les operations entre les derivees
		 * \param i : indice des derivees
		 */
		inline double gradient(int i) const
		{
			return op::gradient(left, 0.,
								right.value(), right.gradient(i));
		}
	};

	/** \struct binop<double,E2,op>
	 * \brief structure binop pour le cas entre un double a droite et des binop ou ad_value a droite
	 * \brief op est l'operateur qui a ete appelle
	 */
	template<class E1, class op>
	struct binop<E1 , double , op>
	{

		/**
		 * \brief objet de type E1 qui est l'objet a gauche
		 */
		const E1 left;
		/**
		 * \brief objet de type double qui est l'objet a gauche
		 */
		const double right;

		/**
		 * \brief Constructeur de la classe 
		 * \param left : objet de type ad_value ou binop qui correspond à l'element à gauche de l'operation
		 * \param right : objet de type double qui correspond à l'element à droite de l'operation
		 */
		inline binop(const E1 left, const double right)
			: left(left)
			, right(right) {}

		/**
		 * \brief methode qui calcule la valeur de l'operation en demandant à l'operateur de faire les operations entre les valeurs
		 */
		inline double value() const { return op::value(left.value(), right); }
		/**
		 * \brief methode qui calcule la derivee en i de l'operation en demandant à l'operateur de faire les operations entre les derivees
		 * \param i : indice des derivees
		 */
		inline double gradient(int i) const
		{
			return op::gradient(left.value(), left.gradient(i),
								right, 0.);
		}

	};

	/** /fn binop<E1, E2, mult> operator * (const E1, const E2)
	 * /brief operateur de multiplication pour les interractions avec des elements ad_value ou binop
	 */
	template<class E1, class E2>
	binop<E1, E2, mult>  operator*(const E1 left, const E2 right)
	{
	  	return binop<E1, E2, mult>(left, right);
	}

	/** /fn binop<E1, E2, divs> operator/(const E1, const E2)
	 * /brief operateur de division pour les interractions avec des elements ad_value ou binop
	 */
	template<class E1, class E2>
	binop<E1, E2, divs>  operator/(const E1 left, const E2 right)
	{
	  	return binop<E1, E2, divs>(left, right);
	}

	/** /fn binop<E1, E2, add> operator+(const E1, const E2)
	 * /brief operateur d'addition pour les interractions avec des elements ad_value ou binop
	 */
	template<class E1, class E2>
	binop<E1, E2, add>  operator+(const E1 left, const E2 right)
	{
	  	return binop<E1, E2,add> (left, right); 
	}

	/** /fn binop<E1, E2, sub> operator-(const E1, const E2)
	 * /brief operateur de soustraction pour les interractions avec des elements ad_value ou binop
	 */
	template<class E1, class E2>
	binop<E1, E2, sub>  operator-(const E1 left, const E2 right)
	{
	  	return binop<E1, E2, sub>(left, right); 
	}

	/** /fn binop<E1, E2, sub> operator-(const E2)
	 * /brief operateur moins unitaire pour les interractions avec des elements ad_value ou binop
	 */
	template< class E2>
	binop<double, E2, sub>  operator-( const E2 right)
	{
	  	return binop<double, E2, sub>(0., right); 
	}

	/** /fn binop<E1, E2, puis> puis(const E1, double)
	 * /brief operateur de puissance pour les interractions avec des elements ad_value ou binop
	 */
	template< class E1>
	binop<E1, double, pui>  puis( const E1 left,double power)
	{
	  	return binop<E1, double, pui>(left, power); 
	}

	/** /fn binop<E1, E2, cosi> operator * (const E1, const E2)
	 * /brief operateur multiplication pour les interractions avec des elements ad_value ou binop
	 */
	template< class E1>
	binop<E1, double, cosi>  cos( const E1 left)
	{
	  	return binop<E1, double, cosi>(left, 0.); 
	}

	/// operateur sinus pour les objets ad_value ou binop	
	/** /fn binop<E1, E2, sinu> sin(const E1)
	 * /brief operateur sinus pour les interractions avec des elements ad_value ou binop
	 */
	template< class E1>
	binop<E1, double, sinu>  sin( const E1 left)
	{
	  	return binop<E1, double, sinu>(left, 0.); 
	}

	/// operateur exponentiel pour les objets ad_value ou binop	
	/** /fn binop<E1, E2, expo> exp(const E1)
	 * /brief operateur exponentiel pour les interractions avec des elements ad_value ou binop
	 */
	template< class E1>
	binop<E1, double, expo>  exp( const E1 left)
	{
	  	return binop<E1, double, expo>(left,0.); 
	}
}
