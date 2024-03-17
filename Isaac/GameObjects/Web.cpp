#include "pch.h"
#include "Web.h"
#include "SceneDev1.h"

Web::Web(const std::string& name)
	:SpriteGo(name)
{
}

Web::~Web()
{
}

void Web::Init()
{
	SpriteGo::Init();
	hasHitBox = true;
}

void Web::Release()
{
	SpriteGo::Release();
}

void Web::Reset()
{
	SpriteGo::Reset();

	player = dynamic_cast<PlayerIsaac*>(SCENE_MGR.GetCurrentScene()->FindGo("Isaac"));
	sceneDev1 = dynamic_cast<SceneDev1*>(SCENE_MGR.GetCurrentScene());

}

void Web::Update(float dt)
{
	SpriteGo::Update(dt);
}
