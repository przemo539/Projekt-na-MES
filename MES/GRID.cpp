#include "GRID.h"


GRID::GRID(void)
{
	nh=-1;
	nl=-1;
}

NODE * GRID::getWezly(){
	return wezly;
}

ELEMENT * GRID::getElement(int numer){
	return &elementy[numer];
}

void GRID::importujSiatke(ELEMENT * el, NODE * no){
	elementy=el;
	wezly=no;
}

void GRID::generujSiatke(dataFromFile * DaneZPliku){
	nh = DaneZPliku->getNh();
	nl = DaneZPliku->getNl();
	H = DaneZPliku->getH();
	L = DaneZPliku->getL();
	if(nl > 1 && nh > 1 && H > 0 && L > 0){
		elementy = new ELEMENT[DaneZPliku->getLiczbaElementow()];
		wezly = new NODE[DaneZPliku->getLiczbaWezlow()];
		double delta_y = H/(nh-1);
		double delta_x = L/(nl-1);
		int kolumna = 1;
		int przesuniecie = 0;
		bool BC = false;
		for(int i = 0;i<nh*nl; i++){
			if((i*1.0)/nh >= 1 && i%nh ==0)
				kolumna++;
			//SPRAWDZANIE BC LEWA STRONA
			if(i <nh)
				BC = true;
			//SPRAWDZANIE BC PRAWA STRONA
			if(i>(nh*nl-nh-1))
				BC = true;
			//SPRAWDZENIE BC DOL + GORA
			if( i%nh ==0 ||  i%nh ==(nh-1))
				BC = true;
			wezly[i].ustaw(delta_x*(kolumna-1),delta_y*(i%nh),BC);
			//wezly[i].wypiszPozycje();
			BC = false;
		}

		for(int i = 0;i<(nh-1)*(nl-1); i++){
			if((i+przesuniecie)%nh == (nh-1))
				++przesuniecie;
			elementy[i].ustaw(i+przesuniecie, nh);
			//element[i].wypiszPozycje();
		}
	}else{
		std::cout <<"DANE NIEPOPRAWNIE WCZYTANE Z PLIKU!!"<<std::endl;
	}
}

GRID::~GRID(void)
{
		delete[] elementy;
		delete[] wezly;		
}
