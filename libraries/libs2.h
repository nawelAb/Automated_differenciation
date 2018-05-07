#include <assert.h>
#include <omp.h>
#include <emmintrin.h>

/** \file libs.h
 * Ce fichier contient la totalite des classes et structures necessaires 
 * au fonctionnement de la differenciation automatique
 */

/** \namespace ad
 * espace de nommage regroupant les outils utilises pour la 
 * differentiation automatique
 */
namespace ad2
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
			v=nullptr;
			dv=nullptr;
			n=0;
		}
		/** 
		 * \brief Constructeur avec parametres de ad_value
		 * \param a : valeur de la variable
		 * \param b : nombre de derivees
		 * \param p : position de la derivee par rapport a la variable courante
		 */
		inline ad_value(float a,int b, int p){
			v=new float[4];
			n=b;
			if(b%4!=0){
				n+=(4-b%4);
			}
			dv=new float[n];
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
			for (int i=0; i<4; i++)
			{
				v[i]= a;
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
		inline auto gradient() { return dv; }

		/** 
		 * \brief methode qui retourne la valeur de la variable en constante
		 * \param i : indice de la variable par laquelle on veut deriver
		 * \return dv[i] : valeur de la derivee de la variable selon la variable i
		 */
		inline const auto gradient() const { return dv; }
		
		inline auto taille() { return n; }
		inline const auto taille() const { return n; }

		//inline const get_width(){return n;}

		private:
			/** \brief valeur de la variable
			 */
			float* v;
			/** \brief tableau des derivees de la variable
			 */
			float* dv;
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
		inline static auto value(float* left, float* right)
		{
			__m128* ptrlv = (__m128*)left;
			__m128* ptrrv = (__m128*)right;
			float* v = new float[4];

 			_mm_store_ps(v,  _mm_mul_ps ( *ptrlv, *ptrrv));

			return  v;
		}

		/**
		 * \brief methode qui calcule la derivee en i de l'operation (derivee en a,b,c ...)
		 * \param left : valeur de l'objet à gauche de l'operateur
		 * \param right : valeur de l'objet à droite de l'operateur
		 * \param dleft : valeur de la derivee de l'objet à gauche de l'operateur
		 * \param dright : valeur de la derivee de l'objet à droite de l'operateur
		 */
		//inline static auto gradient(float left, __m256d dleft, float right, __m256d
		inline static auto gradient(float* left, float* dleft, float* right, float* dright)
		{
			__m128* ptrl = (__m128*)dleft;
			__m128* ptrr = (__m128*)dright;
			__m128* ptrlv = (__m128*)left;
			__m128* ptrrv = (__m128*)right;

			float* dv = new float[52];
			#pragma omp parrallel for
			for (int i=0; i<13; ++i,++ptrl, ++ptrr)
			{
 			_mm_store_ps(dv+4*i,  _mm_add_ps ( _mm_mul_ps(*ptrrv,*ptrl),_mm_mul_ps(*ptrlv,*ptrr)));
			}
			//std::cout<< "result[0] = "<< dv[0] << std::endl;

			return  dv;
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
		inline static auto value(float* left, float* right)
		{
			//assert(right!=0.); //verification si le dénomminateur est non nul
		  	__m128* ptrlv = (__m128*)left;
			__m128* ptrrv = (__m128*)right;
			float* v = new float[4];
 			_mm_store_ps(  v,_mm_div_ps ( *ptrlv, *ptrrv));

			return  v;
		}

		/**
		 * \brief methode qui calcule la derivee en i de l'operation (derivee en a,b,c ...)
		 * \param left : valeur de l'objet à gauche de l'operateur
		 * \param right : valeur de l'objet à droite de l'operateur
		 * \param dleft : valeur de la derivee de l'objet à gauche de l'operateur
		 * \param dright : valeur de la derivee de l'objet à droite de l'operateur
		 */
		inline static auto gradient(float* left, float* dleft, float* right, float* dright)
		{
			//assert(right!=0.); //verification si le dénomminateur est non nul
			__m128* ptrl = (__m128*)dleft;
			__m128* ptrr = (__m128*)dright;
			__m128* ptrlv = (__m128*)left;
			__m128* ptrrv = (__m128*)right;
			float* dv = new float[52];
			#pragma omp parrallel for
			for (int i=0; i<13; ++i,++ptrl, ++ptrr)
			{
 			_mm_store_ps(dv+4*i, _mm_div_ps( _mm_sub_ps ( _mm_mul_ps(*ptrrv,*ptrl),_mm_mul_ps(*ptrlv,*ptrr)),_mm_mul_ps(*ptrr,*ptrl)));
			}
			return  dv;		
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
		inline static auto value(float* left, float* right)
		{
			__m128* ptrlv = (__m128*)left;
			__m128* ptrrv = (__m128*)right;
			float* v = new float[4];
 			_mm_store_ps(v,  _mm_add_ps ( *ptrlv, *ptrrv));

			return  v;		
		}

		/**
		 * \brief methode qui calcule la derivee en i de l'operation (derivee en a,b,c ...)
		 * \param left : valeur de l'objet à gauche de l'operateur
		 * \param right : valeur de l'objet à droite de l'operateur
		 * \param dleft : valeur de la derivee de l'objet à gauche de l'operateur
		 * \param dright : valeur de la derivee de l'objet à droite de l'operateur
		 */
		inline static auto gradient(float* left, float* dleft, float* right, float* dright)
		{
			__m128* ptrl = (__m128*)dleft;
			__m128* ptrr = (__m128*)dright;
			float* dv = new float[52];
			#pragma omp parrallel for
			for (int i=0; i<13; ++i,++ptrl, ++ptrr)
			{
 			_mm_store_ps(dv+4*i,  _mm_add_ps ( *ptrl, *ptrr)); 			
			}

 			//std::cout<<"la valeur est " << dv[0] << std::endl;
			return  dv;		
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
		inline static auto value(float* left, float* right)
		{	
			__m128* ptrlv = (__m128*)left;
			__m128* ptrrv = (__m128*)right;
			float* v = new float[4];
 			_mm_store_ps(v,  _mm_sub_ps ( *ptrlv, *ptrrv));

			return  v;		
		}

		/**
		 * \brief methode qui calcule la derivee en i de l'operation (derivee en a,b,c ...)
		 * \param left : valeur de l'objet à gauche de l'operateur
		 * \param right : valeur de l'objet à droite de l'operateur
		 * \param dleft : valeur de la derivee de l'objet à gauche de l'operateur
		 * \param dright : valeur de la derivee de l'objet à droite de l'operateur
		 */
		inline static auto gradient(float* left, float* dleft, float* right, float* dright)
		{
			__m128* ptrl = (__m128*)dleft;
			__m128* ptrr = (__m128*)dright;
			float* dv = new float[52];
			#pragma omp parrallel for
 			for (int i=0; i<13; ++i,++ptrl, ++ptrr)
			{
			_mm_store_ps(dv+4*i,  _mm_sub_ps ( *ptrl, *ptrr));
			}
			return  dv;			}
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
		inline float* value() const { return op::value(left.value(), right.value()); }
		
		/**
		 * \brief methode qui calcule la derivee en i de l'operation en demandant à l'operateur de faire les operations entre les derivees
		 * \param i : indice des derivees
		 */
		inline float* gradient() const
		{
		return op::gradient(left.value(), left.gradient(),
							right.value(), right.gradient());
		}
	};

	/// structure binop pour le cas d'un float à gauche
	/** \struct binop<float,E2,op>
	 * \brief structure binop pour le cas entre un float a gauche et des binop ou ad_value a droite
	 * \brief op est l'operateur qui a ete appelle
	 */
	template<class E2, class op>
	struct binop<float , E2 , op>
	{

		/**
		 * \brief objet de type float qui est l'objet a gauche
		 */
		const float left;
		/**
		 * \brief objet de type E2 qui est l'objet a droite
		 */
		const E2 right;

		/**
		 * \brief Constructeur de la classe 
		 * \param left : objet de type float qui correspond à l'element à gauche de l'operation
		 * \param right : objet de type ad_value ou binop qui correspond à l'element à droite de l'operation
		 */
		inline binop(const float left, const E2 right)
			: left(left)
			, right(right) {}

		/**
		 * \brief methode qui calcule la valeur de l'operation en demandant à l'operateur de faire les operations entre les valeurs
		 */
		inline float* value() const { return op::value(left, right.value()); }
		/**
		 * \brief methode qui calcule la derivee en i de l'operation en demandant à l'operateur de faire les operations entre les derivees
		 * \param i : indice des derivees
		 */
		inline float* gradient() const
		{
			return op::gradient(left, 0.,
								right.value(), right.gradient());
		}
	};

	/** \struct binop<float,E2,op>
	 * \brief structure binop pour le cas entre un float a droite et des binop ou ad_value a droite
	 * \brief op est l'operateur qui a ete appelle
	 */
	template<class E1, class op>
	struct binop<E1 , float , op>
	{

		/**
		 * \brief objet de type E1 qui est l'objet a gauche
		 */
		const E1 left;
		/**
		 * \brief objet de type float qui est l'objet a gauche
		 */
		const float right;

		/**
		 * \brief Constructeur de la classe 
		 * \param left : objet de type ad_value ou binop qui correspond à l'element à gauche de l'operation
		 * \param right : objet de type float qui correspond à l'element à droite de l'operation
		 */
		inline binop(const E1 left, const float right)
			: left(left)
			, right(right) {}

		/**
		 * \brief methode qui calcule la valeur de l'operation en demandant à l'operateur de faire les operations entre les valeurs
		 */
		inline float* value() const { return op::value(left.value(), right); }
		/**
		 * \brief methode qui calcule la derivee en i de l'operation en demandant à l'operateur de faire les operations entre les derivees
		 * \param i : indice des derivees
		 */
		inline float* gradient() const
		{
			return op::gradient(left.value(), left.gradient(),
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
	binop<float, E2, sub>  operator-( const E2 right)
	{
	  	return binop<float, E2, sub>(0., right); 
	}

}

