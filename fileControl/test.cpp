#include "fileControl.h"

int main(int argc, char **argv)
{
	cout<<"Start to test:"<<endl;

	fileControl fc("/root/Walker//fileControl/ex041219.log");
	if(fc.splitFile(4, true))
        cout<<"spilt file succesful"<<endl;
	return 0;
}
