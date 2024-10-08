#pragma once

// 실체가 없이 기능만 있는 클래스
class Random
{
public:
    static int GetRandomInt(int minValue, int maxValue);
    static float GetRandomFloat(float minValue, float maxValue);
};