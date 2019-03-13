#include "matrixH.h"
#include "matrix.h"


matrixH::matrixH(void){ }

matrixH::matrixH(jakobian2D * jak, double przewodnosc){
	wpiszDane(jak, przewodnosc);
}

void matrixH::wypisz(){
	macierzH->writeMatrix();
}

void matrixH::sumujDoGlobala(globalMatrixH* globalnaMacH){
	for(int i=0; i<4;i++)
		for(int j=0; j<4; j++)
			globalnaMacH->dodajDoMacierzy(element->getWezelPoId(i),element->getWezelPoId(j), macierzH->getValueOfMatrix(i,j));
}

void matrixH::wpiszDane(GRID *siatka, jakobian2D * tablicaJakobianow, dataFromFile *daneZPliku, int numerElementu){
	element = siatka->getElement(numerElementu);
	jakobian = &tablicaJakobianow[numerElementu];
	k=daneZPliku->getPrzewodnosc();
	eta = jakobian->getEta();
	ksi = jakobian->getKsi();	
	generujStale();
	macierzH = new Matrix(4,4);
	oblicz();
}

void matrixH::wpiszDane(jakobian2D * jak, double przewodnosc){
	jakobian = jak;
	k=przewodnosc;
	eta = jakobian->getEta();
	ksi = jakobian->getKsi();	
	generujStale();
	macierzH = new Matrix(4,4);
	oblicz();
}

matrixH::~matrixH(void)
{
	delete 	dN_dKsi, dN_dEta, dN_dX, dN_dY, macierzH;
}

void matrixH::oblicz(){
	//OBLICZAMY MACIERZ dN/dx -> Wyliczamy korzystaj¹c z (1/Det(J))*[ dN/dKsi[X] ] * dN/dKSI + [ dN/dKsi[Y] ]*(1/Det(J)) * dN/dETA <- DLA KONKRETNEGO N I PC
	dN_dX = dN_dKsi->copyMatrix();
	Matrix *dN_dEtaTymczasowe = dN_dEta->copyMatrix();
	for(int i=0;i<4;i++){
		dN_dX->rowMultiplyByNumber(i, jakobian->getWartoscZJakobiego(i,0,0));
		dN_dEtaTymczasowe->rowMultiplyByNumber(i, jakobian->getWartoscZJakobiego(i,0,1));
	}
	dN_dX->addMatrix(dN_dEtaTymczasowe);
	delete dN_dEtaTymczasowe;

	//OBLICZAMY MACIERZ dN/dY -> Wyliczamy korzystaj¹c z (1/Det(J))*[ dN/dETA[X] ] * dN/dKSI + [ dN/dETA[Y] ]*(1/Det(J)) * dN/dETA <- DLA KONKRETNEGO N I PC
	dN_dY = dN_dKsi->copyMatrix();
	dN_dEtaTymczasowe = dN_dEta->copyMatrix();
	for(int i=0;i<4;i++){
		dN_dY->rowMultiplyByNumber(i, jakobian->getWartoscZJakobiego(i,1,0));
		dN_dEtaTymczasowe->rowMultiplyByNumber(i, jakobian->getWartoscZJakobiego(i,1,1));
	}
	dN_dY->addMatrix(dN_dEtaTymczasowe);
	delete dN_dEtaTymczasowe;

	//dN/dX * (dN/dX)^T dla kazdego punktu calkowania
	Matrix* dN_dXmultiplydN_dXT[4];
	for(int i=0;i<4;i++){
		dN_dXmultiplydN_dXT[i] = dN_dX->vektorMultiplyTransVector(i, -1);
	}
		
	//dN/dy * (dN/dyX)^T dla kazdego punktu calkowania
	Matrix* dN_dYmultiplydN_dYT[4];
	for(int i=0;i<4;i++){
		dN_dYmultiplydN_dYT[i] = dN_dY->vektorMultiplyTransVector(i, -1);
	}


	//Mno¿ymy je przez wyznacznik odpowiedni dla swojego punktu calkowania:
	for(int i=0;i<4;i++){
		dN_dXmultiplydN_dXT[i]->multiplyByNumber(jakobian->getJakobian(i));
		dN_dYmultiplydN_dYT[i]->multiplyByNumber(jakobian->getJakobian(i));
	}

	//Sumujemy wszystkie dN_dXmultiplydN_dXT i dN_dYmultiplydN_dYT
	for(int i=0;i<4;i++){
		macierzH->addMatrix(dN_dXmultiplydN_dXT[i]);
		macierzH->addMatrix(dN_dYmultiplydN_dYT[i]);
	}
	//Zsumowane MatrixH mno¿ymy razy wspó³czynnik K;
	macierzH->multiplyByNumber(k);
	//macierzH->writeMatrix();
	
}

void matrixH::generujStale(){
	dN_dKsi = new Matrix(4,4);
	//GENERUJEMY dN/dKsi[0] wed³ug rownania dN/dKsi[0]= -0.25 * (1 - eta)
	for(int i=0;i<4;i++)
		dN_dKsi->setValueOfMatrix(i,0, -0.25*(1-eta->getValueOfMatrix(i,0)));
	//GENERUJEMY dN/dKsi[1] wed³ug rownania dN/dKsi[0]= 0.25 * (1 - eta)
	for(int i=0;i<4;i++)
		dN_dKsi->setValueOfMatrix(i,1, 0.25*(1-eta->getValueOfMatrix(i,0)));
	//GENERUJEMY dN/dKsi[2] wed³ug rownania dN/dKsi[0]= 0.25 * (1 + eta)
	for(int i=0;i<4;i++)
		dN_dKsi->setValueOfMatrix(i,2, 0.25*(1+eta->getValueOfMatrix(i,0)));
		//GENERUJEMY dN/dKsi[3] wed³ug rownania dN/dKsi[0]= 0.25 * (1 + eta)
	for(int i=0;i<4;i++)
		dN_dKsi->setValueOfMatrix(i,3, -0.25*(1+eta->getValueOfMatrix(i,0)));

	dN_dEta = new Matrix(4,4);
	//GENERUJEMY dN/dEta[0] wed³ug rownania dN/dEta[0]= -0.25 * (1 - ksi)
	for(int i=0;i<4;i++)
		dN_dEta->setValueOfMatrix(i,0, -0.25*(1-ksi->getValueOfMatrix(i,0)));
	//GENERUJEMY dN/dEta[0] wed³ug rownania dN/dEta[0]= -0.25 * (1 + ksi)
	for(int i=0;i<4;i++)
		dN_dEta->setValueOfMatrix(i,1, -0.25*(1+ksi->getValueOfMatrix(i,0)));
	//GENERUJEMY dN/dEta[0] wed³ug rownania dN/dEta[0]= 0.25 * (1 + ksi)
	for(int i=0;i<4;i++)
		dN_dEta->setValueOfMatrix(i,2, 0.25*(1+ksi->getValueOfMatrix(i,0)));
	//GENERUJEMY dN/dEta[0] wed³ug rownania dN/dEta[0]= 0.25 * (1 - ksi)
	for(int i=0;i<4;i++)
		dN_dEta->setValueOfMatrix(i,3, 0.25*(1-ksi->getValueOfMatrix(i,0)));
}
