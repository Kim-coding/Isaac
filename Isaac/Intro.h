#pragma once
#include "SpriteGo.h"
#include "Animator.h"

class Intro : public SpriteGo
{
protected:
	Animator animator;

public:
	Intro(const std::string& name = "");
	~Intro() override;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
};

