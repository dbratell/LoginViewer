// Shutdown.h: interface for the CShutdown class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHUTDOWN_H__09FFEB3D_294B_434D_9785_271A899E7CF4__INCLUDED_)
#define AFX_SHUTDOWN_H__09FFEB3D_294B_434D_9785_271A899E7CF4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "StartupShutdown.h"

class CShutdown : public CStartupShutdown
{
public:
	CShutdown();
	virtual ~CShutdown();
};

#endif // !defined(AFX_SHUTDOWN_H__09FFEB3D_294B_434D_9785_271A899E7CF4__INCLUDED_)
