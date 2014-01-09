#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#include "../my_unp.h"

using namespace std;

#define FILE_NAME_MAX 1024
#define FILE_SPLIT_MAX 10

class fileControl
{
private:
	char pfilename[FILE_NAME_MAX];
public:
	fileControl(const char *pname);
	~fileControl();

	bool splitFile(int nBlock, bool bOneLine);
};
