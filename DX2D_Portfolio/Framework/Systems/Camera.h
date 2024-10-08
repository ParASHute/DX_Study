#pragma once

#include "Skeleton/TextureRect.h"

class Camera : public SingletonBase<Camera> {
public:
	friend SingletonBase<Camera>;

	void Update();
	void Render();

	void Move();
	void UpdateView();

	const Vector3 GetPosition() { return position; }
	const Vector3 GetMPosition();	// 마우스 위치

	void Setposition(Vector3 position) { this->position = position; }
	
	void SetTarget(TextureRect* target) { this->target = target; }
	void DelTartget() { this->target = nullptr; }
	TextureRect* GetTarget() { return target; }

private:
	Camera();
	~Camera();

private:
	VPBuffer* vpb = nullptr;
	Matrix view, proj;

	Vector3 position = Values::ZeroVec3;

	bool bMove = false;
	float moveSpd = 100.0;

	// 이걸 타겟으로 카메라가 따라 다닐 예정임
	// 에님랙, 플레이어 등등 상관 없음
	TextureRect* target = nullptr;
};