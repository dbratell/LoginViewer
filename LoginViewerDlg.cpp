// LoginViewerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LoginViewer.h"
#include "LoginViewerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLoginViewerDlg dialog

CLoginViewerDlg::CLoginViewerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLoginViewerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLoginViewerDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
//	m_loglist = new CTypedPtrList<CPtrList, CLoginLogout*>;
}

CLoginViewerDlg::~CLoginViewerDlg()
{
	CleanLists();
}

void CLoginViewerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLoginViewerDlg)
	DDX_Control(pDX, IDOK, m_okbutton);
	DDX_Control(pDX, IDCANCEL, m_cancelbutton);
	DDX_Control(pDX, ID_HELP, m_helpbutton);
	DDX_Control(pDX, IDC_CLEAR, m_clearbutton);
	DDX_Control(pDX, IDC_REFRESHBUTTON, m_refreshbutton);
	DDX_Control(pDX, IDC_PROGRESS, m_progressbar);
	DDX_Control(pDX, IDC_LOGINLIST, m_listctrl);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CLoginViewerDlg, CDialog)
	//{{AFX_MSG_MAP(CLoginViewerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_REFRESHBUTTON, OnRefreshButton)
	ON_BN_CLICKED(IDC_CLEAR, OnClear)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LOGINLIST, OnColumnclickLoginlist)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLoginViewerDlg message handlers

BOOL CLoginViewerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	SetupListColumns();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CLoginViewerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

