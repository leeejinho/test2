#include "stdafx.h"
#include "StageMgr.h"
#include "Butterfly.h"
#include "ZigZag.h"
#include "ObjMgr.h"
#include "Circle_Monster.h"
#include "Monster.h"
#include "KeyMgr.h"
#include "Player.h"

CStageMgr* CStageMgr::m_pInstance = nullptr;
CStageMgr::CStageMgr()
	:m_MonsterCnt{ 0 }, m_bClear(true), m_dwTime{ 0 }, m_eCurStage(0), m_fStage(0.f), m_pPlayer(nullptr), m_bDoubleCheck(false)
{
	ZeroMemory(myStage, sizeof(D3DXVECTOR3) * (X*Y));
	ZeroMemory(m_bMonster, sizeof(bool) * (X*Y));
}


CStageMgr::~CStageMgr()
{
}

void CStageMgr::Initialize()
{
	for (int i = 0; i < X; ++i)
	{
		for (int j = 0; j < Y; ++j)
		{
			myStage[i][j].x = i * 50.f + 100.f;
			myStage[i][j].y = j * 50.f + 50.f;
			myStage[i][j].z = 0;
		}
	}

	m_eCurStage = -1;
	m_bClear = true;


}

void CStageMgr::Update()
{
	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
		Start_Again();
	Check_Clear();
	Start_Stage();
}

void CStageMgr::Start_Again()
{
	//if(CObjMgr::Get_Instance()->Get_List(OBJID::PLAYER).size() > 0)
	//m_pPlayer = CObjMgr::Get_Instance()->Get_Player();
	//else m_pPlayer = nullptr

	if (m_pPlayer != nullptr)
		return;

	CObjMgr::Get_Instance()->Clear_List_For_Restart();
	CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CPlayer>::Create(), OBJID::PLAYER);
	m_fStage = 0.f;
	m_bClear = false;

}

void CStageMgr::Start_Stage()
{
	if (CObjMgr::Get_Instance()->Get_List(OBJID::PLAYER).size() > 0) 
		m_pPlayer = CObjMgr::Get_Instance()->Get_Player();
	else m_pPlayer = nullptr;

	if (m_pPlayer == nullptr) 
		return;

	if (m_bClear)
	{
		// debug

		m_eCurStage = 0;

		m_eCurStage = rand() % 6;
    
		m_bClear = false;
		m_fStage += 0.5f;
		if (m_fStage > 5.f)
			m_fStage = 5.f;
	}
  
	switch (m_eCurStage)
	{
	case 0:
		Spawn_Double(6, 500, BUTTERFLY_RIGHT);
		Spawn_Double(6, 500, BUTTERFLY_LEFT);
		Spawn_Circle_Monster(5, 300, 300.f);
		break;
	case 1:
		Spawn_ZigZag_Left(4, 250);
		Spawn_Double(10, 500, MONSTER_LEFT);
		Spawn_Double(10, 500, MONSTER_RIGHT);
		break;
	case 2:
		Spawn_Double(6, 500, BUTTERFLY_LEFT);
		Spawn_Double(5, 500, BUTTERFLY_LEFT_D);
		Spawn_Double(6, 500, MONSTER_RIGHT);
		break;
	case 3:
		Spawn_Double(9, 500, MONSTER_RIGHT);
		Spawn_Double(9, 500, MONSTER_RIGHT_D);
		Spawn_ZigZag_Left(4, 250);
		break;
	case 4:
		Spawn_Double(6, 500, BUTTERFLY_RIGHT);
		Spawn_Double(5, 500, BUTTERFLY_RIGHT_D);
		Spawn_Double(6, 500, BUTTERFLY_LEFT);
		Spawn_Double(5, 500, BUTTERFLY_LEFT_D);
		Spawn_Circle_Monster(5, 300, 300.f);
		break;
	case 5:
		Spawn_Double(6, 500, MONSTER_LEFT);
		Spawn_Double(5, 500, MONSTER_LEFT_D);
		Spawn_Double(6, 500, MONSTER_RIGHT);
		Spawn_Double(4, 500, MONSTER_RIGHT_D);
		break;
	case 6:
		Spawn_Double(8, 500, BUTTERFLY_RIGHT);
		Spawn_Double(5, 500, BUTTERFLY_RIGHT_D);
		Spawn_Double(8, 500, MONSTER_LEFT);
		Spawn_Double(5, 500, MONSTER_LEFT_D);
		break;
	}
}


