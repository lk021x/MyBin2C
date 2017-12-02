// FileDlgDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FileDlgDemo.h"
#include "FileDlgDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileDlgDemoDlg dialog

CFileDlgDemoDlg::CFileDlgDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFileDlgDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFileDlgDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	convert_type=FALSE;
	fpIn=NULL;
	fpOut=NULL;
}

void CFileDlgDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFileDlgDemoDlg)
	DDX_Control(pDX, IDC_EDIT1, m_ctlEdit);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_BUTTON_TEXT, btn_Text);
	DDX_Control(pDX, IDC_BUTTON_BIN, btn_Bin);
}

BEGIN_MESSAGE_MAP(CFileDlgDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CFileDlgDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_FILE, OnFile)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_TEXT, &CFileDlgDemoDlg::OnBnClickedButtonText)
	ON_BN_CLICKED(IDC_BUTTON_BIN, &CFileDlgDemoDlg::OnBnClickedButtonBin)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileDlgDemoDlg message handlers

BOOL CFileDlgDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFileDlgDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFileDlgDemoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFileDlgDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CFileDlgDemoDlg::OnFile() 
{
	// TODO: Add your control notification handler code here
	CString szFilters="MyType Files (*.html)|*.html|All Files (*.*)|*.*||";		//定义文件过滤器
   //创建打开文件对话框对象，默认的文件扩展名为 ".my".
   CFileDialog fileDlg (TRUE, "", "*.*",OFN_FILEMUSTEXIST| OFN_HIDEREADONLY, szFilters, this);
   //调用DoModal()函数显示打开文件对话框
   if( fileDlg.DoModal ()==IDOK )
   {
      InPathName = fileDlg.GetPathName();
	  // 进行文件的相关操作
	  m_ctlEdit.SetWindowText(InPathName);
	  ext=fileDlg.GetFileExt();

      //将当前窗口的标题设置为打开文件的名字
      //CString fileName = fileDlg.GetFileTitle ();
      //SetWindowText(fileName);

	  OutPathName=InPathName+_T(".h");
   }	
}

