// ClassFactory.h: interface for the CClassFactory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLASSFACTORY_H__3B4B8B30_5B16_4B69_ACC8_25C7259A9F74__INCLUDED_)
#define AFX_CLASSFACTORY_H__3B4B8B30_5B16_4B69_ACC8_25C7259A9F74__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

extern HINSTANCE  g_hInst;
extern UINT       g_DllRefCount;

class CClassFactory : public IClassFactory  
{
protected:
	DWORD m_ObjRefCount;
public:
	CClassFactory();
	virtual ~CClassFactory();

   //IUnknown methods
   STDMETHODIMP QueryInterface(REFIID, LPVOID*);
   STDMETHODIMP_(DWORD) AddRef();
   STDMETHODIMP_(DWORD) Release();

   //IClassFactory methods
   STDMETHODIMP CreateInstance(LPUNKNOWN, REFIID, LPVOID*);
   STDMETHODIMP LockServer(BOOL) { return E_NOTIMPL; };
};

#endif // !defined(AFX_CLASSFACTORY_H__3B4B8B30_5B16_4B69_ACC8_25C7259A9F74__INCLUDED_)
