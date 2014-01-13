#include "Reducer.h"



Reducer::Reducer(char *pName)
{
	ssize_t len = strlen(pName);
	if(len > FILE_NAME_MAX)
	{
		LOG__(LOGID_I, "fileControl::fileControl(): file name is too long");
		exit(1);
	}
	strncpy(m_inputFile, pName, FILE_NAME_MAX - 1);
	m_inputFile[FILE_NAME_MAX] = '\0';	

	sprintf(m_pathFileOut, "%s_RedOutput", m_inputFile);
}

Reducer::~Reducer()
{

}

bool Reducer::InputCollect(ifstream &fsIn, pair<string, string> &pairStr)
{
	string str1, str2;

	if(!fsIn.eof())
		fsIn >> str1;
	if(!fsIn.eof())
		fsIn >> str2;

	if(str1=="" && str2 == "")
		return false;

	pairStr = make_pair(str1, str2);
	return true;
}
bool Reducer::Reduce(pair<string, string> pairStr, pair<string, int> &pairSI)
{
	istringstream strstm;
	string strUrl = pairStr.first;
	int sum = 0;
	int num;
	string strTmp = pairStr.second;

	for(string::size_type i = 0; i < strTmp.size(); ++i)
	{
		if(strTmp[i] == ',')
			strTmp[i] = ' ';
	}

	strstm.str(strTmp);

	while(strstm >> num)
	{
		if(strstm.fail())
		{
			LOG__(LOGID_I, "Invalied input..");
			strstm.clear();
			strstm.ignore(200, ' ');
			continue;
		}
		sum += num;
	}

	if(sum == 0)
		return false;
	pairSI = make_pair(strUrl, sum);
	return true;

}
bool Reducer::OutputCollect(FILE *fpOut, pair<string, int>  &pairSI)
{
	fprintf(fpOut, "%s %d\n", pairSI.first.c_str(), pairSI.second);
}
bool Reducer::Run()
{	
	vector<string> vecStr;
	vector< pair<string, int> > vecPair;

	pair<string, string> pairStr;
	pair<string, int> pairSI;
	ifstream ifs;
	FILE *fpWrite;

	ifs.open(m_inputFile);
	if(!ifs.good())
	{
		LOG__(LOGID_I, "ifstream open() failed...");
		exit (-1);
	}
	fpWrite = fopen(m_pathFileOut, "w");
	if(fpWrite == NULL)
	{
		LOG__(LOGID_I, "fopen(w) failed...");
		exit (-1);
	}

	while(InputCollect(ifs, pairStr) == true)
	{
		if(false == Reduce(pairStr, pairSI))
			continue;
		OutputCollect(fpWrite, pairSI); 
	}	


	ifs.close();
	fclose(fpWrite);
		
	return true;
}
