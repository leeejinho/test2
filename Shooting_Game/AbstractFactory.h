#pragma once


#ifndef __ABSTRACTFACTORY_H__
#define __ABSTRACTFACTORY_H__

class CObj;
template <typename T>
class CAbstractFactory {
public:
	static CObj* Create() {
		CObj* pObj = new T;
		pObj->Initialize();

		return pObj;
	}

	static CObj* Create(float _fX, float _fY) {
		CObj* pObj = new T;
		pObj->Set_Pos(_fX, _fY);
		pObj->Initialize();

		return pObj;
	}	
};
#endif
#pragma once
