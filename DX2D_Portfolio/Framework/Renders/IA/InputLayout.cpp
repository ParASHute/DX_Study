#include "Framework.h"
#include "InputLayout.h"

InputLayout::~InputLayout()
{
	SAFE_RELEASE(inputLayout);
}

void InputLayout::Create(D3D11_INPUT_ELEMENT_DESC* descs, uint count, ID3DBlob* blob)
{
	// 1도 없음 예술(폭팔) ㄱㄱ
	if (!descs || !count || !blob) CHECK(false);

	HRESULT hr = DEVICE->CreateInputLayout
	(
		descs,	// 설계도
		count,	// 요소 개수

		// bolb은 메모리 블록이다 
		// 안에는 버퍼의 다양한 데이터가 들어있다.
		blob->GetBufferPointer(),	
		blob->GetBufferSize(),
		&inputLayout

	);
}

void InputLayout::SetIA()
{
	DC->IASetInputLayout(inputLayout);
}
