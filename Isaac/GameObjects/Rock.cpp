#include "pch.h"
#include "Rock.h"
#include "SceneDev1.h"

Rock::Rock(const std::string& name)
	:SpriteGo(name)
{
}

Rock::~Rock()
{
}

void Rock::Init()
{
	SpriteGo::Init();
	hasHitBox = true;
}

void Rock::Release()
{
	SpriteGo::Release();
}

void Rock::Reset()
{
	SpriteGo::Reset();

	SetOrigin(Origins::MC);
	player = dynamic_cast<PlayerIsaac*>(SCENE_MGR.GetCurrentScene()->FindGo("Isaac"));
	sceneDev1 = dynamic_cast<SceneDev1*>(SCENE_MGR.GetCurrentScene());

}

void Rock::Update(float dt)
{
	SpriteGo::Update(dt);
}

void Rock::OnBurst()
{
	if (!isAlive)
		return;

	isAlive = false;
	SetActive(false);
	sceneDev1->RemoveGo(this);
}