void CLoginViewerDlg::OnDestroy()
{
	WinHelp(0L, HELP_QUIT);
	CDialog::OnDestroy();
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CLoginViewerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CLoginViewerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CLoginViewerDlg::OnRefreshButton() 
{

	HCURSOR wait_pointer = LoadCursor(NULL, IDC_WAIT);
	HCURSOR normal_pointer = LoadCursor(NULL, IDC_ARROW);
	// Set cursor to a waiting cursor.
	// XXX: Disable menus
	m_okbutton.EnableWindow(FALSE);
	m_refreshbutton.EnableWindow(FALSE);
	m_cancelbutton.EnableWindow(FALSE);
	m_helpbutton.EnableWindow(FALSE);
	m_clearbutton.EnableWindow(FALSE);

	SetCursor(wait_pointer);

	// Locate startups and shutdowns
	// Progress 5%
	m_progressbar.SetRange(0,100);
	m_progressbar.SetPos(0);
	ReadStartupShutdownLog();
	m_progressbar.SetPos(5);
	
	// Progress 5%
	// Open the security event log
	if(ReadSecurityLog()) {
		m_progressbar.SetPos(10);
		// The list will have somewhere between n/2 and n items
		// where n is the number of items in m_loglist. Let's prepare
		// for the worst case.
		m_listctrl.SetItemCount(m_loglist.GetCount());
		// Progress 90%
		m_progressbar.SetRange32(0,m_loglist.GetCount()*10/9);
		m_progressbar.SetPos(m_loglist.GetCount()/10);
		AnalyzeAndDisplay();
	}
	m_progressbar.SetRange(0,100);
	m_progressbar.SetPos(100);

	m_okbutton.EnableWindow(TRUE);
	m_refreshbutton.EnableWindow(TRUE);
	m_cancelbutton.EnableWindow(TRUE);
	// m_helpbutton.EnableWindow(TRUE);
	m_clearbutton.EnableWindow(TRUE);

	SetCursor(normal_pointer);
	
}

void CLoginViewerDlg::DisplaySecurityRecord(PEVENTLOGRECORD el)
{
	char string[1024];
	sprintf(string, "Length: %d\nRecordNumber: %d\nTime Generated: %d\nTimeWritten: %d\nEventID: %d\nEventTyp: %d\nEvent Category:%d",
		el->Length, el->RecordNumber, el->TimeGenerated, el->TimeWritten, el->EventID, el->EventType,el->EventCategory);
	::MessageBox(NULL, string, NULL, MB_OK);
}

/*
Eventid
528: Successful Logon
529: Logon Failure: Unknown user name or bad password
537: Logon Failure: An unexpected error occurred during logon
538: User Logoff
540: Successful Network Logon:
680: Account Used for Logon by...
681: The logon to account:... failed


514 An authentication package has been loaded by the LSA
515 A trusted logon process has registered with the LSA
518 A notification package has been loaded by the Security Account Manager
528 Successful Logon
529 Logon Failure: Unknown user name or bad password
530 Logon Failure: Account logon time restriction violation
531 Logon Failure: Account currently disabled
532 Logon Failure: The specified user account has expired
533 Logon Failure: User not allowed to logon at this computer
534 Logon Failure: The user has not been granted the requested logon type at this machine
535 Logon Failure: The specified account's password has expired
536 Logon Failure: The NetLogon component is not active
537 Logon Failure: An unexpected error occurred during logon
538 User Logoff
539 Logon Failure: Account locked out



Category:
   9: Account Logon
   2: Logon/logoff
*/
void CLoginViewerDlg::ProcessSecurityRecord(PEVENTLOGRECORD el)
{
	PTCHAR sourcename;
/*	PSID psid;
	DWORD psid_length;
	*/
	CLoginLogout *ll;

	// Definition of event types?
	// Definition of event ids?

	if(el->EventType != EVENTLOG_AUDIT_SUCCESS) {
		// Nothing for us
		return;
	}

	// A successful audit.

	// Check if source is "Security"
	sourcename = ((char *)&el->DataOffset) + sizeof(el->DataOffset);
	if(strcmp(sourcename, "Security")) {
		// Nope, nothing for us
		return;
	}
	// Check category for a login/logout event
	if(2 != el->EventCategory) {
		// Nothing for us
		return;
	}
	
/*psid_length = el->UserSidLength;
	psid = new BYTE[psid_length];
	if(!psid) {
		MessageBox("Out of memory.\nTry to close a few programs and try again.");
		return;
	}
*/
/*	CopySid(psid_length,
		psid,
		(PSID) ( ((char *)el) + el->UserSidOffset));
*/

/*	DWORD name_buffer_size = 1024;
	char *name_buffer = (char *)malloc(name_buffer_size);
	if(!name_buffer) {
		MessageBox("Out of memory.\nTry to close a few programs and try again.");
		return;
	}
	DWORD domain_name_buffer_size = 1024;
	char *domain_name_buffer = (char *)malloc(domain_name_buffer_size);
	if(!domain_name_buffer) {
		MessageBox("Out of memory.\nTry to close a few programs and try again.");
		return;
	}

	SID_NAME_USE su;

	CString *username;

	if(LookupAccountSid(NULL, psid,
		name_buffer, &name_buffer_size,
		domain_name_buffer, &domain_name_buffer_size,
		&su))
	{
		username = new CString(name_buffer);
	} else {
		username = new CString("<unknown>");
	}

*/
	PTCHAR *logstrings=NULL;
	if(el->NumStrings>0) {
		logstrings = new PTCHAR[el->NumStrings];
		PTCHAR str = (PTCHAR)((LPBYTE)el + el->StringOffset);
		for(int i=0; i<el->NumStrings; i++) {
			logstrings[i] = str;
			// Next string
			str = str+strlen(str)+1;
		}
	}


	CString user;
	// Check EventID
	switch(el->EventID) {
	case 528:
		// Login
		ASSERT(el->TimeGenerated>0);
		ASSERT(el->NumStrings>=3);
		ll = new CLoginLogout(EVENTLOG_LOGIN, el->TimeGenerated,logstrings[2]);
		user = logstrings[0];
		ll->SetUserName(user);
		m_loglist.AddTail(ll);
		break;
	case 538:
		// Logoff
		ASSERT(el->NumStrings>=3);
		ASSERT(el->TimeGenerated>0);
		ll = new CLoginLogout(EVENTLOG_LOGOUT, el->TimeGenerated,logstrings[2]);
		user = logstrings[0];
		ll->SetUserName(user);
		m_loglist.AddTail(ll);
		break;
	case 529:
	case 537:
		// Login failure
		break;
	case 540: // XXX: 540 not in definition list but looks like a login
		// Network Login
		ASSERT(el->NumStrings>=3);
		ASSERT(el->TimeGenerated>0);
		ll = new CLoginLogout(EVENTLOG_LOGIN, el->TimeGenerated,logstrings[2]);
		user = logstrings[0];
		ll->SetUserName(user);
		m_loglist.AddTail(ll);
		break;
	default: ;// nothing
	}

	// DisplayEventlogRecord(el);

	// Clean up

	delete logstrings;
	logstrings = NULL;

/*	delete psid;
	psid = NULL;
*/	

/*	if(name_buffer) {
		free(name_buffer);
		name_buffer = NULL;
	}

	if(domain_name_buffer) {
		free(domain_name_buffer);
		name_buffer = NULL;
	}

	if(username) {
		delete username;
		username = NULL;
	}
*/	
	
}

void CLoginViewerDlg::SetupListColumns()
{
	LVCOLUMN col;
	col.mask = LVCF_SUBITEM;
	// col.fmt =
	// col.cx =
	// col.pszText =
	// col.cchTextMax = 
	col.iSubItem = 0;

	m_listctrl.InsertColumn(USER,"Person", LVCFMT_LEFT, 100,USER);
	m_listctrl.InsertColumn(INTIME,"Tid", LVCFMT_LEFT, 150,INTIME);
	m_listctrl.InsertColumn(LOGINTIME,"Logintid", LVCFMT_LEFT, 150,LOGINTIME);
	m_listctrl.InsertColumn(LOGOUTTIME,"Logouttid", LVCFMT_LEFT, 150,LOGOUTTIME);

}

/**
 * Adds a row to the list control and keeps a reference to the 
 * CUserVisit. You better be sure that it's not in the list control
 * before deleting it.
 */
void CLoginViewerDlg::AddToListControl(CUserVisit &a_uservisit)
{
	CString timestr;
	int count = m_listctrl.GetItemCount();
	LVITEM lv;
	lv.mask = LVIF_TEXT | LVIF_PARAM; 
    lv.iItem = count; 
    lv.iSubItem = USER; 
    // lv.state ; 
    // lv.stateMask; 
    lv.pszText = const_cast<LPTSTR>((LPCTSTR) a_uservisit.GetName()); 
    // lv.cchTextMax; 
    // int iImage; 
    lv.lParam = reinterpret_cast<LPARAM>(&a_uservisit);
	m_listctrl.InsertItem(&lv);
}

void CLoginViewerDlg::OnClear() 
{
	// TODO: Add your control notification handler code here
	m_listctrl.DeleteAllItems();
	m_progressbar.SetPos(0);

	CleanLists();
}

void CLoginViewerDlg::AnalyzeAndDisplay()
{
	// Analyze data

	// For every login, find a logout or a "shutdown". Record those.
	  // need new login structure to save information in.

	// XXX: BAD BAD n^2 algorithm

	m_listctrl.LockWindowUpdate(); // To make the insertion a batch one

	CLoginLogout *ll;
	while(!m_loglist.IsEmpty()) {
		ll = m_loglist.RemoveHead();

		if(ll->IsLogout()) {
			// Logout with no login

			if(0 == (ll->GetUserName().CompareNoCase("guest"))) {
				// Noticed that failed guest logins will generate
				// a logout.
				delete ll;
				m_progressbar.OffsetPos(1);

				// Next entry
				continue;
			}

			if(0 == (ll->GetUserName().CompareNoCase("ANONYMOUS LOGON"))) {
				// Don't know if they should be kept, but drop them for
				// now.
				delete ll;
				m_progressbar.OffsetPos(1);

				// Next entry
				continue;
			}

			
			CUserVisit *uv = new CUserVisit();
			uv->SetName(ll->GetUserName());
			uv->SetLogoutTime(ll->GetTime());

			m_visitlist.AddTail(uv);
			AddToListControl(*uv);

			// clean up
			delete ll;
			m_progressbar.OffsetPos(1);

			// Next entry
			continue; 
		}

		ASSERT(ll->IsLogin());

		CUserVisit *uv = new CUserVisit();
		uv->SetName(ll->GetUserName());
		uv->SetLoginTime(ll->GetTime());

		// Find logout matching this login
		POSITION findlogout = m_loglist.GetHeadPosition();
		while(NULL != findlogout) {
			if(m_loglist.GetAt(findlogout)->IsLogout() &&
				m_loglist.GetAt(findlogout)->IsSameLogId(*ll)) {
				// Match!
					break;
			}
			m_loglist.GetNext(findlogout);
		}

		if(NULL == findlogout) {
			// No matching logout
			// Find shutdown closest after login
			POSITION p;
			CTime closest;
			BOOL found = FALSE;
			p = m_shutdownlist.GetHeadPosition();
			while(NULL != p) {
				if(m_shutdownlist.GetAt(p)->GetTime() > ll->GetTime()) {
					closest = m_shutdownlist.GetAt(p)->GetTime();
					found = TRUE;
					break;
				}
				m_shutdownlist.GetNext(p);
			}

			// If there was a crash there is no shutdown but a startup 
			// closer then the shutdown.
			p = m_startuplist.GetHeadPosition();
			while(NULL != p){
				if((m_startuplist.GetAt(p)->GetTime() > ll->GetTime()) && 
					(!found || 
						(m_startuplist.GetAt(p)->GetTime() < closest ))) {
					closest = m_startuplist.GetAt(p)->GetTime();
					found = TRUE;
				}

				if(found && m_startuplist.GetAt(p)->GetTime() > closest) {
					break;
				}

				m_startuplist.GetNext(p);
			}

			if(found) {
				uv->SetDefinitelyOutBy(closest);
			}

			// TRACE(" No match ");
		} else {
			// Here we should have a match
			// TRACE("\nMatch");
			CLoginLogout *templl = m_loglist.GetAt(findlogout);
			uv->SetLogoutTime(templl->GetTime());
			m_loglist.RemoveAt(findlogout);
			delete templl;
			m_progressbar.OffsetPos(1);
		}

		delete ll;
		m_progressbar.OffsetPos(1);
		m_visitlist.AddTail(uv);
		AddToListControl(*uv);
	}


	SetAllSubItems();

	m_listctrl.UnlockWindowUpdate();

}

/**
 * Returns TRUE if it succeeded
 */
BOOL CLoginViewerDlg::ReadSecurityLog()
{
	BOOL rv;
	DWORD bytes_read, buffer_size_required;
	HANDLE eventlog;
	LPVOID buffer_pointer;
	DWORD buffer_size = 4*1024; // 4 KB

	eventlog = OpenEventLog(NULL, "Security");

	if(!eventlog) {
		MessageBox("Couldn't open the security event log.\nIt is in the security eventlog that logins and logouts are recorded. Do you have the rights to read that log?");
		return FALSE;
	}

	// Get a buffer
	buffer_pointer = new BYTE[buffer_size];
	if(!buffer_pointer) {
		MessageBox("Out of memory.\nTry to close a few programs and try again.");
		return FALSE;
	}

	// Just to start the loop
	rv = 1;
	bytes_read = 1;
	while(rv && bytes_read > 0) {
		// Continue to read
		rv = ::ReadEventLog(eventlog, 
			EVENTLOG_SEQUENTIAL_READ|EVENTLOG_FORWARDS_READ, 0, buffer_pointer,
			buffer_size, &bytes_read, &buffer_size_required);

		if(!rv) {
			DWORD error;
			LPTSTR string;
			error = GetLastError();
			if(ERROR_HANDLE_EOF == error) {
				break;
			}

			FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_IGNORE_INSERTS|FORMAT_MESSAGE_FROM_SYSTEM,
					NULL,error,0,(LPTSTR) &string,0,NULL);
			::MessageBox(NULL, string, NULL, MB_OK);
			LocalFree(string);
		} else {
			PEVENTLOGRECORD el = (PEVENTLOGRECORD) buffer_pointer;
			while((char *)el<((char *)buffer_pointer+bytes_read)) {
				ProcessSecurityRecord(el);
				el = (PEVENTLOGRECORD)(((char *)el) + el->Length);
			}

		}

	}

	CloseEventLog(eventlog);
	eventlog = NULL;

	delete buffer_pointer;
	buffer_pointer = NULL;

	return TRUE;

}

