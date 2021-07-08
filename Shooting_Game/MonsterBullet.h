#pragma once
#ifndef __MONSTERBULLET_H__
#define __MONSTERBULLET_H__
#include "Obj.h"
class CMonsterBullet : public CObj
{
public:
	explicit CMonsterBullet();
	virtual ~CMonsterBullet();

public:


public:
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

};

#endif