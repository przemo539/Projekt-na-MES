#pragma once
#include "ELEMENT.h"
#include "NODE.h"
#include "matrix.h"
#include "GRID.h"
#include <cmath>
using namespace std;
class jakobian2D
{
	ELEMENT* element;
	NODE* wezly;
	Matrix *ksi, *eta, *N1, *N2, *N3, *N4;
	Matrix* Xp, *Yp;
	Matrix* dN_dKsi, *dN_dEta;
	Matrix* jakobian[4];
	void generujStale();
	void oblicz();
public:
	jakobian2D();
	jakobian2D(ELEMENT*, NODE *);
	void wpiszDane(ELEMENT*, NODE *);
	void wpiszDane(GRID* siatka, int numerElementu);
	Matrix *getKsi();
	Matrix *getEta();
	Matrix *getN1();
	Matrix *getN2();
	Matrix *getN3();
	Matrix *getN4();
	double getWartoscZJakobiego(int punktCalkowania, int n, int m);
	double getJakobian(int punktCalkowania);
	~jakobian2D(void);
};

