#include "Framework.h"
#include "Camera.h"

Camera::Camera()
{
	vpb = new VPBuffer();
	
	// View 행렬 설정
	{
		D3DXMatrixLookAtLH
		(
			&view,
			&Vector3(0, 0, 0),	 // 카메라 위치
			&Vector3(0, 0, 1),	 // 카메라가 보는 방향
			&Vector3(0, 1, 0)	 // 카메라의 위쪽 방향
		);
	
		vpb->SetView(view);
	}
	
	// projection 행렬 생성
	{
		D3DXMatrixOrthoOffCenterLH
		(
			&proj,
			0.0f,				// 왼쪽 끝		// x좌표 최소
			(float)WinMaxWidth,	// 오른쪽 끝		// x좌표 최대
			0.0f,				// 맨 아래		// y좌표 최소
			(float)WinMaxHeight,// 맨 위			// y좌표 최대
			0,					// 최소 깊이		// z좌표 최소
			1					// 최대 깊이		// z좌표 최대
		);
	
		vpb->SetProj(proj);
	}
} // Program에서 가져옴

Camera::~Camera()
{
	SAFE_DELETE(vpb);
}


void Camera::Update()
{
	Move();
	UpdateView();
}

void Camera::Render()
{
	vpb->SetVSBuffer(1);
}

void Camera::Move()
{
	// 타겟 있
	if (target != nullptr) {
		// position.x = target->GetPosition().x; -> 안됨(렉트는 중심이 말대로 중심, 카메라는 좌하단이 중심 그래서 안됨)
		position.x = target->GetPosition().x - (WinMaxWidth * 0.5f);
		position.y = target->GetPosition().y - (WinMaxHeight * 0.5f);
	}

	else {
		// F3누르면 개발자 모드로 들어간다 생각하면됨
		// 참은 거짓, 거짓은 참으로 변경됨
		if (Keyboard::Get()->Down(VK_F3)) bMove = !bMove;
		
		if (bMove) {
			if (Keyboard::Get()->Press('W')) position.y += moveSpd * Time::Delta();
			else if (Keyboard::Get()->Press('S')) position.y -= moveSpd * Time::Delta();
			
			if (Keyboard::Get()->Press('A')) position.x -= moveSpd * Time::Delta();
			else if (Keyboard::Get()->Press('D')) position.x += moveSpd * Time::Delta();
		}
		
	}
}

void Camera::UpdateView()
{
	D3DXMatrixLookAtLH
	(
		&view,
		&position,	 // 카메라 위치
		&(position + Vector3(0, 0, 1)),	 // 카메라가 보는 방향
		&Vector3(0, 1, 0)	 // 카메라의 위쪽 방향
	);

	vpb->SetView(view);

}

const Vector3 Camera::GetMPosition()
{
	Vector3 MPos = Mouse::Get()->GetPosition();
	
	MPos += position;

	return MPos;
}