#ifndef _SYSTEMDEF_H
#define _SYSTEMDEF_H

#include "assert.h"
#include <Windows.h>
#include <d3d11_1.h>
#pragma comment (lib,"d3d11.lib")

#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <vector>
#include <list>
#include <map>
#include <string>



//DirextX 폰트용 헤더
#include <d2d1_2.h>
#include <dwrite.h>
#pragma comment(lib,"d2d1.lib")
#pragma comment(lib,"dwrite.lib")

//DirextX 폰트용

//XM은 11버전부터 쓰는 벡터 행렬 연산 관련
#include <DirectXMath.h>//directx 수학 함수

#include <DirectXCollision.h>//directx 충돌 관련
using namespace std;
using namespace DirectX;
using namespace DirectX::TriangleTests;

typedef XMFLOAT4 Float4;
typedef XMFLOAT3 Float3;
typedef XMFLOAT2 Float2;
typedef XMVECTOR Vector4;
typedef XMMATRIX Matrix;
typedef XMFLOAT4X4 Float4x4;


//우리가 추가할 헤더
#include "SystemMcr.h"
#include "SystemConst.h"
#include "SystemStruct.h"

// 
//c++프로젝트인지 확인
#ifdef __cplusplus
#define EXTERN extern "C" //c++프로젝트면 C언어로 변경
#else
#define EXTERN
#endif

//dll로 만드는 애들은 export
//dll을 사용하는 애들은 import
#ifdef SYSTEM_EXPORT
#define SYSTEM_DLL _declspec (dllexport)
#else
#define SYSTEM_DLL _declspec (dllimport)
#endif // SYSTEM_EXPORT

#endif