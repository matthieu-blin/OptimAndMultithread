#pragma once

#include <algorithm> 
#include <chrono> 
#include <iostream> 
#include <memory> 
#include <mutex> 
#include <string> 
#include <thread> 
#include <vector> 
 
class Baguette 
{ 
public: 
    Baguette(){}; 
}; 

//Organisons un repas chinois 
//la nourriture est prete !
//il y a 4 invités qui arrivent (donc 5 mangeurs avec l'hote)
//mais, oops, au moment de mettre la table
//l'hote s'aperçoit qu'il n'y a que 5 baguettes.
//Conscient qu'il faut ABSOLUMENT 2 baguettes pour manger
//l'hote dispose les baguettes ainsi
//         A | B
//        \     /
//       C       D
//        /  E  \ 
//Comme ça chacun a une baguette à sa gauche et à sa droite 
//et peut potentiellement prendre dans le plat, le mettre à sa bouche,
//et reposer les baguettes le temps de macher
//donnant ainsi la possibilité pour ses voisins d'utiliser la baguette 
//qu'ils ont en commun pour prendre la nourriture à son tour.
//bien sûr, etant un minimum poli et ayant du savoir vivre
//chacun utilisera UNIQUEMENT les baguettes prévues à sa droite et sa gauche
//pour corser les choses, il y a ciné après, il s'agit donc de manger au plus vite !
class RepasChinois
{
public :

	const int nombreDeBaguettes = 5;
	const int nombreDeMangeur = 5;
	const int nombreDeBouchee = 10; //nombre de bouchée que représente le plat
	//
	void MettreLaTable()
	{
		for (int i = 0; i < nombreDeBaguettes; ++i)
		{
			m_chopsticks.push_back(new Baguette());
		}
	}
	void Manger()
	{
		printf("A mange rien avec aucune baguette (il est entouré de B4 et B0)\n");
		printf("B mange rien avec aucune baguette (il est entouré de B0 et B1)\n");
		printf("C mange rien avec aucune baguette (il est entouré de B1 et B2)\n");
		printf("D mange rien avec aucune baguette (il est entouré de B2 et B3)\n");
		printf("E mange rien avec aucune baguette (il est entouré de B3 et B4)\n");
	}

private :
	std::vector<Baguette*> m_chopsticks;

};