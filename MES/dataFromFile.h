#pragma once
#include <fstream>
#include <string>
#include <iostream>

class dataFromFile
{
	int nh, nl;
	double H, L;
	double przewodnosc;
	double gestosc;
	double cieploWlasciwe;
	double alfa;
	double tOtoczenia;
	double tPoczatkowa;
	double czasSymulacji;
	double zmianaCzasu;
	std::fstream plik;
public:
	double getPrzewodnosc();
	double getGestosc();
	double getCieploWlasciwe();
	double getH();
	double getL();
	int getNh();
	int getNl();
	double getAlfa();
	double getZmianaCzasu();
	double getCzasSymulacji();
	double gettOtoczenia();
	double gettPoczatkowa();
	void importujPlik();
	int getLiczbaElementow();
	int getLiczbaWezlow();
	dataFromFile(void);
	~dataFromFile(void);
};

