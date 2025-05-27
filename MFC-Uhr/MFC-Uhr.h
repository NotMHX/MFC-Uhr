#pragma once

class CMFCUhrApp : public CWinApp
{
public:
	CMFCUhrApp();
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

extern CMFCUhrApp theApp;
