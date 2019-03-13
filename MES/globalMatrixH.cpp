#include "globalMatrixH.h"

void globalMatrixH::writeMatrix(){
	macierzGlobalnaH->writeMatrix();
}

void globalMatrixH::dodajMacierz(Matrix * macierz){
	macierzGlobalnaH->addMatrix(macierz);
}

void globalMatrixH::dodajDoMacierzy(int n,int m, double wartosc)
{
	macierzGlobalnaH->addValueOfMatrix(n,m, wartosc);
}

globalMatrixH::globalMatrixH(int n){
	macierzGlobalnaH = new Matrix(n,n);
}

Matrix * globalMatrixH::pomnozPrzezVectP(vectP * wektorP){
	return macierzGlobalnaH->multiply(wektorP->VectP);
}

void globalMatrixH::odwroc(){
	bool isInversed = macierzGlobalnaH->inverseMatrix();
	if(!isInversed)
		throw "blad odwracania";
}

globalMatrixH::globalMatrixH(void)
{
}

globalMatrixH::~globalMatrixH(void)
{
	delete macierzGlobalnaH;
}
