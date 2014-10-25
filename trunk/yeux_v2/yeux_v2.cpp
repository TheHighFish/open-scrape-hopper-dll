// yeux_v2.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "yeux_v2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CWinApp theApp;

// The one and only application object

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;
	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		MessageBoxA(NULL, "ERROR", "MFC initialization failed", MB_OK | MB_ICONERROR);
		_tprintf(_T("Fatal Error: MFC initialization failed\n"));
		nRetCode = 1;
	}
	else
	{
		// TODO: code your application's behavior here.
	}

	return nRetCode;
}


CLobbyScraper::CLobbyScraper()
{
}

CLobbyScraper::~CLobbyScraper()
{
}

bool CLobbyScraper::Load(CString filename)
{
  p_tablemap = new CTablemap();
	int line = 0;
	int ret = p_tablemap->LoadTablemap(filename, VER_OPENSCRAPE_2, false, &line, false);
	
	if (ret != SUCCESS)
	{
		MessageBox(NULL,"ERROR", "Hopper C++ : ERROR Loading tablemap", MB_OK | MB_ICONERROR);


		return false;
	}

	return true;
}

void CLobbyScraper::GetRegionPos(const CString name, int& posl, int& post, int& posr, int& posb) 
{																		
	posl = post = posr = posb= -1;
	RMapCI r_it = p_tablemap->r$()->find(name);
	if (r_it == p_tablemap->r$()->end())
		return;
	posl = r_it->second.left;
	post = r_it->second.top;
	posr = r_it->second.right;
	posb = r_it->second.bottom;

}


bool CLobbyScraper::GetSymbol(const CString name, CString& text) 
{
	SMapCI it = p_tablemap->s$()->find(name);
	if (it == p_tablemap->s$()->end())
		return false;
	text = it->second.text;
	return true;
}




bool CLobbyScraper::ReadRegion(HWND hwnd, const CString name, char* &result, int ofsx, int ofsy) 
{
	RMapCI r_it = p_tablemap->r$()->find(name.GetString());
	
	if (r_it == p_tablemap->r$()->end())
		return false;
	
	STablemapRegion region = r_it->second;

	HDC WinDC= GetDC (hwnd);
	HDC CopyDC= CreateCompatibleDC (WinDC);
	HBITMAP subBmp;
	RECT rt = {region.left,region.top + ofsy,region.right,region.bottom + ofsy};
	
	 //Create a bitmap compatible with the DC
	subBmp = CreateCompatibleBitmap (WinDC,
 	rt.right - rt.left+1, //width
 	rt.bottom - rt.top+1);//height
 
	//Associate the bitmap with the DC
	SelectObject (CopyDC, subBmp);
 
	//Copy the window DC to the compatible DC
	BitBlt (CopyDC,   //destination
 	0,0,
 	rt.right - rt.left+1, //width
 	rt.bottom - rt.top+1, //height
 	WinDC,    //source
 	rt.left,rt.top,
 	SRCCOPY);

 	CTransform trans;
	HBITMAP oldbmp=(HBITMAP) SelectObject(CopyDC, subBmp);
	CString text;
	CString separation;
	COLORREF			cr_avg;

	int ret = trans.DoTransform(r_it, CopyDC, &text, &separation, &cr_avg);
	
	strcpy_s(result,256,text);
	//We don`t need the DCs anymore
	ReleaseDC(hwnd, WinDC);
  ReleaseDC(hwnd, CopyDC);
   
  DeleteDC(WinDC);
  DeleteDC(CopyDC);
  DeleteObject(subBmp);
  //DeleteObject(bmp);

	return ret!=-4;
}


//////////// Les appels possible de l'extérieur : 
CLobbyScraper	scraper;

YEUX_V2_API int OpenTablemap(char* filename)
{
	return scraper.Load((CString)filename);
}

YEUX_V2_API int ReadRegion(HWND hwnd, char* name, char* &result, int offset)
{
	
	//char* res;
	if (!scraper.ReadRegion(hwnd, (CString)name, result, 0, offset))
		return 0;
	return 1;
}

YEUX_V2_API void GetRegionPos(char* name, int& posleft, int& postop, int& posright, int& posbottom)
{
	scraper.GetRegionPos(name, posleft, postop, posright, posbottom);
}

