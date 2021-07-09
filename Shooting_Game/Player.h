#pragma once
#include "Obj.h"
#ifndef __PLAYER_H__
#define __PLAYER_H__
class CPlayer :
	public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();

	// CObj을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;



private:
	D3DXMATRIX matScale, matRotZ, matTrans, matWorld;
	void WriteMatrix();
	void KeyCheck();
	void OffSet();


private:
	float fScaleX, fScaleY;

private:
	void Create_Shield();
	void Create_Bullet();


};

#endif //__PLAYER_H__

