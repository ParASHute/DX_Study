#pragma once
class MainApp
{

public:
	HRESULT InitApp(void);
	void Update(void);
	void Render(void);
	void Release(void);

	void FPSPrint();


public:
	MainApp(void);
	~MainApp(void);

};

