#pragma once

#include "SystemDef.h"
class Font
{
	DECLARE_SINGLETON(Font);
public:
	Font();
	~Font();

private:

	ID2D1Factory1* factory;
	IDWriteFactory* writeFactory;

	ID2D1Device* device2D; //direct2d에 있는 폰트기능 사용
	ID2D1DeviceContext* context;

	ID2D1Bitmap1* targetBitmap;

	map<string, ID2D1SolidColorBrush*> brushs;//폰트 색상 원본 담아놓는다.
	map<string, IDWriteTextFormat*> formats;//폰트 원본 담아놓는다.

	ID2D1SolidColorBrush* curBrush;
	IDWriteTextFormat* curFormat;

public:
	//폰트 색상 추가
	void AddColor(string key, float r, float g, float b);

	//폰트 추가
	void AddStyle(string key, wstring font, float size = 20.0f,
		DWRITE_FONT_WEIGHT weight = DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE style = DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH stretch = DWRITE_FONT_STRETCH_NORMAL);

	
	void SetColor(string key);
	void SetStyle(string key);

	//폰트 출력
	void RenderText(wstring text, Float2 pos, Float2 size = Float2());
	void RenderText(string text, Float2 pos, Float2 size = Float2());


	ID2D1DeviceContext* GetDC() { return context; };
	wstring ChangeWString(string value);

	void Release();

};

