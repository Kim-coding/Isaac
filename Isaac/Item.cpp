#include "pch.h"
#include "Item.h"
#include "PlayerIsaac.h"

Item* Item::Create(Types t)
{
	Item* newItem = new Item("Item");

	switch (newItem->type)
	{
	case Types::Boom:
		//newItem->textureId = "graphics/.png";
		break;
	case Types::Health:
		newItem->textureId = "graphics/Health.png";
		break;
	case Types::Coin:
		//newItem->textureId = "graphics/.png";
		break;
	}

	return newItem;
}

Item::Item(const std::string& name)
	:SpriteGo(name)
{
}

void Item::Init()
{
}

void Item::Release()
{
}

void Item::Reset()
{
	SpriteGo::Reset();
	player = dynamic_cast<PlayerIsaac*>(SCENE_MGR.GetCurrentScene()->FindGo("Player"));
}

void Item::Update(float dt)
{
}

void Item::LateUpdate(float dt)
{
}

void Item::FixedUpdate(float dt)
{
	SpriteGo::FixedUpdate(dt);

	if (player == nullptr)
		return;

	if (GetGlobalBounds().intersects(player->GetGlobalBounds()))
	{
		player->OnItem(this);
		SetActive(false);
		SCENE_MGR.GetCurrentScene()->RemoveGo(this);
	}
}

void Item::Draw(sf::RenderWindow& window)
{
}
