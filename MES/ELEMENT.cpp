#include "ELEMENT.h"
#include <iostream>


ELEMENT::ELEMENT(void)
{
	idWezlow = new int[4];
}

ELEMENT::ELEMENT(int pierwszy, int nH)
{
	idWezlow = new int[4];
	idWezlow[0] = pierwszy;
    idWezlow[1] = pierwszy + nH;
    idWezlow[2] = pierwszy + nH + 1;
    idWezlow[3] = pierwszy + 1;    
}
void ELEMENT::ustaw(int pierwszy, int nH)
{
	idWezlow = new int[4];
	idWezlow[0] = pierwszy;
    idWezlow[1] = pierwszy + nH;
    idWezlow[2] = pierwszy + nH + 1;
    idWezlow[3] = pierwszy + 1;    
}

void ELEMENT::printElement(){
        std::cout << "Id wezlow: " << " "  << idWezlow[0] << " " << idWezlow[1] << " " << idWezlow[2] << " " << idWezlow[3]<<std::endl;
}

int ELEMENT::getWezelPoId(int ID){
	return idWezlow[ID];
}

bool ELEMENT::getBCPowierzchniPoId(NODE *wezly, int ID){
	return (wezly[idWezlow[ID%4]].getBC() && wezly[idWezlow[(ID+1)%4]].getBC());
}

double ELEMENT::getDlugoscPowierzchniPoId(NODE *wezly, int ID){
	return sqrt(pow((wezly[idWezlow[(ID+1)%4]].getX()-wezly[idWezlow[ID%4]].getX()),2)+pow((wezly[idWezlow[(ID+1)%4]].getY()-wezly[idWezlow[ID%4]].getY()),2));
}

ELEMENT::~ELEMENT(void)
{
	delete[] idWezlow;
}
