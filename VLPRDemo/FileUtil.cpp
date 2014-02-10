

#include <windows.h>  
#include <ShlObj.h> 
#include <stdio.h>
#include <time.h>   
 

#include "FileUtil.h"


FileUtil::FileUtil(void)
{
}

FileUtil::~FileUtil(void)
{
}

/**
* 列出目录下的所有文件
* @Path : 目录
* @retList: 返回的文件列表
* @
* 
*/
/*
list<const char*> FileUtil::ListFiles(char *czPath, list<char*> listResult, bool bListDirectory, bool bListSub)
{
	char file[MAX_PATH];
	lstrcpy(file,czPath);
	lstrcat(file,"\\*.*"); 

	WIN32_FIND_DATA wfd; 
	HANDLE Find = FindFirstFile(file,&wfd); 
	if (Find == INVALID_HANDLE_VALUE)  
		return NULL;

	char szFindPath[MAX_PATH]={0};
	while (FindNextFile(Find, &wfd))
	{
		if (wfd.cFileName[0] == '.') 
		{
			continue;
		} 
		lstrcpy(szFindPath,czPath); 
		lstrcat(szFindPath,"\\"); 
		lstrcat(szFindPath,wfd.cFileName); 

		if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) 
		{
			if(bListDirectory)
				listResult.push_back( wfd.cFileName );
			if(bListSub)
				ListFiles(szFindPath, listResult, bListDirectory, bListSub);  
		}
		else
			listResult.push_back( wfd.cFileName );
	}
	FindClose(Find);

	return listResult;

}
*/



//选择文件夹 对话框
#ifndef BIF_NEWDIALOGSTYLE
#define BIF_NEWDIALOGSTYLE 0x0040
#endif
char* FileUtil::SelectFolder(HWND hwnd, char* title)
{
	char szFolder[MAX_PATH] = {0};		//得到文件路径			

	//HWND hwnd = hWnd->GetSafeHwnd();   //得到窗口句柄
#ifdef _SHGetMalloc_  
	LPMALLOC pMalloc;
	if (::SHGetMalloc(&pMalloc) == NOERROR)		//取得IMalloc分配器接口
	{   
		BROWSEINFO		bi;
		TCHAR			pszBuffer[MAX_PATH];
		LPITEMIDLIST	pidl;   

		bi.hwndOwner		= hwnd;
		bi.pidlRoot			= NULL;
		bi.pszDisplayName   = pszBuffer;
		bi.lpszTitle		= _T(title); //选择目录对话框的上部分的标题
		//添加新建文件夹按钮 BIF_NEWDIALOGSTYLE
		bi.ulFlags			=  BIF_NEWDIALOGSTYLE | BIF_RETURNONLYFSDIRS | BIF_RETURNFSANCESTORS;
		bi.lpfn				= NULL;
		bi.lParam			= 0;
		bi.iImage			= 0;
		if ((pidl = ::SHBrowseForFolder(&bi)) != NULL)  //取得IMalloc分配器接口
		{   
			if (::SHGetPathFromIDList(pidl, pszBuffer)) //获得一个文件系统路径
			{
				sprintf(szFolder, "%s",  pszBuffer);
			}
			else szFolder = '\0';
			pMalloc->Free(pidl);	//释放内存

			//	MessageBox(m_strPath);
		}
		pMalloc->Release();			//释放接口
	}
#else  
	BROWSEINFO bi;  
	ZeroMemory(&bi,sizeof(BROWSEINFO));  
	LPITEMIDLIST pidl=(LPITEMIDLIST)CoTaskMemAlloc(sizeof(LPITEMIDLIST));  
	pidl = SHBrowseForFolder(&bi);  
	TCHAR * path = new TCHAR[MAX_PATH];  
	if(pidl != NULL)  
	{  
		if(SHGetPathFromIDList(pidl,path))
			sprintf(szFolder, "%s",  path);
		//MessageBox(NULL,path,TEXT(title),MB_OK);  
	}  
	else 
	{  
		MessageBox(NULL,TEXT("EMPTY"),TEXT("Choose"),MB_OK);  
	}  
	CoTaskMemFree(pidl);  
	delete path;  
	return 0;  
#endif  

	return szFolder;
}


//判断文件/文件夹是否存在
//判断文件：	FindFirstFileExists(lpPath, FALSE);  
//判断文件夹：	FindFirstFileExists(lpPath, FILE_ATTRIBUTE_DIRECTORY);  
BOOL FindFirstFileExists(LPCTSTR lpPath, DWORD dwFilter)  
{  
	WIN32_FIND_DATA fd;  
	HANDLE hFind = FindFirstFile(lpPath, &fd);  
	BOOL bFilter = (FALSE == dwFilter) ? TRUE : fd.dwFileAttributes & dwFilter;  
	BOOL RetValue = ((hFind != INVALID_HANDLE_VALUE) && bFilter) ? TRUE : FALSE;  
	FindClose(hFind);  
	return RetValue;  
}  

char *GetDateTime(char *timeString)
{
	struct tm *tmt = 0;
	time_t t = time(0);
	tmt = localtime(&t);
	if(timeString==0)
		timeString = new char[32];
	memset(timeString, 0, 32);
	sprintf(timeString,"%4d-%02d-%02d  %02d:%02d:%02d", tmt->tm_year+1900, tmt->tm_mon+1, tmt->tm_mday, tmt->tm_hour, tmt->tm_min, tmt->tm_sec );
	return timeString;
}

void __cdecl debug(const char *format, ...)
{
	char buf[4096]={0}, *p=buf;
	
	char *t = GetDateTime();
	sprintf(p,"%s ",t);
	p += strlen(p);

    va_list args;
    va_start(args, format);
    p += _vsnprintf(p, sizeof buf - 1, format, args);
    va_end(args);
  // while ( p > buf && isspace(p[-1]) )    *--p = '\0';
    *p++ = '\r';
    *p++ = '\n';
    *p = '\0';

    OutputDebugString(buf);
}