void CLoginViewerDlg::SetAllSubItems()
{
	int count;
	DWORD param;
	CUserVisit *uv;
	CString timestr;

	count = m_listctrl.GetItemCount();

	for(int i=0; i<count; i++) {
		param = m_listctrl.GetItemData(i);
		uv = reinterpret_cast<CUserVisit *>(param);

		if(uv->HasLoginTime()) {
			m_listctrl.SetItemText(i,LOGINTIME, 
				uv->GetLoginTime().Format("%Y-%m-%d %H:%M:%S"));
		} else {
			m_listctrl.SetItemText(i,LOGINTIME, "<not logged>");
		}

		if(uv->HasLogoutTime()) {
			m_listctrl.SetItemText(i,LOGOUTTIME, 
				uv->GetLogoutTime().Format("%Y-%m-%d %H:%M:%S"));
		} else if(uv->HasDefinitelyOutBy()){
			CString prefix("before ");
			CString timestr;
			CTime outby;
			outby = uv->GetDefinitelyOutBy();
			timestr = prefix + outby.Format("%Y-%m-%d %H:%M:%S");
			m_listctrl.SetItemText(i,LOGOUTTIME, timestr);
		} else {
			// Display nothing
			m_listctrl.SetItemText(i,LOGOUTTIME, "");
//			m_listctrl.SetItemText(i,LOGOUTTIME, "<not logged>");
		}

		if(uv->HasLoggedinTime()) {
			m_listctrl.SetItemText(i,INTIME, 
				uv->GetLoggedinTime().Format("%D days, %H:%M:%S"));
		} else if(uv->HasDefinitelyOutBy() && uv->HasLoginTime()) {
			CTimeSpan ts;
			ts = uv->GetDefinitelyOutBy() - uv->GetLoginTime();
			CString prefix("less than ");
			CString timestr;
			timestr = prefix + ts.Format("%D days, %H:%M:%S");
			m_listctrl.SetItemText(i,INTIME, timestr);
		} else {
			m_listctrl.SetItemText(i,INTIME, "<still logged in>");
		}

	} // for

}

