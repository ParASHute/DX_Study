#include "Framework.h"
#include "String.h"

#include <iomanip>	// 입출력 스트림의 조작자를 정의하는 헤더, 스트림의 출력 형식을 제어하는 데 사용
#include <sstream>	// 문자열 스트림을 정의, 메모리 버퍼에 데이터를 읽고 쓰는데 사용

// 문자열을 지정된 구분자로 분할하는 기능 문자열 자르는 기능 (대부분 빽슬이나 슬래시 이용 파일 파기)ㄴㄴ
#pragma region SplitString
void String::SplitString(vector<string>* result, string origin, string tok)
{
	result->clear();
	int cutAt = 0; //자를 위치
	while ((cutAt = (int)origin.find_first_of(tok)) != origin.npos)
	{
		if (cutAt > 0) //자르는 위치가 0보다 크다면
			result->push_back(origin.substr(0, cutAt));

		origin = origin.substr(cutAt + 1);
	}

	if (origin.length() > 0) //자르고도 남은것이 있다면
		result->push_back(origin.substr(0, cutAt));
}

void String::SplitString(vector<wstring>* result, wstring origin, wstring tok)
{
	result->clear();

	int cutAt = 0; //자를 위치
	while ((cutAt = (int)origin.find_first_of(tok)) != origin.npos)
	{
		if (cutAt > 0) //자르는 위치가 0보다 크다면
			result->push_back(origin.substr(0, cutAt));

		origin = origin.substr(cutAt + 1);
	}

	if (origin.length() > 0) //자르고도 남은것이 잇다면
		result->push_back(origin.substr(0, cutAt));
}
#pragma endregion

// 특정한 문자로 시작하는지 체크
#pragma region StartWith
bool String::StartWith(string str, string comp)
{
	//npos no position 즉 없다는 소리
	wstring::size_type index = str.find(comp);
	if (index != wstring::npos && (int)index == 0)
		return true;

	return false;
}

bool String::StartWith(wstring str, wstring comp)
{
	wstring::size_type index = str.find(comp);
	if (index != wstring::npos && (int)index == 0)
		return true;
	return false;
}
#pragma endregion

// 특정한 문자를 포함하는지 체크 
//시작보다 이거 더 많이 씀
#pragma region Contain
bool String::Contain(string str, string comp)
{
	size_t found = str.find(comp);

	return found != wstring::npos;
}

bool String::Contain(wstring str, wstring comp)
{
	size_t found = str.find(comp);

	return found != wstring::npos;
}
#pragma endregion

// 특정한 문자들을 다른 문자들로 대체
// 컴에서는 아마 뺵슬로 자주쓰지만 우리는 그냥 슬래쉬로 사용 이거 혼용하다 난리 안나게 바까주는등의 기능도 필요함
#pragma region Replace
void String::Replace(string* str, string comp, string rep)
{
	string temp = *str;

	size_t startPos = 0;
	while ((startPos = temp.find(comp, startPos)) != wstring::npos)
	{
		temp.replace(startPos, comp.length(), rep);
		startPos += rep.length();
	}

	*str = temp;
}

void String::Replace(wstring* str, wstring comp, wstring rep)
{
	wstring temp = *str;

	size_t startPos = 0;
	while ((startPos = temp.find(comp, startPos)) != wstring::npos)
	{
		temp.replace(startPos, comp.length(), rep);
		startPos += rep.length();
	}

	*str = temp;
}
#pragma endregion

// 벡터를 문자열로 바꿔서 출력
#pragma region ToString
// setprecision : 부동 소수점 숫자의 정밀도를 설정하는 조작자

string String::ToString(D3DXVECTOR3 vec3, int precision)
{
	string temp;
	stringstream stream1, stream2, stream3;
	stream1 << fixed << setprecision(precision) << vec3.x;
	stream2 << fixed << setprecision(precision) << vec3.y;
	stream3 << fixed << setprecision(precision) << vec3.z;
	temp = "X : " + stream1.str() + " Y : " + stream2.str()
		 + " Z : " + stream3.str();
	return temp;
}

wstring String::ToWstring(D3DXVECTOR3 vec3, int precision)
{
	wstring temp;
	wstringstream stream1, stream2, stream3;
	stream1 << fixed << setprecision(precision) << vec3.x;
	stream2 << fixed << setprecision(precision) << vec3.y;
	stream3 << fixed << setprecision(precision) << vec3.z;
	temp = L"X : " + stream1.str() + L" Y : " + stream2.str()
		 + L" Z : " + stream3.str();
	return temp;
}
#pragma endregion

// string -> wstring
// 내부에서 바까 건내줘서 외부 함수에서 사용할때 잘 안되는경우도 존제
wstring String::ToWstring(string str)
{
	wstring temp = L"";
	temp.assign(str.begin(), str.end());
	return temp;
}

// wstring -> string
string String::ToString(wstring str)
{
	string temp = "";
	temp.assign(str.begin(), str.end());
	return temp;
}