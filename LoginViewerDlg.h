// LoginViewerDlg.h : header file
//

#if !defined(AFX_LOGINVIEWERDLG_H__8AC42751_C539_4B38_85D6_89BBE0EB554D__INCLUDED_)
#define AFX_LOGINVIEWERDLG_H__8AC42751_C539_4B38_85D6_89BBE0EB554D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CLoginViewerDlg dialog

#include "LoginLogout.h"
#include "UserVisit.h"
#include "Startup.h"
#include "Shutdown.h"

class CLoginViewerDlg : public CDialog
{

enum listcolumns { USER, LOGINTIME, LOGOUTTIME, INTIME };

// Construction
public:
	CLoginViewerDlg(CWnd* pParent = NULL);	// standard constructor
	~CLoginViewerDlg();
// Dialog Data
	//{{AFX_DATA(CLoginViewerDlg)
	enum { IDD = IDD_LOGINVIEWER_DIALOG };
	CButton	m_okbutton;
	CButton	m_cancelbutton;
	CButton	m_helpbutton;
	CButton	m_clearbutton;
	CButton	m_refreshbutton;
	CProgressCtrl	m_progressbar;
	CListCtrl	m_listctrl;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLoginViewerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CLoginViewerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnRefreshButton();
	afx_msg void OnClear();
	afx_msg void OnColumnclickLoginlist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void CleanLists();
	BOOL ReadStartupShutdownLog();
	void AnalyzeAndDisplay(CTypedPtrList<CPtrList, CLoginLogout*> *loglist);
	void AddToListControl(CUserVisit &a_uservisit);
	void SetupListColumns();
	void DisplaySecurityRecord(PEVENTLOGRECORD el);
	void SetAllSubItems();
	void ProcessSystemRecord(PEVENTLOGRECORD el);
	static int CALLBACK CompareUserVisit(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	CTypedPtrList<CPtrList, CUserVisit*> m_visitlist;
	CTypedPtrList<CPtrList, CStartup*> m_startuplist;
	CTypedPtrList<CPtrList, CShutdown*> m_shutdownlist;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGINVIEWERDLG_H__8AC42751_C539_4B38_85D6_89BBE0EB554D__INCLUDED_)
