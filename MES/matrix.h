#pragma once
#include <cmath>
#include <iostream>
class Matrix {
	double** data;
	int n;
	int m;
	Matrix* copyPartOfMatrix(int remx, int remy);
	void elementalType1(Matrix* mat, int row_1, int row_2);
	void elementalType2(Matrix* mat, int row_1, double c, int row_2);
	void elementalType3(Matrix* mat, int row_1, double c);
	void reducedRowEchelonForm(Matrix* mat);
public:
	Matrix();
	Matrix(int row, int col, double value=0);	
	void multiplyByNumber(double a);
	Matrix* multiply(Matrix * rightMat);
	void rowMultiplyByNumber(int row, double a);
	void setValueOfMatrix(int row, int col, double value);
	void addValueOfMatrix(int row, int col, double value);
	double getValueOfMatrix(int row, int col);
	void writeMatrix() ;
	double determinant();
	void addMatrix(Matrix * mat);
	Matrix* vektorMultiplyTransVector(int row, int col);
	bool inverseMatrix();
	double findMax();
	double findMin();
	Matrix* copyMatrix();
	~Matrix();
};
