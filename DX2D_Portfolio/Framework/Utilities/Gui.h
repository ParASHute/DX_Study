#pragma once

class Gui : public SingletonBase<Gui> {
public:
	friend class SingletonBase<Gui>;

	LRESULT MsgProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
	void Resize();

	void Update();
	void Render();

private:
	Gui();
	~Gui();

private:
	void ApplyStyle();

private:
};