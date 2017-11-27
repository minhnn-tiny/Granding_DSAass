#include "MatrixMult.h"

using namespace std;

MatrixMult::MatrixMult()
{

}
MatrixMult::~MatrixMult()
{

}
void MatrixMult::makeTestCase()
{
	default_random_engine engine(static_cast<int>(time(0)));
	uniform_int_distribution<int> rndInt(10, 100);
	uniform_int_distribution<int> rndNumber(-100, 100);
	for (int t = 0; t < 5; ++t)
	{
		int row1 = rndInt(engine);
		int col1 = rndInt(engine);
		int row2 = col1;
		int col2 = rndInt(engine);
		int** matrix = new int*[row1];
		for (int i = 0; i < row1; ++i)
			matrix[i] = new int[col1];

		int** matrix2 = new int*[row2];
		for (int i = 0; i < row2; ++i)
			matrix2[i] = new int[col2];

		for (int i = 0; i < row1; ++i)
			for (int j = 0; j < col1; ++j)
				matrix[i][j] = rndNumber(engine);

		for (int i = 0; i < row2; ++i)
			for (int j = 0; j < col2; ++j)
				matrix2[i][j] = rndNumber(engine);

		int** ans = mult(matrix, row1, col1, matrix2, row2, col2);

		string path = serverPath + "\\Testcase\\Test" + to_string(t + 1) + "\\input1.txt";
		string pathAns = serverPath + "\\Testcase\\Test" + to_string(t + 1) + "\\output.txt";
		writeMatrix(matrix, row1, col1, path);
		writeNext(matrix2, row2, col2, path);
		writeMatrix(ans, row1, col2, pathAns);
	}
}
int** MatrixMult::mult(int** mat1, int row1, int col1, int** mat2, int row2, int col2)
{
	int** ans = new int*[row1];
	for (int i = 0; i < row1; ++i)
	{
		ans[i] = new int[col2];
		for (int j = 0; j < col2; ++j)
			ans[i][j] = 0;
	}

	for (int i = 0; i < row1; ++i)
		for (int j = 0; j < col2; ++j)
			for (int k = 0; k < col1; ++k)
				ans[i][j] += mat1[i][k] * mat2[k][j];

	return ans;
}
void MatrixMult::writeMatrix(int** mat, int row, int col, std::string path)
{
	ofstream fs(path);
	fs << row << " " << col << endl;
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			fs << mat[i][j] << " ";
		}
		fs << endl;
	}
	fs.close();
}
void MatrixMult::writeNext(int** mat, int row, int col, std::string path)
{
	fstream fs(path, ios::app);
	fs << row << " " << col << endl;
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			fs << mat[i][j] << " ";
		}
		fs << endl;
	}
	fs.close();
}