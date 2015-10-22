// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

//#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C�� ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <d3d11.h>
#include <d3dx11.h>
#include <D3DX10Math.h>
#include <d3dcompiler.h>
#include <xnamath.h>

#include <D3D9Types.h>

#include <Mmsystem.h>

#include <vector>
#include <fbxsdk.h>
#include <PxPhysicsAPI.h>
#include <iostream>



#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console" )
/*
#pragma comment(lib, "PhysX3_x86.lib")
#pragma comment(lib, "PhysX3Common_x86.lib")
#pragma comment(lib, "PhysX3Extensions.lib")
*/
using namespace physx;
using namespace std;

#define GET_SET_FUNC_IMPL(TYPE, FUNC_NAME, PROP) \
	TYPE Get##FUNC_NAME() \
	{ \
		return PROP; \
	} \
	void Set##FUNC_NAME(TYPE _PROP) \
	{ \
		PROP = _PROP; \
	}
// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
#define PS_SLOT_LIGHT		0x00
#define PS_SLOT_MATERIAL	0x01

#define PS_SLOT_TEXTURE		0x00
#define PS_SLOT_SAMPLER_STATE		0x00


#define VS_SLOT_VIEWPROJECTION_MATRIX	0x00
#define VS_SLOT_WORLD_MATRIX			0x01

#define MAX_BONE 60
