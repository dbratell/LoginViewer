// LogAnalyzer.cpp: implementation of the CLogAnalyzer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LoginViewer.h"
#include "LogAnalyzer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLogAnalyzer::CLogAnalyzer()
{

}

CLogAnalyzer::~CLogAnalyzer()
{

}

void CLogAnalyzer::MakeVisitList(CTypedPtrList<CPtrList, CLoginLogout*> *loglist, // IN
		CTypedPtrList<CPtrList, CStartup*> &startuplist, // IN
		CTypedPtrList<CPtrList, CShutdown*> &shutdownlist, // IN
		CTypedPtrList<CPtrList, CUserVisit*> &visitlist) // OUT
{

}