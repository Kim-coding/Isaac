#include "pch.h"
#include "tears.h"

tears::tears(const std::string& name)
{
}

tears::~tears()
{
}

void tears::Cry(const sf::Vector2f& dir, float s, int d)
{
	direction = dir;
	speed = s;
	damage = d;
}

void tears::Init()
{
	SpriteGo::Init();
	SetTexture("graphics/tear.png");
	SetOrigin(Origins::ML);

	hasHitBox = true;
}

void tears::Reset()
{
	SpriteGo::Reset();
}

void tears::Update(float dt)
{
	SetPosition(position + direction * speed * dt);

}

void tears::FixedUpdate(float dt)
{
}
