#include <iostream>
#include <algorithm>
#include <string>
#include <random>
#include <fstream>
#include <ctime>

#include "Submit.h"

class MatrixMult
{
public:
	MatrixMult();
	~MatrixMult();
	static void makeTestCase();
private:
	static int** mult(int**, int, int, int**, int, int);
	static void writeMatrix(int**, int, int, std::string);
	static void writeNext(int**, int, int, std::string);
	
};

