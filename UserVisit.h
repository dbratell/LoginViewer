// UserVisit.h: interface for the CUserVisit class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_USERVISIT_H__9D42FDC3_8EBA_4EEE_BDB7_05F2841836E1__INCLUDED_)
#define AFX_USERVISIT_H__9D42FDC3_8EBA_4EEE_BDB7_05F2841836E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CUserVisit  
{
public:
	BOOL HasLoginTime();
	BOOL HasLogoutTime();
	void SetName(CString a_name);
	CString GetName();
	CTimeSpan GetLoggedinTime();
	CTime GetLoginTime();
	CTime GetLogoutTime();
	BOOL HasLoggedinTime();
	void SetLogoutTime(CTime a_time);
	CUserVisit();
	void SetLoginTime(CTime a_time);
	void SetDefinitelyOutBy(CTime a_time);
	BOOL HasDefinitelyOutBy();
	CTime GetDefinitelyOutBy();
	virtual ~CUserVisit();

private:
	BOOL m_hasdefinitelyoutby;
	CTime m_definitelyoutby;
	BOOL m_hasloggedintime;
	BOOL m_haslogouttime;
	BOOL m_haslogintime;
	CTime m_logouttime;
	CTime m_logintime;
	CTimeSpan m_loggedintime;
	CString m_username;
};

#endif // !defined(AFX_USERVISIT_H__9D42FDC3_8EBA_4EEE_BDB7_05F2841836E1__INCLUDED_)
