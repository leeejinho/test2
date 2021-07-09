#pragma once
#ifndef __BUTTERFLY_H__
#define __BUTTERFLY_H__

#include "Obj.h"
class CButterfly : public CObj
{
public:
	enum STATE { LEFT, RIGHT, END };

public:
	CButterfly();
	virtual ~CButterfly();

public:
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

public:
	void Set_State(STATE _eState) { m_eCurState = _eState; }
	void Set_TargetPos(D3DXVECTOR3 m_vec) { m_pTargetPos = m_vec; }

public:
	int Create_Butterfly_Right();
	int Create_Butterfly_Left();
	void Monster_Descent();


private:
	DWORD		m_dwDescent;
	bool		m_bDescentRot;
	bool		m_bStop;

	STATE		m_eCurState;
	bool		m_bDiagonal;		// �밢��
	bool		m_bRotation;		// ȸ��
	bool		m_bInitialize;
	D3DXVECTOR3	m_pTargetPos;

	float		m_fParentX;			// �θ� x��
	float		m_fParentY;			// �θ� y��
};

#endif // !__BUTTERFLY_H__
