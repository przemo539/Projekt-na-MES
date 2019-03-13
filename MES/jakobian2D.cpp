#include "jakobian2D.h"

jakobian2D::jakobian2D(){}
jakobian2D::jakobian2D(ELEMENT* el, NODE * no){
	wpiszDane(el, no);
}
void jakobian2D::wpiszDane(ELEMENT* el, NODE * no){
	element = el;
	wezly = no;
	generujStale();
	for(int i=0;i<4;i++)
		jakobian[i]=new Matrix(2,2);
	oblicz();
}
void jakobian2D::wpiszDane(GRID* siatka,int numerElementu){
	element = siatka->getElement(numerElementu);
	wezly = siatka->getWezly();
	generujStale();
	for(int i=0;i<4;i++)
		jakobian[i]=new Matrix(2,2);
	oblicz();
}

double jakobian2D::getJakobian(int punktCalkowania){
	return jakobian[punktCalkowania]->determinant();
}

double jakobian2D::getWartoscZJakobiego(int punktCalkowania, int n, int m){
	return (jakobian[punktCalkowania]->getValueOfMatrix(n,m)*(1/jakobian[punktCalkowania]->determinant()));
}

Matrix *jakobian2D::getN1(){
	return N1;
}

Matrix *jakobian2D::getN2(){
	return N2;
}

Matrix *jakobian2D::getN3(){
	return N3;
}

Matrix *jakobian2D::getN4(){
	return N4;
}

Matrix *jakobian2D::getKsi(){
	return ksi;
}

Matrix *jakobian2D::getEta(){
	return eta;
}

jakobian2D::~jakobian2D(){
	delete ksi,	eta, N1, N2, N3, N4, Yp, Xp, dN_dKsi, dN_dEta;
	for(int i=0;i<4;i++)
		delete jakobian[i];
}

void jakobian2D::oblicz(){
	dN_dKsi = new Matrix(4,4);
	//1 FUNKCJA KSZTA£TU  -0.25*(1-ETA)  DLA ETA OD [0;3]
	for(int i=0;i<4;i++)
		dN_dKsi->setValueOfMatrix(0,i, -0.25*(1-eta->getValueOfMatrix(i,0)));
	//2 FUNKCJA KSZTA£TU 0.25*(1-ETA)  DLA ETA OD [0;3]
	for(int i=0;i<4;i++)
		dN_dKsi->setValueOfMatrix(1,i, 0.25*(1-eta->getValueOfMatrix(i,0)));
	//3 FUNKCJA KSZTA£TU 0.25*(1+ETA)  DLA ETA OD [0;3]
	for(int i=0;i<4;i++)
		dN_dKsi->setValueOfMatrix(2,i, 0.25*(1+eta->getValueOfMatrix(i,0)));
	//4 FUNCKA KSZTA£TU -0.25*(1+ETA)  DLA ETA OD [0;3]
	for(int i=0;i<4;i++)
		dN_dKsi->setValueOfMatrix(3,i, -0.25*(1+eta->getValueOfMatrix(i,0)));

	dN_dEta = new Matrix(4,4);
	//1 FUNKCJA KSZTA£TU  -0.25*(1-KSI)  DLA KSI OD [0;3]
	for(int i=0;i<4;i++)
		dN_dEta->setValueOfMatrix(0,i, -0.25*(1-ksi->getValueOfMatrix(i,0)));
	//2 FUNKCJA KSZTA£TU -0.25*(1-KSI)  DLA KSI OD [0;3]
	for(int i=0;i<4;i++)
		dN_dEta->setValueOfMatrix(1,i, -0.25*(1+ksi->getValueOfMatrix(i,0)));
	//3 FUNKCJA KSZTA£TU 0.25*(1+KSI)  DLA KSI OD [0;3]
	for(int i=0;i<4;i++)
		dN_dEta->setValueOfMatrix(2,i, 0.25*(1+ksi->getValueOfMatrix(i,0)));
	//4 FUNCKA KSZTA£TU 0.25*(1+KSI)  DLA KSI OD [0;3]
	for(int i=0;i<4;i++)
		dN_dEta->setValueOfMatrix(3,i, 0.25*(1-ksi->getValueOfMatrix(i,0)));


	
	for(int i = 0; i<4;i++){
		double jacobiX = 0.0;
		//LICZENIE z dN/dKsi -> N1[i]*P1[X] + N2[i]*P2[X] + N3[i]*P3[x] + N4[i]*P4[X] -> i to punkt calkowania
		// | dN/dKsi[X] ...|
		// |   ...      ...|
		for(int j=0; j<4;j++)
			jacobiX += wezly[element->getWezelPoId(j)].getX()*dN_dKsi->getValueOfMatrix(j,0);
			
		jakobian[i]->setValueOfMatrix(0,0,jacobiX);
		double jacobiY = 0.0;
		//LICZENIE  z dN/dKsi -> N1[i]*P1[Y] + N2[i]*P2[Y] + N3[i]*P3[Y] + N4[i]*P4[Y] -> i to punkt calkowania
		// |... dN/dKsi[Y]|
		// |...      ...  |
		for(int j=0; j<4;j++)
		for(int j=0; j<4;j++)
			jacobiY += wezly[element->getWezelPoId(j)].getY()*dN_dKsi->getValueOfMatrix(j,0);

		jakobian[i]->setValueOfMatrix(0,1,jacobiY);
	}

	for(int i = 0; i<4;i++){
		double jacobiX = 0.0;
		//LICZENIE z dN/dEta -> N1[i]*P1[X] + N2[i]*P2[X] + N3[i]*P3[X] + N4[i]*P4[X] -> i to punkt calkowania
		// |  ...      ... |
		// |dN/dEta[x] ... |
		for(int j=0; j<4;j++)
			jacobiX += wezly[element->getWezelPoId(j)].getX()*dN_dEta->getValueOfMatrix(j,0);

		jakobian[i]->setValueOfMatrix(1,0,jacobiX);
		double jacobiY = 0.0;
		//LICZENIE z dN/dEta -> N1[i]*P1[Y] + N2[i]*P2[Y + N3[i]*P3[Y] + N4[i]*P4[Y] -> i to punkt calkowania
		// |...     ...   |
		// |... dN/dEta[y]|		
		for(int j=0; j<4;j++)
			jacobiY += wezly[element->getWezelPoId(j)].getY()*dN_dEta->getValueOfMatrix(j,0);

		jakobian[i]->setValueOfMatrix(1,1,jacobiY);
	}


}

