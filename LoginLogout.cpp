// LoginLogout.cpp: implementation of the CLoginLogout class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LoginViewer.h"
#include "LoginLogout.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLoginLogout::CLoginLogout(int type, DWORD time, char *a_logid)
{
	m_type = type;
	m_time = time;

/*	m_psid_length = psid_length;
	m_psid = malloc(psid_length);
	
	if(!m_psid) {
//		MessageBox("Out of memory.\nTry to close a few programs and try again.");
		return;
	}

	CopySid(psid_length, m_psid, a_psid);
*/
	m_logid=a_logid;

	//	m_username = new CString(*username);
}

CLoginLogout::CLoginLogout(CLoginLogout &ll)
{
	m_type = ll.m_type;
	m_time = ll.m_time;
//	m_username = ll.m_username;


}

CLoginLogout::~CLoginLogout()
{
//	delete m_username;

/*	if(m_psid) {
		free(m_psid);
		m_psid = NULL;
	}
	*/
}

bool CLoginLogout::IsLogin() const
{
	return EVENTLOG_LOGIN==m_type;

}

bool CLoginLogout::IsLogout() const
{
	return EVENTLOG_LOGOUT==m_type;

}

bool CLoginLogout::IsSameLogId(const CLoginLogout &other) const
{
	if(other.m_logid.IsEmpty() || m_logid.IsEmpty()) {
		// A NULL logid is not equal any other logid, even NULL.
		return false;
	}

	return !(strcmp(m_logid, other.m_logid));
}


CString CLoginLogout::GetUserName()
{
	return m_username;
}

void CLoginLogout::SetUserName(CString a_name)
{
	m_username = a_name;

}

CTime CLoginLogout::GetTime()
{
	return m_time;
}