void CLoginViewerDlg::OnColumnclickLoginlist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	switch(pNMListView->iSubItem) {
	case USER:
	case LOGINTIME:
	case LOGOUTTIME:
	case INTIME:
		m_listctrl.SortItems(CompareUserVisit, pNMListView->iSubItem);
		break;
	default:
		TRACE("Unknown column");
	}

	*pResult = 0;
}

// Sort the item in reverse alphabetical order.
int CALLBACK 
CLoginViewerDlg::CompareUserVisit(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{

	CUserVisit *uv1,*uv2;
	uv1 = reinterpret_cast<CUserVisit *>(lParam1);
	uv2 = reinterpret_cast<CUserVisit *>(lParam2);

	switch(lParamSort) {
	case USER:
		return uv1->GetName().Compare(uv2->GetName());
	case LOGINTIME:
		if(uv1->HasLoginTime()) {
			if(uv2->HasLoginTime()) {
				if(uv1->GetLoginTime()<uv2->GetLoginTime()) {
					return -1;
				} else if(uv1->GetLoginTime()>uv2->GetLoginTime()) {
					return 1;
				} else {
					// Equal
					return 0;
				}
			} else {
				return 1;
			}
		} else if(uv2->HasLoginTime()) {
			return -1;
		} else {
			return 0;
		}
		break;
	case LOGOUTTIME:
		// Note that if a logout time is specified, than there is also a
		// "definitely out by" time.
		if(uv1->HasDefinitelyOutBy() && uv2->HasDefinitelyOutBy()) {
				if(uv1->GetDefinitelyOutBy()<uv2->GetDefinitelyOutBy()) {
					return -1;
				} else if(uv1->GetDefinitelyOutBy()>uv2->GetDefinitelyOutBy()) {
					return 1;
				} else {
					// Equal shutdowns/startups
					return 0;
				}
		} else if(uv1->HasDefinitelyOutBy()) {
			// a uv1 time but no uv2 time
			// let's the one without time come after all others.
			return -1;
		} else if(uv2->HasDefinitelyOutBy()) {
			return 1;
		} else {
			return 0;
		}
		
		break;
	case INTIME:
		if(uv1->HasLoggedinTime() ||
			(uv1->HasLoginTime() && uv1->HasDefinitelyOutBy())) {
			// We can create a uv1 time
			CTimeSpan uv1time;
			if(uv1->HasLoggedinTime()) {
				uv1time = uv1->GetLoggedinTime();
			} else {
				uv1time = uv1->GetDefinitelyOutBy()-uv1->GetLoginTime();
			}
			if(uv2->HasLoggedinTime() ||
				(uv2->HasLoginTime() && uv2->HasDefinitelyOutBy())) {
				// We can create a uv2 time
				CTimeSpan uv2time;
				if(uv2->HasLoggedinTime()) {
					uv2time = uv2->GetLoggedinTime();
				} else {
					uv2time = uv2->GetDefinitelyOutBy()-uv2->GetLoginTime();
				}

				if(uv1time<uv2time) {
					return -1;
				} else if(uv1time>uv2time) {
					return 1;
				} else {
					// Equal
					return 0;
				}
			} else {
				// Has a uv1time but no uv2time
				return 1;
			}
		} else if(uv2->HasLoggedinTime() ||
				(uv2->HasLoginTime() && uv2->HasDefinitelyOutBy())) {
				// We can create a uv2 time but have no uv1time
			return -1;
		} else {
			// no times at all
			return 0;
		}
		break;
	default:
		TRACE("Unknown column");
	}

	return 0;
}

void CLoginViewerDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	TRACE("Should set size of parts of the dialog.\n");

	// TODO: Add your message handler code here
	
}


