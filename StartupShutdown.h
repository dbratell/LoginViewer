// StartupShutdown.h: interface for the CStartupShutdown class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STARTUPSHUTDOWN_H__78DB9229_2D57_422D_AD02_0F69EB0862C4__INCLUDED_)
#define AFX_STARTUPSHUTDOWN_H__78DB9229_2D57_422D_AD02_0F69EB0862C4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CStartupShutdown  
{
public:
	CStartupShutdown();
	virtual ~CStartupShutdown();
	void SetTime(CTime a_time);
	CTime GetTime();
	BOOL HasTime();

private:
	BOOL m_hastime;
	CTime m_time;
};

#endif // !defined(AFX_STARTUPSHUTDOWN_H__78DB9229_2D57_422D_AD02_0F69EB0862C4__INCLUDED_)
