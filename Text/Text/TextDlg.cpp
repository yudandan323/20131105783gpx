




// TextDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Text.h"
#include "TextDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CTextDlg 对话框




CTextDlg::CTextDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTextDlg::IDD, pParent)
	, m_list(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTextDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_list);
}

BEGIN_MESSAGE_MAP(CTextDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_Read, &CTextDlg::OnBnClickedRead)
	ON_BN_CLICKED(IDC_Write, &CTextDlg::OnBnClickedWrite)
	ON_BN_CLICKED(IDC_Draw, &CTextDlg::OnBnClickedDraw)
END_MESSAGE_MAP()


// CTextDlg 消息处理程序

BOOL CTextDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTextDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTextDlg::OnPaint()
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
HCURSOR CTextDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTextDlg::OnBnClickedRead()
{
	CFile myFile;
	if(myFile.Open(L"f:\\export.gpx",CFile::modeRead))
	{
		char *s;
		int l=myFile.GetLength ();
		s=new char[l+1];
		myFile.Read (s,l);
		s[l]='\0';
		m_list=s;
		myFile.Close ();
		MessageBox(L"读取成功");
		UpdateData(false);
	}
	else
	{
		MessageBox(L"无此文件");
	}
}


void CTextDlg::OnBnClickedWrite()
{
	char *tRead;
	CFile rFile(L"f:\\export.gpx",CFile::modeRead);
	int l = rFile.GetLength();
	tRead = new char[l+1];
	int r1 = rFile.Read(tRead,l);
	tRead[l] = '\0';
	CFile wFile;
	CFileException fileException;
	CString ofile=NULL;
	int loop = 0,i = 1;
	CString num,lat,lon,date,time,Enter=L"\r\n";
	ofile = tRead;
	wFile.Open(L"f:\\export.csv",CFile::modeWrite|CFile::modeCreate,&fileException);
	loop = ofile.Find(L"trkpt",0);
	while(loop <(l-30))
	{
		lat = ofile.Mid(loop+11,9);
		lon = ofile.Mid(loop+27,10);
		date = ofile.Mid(loop+50,10);
		time = ofile.Mid(loop+61,8);
		num.Format(L"%d",i);
		wFile .Write((char *)(_bstr_t)num,num.GetLength());
		wFile.Write(L",",1);
	    wFile .Write((char *)(_bstr_t)date,10);
		wFile.Write(L",",1);
		wFile .Write((char *)(_bstr_t)time,8);
		wFile.Write(L",",1);
		wFile .Write((char *)(_bstr_t)lat,9);
		wFile.Write(L",",1);
	    wFile .Write((char *)(_bstr_t)lon,10);
		wFile.Write(L",",1);
		wFile .Write((char *)(_bstr_t)Enter,Enter.GetLength());
		loop = loop+94;
		i++;
    }
	wFile.Flush();
	wFile.Close();
}


void CTextDlg::OnBnClickedDraw()
{
	CFile wfile;
	wfile.Open(L"f:\\export.gpx",CFile::modeRead);
	CFile Afile;
	Afile.Open(L"f:\\Gpxmap.html",CFile::modeCreate|CFile::modeReadWrite);
	CFile Bfile;
	Bfile.Open(L"f:\\Start.txt",CFile::modeRead);
	int l;
	l=Bfile.GetLength();
	char *Q;
	Q=new char[l+1];
	Q[l]='\0';
	Bfile.Read(Q,l);
	int i=1;
	int I;
	I=0;
	CString lat,lon,file;
	int L;
	L=wfile.GetLength();
	char *E;
	E=new char[L+1];
	E[L]='\0';
	wfile.Read(E,L);
    CString R;
	R=E;
	file=E;
	I=file.Find(L"trkpt",0);
	CString D=L"new BMap.Point(";
	int C;
	C=D.GetLength();
	Afile.Write(Q,l);
	while(I<(L-94))
	{
		Afile.Write("new BMap.Point(",C);
		lon=R.Mid(I+27,10);
		Afile.Write((char*)(_bstr_t)lon,10);
		Afile.Write(L",",1);
		lat=R.Mid(I+11,9);
		Afile.Write((char*)(_bstr_t)lat,9);
		Afile.Write(")",1);
		if(i!=4979)
			Afile.Write(L",",1);
		else
		{ 
			Afile.Write("\r\n",1);
		}
		I=I+94;
		i++;
	}
	CFile Cfile;
	Cfile.Open(L"f:\\tail.txt",CFile::modeRead);
	char *y;
	int Y;
	Y=Cfile.GetLength();
	y=new char[Y+1];
	y[Y]=0;
	Cfile.Read(y,Y);
	Afile.Write(y,Y);
	wfile.Close();
	Afile.Close();
	Bfile.Close();
	Cfile.Close();
}