/**
 * Returns TRUE if it succeeded
 */
BOOL CLoginViewerDlg::ReadStartupShutdownLog()
{
	BOOL rv;
	DWORD bytes_read, buffer_size_required;
	HANDLE eventlog;
	LPVOID buffer_pointer;
	DWORD buffer_size = 4*1024; // 4 KB

	eventlog = OpenEventLog(NULL, "System");

	if(!eventlog) {
		MessageBox("Couldn't open the system event log.\nIt is in the system eventlog that logs startups and shutdowns. Do you have the rights to read that log?");
		return FALSE;
	}

	// Get a buffer
	buffer_pointer = new BYTE[buffer_size];
	if(!buffer_pointer) {
		MessageBox("Out of memory.\nTry to close a few programs and try again.");
		return FALSE;
	}

	// Just to start the loop
	rv = 1;
	bytes_read = 1;
	while(rv && bytes_read > 0) {
		// Continue to read
		rv = ::ReadEventLog(eventlog, 
			EVENTLOG_SEQUENTIAL_READ|EVENTLOG_FORWARDS_READ, 0, buffer_pointer,
			buffer_size, &bytes_read, &buffer_size_required);

		if(!rv) {
			DWORD error;
			LPTSTR string;
			error = GetLastError();
			if(ERROR_HANDLE_EOF == error) {
				break;
			}

			FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_IGNORE_INSERTS|FORMAT_MESSAGE_FROM_SYSTEM,
					NULL,error,0,(LPTSTR) &string,0,NULL);
			::MessageBox(NULL, string, NULL, MB_OK);
			LocalFree(string);
		} else {
			PEVENTLOGRECORD el = (PEVENTLOGRECORD) buffer_pointer;
			while((char *)el<((char *)buffer_pointer+bytes_read)) {
				ProcessSystemRecord(el);
				el = (PEVENTLOGRECORD)(((char *)el) + el->Length);
			}

		}

	}

	CloseEventLog(eventlog);
	eventlog = NULL;

	delete buffer_pointer;
	buffer_pointer = NULL;

	return TRUE;

}



