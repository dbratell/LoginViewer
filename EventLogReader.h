// EventLogReader.h: interface for the CEventLogReader class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EVENTLOGREADER_H__7F8C20C2_7A46_49A4_A625_8E74EA667669__INCLUDED_)
#define AFX_EVENTLOGREADER_H__7F8C20C2_7A46_49A4_A625_8E74EA667669__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "LoginLogout.h"

class CEventLogReader  
{
public:
	CTypedPtrList<CPtrList, CLoginLogout*> *ReadSecurityLog();
	CEventLogReader();
	virtual ~CEventLogReader();
	void ProcessSecurityRecord(PEVENTLOGRECORD el,CTypedPtrList<CPtrList, CLoginLogout*> *loglist);

};

#endif // !defined(AFX_EVENTLOGREADER_H__7F8C20C2_7A46_49A4_A625_8E74EA667669__INCLUDED_)
