#include "pch.h"
#include "Isaac.h"

Isaac::Isaac(const std::string& name)
	:SpriteGo(name)
{
}

void Isaac::Init()
{
	SpriteGo::Init();
	std::string textureId = "graphics/Monstro.png";
	SetOrigin(Origins::MC);

	animator.SetTarget(&sprite);



	hasHitBox = true;
}

void Isaac::Release()
{
	SpriteGo::Release();
}

void Isaac::Reset()
{
	animator.Play("animators/IdleDown.csv");
	SetOrigin(Origins::MC);
	SetPosition({ 0.f,0.f });
	SetFlipX(false);

	//currentClipInfo = clipInfos[6];
}

void Isaac::Update(float dt)
{
	SpriteGo::Update(dt);

	direction.x = InputMgr::GetAxis(Axis::Horizontal);
	direction.y = InputMgr::GetAxis(Axis::Vertical);
	sf::Vector2f pos = position + direction * speed * dt;
	SetPosition(pos);
}

void Isaac::FixedUpdate(float dt)
{
}

void Isaac::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);

}

void Isaac::OnDamage(int damage)
{
}

void Isaac::OnDie()
{
}
