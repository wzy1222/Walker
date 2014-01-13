#include "Reducer.h"

using namespace std;

int main()
{
	MyLog::Init();
	Reducer red("log100.log");
	red.Run();


	LOG__(LOGID_I, "test Reducer.");
	
	MyLog::Exit();
}
