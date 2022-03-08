#include "stdafx.h"
#include "Coiffeur.h"

//le coiffeur se met au travail

 void SalonDeCoiffure::Start() {
	printf("le coiffeur se met au travail\n");
	c = new Coiffeur(this);
}

  void SalonDeCoiffure::Close() { 
	printf("Fermeture IMMINENTE !\n");
	  while (!clients.empty())
		  std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }


//un client rentre dans le salon

 void SalonDeCoiffure::AddCustomer() {
	 if (nbCut > 4)
		 return;
	 std::this_thread::sleep_for(std::chrono::milliseconds(std::rand() % 500));
	printf("un client rentre dans le salon\n");
	auto c = new Client(this);
	if (c->exit)
		delete (c);
}
