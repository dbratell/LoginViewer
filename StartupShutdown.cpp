// StartupShutdown.cpp: implementation of the CStartupShutdown class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LoginViewer.h"
#include "StartupShutdown.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStartupShutdown::CStartupShutdown() :
m_hastime(FALSE)
{

}

CStartupShutdown::~CStartupShutdown()
{

}

void CStartupShutdown::SetTime(CTime a_time) 
{
	m_hastime=TRUE;
	m_time = a_time;
}

CTime CStartupShutdown::GetTime()
{
	ASSERT(m_hastime);
	return m_time;
}

BOOL CStartupShutdown::HasTime()
{
	return m_hastime;
}
