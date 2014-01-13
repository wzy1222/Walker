#include "Mapper.h"



Mapper::Mapper(char *pName)
{
	ssize_t len = strlen(pName);
	if(len > FILE_NAME_MAX)
	{
		LOG__(LOGID_I, "fileControl::fileControl(): file name is too long");
		exit(1);
	}
	strncpy(m_inputFile, pName, FILE_NAME_MAX - 1);
	m_inputFile[FILE_NAME_MAX] = '\0';	

	sprintf(m_pathMapOut, "%s_MapOutput", m_inputFile);
}

Mapper::~Mapper()
{

}

bool Mapper::InputCollect(FILE *fpIn, vector<string> &vecOut)
{
	char buf[MAXLINE];
	string str;
	int ncount = 0;


	vecOut.clear();
	while(fgets(buf, MAXLINE, fpIn) != NULL)
	{
		str = buf;
		vecOut.push_back(str);
		++ncount;
		if(ncount >= VECTOR_MAX)
			break;
	}	
	if(vecOut.size() == 0)
		return false;
	return true;
}
bool Mapper::Map(vector<string> vecStr, vector< pair<string, int> > &vecPair)
{
	//对每一行,提取出URL,用 pair<URL, 1> 
	istringstream strstm;
	string strUrl;
	vecPair.clear();

	for(int i = 0; i < vecStr.size(); ++i)
	{
		strstm.str(vecStr[i]);
		// 第3串是URL
		for(int j = 0; j < 3; ++j)
			strstm >> strUrl;
		if( strUrl != "")
			vecPair.push_back(make_pair(strUrl, 1));
		strstm.clear();
	}
	
	if(vecPair.size() == 0)
		return false;
	return true;

}
bool Mapper::OutputCollect(FILE *fpOut, vector< pair<string, int> > &vecPair)
{
	for(int i = 0; i < vecPair.size(); ++i)
	{
		fprintf(fpOut, "%s %d\n", vecPair[i].first.c_str(), vecPair[i].second);
	}
}
bool Mapper::Run()
{	
	vector<string> vecStr;
	vector< pair<string, int> > vecPair;
	FILE *fpRead;
	FILE *fpWrite;

	fpRead = fopen(m_inputFile, "r");
	if(fpRead == NULL)
	{
		LOG__(LOGID_I, "fopen() failed...");
		exit (-1);
	}
	fpWrite = fopen(m_pathMapOut, "w");
	if(fpWrite == NULL)
	{
		LOG__(LOGID_I, "fopen(w) failed...");
		exit (-1);
	}

	while(InputCollect(fpRead, vecStr) == true)
	{
		if(false == Map(vecStr, vecPair))
			continue;
		OutputCollect(fpWrite, vecPair); 
	}	

	fclose(fpRead);
	fclose(fpWrite);
		
	return true;
}
