#include "dataFromFile.h"


dataFromFile::dataFromFile(void)
{
	/*czasSymulacji = 500;
	zmianaCzasu = 50;
	tOtoczenia = 1200;
	tPoczatkowa = 100;
	przewodnosc = 25;
	gestosc = 7800.0;
	cieploWlasciwe = 700;

	H=0.100;
	L=0.100;	
	nh=4;
	nl=4;
	
	alfa = 300;*/
}

int dataFromFile::getLiczbaElementow(){
	int liczba = (nh-1)*(nl-1);
	return liczba;
}
int dataFromFile::getLiczbaWezlow(){
	return nh*nl;
}


void dataFromFile::importujPlik(){
	std::string filename="plik2.txt";
	if(!filename.empty()){
		plik.open(filename, std::ios::in);
		if(plik.is_open()){	
			std::string bufor;

			//czasSymulacji:	
			plik >> bufor;
			czasSymulacji = atof(bufor.c_str());
			
			//zmianaCzasu
			plik >> bufor;
			zmianaCzasu = atof(bufor.c_str());

			//tOtoczenia
			plik >> bufor;
			tOtoczenia = atof(bufor.c_str());

			//tPoczatkowa
			plik >> bufor;
			tPoczatkowa = atof(bufor.c_str());

			//przewodnosc
			plik >> bufor;
			przewodnosc = atof(bufor.c_str());

			//gestosc
			plik >> bufor;
			gestosc = atof(bufor.c_str());

			//cieploWlasciwe
			plik >> bufor;
			cieploWlasciwe = atof(bufor.c_str());

			//H
			plik >> bufor;
			H = atof(bufor.c_str());

			//L
			plik >> bufor;
			L = atof(bufor.c_str());

			//nh
			plik >> bufor;
			nh = atoi(bufor.c_str());

			//nl
			plik >> bufor;
			nl = atoi(bufor.c_str());

			//alfa
			plik >> bufor;
			alfa = atof(bufor.c_str());

			plik.close();
		}else{
			std::cout << "BRAK DOSTÊPU LUB PLIK NIE ISTNIEJE!"<<std::endl;
		}
	}else{
		std::cout << "NIEPOPRAWNA LUB BRAK NAZWY PLIKU!!"<<std::endl;
	}
}

double dataFromFile::getPrzewodnosc(){
	return przewodnosc;
}

double dataFromFile::getGestosc(){
	return gestosc;
}

double dataFromFile::getCieploWlasciwe(){
	return cieploWlasciwe;
}

double dataFromFile::getH(){
	return H;
}

double dataFromFile::getL(){
	return L;
}

int dataFromFile::getNh(){
	return nh;
}

int dataFromFile::getNl(){
	return nl;
}

double dataFromFile::getAlfa(){
	return alfa;
}

double dataFromFile::getZmianaCzasu(){
	return zmianaCzasu;
}
double dataFromFile::getCzasSymulacji(){
	return czasSymulacji;
}

double dataFromFile::gettOtoczenia(){
	return tOtoczenia;
}

double dataFromFile::gettPoczatkowa(){
	return tPoczatkowa;
}

dataFromFile::~dataFromFile(void)
{
}
