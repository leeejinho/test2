#pragma once

#ifndef __SCROLLMGR_H__
#define __SCROLLMGR_H__



class CScrollMgr
{
private:
	CScrollMgr();
	~CScrollMgr();

public:
	static CScrollMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CScrollMgr;
		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		SAFE_DELETE(m_pInstance);
	}

public:
	void Set_ScrollX(float _fScrollX) { m_fScrollX += _fScrollX; }
	void Set_ScrollY(float _fScrollY) { m_fScrollY += _fScrollY; }

public:
	float Get_ScrollX() { return m_fScrollX; }
	float Get_ScrollY() { return m_fScrollY; }

private:
	static CScrollMgr* m_pInstance;

	float		m_fScrollX;
	float		m_fScrollY;
};


#endif // !__SCROLLMGR_H__
