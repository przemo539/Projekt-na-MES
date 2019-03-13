#include "matrixH_BC.h"

void matrixH_BC::wpiszDane(GRID *siatka, dataFromFile *daneZPliku, int numerElementu){
	pusty = true;
	element = siatka->getElement(numerElementu);
	wezly = siatka->getWezly();
	for(int i=0; i<4; i++)
		POWIERZCHNIA[i] = element->getBCPowierzchniPoId(wezly, i);
	
	for(int i=0; i<4; i++)
		if(POWIERZCHNIA[i]) pusty = false;
	if(!pusty){
		alfa = daneZPliku->getAlfa();
		macierzH_BC = new Matrix(4,4);
		oblicz();
	}
}

void  matrixH_BC::writeMatrix(){
	if(!pusty){
		macierzH_BC->writeMatrix();
	}
}

void  matrixH_BC::sumujDoGlobala(globalMatrixH* globalnaMacH){
	if(!pusty){
		for(int i=0; i<4;i++)
			for(int j=0; j<4; j++)
				globalnaMacH->dodajDoMacierzy(element->getWezelPoId(i),element->getWezelPoId(j), macierzH_BC->getValueOfMatrix(i,j));
	}
}

void matrixH_BC::oblicz(){
	//generujemy stale KSI + funkcje kszta³tu dla 1D
	double ksi[2], N1[2],N2[2];
	ksi[0] = -1/sqrt(3.0);
	ksi[1] = 1/sqrt(3.0);
	for(int i =0; i<2; i++){
		N1[i] = (1-ksi[i])/2.0;
		N2[i]=(ksi[i]+1)/2.0;
	}
	Matrix *PC1 = new Matrix(2,2); 
	Matrix *PC2 = new Matrix(2,2); 


	//OBLICZENIA POWIERZCHNIA 0
	if(POWIERZCHNIA[0]){//dziala ok
		for(int i=0; i<2;i++)
			for(int j=0;j<2;j++){
				//MNOZYMY {N}*{N}^T * alfa
				PC1->setValueOfMatrix(i,j, N1[i]*N1[j]*alfa);
				PC2->setValueOfMatrix(i,j, N2[i]*N2[j]*alfa);
			}
		PC1->addMatrix(PC2);
		//MNOZYMY RAZY deltaX/2
		PC1->multiplyByNumber(element->getDlugoscPowierzchniPoId(wezly, 0)/2);
		for(int i=0;i<2;i++)
			for(int j=0;j<2;j++)
				macierzH_BC->addValueOfMatrix(i,j, PC1->getValueOfMatrix(i,j));
		// | BC[0;0] BC[0;1]     0        0    |
		// | BC[1;0] BC[1;1]     0        0    |
		// |    0        0       0        0    |
		// |    0        0       0        0    |
	}


	//OBLICZENIA POWIERZCHNIA 1
	if(POWIERZCHNIA[1]){//troche ubylo
		for(int i=0; i<2;i++)
			for(int j=0;j<2;j++){
				//MNOZYMY {N}*{N}^T * alfa
				PC1->setValueOfMatrix(i,j, N1[i]*N1[j]*alfa);
				PC2->setValueOfMatrix(i,j, N2[i]*N2[j]*alfa);
			}
		PC1->addMatrix(PC2);
		//MNOZYMY RAZY deltaX/2
		PC1->multiplyByNumber(element->getDlugoscPowierzchniPoId(wezly, 1)/2);
		for(int i=0;i<2;i++)
			for(int j=0;j<2;j++)
				macierzH_BC->addValueOfMatrix(i+1,j+1, PC1->getValueOfMatrix(i,j));
		// |    0        0       0        0    |
		// |    0     BC[0;0] BC[0;1]     0    |
		// |    0     BC[1;0] BC[1;1]     0    |
		// |    0        0       0        0    |
	}


		//OBLICZENIA POWIERZCHNIA 2
	if(POWIERZCHNIA[2]){//duzo ubylo
		for(int i=0; i<2;i++)
			for(int j=0;j<2;j++){
				//MNOZYMY {N}*{N}^T * alfa
				PC1->setValueOfMatrix(i,j, N1[i]*N1[j]*alfa);
				PC2->setValueOfMatrix(i,j, N2[i]*N2[j]*alfa);
			}
		PC1->addMatrix(PC2);
		//MNOZYMY RAZY deltaX/2
		PC1->multiplyByNumber(element->getDlugoscPowierzchniPoId(wezly, 2)/2);
		for(int i=0;i<2;i++)
			for(int j=0;j<2;j++)
				macierzH_BC->addValueOfMatrix(i+2,j+2, PC1->getValueOfMatrix(i,j));
		// |    0        0       0        0    |
		// |    0        0       0        0    |
		// |    0        0     BC[0;0] BC[0;1] |
		// |    0        0     BC[1;0] BC[1;1] |
	}
	//OBLICZENIA POWIERZCHNIA 3
	if(POWIERZCHNIA[3]){
		for(int i=0; i<2;i++)
			for(int j=0;j<2;j++){
				//MNOZYMY {N}*{N}^T * alfa
				PC1->setValueOfMatrix(i,j, N1[i]*N1[j]*alfa);
				PC2->setValueOfMatrix(i,j, N2[i]*N2[j]*alfa);
			}
		PC1->addMatrix(PC2);
		//MNOZYMY RAZY deltaX/2
		PC1->multiplyByNumber(element->getDlugoscPowierzchniPoId(wezly, 3)/2);
		for(int i=0;i<2;i++)
			for(int j=0;j<2;j++)
				macierzH_BC->addValueOfMatrix(i+i*2,j+j*2, PC1->getValueOfMatrix(i,j));
		// | BC[0;0]     0       0     BC[0;1] |
		// |    0        0       0        0    |
		// |    0        0       0        0    |
		// | BC[1;0]     0       0     BC[1;1] |
	}

}

matrixH_BC::matrixH_BC(void)
{
}

matrixH_BC::~matrixH_BC(void)
{
	if(!pusty){
		delete macierzH_BC;
	}
}