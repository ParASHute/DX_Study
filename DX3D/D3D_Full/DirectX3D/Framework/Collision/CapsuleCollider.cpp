#include "Framework.h"

CapsuleCollider::CapsuleCollider(float radius, float height, UINT stackCount, UINT sliceCount)
    : radius(radius), height(height), stackCount(stackCount), sliceCount(sliceCount)
{
    type = CAPSULE;
    MakeMesh();
    mesh->CreateMesh();
}

bool CapsuleCollider::IsRayCollision(IN Ray ray, OUT Contact* contact)
{
    UpdateWorld();

	return IsRayCollision2(ray, contact);


    Vector3 direction = Up();
    Vector3 pa = GlobalPos() - direction * Height() * 0.5f;
    Vector3 pb = GlobalPos() + direction * Height() * 0.5f;

    float r = Radius();

    Vector3 ro = ray.pos;
    Vector3 rd = ray.dir;

    Vector3 ba = pb - pa;
    Vector3 oa = ro - pa;

    float baba = Dot(ba, ba);
    float bard = Dot(ba, rd);
    float baoa = Dot(ba, oa);
    float rdoa = Dot(rd, oa);
    float oaoa = Dot(oa, oa);

    float a = baba - bard * bard;
    float b = baba * rdoa - baoa * bard;
    float c = baba * oaoa - baoa * baoa - r * r * baba;
    
    float h = b * b - a * c;

    if (h >= 0.0f)
    {
        float t = (-b - sqrt(h)) / a;

        float distance = baoa + t * bard;

        if (distance > 0.0f && distance < baba)
        {
            if (contact)
            {
                contact->distance = distance;
                contact->hitPoint = ray.pos + ray.dir * t;
            }

            return true;
        }

        Vector3 oc = (distance <= 0.0f) ? oa : ro - pb;
        b = Dot(rd, oc);
        c = Dot(oc, oc) - r * r;
        h = b * b - c;

        if (h > 0.0f)
        {
            if (contact)
            {
                contact->distance = distance;
                contact->hitPoint = ray.pos + ray.dir * t;
            }

            return true;
        }
    }   

    return false;
}

bool CapsuleCollider::IsBoxCollision(BoxCollider* collider)
{  
    BoxCollider::ObbDesc box;
    collider->GetObb(box);

    Vector3 direction = Up();
    Vector3 pa = GlobalPos() - direction * Height() * 0.5f;
    Vector3 pb = GlobalPos() + direction * Height() * 0.5f;

    Vector3 closestPointToSphere = box.pos;
    Vector3 pointOnLine = ClosestPointOnLine(pa, pb, box.pos);

    for (UINT i = 0; i < 3; i++)
    {
        Vector3 direction = pointOnLine - box.pos;
        float length = Dot(box.axis[i], direction);
        float mult = (length < 0.0f) ? -1.0f : 1.0f;
        length = min(abs(length), box.halfSize[i]);
        closestPointToSphere += box.axis[i] * length * mult;
    }

    float distance = Distance(pointOnLine, closestPointToSphere);

    return distance <= Radius();
}

bool CapsuleCollider::IsSphereCollision(SphereCollider* collider)
{
    Vector3 direction = Up();
    Vector3 pa = GlobalPos() - direction * Height() * 0.5f;
    Vector3 pb = GlobalPos() + direction * Height() * 0.5f;

    Vector3 P = collider->GlobalPos();

    Vector3 pointOnLine = ClosestPointOnLine(pa, pb, P);

    float distance = Distance(P, pointOnLine);

    return distance <= (Radius() + collider->Radius());
}

bool CapsuleCollider::IsCapsuleCollision(CapsuleCollider* collider)
{
    Vector3 aDirection = Up();
    Vector3 aA = GlobalPos() - aDirection * Height() * 0.5f;
    Vector3 aB = GlobalPos() + aDirection * Height() * 0.5f;

    Vector3 bDirection = collider->Up();
    Vector3 bA = collider->GlobalPos() - bDirection * collider->Height() * 0.5f;
    Vector3 bB = collider->GlobalPos() + bDirection * collider->Height() * 0.5f;

    Vector3 v0 = bA - aA;
    Vector3 v1 = bB - aA;
    Vector3 v2 = bA - aB;
    Vector3 v3 = bB - aB;

    float d0 = Dot(v0, v0);
    float d1 = Dot(v1, v1);
    float d2 = Dot(v2, v2);
    float d3 = Dot(v3, v3);

    Vector3 bestA;
    if (d2 < d0 || d2 < d1 || d3 < d0 || d3 > d1)
        bestA = aB;
    else
        bestA = aA;

    Vector3 bestB = ClosestPointOnLine(bA, bB, bestA);
    bestA = ClosestPointOnLine(aA, aB, bestB);
    bestB = ClosestPointOnLine(bA, bB, bestA);

    float distance = Distance(bestA, bestB);

    return distance <= (Radius() + collider->Radius());
}

