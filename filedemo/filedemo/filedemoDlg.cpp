
// filedemoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "filedemo.h"
#include "filedemoDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CfiledemoDlg �Ի���



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


// CfiledemoDlg ��Ϣ�������

BOOL CfiledemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CfiledemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CfiledemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CfiledemoDlg::OnBnClickedBtnGetPath()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CFileDialog cFileDlg(TRUE);
	if (cFileDlg.DoModal() == IDOK)
	{
		m_editPath.SetWindowTextW(cFileDlg.GetPathName());
		UpdateData();
	}
}

void CfiledemoDlg::OnBnClickedBtnCheckPe()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (m_editValue.IsEmpty())
	{
		//��ûѡ���ļ�
		OnBnClickedBtnGetPath();
	}

	HANDLE hFile = INVALID_HANDLE_VALUE;
	do
	{
		hFile = CreateFile(m_editValue, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
		if (hFile == INVALID_HANDLE_VALUE)
			break;
		//IMAGE_DOS_HEADERֻ��Ҫ��ע2������
		//WORD   e_magic;                     // Magic number
		// LONG   e_lfanew;                    // File address of new exe header
		//����������Ϊ�˼���DOS����
		IMAGE_DOS_HEADER dosHeader;
		DWORD dwReadSize = 0;
		::ReadFile(hFile, &dosHeader, sizeof(IMAGE_DOS_HEADER), &dwReadSize, nullptr);
		if (dwReadSize != sizeof(IMAGE_DOS_HEADER))
			break;
		
		//==MZ���Ǻϸ��DOSͷ
		if (dosHeader.e_magic != IMAGE_DOS_SIGNATURE)
			break;

		//���Ӧ�ó�����64
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
