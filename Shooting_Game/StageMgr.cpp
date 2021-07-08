#include "stdafx.h"
#include "StageMgr.h"
#include "Butterfly.h"

CStageMgr* CStageMgr::m_pInstance = nullptr;
CStageMgr::CStageMgr()
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
}

void CStageMgr::Update()
{
	
}

bool CStageMgr::Check_Monster(int x, int y)
{
	if(m_bMonster[x][y])
		return true;

	else return false;
}

