#include "Framework.h"
#include "Player.h"

Player::Player(Vector3 position, Vector3 size, float rotation)
	: position(position), size(size)
{
	body = new AnimationRect(position, size);

	attMotion = new AnimationRect({ position.x - (position.x * 0.5f), position.y - (position.y * 0.5f), position.z }, { size.x * 0.5f, size.y * 0.5f, size.z });
	swordRange = size.x * 0.5f + size.x * 0.25;
	
	Texture2D* IdleSrcTex = new Texture2D(TexturePath + L"Player/SeparateAnim/Idle.png");
	Texture2D* WalkSrcTex = new Texture2D(TexturePath + L"Player/SeparateAnim/Walk.png");
	Texture2D* AttSrcTex = new Texture2D(TexturePath + L"Player/SeparateAnim/Attack.png");
	Texture2D* ItemSrcTex = new Texture2D(TexturePath + L"Player/SeparateAnim/Item.png");
	Texture2D* DeadSrcTex = new Texture2D(TexturePath + L"Player/SeparateAnim/Dead.png");

	//Idle
	AnimationClip* IdleD = new AnimationClip(L"IdleD", IdleSrcTex, 1,
		Values::ZeroVec2, 
		{ IdleSrcTex->GetWidth() * 0.25f, IdleSrcTex->GetHeight() });

	AnimationClip* IdleU = new AnimationClip(L"IdleU", IdleSrcTex, 1,
		{ IdleSrcTex->GetWidth() * 0.25f, 0 },
		{ IdleSrcTex->GetWidth() * 0.25f * 2, IdleSrcTex->GetHeight() });

	AnimationClip* IdleL = new AnimationClip(L"IdleL", IdleSrcTex, 1,
		{ IdleSrcTex->GetWidth() * 0.25f * 2, 0 },
		{ IdleSrcTex->GetWidth() * 0.25f * 3, IdleSrcTex->GetHeight() });

	AnimationClip* IdleR = new AnimationClip(L"IdleR", IdleSrcTex, 1,
		{ IdleSrcTex->GetWidth() * 0.25f * 3, 0 },
		{ IdleSrcTex->GetWidth() * 0.25f * 4, IdleSrcTex->GetHeight() });

	// Move
	AnimationClip* MoveD = new AnimationClip(L"MoveD", WalkSrcTex, 4,
		Values::ZeroVec2, 
		{ WalkSrcTex->GetWidth() * 0.25f, WalkSrcTex->GetHeight() }, true);

	AnimationClip* MoveU = new AnimationClip(L"MoveU", WalkSrcTex, 4,
		{ WalkSrcTex->GetWidth() * 0.25f, 0 }, 
		{ WalkSrcTex->GetWidth() * 0.25f * 2 , WalkSrcTex->GetHeight() }, true);

	AnimationClip* MoveL = new AnimationClip(L"MoveL", WalkSrcTex, 4,
		{ WalkSrcTex->GetWidth() * 0.25f * 2 , 0}, 
		{ WalkSrcTex->GetWidth() * 0.25f * 3, WalkSrcTex->GetHeight() }, true);

	AnimationClip* MoveR = new AnimationClip(L"MoveR", WalkSrcTex, 4,
		{ WalkSrcTex->GetWidth() * 0.25f * 3, 0 }, 
		{ WalkSrcTex->GetWidth() * 0.25f * 4, WalkSrcTex->GetHeight() }, true);

	// Att
	AnimationClip* AttD = new AnimationClip(L"AttD", AttSrcTex, 1,
		Values::ZeroVec2,
		{ AttSrcTex->GetWidth() * 0.25f, AttSrcTex->GetHeight() });

	AnimationClip* AttU = new AnimationClip(L"AttU", AttSrcTex, 1,
		{ AttSrcTex->GetWidth() * 0.25f, 0 },
		{ AttSrcTex->GetWidth() * 0.25f * 2, AttSrcTex->GetHeight() });

	AnimationClip* AttL = new AnimationClip(L"AttL", AttSrcTex, 1,
		{ AttSrcTex->GetWidth() * 0.25f * 2, 0 },
		{ AttSrcTex->GetWidth() * 0.25f * 3, AttSrcTex->GetHeight() });

	AnimationClip* AttR = new AnimationClip(L"AttR", AttSrcTex, 1,
		{ AttSrcTex->GetWidth() * 0.25f * 3, 0 },
		{ AttSrcTex->GetWidth() * 0.25f * 4 , AttSrcTex->GetHeight()});

	// Item
	AnimationClip* Item = new AnimationClip(L"Item", ItemSrcTex, 1,
		Values::ZeroVec2,
		{ ItemSrcTex->GetWidth(), ItemSrcTex->GetHeight()});

	// Dead
	AnimationClip* Dead = new AnimationClip(L"Dead", DeadSrcTex, 1,
		Values::ZeroVec2,
		{ DeadSrcTex->GetWidth(), DeadSrcTex->GetHeight() });

	// Sword
	Texture2D* SwordSrcTex = new Texture2D(TexturePath + L"Player/Sword/SpriteInHandD.png");
	AnimationClip* SowrdD = new AnimationClip(L"SowrdD", SwordSrcTex, 1,
		Values::ZeroVec2,
		{ SwordSrcTex->GetWidth(), SwordSrcTex->GetHeight() });

	SwordSrcTex = new Texture2D(TexturePath + L"Player/Sword/SpriteInHandU.png");
	AnimationClip* SowrdU = new AnimationClip(L"SowrdU", SwordSrcTex, 1,
		Values::ZeroVec2,
		{ SwordSrcTex->GetWidth(), SwordSrcTex->GetHeight() });

	SwordSrcTex = new Texture2D(TexturePath + L"Player/Sword/SpriteInHandL.png");
	AnimationClip* SowrdL = new AnimationClip(L"SowrdL", SwordSrcTex, 1,
		Values::ZeroVec2,
		{ SwordSrcTex->GetWidth(), SwordSrcTex->GetHeight() });

	SwordSrcTex = new Texture2D(TexturePath + L"Player/Sword/SpriteInHandR.png");
	AnimationClip* SowrdR = new AnimationClip(L"SowrdR", SwordSrcTex, 1,
		Values::ZeroVec2,
		{ SwordSrcTex->GetWidth(), SwordSrcTex->GetHeight() });
	
	Animator* ani = new Animator();
	Animator* attAni = new Animator();

	ani->AddAnimClip(IdleD);
	ani->AddAnimClip(IdleU);
	ani->AddAnimClip(IdleL);
	ani->AddAnimClip(IdleR);

	ani->AddAnimClip(MoveD);
	ani->AddAnimClip(MoveU);
	ani->AddAnimClip(MoveL);
	ani->AddAnimClip(MoveR);

	ani->AddAnimClip(AttD);
	ani->AddAnimClip(AttU);
	ani->AddAnimClip(AttL);
	ani->AddAnimClip(AttR);

	ani->AddAnimClip(Item);

	ani->AddAnimClip(Dead);

	attAni->AddAnimClip(SowrdD);
	attAni->AddAnimClip(SowrdU);
	attAni->AddAnimClip(SowrdL);
	attAni->AddAnimClip(SowrdR);

	body->SetAnimator(ani);
	body->GetAnimator()->SetCurrentAnimClip(L"IdleD");

	attMotion->SetAnimator(attAni);
	attMotion->GetAnimator()->SetCurrentAnimClip(L"SowrdD"); 
	

	SAFE_DELETE(SwordSrcTex);
	SAFE_DELETE(DeadSrcTex);
	SAFE_DELETE(ItemSrcTex);
	SAFE_DELETE(AttSrcTex);
	SAFE_DELETE(WalkSrcTex);
	SAFE_DELETE(IdleSrcTex);

	body->SetPosition(position);
	body->SetSize(size);

	body->UpdateWorld();
	attMotion->UpdateWorld();

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			bStay[i][j] = false;
		}
	}
}

