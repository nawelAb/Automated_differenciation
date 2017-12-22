namespace ourlibs{
	class diffTree{
	private:
		diffTree* diff;
		values* values;
		char ourOperator[4];
                double power;
	public:
		//constructeur pour les 3 cas possibles
		diffTree(diffTree, diffTree);
		diffTree(values, diffTree);
		diffTree(values, values);
                diiffTree(diffTree, double);
		diffTree~();

		//crée un difftree a partir de deux éléments
                diffTree& operator=(diffTree&);
		diffTree operator*(double);
		diffTree operator*(values);
		diffTree operator*(diffTree&);
		diffTree operator*(double);
		diffTree operator+(values);
		diffTree operator+(diffTree&);

		//fait la résolution du diff et supprime la référence vers le diff
		//vérifie si le diff existe et le supprime après résolution
		void replaceDiff(int, values);

		//résous l'arborescence du difftree pui renvois les résultats sous la
		//forme d'un objet values (@)
		values* resolution();

	};
};