void jakobian2D::generujStale(){
	//MACIERZ STA£YCH KSI
	ksi = new Matrix(4,1);
	ksi->setValueOfMatrix(0, 0, -1/sqrt(3.0));
	ksi->setValueOfMatrix(1, 0, 1/sqrt(3.0));
	ksi->setValueOfMatrix(2, 0, 1/sqrt(3.0));
	ksi->setValueOfMatrix(3, 0, -1/sqrt(3.0));
	//MACIERZ STA£YCH ETA
	eta = new Matrix(4,1);
	eta->setValueOfMatrix(0, 0, -1/sqrt(3.0));
	eta->setValueOfMatrix(1, 0, -1/sqrt(3.0));
	eta->setValueOfMatrix(2, 0, 1/sqrt(3.0));
	eta->setValueOfMatrix(3, 0, 1/sqrt(3.0));
	//MACIERZ N1 = 0.25*(1 - ETA)(1 - NI) DLA ETA I KSI OD [0;3]
	N1 = new Matrix(4,1);
	for(int i=0;i<4;i++)
		N1->setValueOfMatrix(i, 0, 0.25*(1-ksi->getValueOfMatrix(i, 0))*(1-eta->getValueOfMatrix(i, 0)));
	//MACIERZ N2 = 0.25*(1 + ETA)(1 - NI) DLA ETA I KSI OD [0;3]
	N2 = new Matrix(4,1);
	for(int i=0;i<4;i++)
		N2->setValueOfMatrix(i, 0, 0.25*(1+ksi->getValueOfMatrix(i, 0))*(1-eta->getValueOfMatrix(i, 0)));
	//MACIERZ N3 = 0.25*(1 + ETA)(1 + NI) DLA ETA I KSI OD [0;3]
	N3 = new Matrix(4,1);
	for(int i=0;i<4;i++)
		N3->setValueOfMatrix(i, 0, 0.25*(1+ksi->getValueOfMatrix(i, 0))*(1+eta->getValueOfMatrix(i, 0)));
	//MACIERZ N4 = 0.25*(1 - ETA)(1 - NI) DLA ETA I KSI OD [0;3]
	N4 = new Matrix(4,1);
	for(int i=0;i<4;i++)
		N4->setValueOfMatrix(i, 0, 0.25*(1-ksi->getValueOfMatrix(i, 0))*(1+eta->getValueOfMatrix(i, 0)));
	//MACIERZ Xp = N1*P1[X] + N2*P2[X] + N3*P[X]+N4*P[X] DLA FUNKCJI KSZTALTU OD [0;3]
	Xp = new Matrix(4,1);
	for(int i=0;i<4;i++)
		Xp->setValueOfMatrix(i, 0, (wezly[element->getWezelPoId(0)].getX()*N1->getValueOfMatrix(i,0) +
									wezly[element->getWezelPoId(1)].getX()*N2->getValueOfMatrix(i,0) +
									wezly[element->getWezelPoId(2)].getX()*N3->getValueOfMatrix(i,0) +
									wezly[element->getWezelPoId(3)].getX()*N4->getValueOfMatrix(i,0)));
	//MACIERZ Yp = N1*P1[Y] + N2*P2[Y] + N3*P[Y]+N4*P[Y] DLA FUNKCJI KSZTALTU OD [0;3]
	Yp = new Matrix(4,1);
	for(int i=0;i<4;i++)
		Yp->setValueOfMatrix(i, 0, (wezly[element->getWezelPoId(0)].getY()*N1->getValueOfMatrix(i,0) + 
									wezly[element->getWezelPoId(1)].getY()*N2->getValueOfMatrix(i,0) + 
									wezly[element->getWezelPoId(2)].getY()*N3->getValueOfMatrix(i,0) + 
									wezly[element->getWezelPoId(3)].getY()*N4->getValueOfMatrix(i,0)));

}