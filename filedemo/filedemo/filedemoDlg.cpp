
// filedemoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "filedemo.h"
#include "filedemoDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CfiledemoDlg 对话框



CfiledemoDlg::CfiledemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CfiledemoDlg::IDD, pParent)
	, m_editValue(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CfiledemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_FILE_PATH, m_editValue);
	DDX_Control(pDX, IDC_FILE_PATH, m_editPath);
}

BEGIN_MESSAGE_MAP(CfiledemoDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_GET_PATH, &CfiledemoDlg::OnBnClickedBtnGetPath)
	ON_BN_CLICKED(IDC_BTN_CHECK_PE, &CfiledemoDlg::OnBnClickedBtnCheckPe)
END_MESSAGE_MAP()


// CfiledemoDlg 消息处理程序

BOOL CfiledemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CfiledemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CfiledemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CfiledemoDlg::OnBnClickedBtnGetPath()
{
	// TODO:  在此添加控件通知处理程序代码
	CFileDialog cFileDlg(TRUE);
	if (cFileDlg.DoModal() == IDOK)
	{
		m_editPath.SetWindowTextW(cFileDlg.GetPathName());
		UpdateData();
	}
}

void CfiledemoDlg::OnBnClickedBtnCheckPe()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_editValue.IsEmpty())
	{
		//还没选中文件
		OnBnClickedBtnGetPath();
	}

	HANDLE hFile = INVALID_HANDLE_VALUE;
	do
	{
		hFile = CreateFile(m_editValue, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
		if (hFile == INVALID_HANDLE_VALUE)
			break;
		//IMAGE_DOS_HEADER只需要关注2个变量
		//WORD   e_magic;                     // Magic number
		// LONG   e_lfanew;                    // File address of new exe header
		//其他变量是为了兼容DOS程序
		IMAGE_DOS_HEADER dosHeader;
		DWORD dwReadSize = 0;
		::ReadFile(hFile, &dosHeader, sizeof(IMAGE_DOS_HEADER), &dwReadSize, nullptr);
		if (dwReadSize != sizeof(IMAGE_DOS_HEADER))
			break;
		
		//==MZ才是合格的DOS头
		if (dosHeader.e_magic != IMAGE_DOS_SIGNATURE)
			break;

		//如果应用程序用64
		IMAGE_NT_HEADERS32 ntHeader;
		if (SetFilePointer(hFile, dosHeader.e_lfanew, nullptr, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
			break;

		::ReadFile(hFile, &ntHeader, sizeof(IMAGE_NT_HEADERS32), &dwReadSize,nullptr);
		if (dwReadSize != sizeof(IMAGE_NT_HEADERS32))
			break;
		
		if (ntHeader.Signature != IMAGE_NT_SIGNATURE)
			break;

		MessageBoxW(L"Is PE");

	} while (false);

	if (hFile != INVALID_HANDLE_VALUE)
		CloseHandle(hFile);
}
