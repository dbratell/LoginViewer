// Startup.h: interface for the CStartup class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STARTUP_H__2E9A99EC_9228_4134_B636_A32496028F4F__INCLUDED_)
#define AFX_STARTUP_H__2E9A99EC_9228_4134_B636_A32496028F4F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "StartupShutdown.h"

class CStartup : public CStartupShutdown 
{
public:
	CStartup();
	virtual ~CStartup();
};

#endif // !defined(AFX_STARTUP_H__2E9A99EC_9228_4134_B636_A32496028F4F__INCLUDED_)
