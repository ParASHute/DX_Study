#include "Framework.h"
#include "AnimationRect.h"

AnimationRect::AnimationRect(Vector3 position, Vector3 size, float rotation)
	:TextureRect(position, size, rotation)
{
	SetShader(ShaderPath + L"VertexTexture.hlsl");

	animator = new Animator();

	// 애니메이션 클립 제작 및 저장
	{
		Texture2D* srcTex = new Texture2D(TexturePath +
			L"SampleSheet.png");

		AnimationClip* RunD = new AnimationClip(L"RunD", srcTex,
			4, Values::ZeroVec2,
			{ srcTex->GetWidth() * 0.5f, srcTex->GetHeight() * 0.125f });

		AnimationClip* RunLD = new AnimationClip(L"RunLD", srcTex,
			4, { 0, srcTex->GetHeight() * 0.125f },
			{ srcTex->GetWidth() * 0.5f, (srcTex->GetHeight() * 0.125f) * 2 });

		AnimationClip* RunL = new AnimationClip(L"RunL", srcTex,
			4, { 0, (srcTex->GetHeight() * 0.125f) * 2 },
			{ srcTex->GetWidth() * 0.5f, (srcTex->GetHeight() * 0.125f) * 3 });

		animator->AddAnimClip(RunD);
		animator->AddAnimClip(RunLD);
		animator->AddAnimClip(RunL);

		SAFE_DELETE(srcTex);
	}

	animator->SetCurrentAnimClip(L"RunD");

	// Sampler
	{
		D3D11_SAMPLER_DESC desc;
		States::GetSamplerDesc(&desc);
		States::CreateSampler(&desc, &sampler[0]);

		// 선형보간
		desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		States::CreateSampler(&desc, &sampler[1]);
	}

	//Blend
	{
		D3D11_BLEND_DESC desc;
		States::GetBlendDesc(&desc);
		States::CreateBlend(&desc, &blend[0]);

		desc.RenderTarget[0].BlendEnable = true;
		States::CreateBlend(&desc, &blend[1]);
	}
}

AnimationRect::~AnimationRect()
{
	SAFE_DELETE(animator);
}

void AnimationRect::Update()
{
	/*
	if (Keyboard::Get()->Press('S'))
	{
		animType = AnimType::Down;
	}
	else if (Keyboard::Get()->Press('A'))
	{
		animType = AnimType::Left;
	}

	switch (animType)
	{
	case AnimType::Down:
		animator->SetCurrentAnimClip(L"RunD");
		break;
	case AnimType::Left:
		animator->SetCurrentAnimClip(L"RunLD");
		break;
	default:
		break;
	}
	// 여기 까지는 무브로 따로 빼거나, 지워서 플레이어한태 무브 주는게 좋음
	*/
	

	animator->Update();

	DC->Map(vb->GetResource(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subRe);
	{
		// uv 좌표로 봤을때 0번은 0,1 지점 (좌 하단)
		vertices[0].uv.x = animator->GetCurrentFrame().x;
		vertices[0].uv.y = animator->GetCurrentFrame().y +
			animator->GetTexelFrameSize().y;

		// uv 좌표로 봤을때 1번은 1,0 지점 (우 상단)
		vertices[1].uv.x = animator->GetCurrentFrame().x +
			animator->GetTexelFrameSize().x;
		vertices[1].uv.y = animator->GetCurrentFrame().y;

		// uv 좌표로 봤을때 2번은 1,1 지점 (우 하단)
		vertices[2].uv.x = animator->GetCurrentFrame().x +
			animator->GetTexelFrameSize().x;
		vertices[2].uv.y = animator->GetCurrentFrame().y +
			animator->GetTexelFrameSize().y;

		// uv 좌표로 봤을때 3번은 0,0 지점 (좌 상단)
		vertices[3].uv.x = animator->GetCurrentFrame().x;
		vertices[3].uv.y = animator->GetCurrentFrame().y;
	}
	memcpy(subRe.pData, vertices.data(),
		sizeof(vertices[0]) * vertices.size());
	DC->Unmap(vb->GetResource(), 0);

	__super::Update();
}


void AnimationRect::Render()
{
	srv = animator->GetCurrentSRV();

	DC->PSSetSamplers(0, 1, &sampler[1]);
	DC->OMSetBlendState(blend[1], nullptr, (UINT)0xFFFFFFFF);

	__super::Render();
}

void AnimationRect::GUI(string Name)
{
	ImGui::Begin("GUI", &bOpen); // 여기부터
	{
		ImGui::Text(MakeLable(Name).c_str());
		ImGui::SliderFloat2(MakeLable("Pos").c_str(), position, 0, WinMaxWidth);
		ImGui::SliderFloat2(MakeLable("Size").c_str(), size, 0, WinMaxHeight);
	}
	ImGui::End();
}

string AnimationRect::MakeLable(string lable)
{
	string Label = lable + "##" + to_string((uint)this);

	return Label;
}

void AnimationRect::SetAnimator(Animator* animator)
{
	// 에니메이터를 갈아 끼울때 메모리릭 방지를 위해서
	SAFE_DELETE(this->animator);
	this->animator = animator;
}
