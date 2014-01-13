/*
 * mylog ��װ��yaolog,���������һ�㡣
 * ����ģʽ
 * ʹ��ֻ��Ҫ MyLog::Init() ��ʼ����
 * ��ʹ���� MyLog::Exit(), ȫ�ֱ�������ʱ����Ȼ��Exit()����
 * LOG__(LOGID_I, "something");  //use
 */

#ifndef __MYLOG_H
#define __MYLOG_H
#include "yaolog.h"

#define LOGID_I  "info"
#define LOGID_C  "custom"
#define LOGID_B  "bin"
#define LOGID_FB "formatted_bin"

class MyLog
{
private:
	MyLog();
	static MyLog *m_pInstance;
public:
	~MyLog();
	static void Init();
	static void Exit();
	static MyLog *GetInstance();
	static void CleanInstance();
};
#endif