Player::~Player()
{
	SAFE_DELETE(body);
	SAFE_DELETE(attMotion);
}

void Player::Update()
{
	Move();

	attMotion->Update();
	body->SetPosition(position);
	body->SetSize(size);
	body->Update();
}

void Player::Render()
{
	if (bDef != true) attMotion->Render();
	body->Render();
}

void Player::Move()
{
	if(bAtt == false){
		if (Keyboard::Get()->Press('W')) {
			attMotion->SetPosition(
				{ position.x , position.y + swordRange, position.z }
			);
			type = AnimType::Up;
			SetAni(type);
			moveU = true;
			position.y += MoveSpd * Time::Delta();
		}
		if (Keyboard::Get()->Up('W')) {
			moveU = false;
			type = AnimType::IdleU;
			SetAni(type);
		}

		else if (Keyboard::Get()->Press('S')) {
			attMotion->SetPosition(
				{ position.x, position.y - swordRange, position.z }
			);
			type = AnimType::Down;
			SetAni(type);
			moveD = true;
			position.y -= MoveSpd * Time::Delta();
			if (Keyboard::Get()->Press('W') && moveU == false) {
				type = AnimType::Up;
				SetAni(type);
				position.y += (MoveSpd * 2) * Time::Delta();
			}
		}
		if (Keyboard::Get()->Up('S')) {
			type = AnimType::IdleD;
			SetAni(type);
			moveD = false;
		}

		else if (Keyboard::Get()->Press('A') && moveU == false && moveD == false) {
			attMotion->SetPosition(
				{ position.x - swordRange + 1, position.y - 1, position.z }
			);
			type = AnimType::Left;
			SetAni(type);
			moveL == true;
			position.x -= MoveSpd * Time::Delta();
		}
		if (Keyboard::Get()->Up('A')) {
			type = AnimType::IdleL;
			SetAni(type);
			moveL = false;
		}

		if (Keyboard::Get()->Press('D') && moveU == false && moveD == false) {
			attMotion->SetPosition(
				{ position.x + swordRange, position.y, position.z }
			);
			type = AnimType::Right;
			SetAni(type);
			moveR = true;
			position.x += MoveSpd * Time::Delta();
		}

		if (Keyboard::Get()->Up('D')) {
			type = AnimType::IdleR;
			SetAni(type);
			moveD = false;
		}	
	}

	if (Keyboard::Get()->Press('L')) {
		if (type == AnimType::IdleD || type == AnimType::Down) {
			type = AnimType::AttD;
			SetAni(type);
		}
		else if (type == AnimType::IdleU || type == AnimType::Up) {
			type = AnimType::AttU;
			SetAni(type);
		}
		else if (type == AnimType::IdleL || type == AnimType::Left) {
			type = AnimType::AttL;
			SetAni(type);
		}
		else if (type == AnimType::IdleR || type == AnimType::Right) {
			type = AnimType::AttR;
			SetAni(type);
		}
		bAtt = true;
		bDef = false;
	}

	if (Keyboard::Get()->Up('L') && canAtt == true) {
		if (type == AnimType::AttD) {
			type = AnimType::IdleD;
			SetAni(type);
		}
		else if (type == AnimType::AttU) {
			type = AnimType::IdleU;
			SetAni(type);
		}
		else if (type == AnimType::AttL) {
			type = AnimType::IdleL;
			SetAni(type);
		}
		else if (type == AnimType::AttR) {
			type = AnimType::IdleR;
			SetAni(type);
		}
		bAtt = false;
		bDef = true;
	}
}

