

namespace ourlibs{
	class diffTree{
	private:
		diffTree diff[2];
		values values[2];
		char ourOperator[3];
	public:
		//constructeur pour les 3 cas possibles
		diffTree(ourlibs::diffTree,ourlibs::diffTree);
		diffTree(ourlibs::values,ourlibs::diffTree);
		diffTree(ourlibs::values,ourlibs::values);
		diffTree~();

		//crée un difftree a partir de deux éléments
		diffTree* operator*(ourlibs::values*);
		diffTree* operator*(ourlibs::diffTree*);

		diffTree* operator+(ourlibs::values*);
		diffTree* operator+(ourlibs::diffTree*);

		//fait la résolution du diff et supprime la référence vers le diff
		//vérifie si le diff existe et le supprime après résolution
		void replaceDiff(int,ourlibs::values)

		//résous l'arborescence du difftree pui renvois les résultats sous la
		//forme d'un objet values (@)
		values* resolution();

	};
};