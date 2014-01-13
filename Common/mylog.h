/*
 * mylog 封装了yaolog,用起来舒服一点。
 * 单例模式
 * 使用只需要 MyLog::Init() 初始化。
 * 即使忘记 MyLog::Exit(), 全局变量销毁时，仍然会Exit()掉。
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
