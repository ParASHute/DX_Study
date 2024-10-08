#pragma once
// 순수 가상함수만 있는 인터페이스 클라스 이름 제일 앞자리에 I를 붙여 표현
// 인터페이는 모든 함수가 순수 가상함수인 특징이 있고
// 인터페이스를 상속 받는 모든 자식 객체는 반드시 부모객체의 모든 함수를 만들지 않으면 객체화 시킬수 없음
// CPU에서 글카에게 쉐이더명령을 내리는 역할
// 쉐이더 버퍼가 전달한 데이터를 IShader가 명령을 내려서 처리함 이라 생각하면 편하다.

class IShader {
public:
	// 생성
	virtual void Create(const wstring path, const string entryName) = 0;

	// 객체 초기화
	virtual void Clear() = 0;

	// 쉐이더에 세팅
	virtual void SetShader() = 0;

protected:
	void CompileShader(wstring path, string entryName, string profile,
		ID3DBlob** blob);

	wstring path = L"";		// 쉐이터 경로
	string entryName = "";	// 진입 경로 (vs로 갈껀지 ps로 갈껀지)

private:
	// 이게 퍼블릭이나 프로택티드로 올라가 외부 또는 자식이 접근 가능하면 애러를 무시할수 있기 떄문
	void CheckShaderError(HRESULT hr, ID3D10Blob* error);
};