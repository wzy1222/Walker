#ifndef __MAPPER_H
#define __MAPPER_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "../Common/mylog.h"
#include "../Common/walkerstd.h"
#include <sstream>
using namespace std;

#define FILE_NAME_MAX 1024
#define VECTOR_MAX 100

class Mapper
{
private:
	char m_inputFile[FILE_NAME_MAX + 1];
	char m_pathMapOut[FILE_NAME_MAX + 1 + 10];

public:
	Mapper(char *pName);
	~Mapper();

	//InputCollect ���ļ���ȡ���ݣ���֮����vector��һ������VECTOR_MAX����
	bool InputCollect(FILE *fpIn, vector<string> &vecOut);
	bool Map(vector<string> vecStr, vector< pair<string, int> > &vecPair);
	bool OutputCollect(FILE *fpOut, vector< pair<string, int> > &vecPair);

	bool Run();
};


#endif