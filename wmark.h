
// wmark.h : ������� ���� ��������� ��� ���������� PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�������� stdafx.h �� ��������� ����� ����� � PCH"
#endif

#include "resource.h"		// �������� �������


// CwmarkApp:
// � ���������� ������� ������ ��. wmark.cpp
//

class CwmarkApp : public CWinApp
{
public:
	CwmarkApp();

// ���������������
public:
	virtual BOOL InitInstance();

// ����������

	DECLARE_MESSAGE_MAP()
};

extern CwmarkApp theApp;