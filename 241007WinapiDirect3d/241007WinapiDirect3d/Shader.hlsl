struct VS_INPUT
{
	float2 pos : POS;
	float4 color : COL;
};
struct VS_Output
{
	float4 position : SV_POSITION;
	float4 color : COL;
};
VS_Output vs_main(VS_INPUT input)//πˆ≈ÿΩ∫ Ω¶¿Ã¥ı
{
	VS_Output output;
	output.position = float4(input.pos, 0.0f, 1.0f);
	output.color = input.color;
	return output;
}
float4 ps_main(VS_Output input) : SV_TARGET //«»ºø Ω¶¿Ã¥ı
{
	return input.color;
}
