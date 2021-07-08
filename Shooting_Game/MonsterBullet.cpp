#include "stdafx.h"
#include "MonsterBullet.h"
#include "ObjMgr.h"

CMonsterBullet::CMonsterBullet()
{
}


CMonsterBullet::~CMonsterBullet()
{
}

HRESULT CMonsterBullet::Initialize()
{
	m_tInfo.vPos = CObjMgr::Get_Instance()->Get_Player()->Get_Info().vPos;
	m_tInfo.vDir = { 0.f, 1.f, 0.f };
	m_tInfo.vSize = { 10.f, 10.f, 0.f };

	m_fSpeed = 5.f;

	return S_OK;
}

int CMonsterBullet::Update()
{
	if (m_bDead)
		return OBJ_DEAD;



	return OBJ_NOEVENT;
}

void CMonsterBullet::Late_Update()
{
}

void CMonsterBullet::Render(HDC _DC)
{
}

void CMonsterBullet::Release()
{
}