void CLoginViewerDlg::ProcessSystemRecord(PEVENTLOGRECORD el)
{
	PTCHAR sourcename;
	CStartup *startup;
	CShutdown *shutdown;

	// Definition of event types?
	// Definition of event ids?

	if(el->EventType != EVENTLOG_INFORMATION_TYPE) {
		// Nothing for us
		return;
	}

	// A successful audit.

	// Check if source is "EventLog"
	sourcename = ((char *)&el->DataOffset) + sizeof(el->DataOffset);
	if(strcmp(sourcename, "EventLog")) {
		// Nope, nothing for us
		return;
	}

//	TRACE("Eventlog, tjoho\n");
	
	DWORD eventid = el->EventID & 0x7FFF;

	// Check EventID
	switch(eventid) {
	case 6005:
		// Eventlog started
		startup = new CStartup();
//		ASSERT(el->TimeGenerated>0);
//		startup->SetTime(el->TimeGenerated);
		startup->SetTime(el->TimeWritten);
		m_startuplist.AddTail(startup);
		break;
	case 6006:
		shutdown = new CShutdown();
//		ASSERT(el->TimeGenerated>0);
//		shutdown->SetTime(el->TimeGenerated);
		shutdown->SetTime(el->TimeWritten);
		m_shutdownlist.AddTail(shutdown);
		// Eventlog shutdown
		break;
	default: ;// nothing
	}

}

void CLoginViewerDlg::CleanLists()
{
	CLoginLogout *ll;
	while(!m_loglist.IsEmpty()) {
		ll = m_loglist.RemoveHead();
		delete ll;
	}

	CUserVisit *uv;
	while(!m_visitlist.IsEmpty()) {
		uv = m_visitlist.RemoveHead();
		delete uv;
	}

	CStartup *st;
	while(!m_startuplist.IsEmpty()) {
		st = m_startuplist.RemoveHead();
		delete st;
	}

	CShutdown *sh;
	while(!m_shutdownlist.IsEmpty()) {
		sh = m_shutdownlist.RemoveHead();
		delete sh;
	}


}
