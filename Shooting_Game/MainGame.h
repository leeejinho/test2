#pragma once
#ifndef __MAINGAME_H__
#define __MAINGAME_H__

class CMainGame final
{
public:
	CMainGame();
	~CMainGame();

public:
	void Initialize();
	void Update();
	void Late_Update();
	void Render();
	void Release();

private:
	HDC		m_hDC;
	HDC		m_BackDC;
	HBITMAP m_backBit;
	HBITMAP m_oldBit;
	DWORD	m_dwTime;

};

#endif // !__MAINGAME_H__
