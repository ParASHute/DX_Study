#pragma once
#define SYSTEM_EXPORT
#include "SystemDef.h"
EXTERN class SYSTEM_DLL Device
{
	DECLARE_SINGLETON(Device); //싱글톤
private:
	~Device();
	Device();
private:
	ID3D11Device1* d3d11Device; //장치정보

	//장치 세팅용 리소스 파이프라인 바인딩 상태 설정
	ID3D11DeviceContext1* d3d11DeviceContext;

	//화면 출력 프레임 버퍼 앞 뒤 관리 역할
	IDXGISwapChain1* d3d11SwapChain;

	//스왑체인 어댑터,표면 등 dxgi 객체 생성용
	IDXGIFactory2* dxgiFactory;

	//깊이,스텐실 버퍼
	ID3D11DepthStencilView* depthStencilView;

	//화면에 풀력할 프레임 버퍼 렌더링에 사용하는 뷰
	//최종 출력용
	ID3D11RenderTargetView* d3d11FrameBufferView;
public:

	HRESULT InitDevice(WINMODE Mode, HWND hWnd,
		const int& WinSizeX, const int& WinSizeY);

	void Clear();
	void Present();
public:
	//getter
	ID3D11Device1* GetDevice() { return d3d11Device; };
	ID3D11DeviceContext1* GetContext() { return d3d11DeviceContext; };
	IDXGISwapChain1* GetSwapChain() { return d3d11SwapChain; };
};

