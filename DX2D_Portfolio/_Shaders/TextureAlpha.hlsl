
// VertexInput == VertexBuffer에 있는 데이터
// VertexShader에서 사용할 데이터
struct VertexInput
{
	float4 position : POSITION0;	// 위치
	float2 uv		: TEXCOORD0;	// 그림 좌표
};

// PixelInput
// PixelShader에서 사용할 데이터
struct PixelInput
{
	float4 position : SV_POSITION0; // 위치
	float2 uv		: TEXCOORD0;	// 그림 좌표
};

// 월드 버퍼란 이름의 버퍼 슬롯 0번에 있는 상수 버퍼
cbuffer WorldBuffer : register(b0)
{
	matrix _world;
};

// VP 버퍼란 이름의 버퍼 슬롯 1번에 있는 상수 버퍼
cbuffer VPBuffer : register(b1)
{
	matrix _view;
	matrix _projection;
};

PixelInput VS(VertexInput input)
{
	PixelInput output;
	
	// 정점에 위치와 월드를 곱하고
	output.position = mul(input.position, _world);
	// 월드가 곱해진 데이터에 뷰를 곱하고
	output.position = mul(output.position, _view);
	// 뷰까지 곱해진 데이터에 프로젝션을 곱한다.
	output.position = mul(output.position, _projection);
	// 이 순서로 곱해야 DirectX 가 공간에 위치한다고 인식할수 있음
	
	output.uv = input.uv;
	
	return output;
};

cbuffer AlphaBuffer : register(b0)
{
	float4 _clearColor;
	float _alpha;
};

Texture2D _sourceTex : register(t0);
SamplerState _samp : register(s0);

float4 PS(PixelInput input) : SV_Target
{
	float4 color = _sourceTex.Sample(_samp, (float2)input.uv);
	float4 resultColor = 0;
	
	if (color.r >= 0.99f && color.g <= 0.01f && color.b >= 0.99f) 
		discard; 
	
	if (_alpha >= 0.001f)
	{
		resultColor.r = (color.r - (color.r * _alpha)) +
			(_clearColor.r * _alpha);
		
		resultColor.g = (color.g - (color.g * _alpha)) +
			(_clearColor.g * _alpha);
		
		resultColor.b = (color.b - (color.b * _alpha)) +
			(_clearColor.b * _alpha);
		
		resultColor.a = (color.a - (color.a * _alpha)) +
			(_clearColor.a * _alpha);
	}
	else
	{
		resultColor = color;
	}

	return resultColor;
};