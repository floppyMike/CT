#pragma once

#include <afxwin.h>
#include "resource.h"

// Window dialog

class Window : public CDialog
{
	DECLARE_DYNAMIC(Window)

public:
	Window(CWnd* pParent = nullptr);   // standard constructor
	virtual ~Window();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOGBAR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
