
// VLPRDemo.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "VLPRDemo.h"
#include "VLPRDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "SkinPPWTL.h"
#pragma comment(lib, "SkinPPWTL.lib")

CVLPRDemoApp theApp;


// CVLPRDemoApp

BEGIN_MESSAGE_MAP(CVLPRDemoApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CVLPRDemoApp 构造

CVLPRDemoApp::CVLPRDemoApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CVLPRDemoApp 对象



// CVLPRDemoApp 初始化

CString CVLPRDemoApp::m_appPath="";

BOOL CVLPRDemoApp::InitInstance()
{
//	skinppLoadSkin(_T("skin/AquaOS.ssk"));
//	skinppLoadSkin(_T(""));

	CString g_szOcxPath = this->m_pszHelpFilePath;
	CString g_szOcxName = this->m_pszExeName;

	g_szOcxName += ".HLP";
	int nTmp = g_szOcxName.GetLength();
	nTmp = g_szOcxPath.GetLength() - nTmp;
	g_szOcxPath = g_szOcxPath.Left(nTmp-1);

	m_appPath = g_szOcxPath;


	//初始化GDI+.
	GdiplusStartup(&m_pGdiToken, &m_gdiplusStartupInput, NULL);

	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	CVLPRDemoDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}

int CVLPRDemoApp::ExitInstance()
{
	skinppExitSkin(); 

	return CWinAppEx::ExitInstance();
}
