#include <iostream>
#include "GRID.h"
#include "ELEMENT.h"
#include "matrixH.h"
#include "matrixH_BC.h"
#include "matrixC.h"
#include "jakobian2D.h"
#include "dataFromFile.h"
#include "globalMatrixH.h"
#include "globalMatrixC.h"
#include "vectP.h"

using namespace std;

int main(){
	//POBRANIE DANYCH Z PLIKU I GENERACJA SIATKI
	dataFromFile daneZPliku;
	daneZPliku.importujPlik();
	GRID siatka;
	siatka.generujSiatke(&daneZPliku);
	

	//INICJALIZACJA WEKTORA TEMPERATUR:
	Matrix * wektorTemp0 = new Matrix(daneZPliku.getLiczbaWezlow(), 1, daneZPliku.gettPoczatkowa());
	Matrix * wektorTemp = wektorTemp0;
	int liczbaElementow = daneZPliku.getLiczbaElementow();

	for(int i_t=1; i_t<=(daneZPliku.getCzasSymulacji()/daneZPliku.getZmianaCzasu()); i_t++){
	//INICJALIZACJA POTRZEBNYCH ZMIENNYCH
		jakobian2D *jakobian = new jakobian2D[daneZPliku.getLiczbaElementow()];
		matrixH *lokalnaMacH = new matrixH[daneZPliku.getLiczbaElementow()];
		matrixH_BC *lokalMacH_BC = new matrixH_BC[daneZPliku.getLiczbaElementow()];
		matrixC *lokalnaMacC = new matrixC[daneZPliku.getLiczbaElementow()];
		vectP* lokalnyVectP = new vectP[daneZPliku.getLiczbaWezlow()];
		globalMatrixH *globalnaMacH = new globalMatrixH(daneZPliku.getLiczbaWezlow());
		globalMatrixC *globalnaMacC = new globalMatrixC(daneZPliku.getLiczbaWezlow());
		vectP* globalnyVectP = new vectP(daneZPliku.getLiczbaWezlow());

		//WIELOWATKOWOSC :
		
		for(int i=0; i<liczbaElementow;i++){
			 jakobian[i].wpiszDane(&siatka, i);
		}


		////////////////BARIERA : :
		//WIELOWATKOWOSC :
		for(int i=0; i< liczbaElementow;i++){
			 lokalnaMacH[i].wpiszDane(&siatka, jakobian, &daneZPliku, i);
			 lokalnaMacH[i].sumujDoGlobala(globalnaMacH);
		}
		//cout <<"MACIERZ GLOBALNA H: "<<endl;
		//globalnaMacH->writeMatrix();
		delete[] lokalnaMacH;

		for(int i=0; i<liczbaElementow;i++){
			 lokalMacH_BC[i].wpiszDane(&siatka, &daneZPliku, i);
			 //lokalMacH_BC[i].writeMatrix();
			 lokalMacH_BC[i].sumujDoGlobala(globalnaMacH);
		}

		//cout <<"MACIERZ GLOBALNA H Z BC: "<<endl;
		//globalnaMacH->writeMatrix();
		delete[] lokalMacH_BC;

		for(int i=0; i< liczbaElementow;i++){
			lokalnyVectP[i].wpiszDane(&siatka, jakobian, &daneZPliku, i);
			lokalnyVectP[i].sumujDoGlobala(globalnyVectP);
		}


		delete[] lokalnyVectP;
		/////////////////BARIERA : :
		//WIELOWATKOWOSC :
		for(int i=0; i<liczbaElementow;i++){
			lokalnaMacC[i].wpiszDane(&siatka, jakobian, &daneZPliku, i);
			lokalnaMacC[i].sumujDoGlobala(globalnaMacC);
		}
		//cout <<"MACIERZ GLOBALNA C:"<<endl;
		//globalnaMacC->writeMatrix();
		//cout <<"WEKTOR GLOBALNY P:"<<endl;
		//globalnyVectP->writeMatrix();
		delete[] lokalnaMacC;
		delete[] jakobian;

	
		//OBLICZAMY     ----->    [C]/dT
		globalnaMacC->pomnozPrzezLiczbe(1.0/(daneZPliku.getZmianaCzasu()));

		//cout <<"[H] = [H]+[C]/dT:"<<endl;
		globalnaMacH->dodajMacierz(globalnaMacC->getMacierz());
		//globalnaMacH->writeMatrix();

		//Vector([{P}+{[C]/dT}*{T0})
		Matrix* C_przez_dT_razyTemp = globalnaMacC->pomnozPrzezWektor(wektorTemp);
		globalnyVectP->dodajWektor(C_przez_dT_razyTemp);
		delete C_przez_dT_razyTemp;
		//cout <<endl<<"Vector([{P}+{[C]/dT}*{T0}):"<<endl;
		//globalnyVectP->writeMatrix();
		//[H']{t}-{P'} =0; => [H']{t}={P'}  => {t}=([H']^-1){P'}
		globalnaMacH->odwroc();
		delete wektorTemp;
		wektorTemp =  globalnaMacH->pomnozPrzezVectP(globalnyVectP);
		//cout << "{noweTemperatur}: "<<endl;
		//wektorTemp->writeMatrix();
		cout <<"step: "<< i_t * daneZPliku.getZmianaCzasu()<<" TEMP MAX: "<< wektorTemp->findMax() << " TEMP MIN " <<wektorTemp->findMin()<<endl;
	
		delete globalnyVectP;
		delete globalnaMacH;
		delete globalnaMacC;
	}
	delete wektorTemp;
	system("PAUSE");

	return 0;
}