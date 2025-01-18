#pragma once
#include "../Global/Define/GlobalDefine.h"
class Screen {
private:
	COORD Pos;
	COORD Start;

protected:

	
public:
	Screen() { }
	~Screen() { }
	void SetStart(int x, int y);
	COORD GetCoord() { return this->Pos; }
	void EndLine() { this->Pos.Y++; }
	void AfterCls() { this->Pos = this->Start; }
};// 쿠드를 스크린 마다? -> 위치가 다를뿐 출력하는건 같음(클라스로 묶어서)
/*
class Screen1 : Coord {
private:

protected:

public:
	Screen1() { }
	~Screen1() { }
	void SetCoord() { this->Pos = { 3,1 }; }
	COORD GetCoord() { return this->Pos; }
	void EndLine() { this->Pos.Y++; }
};
class Screen2 : Coord {
private:

protected:

public:
	Screen2() { }
	~Screen2() { }
	void SetCoord() { this->Pos = { 3,15 }; }
	COORD GetCoord() { return this->Pos; }
	void EndLine() { this->Pos.Y++; }
	void AfterCls() {this->Pos = { 3,15 }; }
};
class Screen3 : Coord {
private:

protected:

public:
	Screen3() { }
	~Screen3() { }
	void SetCoord() { this->Pos = { 3,21 }; }
	COORD GetCoord() { return this->Pos; }
	void EndLine() { this->Pos.Y++; }
	void AfterCls() { this->Pos = { 3,21 }; }
};
class Screen4 : Coord {
private:

protected:

public:
	Screen4() { }
	~Screen4() { }
	void SetCoord() { this->Pos = { 80,21 }; }
	COORD GetCoord() { return this->Pos; }
	void EndLine() { this->Pos.Y++; }
	void AfterCls() { this->Pos = { 80,21 }; }
};
*/
void PrintScreen(); // system("cls"); 찍으면 이거 선언 합시다!!
void PrintDiceDungeon();
/* 씬 안에서 움직이는 함수. 이건 맨 처음 시작할때 이걸로 선언하고 아래 라인을 만들어서 사용가능
	-> 클라스 안에서 SetCoord()로 변경
void goScreen1();
void goScreen2();
void goScreen3();
void goScreen4();

여기 함수는 스크린 안에서 인테자 변수를 받아서 줄수를 옮겨 준다, (endl처럼 뒤에다 쓰면 그 뒤는 다음줄에 찍혀 나온다.)
	-> 클라스 안에서 EndLine()으로 정의
void InLine1(int Line);
void InLine2(int Line);
void InLine3(int Line);
void InLine4(int Line);

스크린 안을 지우는 함수
	-> 클라스 안에서 AfterCls()으로 정의
		-> system("cls") 이후에 선언해 사용하도록하자
void Screen1Cls();
void Screen2Cls();
void Screen2Cls();
void Screen4Cls();
*/