#pragma once
#include <iostream>
class NODE
{
	double x;
	double y;
	bool bc;
public:
	NODE(void);
	NODE(double, double, bool);
	void ustaw(double, double, bool);
	void wypiszPozycje(int id);
	double getY();
	double getX();
	bool getBC();
	~NODE(void);
};

