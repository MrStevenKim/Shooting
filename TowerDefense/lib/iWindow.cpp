#pragma once

#include "iWindow.h"

#include "iStd.h"


static HWND hWnd;
static HINSTANCE hInstance;
int ctrlNum;

void initWndCtrlSystem()
{
	InitCommonControls(); 
	ctrlNum = 0;

}

HWND* hBt;
HWND hBtnCheck;
HWND* hBtnRadio;
HWND hCbWho;
HWND hLbWho;
HWND hBtnWhoAdd, hBtnWhoRemove;
HWND hEbTmp;
HWND hDlgTest;
void testcheckButton(WPARAM wParam, LPARAM lParam)
{
	HWND hwnd = (HWND)lParam;
	for (int i = 0; i < 3; i++)
	{
		if (hwnd == hBt[i])
		{
			printf("selected Btn = %d\n", i);
			if (i == 0)
			{
				showChooseColor(NULL);
			}

			else
				openFileDlg(i == 1 ? true : false, TEXT("PNG Files\0\*.png;*.PNG\0ALL Files\0*.*\0"));
			return;
		}
	}


	if (hwnd == hBtnCheck)
	{
		bool check = getCheckBox(hwnd);
		setCheckBox(hwnd, !check);
		enableWnd(hEbTmp, !check);
		ShowWindow(hDlgTest, SW_SHOW);
	

		return;
	}

	for (int i = 0; i < 3; i++)
	{
		if (hwnd == hBtnRadio[i])
		{
			setWndRadio(hBtnRadio[i], true);
		}
		else
		{
			setWndRadio(hBtnRadio[i], false);
		}
	}

	if (hwnd == hBtnWhoAdd)
	{
		int index =	indexWndComboBox(hCbWho);
		char* str = getWndComboBox(hCbWho, index);
		
		int last = countWndListBox(hLbWho) - 1;
		addWndListBox(hLbWho, last, getWndComboBox(hCbWho, index));
		free(str);
	}
	else if (hwnd == hBtnWhoRemove)
	{
#if 0
		int index = indexWndListBox(hLbWho);

		if (index != countWndListBox(hLbWho) - 1)
		{
			removeWndListBox(hLbWho, index);
			setWndListBox(hLbWho, index);
		}
#else
		int index = indexWndComboBox(hCbWho);
		removeWndComboBox(hCbWho, index);
		setWndComboBox(hCbWho, index);

#endif
	}

}

bool getCheckBox(HWND hwnd)
{
	return SendMessage(hwnd, (UINT)BM_GETCHECK, (WPARAM)0, (LPARAM)0);
}

void setCheckBox(HWND hwnd, bool on)
{
	SendMessage(hwnd, BM_SETCHECK, on ? BST_CHECKED : BST_UNCHECKED, 0);
}

HWND createWndRadio(int x, int y, int width, int height, const char* str)
{
	wchar_t* ws = utf8_to_utf16(str);

	HWND hwnd = CreateWindow(WC_BUTTON, ws, WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, x, y, width, height, (HWND)hWnd, (HMENU)ctrlNum, (HINSTANCE)hInstance, NULL);

	ctrlNum++;
	free(ws);

	return hwnd;
}

bool getWndRadio(HWND hwnd)
{
	return SendMessage(hwnd, (UINT)BM_GETCHECK, (WPARAM)0, (LPARAM)0);
}

void setWndRadio(HWND hwnd, bool on)
{
	SendMessage(hwnd, BM_SETCHECK, on ? BST_CHECKED : BST_UNCHECKED, 0);
}

HWND createWndGroup(int x, int y, int width, int height, const char* str)
{
	wchar_t* ws = utf8_to_utf16(str);

	HWND hwnd = CreateWindow(WC_BUTTON, ws, WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_GROUPBOX, x, y, width, height, (HWND)hWnd, (HMENU)ctrlNum, (HINSTANCE)hInstance, NULL);

	ctrlNum++;
	free(ws);

	return hwnd;
}

HWND createWndComboBox(int x, int y, int width, int height, const char** line, int lineNum)
{
	HWND hwnd = CreateWindow(WC_COMBOBOX, NULL, WS_TABSTOP | WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWN | CBS_HASSTRINGS, x, y, width, height, (HWND)hWnd, (HMENU)ctrlNum, (HINSTANCE)hInstance, NULL);
	


	ctrlNum++;
	addWndComboBox(hwnd, line, lineNum);

	setWndComboBox(hwnd, 0);

	return hwnd;
}

