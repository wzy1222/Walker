#include "mylog.h"
MyLog *MyLog::m_pInstance = NULL;

MyLog::MyLog()
{
	
}
MyLog::~MyLog()
{
	Exit();
}
MyLog *MyLog::GetInstance()
{
	return m_pInstance;
}
void MyLog::CleanInstance()
{
	if(m_pInstance != NULL)
		delete m_pInstance;
	m_pInstance = NULL;
}

void MyLog::Init()
{
	if(m_pInstance == NULL)
	{
		m_pInstance = new MyLog();
		YAOLOG_INIT;   

		// ������־����
		YAOLOG_CREATE(LOGID_I, true, YaoUtil::LOG_TYPE_TEXT);
		YAOLOG_CREATE(LOGID_C, true, YaoUtil::LOG_TYPE_TEXT);
		YAOLOG_CREATE(LOGID_B, true, YaoUtil::LOG_TYPE_BIN);
		YAOLOG_CREATE(LOGID_FB, true, YaoUtil::LOG_TYPE_FORMATTED_BIN);

		YAOLOG_SET_LOG_ATTR(
			LOGID_I, true,
			YaoUtil::OUT_FLAG_STDOUT | YaoUtil::OUT_FLAG_FILE,
			true, false, true, true, NULL);
	}
}
void MyLog::Exit()
{
	if(m_pInstance != NULL)
		YAOLOG_EXIT;
	CleanInstance();
}

// LOG__(LOGID_I, "something");  //use
