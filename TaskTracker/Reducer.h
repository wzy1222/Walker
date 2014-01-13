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

	//InputCollect ���ļ���ȡ����,ÿһ���� (key, <v1,v2...vn>) ��ʽ
	//��Ϊ <v1,v2,...,vn> ���ܻᳬ����������C++�������������
	bool InputCollect(ifstream &fsIn, pair<string, string> &pairStr);
	bool Reduce(pair<string, string> pairStr, pair<string, int> &pairSI);
	bool OutputCollect(FILE *fpOut, pair<string, int>  &pairSI);
	bool Run();
};


#endif
