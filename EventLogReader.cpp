// EventLogReader.cpp: implementation of the CEventLogReader class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LoginViewer.h"
#include "EventLogReader.h"
#include "LoginLogout.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEventLogReader::CEventLogReader()
{

}

CEventLogReader::~CEventLogReader()
{

}

CTypedPtrList<CPtrList, CLoginLogout*> *CEventLogReader::ReadSecurityLog()
{
	BOOL rv;
	DWORD bytes_read, buffer_size_required;
	HANDLE eventlog;
	LPVOID buffer_pointer;
	DWORD buffer_size = 4*1024; // 4 KB

	CTypedPtrList<CPtrList, CLoginLogout*> *loglist = new CTypedPtrList<CPtrList, CLoginLogout*>();

	eventlog = OpenEventLog(NULL, "Security");

	if(!eventlog) {
		MessageBox(NULL, 
			"Couldn't open the security event log.\nIt is in the security eventlog that logins and logouts are recorded. Do you have the rights to read that log?",
			NULL,
			MB_OK);
		delete loglist;
		return NULL;
	}

	// Get a buffer
	buffer_pointer = new BYTE[buffer_size];
	if(!buffer_pointer) {
		MessageBox(NULL,
			"Out of memory.\nTry to close a few programs and try again.",
			NULL,
			MB_OK);
		delete loglist;
		return NULL;
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
				ProcessSecurityRecord(el,loglist);
				el = (PEVENTLOGRECORD)(((char *)el) + el->Length);
			}

		}

	}

	CloseEventLog(eventlog);
	eventlog = NULL;

	delete buffer_pointer;
	buffer_pointer = NULL;

	return loglist;
}



void CEventLogReader::ProcessSecurityRecord(PEVENTLOGRECORD el,CTypedPtrList<CPtrList, CLoginLogout*> *loglist)
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
		loglist->AddTail(ll);
		break;
	case 538:
		// Logoff
		ASSERT(el->NumStrings>=3);
		ASSERT(el->TimeGenerated>0);
		ll = new CLoginLogout(EVENTLOG_LOGOUT, el->TimeGenerated,logstrings[2]);
		user = logstrings[0];
		ll->SetUserName(user);
		loglist->AddTail(ll);
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
		loglist->AddTail(ll);
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
