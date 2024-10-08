#pragma once
#include "TextureRect.h"

class ShadedBuffer : public ShaderBuffer {
public:
	ShadedBuffer() :ShaderBuffer(&data, sizeof(data)) {
		data.selection = 1;
		data.blurCount = 1;
		data.textureSize = Vector2(0, 0);
	}

	int* GetSelecttionPtr() { return &data.selection; }
	int* GetBlurCountPtr() { return &data.blurCount; }
	
	void SetTextureSize(Vector2 size) {
		data.textureSize = size;
	}
	//~ShadedBuffer();
	
	// 프로그레머가 조작해 cpu to gpu 전달데이터 
	// 2^n 의 크기로 만들면 좋음 (n >= 4)
	struct Data
	{
		int selection;			// 효과 지정 번호(4)

		int blurCount;			// 블러 강도(4)
		Vector2 textureSize;	// 이미지 사이즈(8)
		// 따라서 총 16
	};

private:
	Data data;
};

class ShadedTexture  : public TextureRect {
public:
	ShadedTexture(Vector3 position, Vector3 size, float rotation, wstring path);
	~ShadedTexture();

	void Update();
	void Render();
	void GUI();

private:
	ShadedBuffer* sb = nullptr;
};