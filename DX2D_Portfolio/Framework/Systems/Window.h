#pragma once

struct DXDesc
{
	wstring AppName;
	HINSTANCE instance;
	HWND handle;
	UINT width; //윈도우 창의 가로 세로 크기
	UINT height;
};

class Window
{
public:
	Window(DXDesc desc);
	~Window();

	WPARAM Run(IObject* mainObj); //게임루프 함수
private:
	//함수호출 규약
	//stdcall
	//cdecl
	static LRESULT CALLBACK WndProc //메세지 처리함수
	(
		HWND handle,
		UINT message,
		WPARAM wParam,
		LPARAM lParam
	);
	void MainRender();

	static DXDesc desc;
	IObject* mainObj = nullptr;
};

