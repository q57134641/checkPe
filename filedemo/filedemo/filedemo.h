
// filedemo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CfiledemoApp: 
// �йش����ʵ�֣������ filedemo.cpp
//

class CfiledemoApp : public CWinApp
{
public:
	CfiledemoApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CfiledemoApp theApp;