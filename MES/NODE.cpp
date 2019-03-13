#include "NODE.h"
NODE::NODE(double X, double Y, bool BC)
{
	x=X;
	y=Y;
	bc=BC;
}

void NODE::ustaw(double X, double Y, bool BC)
{
	x=X;
	y=Y;
	bc=BC;
}

void NODE::wypiszPozycje(int id){
	std::cout << "ID["<<id<<"]: X:"<<x<<", Y:"<< y<<", BC:"<<bc<<std::endl;
}

double NODE::getX(){
	return x;
}

double NODE::getY(){
	return y;
}

bool NODE::getBC(){
	return bc;
}

NODE::NODE(void)
{
}

NODE::~NODE(void)
{
}
