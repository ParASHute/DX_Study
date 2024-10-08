#include "Framework.h"
#include "VertexBuffer.h"

VertexBuffer::~VertexBuffer ()
{
	/*
		SAFE_RELEASE는 ID3D로 시작하는 인터페이스를 헤제하는데 사용되며
		해당 인터페이스들은 프로그래머가 만드는 것이 아닌
		다랙에서 만들어놓은 기능을 빌려오는 방식이기 떄문에
		세이프 딜리트가 아닌 "SAFE_RELEASE"를 사용한다.

		** 게임 종료시 오류가 뜰때는 SAFE_RELEASE해야 되는 곳을 세이프 딜리트로 해서 그럼
	*/

	SAFE_RELEASE(buffer);
}

void VertexBuffer::SetIA()
{
	//인푹 어셈블러에 버퍼 넣어주는 함수
	DC->IASetVertexBuffers(0, 1, &buffer, &stride, &offset);
}
