#include "matrixC.h"

matrixC::matrixC(void)
{
}
void matrixC::sumujDoGlobala(globalMatrixC* globalnaMacC){
	for(int i=0; i<4;i++)
		for(int j=0; j<4; j++)
			globalnaMacC->dodajDoMacierzy(element->getWezelPoId(i),element->getWezelPoId(j), macierzC->getValueOfMatrix(i,j));
}


matrixC::matrixC(jakobian2D * jak, double Gestosc, double CieploWlasciwe)
{	
	gestosc = Gestosc;
	cieploWlasciwe = CieploWlasciwe;
	jakobian = jak;
	eta = jakobian->getEta();
	ksi = jakobian->getKsi();
	N1 = jakobian->getN1();
	N2 = jakobian->getN2();
	N3 = jakobian->getN3();
	N4 = jakobian->getN4();
	macierzC = new Matrix(4,4);
	oblicz();
}

void matrixC::wpiszDane(GRID* siatka, jakobian2D *jakob,dataFromFile *daneZPliku, int numerElementu){
	element = siatka->getElement(numerElementu);
	gestosc = daneZPliku->getGestosc();
	cieploWlasciwe = daneZPliku->getCieploWlasciwe();
	jakobian = &jakob[numerElementu];
	eta = jakobian->getEta();
	ksi = jakobian->getKsi();
	N1 = jakobian->getN1();
	N2 = jakobian->getN2();
	N3 = jakobian->getN3();
	N4 = jakobian->getN4();
	macierzC = new Matrix(4,4);
	oblicz();
}

matrixC::~matrixC(void)
{
	delete macierzC;
	for(int i=0;i<4;i++){
		delete PC[i];
	}
}


void matrixC::oblicz(){
	//N1->writeMatrix();
	//Obliczamy {N1}{N1} dla PC1 -> pozniej mnozymy razy gestosc i cieploWlasciwe
	PC[0] = N1->vektorMultiplyTransVector(-1, 0);
	PC[0]->multiplyByNumber(jakobian->getJakobian(0) * gestosc * cieploWlasciwe);
	//PC[0]->writeMatrix();

	//Obliczamy {N2}{N2} dla PC2 -> pozniej mnozymy razy gestosc i cieploWlasciwe
	PC[1] = N2->vektorMultiplyTransVector(-1, 0);
	PC[1]->multiplyByNumber(jakobian->getJakobian(0) * gestosc * cieploWlasciwe);
	//PC[1]->writeMatrix();

	//Obliczamy {N3}{N3} dla PC3 -> pozniej mnozymy razy gestosc i cieploWlasciwe
	PC[2] = N3->vektorMultiplyTransVector(-1, 0);
	PC[2]->multiplyByNumber(jakobian->getJakobian(0) * gestosc * cieploWlasciwe);
	//PC[2]->writeMatrix();

	//Obliczamy {N4}{N4} dla PC4 -> pozniej mnozymy razy gestosc i cieploWlasciwe
	PC[3] = N4->vektorMultiplyTransVector(-1, 0);
	PC[3]->multiplyByNumber(jakobian->getJakobian(0) * gestosc * cieploWlasciwe);
	//PC[3]->writeMatrix();

	//Sumujemy poszczególne Cp{N}{N} uzyskuj¹æ macierz C
	for(int i=0;i<4;i++)
		macierzC->addMatrix(PC[i]);
	//macierzC->writeMatrix();
}