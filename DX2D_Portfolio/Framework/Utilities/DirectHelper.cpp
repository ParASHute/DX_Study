#include "Framework.h"
#include "DirectHelper.h"

const float Values::PI = 3.141592f;

const Vector3 Values::ZeroVec3 = Vector3(0, 0, 0);
const Vector3 Values::OneVec3 = Vector3(1, 1, 1);
const Vector3 Values::LeftVec = Vector3(-1, 0, 0); //
const Vector3 Values::RightVec = Vector3(1, 0, 0);
const Vector3 Values::UpVec = Vector3(0, 1, 0);
const Vector3 Values::DownVec = Vector3(0, -1, 0);
const Vector3 Values::FwdVec = Vector3(0, 0, 1);
const Vector3 Values::ScreenSize = Vector3((float)WinMaxWidth, (float)WinMaxHeight, 1);

const Vector2 Values::ZeroVec2 = Vector2(0, 0);
const Vector2 Values::OneVec2 = Vector2(1, 1);
const Vector2 Values::uvLT = Vector2(0, 0);
const Vector2 Values::uvLB = Vector2(0, 1);
const Vector2 Values::uvRT = Vector2(1, 0);
const Vector2 Values::uvRB = Vector2(1, 1);

const Color Values::Red = Color(1, 0, 0, 1);
const Color Values::Green = Color(0, 1, 0, 1);
const Color Values::Blue = Color(0, 0, 1, 1);
const Color Values::Magenta = Color(1, 0, 1, 1);
const Color Values::Black = Color(0, 0, 0, 1);
const Color Values::White = Color(1, 1, 1, 1);
// const Color Values::ClearColor = 0xFF555566; // 디파인으로 빠져 있어 지워도 큰 문제 없음

const Matrix Values::Identity = { 1, 0, 0, 0,
								  0, 1, 0, 0,
								  0, 0, 1, 0,
								  0, 0, 0, 1 };