//void CStageMgr::Spawn_ButterFly_Left(int _Cnt, int _delay)		// delay 500 ����
//{
//	if (m_MonsterCnt[BUTTERFLY_LEFT] < _Cnt)
//	{
//		if (m_dwTime[BUTTERFLY_LEFT] + _delay < GetTickCount())
//		{
//			int x = 0;
//			int y = 0;
//			bool Check = false;
//			for (int i = 0; i < 30; ++i)
//			{
//				x = rand() % X;
//				y = rand() % Y;
//
//				if (!Check_Monster(x, y))
//				{
//					Check = true;
//					break;
//				}
//			}
//
//			if (Check)
//			{
//				CObj* pObj = CAbstractFactory<CButterfly>::Create();
//				static_cast<CButterfly*>(pObj)->Set_State(CButterfly::LEFT);
//				static_cast<CButterfly*>(pObj)->Set_TargetPos(GetVec(x, y));
//				Set_Check(x, y);
//				CObjMgr::Get_Instance()->Add_Object(pObj, OBJID::MONSTER);
//				++m_MonsterCnt[BUTTERFLY_LEFT];
//			}
//			m_dwTime[BUTTERFLY_LEFT] = GetTickCount();
//		}
//	}
//}
//
//void CStageMgr::Spawn_ButterFly_Right(int _Cnt, int _delay)
//{
//	if (m_MonsterCnt[BUTTERFLY_RIGHT] < _Cnt)
//	{
//		if (m_dwTime[BUTTERFLY_RIGHT] + _delay < GetTickCount())
//		{
//			int x = 0;
//			int y = 0;
//			bool Check = false;
//			for (int i = 0; i < 30; ++i)
//			{
//				x = rand() % X;
//				y = rand() % Y;
//
//				if (!Check_Monster(x, y))
//				{
//					Check = true;
//					break;
//				}
//			}
//
//			if (Check)
//			{
//				CObj* pObj = CAbstractFactory<CButterfly>::Create();
//				static_cast<CButterfly*>(pObj)->Set_State(CButterfly::RIGHT);
//				static_cast<CButterfly*>(pObj)->Set_TargetPos(GetVec(x, y));
//				Set_Check(x, y);
//				CObjMgr::Get_Instance()->Add_Object(pObj, OBJID::MONSTER);
//				++m_MonsterCnt[BUTTERFLY_RIGHT];
//			}
//
//			m_dwTime[BUTTERFLY_RIGHT] = GetTickCount();
//		}
//	}
//	
//}


void CStageMgr::Spawn_ZigZag_Left(int _Cnt, int _delay)
{

	if (m_MonsterCnt[ZIGZAG_LEFT] < _Cnt)
	{
		if (m_dwTime[ZIGZAG_LEFT] + _delay < GetTickCount())
		{
			CObj* pObj = CAbstractFactory<CZigZag>::Create_UnIntialize();
			static_cast<CZigZag*>(pObj)->Set_Left();
			pObj->Initialize();
			CObjMgr::Get_Instance()->Add_Object(pObj, OBJID::MONSTER);
			m_dwTime[ZIGZAG_LEFT] = GetTickCount();

			++m_MonsterCnt[ZIGZAG_LEFT];
		}
	}
}

void CStageMgr::Spawn_ZigZag_Right(int _Cnt, int _delay)
{

	if (m_MonsterCnt[ZIGZAG_RIGHT] < _Cnt)
	{
		if (m_dwTime[ZIGZAG_RIGHT] + _delay < GetTickCount())
		{
			CObj* pObj = CAbstractFactory<CZigZag>::Create_UnIntialize();
			pObj->Initialize();
			CObjMgr::Get_Instance()->Add_Object(pObj, OBJID::MONSTER);
			m_dwTime[ZIGZAG_RIGHT] = GetTickCount();

			++m_MonsterCnt[ZIGZAG_RIGHT];
		}
	}
}

