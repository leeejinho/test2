#pragma once
#ifndef __INCLUDE_H__
#define __INCLUDE_H__

#include "Define.h"
#include "Extern.h"
#include "Struct.h"
#include "Function.h"
#include "Enum.h"
#include "AbstractFactory.h"

#endif // !__INCLUDE_H__


#ifdef _DEBUG

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifndef DBG_NEW 

#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
#define new DBG_NEW 

#endif

#endif // _DEBUG