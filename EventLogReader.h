// EventLogReader.h: interface for the CEventLogReader class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EVENTLOGREADER_H__7F8C20C2_7A46_49A4_A625_8E74EA667669__INCLUDED_)
#define AFX_EVENTLOGREADER_H__7F8C20C2_7A46_49A4_A625_8E74EA667669__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "LoginLogout.h"
#include "Startup.h"
#include "Shutdown.h"

class CEventLogReader  
{
public:
	CEventLogReader();
	static CTypedPtrList<CPtrList, CLoginLogout*> *ReadSecurityLog();
	virtual ~CEventLogReader();
	static BOOL ReadStartupShutdownLog(CTypedPtrList<CPtrList, CStartup*> &startuplist,
		CTypedPtrList<CPtrList, CShutdown*> &shutdownlist);
private:
	void Cleanup();
	static void ProcessSecurityRecord(PEVENTLOGRECORD el,CTypedPtrList<CPtrList, CLoginLogout*> *loglist);
	static void ProcessSystemRecord(PEVENTLOGRECORD el,
		CTypedPtrList<CPtrList, CStartup*> &startuplist,
		CTypedPtrList<CPtrList, CShutdown*> &shutdownlist);

};

#endif // !defined(AFX_EVENTLOGREADER_H__7F8C20C2_7A46_49A4_A625_8E74EA667669__INCLUDED_)
