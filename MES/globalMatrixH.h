#pragma once
#include "matrix.h"
#include "vectP.h"
class globalMatrixH
{
	Matrix *macierzGlobalnaH;
public:
	globalMatrixH();
	globalMatrixH(int n);
	void dodajDoMacierzy(int n,int m, double wartosc);
	void dodajMacierz(Matrix *);
	void writeMatrix();
	void odwroc();
	Matrix * pomnozPrzezVectP(vectP * wektorP);
	~globalMatrixH(void);
};

