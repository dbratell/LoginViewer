// LogAnalyzer.h: interface for the CLogAnalyzer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGANALYZER_H__ACCD4E10_1B0C_4570_A284_811D5D1F1009__INCLUDED_)
#define AFX_LOGANALYZER_H__ACCD4E10_1B0C_4570_A284_811D5D1F1009__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "LoginLogout.h"
#include "Startup.h"
#include "Shutdown.h"
#include "UserVisit.h"

class CLogAnalyzer  
{
public:
	static void MakeVisitList(CTypedPtrList<CPtrList, CLoginLogout*> *loglist,
		CTypedPtrList<CPtrList, CStartup*> &startuplist,
		CTypedPtrList<CPtrList, CShutdown*> &shutdownlist,
		CTypedPtrList<CPtrList, CUserVisit*> &visitlist);
	CLogAnalyzer();
	virtual ~CLogAnalyzer();

};

#endif // !defined(AFX_LOGANALYZER_H__ACCD4E10_1B0C_4570_A284_811D5D1F1009__INCLUDED_)
