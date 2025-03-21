#include "Font.h"
#include "../Include/Device.h"

Font::Font()
{
	DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(IDWriteFactory),(IUnknown**)&writeFactory);

	D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED,&factory);

	//DXGI 디바이스 생성
	IDXGIDevice* dxgiDevice;
	GET_SINGLE(Device)->GetDevice()->QueryInterface(&dxgiDevice);
	factory->CreateDevice(dxgiDevice, &device2D); //2d 디바이스 생성
	
	device2D->CreateDeviceContext(
		D2D1_DEVICE_CONTEXT_OPTIONS_ENABLE_MULTITHREADED_OPTIMIZATIONS,
		&context);

	IDXGISurface* dxgiSurface = nullptr;
	GET_SINGLE(Device)->GetSwapChain()->GetBuffer(0,
		__uuidof(IDXGISurface), (void**)&dxgiSurface);

	DXGI_SURFACE_DESC surfDesc;
	dxgiSurface->GetDesc(&surfDesc);

	D2D1_BITMAP_PROPERTIES1 bp = {};

	//디바이스 생성시 설정한 픽셀포멧과 동일 해야됨.
	bp.pixelFormat.format = surfDesc.Format;
	bp.pixelFormat.alphaMode = D2D1_ALPHA_MODE_IGNORE;
	bp.dpiX = 96;
	bp.dpiY = 96;
	bp.bitmapOptions = D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW;
	bp.colorContext = nullptr;

	HRESULT result = context->CreateBitmapFromDxgiSurface(dxgiSurface,&bp,&targetBitmap);
	if (SUCCEEDED(result))
		context->SetTarget(targetBitmap);
	else
	{
		SAFE_RELEASE(targetBitmap);
		MSGBOX(L"폰트 생성 실패!");
	}
}

Font::~Font()
{
	Release();
}
void Font::Release()
{
	//map<string, ID2D1SolidColorBrush*> brushs;//폰트 색상 원본 담아놓는다.
	//map<string, IDWriteTextFormat*> formats;//폰트 원본 담아놓는다.

	for (pair<string, ID2D1SolidColorBrush*> brush : brushs)
		brush.second->Release();

	for (pair<string, IDWriteTextFormat*> format : formats)
		format.second->Release();

	SAFE_RELEASE(factory);
	SAFE_RELEASE(writeFactory);
	SAFE_RELEASE(targetBitmap);
	SAFE_RELEASE(context);
	SAFE_RELEASE(device2D);
}

void Font::AddColor(string key, float r, float g, float b)
{
	if (brushs.count(key) > 0)return;
	ID2D1SolidColorBrush* brush = nullptr;

	D2D1::ColorF colorF(r, g, b);
	context->CreateSolidColorBrush(colorF,&brush);

	brushs[key] = brush;
}

void Font::AddStyle(string key, wstring font, float size, DWRITE_FONT_WEIGHT weight, DWRITE_FONT_STYLE style, DWRITE_FONT_STRETCH stretch)
{
	if (formats.count(key) > 0)return;
	IDWriteTextFormat* format;

	HRESULT result = writeFactory->CreateTextFormat(font.c_str(),nullptr,
	weight,style,stretch,size,L"ko",&format);

	formats[key] = format;

	if (result != S_OK)
	{
		MSGBOX(L"폰트 로드 실패!");
	}

}

void Font::SetColor(string key)
{
	if (brushs.count(key) == 0)return;

	curBrush = brushs[key];
}

void Font::SetStyle(string key)
{
	if (formats.count(key) == 0)return;
	
	curFormat = formats[key];
	
}

void Font::RenderText(wstring text, Float2 pos, Float2 size)
{
	//설정 안하면 기본값
	if (size.x == 0.0f && size.y == 0.0f)
	{
		size.x = text.size() * curFormat->GetFontSize();
		size.y = curFormat->GetFontSize();
	}

	Float2 halfSize = { size.x * 0.5f,size.y * 0.5f };


	D2D1_RECT_F rectF;
	rectF.left = pos.x - halfSize.x;
	rectF.right = pos.x + halfSize.x;

	rectF.top = pos.y - halfSize.y;
	rectF.bottom = pos.y + halfSize.y;

	context->DrawTextW(text.c_str(), text.size(),
		curFormat, &rectF, curBrush);
}

void Font::RenderText(string text, Float2 pos, Float2 size)
{
	//설정 안하면 기본값
	if (size.x == 0.0f && size.y == 0.0f)
	{
		size.x = text.size() * curFormat->GetFontSize();
		size.y = curFormat->GetFontSize();
	}

	Float2 halfSize = { size.x * 0.5f,size.y * 0.5f };


	D2D1_RECT_F rectF;
	rectF.left = pos.x - halfSize.x;
	rectF.right = pos.x + halfSize.x;

	rectF.top = pos.y - halfSize.y;
	rectF.bottom = pos.y + halfSize.y;

	wstring temp = ChangeWString(text);
	context->DrawTextW(temp.c_str(), temp.size(),
		curFormat, &rectF, curBrush);
}

wstring Font::ChangeWString(string value)
{
	int nLen = MultiByteToWideChar(CP_ACP,0,&value[0], value.size(),nullptr,0);
	wstring strUni(nLen + 1, 0);

	int len = MultiByteToWideChar(CP_ACP, 0, value.c_str(), value.size(), &strUni[0], nLen);
	strUni[len] = 0;

	return strUni;
}

