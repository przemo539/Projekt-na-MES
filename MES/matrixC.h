#pragma once
#include "matrix.h"
#include "jakobian2D.h"
#include "dataFromFile.h"
#include "globalMatrixC.h"
class matrixC
{
	ELEMENT *element;
	jakobian2D* jakobian;
	Matrix *N1, *N2, *N3, *N4;
	Matrix *eta, *ksi;
	Matrix *macierzC;
	Matrix *PC[4];
	double gestosc, cieploWlasciwe;
	void oblicz();
public:
	matrixC(void);
	matrixC(jakobian2D *,double Gestosc, double CieploWlasciwe);
	void wpiszDane(GRID* siatka, jakobian2D *jakob,dataFromFile* daneZPliku, int numerElementu);
	void sumujDoGlobala(globalMatrixC* globalnaMacC);
	~matrixC(void);
};

