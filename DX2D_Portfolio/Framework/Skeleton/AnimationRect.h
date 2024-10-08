 #pragma once

#include "TextureRect.h"
#include "Utilities/Animator.h"

enum class AnimType
{
	// Idle
	IdleD = 0,
	IdleU,
	IdleL,
	IdleR,

	// Move
	Down,
	Up,
	Left,
	Right,

	// Att
	AttD,
	AttU,
	AttL,
	AttR,

	Item,
	Dead
};

class AnimationRect : public TextureRect {
public:
	AnimationRect(Vector3 position, Vector3 size, float rotation = 0.0f);
	~AnimationRect();

	void Update();
	void Render();
	void GUI(string Name);
	string MakeLable(string lable);

	Animator* GetAnimator() { return animator; }
	void SetAnimator(Animator* animator);

private:
	Animator* animator = nullptr;

	ID3D11SamplerState* sampler[2];
	ID3D11BlendState* blend[2];

	AnimType animType = AnimType::Down;
};