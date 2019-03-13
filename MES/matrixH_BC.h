#pragma once
#include "ELEMENT.h"
#include "NODE.h"
#include "matrix.h"
#include "GRID.h"
#include "dataFromFile.h"
#include "globalMatrixH.h"
class matrixH_BC
{
	ELEMENT *element;
	NODE* wezly;
	Matrix *macierzH_BC;
	double alfa;	
	bool pusty;
	void oblicz();
	bool POWIERZCHNIA[4];
public:
	matrixH_BC(void);
	void wpiszDane(GRID *siatka, dataFromFile *daneZPliku, int numerElementu);
	void sumujDoGlobala(globalMatrixH* globalnaMacH);
	void writeMatrix();
	~matrixH_BC(void);
};

