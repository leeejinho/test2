#pragma once
#ifndef __CSTAGEMGR_H__
#define __CSTAGEMGR_H__

#define X 10
#define Y 4

class CStageMgr
{
private:
	static CStageMgr* m_pInstance;
private:
	CStageMgr();
	~CStageMgr();


public:
	static CStageMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CStageMgr;
		return m_pInstance;
	}

	static void Destroy_Instance()
	{
		if (m_pInstance)
		{
			SAFE_DELETE(m_pInstance);
		}
	}
public:
	void Initialize();
	void Update();

public:
	D3DXVECTOR3		    GetVec(int x, int y) { return myStage[x][y]; }
	void				Set_Check(int x, int y) { m_bMonster[x][y] = true; }
	bool				Check_Monster(int x, int y);				// 자리 비었는지 체크하는 함수

private:
	D3DXVECTOR3			myStage[X][Y];
	bool				m_bMonster[X][Y];

};

#endif //__CSTAGEMGR_H__