void addWndComboBox(HWND hwnd, int index, const char* str)
{
	wchar_t* ws = utf8_to_utf16(str);

	SendMessage(hwnd, CB_INSERTSTRING, (WPARAM)index, (LPARAM)ws);
	
	free(ws);

}

void addWndComboBox(HWND hwnd, const char** line, int lineNum)
{
	for (int i = 0; i < lineNum; i++)
	{
		addWndComboBox(hwnd, i, line[i]);
	}
}

void removeWndComboBox(HWND hwnd, int index)
{
	SendMessage(hwnd, CB_DELETESTRING, (WPARAM)index, (LPARAM)0);
}

void setWndComboBox(HWND hwnd, int index)
{
	SendMessage(hwnd, CB_SETCURSEL, (WPARAM)index, (LPARAM)0);
}

int indexWndComboBox(HWND hwnd)
{
	int index = SendMessage(hwnd, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
	return index;
}

int countWndComboBox(HWND hwnd)
{
	
	return SendMessage(hwnd, CB_GETCOUNT, (WPARAM)0, (LPARAM)0);
	
}

char* getWndComboBox(HWND hwnd, int index)
{
	wchar_t wstr[128];

	SendMessage(hwnd, CB_GETLBTEXT, (WPARAM)index, (LPARAM)wstr);

	return utf16_to_utf8(wstr);
}

HWND createWndListBox(int x, int y, int width, int height, const char** line, int lineNum)
{
	HWND hwnd = CreateWindow(WC_LISTBOX, NULL, WS_TABSTOP | WS_CHILD | WS_VISIBLE | WS_BORDER | WS_HSCROLL| WS_VSCROLL|  LBS_NOTIFY | LBS_HASSTRINGS, x, y, width, height, (HWND)hWnd, (HMENU)ctrlNum, (HINSTANCE)hInstance, NULL);

	ctrlNum++;
	addWndListBox(hwnd, line, lineNum);

	setWndListBox(hwnd, 0);

	return hwnd;
}

void addWndListBox(HWND hwnd, int index, const char* str)
{
	wchar_t* ws = utf8_to_utf16(str);

	SendMessage(hwnd, LB_INSERTSTRING, (WPARAM)index, (LPARAM)ws);

	free(ws);
}

void addWndListBox(HWND hwnd, const char** line, int lineNum)
{
	for (int i = 0; i < lineNum; i++)
	{
		addWndListBox(hwnd, i, line[i]);
	}
}

void removeWndListBox(HWND hwnd, int index)
{
	SendMessage(hwnd, LB_DELETESTRING, (WPARAM)index, (LPARAM)0);
}

void setWndListBox(HWND hwnd, int index)
{
	SendMessage(hwnd, LB_SETCURSEL, (WPARAM)index, (LPARAM)0);
}

int indexWndListBox(HWND hwnd)
{
	int index = SendMessage(hwnd, LB_GETCURSEL, (WPARAM)0, (LPARAM)0);
	return index;
}

int countWndListBox(HWND hwnd)
{

	return SendMessage(hwnd, LB_GETCOUNT, (WPARAM)0, (LPARAM)0);

}

char* getWndListBox(HWND hwnd, int index)
{
	wchar_t wstr[128];

	SendMessage(hwnd, LB_GETTEXT, (WPARAM)index, (LPARAM)wstr);

	return utf16_to_utf8(wstr);
}

static int ebMaxLength = 10;

void setWndEditBoxLength(int maxLength)
{
	ebMaxLength = maxLength;
}

LRESULT CALLBACK WndEditBoxProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) // 메인윈도우보다 우선순위를 먼저하기 위해서!
{
	WNDPROC wpOld = (WNDPROC)GetWindowLongPtr(hwnd, GWLP_USERDATA);

	switch (msg)
	{
	case WM_NCDESTROY:
		SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)wpOld);
		SetWindowLongPtr(hwnd, GWLP_USERDATA, 0);
		break;

	case WM_CHAR:
	{
		//숫자 값은 제외
		if (wParam >= '0' && wParam <= '9')
			return 0;

		//return 0; 실제 화면에 입력안되게 하려면 리턴해버리면됨 예를들어서 숫자만 들어와야하는데 문자가 들어올떄 예외처리할때 씀!
		
		wchar_t ws[1024]; // 완성된 값
		int length = GetWindowTextLength(hwnd) + 1;
		GetWindowText(hwnd, ws, length);
		char* s = utf16_to_utf8(ws);
		printf("%c %s\n", wParam, s);
		free(s);
		break;
	} // end of WM_CHAR


	}// end of switch

	return CallWindowProc(wpOld, hwnd, msg, wParam, lParam);

}

