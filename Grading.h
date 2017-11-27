
#ifndef GRADING_H
#define GRADING_H

#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/foreach.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <Windows.h>
#include <queue>
#include <random>
#include <ctime>

#include "SubmitList.h"
#include "tinyxml2.h"
#include "Submit.h"
#include "Heap.h"

class Grading
{
public:
	Grading();
	void process();
	void readTask();
	void processFolder(Submit s);
	std::string getCompileStr(Submit t, std::string compileStd);
	void compileAndRun(Submit s);
	bool compare(std::string path, std::string path2);
private:
	SubmitList* submitList;
	
	const int N_TESTCASE = 5;
};
#endif // !GRADING_H
