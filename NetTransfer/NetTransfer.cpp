#include "NetTransfer.h"

NetTransfer::NetTransfer(int connfd)
{
	this->connfd = connfd;
}

NetTransfer::~NetTransfer()
{

}
unsigned char NetTransfer::CheckSum(const string &strSrc)
{
	unsigned char ckCode = 0;
	for(string::size_type i = 0; i < strSrc.size(); ++i)
		ckCode ^= strSrc[i];
	return ckCode;
}


bool NetTransfer::SendStr(const string &strSnd)
{
    LOG__(LOGID_I, "connfd = %d",connfd);
	if(strSnd.size() == 0)
		return false;
	unsigned char type = TSF_TYPE_STRING;
	unsigned int len = strSnd.size();
	unsigned int netLen;
	unsigned char ckCode;

	if(sizeof(type) != writen(connfd, &type, sizeof(type)))
		return false;
	netLen = htonl(len);
	if(sizeof(len) != writen(connfd, &netLen, sizeof(len)))
		return false;

	if(strSnd.size() != writen(connfd, strSnd.c_str(), strSnd.size()))
		return false;

	ckCode = CheckSum(strSnd);
	if(sizeof(ckCode) != writen(connfd, &ckCode, sizeof(ckCode)))
		return false;


	return true;
		
}
bool NetTransfer::SendFile(const string &strFileName)
{
	FILE *fp = fopen(strFileName.c_str(), "r");
	if(fp == NULL)
	{
		LOG__(LOGID_I, "fopen() failed");
		return false;
	}
	unsigned char type = TSF_TYPE_FILE;
	unsigned int len;
	if(-1 == fseek(fp, 0, SEEK_END))
	{
		LOG__(LOGID_I, "fseek() to end failed..");
		fclose(fp);
		return false;
	}
	len = (unsigned int)ftell(fp);
	if(-1 == fseek(fp, 0, SEEK_SET))
	{
		LOG__(LOGID_I, "fseek() to start failed..");
		fclose(fp);
		return false;
	}


	unsigned int netLen;
	if(sizeof(type) != writen(connfd, &type, sizeof(type)))
		return false;
	netLen = htonl(len);
	if(sizeof(len) != writen(connfd, &netLen, sizeof(len)))
		return false;

	char buf[MAXLINE];
	unsigned int nleft = len;
	unsigned int nsend;
	while(nleft > 0)
	{
		if(nleft > MAXLINE)
			nsend = MAXLINE;
		else
			nsend = nleft;
		if(nsend != fread(buf, sizeof(char), nsend, fp))
		{
			LOG__(LOGID_I, "fread() failed..");
			fclose(fp);
			return false;
		}
		if(nsend != writen(connfd, buf, nsend))
		{
			LOG__(LOGID_I, "writen failed..");
			fclose(fp);
			return false;
		}
		nleft -= nsend;
	}
	
	fclose(fp);
	if(nleft < 0)
	{
		LOG__(LOGID_I, "sendFile() failed,nleft < 0");
		return false;
	}
	return true;
}

bool NetTransfer::Recv()
{
	unsigned char recvType;
    LOG__(LOGID_I, "connfd = %d",connfd);
	while(1)
	{
        ssize_t n;
		if(1 != (n=read(connfd, &recvType, 1)))
		{
			LOG__(LOGID_I, "read type failed..n=%d",n);
			return false;
		}
		switch(recvType)
		{
			case TSF_TYPE_STRING:
			{
				string str = RecvStr();
                LOG__(LOGID_I, "the string is %s", str.c_str());


			}
				break;
			case TSF_TYPE_FILE:
			{
				string strPath = "recvFileName";
				RecvFile(strPath);
                LOG__(LOGID_I, "write File done..");
			}
				break;
			default:
				break;
	
		}
	}

}
string NetTransfer::RecvStr()
{
	unsigned int len = 0;
	string strRes = "";
	if(4 != readn(connfd, &len, 4))
	{
		LOG__(LOGID_I, "read lenth failed");
		return strRes;
	}
	len = ntohl(len);

	//�ظ����û�����.
	char buf[MAXLINE] = {0};
	int nleft = len;
	int n;
	while(nleft > 0)
	{
		if(nleft > MAXLINE)
			n = MAXLINE;
		else
			n = nleft;
		if(n != readn(connfd, buf, n))
		{
			LOG__(LOGID_I, "read value failed..");
			return strRes;
		}
		strRes += buf;
		nleft -= n;
	}
	if(nleft < 0)
	{
		LOG__(LOGID_I, "RecvStr failed...");
		return string("");
	}

	//�����֤һ��У����.
	unsigned char ckCode;
	if(sizeof(ckCode) != readn(connfd, &ckCode, sizeof(ckCode)))
	{
		LOG__(LOGID_I, "readn : read ckCode failed");
		return string("");
	}
	if(ckCode != CheckSum(strRes))
	{
		LOG__(LOGID_I, "check the string failed..");
		return string("");
	}

	LOG__(LOGID_I, "the string is %s", strRes.c_str());
	return strRes;
}

bool NetTransfer::RecvFile(const string &strPathOut)
{
	FILE *fp = fopen(strPathOut.c_str(), "w");
	if(fp == NULL)
	{
		LOG__(LOGID_I, "failed in fopen..");
		return false;
	}
	unsigned int len = 0;
	if(4 != readn(connfd, &len, 4))
	{
		LOG__(LOGID_I, "read lenth failed");
		fclose(fp);
		return false;
	}
	len = ntohl(len);

	//�ظ����û�����.
	char buf[MAXLINE] = {0};
	int nleft = len;
	int n;
	while(nleft > 0)
	{
		if(nleft > MAXLINE)
			n = MAXLINE;
		else
			n = nleft;
		if(n != readn(connfd, buf, n))
		{
			LOG__(LOGID_I, "read value failed..");
			fclose(fp);
			return false;
		}

		if(n != fwrite(buf, sizeof(char), n, fp))
		{
			LOG__(LOGID_I, "fwrite failed..");
			fclose(fp);
			return false;
		}
		nleft -= n;
	}
	if(nleft < 0)
	{
		LOG__(LOGID_I, "RecvStr failed...");
		fclose(fp);
		return false;
	}


	fclose(fp);
	return true;
}