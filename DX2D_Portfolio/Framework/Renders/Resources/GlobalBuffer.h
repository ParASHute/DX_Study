#pragma once
// 여기도 인덱스 버퍼처럼 헤더파일만

#include "Framework.h"
// #include "Renders/Resources/ShaderBuffer.h"

/*
	WVP = 월드(공간) * 뷰(카메라) * 프로젝션(투영법)

	 WVP는 3차원공간과 모델을 2차원 스크린 좌표로 변환하는 과정중 하나이다
	 모니터또한 평면(2차원)이기 떄문에 3D게임도 스크린 좌표로 변환하는 과정이 필요하다.

	 World(공간)
		- 모델의 정점을 글로벌 좌표계에서 지역 좌표계로 변환 하는 것을 의미한다.
		- 모델의 위치, 회전, 크기를 조정한다.

	View(카메라)
		- 카메라의 위치, 방향, 시야를 나타내는 행렬
		- 글러벌 좌표계에서 카메라가 바라보는 방향을 나타낸다.(실제로 카메라가 존제하는건 아님)
		- 카메라의 위치와 방향을 번경 시켜준다.

	Projection(투영법)
		- 3D공간을 2D스크린 좌표로 변환시키는 방법
		- 시야각, 종횡비, 크리핑 평면(단면도 // 물체를 각아서 내부 확인을 할 수 있는)등을 고려해 실행
*/

class WorldBuffer : public ShaderBuffer {
public:
	WorldBuffer() : ShaderBuffer(&data, sizeof(Data)) {
		D3DXMatrixIdentity(&data.world); // 행열 초기화
	}

	void SetWorld(Matrix world) {
		// 전치 행렬
		// 열과 행을 서로 교환
		// world의 행이 데이트 월드의 열, 열은 행으로 들어감
		D3DXMatrixTranspose(&data.world, &world);
	}

	// cpu에 넘길 데이터 종류
	// 16배수로 할당해주는 것이 제일 좋음(int 4개 or char 16개 처럼)
	// 16보다 작으면 글카가 재대로 못가져 가는 상황이 생김
	struct  Data
	{
		// float 4개 있는 구조체
		Matrix world;
	};

private:
	Data data;
};

class VPBuffer : public ShaderBuffer {
public:
	VPBuffer() : ShaderBuffer(&data, sizeof(Data)) {
		D3DXMatrixIdentity(&data.view);
		D3DXMatrixIdentity(&data.projection);
	}

	void SetView(Matrix view) {
		D3DXMatrixTranspose(&data.view, &view);
	}

	void SetProj(Matrix projection) {
		D3DXMatrixTranspose(&data.projection, &projection);
	}

	struct  Data
	{
		// float 4개 있는 구조체
		Matrix view;		// 카매라
		Matrix projection;	// 투영법
	};

private:
	Data data;
};