void CStageMgr::Spawn_Circle_Monster(int _Cnt, int _delay, float fX)
{

	if (m_MonsterCnt[CIRCLE_MONSTER] < _Cnt)
	{
		if (m_dwTime[CIRCLE_MONSTER] + _delay < GetTickCount())
		{
			CObj* pObj = CAbstractFactory<CCircle_Monster>::Create(300.f, 0.f);
			CObjMgr::Get_Instance()->Add_Object(pObj, OBJID::MONSTER);

			pObj = CAbstractFactory<CCircle_Monster>::Create(300.f, 0.f);
			static_cast<CCircle_Monster*>(pObj)->Set_Left();
			CObjMgr::Get_Instance()->Add_Object(pObj, OBJID::MONSTER);
			m_dwTime[CIRCLE_MONSTER] = GetTickCount();

			++m_MonsterCnt[CIRCLE_MONSTER];
		}
	}
}


//void CStageMgr::Spawn_Monster_Left(int _Cnt, int _delay)
//{
//
//	if (m_MonsterCnt[MONSTER_LEFT] < _Cnt)
//	{
//		if (m_dwTime[MONSTER_LEFT] + _delay < GetTickCount())
//		{
//
//			int x = 0;
//			int y = 0;
//			bool Check = false;
//			for (int i = 0; i < 30; ++i)
//			{
//				x = rand() % X;
//				y = rand() % Y;
//
//				if (!Check_Monster(x, y))
//				{
//					Check = true;
//					break;
//				}
//			}
//
//			if (Check)
//			{
//				CObj* pObj = CAbstractFactory<CMonster>::Create();
//				static_cast<CMonster*>(pObj)->Set_State(CMonster::LEFT);
//				static_cast<CMonster*>(pObj)->Set_TargetPos(GetVec(x, y));
//				Set_Check(x, y);
//				CObjMgr::Get_Instance()->Add_Object(pObj, OBJID::MONSTER);
//				++m_MonsterCnt[MONSTER_LEFT];
//			}
//			m_dwTime[MONSTER_LEFT] = GetTickCount();
//		}
//	}
//}
//
//void CStageMgr::Spawn_Monster_Right(int _Cnt, int _delay)
//{
//	if (m_MonsterCnt[MONSTER_RIGHT] < _Cnt)
//	{
//		if (m_dwTime[MONSTER_RIGHT] + _delay < GetTickCount())
//		{
//			int x = 0;
//			int y = 0;
//			bool Check = false;
//			for (int i = 0; i < 30; ++i)
//			{
//				x = rand() % X;
//				y = rand() % Y;
//
//				if (!Check_Monster(x, y))
//				{
//					Check = true;
//					break;
//				}
//			}
//
//			if (Check)
//			{
//				CObj* pObj = CAbstractFactory<CMonster>::Create();
//				static_cast<CMonster*>(pObj)->Set_State(CMonster::RIGHT);
//				static_cast<CMonster*>(pObj)->Set_TargetPos(GetVec(x, y));
//				Set_Check(x, y);
//				CObjMgr::Get_Instance()->Add_Object(pObj, OBJID::MONSTER);
//				++m_MonsterCnt[MONSTER_RIGHT];
//
//				m_dwTime[MONSTER_RIGHT] = GetTickCount();
//			}
//		}
//	}
//}


void CStageMgr::Check_Clear()
{
	if (CObjMgr::Get_Instance()->Get_List(OBJID::MONSTER).size() < 1)
	{
		m_bClear = true;
		m_eCurStage = -1;

		for (int i = 0; i < MONSTER_END; ++i)
		{
			m_MonsterCnt[i] = 0;
		}
		for (int i = 0; i < Y; ++i)
		{
			for (int j = 0; j < X; ++j)
			{
				m_bMonster[i][j] = false;
			}
		}
	}
}

bool CStageMgr::Check_Monster(int x, int y)
{
	if (m_bMonster[x][y])
		return true;

	else return false;
}

