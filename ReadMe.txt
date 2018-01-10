Ceci est le premier fichier du projet.

Il contient:

    1-les commandes à lancer pour compiler et lancer le programme
    2-la librairie du projet.
    3-Contribution.


    1-les commandes à lancer pour compiler et lancer le programme.

	    On a utilisé comme outils de compilation CMake (version 3.5.1), de ce fait,  
	    ainsi est le modèle pour notre cas de compilation est :

	    CMakeList.txt >> CMake >> SCRIPT DE COMPILATION << Fichier Source.
                                         ||
                                         ||
                                     EXECUTABLE

	    Il y en a plusieurs formes de Script de Compilation mais notre
	    cas il s'agit Makefile.
	    En ce qui concerne le fichier CMakeList.txt, il est indépendant
	    de la plateforme, on décrit à l'intérieur comment on s'y prend pour
	    compiler le projet à l'aide des informations comme : le language 
	    utilisé, les fichiers à compiler, les dépendances (externes 
	    ou comme sous-projet). Conséquemment, Cmake va pouvoir nous générer
	    le script de compilation adéquat pour le projet.


	2-la librairie du projet.

		On a implémenté une librairie dont on a nommé "libs.h". Le 
		contenu de celle-ci s'agit :
			- une classe "ad_values" qui contient une valeur et sa dérivée,
			- des structures pour effectuer les différentes opérations,
			- une structure "binop" qui correspond à un arbre binaire d'opérateur
	
	3-Contribution

		Bidault Romain, Mahamoud Moursal, Naoual Abbou,Amarouchene Lynda, Ghenai
		Mohammed, Anis Seddik. 


	    

