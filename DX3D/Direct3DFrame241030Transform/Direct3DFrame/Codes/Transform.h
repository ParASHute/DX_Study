#pragma once
#include "Component.h"
class Transform :
    public Component
{
	GENERATED_BODY(Component);


public:
	Transform();
	~Transform() = default;

public:
	virtual HRESULT Start() override;
	virtual void Release() override;

	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void GUIRender() override;

	virtual void Save();
	virtual void Load();

public:
	Vector3 Right()const { return right.GetNormalized(); };
	Vector3 Left()const { return right.GetNormalized() * -1.0f; };

	Vector3 Up()const { return up.GetNormalized(); };
	Vector3 Down()const { return up.GetNormalized() * -1.0f; };

	Vector3 Forward()const { return forward.GetNormalized(); };
	Vector3 Back()const { return forward.GetNormalized() * -1.0f; };

	Vector3 GlobalPosition() { return globalPosition; }
	Vector3 GlobalScale() { return globalScale; }

	Transform* GetChild();
	Transform* GetParent();

	void SetParent(Transform* transform)
	{
		parent = transform;
		this->child = parent->child;
		parent->child = this;
		IsTop = false;
	}

	void SetPiviot(Vector3 pivot) { this->pivot = pivot; }
	void SetWorld(Matrix matrix) { this->world = matrix; }

	Matrix GetWorld() { return world; }
	bool Active();
	bool ActiveSelf() { return IsActive; };

	void SetActive(bool isActive) {this->IsActive = isActive;}

	Vector3& Position() { return localPosition; }
	Vector3& Rotation() { return localRotation; }
	Vector3& Scale() { return localScale; }

	void AddPosition(Vector3 dir);

protected:
	Vector3 localPosition = { 0,0,0 };
	Vector3 localRotation = { 0,0,0 };
	Vector3 localScale = { 1,1,1 };

	bool IsActive = true;
	Matrix world;
private:
	Transform* parent = nullptr;
	Transform* child = nullptr;

	Vector3 pivot;

	Vector3 right, up, forward;
	Vector3 globalPosition, globalScale;
	XMFLOAT4X4 matWorld;


};

