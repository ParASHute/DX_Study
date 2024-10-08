#pragma once
#include "IShader.h"

class PixelShader : public IShader {
public:
	~PixelShader();

	// IShader을(를) 통해 상속됨
	virtual void Create(const wstring path, const string entryName) override;
	virtual void Clear() override;
	virtual void SetShader() override;

	ID3D11PixelShader* GetResource() { return shader; }
	ID3DBlob* GetBolb() { return blob; }

private:
	ID3D11PixelShader* shader = nullptr;
	ID3DBlob* blob = nullptr;
};