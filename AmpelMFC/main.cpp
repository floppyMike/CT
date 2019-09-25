#include <afxwin.h>
#include "Window.h"

class App : public CWinApp
{
public:
	App();
	~App();

	BOOL InitInstance();

private:

};

App::App()
{
}

App::~App()
{
}

BOOL App::InitInstance()
{
	auto* win = new Window();
	m_pMainWnd = win;

	win->DoModal();
	/*m_pMainWnd->ShowWindow(SW_NORMAL);
	m_pMainWnd->UpdateWindow();*/

	return TRUE;
}


App a;