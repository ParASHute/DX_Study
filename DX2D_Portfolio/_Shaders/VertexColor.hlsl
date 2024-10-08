
// VertexInput == VertexBuffer에 있는 데이터
// VertexShader에서 사용할 데이터
struct VertexInput
{
	float4 position : POSITION0;	// 위치
	float4 color : COLOR0;			// 색상
};

// PixelInput
// PixelShader에서 사용할 데이터
struct PixelInput
{
	float4 position : SV_POSITION0; // 위치
	float4 color : COLOR0;			// 색상
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
	
	output.color = input.color;
	
	return output;
};

// SV_Target은 메모리상에 남아있는 데이터중 적절 한데이터를
// 자동으로 끌고와 사용해주는 걸로 기억한다. // 확실하진 않음
float4 PS(PixelInput input) : SV_Target
{
	return input.color;
};

/*
Semantic : 세멕틱
- HLSL에서 데이터의 의미를 지정하는데 사용하는 문자
- 쉐이더가 입력 데이터와 출력 데이터를 올바르게 해석하고 처리하는데 사용
- 변수 이름뒤에 : 과 함께 지정
- SV_ 접두사로 시작하는 세멘틱은 DirectX가 지정한 특수한 의미를 지닌다.
- 이러한 세멘텍을 시스템 값 세멘틱이라 부른다. // SystemValue_

slot
- GPU에서 사용하는 상수 버퍼, 텍스쳐, 샘플러 등의 다양한 데이터를 식별하는
번호
- 각 슬롯은 고유한 번호르 지니며, 해당 데이터의 유향과 역할에 따라
다양한 슬롯이 존재한다.
- register 키워드를 사용하여 지정한다.

- 상수 버퍼 슬롯
- 상수 데이터를 지정하는데 사용되며, VS와 PS가 공유할수 있다.
- 주로 정점에 대한 데이터 말고 다양한 데이터를 건내줄때 사용한다.
- 상수 버퍼 슬롯은 register(b#)을 사용하여 지정한다. 
// #에는 슬롯 번호가 들어감

- 텍스처 슬롯
- 이미지 데이터를 저장하는데 사용
- 텍스처 슬롯은 register(t#)을 사용하여 지정한다. 

- 샘플러 슬롯
- 이미지를 가공하는 법이 저장되는 슬롯
- 샘플러 슬롯은 register(s#)을 사용하여 지정한다. 

cbuffer : 상수 버퍼 // constant buffer
- 쉐이더에 사용할수있는 전역 변수를 저장하는데 사용
- CPU에서 정점 데이터가 아닌 다른 데이터를 전달할때 사용
- 각 상수 버퍼 레지스터는 한개의 상수버퍼만 할당할수 있다.
- 상수 버퍼 내부에는 여러개의 변수를 선언할 수 있다.
- 단, 이러한 데이터는 쉐이더 버퍼를 통해 지정된 형식으로 건내줘야한다.
*/
