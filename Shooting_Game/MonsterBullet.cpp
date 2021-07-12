#include "stdafx.h"
#include "MonsterBullet.h"
#include "ObjMgr.h"
#include "StageMgr.h"

CMonsterBullet::CMonsterBullet()
{
}


CMonsterBullet::~CMonsterBullet()
{
}

HRESULT CMonsterBullet::Initialize()
{
	if (!CObjMgr::Get_Instance()->Get_List(OBJID::PLAYER).empty())
		m_tInfo.vDir = CObjMgr::Get_Instance()->Get_Player()->Get_Info().vPos - m_tInfo.vPos;
	else
		m_tInfo.vDir = { 0.f, 1.f, 0.f };

	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
	m_tInfo.vSize = { 10.f, 10.f, 0.f };

	m_fSpeed = 4.5f + CStageMgr::Get_Instance()->Get_Stage();
	

	return S_OK;
}

int CMonsterBullet::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;

	return OBJ_NOEVENT;
}

void CMonsterBullet::Late_Update()
{
	if (m_tInfo.vPos.y > WINCY + (m_tInfo.vSize.y * 0.5f))
		m_bDead = true;
}

void CMonsterBullet::Render(HDC _DC)
{
	RECT rc{};
	rc.left = LONG(m_tInfo.vPos.x - (m_tInfo.vSize.x * 0.5f));
	rc.top = LONG(m_tInfo.vPos.y - (m_tInfo.vSize.x * 0.5f));
	rc.right = LONG(m_tInfo.vPos.x + (m_tInfo.vSize.x * 0.5f));
	rc.bottom = LONG(m_tInfo.vPos.y + (m_tInfo.vSize.x * 0.5f));

	Ellipse(_DC, rc.left, rc.top, rc.right, rc.bottom);
}

void CMonsterBullet::Release()
{
}
