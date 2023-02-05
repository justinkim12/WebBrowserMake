
// MFCApplication3Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication3.h"
#include "MFCApplication3Dlg.h"
#include "afxdialogex.h"
#define _WINDSOCK_DEPRECATED_NO_WARNINGS
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <string.h>
#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <vector>
#include <locale>
#include <sstream>
#include <fstream>
#include <ShlObj.h>
#include <MsHTML.h>


using namespace std;
#pragma comment(lib,"ws2_32.lib")
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication3Dlg 대화 상자



CMFCApplication3Dlg::CMFCApplication3Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION3_DIALOG, pParent)
	, url1(_T(""))
	, html1(_T(""))
	, req(_T(""))
	, res(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXPLORER1, browser);

	DDX_Control(pDX, IDC_EDIT1, url_in);
	DDX_Control(pDX, IDC_EDIT2, html_out);
	DDX_Text(pDX, IDC_EDIT1, url1);
	DDX_Text(pDX, IDC_EDIT2, html1);
	DDX_Text(pDX, IDC_EDIT3, req);
	DDX_Text(pDX, IDC_EDIT4, res);
}

BEGIN_MESSAGE_MAP(CMFCApplication3Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT1, &CMFCApplication3Dlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplication3Dlg::OnBnClickedButton2)
	ON_EN_CHANGE(IDC_EDIT2, &CMFCApplication3Dlg::OnEnChangeEdit2)

END_MESSAGE_MAP()


// CMFCApplication3Dlg 메시지 처리기

BOOL CMFCApplication3Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCApplication3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCApplication3Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCApplication3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication3Dlg::OnEnChangeEdit1()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMFCApplication3Dlg::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//	CString strText = _T("");//문자열 저장용 변수
//	url_in.GetWindowTextW(strText);//입력되는 문자열 저장
	UpdateData(true);
	WSADATA wsaData;
	SOCKET Socket;
	SOCKADDR_IN SockAddr;
	int lineCount = 0;
	int rowCount = 0;
	struct hostent *host;
	locale local;
	char buffer[10000];
	int i = 0;
	int nDataLength;
	string website_HTML;
	string response;
	string url_ = string(CW2A(url1));
	string query_url;
	string host_url;
	CComVariant var((url_).c_str());

	if (url_.find("/") != string::npos) { //host 부분 query 부분 나눠서 함
		host_url = url_.substr(0, url_.find('/'));//hostname 부분에 넣을것
		query_url = url_.substr(url_.find('/')); //request 메세지 부분에 넣을것
	}
	else {// query 부분이 없는 경우
		host_url = url_;
		query_url = '/';

	}
	string get_http = "GET " + query_url + " HTTP/1.1\r\nHost: " + host_url + "\r\nConnection: close\r\n\r\n";
	//request 메세지 작성

	req=get_http.c_str();//request message update

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {//윈도우 소켓 초기화
		cout << "WSAStartup failed.\n";
		system("pause");
		//return 1;
	}

	Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //주소체계, 소켓 타입(stream socket), TCP 설정
	host = gethostbyname(host_url.c_str()); //호스트 네임 알아내기

	SockAddr.sin_port = htons(80);//포트 번호
	SockAddr.sin_family = AF_INET; //소켓이 사용하는 주소 체계(IP v4 주소) 
	SockAddr.sin_addr.s_addr = *((unsigned long*)host->h_addr); 

	if (connect(Socket, (SOCKADDR*)(&SockAddr), sizeof(SockAddr)) != 0) {
		cout << "Could not connect";
		system("pause");
		//return 1;
	}

	// send GET / HTTP
	send(Socket, get_http.c_str(), strlen(get_http.c_str()), 0);
	//메세지 보내기

	// recieve html
	int data_switch = 0;
	while ((nDataLength = recv(Socket, buffer, 10000, 0)) > 0) {
		int i = 0;
		while (buffer[i] >= 32 || buffer[i] == '\n' || buffer[i] == '\r') {
			if (buffer[i] == '<')
				data_switch = 1;
			if (data_switch == 1)
				website_HTML += buffer[i];//html 부분 가져오기
			else
				response += buffer[i];//response message 가져오기
			i += 1;
		}
	}
	res = response.c_str();//Response message 출력
	closesocket(Socket);
	WSACleanup();

	LPCTSTR website = (LPCTSTR)(website_HTML.c_str());
	html1 = website_HTML.c_str();//html update
	UpdateData(false);

	string OK = response.substr(9, 3);
	string OKcheck = "200";// ok 200 받은 경우
	if (OK.compare(OKcheck) == 0)
	{
		
		browser.Navigate2(&var, NULL, NULL, NULL, NULL);//창 띄우기
	}

	
}


void CMFCApplication3Dlg::OnEnChangeEdit2()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMFCApplication3Dlg::OnEnChangeEdit3()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
