
// filedemoDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CfiledemoDlg �Ի���
class CfiledemoDlg : public CDialogEx
{
// ����
public:
	CfiledemoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_FILEDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnGetPath();
	CString m_editValue;
	CEdit m_editPath;
	//���PE�ṹ
	afx_msg void OnBnClickedBtnCheckPe();
};
