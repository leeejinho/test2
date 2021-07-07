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

public:
	int Create_Monster_Left();
	int Create_Monster_Right();

private:
	bool		m_bDiagonal;
	bool		m_bRotation;
	float		m_fParentX;
	float		m_fParentY;

	STATE		m_eCurState;
};

#endif // !__MONSTER_H__
