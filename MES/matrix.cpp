#include "matrix.h"
Matrix::Matrix(){};

bool Matrix::inverseMatrix(){
	if(m != n)
		return false;
	Matrix* mat = new Matrix();
	mat->n = n;
	mat->m = m * 2;
	double** table = new double*[mat->n];
	for(int i = 0; i < mat->n; i++){
		double* row = new double[mat->m];
		for(int j = 0; j <m; j++)
			row[j] = data[i][j];
		for(int j = m; j < mat->m; j++)
			row[j] = 0;
		row[m+i]=1;
		table[i] = row;
	}
	mat->data = table;
	reducedRowEchelonForm(mat);
	for(int i = 0; i < mat->n; i++){
		for(int j = 0; j < m; j++)
			data[i][j] = mat->data[i][m + j];
		delete[] mat->data[i];
	}
	delete[] mat->data;
	return true;
}

Matrix* Matrix::multiply(Matrix * rightMat){
	if(m != rightMat->n)
		throw "diffrent dimension of matrixs";
	Matrix * returning = new Matrix(n, rightMat->m);
	for(int i_row=0;i_row<n;i_row++){ //ours m
		for(int j_col=0;j_col< rightMat->m;j_col++){//ours n
			double buffer  = 0.0;
			for(int k_iter=0; k_iter<m;k_iter++){
				buffer +=data[i_row][k_iter]*rightMat->getValueOfMatrix(k_iter,j_col);
			}
			returning->setValueOfMatrix(i_row,j_col,buffer);
		}
	}
				
	return returning;
}

Matrix* Matrix::vektorMultiplyTransVector(int row, int col){
	if(row >= 0 && col == -1){
		Matrix * returning = new Matrix(m, m);
		for(int i_row=0; i_row<m; i_row++)
			for(int j_col=0; j_col<m; j_col++)
				returning->data[j_col][i_row]=data[row][i_row]*data[row][j_col];
		return returning;
	}else if(row == -1 && col >= 0){
		Matrix * returning = new Matrix(n, n);
		for(int i_row=0; i_row<n; i_row++)
			for(int j_col=0; j_col<n; j_col++)
				returning->data[j_col][i_row]=data[i_row][col]*data[j_col][col];
		return returning;
	}else
		return nullptr;
}

Matrix::Matrix(int row, int col, double value){
	n = row;
	m = col;
	double** table = new double*[n];
	for (int i = 0; i < n; i++) {
		double* row = new double[m];
		for (int j = 0; j < m; j++) {
			row[j] = value;
		}
		table[i] = row;
	}
	data = table;
}

void Matrix::addMatrix(Matrix * mat){
	if(n != mat->n || m != mat->m)
		throw "diffrent dimension of matrixs";
	for(int i_row=0;i_row<n;i_row++){
		for(int j_col=0;j_col<m;j_col++)
			data[i_row][j_col] +=mat->getValueOfMatrix(i_row,j_col);
	}
}

double Matrix::determinant () {
	if (m != n)
		throw "Matrix isn't square";
	if (m == 1)
		return data[0][0];
	double w = 0;
	for (int i_row = 0; i_row < n; i_row++) {
		Matrix* cmatrix = copyPartOfMatrix(0, i_row);
		w += pow(-1.0, i_row + 1) * data[i_row][0] * cmatrix->determinant();
		delete cmatrix;
	}
	return -1*w;
}

Matrix* Matrix::copyMatrix() {
	Matrix* matrix = new Matrix();
	matrix->n = n;
	matrix->m = m;
	double** table = new double*[matrix->n];
	for (int i_row = 0; i_row < matrix->n; i_row++) {
		double* row = new double[matrix->m];
		for (int j_col = 0; j_col < matrix->m; j_col++) {
			row[j_col] = data[i_row][j_col];
		}
		table[i_row] = row;
	}
	matrix->data = table;
	return matrix;
}


void Matrix::multiplyByNumber(double a){
	for(int row = 0; row <n; row++)
		for(int col = 0; col <m; col++)
			data[row][col] *= a;
}

void Matrix::rowMultiplyByNumber(int row, double a){
	for(int col=0;col<m;col++)
		data[row][col]*=a;
}

double  Matrix::findMax(){
	if(n == 0 || m == 0)
		throw "matrix doesn't exist";
	double buffer = data[0][0];
	for(int i_row=0;i_row<n;i_row++){
		for(int j_col=0;j_col<m;j_col++){
			if(buffer<data[i_row][j_col])
				buffer = data[i_row][j_col];
		}
	}
	return buffer;
}

double  Matrix::findMin(){
	if(n == 0 || m == 0)
		throw "matrix doesn't exist";
	double buffer = data[0][0];
	for(int i_row=0;i_row<n;i_row++){
		for(int j_col=0;j_col<m;j_col++){
			if(buffer>data[i_row][j_col])
				buffer = data[i_row][j_col];
		}
	}
	return buffer;
}


void Matrix::setValueOfMatrix(int row, int col, double value) {
	data[row][col]=value;
}

void Matrix::addValueOfMatrix(int row, int col, double value) {
	data[row][col]+=value;
}


double Matrix::getValueOfMatrix(int row, int col) {
	return data[row][col];
}

void Matrix::writeMatrix() {
	for (int row = 0; row < n; row++) {
		for (int col = 0; col < m; col++) {
			std::cout << data[row][col] << '\t';
		}
		std::cout << std::endl;
	}
	std::cout << std::endl<<std::endl;
}
Matrix::~Matrix(){
	for (int row = 0; row < n; row++) {
		delete data[row];
	}
	delete data;
}

Matrix* Matrix::copyPartOfMatrix(int remx, int remy) {
	Matrix* matrix = new Matrix();
	matrix->n = n - 1;
	matrix->m = m - 1;
	double** table = new double*[matrix->n];
	for (int i = 0, ipos = 0; i < n; i++) {
		if (i != remy) {
			double* row = new double[matrix->m];
			for (int j = 0, jpos = 0; j < m; j++) {
				if (j != remx) {
					row[jpos] = data[i][j];
					jpos++;
				}
			}
			table[ipos] = row;
			ipos++;
		}
	}
	matrix->data = table;
	return matrix;
}

void Matrix::elementalType1(Matrix* mat, int row_1, int row_2){
	double* lista = mat->data[row_1];
	mat->data[row_1] = mat->data[row_2];
	mat->data[row_2] = lista;
}

void Matrix::elementalType2(Matrix* mat, int row_1, double c, int row_2){
	for(int j = 0; j < mat->m; j++)
		mat->data[row_1][j] += c * mat->data[row_2][j];
}

void Matrix::elementalType3(Matrix* mat, int row_1, double c){
	for(int j = 0; j < mat->m; j++)
		mat->data[row_1][j] = c * mat->data[row_1][j];
}

void Matrix::reducedRowEchelonForm(Matrix* mat){
	int row = 0;
	int col = 0;
	while(row < mat->n && col < mat->m){
		int j = 0;
		while(j + row < mat->n && mat->data[j + row][col] == 0)
			j++;
		if(j + row == mat->n){
			col++;
		} else {
			if(j != 0)
				elementalType1(mat, row, j+row);
			if(mat->data[row][col] != 1)
				elementalType3(mat, row, 1/mat->data[row][col]);
			for(j = 0; j < mat->n; j++)
				if(j != row && mat->data[j][col] != 0)
					elementalType2(mat, j, -mat->data[j][col], row);
			row++;
			col++;
        }
	}
}
