
// TextDlg.h : ͷ�ļ�
//

#pragma once


// CTextDlg �Ի���
class CTextDlg : public CDialogEx
{
// ����
public:
	CTextDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TEXT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_list;
	afx_msg void OnBnClickedRead();
	afx_msg void OnBnClickedWrite();
	afx_msg void OnBnClickedDraw();
};
