// 241007WinapiDirect3d.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "241007WinapiDirect3d.h"

#include <d3d11_1.h> //11.1버전
#pragma comment(lib,"d3d11.lib") //라이브러리 추가

#include "assert.h" //오류 메시지용

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
HWND g_hWnd = NULL; //윈도우 창 핸들 번호

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY241007WINAPIDIRECT3D, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY241007WINAPIDIRECT3D));

    MSG msg;



	//장치 그래픽
	ID3D11Device1* d3d11Device;
	ID3D11DeviceContext1* d3d11DeviceContext; //장치 설정용

	{
		ID3D11Device* baseDevice;
		ID3D11DeviceContext* baseDeviceContext;
		D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_0 };
		UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

		//장치 생성 함수
		HRESULT hResult = D3D11CreateDevice(0, D3D_DRIVER_TYPE_HARDWARE,
			0, creationFlags,
			featureLevels, ARRAYSIZE(featureLevels),
			D3D11_SDK_VERSION, &baseDevice,
			0,&baseDeviceContext);

		//if(hResult == S_FALSE)
		//디바이스 생성 실패
		if (FAILED(hResult)) 
		{
			MessageBoxA(0, "D3D11CreateDevice() failed", "Fatal Error", MB_OK);
			return GetLastError();
		}


		hResult = baseDevice->QueryInterface(__uuidof(ID3D11Device1), (void**)&d3d11Device);
		assert(SUCCEEDED(hResult)); //오류 메시지 어디서 났는지
		baseDevice->Release(); //지워줌

		baseDeviceContext->QueryInterface(__uuidof(ID3D11DeviceContext1), (void**)&d3d11DeviceContext);
		assert(SUCCEEDED(hResult));
		baseDeviceContext->Release(); //지워줌

	}

	IDXGISwapChain1* d3d11SwapChain;
	{
		IDXGIFactory2* dxgiFactory;
		{
			IDXGIDevice1* dxgiDevice; //디바이스에서 DXGI용으로 변환해서 얻음
			HRESULT hResult = d3d11Device->QueryInterface(__uuidof(IDXGIDevice1),(void**)&dxgiDevice);
			assert(SUCCEEDED(hResult));

			IDXGIAdapter* dxgiadapter;
			hResult = dxgiDevice->GetAdapter(&dxgiadapter);
			assert(SUCCEEDED(hResult));
			dxgiDevice->Release();

			DXGI_ADAPTER_DESC adapterDesc;
			dxgiadapter->GetDesc(&adapterDesc); //내 그래픽 디바이스 정보 얻어온다.
			OutputDebugStringA("Graphics Device : ");
			OutputDebugStringW(adapterDesc.Description);//그래픽카드 이름 출력

			hResult = dxgiadapter->GetParent(__uuidof(IDXGIFactory2),(void**)&dxgiFactory); //설정용
			assert(SUCCEEDED(hResult));
			dxgiadapter->Release();
		}
		
		DXGI_SWAP_CHAIN_DESC1 d3d11SwapChainDesc = {};
		d3d11SwapChainDesc.Width = 0; //0이면 윈도우 사이즈 알아서 얻어와서 만든다.
		d3d11SwapChainDesc.Height = 0; //0이면 윈도우 사이즈 알아서 얻어와서 만든다.
		d3d11SwapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB; //그래픽 픽셀 타입?
		d3d11SwapChainDesc.SampleDesc.Count = 1;
		d3d11SwapChainDesc.SampleDesc.Quality = 0;
		d3d11SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		d3d11SwapChainDesc.BufferCount = 2; //더블 버퍼팅
		d3d11SwapChainDesc.Scaling = DXGI_SCALING_STRETCH; //창사이즈 바뀌면 따라감
		d3d11SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		d3d11SwapChainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
		d3d11SwapChainDesc.Flags = 0;
		HRESULT hResult = dxgiFactory->CreateSwapChainForHwnd(d3d11Device, g_hWnd,
			&d3d11SwapChainDesc,0,0,&d3d11SwapChain);
		assert(SUCCEEDED(hResult));
		dxgiFactory->Release();
	}

	ID3D11RenderTargetView* d3d11FrameBufferView;
	{
		ID3D11Texture2D* d3d11frameBuffer;

		//버퍼 얻어온다.
		HRESULT hResult = d3d11SwapChain->GetBuffer(0,__uuidof(ID3D11Texture2D),(void**)&d3d11frameBuffer);
		assert(SUCCEEDED(hResult));

		//출력할 타겟 뷰 만든다.
		hResult = d3d11Device->CreateRenderTargetView(d3d11frameBuffer,0, &d3d11FrameBufferView);
		assert(SUCCEEDED(hResult));
		d3d11frameBuffer->Release();
	}


    // 기본 메시지 루프입니다:
    //while (GetMessage(&msg, nullptr, 0, 0))
	bool IsRunning = true;
	while(IsRunning)
    {
		//윈도우 메시지 처리 부분
		while (PeekMessageW(&msg,0,0,0,PM_REMOVE))
		{
			//프로그램 종료시 루프 끔
			if (msg.message == WM_QUIT)
				IsRunning = false;

			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}

		FLOAT backgroundColor[4] = { 0.1f, 0.1f, 0.6f, 1.0f };
		d3d11DeviceContext->ClearRenderTargetView(d3d11FrameBufferView, backgroundColor);

		d3d11SwapChain->Present(1, 0);
    }
    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY241007WINAPIDIRECT3D));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName   = NULL;// MAKEINTRESOURCEW(IDC_MY241007WINAPIDIRECT3D);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   RECT InitialRect = { 0,0, 800,600 };
   AdjustWindowRectEx(&InitialRect,WS_OVERLAPPEDWINDOW,FALSE,WS_EX_OVERLAPPEDWINDOW);
   LONG InitialWidth = InitialRect.right - InitialRect.left;
   LONG InitialHeight = InitialRect.bottom - InitialRect.top;


   HWND hWnd = g_hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, CW_USEDEFAULT, InitialWidth, InitialHeight, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
	  MessageBoxA(0, "에러 메시지", "생성 실패", MB_OKCANCEL);
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
		case WM_KEYDOWN:
		{
			if (wParam == VK_ESCAPE)
				DestroyWindow(hWnd);
				break;
		}
		break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
			//Rectangle(hdc, 10, 10, 200, 200);
			//Rectangle(hdc, 10, 10, 20, 20);


            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}


