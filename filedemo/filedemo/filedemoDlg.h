
// filedemoDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CfiledemoDlg 对话框
class CfiledemoDlg : public CDialogEx
{
// 构造
public:
	CfiledemoDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_FILEDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnGetPath();
	CString m_editValue;
	CEdit m_editPath;
	//检查PE结构
	afx_msg void OnBnClickedBtnCheckPe();
};
