#include "Framework.h"
#include "IndexBuffer.h"

IndexBuffer::~IndexBuffer()
{
	SAFE_RELEASE(buffer);
}

void IndexBuffer::Create(const vector<uint>& indices, const D3D11_USAGE& usage)
{
	stride = sizeof(uint);	// 정점 크기 저장
	count = indices.size();
	D3D11_BUFFER_DESC desc;		//desc는 프로그래머가 원하는 목적에 따라 사용할 DX데이터를 만들기 위한 구조체
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC)); // desc 메모리 초기화

	//desc 설정
	{
		// 사용 용도 
		desc.Usage = usage;

		// 사용 목적
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

		// 버퍼 크기
		desc.ByteWidth = stride * count;

		//cpu 접근 설정(글카는 다 접근 가능)
		switch (usage)
		{
		case D3D11_USAGE_DEFAULT:
			// gpu만 수정 할 수 있는 버퍼(cpu접근 불가)

		case D3D11_USAGE_IMMUTABLE:
			// 글카에서 접근 할 수는 있지만 수정은 불가한 버퍼
			break;

		case D3D11_USAGE_DYNAMIC:
			// cpu만 접근, 수정가능 버퍼
			desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			break;

		case D3D11_USAGE_STAGING:
			// cpu접근 가능 cpu,글카 다 수정가능 버퍼
			desc.CPUAccessFlags =
				D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;
			break; // 브레이크 안걸었음
		}
	}

	// 버퍼 생성
	{
		D3D11_SUBRESOURCE_DATA subData; // 다영한 데이터를 임시로 보관하는 구조체
		ZeroMemory(&subData, sizeof(D3D11_SUBRESOURCE_DATA));

		subData.pSysMem = indices.data();

		/*
			HR~은 해당 작업이 정상적으로 수행 됐는지 판단하는 자료형
			작업이 끝난 변수를 CHECK에 넣어
			작업이 정상적으로 진행되지 않았다면 에러메세지를 출력한다
		*/ 
		HRESULT hr = DEVICE->CreateBuffer(&desc, &subData, &buffer);
		CHECK(hr);
	}
}


void IndexBuffer::SetIA()
{
	// 정점 개수를 32비트로 설정
	DC->IASetIndexBuffer(buffer, DXGI_FORMAT_R32_UINT, offset);
}
