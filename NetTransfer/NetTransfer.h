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
// 每send一种,都有一种 type. 每种type都是有意义的才好.~  
// TLV格式, sizeof(T) = 1, sizeof(L) = 4, sizeof(V) = L;
// 每个发送 发送4个字段, T, L, V, checkCode

	unsigned char CheckSum(const string &strSrc);

	bool SendStr(const string &strSnd);
	//文件的检验码,可以发送其 MD5值,作为检验码.暂时不添加吧.
	bool SendFile(const string &strFileName);

	// 阻塞自己,直到有数据.
	bool Recv();

	string RecvStr();
	bool RecvFile(const string &strPathOut);

};


#endif
