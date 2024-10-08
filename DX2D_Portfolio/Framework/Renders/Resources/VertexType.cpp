#include "Framework.h"
#include "VertexType.h"

/*
    D3D11_INPUT_ELEMENT_DESC

    SemanticName		: 정점 데이터의 의미를 나타내는 문구
    SemanticIndex		: 위 이름이 중복되는 경우 구분하기 위한 인덱스 값
    Format				: 데이터 형식을 나타냄
    InputSlot			: 입력 슬롯의 인덱스
    AligendByteOffset	: 정점 데이터의 바이트 탄위 오프셋 ( 0 = 자동계산 )
    InputSlotClass		: 사용되는 데이터 형식을 지정
    InstanceDataStepRate: 인스턴스마다 데이터를 읽어들이는데 사용할 스텝 레이트 값
*/

D3D11_INPUT_ELEMENT_DESC VertexColor::descs[]
{
    {"POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0,							0	,D3D11_INPUT_PER_VERTEX_DATA,0 },
    {"COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0,D3D11_APPEND_ALIGNED_ELEMENT	,D3D11_INPUT_PER_VERTEX_DATA,0 },
};

D3D11_INPUT_ELEMENT_DESC VertexTexture::descs[]
{
    {"POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0,							0	,D3D11_INPUT_PER_VERTEX_DATA,0 },
    {"TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,		0,D3D11_APPEND_ALIGNED_ELEMENT	,D3D11_INPUT_PER_VERTEX_DATA,0 },
};

D3D11_INPUT_ELEMENT_DESC VertexTile::descs[]
{
    {"POSITION",0, DXGI_FORMAT_R32G32B32_FLOAT,
    0,							0,
    D3D11_INPUT_PER_VERTEX_DATA,0 },

    {"TEXCOORD",0, DXGI_FORMAT_R32G32_FLOAT,
    0, D3D11_APPEND_ALIGNED_ELEMENT,
    D3D11_INPUT_PER_VERTEX_DATA,0 },

    {"TEXCOORD",1, DXGI_FORMAT_R32G32_FLOAT,
    0, D3D11_APPEND_ALIGNED_ELEMENT,
    D3D11_INPUT_PER_VERTEX_DATA,0 },

    {"COLOR",	0, DXGI_FORMAT_R32G32B32A32_FLOAT,
    0, D3D11_APPEND_ALIGNED_ELEMENT,
    D3D11_INPUT_PER_VERTEX_DATA,0 },

    {"INDEX",	0, DXGI_FORMAT_R32_UINT,
    0, D3D11_APPEND_ALIGNED_ELEMENT,
    D3D11_INPUT_PER_VERTEX_DATA,0 }
};