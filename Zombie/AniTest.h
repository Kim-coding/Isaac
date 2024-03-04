#pragma once
#include "SpriteGo.h"
#include "Animator.h"

class AniTest : public SpriteGo            //�ִϸ��̼� �׽�Ʈ.
{
protected:
	Animator animator;

	float gravity = 500.f;
	float speed = 500.f;
	sf::Vector2f velocity;   //���� * ���ǵ�
	bool isGrounded = true;

public:
	AniTest(const std::string& name = "");
	~AniTest() override;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
};