HWND createWndEditBox(int x, int y, int width, int height, const char* str)
{
	wchar_t* s = utf8_to_utf16(str);
	HWND hwnd = CreateWindow(WC_EDIT, s, WS_TABSTOP | WS_CHILD | WS_VISIBLE | WS_BORDER| ES_CENTER , x, y, width, height, (HWND)hWnd, (HMENU)ctrlNum, (HINSTANCE)hInstance, NULL);
	free(s);
	ctrlNum++;
	SendMessage(hwnd, (UINT)EM_LIMITTEXT, (WPARAM)ebMaxLength, (LPARAM)0);
	SetWindowLongPtr(hwnd, GWLP_USERDATA, GetWindowLongPtr(hwnd, GWLP_WNDPROC));
	SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)WndEditBoxProc);
	return hwnd;
}

void enableWnd(HWND hwnd, bool enable)
{
	EnableWindow(hwnd, enable);
}

void setWndText(HWND hwnd, const char* szFormat, ...)
{
	char szText[1024];
	va_list args;

	va_start(args, szFormat);
	_vsnprintf(szText, sizeof(szText), szFormat, args);
	va_end(args);

	wchar_t* ws = utf8_to_utf16(szText);
	SetWindowText(hwnd, ws);
	free(ws);
}

char* getWndText(HWND hwnd)
{
	wchar_t ws[1024];
	int length = GetWindowTextLength(hwnd) + 1;
	GetWindowText(hwnd, ws, length);

	return utf16_to_utf8(ws);
}

int getWndInt(HWND hwnd)
{
	char* str = getWndText(hwnd);
	int n = atoi(str);
	free(str);
	return n;
}

float getWndFloat(HWND hwnd)
{
	char* str = getWndText(hwnd);
	float n = atof(str);
	free(str);
	return n;
}

LRESULT CALLBACK dlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:

		//unshow
		ShowWindow(hDlgTest, SW_HIDE);

		//destroy

		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

HWND createWndDlg(int x, int y, int width, int height, const char* strTitle, WNDPROC wndProc)
{
	wchar_t* ws = utf8_to_utf16(strTitle);
	LPCWSTR dlgClassName = ws;

	WNDCLASSEX wc;
	if (GetClassInfoEx(NULL, TEXT("#32770"), &wc))
	{
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.lpfnWndProc = wndProc;
		wc.lpszClassName = dlgClassName;
		RegisterClassEx(&wc);
	}

	HWND hDlg = CreateWindowEx(WS_EX_DLGMODALFRAME,dlgClassName, ws, WS_SYSMENU | WS_CAPTION, x, y, width, height, (HWND)NULL, (HMENU)0, hInstance, NULL);
	free(ws);

	return hDlg;
	 
}

void showChooseColor(methodChooseColor method)
{
	CHOOSECOLOR cc;// 색선택하는 이미 만들어져있는 윈도우
	memset(&cc, 0x00, sizeof(CHOOSECOLOR));
	
	cc.lStructSize = sizeof(CHOOSECOLOR);
	cc.hwndOwner = hWnd;

	COLORREF color[16];
	cc.lpCustColors = color;
	cc.Flags = CC_RGBINIT | CC_FULLOPEN;

	if (!ChooseColor(&cc)) // 창이 열려있으면 어떠한 값도 넘겨주지 읺게 위함
		return;

	int r = (cc.rgbResult & 0x0000ff);
	int g = (cc.rgbResult & 0x00ff00) >> 8;
	int b = (cc.rgbResult & 0xff0000) >> 16;

	printf("r = %d, g = %d, b = %d\n", r, g, b);
	
	if(method) // 색이 선택되고 끝나면 method에 해당하는 함수의 인자로 rgb를 대입하고 그 함수를 호출한다.
		method(r, g, b);
}


