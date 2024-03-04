#pragma once
#include "SpriteGo.h"
#include "Animator.h"

class AniTest : public SpriteGo            //애니매이션 테스트.
{
protected:
	Animator animator;

	float gravity = 500.f;
	float speed = 500.f;
	sf::Vector2f velocity;   //방향 * 스피드
	bool isGrounded = true;

public:
	AniTest(const std::string& name = "");
	~AniTest() override;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
};

