#include "Framework.h"
#include "Random.h"

int Random::GetRandomInt(int minValue, int maxValue)
{
    /*
    random_device는 프로그래머가 제어 할수없는 난수값을 만들어내며 
    지역에 벗어났을때 자동으로 소멸된다.

    또한, random_device는 호출할 때 마다 다른 난수값을 출력한다.
    */
    random_device randDevice; // 럭키 srand

    /*
    uniform_int_distribution은 뽑아낼 랜덤값의 자료형과 범위를 지정할수 있다.
    
    선언뒤 <>를 입력해 <>사시에 결과값으로 원하는 자료형을 입력할수 있고

    uniform_int_distribution은 정수형 범우와 결과값만 만들어낼 수 있다.

    uniform_int<> 또한 똑같은 작동을 하지만 기억은 안나는 대충 뭔가 이유 때문에
    uniform_int_distribution를 쓴다

    선언후 원하는 변수명을 지은뒤 ()에 출력하고 싶은 최소 값과 최대값을 넣어주면
    된다.

    이때 최소값과 최대값을 포함하는 랜덤한 수를 출력한다.
    Ex) intRand(100,200) 이면 100 ~ 200 까지의 숫자가 나온다.
    */
    uniform_int_distribution<int> intRand(minValue, maxValue);

    /*
    랜덤 값을 출력해 내기 위해서는 uniform과 rand_device를 조합하여 출력된
    데이터를 변수에 넣어줘야 한다.

    이때 변수에 넣어주기 전까지는 변수의 데이터로써 인식이 되지 않기 때문에
    해당 데이터를 다이렉트로 연산하거나 변형할때 오류가 발생할 수도 있다.

    추가로 intRand(randDevice)의 똑같은 형태의 데이터를 여러번 호출해 여러번
    집어넣어도 매번 다른 결과값의 데이터가 들어간다.
    */
    int aValue = intRand(randDevice);

    return aValue;
}

float Random::GetRandomFloat(float minValue, float maxValue)
{
    random_device randDevice;

    /*
    실수형의 랜덤값을 얻기 위해서는 uniform_real 형태의 클래스를 사용하면 된다.

    이때 주의사항은 실수형의 범위는 일반적인 정수형과 달리 표시할수 있는 자릿수의
    모든값이 랜덤의 범위에 들어가기 때문에 실질적인 제어가 매우 어렵고

    매우 작은값들을 관리해야 하기 때문에 추천하진 않는다.

    Ex) floatRand(0.5f, 1.0f)
    0.5000000 ~ 1.0000000 까지의 범위이기 때문에
    결과 값으로 0.7842516 같은 수가 나올수도 있다.
    */
    uniform_real_distribution<float> floatRand(minValue, maxValue);

    float aValue = floatRand(randDevice);

    return aValue;
}
