#include "vectP.h"


vectP::vectP(void)
{
}

void vectP::dodajWektor(Matrix * wektor){
	VectP->addMatrix(wektor);
}

void vectP::writeMatrix(){
	VectP->writeMatrix();
}
vectP::vectP(int kolumny){
	VectP = new Matrix(kolumny,1 );
}

void vectP::sumujDoGlobala(vectP* globalnyVectP){
	if(!pusty){
		for(int kolumna=0; kolumna<4; kolumna++)
			globalnyVectP->VectP->setValueOfMatrix(element->getWezelPoId(kolumna),0, this->VectP->getValueOfMatrix(kolumna,0));
	}
}


void vectP::wpiszDane(GRID *siatka, jakobian2D * tablicaJakobianow, dataFromFile *daneZPliku, int numerElementu){
	pusty = true;
	alfa = daneZPliku->getAlfa();
	tOtoczenia = daneZPliku->gettOtoczenia();
	element = siatka->getElement(numerElementu);
	wezly = siatka->getWezly();
		for(int i=0; i<4; i++)
		POWIERZCHNIA[i] = element->getBCPowierzchniPoId(wezly, i);
	
	for(int i=0; i<4; i++)
		if(POWIERZCHNIA[i]) pusty = false;
	if(!pusty){
		VectP = new Matrix(4,1);
		oblicz();
	}
}


vectP::~vectP(void)
{
	if(!pusty)
		delete VectP;
}

void vectP::oblicz(){
	double ksi[2], N1[2],N2[2];
	ksi[0] = -1/sqrt(3.0);
	ksi[1] = 1/sqrt(3.0);
	for(int i =0; i<2; i++){
		N1[i] = (1-ksi[i])/2.0;
		N2[i]=(ksi[i]+1)/2.0;
	}
	//OBLICZENIA dla punktu 1
		//MNOZYMY {N} * alfa * tOtoczenia * (dlugoscboku/2)
	if(POWIERZCHNIA[0] || POWIERZCHNIA[3]){
		for(int i=0;i<2;i++){
			VectP->addValueOfMatrix(0,0, N1[i] * alfa * tOtoczenia * (element->getDlugoscPowierzchniPoId(wezly, 0)/2));  //DLA N1
			VectP->addValueOfMatrix(0,0, N2[i] * alfa * tOtoczenia * (element->getDlugoscPowierzchniPoId(wezly, 0)/2));  //DLA N2
		}
	}
	//OBLICZENIA dla punktu 2
	if(POWIERZCHNIA[0] || POWIERZCHNIA[1]){
		for(int i=0;i<2;i++){
			VectP->addValueOfMatrix(1,0, N1[i] * alfa * tOtoczenia * (element->getDlugoscPowierzchniPoId(wezly, 0)/2));
			VectP->addValueOfMatrix(1,0, N2[i] * alfa * tOtoczenia * (element->getDlugoscPowierzchniPoId(wezly, 0)/2));
		}
	}
	//OBLICZENIA dla punktu 3
	if(POWIERZCHNIA[1]  || POWIERZCHNIA[2]){
		for(int i=0;i<2;i++){
			VectP->addValueOfMatrix(2,0, N1[i] * alfa * tOtoczenia * (element->getDlugoscPowierzchniPoId(wezly, 0)/2));
			VectP->addValueOfMatrix(2,0, N2[i] * alfa * tOtoczenia * (element->getDlugoscPowierzchniPoId(wezly, 0)/2));
		}
	}
	//OBLICZENIA dla punktu 4
	if(POWIERZCHNIA[2]  || POWIERZCHNIA[3]){
		for(int i=0;i<2;i++){
			VectP->addValueOfMatrix(3,0, N1[i] * alfa * tOtoczenia * (element->getDlugoscPowierzchniPoId(wezly, 0)/2));
			VectP->addValueOfMatrix(3,0, N2[i] * alfa * tOtoczenia * (element->getDlugoscPowierzchniPoId(wezly, 0)/2));
		}
	}
	//VectP->writeMatrix();
}