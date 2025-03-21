#include "Device.h"

Device::Device()
:d3d11Device(NULL),
d3d11DeviceContext(NULL),
d3d11SwapChain(NULL),
dxgiFactory(NULL),
depthStencilView(NULL),
d3d11FrameBufferView(NULL)
{


}

Device::~Device()
{
	//device 삭제시 전부 release
	SAFE_RELEASE(d3d11Device);
	SAFE_RELEASE(d3d11DeviceContext);
	SAFE_RELEASE(d3d11SwapChain);
	SAFE_RELEASE(dxgiFactory);
	SAFE_RELEASE(depthStencilView);
	SAFE_RELEASE(d3d11FrameBufferView);
}



HRESULT Device::InitDevice(
	WINMODE Mode, HWND hWnd,
	const int& WinSizeX, const int& WinSizeY)
{
	HRESULT hResult = NULL;
	//d3d11 디바이스, 컨텍스트 생성
	{
		ID3D11Device* baseDevice;
		ID3D11DeviceContext* baseDeviceContext;

		D3D_FEATURE_LEVEL featureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0,
			D3D_FEATURE_LEVEL_9_3,
			D3D_FEATURE_LEVEL_9_2,
			D3D_FEATURE_LEVEL_9_1,
		};

		//기본 타입
		UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
		
		#if defined(DEBUG_BUILD) //디버그만 플래그 추가
				creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
		#endif

		//디바이스 생성
		hResult = D3D11CreateDevice(0,
					D3D_DRIVER_TYPE_HARDWARE,
					0, creationFlags,
					featureLevels, ARRAYSIZE(featureLevels),
					D3D11_SDK_VERSION, &baseDevice,
					0, &baseDeviceContext);
		if (FAILED(hResult))
		{
			MSGBOX(L"D3D11CreateDevice() Failed");
			return GetLastError(); //마지막 에러 정보 메시지
		}

		//1.1용으로 device 얻어온다.
		hResult = baseDevice->QueryInterface(__uuidof(ID3D11Device1),(void**)&d3d11Device );
		Check(hResult); //성공여부 체크

		//1.1용 context 얻어온다.
		hResult = baseDeviceContext->QueryInterface(__uuidof(ID3D11DeviceContext1), (void**)&d3d11DeviceContext);
		Check(hResult); //성공여부 체크
		SAFE_RELEASE(baseDeviceContext); //사용 했으니 초기화
		SAFE_RELEASE(baseDevice); //사용 했으니 초기화

	}
	
	//스왑 체인 생성
	{
		IDXGIDevice1* dxgiDevice;

		hResult = d3d11Device->QueryInterface(__uuidof(IDXGIDevice1), (void**)&dxgiDevice);
		Check(hResult); //성공여부 체크

		IDXGIAdapter* dxgiAdapter;
		hResult = dxgiDevice->GetAdapter(&dxgiAdapter);
		Check(hResult);
		SAFE_RELEASE(dxgiDevice);

		DXGI_ADAPTER_DESC adapterDesc;
		dxgiAdapter->GetDesc(&adapterDesc);

		//그래픽 사양 비주얼스튜디오에 출력
		OutputDebugStringA("Graphic Device : ");
		OutputDebugStringW(adapterDesc.Description);
		hResult = dxgiAdapter->GetParent(__uuidof(IDXGIFactory2), (void**)&dxgiFactory);\
		Check(hResult);
		SAFE_RELEASE(dxgiAdapter);

		DXGI_SWAP_CHAIN_DESC1 d3d11SwapChainDesc = {};
		d3d11SwapChainDesc.Width = WinSizeX;
		d3d11SwapChainDesc.Height = WinSizeY;
		d3d11SwapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		d3d11SwapChainDesc.SampleDesc.Count = 1;
		d3d11SwapChainDesc.SampleDesc.Quality = 0;
		d3d11SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		d3d11SwapChainDesc.BufferCount = 2;
		d3d11SwapChainDesc.Scaling = DXGI_SCALING_STRETCH;
		d3d11SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		d3d11SwapChainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
		d3d11SwapChainDesc.Flags = 0;

		dxgiFactory->CreateSwapChainForHwnd(d3d11Device, hWnd,
			&d3d11SwapChainDesc, 0, 0, &d3d11SwapChain);

		Check(hResult);
		SAFE_RELEASE(dxgiFactory);
	}

	//Create Framebuffer Render Target
	{
		ID3D11Texture2D* d3d11FrameBuffer;
		hResult = d3d11SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D),(void**)&d3d11FrameBuffer);
		assert(SUCCEEDED(hResult));

		hResult = d3d11Device->CreateRenderTargetView(d3d11FrameBuffer,0,&d3d11FrameBufferView);
		assert(SUCCEEDED(hResult));
		SAFE_RELEASE(d3d11FrameBuffer);
	}
	//depth, 깊이 버퍼 관련 설정
	{
		ID3D11Texture2D* depthBuffer = NULL;
		D3D11_TEXTURE2D_DESC depthDesc = {};
		depthDesc.Width = WinSizeX;
		depthDesc.Height = WinSizeY;
		depthDesc.MipLevels = 1;
		depthDesc.ArraySize = 1;
		depthDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthDesc.SampleDesc.Count = 1;
		depthDesc.Usage = D3D11_USAGE_DEFAULT;
		depthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL; //깊이버퍼,스텐실 버퍼 사용

		d3d11Device->CreateTexture2D(&depthDesc, nullptr, &depthBuffer);

		D3D11_DEPTH_STENCIL_VIEW_DESC depthViewDesc = {};
		depthViewDesc.Format = depthDesc.Format;
		depthViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;

		if (depthBuffer)
		{
			d3d11Device->CreateDepthStencilView(depthBuffer,&depthViewDesc,&depthStencilView);
			SAFE_RELEASE(depthBuffer);
		}
	}

	return S_OK;
}

void Device::Clear()
{
	//출력할 타겟
	d3d11DeviceContext->OMSetRenderTargets(1, &d3d11FrameBufferView, depthStencilView);

	float clearColor[4] = { 0.0f,0.125f,0.3f,1.0f };

	//버퍼 색상 초기화
	d3d11DeviceContext->ClearRenderTargetView(d3d11FrameBufferView, clearColor);

	//깊이버퍼 초기화
	d3d11DeviceContext->ClearDepthStencilView(depthStencilView,D3D11_CLEAR_DEPTH,1.0f,0);
}

void Device::Present()
{
	d3d11SwapChain->Present(1, 0);//SyncInterval 1 : vSync 활성화,0 비활성화
}
