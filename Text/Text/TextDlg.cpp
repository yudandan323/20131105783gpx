




// TextDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Text.h"
#include "TextDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CTextDlg �Ի���




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


// CTextDlg ��Ϣ�������

BOOL CTextDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTextDlg::OnPaint()
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
		MessageBox(L"��ȡ�ɹ�");
		UpdateData(false);
	}
	else
	{
		MessageBox(L"�޴��ļ�");
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
