#pragma once

// (단색)사각형 물체 출력 객체
class Rect {
public:
	// 객체 위치, 크기, 회전
	Rect(Vector3 position, Vector3 size, float rotation = 0.0f);
	~Rect();

	// 매 프레임 마다 실행될 내용들
	void Update();

	// 매 프레임 마다 그림을 그리는 코드들
	void Render();

	void Move(); // 과제

	void GUI();	// UI창 띄우기
	
	void UpdateColor();
	string MakeLable(string lable);

	void UpdateWorld();
	void SetColor(Color color);
	// 이거 위에 두개만 없음

	BoundingBox* GetCollision() { return collision; }
	
	Vector3 GetSize() { return size; }
	void SetSize(Vector3 size) { this->size = size; }

	Vector3 GetPosition() { return position; }
	void SetPosition(Vector3 pos) { this->position = pos; }

private:
	// 정점의 데이터들 (사각형이니까 4개 필요해서 백터로 선언)
	vector<VertexColor> vertices;
	VertexBuffer* vb = nullptr;

	// 삼각형 그리는 순서
	vector<UINT> indices;
	IndexBuffer* ib = nullptr;

	// 정점의 데이터 해석방법
	InputLayout* il = nullptr;

	// 그림을 그릴 쉐이터들
	VertexShader* vs = nullptr;
	PixelShader* ps = nullptr;

	WorldBuffer* wb = nullptr;			// 공간을 GPU로 넘겨줄 버퍼
	D3DXMATRIX world;					// 인식할 공간
	D3DXMATRIX S, R, T;					// 공간에 해당 객체의 크기, 회전, 위지

	Vector3 position;					// 좌표
	Vector3 size;						// 크기
	float rotation;						// 회전

	Color color = Color(1, 0, 0, 1);	// 객체 색 (RGBA)

	bool bOpen = true;					// imGUI에서 사용할 불 값

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
};