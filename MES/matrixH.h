#pragma once
#include "matrix.h"
#include "jakobian2D.h"
#include "GRID.h"
#include "ELEMENT.h"
#include "dataFromFile.h"
#include "globalMatrixH.h"
class matrixH
{
	ELEMENT *element;
	jakobian2D* jakobian;
	Matrix *dN_dKsi, *dN_dEta;
	Matrix *eta, *ksi;
	Matrix *dN_dX, *dN_dY;
	Matrix *macierzH;
	double k;
	void generujStale();
	void oblicz();
public:
	matrixH(void);
	matrixH(jakobian2D *, double przewodnosc);
	void wpiszDane(jakobian2D *, double przewodnosc);
	void wpiszDane(GRID *siatka, jakobian2D * tablicaJakobianow, dataFromFile *daneZPliku, int numerElementu);
	void sumujDoGlobala(globalMatrixH* globalnaMacH);
	void wypisz();
	~matrixH(void);
};

