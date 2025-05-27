#include "pch.h"
#include "MFC-Uhr.h"
#include "HerrmannUhr/HerrmannUhr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CMFCUhrApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


CMFCUhrApp::CMFCUhrApp()
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// The one and only CMFCUhrApp object
CMFCUhrApp theApp;

// CMFCUhrApp initialization
BOOL CMFCUhrApp::InitInstance()
{
	__super::InitInstance();

	Messerli::HerrmannUhr::StartApp(NULL);
	return TRUE;
}
