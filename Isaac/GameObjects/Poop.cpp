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
}
