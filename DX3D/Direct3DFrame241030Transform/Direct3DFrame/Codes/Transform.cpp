#include "framework.h"
#include "Transform.h"

Transform::Transform()
	:Super(), parent(nullptr), child(nullptr)
{
	world = XMMatrixIdentity(); //배열 초기화
	XMStoreFloat4x4(&matWorld,world);
}

HRESULT Transform::Start()
{
	return E_NOTIMPL;
}

void Transform::Release()
{
}

void Transform::Update()
{
	//멤버 변수 vector 기준으로 위치,크기,회전값 행렬 세팅
	world = XMMatrixTransformation(pivot,
		XMQuaternionIdentity(),localScale,pivot,
		XMQuaternionRotationRollPitchYawFromVector(localRotation),
		localPosition);

	//부모가 있으면 부모 행렬을 곱해서 자식으로
	if (parent)
		world *= parent->world;

	//생성된 행렬 기반으로 내 변수 다시 세팅
	XMStoreFloat4x4(&matWorld, world);
	right = Vector3(matWorld._11, matWorld._12, matWorld._13);
	up = Vector3(matWorld._21, matWorld._22, matWorld._23);
	forward = Vector3(matWorld._31, matWorld._32, matWorld._33);

	//월드 포지션,스케일 얻어옴
	XMVECTOR outS, outR, outT;
	XMMatrixDecompose(&outS, &outR, &outT, world);

	Float3 outPos, outScale;
	XMStoreFloat3(&outPos,outT);
	XMStoreFloat3(&outScale, outS);
	globalPosition = outPos; 
	globalScale = outS;

}

void Transform::PreRender()
{
}

void Transform::Render()
{
}

void Transform::PostRender()
{
}

void Transform::GUIRender()
{
}

void Transform::Save()
{
}

void Transform::Load()
{
}

Transform* Transform::GetChild()
{
	if (child != nullptr)
		return child->GetChild();

	return this;
}

Transform* Transform::GetParent()
{
	if (parent != nullptr)
		return parent->GetParent();

	return this;
}

bool Transform::Active()
{
	if (parent == nullptr)
		return IsActive;
	if(IsActive == false)
		return false;

	return parent->Active();
}

void Transform::AddPosition(Vector3 dir)
{
	localPosition += dir;
}
