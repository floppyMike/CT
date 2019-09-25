// Window.cpp : implementation file
//

#include "Window.h"
#include "afxdialogex.h"


// Window dialog

IMPLEMENT_DYNAMIC(Window, CDialog)

Window::Window(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOGBAR)
{
	//Create(nullptr, "Ampel");
}

Window::~Window()
{
}

void Window::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Window, CDialog)
END_MESSAGE_MAP()


// Window message handlers
