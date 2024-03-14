#include "pch.h"
#include "Intro.h"

Intro::Intro(const std::string& name)
	:SpriteGo(name)
{
}

Intro::~Intro()
{
}

void Intro::Init()
{
	SpriteGo::Init();
	animator.SetTarget(&sprite);
}

void Intro::Reset()
{
	animator.Play("animators/Intro.csv");
	SetOrigin(Origins::BC);
	SetPosition({ 100.f,0.f });
}

void Intro::Update(float dt)
{
	SpriteGo::Update(dt);
}
