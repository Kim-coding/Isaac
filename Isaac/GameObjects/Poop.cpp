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

	if (isCount>=7)
	{
		SetActive(false);
	}
	if (isCount >= 6)
	{
		SetTexture("graphics/Poop4.png");
	}
	else if (isCount >= 5)
	{
		SetTexture("graphics/Poop3.png");
	}
	else if (isCount >= 4)
	{
		SetTexture("graphics/Poop2.png");
	}
	else if (isCount >= 2)
	{
		SetTexture("graphics/Poop1.png");
	}
} 


void Poop::AddCount()
{
	++isCount;
}
