#include "stdafx.h"
#include "Bullet.h"
#include "ObjMgr.h"

CBullet::CBullet()
{
}


CBullet::~CBullet()
{
}

HRESULT CBullet::Initialize()
{
	m_tInfo.vPos = CObjMgr::Get_Instance()->Get_Player()->Get_Info().vPos;
	m_tInfo.vDir = { 0.f, 1.f, 0.f };
	m_tInfo.vSize = { 10.f, 10.f, 0.f };

	m_fSpeed = 5.f;

	return S_OK;
}

int CBullet::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;

	return OBJ_NOEVENT;
}

void CBullet::Late_Update()
{
	if (m_tInfo.vPos.y < 0)
		m_bDead = true;
}

void CBullet::Render(HDC _DC)
{
	RECT rc{};
	rc.left = LONG(m_tInfo.vPos.x - (m_tInfo.vSize.x * 0.5f));
	rc.top = LONG(m_tInfo.vPos.y - (m_tInfo.vSize.x * 0.5f));
	rc.right = LONG(m_tInfo.vPos.x + (m_tInfo.vSize.x * 0.5f));
	rc.bottom = LONG(m_tInfo.vPos.y + (m_tInfo.vSize.x * 0.5f));

	Ellipse(_DC, rc.left, rc.top, rc.right, rc.bottom);
}

void CBullet::Release()
{
}
