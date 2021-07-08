#include "stdafx.h"
#include "Player.h"
#include "Shield.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "Bullet.h"


CPlayer::CPlayer()
	:isBomb(false), fScaleX(0), fScaleY(0)
{
}


CPlayer::~CPlayer()
{
}

HRESULT CPlayer::Initialize()
{
	m_tInfo.vPos = { WINCX >> 1, WINCY - 50.f, 0.f };
	m_tInfo.vDir = { 1.f, 0.f, 0.f };
	m_tInfo.vSize = { 80.f, 80.f, 0.f };

	m_fSpeed = 5.f;
	fScaleX = 1.f;
	fScaleY = 1.f;

	m_vP[0] = { -m_tInfo.vSize.x * 0.5f, -m_tInfo.vSize.y * 0.5f, 0.f };
	m_vP[1] = { m_tInfo.vSize.x * 0.5f, -m_tInfo.vSize.y * 0.5f, 0.f };
	m_vP[2] = { m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f };
	m_vP[3] = { -m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f };

	return S_OK;
}

int CPlayer::Update()
{
	KeyCheck();
	OffSet();
	WriteMatrix();
	return 0;
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

	Ellipse(_DC, int(m_tInfo.vPos.x - m_tInfo.vSize.x * 0.2f), int(m_tInfo.vPos.y - m_tInfo.vSize.y * 0.2f),
		int(m_tInfo.vPos.x + m_tInfo.vSize.x * 0.2f), int(m_tInfo.vPos.y + m_tInfo.vSize.y * 0.2f));
}

void CPlayer::Release()
{
}

void CPlayer::WriteMatrix()
{
	if (!isBomb)
	{
		if (fScaleX > 1.0f)
		{
			fScaleX -= 0.04f;
			fScaleY -= 0.04f;
		}
		D3DXMatrixScaling(&matScale, fScaleX, fScaleY, 0.f);
	}

	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(0.f));
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	matWorld = matScale * matRotZ * matTrans;

	for (int i = 0; i < 4; ++i)
		D3DXVec3TransformCoord(&m_vQ[i], &m_vP[i], &matWorld);
}

void CPlayer::KeyCheck()
{
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
	{
		m_tInfo.vPos += -m_tInfo.vDir * m_fSpeed;
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
	{
		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
	{
		m_tInfo.vPos += -D3DXVECTOR3(0.f, 1.f, 0.f) * m_fSpeed;
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
	{
		m_tInfo.vPos += D3DXVECTOR3(0.f, 1.f, 0.f) * m_fSpeed;
	}

	if (CKeyMgr::Get_Instance()->Key_Down('A'))
		Create_Bullet();

	if (CKeyMgr::Get_Instance()->Key_Down('S'))
		isBomb = true;

	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
		Create_Shield();


	if (isBomb)
		myBombTest();

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
	CObj* pObj = CAbstractFactory<CShield>::Create();
	static_cast<CShield*>(pObj)->Set_Player(this);
	CObjMgr::Get_Instance()->Add_Object(pObj, OBJID::SKILL);
}

void CPlayer::Create_Bullet()
{
	if (CObjMgr::Get_Instance()->Get_List(OBJID::BULLIT).size() > (size_t)4)	// 총알 수 제한	(몬스터 bullet이 추가되면 OBJID 수정해야될수도)
		return;

	CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CBullet>::Create(), OBJID::BULLIT);
}

void CPlayer::myBombTest()
{
	if (fScaleX <= 5.f)
	{
		fScaleX += 0.1f;
		fScaleY += 0.1f;
	}

	if (fScaleX >= 4.98f)
		isBomb = false;

	D3DXMatrixScaling(&matScale, fScaleX, fScaleY, 0.f);
}
