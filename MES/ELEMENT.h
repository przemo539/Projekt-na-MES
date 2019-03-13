#pragma once
#include"NODE.h"
class ELEMENT
{
	int* idWezlow;
public:
	ELEMENT(void);
	ELEMENT(int, int);
	void ustaw(int, int);
	void printElement();
	int getWezelPoId(int);
	bool getBCPowierzchniPoId(NODE *wezly, int ID);
	double getDlugoscPowierzchniPoId(NODE *wezly, int ID);
	~ELEMENT(void);
};