static char* strOpenPath = NULL;
const char* openFileDlg(bool open, LPCWSTR filter)
{
	wchar_t wstrPath[1024];

	OPENFILENAME ofn;
	memset(&ofn, 0x00, sizeof(OPENFILENAME));
	
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFilter = filter;
	ofn.nFilterIndex = 1; // 파일을 선택할수 있는 갯수 설정
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.lpstrFile = wstrPath;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	
	bool success = false;

	if (open) success = GetOpenFileName(&ofn);
	else success = GetSaveFileName(&ofn);

	if (success)
	{
		wsprintf(wstrPath, TEXT("%s"), ofn.lpstrFile);
		if (strOpenPath)
			free(strOpenPath);
		strOpenPath = utf16_to_utf8(wstrPath);
		printf("strOpenPath = %s\n", strOpenPath);
		return strOpenPath;
	}
	return NULL;


}

HANDLE startOnlyRun(const wchar_t* className)
{
	HANDLE event = CreateEvent(NULL, TRUE, FALSE, className);
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		CloseHandle(event);
		return NULL;
	}
	return event;
}

void endOnlyRun(HANDLE handle)
{
	CloseHandle(handle);
}

void testCtrlSystem(HWND hwnd, HINSTANCE hinstance)
{
	hWnd = hwnd;
	hInstance = hinstance;

	DragAcceptFiles(hWnd, true);

	createWndStatic(10, 10, 200, 80, "TOOL");
	
	hBt = (HWND*)malloc(sizeof(HWND) * 3);
	const char* strBtn[3] = { "Color","Open","Save" };

	for(int i = 0; i <3; i++)
		hBt[i]=createWndButton(10+220*i, 120, 200, 80, strBtn[i]);

	hBtnCheck = createWndCheckBox(10, 220, 200, 80, "동의함");
	hBtnRadio = (HWND*)malloc(sizeof(HWND) * 3);
	createWndGroup(5, 300, 300, 120, "설문지");

	const char* strBtnRadio[3] = { "1", "2", "3" };
	for (int i = 0; i < 3; i++)
		hBtnRadio[i] = createWndRadio(10 + 100 * i, 320, 80, 80, strBtnRadio[i]);

	const char* strLine[5] = { "최정훈", "정성원", "이호민", "김시윤", "김종민" };
	const char* strList[1] = { "List of End" };
	hCbWho = createWndComboBox(10, 450, 120, 120 * 2, strLine, 5);
	hLbWho = createWndListBox(140, 450, 120, 120 * 2, strList, 1);

	hBtnWhoAdd = createWndButton(300, 450, 80, 30, "Add");
	hBtnWhoRemove = createWndButton(300, 450+80, 80, 30, "Del");

	hEbTmp = createWndEditBox(10, 500, 100, 50, "aaa");

	hDlgTest = createWndDlg(0, 0, 200, 200, "TestDlg", dlgProc);

}

HWND createWndStatic(int x, int y, int width, int height, const char* str)
{
	wchar_t* ws = utf8_to_utf16(str);

	HWND hwnd = CreateWindow(WC_STATIC, ws, WS_CHILD | WS_VISIBLE | ES_CENTER , x, y, width, height, (HWND)hWnd, (HMENU)ctrlNum, (HINSTANCE)hInstance, NULL);
	
	ctrlNum++;
	free(ws);

	return hwnd;

}

HWND createWndButton(int x, int y, int width, int height, const char* str)
{
	wchar_t* ws = utf8_to_utf16(str);

	HWND hwnd = CreateWindow(WC_BUTTON, ws, WS_TABSTOP |WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, x, y, width, height, (HWND)hWnd, (HMENU)ctrlNum, (HINSTANCE)hInstance, NULL);

	ctrlNum++;
	free(ws);

	return hwnd;

}

HWND createWndCheckBox(int x, int y, int width, int height, const char* str)
{
	wchar_t* ws = utf8_to_utf16(str);

	HWND hwnd = CreateWindow(WC_BUTTON, ws, WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_CHECKBOX, x, y, width, height, (HWND)hWnd, (HMENU)ctrlNum, (HINSTANCE)hInstance, NULL);

	ctrlNum++;
	free(ws);

	return hwnd;

}

static iCriticalSection* instanceCS = NULL;

iCriticalSection::iCriticalSection()
{
	InitializeCriticalSection(&cs);
}

iCriticalSection* iCriticalSection::instance()
{
	if (instanceCS == NULL)
		instanceCS = new iCriticalSection();
	return instanceCS;
}

iCriticalSection::~iCriticalSection()
{
	DeleteCriticalSection(&cs);
	delete instanceCS;

	instanceCS = NULL;
}

void iCriticalSection::start()
{
	EnterCriticalSection(&cs);
}

void iCriticalSection::end()
{
	LeaveCriticalSection(&cs);
}
