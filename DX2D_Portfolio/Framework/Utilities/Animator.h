#pragma once

// 요 클래스가 에니메이션 이미지 문할 모음
class AnimationClip {
public:
	friend class Animator;

	AnimationClip(wstring clipName, Texture2D* srcTex, UINT frameCount, Vector2 startPos, Vector2 endPos, bool Down = false, bool bReversed = false);

private:
	wstring clipName = L"";
	vector<Vector2> keyFarmes;
	UINT frameCount = 0;
	ID3D11ShaderResourceView* srv = nullptr;
	Vector2 texelFrameSize = Values::ZeroVec2;
	bool bReversed = false;
};

// 위에 있는 클립의 실행도구
class Animator {
public:
	Animator();
	~Animator();

	void Update();

	// 현제 실행중인 이미지 좌표값 반환
	Vector2 GetCurrentFrame() { return currentFrame; }

	// 현재 실행중인 이미지 UV값 반환
	Vector2 GetTexelFrameSize() { return currentClip->texelFrameSize; }

	// 이걸 택스쳐랙트가 받아서 이미지 가는거임
	// 현재 실행중인 이미지 SRV반환 (SRV == 실질적 그림데이터)
	ID3D11ShaderResourceView* GetCurrentSRV() { return currentClip->srv; }

	// ANIMCLIP에 클립 추가
	void AddAnimClip(AnimationClip* animClip);
	// 지금 실행 시킬 크립 지정
	void SetCurrentAnimClip(wstring clipName);

	// 클립 이름 반환
	wstring GetcureentClipName() { return currentClip->clipName; }
	// 실행중 애니메이션 속도 조절 (이미지 전호나 속도)
	void SetPlayeRate(float playRate) { this->playRate = playRate; }

private:
	unordered_map<wstring, AnimationClip*> animClips;
	bool CheckExist(wstring clipName) { return animClips.find(clipName) != animClips.end(); }
	
	AnimationClip* currentClip = nullptr;
	UINT currentFrameIndex = 0;
	Vector2 currentFrame = Values::ZeroVec2;
	
	// 이게 플레이 레이트보다 커지면 이미지를 바꿀꺼임
	float deltaTime = 0.0f;

	// 이미지 전환 속도
	float playRate = 1.0f / 15.0f;
};