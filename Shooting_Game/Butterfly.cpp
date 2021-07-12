#include "stdafx.h"
#include "Butterfly.h"
#include "StageMgr.h"
#include "DeadEffect.h"
#include "ObjMgr.h"
#include "MonsterBullet.h"
#include "StageMgr.h"


CButterfly::CButterfly()
	:m_eCurState(END), m_bDiagonal(true), m_bRotation(true), m_fParentX(0.f), m_fParentY(0.f), m_bInitialize(true), m_dwDescent(0), m_bStop(false), m_bDescentRot(true)
	, m_fDouble(0.f)
{
	ZeroMemory(&m_pTargetPos, sizeof(D3DXVECTOR3));
}


CButterfly::~CButterfly()
{
	Release();
}

HRESULT CButterfly::Initialize()
{
	m_tInfo.vPos = { 0.f, 500.f, 0.f };
	m_tInfo.vDir = D3DXVECTOR3(1.f, 1.f, 0.f);
	m_tInfo.vSize = D3DXVECTOR3(30.f, 40.f, 0.f);

	m_vP[0] = { -m_tInfo.vSize.x * 0.5f, -m_tInfo.vSize.y * 0.5f, 0.f };
	m_vP[1] = { m_tInfo.vSize.x * 0.5f, -m_tInfo.vSize.y * 0.5f, 0.f };
	m_vP[2] = { m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f };
	m_vP[3] = { -m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f };

	m_vP[4] = { 0.f, 0.f, 0.f };


	m_fDouble = 25.f * sqrtf(2);


	m_fSpeed = 2.f + CStageMgr::Get_Instance()->Get_Stage();
	m_Delay = rand() & 3000 + 2000;

	return S_OK;
}

int CButterfly::Update()
{
	CheckPos_Dead();
	int i = 0;
	if (m_bDead)
	{
		Play_Dead_Effect(this);
		return OBJ_DEAD;
	}

	if (!m_bStop)
	{
		if (m_eCurState == LEFT || m_eCurState == DOUBLE_LEFT)
			Create_Butterfly_Left();
		if (m_eCurState == RIGHT || m_eCurState == DOUBLE_RIGHT)
			Create_Butterfly_Right();
	}
	else
		Monster_Descent();

	return OBJ_NOEVENT;
}

void CButterfly::Late_Update()
{
}

void CButterfly::Render(HDC _DC)
{
	MoveToEx(_DC, (int)m_vQ[0].x, (int)m_vQ[0].y, nullptr);

	for (int i = 1; i < 4; ++i)
		LineTo(_DC, (int)m_vQ[i].x, (int)m_vQ[i].y);
	LineTo(_DC, (int)m_vQ[0].x, (int)m_vQ[0].y);


}

void CButterfly::Release()
{
}

int CButterfly::Create_Butterfly_Right()
{

	D3DXMATRIX matParentTrans;

	D3DXMATRIX matScale, matRotZ, matTrans, matRelRotZ, matWorld;
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	D3DXMatrixRotationZ(&matRelRotZ, D3DXToRadian(m_fAngle));

	if (m_bInitialize)			// 한번만 초기화
	{
		if(m_eCurState == RIGHT)
			m_tInfo.vPos = { 800.f , 500.f, 0.f };
		if (m_eCurState == DOUBLE_RIGHT)
			m_tInfo.vPos = { 800.f - m_fDouble, 500.f + m_fDouble, 0.f };
		m_bInitialize = false;
	}

	if (m_bDiagonal)				// 대각선
	{
		m_fAngle = 135.f;
		matWorld = matRotZ * matTrans;
		m_tInfo.vPos.x -= m_fSpeed;
		m_tInfo.vPos.y -= m_fSpeed;

		if (m_bDiagonal && m_tInfo.vPos.y <= 350.f && m_eCurState == RIGHT)
		{
			m_bDiagonal = false;
			m_fAngle = 180.f;
		}

		if (m_tInfo.vPos.y <= 410.f && m_eCurState == DOUBLE_RIGHT && m_bDiagonal)
		{
			m_bDiagonal = false;
			m_fAngle = 130.f;
		}


	}
	if (!m_bDiagonal)
	{
		D3DXMatrixTranslation(&matParentTrans, m_fParentX, m_fParentY, 0.f);

		if (m_bRotation)				// 회전
		{
			m_fParentX = 700.f;
			m_fParentY = 350.f;
			if (m_eCurState == RIGHT)
				m_tInfo.vPos = { 50.f, 0.f, 0.f };
			if (m_eCurState == DOUBLE_RIGHT)
				m_tInfo.vPos = { 90.f, 0.f, 0.f };
			matWorld = matTrans * matRelRotZ * matParentTrans;
			if (m_fAngle < 540.f)
				m_fAngle += m_fSpeed;
			else
			{
				m_bRotation = false;
				m_tInfo.vPos = m_vQ[4];
			}
		}
		else					// 회전후 올라감
		{
			matWorld = matTrans;
			if (m_tInfo.vPos.y >= 250.f)
				m_tInfo.vPos.y -= m_fSpeed;

			else
			{
				m_tInfo.vDir = m_pTargetPos - m_tInfo.vPos;
				float fDist = D3DXVec3Length(&m_tInfo.vDir);
				D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);

				if (fDist > 3.f)
					m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
				else
				{
					m_tInfo.vPos = m_pTargetPos;
					m_bStop = true;
					m_fAngle = 0.f;
					m_vP[4] = { 0.f, 0.f, 0.f };
					m_dwDescent = GetTickCount();
				}

			}
		}
	}

	for (int i = 0; i < 5; ++i)
		D3DXVec3TransformCoord(&m_vQ[i], &m_vP[i], &matWorld);

	return 0;
}