//不支持 '/* ... */'注释行的转换
void CFileDlgDemoDlg::OnBnClickedButtonText()
{
	// TODO: 在此添加控件通知处理程序代码
	convert_type=TRUE;
	fpIn=fopen(InPathName, _T("rb"));
	fpOut=fopen(OutPathName, _T("w"));
	if(fpIn == NULL)
	{
		return ;
	}
	if(fpOut == NULL)
	{
		fclose(fpIn);
		return ;
	}

	fwrite( "static const char a[] = {\n", 1, strlen("static const char a[] = {\n"), fpOut );

	if(ext==_T("html"))
	{
		fwrite( "\"HTTP/1.1 200 OK\\r\\nContent-Type:text/html\\r\\nAccept-Ranges:bytes\\r\\n\\r\\n\"\n", 1, 
			strlen("\"HTTP/1.1 200 OK\\r\\nContent-Type:text/html\\r\\nAccept-Ranges:bytes\\r\\n\\r\\n\"\n"), fpOut );
	}
	else if(ext==_T("js"))
	{
		fwrite( "\"HTTP/1.1 200 OK\\r\\nContent-Type:text/javascript\\r\\nAccept-Ranges:bytes\\r\\n\\r\\n\"\n", 1, 
			strlen("\"HTTP/1.1 200 OK\\r\\nContent-Type:text/javascript\\r\\nAccept-Ranges:bytes\\r\\n\\r\\n\"\n"), fpOut );
	}
	else if(ext==_T("css"))  //
	{
		fwrite( "\"HTTP/1.1 200 OK\\r\\nContent-Type: text/css\\r\\n\\r\\n\"\n", 1, 
			strlen("\"HTTP/1.1 200 OK\\r\\nContent-Type: text/css\\r\\n\\r\\n\"\n"), fpOut );
	}

	int current_index=0;             //当前读取的行 
	char strLine[1024];             //每行最大读取的字符数,可根据实际情况扩大 
	bool frist;
	bool end;
	bool skip;			//整行都是注释  
	bool midlle;        //行的部分是注释
	int len;
	long row=0;
	while (!feof(fpIn))
	{
		memset(strLine,0x00,1024);
		strLine[0]=0x20;
		frist=false;
		end=false;
		skip=false;
		midlle=false;
		fgets(&strLine[1],1023,fpIn);  //读取一行 
		len=strlen(strLine);
		row++;
		//替换掉符号(")为(\")
		int pos=0;
		char temp[1200];
		memset(temp,0,1200);
		for(int i=0; i<1023; i++)
		{
			if(strLine[i]!='\"')
			{
				temp[pos]=strLine[i];
				pos+=1;
			}
			else
			{
				temp[pos]='\\';
				temp[pos+1]='\"';
				pos+=2;
			}
		}
		memcpy(strLine, temp, 1024);

		if(row==103)
		{
			row=row;	
		}

		//格式化文本, 去除空格和注释
		for(int i=0; i<1023; i++)
		{
			if((frist==false)&& i>0 && strLine[i] != ' ' &&
				strLine[i] != 0x09 && strLine[i]!='\n')
			{
				if(strLine[i]=='/' && strLine[i+1]=='/')
				{
					//整行注释跳过
					frist=true; 
					skip=true; 
				}
				else
				{
					frist=true;
					if(i==0) strLine[0]='\"';
					else strLine[i-1]='\"';
				}
			}

			if(ext==_T("html"))  
			{
				if(frist==true && skip==false && row>2 && strLine[i]=='/' && strLine[i+1]=='/')  //部分注释跳过,跳过html前2行
				{
					midlle=true;
					int index=i;
					char buf[1024];
					int cnt=0;
					for(int j=0; j<len-index; j++) {buf[j]=strLine[j+index];cnt++;}
					strLine[index]='\"';
					for(int k=0; k<cnt; k++)strLine[k+index+1]=buf[k];
					strLine[cnt+index+1]='\0';
					i++;
				}
			}
			else
			{
				if(frist==true && skip==false && strLine[i]=='/' && strLine[i+1]=='/')  //部分注释跳过
				{
					midlle=true;
					int index=i;
					char buf[1024];
					int cnt=0;
					for(int j=0; j<len-index; j++) {buf[j]=strLine[j+index];cnt++;}
					strLine[index]='\"';
					for(int k=0; k<cnt; k++)strLine[k+index+1]=buf[k];
					strLine[cnt+index+1]='\0';
				}
			}

			if(frist==true&&strLine[i]=='\r')//0x0d
			{
				if(strLine[i-1]=='\n')   //unicode 包含 \r; 0x0d 回车 \n:0x0a 换行
				{
					if(skip==false && midlle==false)
					{
						strLine[i-1]='\\';
						strLine[i]='n';
						strLine[i+1]='\"';
						strLine[i+2]='\n';
					}
					else
					{
						strLine[i-1]='\n';
						strLine[i]='\0';
					}
				} 
				else   //utf-8 只有 \n
				{
					if(skip==false && midlle==false)
					{
						strLine[i]='\\';
						strLine[i+1]='n';
						strLine[i+2]='\"';
						strLine[i+3]='\n';
					}
					else
					{
						strLine[i]='\n';
						strLine[i+1]='\0';
					}
				}
				if(skip==false && midlle==false)
				{
					for(int j=i-1; j>0; j--)
					{
						if(strLine[j]==' ')
						{
							strLine[i]='\\';
							strLine[i+1]='n';
							strLine[i+2]='\"';
							strLine[i+3]='\n';
						}
						else break;
					}
				}
				end=true;
				break;
			}
		}

		if(frist&&end)
			fwrite( strLine, 1, strlen(strLine), fpOut );
	}
	fwrite( "};", 1, strlen("};"), fpOut );
	fclose(fpIn);
	fclose(fpOut);
	MessageBox("转换成功!");
}

void CFileDlgDemoDlg::OnBnClickedButtonBin()
{
	// TODO: 在此添加控件通知处理程序代码
	convert_type=FALSE;
	fpIn=fopen(InPathName, _T("rb"));
	fpOut=fopen(OutPathName, _T("w"));
	if(fpIn == NULL)
	{
		return ;
	}
	if(fpOut == NULL)
	{
		fclose(fpIn);
		return ;
	}

	fseek( fpIn, 0, SEEK_END );//定位文件指针到文件末尾//成功返回0，不成功返回-1；
	long file_size = ftell( fpIn );//ftell：获得当前文件指针到文件首的大小
	fseek( fpIn, 0, SEEK_SET );//再定位文件指针到文件头

	fwrite( "static const char a[] = {\n", 1, strlen("static const char a[] = {\n"), fpOut );

	char buffer[64]={0};
	unsigned char temp=0;
	int num=0;
	int count=0;
	while (!feof(fpIn))
	{
		memset(buffer,0,64);
		num=0;
		num=fread(&temp, 1, 1, fpIn);
		if(num==1)
		{
			count+=num;
			if(count < file_size)
				_stprintf(buffer, _T("0x%02x,"),temp);
			else
				_stprintf(buffer, _T("0x%02x"),temp);
			fwrite( buffer, 1, strlen(buffer), fpOut );
		}

		if(count%16==0)fwrite( "\n", 1, strlen("\n"), fpOut );
	}

	fwrite( "\n};", 1, strlen("\n};"), fpOut );
	fclose(fpIn);
	fclose(fpOut);
	MessageBox("转换成功!");
}
