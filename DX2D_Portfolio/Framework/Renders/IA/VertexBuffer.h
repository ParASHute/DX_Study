#pragma once
// 데이터를 전송하는 박스라고 보면 됨

class VertexBuffer {
public:
	~VertexBuffer ();


	/*
		template<typename T>은 이담에 오는 함수에 들어가는 T를
		어떤게 들어가던 사용할수 있도록 해주는 기능이다.
		Create에서 템플릿을 시용한 이유는 그리고 싶은 사각형에 따라
		다른 데이터를 건내 줘야 하기 때문이다.

		(좌표 색 등등 줘야 할 값들이 목적에 따라서 달라지기 떄문이다.)
	*/
	template<typename T>
	void Create(const vector<T>& verices,
		const D3D11_USAGE& usage = D3D11_USAGE_DEFAULT);

	ID3D11Buffer* GetResource() { return buffer; }
	uint GetStride() { return stride; }
	uint GetOffset() { return offset; }
	uint GetCount() { return count; }

	void SetIA();

private:
	ID3D11Buffer* buffer = nullptr;

	// 버퍼에서 한 정점의 크기를 나타내는 값
	uint stride = 0;

	// 버퍼에서 읽을 시작 위치
	uint offset = 0;

	// 버퍼에서 읽을 정점의 개수
	uint count = 0;
};

template<typename T>
inline void VertexBuffer ::Create(const vector<T>& vertices, const D3D11_USAGE& usage)
{
	stride = sizeof(T);	// 정점 크기 저장
	count = vertices.size();	// 정점 개수
	D3D11_BUFFER_DESC desc;		//desc는 프로그래머가 원하는 목적에 따라 사용할 DX데이터를 만들기 위한 구조체
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC)); // desc 메모리 초기화

	//desc 설정
	{
		// 사용 용도 
		desc.Usage = usage;

		// 사용 목적
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

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
			break;
		}
	}

	// 생성
	{
		D3D11_SUBRESOURCE_DATA subData; // 다영한 데이터를 임시로 보관하는 구조체
		ZeroMemory(&subData, sizeof(D3D11_SUBRESOURCE_DATA));

		subData.pSysMem = vertices.data();

		// HR~은 해당 작업이 정상적으로 수행 됐는지 판단하는 자료형
		// 작업이 끝난 변수를 CHECK에 넣어
		// 작업이 정상적으로 진행되지 않았다면 에러메세지를 출력한다
		HRESULT hr = DEVICE->CreateBuffer(&desc, &subData, &buffer);
		CHECK(hr);
	}
}
