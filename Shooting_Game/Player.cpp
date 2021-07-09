#include "stdafx.h"
#include "Player.h"
#include "Bomb.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "Bullet.h"


CPlayer::CPlayer()
	: fScaleX(0), fScaleY(0)
{
}


CPlayer::~CPlayer()
{
}

HRESULT CPlayer::Initialize()
{
	m_tInfo.vPos = { WINCX >> 1, WINCY - 50.f, 0.f };
	m_tInfo.vDir = { 1.f, 0.f, 0.f };
	m_tInfo.vSize = { 60.f, 60.f, 0.f };

	m_fSpeed = 5.f;
	fScaleX = 1.f;
	fScaleY = 1.f;

	m_vP[0] = { -m_tInfo.vSize.x * 0.5f, -m_tInfo.vSize.y * 0.5f, 0.f };
	m_vP[1] = { m_tInfo.vSize.x * 0.5f, -m_tInfo.vSize.y * 0.5f, 0.f };
	m_vP[2] = { m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f };
	m_vP[3] = { -m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f };
	m_vP[4] = { 0.f, 0.f, 0.f };

	return S_OK;
}

int CPlayer::Update()
{
	if (m_bDead)
	{
		Play_Dead_Effect(this);
		return OBJ_DEAD;
	}

	KeyCheck();
	OffSet();
	WriteMatrix();
	return OBJ_NOEVENT;
}

void CPlayer::Late_Update()
{
}

void CPlayer::Render(HDC _DC)
{
	MoveToEx(_DC, (int)m_vQ[0].x, (int)m_vQ[0].y, nullptr);

	for (int i = 1; i < 4; ++i)
		LineTo(_DC, (int)m_vQ[i].x, (int)m_vQ[i].y);
	LineTo(_DC, (int)m_vQ[0].x, (int)m_vQ[0].y);

	Ellipse(_DC, int(m_tInfo.vPos.x - m_tInfo.vSize.x * 0.4f), int(m_tInfo.vPos.y - m_tInfo.vSize.y * 0.4f),
		int(m_tInfo.vPos.x + m_tInfo.vSize.x * 0.4f), int(m_tInfo.vPos.y + m_tInfo.vSize.y * 0.4f));
}

void CPlayer::Release()
{
}

void CPlayer::WriteMatrix()
{

	D3DXMatrixScaling(&matScale, fScaleX, fScaleY, 0.f);
	

	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(0.f));
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	matWorld = matScale * matRotZ * matTrans;

	for (int i = 0; i < 5; ++i)
		D3DXVec3TransformCoord(&m_vQ[i], &m_vP[i], &matWorld);
}

void CPlayer::KeyCheck()
{
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
		m_tInfo.vPos += -m_tInfo.vDir * m_fSpeed;

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
	

	if (CKeyMgr::Get_Instance()->Key_Down('A'))
		Create_Bullet();

	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
		Create_Shield();
}

void CPlayer::OffSet()
{
	if (m_tInfo.vPos.x < m_tInfo.vSize.x)
		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;

	if (m_tInfo.vPos.x > WINCX - m_tInfo.vSize.x)
		m_tInfo.vPos += -m_tInfo.vDir * m_fSpeed;
}

void CPlayer::Create_Shield()
{
	CObj* pObj = CAbstractFactory<CBomb>::Create();
	static_cast<CBomb*>(pObj)->Set_Player(this);
	CObjMgr::Get_Instance()->Add_Object(pObj, OBJID::SKILL);
}

void CPlayer::Create_Bullet()
{
	if (CObjMgr::Get_Instance()->Get_List(OBJID::BULLIT).size() > (size_t)4)	// 총알 수 제한	(몬스터 bullet이 추가되면 OBJID 수정해야될수도)
		return;

	CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CBullet>::Create(), OBJID::BULLIT);
}

