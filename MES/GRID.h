#include "ELEMENT.h"
#include "NODE.h"
#include "dataFromFile.h"
#pragma once
class GRID
{
	NODE *wezly;
	ELEMENT *elementy;
	int nh, nl;
	double H, L;

public:
	void generujSiatke(dataFromFile * DaneZPliku);
	ELEMENT * getElement(int numer);
	void importujSiatke(ELEMENT * el, NODE * no);
	NODE * getWezly();
	GRID(void);
	~GRID(void);
};

