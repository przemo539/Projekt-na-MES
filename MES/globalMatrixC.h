#pragma once
#include "matrix.h"
class globalMatrixC
{
	Matrix *macierzGlobalnaC;
public:
	globalMatrixC(void);
	globalMatrixC(int n);
	void dodajDoMacierzy(int n,int m, double wartosc);
	void writeMatrix();
	void pomnozPrzezLiczbe(double);
	Matrix * pomnozPrzezWektor(Matrix *);
	Matrix *getMacierz();
	~globalMatrixC(void);
};

