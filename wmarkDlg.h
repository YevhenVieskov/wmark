
// wmarkDlg.h : ���� ���������
//

#pragma once
#include "afxwin.h"


// ���������� ���� CwmarkDlg
class CwmarkDlg : public CDialogEx
{
// ��������
public:
	CwmarkDlg(CWnd* pParent = NULL);	// ����������� �����������

// ������ ����������� ����
	enum { IDD = IDD_WMARK_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// ��������� DDX/DDV


// ����������
protected:
	HICON m_hIcon;

	// ��������� ������� ����� ���������
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnEnChangeEditEsmsg();
	afx_msg void OnEnChangeEditEpath();
	afx_msg void OnBnClickedButtonEmbed();
	afx_msg void OnEnChangeEditDpath();
	afx_msg void OnEnChangeEditDmsg();
	afx_msg void OnBnClickedButtonDecrypt();
	// secret message
	CEdit m_esmsg;
	// path to graphical file
	CEdit m_epath;
	// path to watermarked image
	CEdit m_dpath;
	// decripted image
	CEdit m_dmsg;
	afx_msg void OnBnClickedButtonRandom();
	afx_msg void OnBnClickedCheckRandom();
	CButton m_check_random;
	void UpdateState();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButtonHelp();
	void DoEsmsgOp();
	void DoEpathOp();
	void DoEpathsOp();
	void DoDpathOp();
};
