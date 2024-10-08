#pragma once

class TextureRect {
public:
	TextureRect(Vector3 position, Vector3 size, float rotation = 0.0f);

	// 여기는 이미지 경로가 있는 경우
	TextureRect(Vector3 position, Vector3 size, float rotation, wstring path);

	// 소멸자는 앞으로 사용할 애니매이션 클라스부터 시작해 이곳저곳 사용하기 때문에 가상함수로 선언
	virtual ~TextureRect();

	void Update();
	void Render();
	void Gui();

	void UpdateWorld();

	void SetPosition(Vector3 position) { this->position = position; }
	Vector3 GetPosition() { return position; }

	void SetSize(Vector3 size) { this->size = size; }
	Vector3 GetSize() { return size; }


	// 그림 해석하고 쉐이더 한태 건내는 역할
	void SetSRV(ID3D11ShaderResourceView* srv) { this->srv = srv; }
	void SetShader(wstring shaderPath);
	void SetImage(wstring imagePath);

	BoundingBox* GetCollision() { return collision; }

protected:
	// 원래는 VertexColor였지만 color랑 같은 의미에서 Texture로 수정
	vector<VertexTexture> vertices;	
	VertexBuffer* vb = nullptr;
	
	vector<UINT> indices;
	IndexBuffer* ib = nullptr;

	InputLayout* il = nullptr;

	VertexShader* vs = nullptr;
	PixelShader* ps = nullptr;

	WorldBuffer* wb = nullptr;
	D3DXMATRIX world;
	D3DXMATRIX S, R, T;

	Vector3 position;
	Vector3 size;
	float rotation;

	// Color color = Color(1, 0, 0, 1); -> 우리는 그림파일을 사용할 것이기 떄문에 사용 안함
	ID3D11ShaderResourceView* srv = nullptr;
	ID3D11RasterizerState* rs = nullptr;

	bool bOpen = true;

	RectEdge* edge = nullptr;
	BoundingBox* collision = nullptr;

	Vector3 verticesPosition[4];

	string Name;

	// 이동 체크
	bool moveD = false; // 아래로 움직이는지
	bool moveR = false;	// 위로 움직이는지
	bool moveU = false; // 점프 중인지
	bool G = true; // 중력 구현

	// 이단 점프 구현용 점프 카운터
	//int countJump = 0; 

	float TimeDelta = 0;
	float GravityTime;


	D3D11_MAPPED_SUBRESOURCE subRe;
};