#include "pch.h"
#include "Tears.h"
#include "SceneDev1.h"

Tears::Tears(const std::string& name)
{
}

Tears::~Tears()
{
}

void Tears::Cry(const sf::Vector2f& dir, float s, int d)
{
	direction = dir;
	speed = s;
	damage = d;
}

void Tears::Init()
{
	SpriteGo::Init();
	SetTexture("graphics/tear.png");
	SetOrigin(Origins::ML);

	hasHitBox = true;
}

void Tears::Reset()
{
	SpriteGo::Reset();

	sceneDev1 = dynamic_cast<SceneDev1*>(SCENE_MGR.GetCurrentScene());

}

void Tears::Update(float dt)
{
	SetPosition(position + direction * speed * dt);     // �ʰ� �浹 ó��
	if (sceneDev1 != nullptr)                       
	{
		
	}
}

void Tears::FixedUpdate(float dt)                       //���Ϳ� �浹 ó��
{
}
