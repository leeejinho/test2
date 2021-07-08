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

public:
	int Create_Butterfly_Right();
	int Create_Butterfly_Left();

private:
	STATE		m_eCurState;
	bool		m_bDiagonal;		// 대각선
	bool		m_bRotation;		// 회전
	bool		m_bInitialize;

	float		m_fParentX;			// 부모 x축
	float		m_fParentY;			// 부모 y축
};

#endif // !__BUTTERFLY_H__
