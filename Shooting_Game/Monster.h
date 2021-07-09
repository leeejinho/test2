#pragma once
#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "Obj.h"
class CMonster : public CObj
{
public:
	enum STATE { LEFT, RIGHT, END};

public:
	CMonster();
	virtual ~CMonster();

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
	int Create_Monster_Left();
	int Create_Monster_Right();

	void Monster_Descent();


private:
	DWORD		m_dwDescent;
	bool		m_bDescentRot;

	bool		m_bDiagonal;		// 대각선 
	bool		m_bRotation;		// 회전
	float		m_fParentX;			// 부모 x축
	float		m_fParentY;			// 부모 y축
	bool		m_bStop;
	D3DXVECTOR3	m_pTargetPos;

	STATE		m_eCurState;
};

#endif // !__MONSTER_H__
