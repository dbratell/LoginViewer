// UserVisit.cpp: implementation of the CUserVisit class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LoginViewer.h"
#include "UserVisit.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUserVisit::CUserVisit() :
m_haslogintime(FALSE),
m_haslogouttime(FALSE),
m_hasloggedintime(FALSE),
m_hasdefinitelyoutby(FALSE)
{

}

CUserVisit::~CUserVisit()
{

}

/**
 * Sets the login time.
 * @param in CTime a_time The login time
 */
void CUserVisit::SetLoginTime(CTime a_time)
{
	m_haslogintime = TRUE;
	m_logintime = a_time;
	if(m_haslogouttime) {
		m_loggedintime = m_logouttime - m_logintime;
		m_hasloggedintime = TRUE;
	}

}

void CUserVisit::SetLogoutTime(CTime a_time)
{
	m_haslogouttime = TRUE;
	m_logouttime = a_time;
	if(m_haslogintime) {
		m_loggedintime = m_logouttime - m_logintime;
		m_hasloggedintime = TRUE;
	}

	m_hasdefinitelyoutby=TRUE;
	m_definitelyoutby=a_time;
}

void CUserVisit::SetDefinitelyOutBy(CTime a_time)
{
	if(m_haslogouttime) {
		return;
	}
	if(!m_hasdefinitelyoutby || 
		(m_definitelyoutby > a_time)) {
		m_hasdefinitelyoutby = TRUE;
		m_definitelyoutby = a_time;
	}
}

BOOL CUserVisit::HasLoggedinTime()
{
	return m_hasloggedintime;
}

CTimeSpan CUserVisit::GetLoggedinTime()
{
	ASSERT(m_hasloggedintime);
	return m_loggedintime;
}

CTime CUserVisit::GetDefinitelyOutBy()
{
	ASSERT(m_hasdefinitelyoutby);
	return m_definitelyoutby;
}

CTime CUserVisit::GetLoginTime()
{
	ASSERT(m_haslogintime);
	return m_logintime;
}

CTime CUserVisit::GetLogoutTime()
{
	ASSERT(m_haslogouttime);
	return m_logouttime;
}

void CUserVisit::SetName(CString a_name)
{
	m_username = a_name;

}

CString CUserVisit::GetName()
{
	return m_username;
}

BOOL CUserVisit::HasLoginTime()
{
	return m_haslogintime;

}

BOOL CUserVisit::HasLogoutTime()
{
	return m_haslogouttime;
}

BOOL CUserVisit::HasDefinitelyOutBy()
{
	return m_hasdefinitelyoutby;
}
