#ifndef __NET_TRANSFER_H
#define __NET_TRANSFER_H

#include "../Common/walkerstd.h"
#include "../Common/mylog.h"
#include "../Common/my_unp.h"

using namespace std;

//Transfer Type
enum TSF_TYPE
{
	TSF_TYPE_STRING = 21,
	TSF_TYPE_FILE
};

class NetTransfer
{
private:
	int connfd;
public:
	NetTransfer(int connfd);
	~NetTransfer();
// ÿsendһ��,����һ�� type. ÿ��type����������Ĳź�.~  
// TLV��ʽ, sizeof(T) = 1, sizeof(L) = 4, sizeof(V) = L;
// ÿ������ ����4���ֶ�, T, L, V, checkCode

	unsigned char CheckSum(const string &strSrc);

	bool SendStr(const string &strSnd);
	//�ļ��ļ�����,���Է����� MD5ֵ,��Ϊ������.��ʱ�����Ӱ�.
	bool SendFile(const string &strFileName);

	// �����Լ�,ֱ��������.
	bool Recv();

	string RecvStr();
	bool RecvFile(const string &strPathOut);

};


#endif