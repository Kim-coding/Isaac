#include "pch.h"
#include "Monster.h"

Monster::Monster(const std::string& name)
	:SpriteGo(name)
{
}

Monster::~Monster()
{
}

void Monster::Init()
{
	SpriteGo::Init();
}

void Monster::Release()
{
	SpriteGo::Release();

}

void Monster::Reset()
{
	SpriteGo::Reset();

}

void Monster::Update(float dt)
{
	SpriteGo::Update(dt);

}

void Monster::FixedUpdate(float dt)
{
	SpriteGo::FixedUpdate(dt);

}

void Monster::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);

}

void Monster::OnDamage(int damage)
{
}

void Monster::OnDie()
{
}
