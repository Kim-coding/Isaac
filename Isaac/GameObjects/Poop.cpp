#include "pch.h"
#include "Poop.h"
#include "SceneDev1.h"

Poop::Poop(const std::string& name)
	:SpriteGo(name)
{
}

Poop::~Poop()
{
}

void Poop::Init()
{
	SpriteGo::Init();
	SetTexture("graphics/Poop1.png");
	hasHitBox = true;
}

void Poop::Release()
{
	SpriteGo::Release();
}

void Poop::Reset()
{
	SpriteGo::Reset();

	player = dynamic_cast<PlayerIsaac*>(SCENE_MGR.GetCurrentScene()->FindGo("Isaac"));
	sceneDev1 = dynamic_cast<SceneDev1*>(SCENE_MGR.GetCurrentScene());
}

void Poop::Update(float dt)
{
	SpriteGo::Update(dt);

	if (count = 4)
	{
		SetTexture("graphics/Poop4.png");
	}
	if (count = 3)
	{
		SetTexture("graphics/Poop3.png");
	}
	if (count = 2)
	{
		SetTexture("graphics/Poop2.png");
	}
	if (count = 1)
	{
		SetTexture("graphics/Poop1.png");
	}
}
