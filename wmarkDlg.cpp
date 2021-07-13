
// wmarkDlg.cpp : файл реализации
//

#include "stdafx.h"
#include "wmark.h"
#include "wmarkDlg.h"
#include "afxdialogex.h"
#include<locale>
#include<codecvt>
#include<string>
#include<cstdlib>
#include<afx.h>
#include<afxstr.h>
#include"stegokoch.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CString SecretMessage, EmPath, EmPathS, DecryptMessage, DcPath;
// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// диалоговое окно CwmarkDlg



CwmarkDlg::CwmarkDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CwmarkDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
}

void CwmarkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_ESMSG, m_esmsg);
	DDX_Control(pDX, IDC_EDIT_EPATH, m_epath);
	DDX_Control(pDX, IDC_EDIT_DPATH, m_dpath);
	DDX_Control(pDX, IDC_EDIT_DMSG, m_dmsg);
	DDX_Control(pDX, IDC_CHECK_RANDOM, m_check_random);
}

BEGIN_MESSAGE_MAP(CwmarkDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()	
	ON_EN_CHANGE(IDC_EDIT_ESMSG, &CwmarkDlg::OnEnChangeEditEsmsg)
	ON_EN_CHANGE(IDC_EDIT_EPATH, &CwmarkDlg::OnEnChangeEditEpath)
	ON_BN_CLICKED(IDC_BUTTON_EMBED, &CwmarkDlg::OnBnClickedButtonEmbed)
	ON_EN_CHANGE(IDC_EDIT_DPATH, &CwmarkDlg::OnEnChangeEditDpath)
	ON_EN_CHANGE(IDC_EDIT_DMSG, &CwmarkDlg::OnEnChangeEditDmsg)
	ON_BN_CLICKED(IDC_BUTTON_DECRYPT, &CwmarkDlg::OnBnClickedButtonDecrypt)
	
	ON_BN_CLICKED(IDC_CHECK_RANDOM, &CwmarkDlg::OnBnClickedCheckRandom)
	
	ON_BN_CLICKED(IDC_BUTTON_HELP, &CwmarkDlg::OnBnClickedButtonHelp)
END_MESSAGE_MAP()


// обработчики сообщений CwmarkDlg

BOOL CwmarkDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	UpdateState();
	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CwmarkDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CwmarkDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CwmarkDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}





void CwmarkDlg::OnEnChangeEditEsmsg()
{
	// TODO:  Если это элемент управления RICHEDIT, то элемент управления не будет
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Добавьте код элемента управления
	//CString SecretMessage, EmPath, DecryptMessage, DcPath;
	//GetWindowTextW(SecretMessage);
	//if (m_check_random) m_esmsg.EnableWindow(false);
	
}


void CwmarkDlg::OnEnChangeEditEpath()
{
	// TODO:  Если это элемент управления RICHEDIT, то элемент управления не будет
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Добавьте код элемента управления
	//CString SecretMessage, EmPath,EmPathS, DecryptMessage, DcPath;
}


void CwmarkDlg::OnBnClickedButtonEmbed()
{
	// TODO: добавьте свой код обработчика уведомлений
	//CString SecretMessage, EmPath, DecryptMessage, DcPath;
	//GetWindowText(IDC_EDIT_ESMSG, SecretMessage,250);
	//GetWindowTextW(SecretMessage);

	if (m_check_random.GetCheck() == BST_CHECKED)
	{

		std::vector<std::string> letters;

		letters.push_back("q");
		letters.push_back("w");
		letters.push_back("e");
		letters.push_back("r");
		letters.push_back("t");
		letters.push_back("y");
		letters.push_back("u");
		letters.push_back("i");
		letters.push_back("o");
		letters.push_back("p");
		letters.push_back("a");
		letters.push_back("s");
		letters.push_back("d");
		letters.push_back("f");
		letters.push_back("g");
		letters.push_back("h");
		letters.push_back("j");
		letters.push_back("k");
		letters.push_back("l");
		letters.push_back("z");
		letters.push_back("x");
		letters.push_back("c");
		letters.push_back("v");
		letters.push_back("b");
		letters.push_back("n");
		letters.push_back("m");
		letters.push_back("0");
		letters.push_back("1");
		letters.push_back("2");
		letters.push_back("3");
		letters.push_back("4");
		letters.push_back("5");
		letters.push_back("6");
		letters.push_back("7");
		letters.push_back("8");
		letters.push_back("9");

		int genRnd = rand() % letters.size();
		std::string res = "";
		for (int i = 0; i < letters.size(); ++i)
		{
			genRnd = rand() % letters.size();
			res += letters[genRnd];
		}

		char smsg[256]; 
		size_t lens = res.copy(smsg, res.size());
		if (lens > 0u)
			smsg[lens] = '\0';
		
		
		GetDlgItemText(IDC_EDIT_EPATH, EmPath);
		GetDlgItemText(IDC_EDIT_EPATHS, EmPathS);		
		const wchar_t* wfiname = EmPath.GetString();
		const wchar_t* wfsname = EmPathS.GetString();
		//const WCHAR* smsg = SecretMessage.GetString();
		char  finame[256], fsname[256];
		
		size_t len2 = wcstombs(finame, wfiname, wcslen(wfiname));
		if (len2 > 0u)
			finame[len2] = '\0';
		size_t len3 = wcstombs(fsname, wfsname, wcslen(wfsname));
		if (len3 > 0u)
			fsname[len3] = '\0';
		StegoKoch steg(finame, fsname, smsg);

	}		
	else
	{
		GetDlgItemText(IDC_EDIT_ESMSG, SecretMessage);
		GetDlgItemText(IDC_EDIT_EPATH, EmPath);
		GetDlgItemText(IDC_EDIT_EPATHS, EmPathS);


		const wchar_t* wsmsg = SecretMessage.GetString();
		const wchar_t* wfiname = EmPath.GetString();
		const wchar_t* wfsname = EmPathS.GetString();
		//const WCHAR* smsg = SecretMessage.GetString();
		char smsg[256], finame[256], fsname[256];
		size_t len1 = wcstombs(smsg, wsmsg, wcslen(wsmsg));
		if (len1 > 0u)
			smsg[len1] = '\0';
		size_t len2 = wcstombs(finame, wfiname, wcslen(wfiname));
		if (len2 > 0u)
			finame[len2] = '\0';
		size_t len3 = wcstombs(fsname, wfsname, wcslen(wfsname));
		if (len3 > 0u)
			fsname[len3] = '\0';
		StegoKoch steg(finame, fsname, smsg);
	}

	
/*	try
	{
		// Execute some code that might throw an exception.
		DoEsmsgOp();
		DoEpathOp();
		DoEpathsOp();
		
		
		
	}
	catch (CUserException* e)
	{
		// Handle the out-of-memory exception here.
		e->Delete();
	}
	catch (CMemoryException* e)
	{
		// Handle the out-of-memory exception here.
		e->Delete();
	}
	catch (CFileException* e)
	{
		// Handle the file exceptions here.
		e->Delete();
	}
	catch (CException* e)
	{
		// Handle all other types of exceptions here.
		e->Delete();
	}*/
	
}


