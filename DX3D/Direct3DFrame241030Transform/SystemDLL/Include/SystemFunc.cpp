#include "SystemFunc.h"
#include "Device.h"
#include "../Utillities/Font.h"
#include "../Utillities/TimeManager.h"
EXTERN SYSTEM_DLL HRESULT DEVICE_SYSTEM::InitDevice(
	WINMODE Mode, HWND hWnd, const int& WinSizeX, const int& WinSizeY)
{
	return GET_SINGLE(Device)->InitDevice(Mode, hWnd, WinSizeX, WinSizeY);
}

EXTERN SYSTEM_DLL void DEVICE_SYSTEM::Clear()
{
	GET_SINGLE(Device)->Clear();
}

EXTERN SYSTEM_DLL void DEVICE_SYSTEM::Present()
{
	GET_SINGLE(Device)->Present();
}

EXTERN SYSTEM_DLL void DEVICE_SYSTEM::System_Release()
{
	GET_SINGLE(Font)->DestroyInstance();
	GET_SINGLE(Device)->DestroyInstance();

}

EXTERN SYSTEM_DLL void XFONT::AddColor(string key, float r, float g, float b)
{
	GET_SINGLE(Font)->AddColor(key,r,g,b);
}

EXTERN SYSTEM_DLL void XFONT::AddStyle(string key, wstring font, 
	float size, 
	DWRITE_FONT_WEIGHT weight,
	DWRITE_FONT_STYLE style,
	DWRITE_FONT_STRETCH stretch)
{
	GET_SINGLE(Font)->AddStyle(key, font, size,weight,style,stretch);
}

EXTERN SYSTEM_DLL void XFONT::SetColor(string key)
{
	GET_SINGLE(Font)->SetColor(key);
}

EXTERN SYSTEM_DLL void XFONT::SetStyle(string key)
{
	GET_SINGLE(Font)->SetStyle(key);
}

EXTERN SYSTEM_DLL void XFONT::RenderTextW(wstring text, Float2 pos, Float2 size)
{
	GET_SINGLE(Font)->RenderText(text,pos,size);
}

EXTERN SYSTEM_DLL void XFONT::RenderText(string text, Float2 pos, Float2 size)
{
	GET_SINGLE(Font)->RenderText(text, pos, size);
}

EXTERN SYSTEM_DLL wstring XFONT::ChangeWString(string value)
{
    return GET_SINGLE(Font)->ChangeWString(value);
}

EXTERN SYSTEM_DLL void XFONT::BeginDraw()
{
	GET_SINGLE(Font)->GetDC()->BeginDraw();
}

EXTERN SYSTEM_DLL void XFONT::EndDraw()
{
	GET_SINGLE(Font)->GetDC()->EndDraw();
}

EXTERN SYSTEM_DLL void XTIMER::SetTime()
{
	GET_SINGLE(TimeManager)->SetTime();
}

EXTERN SYSTEM_DLL float XTIMER::GetDeltaTime()
{
	return GET_SINGLE(TimeManager)->GetDeltaTime();
}

EXTERN SYSTEM_DLL void XTIMER::SetTimeScale(float Scale)
{
	GET_SINGLE(TimeManager)->SetTimeScale(Scale);
}

EXTERN SYSTEM_DLL float XTIMER::GetTimeScale()
{
	return GET_SINGLE(TimeManager)->GetTimeScale();
}
