#include "globalMatrixC.h"

Matrix * globalMatrixC::pomnozPrzezWektor(Matrix * wektor){
	return macierzGlobalnaC->multiply(wektor);
}

void globalMatrixC::writeMatrix(){
	macierzGlobalnaC->writeMatrix();
}

Matrix* globalMatrixC::getMacierz(){
	return macierzGlobalnaC;
}

void globalMatrixC::pomnozPrzezLiczbe(double liczba){
	macierzGlobalnaC->multiplyByNumber(liczba);
}

void globalMatrixC::dodajDoMacierzy(int n,int m, double wartosc)
{
	macierzGlobalnaC->addValueOfMatrix(n,m, wartosc);
}

globalMatrixC::globalMatrixC(int n){
	macierzGlobalnaC = new Matrix(n,n);
}


globalMatrixC::globalMatrixC(void)
{
}


globalMatrixC::~globalMatrixC(void)
{
	delete macierzGlobalnaC;
}
