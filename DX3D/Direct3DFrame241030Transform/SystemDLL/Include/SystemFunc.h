#ifndef _SYSTEMFUNC_H
#define _SYSTEMFUNC_H

#define SYSTEM_EXPORT
#include "SystemDef.h"
namespace DEVICE_SYSTEM
{
	EXTERN SYSTEM_DLL HRESULT InitDevice(WINMODE Mode, HWND hWnd,
		const int& WinSizeX, const int& WinSizeY);

	EXTERN SYSTEM_DLL void Clear();
	EXTERN SYSTEM_DLL void Present();
	EXTERN SYSTEM_DLL void System_Release();
}

namespace XFONT
{
	EXTERN SYSTEM_DLL void AddColor(string key, float r, float g, float b);

	//폰트 추가
	EXTERN SYSTEM_DLL void AddStyle(string key, wstring font, float size = 20.0f,
		DWRITE_FONT_WEIGHT weight   = DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE style     = DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH stretch = DWRITE_FONT_STRETCH_NORMAL);


	EXTERN SYSTEM_DLL void SetColor(string key);
	EXTERN SYSTEM_DLL void SetStyle(string key);

	EXTERN SYSTEM_DLL void RenderTextW(wstring text, Float2 pos, Float2 size = Float2());
	EXTERN SYSTEM_DLL void RenderText(string text, Float2 pos, Float2 size = Float2());

	EXTERN SYSTEM_DLL wstring ChangeWString(string value);


	EXTERN SYSTEM_DLL void BeginDraw();
	EXTERN SYSTEM_DLL void EndDraw();


}

namespace XTIMER
{
	EXTERN SYSTEM_DLL void SetTime();

	EXTERN SYSTEM_DLL float GetDeltaTime();

	EXTERN SYSTEM_DLL void SetTimeScale(float Scale);
	EXTERN SYSTEM_DLL float GetTimeScale();
}


#endif