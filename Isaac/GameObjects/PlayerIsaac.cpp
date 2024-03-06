#include "pch.h"
#include "PlayerIsaac.h"

PlayerIsaac::PlayerIsaac(const std::string& name)
	:SpriteGo(name)
{
}

PlayerIsaac::~PlayerIsaac()
{
}

void PlayerIsaac::Init()
{
	SpriteGo::Init();
}

void PlayerIsaac::Release()
{
	SpriteGo::Release();
}

void PlayerIsaac::Update(float dt)
{
	SpriteGo::Update(dt);
}

void PlayerIsaac::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

void PlayerIsaac::Cry()
{
}
