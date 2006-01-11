#pragma once

#include "Cursors.h"
#include "SelectionHandler.h"

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
// User-defined message for notifying ConsoleViewContainer

#define UM_CONSOLE_RESIZED	WM_USER + 0x1000
#define UM_CONSOLE_CLOSED	WM_USER + 0x1001

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////

class ConsoleView : public CWindowImpl<ConsoleView>, public CScrollImpl<ConsoleView> {

	public:
		DECLARE_WND_CLASS(NULL)

		ConsoleView(DWORD dwTabIndex, DWORD dwRows, DWORD dwColumns);
		~ConsoleView();

		BOOL PreTranslateMessage(MSG* pMsg);

		BEGIN_MSG_MAP(ConsoleView)
			MESSAGE_HANDLER(WM_CREATE, OnCreate)
			MESSAGE_HANDLER(WM_CLOSE, OnClose)
			MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
			MESSAGE_HANDLER(WM_PAINT, OnPaint)
			MESSAGE_HANDLER(WM_WINDOWPOSCHANGED, OnWindowPosChanged)
			MESSAGE_HANDLER(WM_SYSKEYDOWN, OnSysKey)
			MESSAGE_HANDLER(WM_SYSKEYUP, OnSysKey)
			MESSAGE_HANDLER(WM_KEYDOWN, OnKey)
			MESSAGE_HANDLER(WM_KEYUP, OnKey)
			MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
			MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
			MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
			MESSAGE_HANDLER(WM_TIMER, OnTimer)
			CHAIN_MSG_MAP(CScrollImpl<ConsoleView>)
		END_MSG_MAP()

//		Handler prototypes (uncomment arguments if needed):
//		LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//		LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//		LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

		LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
		LRESULT OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
		LRESULT OnEraseBkgnd(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled);
		LRESULT OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
		LRESULT OnWindowPosChanged(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/);
		LRESULT OnSysKey(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/);
		LRESULT OnKey(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/);
		LRESULT OnLButtonDown(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/);
		LRESULT OnLButtonUp(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/);
		LRESULT OnMouseMove(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/);
		LRESULT OnTimer(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/);


	public:

		void GetRect(RECT& clientRect);
		bool GetMaxRect(RECT& maxClientRect);
		void AdjustRectAndResize(RECT& clientRect);
		void OwnerWindowMoving();

		ConsoleHandler& GetConsoleHandler() { return m_consoleHandler; }

		bool GetConsoleWindowVisible() const { return m_bConsoleWindowVisible; }
		void SetConsoleWindowVisible(bool bVisible);

		void SetAppActiveStatus(bool bAppActive);

		void SetViewActive(bool bActive) { m_bViewActive = bActive; }

		shared_ptr<CIcon> GetIcon() const { return m_tabSettings->tabIcon; }

		void Copy(const CPoint* pPoint = NULL);
		void Paste();

	private:

		void OnConsoleChange(bool bResize);
		void OnConsoleClose();

		void CreateOffscreenBuffers();
		void CreateOffscreenBitmap(const CPaintDC& dcWindow, const RECT& rect, CDC& cdc, CBitmap& bitmap);
		void CreateFont(const wstring& strFontName);

		DWORD GetBufferDifference();

		void Repaint();

		void RepaintText();
		void RepaintTextChanges();

		void BitBltOffscreen();

		// sends text to the windows console
		void SendTextToConsole(const wchar_t* pszText);


	private:

		bool	m_bInitializing;
		bool	m_bAppActive;
		bool	m_bViewActive;
		bool	m_bConsoleWindowVisible;

		DWORD	m_dwStartupRows;
		DWORD	m_dwStartupColumns;

		ConsoleHandler	m_consoleHandler;

		CDC		m_dcOffscreen;
		CDC		m_dcText;

		CBitmap	m_bmpOffscreen;
		CBitmap	m_bmpText;

		CFont	m_fontText;

		int		m_nCharHeight;
		int		m_nCharWidth;

		shared_array<CHAR_INFO>	m_screenBuffer;

		int			m_nInsideBorder;

		bool		m_bUseFontColor;
		COLORREF	m_crFontColor;

		bool		m_bMouseDragable;
		bool		m_bInverseShift;

		shared_ptr<TabSettings>			m_tabSettings;

		shared_ptr<Cursor>				m_cursor;
		shared_ptr<SelectionHandler>	m_selectionHandler;
};

//////////////////////////////////////////////////////////////////////////////
