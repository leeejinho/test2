#pragma once
#ifndef __CSTAGEMGR_H__
#define __CSTAGEMGR_H__

#define X 10
#define Y 5

class CStageMgr
{
private:
	enum ID { BUTTERFLY_LEFT, BUTTERFLY_RIGHT, ZIGZAG_LEFT, ZIGZAG_RIGHT, CIRCLE_MONSTER, MONSTER_LEFT, MONSTER_RIGHT, BUTTERFLY_LEFT_D,BUTTERFLY_RIGHT_D
		, MONSTER_LEFT_D, MONSTER_RIGHT_D, MONSTER_END };
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
	//void Spawn_ButterFly_Left(int _Cnt, int _delay);
	//void Spawn_ButterFly_Right(int _Cnt, int _delay);
	void Spawn_ZigZag_Left(int _Cnt, int _delay);
	void Spawn_ZigZag_Right(int _Cnt, int _delay);
	void Spawn_Circle_Monster(int _Cnt, int _delay, float fX);
	//void Spawn_Monster_Left(int _Cnt, int _delay);
	//void Spawn_Monster_Right(int _Cnt, int _delay);


	void Spawn_Double(int _Cnt, int _delay, CStageMgr::ID _eID);				// 2줄 나오는 것만.

	void Start_Again();
	void Start_Stage();
	void Check_Clear();

public:
	float Get_Stage() { return m_fStage; }

public:
	D3DXVECTOR3		    GetVec(int x, int y) { return myStage[x][y]; }
	void				Set_Check(int x, int y) { m_bMonster[x][y] = true; }
	bool				Check_Monster(int x, int y);				// 자리 비었는지 체크하는 함수


private:
	CObj*				m_pPlayer;
	D3DXVECTOR3			myStage[X][Y];
	bool				m_bMonster[X][Y];
	bool				m_bClear;

	DWORD				m_dwTime[MONSTER_END];
	int					m_MonsterCnt[MONSTER_END];
	int					m_eCurStage;


	bool				m_bDoubleCheck;			// 2줄인지 아닌지 체크

	float				m_fStage;


};

#endif //__CSTAGEMGR_H__
