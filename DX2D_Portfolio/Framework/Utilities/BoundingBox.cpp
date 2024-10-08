#include "Framework.h"
#include "BoundingBox.h"

BoundingBox::BoundingBox()
{
	edge = new RectEdge();
	data = new AxisData();
}

BoundingBox::~BoundingBox()
{
	SAFE_DELETE(data);
	SAFE_DELETE(edge);
}

void BoundingBox::UpdateCollisionData(const Matrix world, const Vector3 verticesLocalPositino[])
{
	//AABB
	{
		// local pos -> World pos
		D3DXVec3TransformCoord(&edge->LT, &verticesLocalPositino[3], &world);
		D3DXVec3TransformCoord(&edge->LB, &verticesLocalPositino[0], &world);
		D3DXVec3TransformCoord(&edge->RT, &verticesLocalPositino[1], &world);
		D3DXVec3TransformCoord(&edge->RB, &verticesLocalPositino[2], &world);
	}

	// OBB
	{
		// CenterPos Vector Upadate (축 중심 확인)
		{
			data->centerPos = Vector3(
				(edge->LT.x + edge->LB.x + edge->RT.x + edge->RB.x) * 0.25f,	// LT랑 RB값 평균 내는 거랑 같은데도 이렇게 하는건 가끔식 터지기 때문이다.
				(edge->LT.y + edge->LB.y + edge->RT.y + edge->RB.y) * 0.25f,
				0
			);
		}

		// AxisDir Updata (축 방향 확인)
		{
			// 노말이 들어간 함수 대부분은 정규화 하는 함수이다
			// 정규화는 모든 값을 0 ~ 1 로 바꾸는 과정이다.
			D3DXVec3TransformNormal(&data->axisDir[x],
				&Vector3(1, 0, 0), &world);

			D3DXVec3TransformNormal(&data->axisDir[y],
				&Vector3(0, 1, 0), &world);

			D3DXVec3Normalize(&data->axisDir[x], &data->axisDir[x]);
			D3DXVec3Normalize(&data->axisDir[y], &data->axisDir[y]);
		}

		// AxisLen Updata(축 길이 구하기 // 마름모 꼴이 나올수도 있기 때문이다.)
		{
			Vector3 unitAxis[2] = {
				data->axisDir[x], data->axisDir[y]
			};

			Vector3 verticesPos[4] = {
				edge->LT, edge->LB, edge->RB, edge->RT
			};

			float minValuse[2] = {
				INT_MAX, INT_MAX
			};

			float maxValuse[2] = {
				INT_MIN, INT_MIN
			};

			for (int i = 0; i < 4; i++) {
				Vector3 point = verticesPos[i];

				for (int j = 0; j < 2; j++) {
					float projection =
						D3DXVec3Dot(&point, &unitAxis[j]);

					// 사각형이 가지고 있는 x,y축의 최소값 / 최대값 찾기
					if (projection < minValuse[j]) minValuse[j] = projection;
					if (projection > maxValuse[j]) maxValuse[j] = projection;
				}
			}
			data->axisLen[x] = (maxValuse[x] - minValuse[x]) * 0.5f;
			data->axisLen[y] = (maxValuse[y] - minValuse[y]) * 0.5f;
		}
	}
}

bool BoundingBox::AABB(BoundingBox* a, BoundingBox* b)
{
	if(a == nullptr || b == nullptr ) return false;
	RectEdge aEdge = *a->edge;
	RectEdge bEdge = *b->edge;

	/*
		회전하지 않은 사각형들의 충돌은 각각의 사각형이 가진
		가장 큰 XY와 가장작은 XY를 비교하는 것으로 가능하다.

		주요 내용은 메모장 참고
	*/

	if (aEdge.LT.x <= bEdge.RB.x &&
		aEdge.LT.y >= bEdge.RB.y &&
		aEdge.RB.x >= bEdge.LT.x &&
		aEdge.RB.y <= bEdge.LT.y)
		return true;

	return false;
}

bool BoundingBox::OBB(BoundingBox* a, BoundingBox* b)
{
	AxisData ad = *a->data;
	AxisData bd = *b->data;

	Vector3 centerDir, axis;
	float centerProjDist, r1, r2;

	// a와 b 사이의 거리
	centerDir = ad.centerPos - bd.centerPos;

	// a의 x축
	{
		axis = ad.axisDir[x];

		// 실제 비교할 사이 거리 
		centerProjDist = abs(D3DXVec3Dot(&centerDir, &axis));

		r1 = ad.axisLen[x];
		r2 = abs(D3DXVec3Dot(&bd.axisDir[x], &axis) * bd.axisLen[x])
			+ abs(D3DXVec3Dot(&bd.axisDir[y], &axis) * bd.axisLen[y]);

		if (centerProjDist > r1 + r2)return false;
	}

	// a의 y축
	{
		axis = ad.axisDir[y];

		// 실제 비교할 사이 거리 
		centerProjDist = abs(D3DXVec3Dot(&centerDir, &axis));

		r1 = ad.axisLen[y];
		r2 = abs(D3DXVec3Dot(&bd.axisDir[x], &axis) * bd.axisLen[x])
			+ abs(D3DXVec3Dot(&bd.axisDir[y], &axis) * bd.axisLen[y]);

		if (centerProjDist > r1 + r2)return false;
	}

	// b의 x축
	{
		axis = bd.axisDir[x];

		// 실제 비교할 사이 거리 
		centerProjDist = abs(D3DXVec3Dot(&centerDir, &axis));

		r1 = bd.axisLen[x];
		r2 = abs(D3DXVec3Dot(&ad.axisDir[x], &axis) * ad.axisLen[x])
			+ abs(D3DXVec3Dot(&ad.axisDir[y], &axis) * ad.axisLen[y]);

		if (centerProjDist > r1 + r2)return false;
	}

	// a의 y축
	{
		axis = bd.axisDir[y];

		// 실제 비교할 사이 거리 
		centerProjDist = abs(D3DXVec3Dot(&centerDir, &axis));

		r1 = bd.axisLen[y];
		r2 = abs(D3DXVec3Dot(&ad.axisDir[x], &axis) * ad.axisLen[x])
			+ abs(D3DXVec3Dot(&ad.axisDir[y], &axis) * ad.axisLen[y]);

		if (centerProjDist > r1 + r2)return false;
	}

	return true;
}
