#include "Framework.h"
#include "IShader.h"

void IShader::CompileShader(wstring path, string entryName, string profile, ID3DBlob** blob)
{
	ID3DBlob* error = nullptr;
	HRESULT hr = D3DCompileFromFile(
		path.c_str(),					// 쉐이더 파일 경로
		nullptr,						// 쉐이더 파일의 헤더를 나타낼 포인터
		nullptr,						// 결과를 보내줄 다른 파일의 포인터
		entryName.c_str(),				// 진입점 위치 (주로 vs 또는 ps) 
		profile.c_str(),				// 쉐이터 파일에서 사용할 프로필 이름
		D3DCOMPILE_ENABLE_STRICTNESS,	// 컴파일 경고 레벨옵션 / 메세지 레벨을 1로 설정
		0,								// 디버그 정보가 포함된 컴파일 결과 생성 위치
		blob,							// 검파일 결과를 저장할 블롭
		&error							// 컴파일 오류 메세지를 저장할 블롭
	);

	CheckShaderError(hr, error);

	SAFE_RELEASE(error);
}

void IShader::CheckShaderError(HRESULT hr, ID3D10Blob* error)
{
	// HRESULT가 실패할경우(파일에서 데이터를 뽑아오는데)
	if (FAILED(hr)) {
		// 에러가 존제할 경우 
		if (error) {
			// 에러난 쉐이더의 몇번째 줄에서 에러 났는지 확인
			string str = (const char*)error->GetBufferPointer();

			// 에러난 위치와 쉐이더 에러라고 알려줄 문자를 확인 버튼과 함깨 출력
			MessageBoxA(handle, str.c_str(), "Shader Error", MB_OK);
		}

		CHECK(false);
	}
}
