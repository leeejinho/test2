#include "stdafx.h"
#include "Monster.h"
#include "MonsterBullet.h"
#include "ObjMgr.h"

CMonster::CMonster()
	: m_bDiagonal(true), m_bRotation(true), m_fParentX(0.f), m_fParentY(0.f), m_eCurState(END)
{
}


CMonster::~CMonster()
{
	Release();
}

HRESULT CMonster::Initialize()
{
	m_tInfo.vPos = { 400.f, 0.f, 0.f };
	m_tInfo.vDir = D3DXVECTOR3(1.f, 1.f, 0.f);
	m_tInfo.vSize = D3DXVECTOR3(40.f, 40.f, 0.f);

	m_vP[0] = { -m_tInfo.vSize.x * 0.5f, -m_tInfo.vSize.y * 0.5f, 0.f };
	m_vP[1] = { m_tInfo.vSize.x * 0.5f, -m_tInfo.vSize.y * 0.5f, 0.f };
	m_vP[2] = { m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f };
	m_vP[3] = { -m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f };


	m_fSpeed = 2.f;

	return S_OK;
}

int CMonster::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	if(m_eCurState == LEFT)
		Create_Monster_Left();
	if(m_eCurState == RIGHT)
		Create_Monster_Right();

	return OBJ_NOEVENT;
}

void CMonster::Late_Update()
{
}

void CMonster::Render(HDC _DC)
{
	MoveToEx(_DC, (int)m_vQ[0].x, (int)m_vQ[0].y, nullptr);

	for (int i = 1; i < 4; ++i)
		LineTo(_DC, (int)m_vQ[i].x, (int)m_vQ[i].y);
	LineTo(_DC, (int)m_vQ[0].x, (int)m_vQ[0].y);


}

void CMonster::Release()
{
}

int CMonster::Create_Monster_Left()
{
	D3DXMATRIX matParentTrans;

	D3DXMATRIX matScale, matRotZ, matTrans, matRelRotZ, matWorld;
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	D3DXMatrixRotationZ(&matRelRotZ, D3DXToRadian(m_fAngle));

	//matWorld = matScale * matRotZ * matTrans * matRelRotZ/* * matParentTrans*/;
	if (m_bDiagonal)				// �밢��
	{
		matWorld = matTrans;
		m_tInfo.vPos.x -= m_fSpeed;
		m_tInfo.vPos.y += m_fSpeed;
		
	}
	if (m_tInfo.vPos.y > 300.f && m_tInfo.vPos.x < 100.f)
		m_bDiagonal = false;
	
	if (!m_bDiagonal)
	{
			D3DXMatrixTranslation(&matParentTrans, m_fParentX, m_fParentY, 0.f);

		if (m_bRotation)				// ȸ��
		{
			m_fParentX = 195.f;
			m_fParentY = 300.f;
			m_tInfo.vPos = { -100.f, 0.f, 0.f };
			matWorld = matTrans * matRelRotZ * matParentTrans;
			if (m_fAngle > -180.f)
				m_fAngle -= m_fSpeed;
			else
			{
				m_bRotation = false;
				m_tInfo.vPos = { 100.f, 0.f, 0.f };
			}
			
		}
		else					// ȸ���� �ö�
		{
			m_tInfo.vPos = { 100.f, 0.f, 0.f };
			matWorld = matTrans * matParentTrans;
			if(m_fParentY >= 50.f)
				m_fParentY -= m_fSpeed;
		}
	}

	for (int i = 0; i < 4; ++i)
		D3DXVec3TransformCoord(&m_vQ[i], &m_vP[i], &matWorld);
	CObj* pObj = CAbstractFactory<CMonsterBullet>::Create(m_tInfo.vPos.x, m_tInfo.vPos.y);
	CObjMgr::Get_Instance()->Add_Object(pObj, OBJID::BULLIT);
	return 0;
}

int CMonster::Create_Monster_Right()
{
	D3DXMATRIX matParentTrans;

	D3DXMATRIX matScale, matRotZ, matTrans, matRelRotZ, matWorld;
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	D3DXMatrixRotationZ(&matRelRotZ, D3DXToRadian(m_fAngle));

	//matWorld = matScale * matRotZ * matTrans * matRelRotZ/* * matParentTrans*/;
	if (m_bDiagonal)				// �밢��
	{
		matWorld = matTrans;
		m_tInfo.vPos.x += m_fSpeed;
		m_tInfo.vPos.y += m_fSpeed;
		CObj* pObj = CAbstractFactory<CMonsterBullet>::Create(m_tInfo.vPos.x, m_tInfo.vPos.y);
		CObjMgr::Get_Instance()->Add_Object(pObj, OBJID::BULLIT);
	}
	if (m_tInfo.vPos.y > 300.f && m_tInfo.vPos.x > 700.f)
		m_bDiagonal = false;

	if (!m_bDiagonal)
	{
		D3DXMatrixTranslation(&matParentTrans, m_fParentX, m_fParentY, 0.f);

		if (m_bRotation)				// ȸ��
		{
			m_fParentX = 602.f;
			m_fParentY = 300.f;
			m_tInfo.vPos = { 100.f, 0.f, 0.f };
			matWorld = matTrans * matRelRotZ * matParentTrans;
			if (m_fAngle < 180.f)
				m_fAngle += m_fSpeed;
			else
			{
				m_bRotation = false;
				m_tInfo.vPos = { -100.f, 0.f, 0.f };
			}
		}
		else					// ȸ���� �ö�
		{
			m_tInfo.vPos = {- 100.f, 0.f, 0.f };
			matWorld = matTrans * matParentTrans;
			if (m_fParentY >= 50.f)
				m_fParentY -= m_fSpeed;
		}
	}

	for (int i = 0; i < 4; ++i)
		D3DXVec3TransformCoord(&m_vQ[i], &m_vP[i], &matWorld);

	return 0;
}