void CStageMgr::Spawn_Double(int _Cnt, int _delay, CStageMgr::ID _eID)
{
	if (m_MonsterCnt[_eID] < _Cnt)
	{
		if (m_dwTime[_eID] + _delay < GetTickCount())
		{
			int x = 0;
			int y = 0;
			bool Check = false;
			for (int i = 0; i < 30; ++i)
			{
				x = rand() % X;
				y = rand() % Y;

				if (!Check_Monster(x, y))
				{
					Check = true;
					break;
				}
			}
			if (Check)
			{
				CObj* pObj = nullptr;
				switch (_eID)
				{
				case CStageMgr::BUTTERFLY_LEFT:
					pObj = CAbstractFactory<CButterfly>::Create();
					static_cast<CButterfly*>(pObj)->Set_State(CButterfly::LEFT);
					static_cast<CButterfly*>(pObj)->Set_TargetPos(GetVec(x, y));
					Set_Check(x, y);
					CObjMgr::Get_Instance()->Add_Object(pObj, OBJID::MONSTER);
					++m_MonsterCnt[BUTTERFLY_LEFT];
					break;
				case CStageMgr::BUTTERFLY_RIGHT:
					pObj = CAbstractFactory<CButterfly>::Create();
					static_cast<CButterfly*>(pObj)->Set_State(CButterfly::RIGHT);
					static_cast<CButterfly*>(pObj)->Set_TargetPos(GetVec(x, y));
					Set_Check(x, y);
					CObjMgr::Get_Instance()->Add_Object(pObj, OBJID::MONSTER);
					++m_MonsterCnt[BUTTERFLY_RIGHT];
					break;
				case CStageMgr::MONSTER_LEFT:
					pObj = CAbstractFactory<CMonster>::Create();
					static_cast<CMonster*>(pObj)->Set_State(CMonster::LEFT);
					static_cast<CMonster*>(pObj)->Set_TargetPos(GetVec(x, y));
					Set_Check(x, y);
					CObjMgr::Get_Instance()->Add_Object(pObj, OBJID::MONSTER);
					++m_MonsterCnt[MONSTER_LEFT];
					break;
				case CStageMgr::MONSTER_RIGHT:
					pObj = CAbstractFactory<CMonster>::Create();
					static_cast<CMonster*>(pObj)->Set_State(CMonster::RIGHT);
					static_cast<CMonster*>(pObj)->Set_TargetPos(GetVec(x, y));
					Set_Check(x, y);
					CObjMgr::Get_Instance()->Add_Object(pObj, OBJID::MONSTER);
					++m_MonsterCnt[MONSTER_RIGHT];
					break;
				case CStageMgr::BUTTERFLY_LEFT_D:
					pObj = CAbstractFactory<CButterfly>::Create();
					static_cast<CButterfly*>(pObj)->Set_State(CButterfly::DOUBLE_LEFT);
					static_cast<CButterfly*>(pObj)->Set_TargetPos(GetVec(x, y));
					Set_Check(x, y);
					CObjMgr::Get_Instance()->Add_Object(pObj, OBJID::MONSTER);
					++m_MonsterCnt[BUTTERFLY_LEFT_D];
					break;
				case CStageMgr::BUTTERFLY_RIGHT_D:
					pObj = CAbstractFactory<CButterfly>::Create();
					static_cast<CButterfly*>(pObj)->Set_State(CButterfly::DOUBLE_RIGHT);
					static_cast<CButterfly*>(pObj)->Set_TargetPos(GetVec(x, y));
					Set_Check(x, y);
					CObjMgr::Get_Instance()->Add_Object(pObj, OBJID::MONSTER);
					++m_MonsterCnt[BUTTERFLY_RIGHT_D];
					break;
				case CStageMgr::MONSTER_LEFT_D:
					pObj = CAbstractFactory<CMonster>::Create();
					static_cast<CMonster*>(pObj)->Set_State(CMonster::DOUBLE_LEFT);
					static_cast<CMonster*>(pObj)->Set_TargetPos(GetVec(x, y));
					Set_Check(x, y);
					CObjMgr::Get_Instance()->Add_Object(pObj, OBJID::MONSTER);
					++m_MonsterCnt[MONSTER_LEFT_D];
					break;
				case CStageMgr::MONSTER_RIGHT_D:
					pObj = CAbstractFactory<CMonster>::Create();
					static_cast<CMonster*>(pObj)->Set_State(CMonster::DOUBLE_RIGHT);
					static_cast<CMonster*>(pObj)->Set_TargetPos(GetVec(x, y));
					Set_Check(x, y);
					CObjMgr::Get_Instance()->Add_Object(pObj, OBJID::MONSTER);
					++m_MonsterCnt[MONSTER_RIGHT_D];
					break;
				case CStageMgr::MONSTER_END:
					break;
				default:
					break;
				}
			}

			m_dwTime[_eID] = GetTickCount();
		}
	}

}