// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the YEUX_V2_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// YEUX_V2_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.

#ifdef YEUX_V2_EXPORTS
#define YEUX_V2_API __declspec(dllexport)
#else
#define YEUX_V2_API __declspec(dllimport)
#endif

extern "C"
{
YEUX_V2_API int fnyeux_v2(void);
YEUX_V2_API int OpenTablemap(char* filename);
YEUX_V2_API int ReadRegion(HWND hwnd,char* name, char* & result, int offset);
YEUX_V2_API void GetRegionPos(char* name, int& posleft, int& postop, int& posright, int& posbottom);

}
class CLobbyScraper
{
public: 
	char* ScrapeResult;
public:
	CLobbyScraper();
	~CLobbyScraper();
	bool Load(CString filename);
  void UnloadTableMap();
	bool GetSymbol(const CString name, CString& text) ;
	bool ProcessRegion(RMapCI r_iter);
	bool ReadRegion(HWND hwnd, const CString name, char* & result, int ofsx=0, int ofsy=0) ;
	void GetRegionPos(const CString name, int& posl, int& post, int& posr, int& posb) ;
};