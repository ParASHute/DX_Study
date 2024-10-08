#pragma once
#include "Framework.h"

// 정점 데이터 이외의 데이터를 cpu에서 gpu로 넘겨줄때 사용할 버퍼
// 상속 해줄 객체(부모)
class ShaderBuffer {
public:
	void SetVSBuffer(uint slot) {
		// 데이터 복사
		MapData();

		// PS에서 사용할 데이터를 1개 넘겨주겠다.
		DC->VSSetConstantBuffers(slot, 1, &buffer);
	}

	void SetPSBuffer(uint slot) {
		// 데이터 복사
		MapData();

		// PS에서 사용할 데이터를 1개 넘겨주겠다.
		DC->PSSetConstantBuffers(slot, 1, &buffer);
	} 

protected:
	// 글카가 정점 이외의 데이터를 받을땐 상수버퍼를 사용해 받는다.
	ShaderBuffer(void* data, uint dataSize) : data(data), dataSize(dataSize) {
		// 사용용도 
		desc.Usage = D3D11_USAGE_DYNAMIC;

		// 버퍼 크기
		desc.ByteWidth = dataSize;

		// 바인딩 대상
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER; // 상수 버퍼

		// cpu 접근 방식
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		// 버퍼 만들기
		HRESULT hr = DEVICE->CreateBuffer(&desc, nullptr, &buffer);
		CHECK(hr);
	}

private:
	// DX에서 맵은 데이터를 잠시동안 묶어두고 해당데이터를 런타임중에 수정, 복사를 허럭하는 것이다
	// Map을 했음 반드시 unMap을 실행해줘야한다.(데이터 매핑)
	void MapData() {
		// 데이터 임시보관(temp역할)
		D3D11_MAPPED_SUBRESOURCE subResource;

		HRESULT hr = DC->Map(
			buffer,						// 매핑 대상
			0,							// 매핑 시작 위치(0은 첨부터 하겠단것)
			D3D11_MAP_WRITE_DISCARD,	// 매핑 방법(지우고 다시쓰겠다)
			0,							// 추가로 매핑할 하위 리소스
			&subResource				// 매핑한 데이터를 저장할 변수
		); // "buffer"에 있는 (시작부터 있는) 모든 데이터를 지우고 다시 쓰는걸로 뜯은 다음에 "subResource"에 저장하겠다.

		// 오류가 있는지 확인후에
		CHECK(hr);

		// 데이터 복사 (여기있는 데이터를, 여기에다, 이만큼)
		memcpy(subResource.pData, data, dataSize);

		DC->Unmap(buffer, 0); // 그림을 지우거나 수정을 위해서는 언맵을 항상 진행 예정
	}

private:
	D3D11_BUFFER_DESC desc = { 0 };
	ID3D11Buffer* buffer = nullptr;

	void* data = nullptr; // 자료형이 정해지지 않은 어떤 자료형의 데이터도 가르킬수 있는 포인터이다.
	uint dataSize = 0;
};