#include <iostream>
#include "mylog.h"

using namespace std;

int main()
{
	MyLog::Init();

	LOG__(LOGID_I, "tes.......");

	MyLog::Exit();
	return 0;
}
