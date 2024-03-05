#pragma once
#include "SpriteGo.h"
#include "Animator.h"

class Isaac : public SpriteGo
{
public:
	struct ClipInfo                   
	{
		std::string idle;
		std::string move;
		bool filpX = false;
		sf::Vector2f point;

		ClipInfo()
		{
		}

		ClipInfo(const std::string& idle, const std::string& move, bool flipX, const sf::Vector2f& point)
			: idle(idle), move(move), filpX(flipX), point(point)
		{
		}
	};
protected:
	Animator animator;

	sf::Vector2f direction;
	float speed = 250.f;

	int maxHp = 500;
	int hp;

	bool isAlive = true;
	bool isNoDamage = false;
	float noDamageTimer = 0.f;
	float noDamageInterval = 1.f;

	std::vector<ClipInfo> clipInfos;
	ClipInfo currentClipInfo;

public:
	Isaac(const std::string& name = "");
	~Isaac() override = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void FixedUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void OnDamage(int damage);
	void OnDie();

};

