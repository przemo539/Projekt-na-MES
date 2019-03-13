#pragma once
#include "dataFromFile.h"
#include "GRID.h"
#include "jakobian2D.h"
class vectP
{
	friend class globalMatrixH;
	ELEMENT * element;
	NODE * wezly;
	double alfa;
	double tOtoczenia;
	Matrix * VectP;
	bool POWIERZCHNIA[4];
	bool pusty;
	void oblicz();
public:
	vectP(void);
	vectP(int kolumny);
	void wpiszDane(GRID *siatka, jakobian2D * tablicaJakobianow, dataFromFile *daneZPliku, int numerElementu);
	void sumujDoGlobala(vectP* globalnyVectP);
	void writeMatrix();
	void dodajWektor(Matrix * wektor);
	~vectP(void);
};

