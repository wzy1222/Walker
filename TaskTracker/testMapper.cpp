#include "Mapper.h"

using namespace std;

int main()
{

	MyLog::Init();
	Mapper mp("ex041224.log");

	mp.Run();


	MyLog::Exit();
	return 0;
}
