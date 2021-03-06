#pragma once

#ifndef __ENGINE_INCLUDE_H__

/*
Standard
*/
#include <list>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <functional>
#pragma warning(disable : 4251)	// stl

#include <cassert>

#ifdef _DEBUG
#include <iostream>	// 디버그용 콘솔창 출력
#endif // _DEBUG

using namespace std;

/*
dx9
*/
#include <d3d9.h>
#include <d3dx9.h>

/*
User
*/
#include "Engine_Define.h"
#include "Engine_Typedef.h"
#include "Engine_Enum.h"
#include "Engine_Struct.h"
#include "Engine_Function.h"

#define __ENGINE_INCLUDE_H__
#endif