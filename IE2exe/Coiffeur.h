#pragma once 
//Problème de coiffeur 
//un coiffeur possède un tout petit salon de coiffure
//il y a une seule chaise dans l'espace de travail 
//et 4 tabourets dans la salle d'attente
//
//le salon tourne ainsi ainsi :
//quand le coiffeur finit une coupe d'un client, le client s'en va
//le coiffeur va alors dans la salle d'attente
//si celle ci contient des clients :
//    il en prend un , va le faire s'asseoir sur la chaise de l'espace de travail
//    et commence la coupe
//si celle ci ne contient pas de client :
//    il retourne dans l'espace de travail, et se repose sur sa chaise
//
//quand un client arrive, il va voir le coiffeur
//si celui ci dort, il le reveille et s'asseoit dans la chaise pour une coupe immédiate
//si celui ci travaille, il va s'asseoir dans la salle d'attente
//si la salle d'attente est pleine, le client s'en va.

#include <thread>
#include <mutex>
#include <queue>
#include <iostream>
class Coiffeur;
class Client;
class SalonDeCoiffure
{
public :
	std::mutex mu;
	int nbClient = 0;
	int nbClientDay = 0;
	std::atomic<int> nbCut = 0;
	std::atomic<bool> closed = 0;
	std::queue<Client*> clients;
	Coiffeur* c;
	//le coiffeur se met au travail
	void Start();
	bool Closing() { return nbCut >= 4; };
	void Close();
	//un client rentre dans le salon
	void AddCustomer();


};
class Client
{
public:
	std::thread* m_thread = nullptr;
	SalonDeCoiffure* m_salon;
	std::mutex h;
	std::atomic<bool> exit = false;
	int id = 0;
	Client(SalonDeCoiffure* s)
	{
		id = s->nbClientDay++;
		m_salon = s;
		m_thread = new std::thread(&Client::wait, this);
		std::lock_guard<std::mutex> l(m_salon->mu);
		if (m_salon->clients.size() >= 4)
		{
			exit = true;
			return;
		}
		m_salon->clients.push(this);
		std::cout << id << " waiting for cut" << std::endl;

	}
	~Client()
	{
		m_thread->join();
		std::cout << id << " leave" << std::endl;
	}


	void wait()
	{
		while (!exit)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(200));
		}
	}

};

class Coiffeur
{
public:
	std::thread* m_thread = nullptr;
	SalonDeCoiffure* m_salon;
	Client* currentClient = nullptr;
	bool sleeping = true;
	Coiffeur(SalonDeCoiffure* s)
	{
		m_salon = s;
		m_thread = new std::thread(&Coiffeur::work, this);
	}

	void work()
	{
		while (1)
		{
			m_salon->mu.lock();
			if (!m_salon->clients.empty())
			{
				currentClient = m_salon->clients.front();
				m_salon->clients.pop();
				sleeping = false;
			}
			else
			{
				sleeping = true;
			}
			m_salon->mu.unlock();
			if (sleeping)
			{
				std::cout << "sleeping" << std::endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
			}
			else
			{
				currentClient->h.lock();
				std::cout << "cutting hair of " <<  currentClient->id << std::endl;
				std::this_thread::sleep_for(std::chrono::seconds(1));
				currentClient->exit = true;
				currentClient->h.unlock();
				m_salon->nbCut++;
				delete(currentClient);

			}
		}
	}

};


