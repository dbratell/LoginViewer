// LoginLogout.h: interface for the CLoginLogout class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGINLOGOUT_H__3D1B2183_01F4_4ADA_9BCF_7A87B5FFC505__INCLUDED_)
#define AFX_LOGINLOGOUT_H__3D1B2183_01F4_4ADA_9BCF_7A87B5FFC505__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

enum logtype {
		EVENTLOG_LOGIN=1,
		EVENTLOG_LOGOUT
};


//#define EVENTLOG_LOGIN 1
//#define EVENTLOG_LOGOUT 2

class CLoginLogout  
{
public:
	CTime GetTime();
	void SetUserName(CString a_name);
	CString GetUserName();
	bool IsSameLogId(const CLoginLogout &other) const;
	bool IsLogin() const;
	bool IsLogout() const;
	CLoginLogout::CLoginLogout(int type, DWORD time, char *a_logid);
	CLoginLogout(CLoginLogout &ll);
	virtual ~CLoginLogout();

private:
	CString m_logid;
/*	DWORD m_psid_length;
	PSID m_psid;
	*/
	CTime m_time;
	DWORD m_type;
	CString m_username;
};

#endif // !defined(AFX_LOGINLOGOUT_H__3D1B2183_01F4_4ADA_9BCF_7A87B5FFC505__INCLUDED_)
