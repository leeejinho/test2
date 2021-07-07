#pragma once
#ifndef __STRUCT_H__
#define __STRUCT_H__

typedef struct tagInfo
{
	tagInfo() { ZeroMemory(this, sizeof(tagInfo)); }

	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vDir;
	D3DXVECTOR3 vSize;
}INFO;


#endif // !__STRUCT_H__
