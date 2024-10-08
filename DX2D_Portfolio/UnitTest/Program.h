#pragma once

class Program : public IObject
{
	virtual void Init() override;
	virtual void Destroy() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void GUI() override;

private:
	void Push(IObject* obj);

	VPBuffer* vpb = nullptr;

	Matrix view, proj;

	vector<IObject*> objs;
};