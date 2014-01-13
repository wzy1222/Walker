#ifndef __REDUCER_H
#define __REDUCER_H

#include <iostream>
#include <vector>
#include <string>
#include "../Common/mylog.h"
#include "../Common/walkerstd.h"
#include <sstream>
#include <fstream>
using namespace std;



class Reducer
{
private:
	char m_inputFile[FILE_NAME_MAX + 1];
	char m_pathFileOut[FILE_NAME_MAX + 1 + 10];

public:
	Reducer(char *pName);
	~Reducer();

	//InputCollect 从文件读取数据,每一行是 (key, <v1,v2...vn>) 格式
	//因为 <v1,v2,...,vn> 可能会超长超长，用C++流来读避免溢出
	bool InputCollect(ifstream &fsIn, pair<string, string> &pairStr);
	bool Reduce(pair<string, string> pairStr, pair<string, int> &pairSI);
	bool OutputCollect(FILE *fpOut, pair<string, int>  &pairSI);
	bool Run();
};


#endif
