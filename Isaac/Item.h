#pragma once
#include "SpriteGo.h"

class PlayerIsaac;

class Item : public SpriteGo
{
public:
	enum class Types
	{
		None = -1,
		Boom,
		Health,
		Coin,
		Count,
	};

	static Item* Create(Types t);
protected:
	PlayerIsaac* player;
	Types type = Types::None;

public:
	Item(const std::string& name = "");
	~Item() override = default;

	Types GetType() const { return type; }

	void Init() override;
	void Release() override;

	void Reset() override;

	void Update(float dt) override;
	void LateUpdate(float dt) override;
	void FixedUpdate(float dt) override;

	void Draw(sf::RenderWindow& window) override;

};