void CwmarkDlg::OnEnChangeEditDpath()
{
	// TODO:  Если это элемент управления RICHEDIT, то элемент управления не будет
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Добавьте код элемента управления
	//CString SecretMessage, EmPath, DecryptMessage, DcPath;
}


void CwmarkDlg::OnEnChangeEditDmsg()
{
	// TODO:  Если это элемент управления RICHEDIT, то элемент управления не будет
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Добавьте код элемента управления
	//CString SecretMessage, EmPath, DecryptMessage, DcPath;
}


void CwmarkDlg::OnBnClickedButtonDecrypt()
{
	// TODO: добавьте свой код обработчика уведомлений
	
	GetDlgItemText(IDC_EDIT_DPATH, DcPath);	

	const wchar_t* wfsname = DcPath.GetString();
	char fsname[256];
	
	size_t len = wcstombs(fsname, wfsname, wcslen(wfsname));
	if (len > 0u)
		fsname[len] = '\0';
	
	StegoKoch steg = StegoKoch(fsname);

	
	char chstr[256];
	size_t lens = steg.outMes_s.copy(chstr, steg.outMes_s.size());
	if (lens > 0u)
		chstr[lens] = '\0';
	CString cstr = CString(chstr);
	SetDlgItemText(IDC_EDIT_DMSG, cstr);

	/*try
	{
		// Execute some code that might throw an exception.
		
		DoDpathOp();
	}
	catch (CUserException* e)
	{
		// Handle the out-of-memory exception here.
		e->Delete();
	}
	catch (CMemoryException* e)
	{
		// Handle the out-of-memory exception here.
		e->Delete();
	}
	catch (CFileException* e)
	{
		// Handle the file exceptions here.
		e->Delete();
	}
	catch (CException* e)
	{
		// Handle all other types of exceptions here.
		e->Delete();
	}*/
	
}






void CwmarkDlg::OnBnClickedCheckRandom()
{
	// TODO: добавьте свой код обработчика уведомлений
	
	
	UpdateState();
	
}


void CwmarkDlg::UpdateState()
{
	m_esmsg.EnableWindow(!(m_check_random.GetCheck() == BST_CHECKED));
}


void CwmarkDlg::OnBnClickedButton5()
{
	// TODO: добавьте свой код обработчика уведомлений
}


void CwmarkDlg::OnBnClickedButtonHelp()
{
	// TODO: добавьте свой код обработчика уведомлений
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


void CwmarkDlg::DoEsmsgOp()
{
	AfxMessageBox(_T("Невiрне секретне повiдомлення"));
	AfxThrowUserException();
}


void CwmarkDlg::DoEpathOp()
{
	AfxMessageBox(_T("Невiрне i'мя вхiдного файлу"));
	AfxThrowUserException();
}


void CwmarkDlg::DoEpathsOp()
{
	AfxMessageBox(_T("Невiрне i'мя вихiдного файлу"));
	AfxThrowUserException();
}




void CwmarkDlg::DoDpathOp()
{
	AfxMessageBox(_T("Невiрне i'мя зашифрованого файлу"));
	AfxThrowUserException();
}