int CButterfly::Create_Butterfly_Left()
{
	D3DXMATRIX matParentTrans;

	D3DXMATRIX matScale, matRotZ, matTrans, matRelRotZ, matWorld;
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	D3DXMatrixRotationZ(&matRelRotZ, D3DXToRadian(m_fAngle));
	if (m_bInitialize)			// 한번만 초기화
	{
		if (m_eCurState == LEFT)
			m_tInfo.vPos = { 0.f , 500.f, 0.f };
		if (m_eCurState == DOUBLE_LEFT)
			m_tInfo.vPos = { 0.f + m_fDouble, 500.f + m_fDouble, 0.f };
		m_bInitialize = false;
	}
	if (m_bDiagonal)				// 대각선
	{
		m_fAngle = 45.f;
		matWorld = matRotZ * matTrans;
		m_tInfo.vPos.x += m_fSpeed;
		m_tInfo.vPos.y -= m_fSpeed;


		if (m_bDiagonal && m_tInfo.vPos.y <= 350.f && m_eCurState == LEFT)
		{
			m_bDiagonal = false;
			m_fAngle = 180.f;
		}

		if (m_bDiagonal && m_tInfo.vPos.y <= 410.f && m_eCurState == DOUBLE_LEFT)
		{
			m_bDiagonal = false;
			m_fAngle = 230.f;
		}
	}
	if (!m_bDiagonal)
	{
		D3DXMatrixTranslation(&matParentTrans, m_fParentX, m_fParentY, 0.f);

		if (m_bRotation)				// 회전
		{
			m_fParentX = 100.f;
			m_fParentY = 350.f;
			if (m_eCurState == LEFT)
				m_tInfo.vPos = { -50.f, 0.f, 0.f };
			if (m_eCurState == DOUBLE_LEFT)
				m_tInfo.vPos = { -90.f, 0.f, 0.f };
			matWorld = matTrans * matRelRotZ * matParentTrans;
			if (m_fAngle > -180.f)
				m_fAngle -= m_fSpeed;
			else
			{
				m_bRotation = false;
				m_tInfo.vPos = m_vQ[4];
			}
		}
		else					// 회전후 올라감
		{
			matWorld = matTrans;
			if (m_tInfo.vPos.y >= 250.f)
				m_tInfo.vPos.y -= m_fSpeed;

			else
			{
				m_tInfo.vDir = m_pTargetPos - m_tInfo.vPos;
				float fDist = D3DXVec3Length(&m_tInfo.vDir);
				D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
				if (fDist > 3.f)
					m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
				else
				{
					m_tInfo.vPos = m_pTargetPos;
					m_bStop = true;
					m_fAngle = 0.f;
					m_vP[4] = { 0.f, 0.f, 0.f };
					m_dwDescent = GetTickCount();
				}

			}
		}
	}

	for (int i = 0; i < 5; ++i)
		D3DXVec3TransformCoord(&m_vQ[i], &m_vP[i], &matWorld);

	return 0;
}

void CButterfly::Monster_Descent()
{
	D3DXMATRIX matParentTrans;
	D3DXMATRIX matTrans, matRelRotZ, matWorld;
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	int iCount = 0;

	if (m_dwDescent + m_Delay < GetTickCount())
	{
		if (m_bDescentRot)
		{
			m_fAngle += m_fSpeed;
			if (m_tInfo.vPos.x < (WINCX >> 1))
			{
				D3DXMatrixTranslation(&matTrans, 50.f, 0.f, 0.f);
				D3DXMatrixTranslation(&matParentTrans, m_tInfo.vPos.x - 50.f, m_tInfo.vPos.y, 0.f);
				D3DXMatrixRotationZ(&matRelRotZ, D3DXToRadian(-m_fAngle));
			}
			else
			{
				D3DXMatrixTranslation(&matTrans, -50.f, 0.f, 0.f);
				D3DXMatrixTranslation(&matParentTrans, m_tInfo.vPos.x + 50.f, m_tInfo.vPos.y, 0.f);
				D3DXMatrixRotationZ(&matRelRotZ, D3DXToRadian(m_fAngle));
			}
			matWorld = matTrans * matRelRotZ * matParentTrans;

			if (m_fAngle > 180)
			{
				m_tInfo.vPos = m_vQ[4];
				if (!CObjMgr::Get_Instance()->Get_List(OBJID::PLAYER).empty())
					m_tInfo.vDir = CObjMgr::Get_Instance()->Get_Player()->Get_Info().vPos - m_vQ[4];
				else
					m_tInfo.vDir = { 0.f, 1.f, 0.f };
				D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
				for (int i = 0; i < 3; ++i)
				{
					CObj* pObj = CAbstractFactory<CMonsterBullet>::Create(m_tInfo.vPos.x, m_tInfo.vPos.y);
					CObjMgr::Get_Instance()->Add_Object(pObj, OBJID::MONSTERBULLIT);
					
				}
				m_bDescentRot = !m_bDescentRot;
			}
		}
		else
		{
			m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
			D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
			matWorld = matTrans;
		}
	}
	else
	{
		D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
		matWorld = matTrans;
	}

	for (int i = 0; i < 5; ++i)
		D3DXVec3TransformCoord(&m_vQ[i], &m_vP[i], &matWorld);

	if (m_tInfo.vPos.y > WINCY + 200)
		m_bDead = true;
}
