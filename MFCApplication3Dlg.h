﻿
// MFCApplication3Dlg.h: 헤더 파일
//

#pragma once
#include "CWebBrowser2.h"


// CMFCApplication3Dlg 대화 상자
class CMFCApplication3Dlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCApplication3Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION3_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CWebBrowser2 browser;
	CButton go;
	afx_msg void OnEnChangeEdit1();
	CEdit url_in;
	CEdit html_out;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit3();
	CString url1;
	CString html1;
	CString req;
	CString res;
};
