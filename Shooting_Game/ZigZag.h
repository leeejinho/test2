#pragma once
#ifndef __CZIGZAG__H_
#define __CZIGZAG__H_
#include "Obj.h"
class CZigZag :
	public CObj
{
public:
	CZigZag();
	virtual ~CZigZag();

	// CObj을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;


public:
	void		Set_Left() { m_bLeft = true; }
	void		myPattern();
private:
	D3DXVECTOR3 m_ChangePos[2];
	int			m_PatternNum;
	bool		m_bLeft;
};


#endif //__CZIGZAG__H_