void CapsuleCollider::MakeMesh()
{
    float thetaStep = XM_2PI / sliceCount;
    float phiStep = XM_PI / stackCount;

    vector<Vertex>& vertices = mesh->GetVertices();
    vertices.reserve((sliceCount + 1) * (stackCount + 1));

    for (UINT i = 0; i <= stackCount; i++)
    {
        float phi = i * phiStep;

        for (UINT j = 0; j <= sliceCount; j++)
        {
            float theta = j * thetaStep;

            Vertex vertex;
            vertex.pos.x = sin(phi) * cos(theta) * radius;
            vertex.pos.y = cos(phi) * radius;
            vertex.pos.z = sin(phi) * sin(theta) * radius;

            if (vertex.pos.y > 0)
                vertex.pos.y += height * 0.5f;
            else if(vertex.pos.y < 0)
                vertex.pos.y -= height * 0.5f;

            vertices.push_back(vertex);
        }
    }

    //Indices
    vector<UINT>& indices = mesh->GetIndices();

    indices.reserve(sliceCount * stackCount * 6);

    for (UINT i = 0; i < stackCount; i++)
    {
        for (UINT j = 0; j < sliceCount; j++)
        {
            indices.push_back((sliceCount + 1) * i + j);//0
            indices.push_back((sliceCount + 1) * (i + 1) + j);//1

            indices.push_back((sliceCount + 1) * i + j);//0            
            indices.push_back((sliceCount + 1) * i + j + 1);//2            
        }
    }
}
bool CapsuleCollider::IntersectRaySphere(Ray& ray,TSphere& sphere, float& tmin, float& tmax)
{
    Vector3 CO = ray.pos - sphere.Center;

    float a = Dot(ray.dir,ray.dir);
    float b = 2.0f * Dot(CO,ray.dir);
    float c = Dot(CO,CO) - (sphere.Radius * sphere.Radius);

    float discriminant = b * b - 4.0f * a * c;
    if (discriminant < 0.0f)
        return false;

    tmin = (-b - sqrtf(discriminant)) / (2.0f * a);
    tmax = (-b + sqrtf(discriminant)) / (2.0f * a);
    if (tmin > tmax)
    {
        float temp = tmin;
        tmin = tmax;
        tmax = temp;
    }
    return true;
}
bool CapsuleCollider::IsRayCollision2(IN Ray ray, OUT Contact* contact)
{
	// http://pastebin.com/2XrrNcxb
	// https://gist.github.com/jdryg/ecde24d34aa0ce2d4d87

		// Substituting equ. (1) - (6) to equ. (I) and solving for t' gives:
		//
		// t' = (t * dot(AB, d) + dot(AB, AO)) / dot(AB, AB); (7) or
		// t' = t * m + n where 
		// m = dot(AB, d) / dot(AB, AB) and 
		// n = dot(AB, AO) / dot(AB, AB)
		//
	Vector3 aDirection = Up();
	Vector3 cA = GlobalPos() - aDirection * Height() * 0.5f;
	Vector3 cB = GlobalPos() + aDirection * Height() * 0.5f;


	Vector3 AB = cB - cA;
	Vector3 AO = ray.pos - cA;

	float AB_dot_d  = Dot(AB,ray.dir);
	float AB_dot_AO = Dot(AB,AO);
	float AB_dot_AB = Dot(AB,AB);

	float m = AB_dot_d / AB_dot_AB;
	float n = AB_dot_AO / AB_dot_AB;

	// Substituting (7) into (II) and solving for t gives:
	//
	// dot(Q, Q)*t^2 + 2*dot(Q, R)*t + (dot(R, R) - r^2) = 0
	// where
	// Q = d - AB * m
	// R = AO - AB * n
	Vector3 Q = ray.dir - (AB * m);
	Vector3 R = AO - (AB * n);

	float a = Dot(Q,Q);
	float b = 2.0f * Dot(Q,R);
	float c = Dot(R,R) - (Radius() * Radius());

	if (a == 0.0f)
	{
		// Special case: AB and ray direction are parallel. If there is an intersection it will be on the end spheres...
		// NOTE: Why is that?
		// Q = d - AB * m =>
		// Q = d - AB * (|AB|*|d|*cos(AB,d) / |AB|^2) => |d| == 1.0
		// Q = d - AB * (|AB|*cos(AB,d)/|AB|^2) =>
		// Q = d - AB * cos(AB, d) / |AB| =>
		// Q = d - unit(AB) * cos(AB, d)
		//
		// |Q| == 0 means Q = (0, 0, 0) or d = unit(AB) * cos(AB,d)
		// both d and unit(AB) are unit vectors, so cos(AB, d) = 1 => AB and d are parallel.
		// 
		TSphere sphereA, sphereB;
		sphereA.Center = cA;
		sphereA.Radius = Radius();
		sphereB.Center = cB;
		sphereB.Radius = Radius();

		float atmin, atmax, btmin, btmax;
		if (!IntersectRaySphere(ray, sphereA, atmin, atmax) ||
			!IntersectRaySphere(ray, sphereB, btmin, btmax))
		{
			// No intersection with one of the spheres means no intersection at all...
			return false;
		}

		if (atmin < btmin)
		{
			if (contact)
			{		
				contact->hitPoint = ray.pos + ray.dir * atmin;
				contact->distance = Distance(ray.pos, contact->hitPoint);
			}
		}
		else
		{
			if (contact)
			{
				contact->hitPoint = ray.pos + ray.dir * btmin;
				contact->distance = Distance(ray.pos, contact->hitPoint);
			}
		}

		if (atmax > btmax)
		{
			if (contact)
			{
				contact->hitPoint = ray.pos + ray.dir * atmax;
				contact->distance = Distance(ray.pos, contact->hitPoint);
			}
		}
		else
		{
			if (contact)
			{
				contact->hitPoint = ray.pos + ray.dir * btmax;
				contact->distance = Distance(ray.pos, contact->hitPoint);
			}
		}

		return true;
	}

	float discriminant = b * b - 4.0f * a * c;
	if (discriminant < 0.0f)
	{
		// The ray doesn't hit the infinite cylinder defined by (A, B).
		// No intersection.
		return false;
	}

	float tmin = (-b - sqrtf(discriminant)) / (2.0f * a);
	float tmax = (-b + sqrtf(discriminant)) / (2.0f * a);
	if (tmin > tmax)
	{
		float temp = tmin;
		tmin = tmax;
		tmax = temp;
	}

	// Now check to see if K1 and K2 are inside the line segment defined by A,B
	float t_k1 = tmin * m + n;
	if (t_k1 < 0.0f)
	{
		// On sphere (A, r)...
		TSphere s;
		s.Center = cA;
		s.Radius = Radius();

		float stmin, stmax;
		if (IntersectRaySphere(ray, s, stmin, stmax))
		{
			if (contact)
			{
				contact->hitPoint = ray.pos + ray.dir * stmin;
				contact->distance = Distance(ray.pos, contact->hitPoint);
			}
		}
		else
			return false;
	}
	else if (t_k1 > 1.0f)
	{
		// On sphere (B, r)...
		TSphere s;
		s.Center = cB;
		s.Radius = Radius();

		float stmin, stmax;
		if (IntersectRaySphere(ray, s, stmin, stmax))
		{
			if (contact)
			{
				contact->hitPoint = ray.pos + ray.dir * stmin;
				contact->distance = Distance(ray.pos, contact->hitPoint);
			}
		}
		else
			return false;
	}
	else
	{
		// On the cylinder...
		if (contact)
		{
			contact->hitPoint = ray.pos + ray.dir * tmin;
			contact->distance = Distance(ray.pos, contact->hitPoint);
		}
	}

	float t_k2 = tmax * m + n;
	if (t_k2 < 0.0f)
	{
		// On sphere (A, r)...
		TSphere s;
		s.Center = cA;
		s.Radius = Radius();

		float stmin, stmax;
		if (IntersectRaySphere(ray, s, stmin, stmax))
		{
			if (contact)
			{
				contact->hitPoint = ray.pos + ray.dir * stmax;
				contact->distance = Distance(ray.pos, contact->hitPoint);
			}
		}
		else
			return false;
	}
	else if (t_k2 > 1.0f)
	{
		// On sphere (B, r)...
		TSphere s;
		s.Center = cB;
		s.Radius = Radius();

		float stmin, stmax;
		if (IntersectRaySphere(ray, s, stmin, stmax))
		{
			if (contact)
			{
				contact->hitPoint = ray.pos + ray.dir * stmax;
				contact->distance = Distance(ray.pos, contact->hitPoint);
			}
		}
		else
			return false;
	}
	else
	{
		if (contact)
		{
			contact->hitPoint = ray.pos + ray.dir * tmax;
			contact->distance = Distance(ray.pos, contact->hitPoint);
		}
	}

	return true;



}