void Player::SetAni(AnimType type)
{
	switch (type) {
	// Idle
	case AnimType::IdleD:{
		body->GetAnimator()->SetCurrentAnimClip(L"IdleD");
	}break;

	case AnimType::IdleU:{
		body->GetAnimator()->SetCurrentAnimClip(L"IdleU");
	}break;

	case AnimType::IdleL:{
		body->GetAnimator()->SetCurrentAnimClip(L"IdleL");
	}break;

	case AnimType::IdleR:{
		body->GetAnimator()->SetCurrentAnimClip(L"IdleR");
	}break;

	// Move
	case AnimType::Down:{
		body->GetAnimator()->SetCurrentAnimClip(L"MoveD");
	}break;

	case AnimType::Up:{
		body->GetAnimator()->SetCurrentAnimClip(L"MoveU");
	}break;

	case AnimType::Left:{
		body->GetAnimator()->SetCurrentAnimClip(L"MoveL");
	}break;

	case AnimType::Right:{
		body->GetAnimator()->SetCurrentAnimClip(L"MoveR");
	}break;

	// Att -> 칼이 첫 포지션은 잘 잡는데 이동후 포지션을 못잡음
	case AnimType::AttD:{
		body->GetAnimator()->SetCurrentAnimClip(L"AttD");
		attMotion->GetAnimator()->SetCurrentAnimClip(L"SowrdD");
	}break;

	case AnimType::AttU:{
		body->GetAnimator()->SetCurrentAnimClip(L"AttU");
		
		attMotion->GetAnimator()->SetCurrentAnimClip(L"SowrdU");
	}break;

	case AnimType::AttL:{
		body->GetAnimator()->SetCurrentAnimClip(L"AttL");
		
		attMotion->GetAnimator()->SetCurrentAnimClip(L"SowrdL");
	}break;

	case AnimType::AttR:{
		body->GetAnimator()->SetCurrentAnimClip(L"AttR");
		attMotion->GetAnimator()->SetCurrentAnimClip(L"SowrdR");
	}break;

	// Item
	case AnimType::Item:{
		body->GetAnimator()->SetCurrentAnimClip(L"Item");
	}break;

	// Dead
	case AnimType::Dead:{
		body->GetAnimator()->SetCurrentAnimClip(L"Dead");
	}break;
	
	default:
		break;
	}
}

void Player::setStay(int y, int x)
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (bStay[i][j] == true) {
				bStay[i][j] = false;
				break;
			}
		}
	}
	bStay[y][x] = true;
}

void Player::GUI()
{
	body->GUI("Player");
	attMotion->GUI("Motion");
}

string Player::MakeLable(string lable)
{
	// 자기 자신의 주소를 매계변수로 받은 라벨 뒤에 직접 적음
	string Label = lable + "##" + to_string((uint)this);

	return Label;
}
